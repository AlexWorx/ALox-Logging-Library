// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
//
// Notes:
// This tool replaces simple, pure 'integer' template instantiation nodes in doxygen
// dot files by their parameterized template class counterparts.
// This is a quick and dirty written piece of code.
// Maybe doxygen will support an option to remove instantiated classes some day.
// #################################################################################################
/**@file*///<- needed for Doxygen include of the using statements at the end of the file

// to preserve the right order, we are not includable directly from outside.
#include <alox/alox.hpp>
#include "alib/compatibility/std_iostream.hpp"
#include "alib/config/inifile.hpp"
#include "alib/system/system.hpp"
#include "alib/system/directory.hpp"

#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>

using namespace aworx;
using namespace std;


// #################################################################################################
// Globals
// #################################################################################################
bool     DebugMode;
IniFile* Inifile;
AString  FileName;
String   NewFileNameSuffix= ".corrected.dot";

// #################################################################################################
// Simple data structurs
// #################################################################################################
struct Content
{
    enum class Type{ Other, Node, Link };

    Type        type;
    Substring   LineRest;

    Content ( Type type) : type(type) {}
};

struct Node : public Content
{
    int       Num;
    Substring TClassName;
    String32  TParamName;
    bool      IsIntInstance   = false;
    int       TInstantiationNum  = -1;
    int       ReplacementNodeNum = -1;

    Node()  : Content( Content::Type::Node )  {}
};

struct Link : public Content
{
    int       From;
    int       To;
    bool      Skip               = false;
    Link()  : Content( Content::Type::Link ) {}
};

struct Line
{
    AString     original;
    Content*    content = nullptr;
};

struct DotFile
{
    list<Line>           Lines;
    list<Node*>          TClasses;
    list<Line*>          TClassesUntouched;
    vector<Node*>        ReplacedNodes;
    vector<Link*>        SortedLinks;
};

vector<pair<String8, String8>>   nodesToDelete;

DotFile dotFile;


// #################################################################################################
// Parse a single line and create content entry
// #################################################################################################
bool ParseLine( Line& fileLine )
{
    Substring line(fileLine.original);

    // Ignore lines not starting with "Node"
    if ( !line.Consume( "Node", Whitespaces::Trim ) )
        return true;

    // From now on, unknown means error (stop processing file)
    int nodeNum;
    if( !line.ConsumeInteger( nodeNum ) )
        return false;

    //------------- read node definition lines -------------
    if( line.Consume( "[label=\"", Whitespaces::Trim ) )
    {
        int idx= line.IndexOf( '\"' );
        if (idx < 0 )
            return false;

        Substring  lineRest;
        line.Split( idx, lineRest, 1 );
        Log_Verbose( String256() << "Found Node " << nodeNum << "=" << Format::Tab(14)  << line );

        // is template class node?
        idx= line.IndexOf( '<' );
        if ( idx < 0 )
            return true;

        // save information
        Node* node= new Node();
        fileLine.content=   node;
        node->Num=          nodeNum;
        node->LineRest=     lineRest;
        line.Consume<false>( idx - 1, &node->TClassName );

        // read contents of brackets
        line.Consume<false>( 2 );
        line.ConsumeFromEnd( '>', Whitespaces::Trim );
        line.ConsumeFromEnd();

        node->IsIntInstance=     line.ConsumeInteger( node->TInstantiationNum )
                             &&  line.Trim();


        // save if original name
        if ( !node->IsIntInstance )
        {
            line.Trim();
            if ( line.IndexOfAny(", &", Inclusion::Include) < 0  && isupper( node->TClassName.CharAtStart() ) )
            {
                node->TParamName= line;
                dotFile.TClasses.emplace_back( node );

                Log_Info( String64() << " Saveing param name: " << node->TParamName, 1 );
                Inifile->Save( nullptr, node->TClassName, node->TParamName, "auto generated", '\0' );
            }
            else
            {
                Log_Info( String128() << " Template param <" << line << "> found, not usable as parameter name", 1 );
                dotFile.TClassesUntouched.emplace_back( &fileLine );
            }

        }
        else
            Log_Info( String64() << " Template<NN> found", 1 );

        // OK
        return true;
    }

    //------------- read link lines -------------
    if( line.Consume( "-> Node", Whitespaces::Trim ) )
    {
        Link* link= new Link();
        fileLine.content=   link;
        link->From=         nodeNum;
        line.ConsumeInteger( link->To );
        link->LineRest=     line;

        return true;
    }

    // error: format not recognized
    return false;
}

// #################################################################################################
// Read/Write File
// #################################################################################################
int ReadFile()
{
    Log_Info( String512() << "Reading file: " << FileName );

    dotFile.Lines.clear();
    ifstream file( FileName.ToCString() );
    if ( !file.is_open() )
    {
        cerr << "DoxygenGraphTemplateInstanceRemover:  opening file: "<< FileName << endl;
        return -1;
    }

    lib::strings::ReadLineFromIStream readOp= lib::strings::ReadLineFromIStream( file );
    while( !readOp.IsEOF )
    {
        dotFile.Lines.emplace_back( Line() );
        dotFile.Lines.back().original << readOp;
        if( !ParseLine( dotFile.Lines.back() ) )
            return 0;
    }

    return dotFile.Lines.size();
}



// #################################################################################################
// Build all information needed to write the new file
// #################################################################################################
bool Build()
{
    Log_Info( String512() << "Building..." );

    // ------------ Nodes: find nodes that are to be replaced ------------
    Log_Info( String512() << "Searching replacement nodes..." );
    int qtyReplacements= 0;
    for ( Line& line : dotFile.Lines )
    {
        // not a node line
        if (    line.content == nullptr
             || line.content->type != Content::Type::Node )
            continue;

        // not a template int instantiation line
        Node* actNode= static_cast<Node*>(line.content);
        if ( !actNode->IsIntInstance )
            continue;

        // template instantiations: search main node
        bool found= false;
        for ( auto& replacementNode : dotFile.TClasses )
            if( actNode->TClassName.Equals( replacementNode ->TClassName ) )
            {
                qtyReplacements++;
                actNode->ReplacementNodeNum= replacementNode->Num;
                dotFile.ReplacedNodes.emplace_back( actNode );
                found= true;
                break;
            }

        // if no original TClass found, this instantiation Node will become the main!
        if ( !found )
        {
            // make this one the main node!
            actNode->IsIntInstance= false;

            if (!Inifile->Get( nullptr, actNode->TClassName, actNode->TParamName ) )
                actNode->TParamName= "T";

            Log_Info( String512() <<  "No general TClass found for this node. Using this node as target for all: "
                                  <<  actNode->TClassName << "<" << actNode->TInstantiationNum << ">"
                                  <<  ", with '" << actNode->TParamName << "' as parameter name."
                                  , 1);
            dotFile.TClasses.emplace_back(actNode);
        }
    }

    if ( qtyReplacements == 0 )
    {
        Log_Info( String512() << "Nothing to replace. Using original file." );
        return false;
    }

    Log_Info( String512() <<  dotFile.TClasses.size() << " TClass(es) found:" );
    Log_Prune ( for( auto tClass : dotFile.TClasses )               )
        Log_Verbose( String32() <<tClass->TClassName, 1 )


    // sort nodes
    std::sort( begin(dotFile.ReplacedNodes), end( dotFile.ReplacedNodes ),
              [](Node* n1, Node* n2) { return n1->Num < n2->Num; } );

    Log_Info( String512() << "Replacement nodes sorted" );
    Log_Prune( for (auto n : dotFile.ReplacedNodes) { )
        Log_Verbose( String512() << n->Num << " \"" << n->TClassName <<'\"' << Format::Tab(20)
                    << "   ->  " << n->ReplacementNodeNum ,1 );
    Log_Prune( } )


    // ------------ Links: set new node numbers ------------
    Log_Info( String512() << "Processing links: Replace nodes and sort..." );
    for ( Line& line : dotFile.Lines )
    {
        if ( line.content == nullptr )
            continue;

        if ( line.content->type == Content::Type::Link )
        {
            Link* link= static_cast<Link*>(line.content);
            dotFile.SortedLinks.emplace_back(link);

            // search and set replace node for 'from' node
            auto it=
            std::lower_bound( begin(dotFile.ReplacedNodes), end( dotFile.ReplacedNodes ),
                              nullptr,
                              [link](Node* n, Node* ){ return n->Num < link->From; } );

            if( it != dotFile.ReplacedNodes.end() && (*it)->Num == link->From )
                link->From= (*it)->ReplacementNodeNum;


            // search and set replace node for 'to' node
            it=
            std::lower_bound( begin(dotFile.ReplacedNodes), end( dotFile.ReplacedNodes ),
                              nullptr,
                              [link](Node* n, Node* ){ return n->Num < link->To; } );

            if( it != dotFile.ReplacedNodes.end() && (*it)->Num == link->To )
                link->To= (*it)->ReplacementNodeNum;
        }
    }

    // sort links
    std::sort( begin(dotFile.SortedLinks), end( dotFile.SortedLinks ),
              [](Link* l1, Link* l2)
              {
                return l1->From != l2->From ? l1->From < l2->From
                                            : l1->To   < l2->To;
              } );

    Log_Prune( for (auto n : dotFile.SortedLinks) { )
        Log_Verbose( String512() << n->From << " -> " << n->To, 1  );
    Log_Prune( } )

    // ------------ remove double links ------------
    Log_Info( String512() << "Removing double links..." );
    Link* lastLink= nullptr;
    for( Link* link : dotFile.SortedLinks )
    {
        if (    lastLink != nullptr
             && lastLink->From == link->From
             && lastLink->To   == link->To
             && link->LineRest.IndexOfAS("label=") < 0 )
        {
            Log_Verbose( String512() << "Removing link: "
                                     << "  Node"   << link->From << " -> Node" << link->To
                                     << link->LineRest
                         , 1 );
            link->Skip= true;
            continue;
        }
        lastLink= link;
    }

    return true;
}

bool WriteFile()
{
    Log_Info( String512() << "Writing file " );

    // create file or redirect to cout (in debug mode)
    ofstream* file= nullptr;
    if (!DebugMode)
    {
        FileName._(NewFileNameSuffix);
        file= new ofstream( FileName.ToCString() );
        if ( !file->is_open() )
        {
            cerr << "DoxygenGraphTemplateInstanceRemover: Error writing file" << endl;
            return false;
        }
    }
    ostream& out= DebugMode ? cout : *file;

    Log_Info( String512() << "Untouched stuff" );

    // write file
    bool nodesAndLinksWritten= false;
    for ( Line& line : dotFile.Lines )
    {
        // write untouched lines
        if( line.content == nullptr )
        {
            out << line.original << endl;
            continue;
        }

        // write our stuff once the first node/link line comes
        if ( !nodesAndLinksWritten )
        {
            nodesAndLinksWritten= true;

            Log_Info( String512() << "Writing Nodes" );

            // write nodes
            Log_Info( String512() << "Writing untouched template nodes" );
            for( Line* nline : dotFile.TClassesUntouched )
            {
                out << nline->original << endl;
            }

            // write nodes
            Log_Info( String512() << "Writing template replacement nodes" );
            for( Node* node : dotFile.TClasses )
            {
                out  << "  Node" << node->Num << " [label=\"" << node->TClassName
                     << "\\< " << node->TParamName << " \\>\""
                     << node->LineRest << endl;
            }

            // write links
            Log_Info( String512() << "Writing links" );
            for( Link* link : dotFile.SortedLinks )
                if ( !link->Skip )
                    out << "  Node"   << link->From  << " -> Node" << link->To << link->LineRest << endl;
            Log_Info( String512() << "The rest is untouched stuff again" );
        }
    }

    // check
    if (!nodesAndLinksWritten)
    {
        FileName.DeleteEnd( NewFileNameSuffix.Length() );
        cerr << "Error: Nodes and Links not written: " << FileName << endl;
    }
    else
        Log_Info( String512() << "Replaced File: " << FileName );

    if (!DebugMode)
        delete file;

    return true;
}

// #################################################################################################
// InvokeDotAndExit
// #################################################################################################
void     InvokeDotAndExit( int argc, char *argv[] )
{
    if (DebugMode )
        return;

    //----- invoking dot ---------
    AString dotCommand("dot");
    dotCommand._(' ')._(FileName);
    for( int i= 2; i< argc ; i++ )
        dotCommand << ' ' << argv[i];

    FILE* pipe = popen( dotCommand.ToCString(), "r");

    string result;
    if (!pipe)
    {
        cerr << "Error invoking command: `" << dotCommand << '`'  << endl;
        cerr << "              returned: "  << result             << endl;

        exit(2);
    }

    pclose(pipe);

    exit(0);
}



int main(int argc, char *argv[])
{
    DebugMode= argc==1;

    // init ALib/ALox
    Log::Init( Inclusion::Exclude, argc, (void**) argv);
    Log_AddDebugLogger();
    Log_SetDomain( "DOXGRAPH", Log::Scope::SourceFile );
    Log_SetDomain( "DOXGRAPH", System::IsDebuggerPresent() ?  Log::DomainLevel::All
                                                           :  Log::DomainLevel::WarningsAndErrors );

    Log_Prune( if ( DebugMode ) )
    Log_SetDomain( "DOXGRAPH", Log::DomainLevel::All);


    if (!DebugMode )
    {
        lib::Report::GetDefault().PushHaltFlags( false, false );
        FileName= argv[1];
    }
    else
    {
        //String debugFile( "/classaworx_1_1lox_1_1core_1_1textlogger_1_1ObjectConverter__coll__graph.dot" );
        //String debugFile( "/classaworx_1_1lib_1_1strings_1_1ASTerminatable__inherit__graph.dot");
        //String debugFile( "/classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger__inherit__graph.dot");
        //String debugFile( "/classaworx_1_1lox_1_1core_1_1textlogger_1_1MetaInfo__coll__graph.dot" );
        //String debugFile( "/classaworx_1_1lox_1_1loggers_1_1AnsiConsoleLogger__coll__graph.dot" );
        String debugFile( "/classaworx_1_1lox_1_1core_1_1textlogger_1_1TextLogger__coll__graph.dot" );

        FileName._("../html/cpp_ref");
        for( int depth= 0; depth < 10 ; depth++ )
        {
            if ( Directory::Exists( FileName ) )
            {
                FileName._( debugFile );
                break;
            }
            FileName.InsertAt( "../", 0 );
        }
    }

    // read ini file
    Inifile= new IniFile("doxygenDotFixer.cfg");

    Inifile->AutoSave=      true;
    Inifile->FileComments=
     "======================================================================================" "\n" \
     "ALib - A-Worx Utility Library"                                                          "\n" \
     "(c) 2013-2016 A-Worx GmbH, Germany"                                                     "\n" \
     "Published under MIT License (Open Source License, see LICENSE.txt)"                     "\n" \
     "======================================================================================" "\n" \
     "This tool replaces simple, pure integer template instantiation nodes in doxygen"        "\n" \
     "dot files by their parameterized template class counterparts."                          "\n" \
     "--------------------------------------------------------------------------------------" "\n" \
     "This cfg-file is auto generated."                                                       "\n" \
     "Template parameter names detected across invocations are stored here."                 "\n" \
     "--------------------------------------------------------------------------------------" "\n" \
     ;

    // do it
    if( ReadFile() &&  Build() )
        WriteFile();

    InvokeDotAndExit( argc, argv );

    // cleanup
    for( Line& line : dotFile.Lines )
        if ( line.content != nullptr )
        {
            if ( line.content->type == Content::Type::Link )
                delete static_cast<Link*>( line.content );
            else
                delete static_cast<Node*>( line.content );
        }

    delete Inifile;
    FileName.SetNull();
    Log::TerminationCleanUp();

    return 0;
}

