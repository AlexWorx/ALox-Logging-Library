// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"

#if !defined (HPP_ALIB_CONFIG_INI_FILE)
    #include "alib/config/inifile.hpp"
#endif
#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif
#if !defined (HPP_ALIB_SYSTEM_DIRECTORY)
    #include "alib/system/directory.hpp"
#endif

#include "alib/strings/util/spaces.hpp"
#include "alib/compatibility/std_iostream.hpp"


#define TESTCLASSNAME       CPP_ALib_Containers
#include "aworx_unittests.hpp"


#include <iostream>
#include <fstream>

using namespace std;
using namespace aworx;

namespace ut_aworx {

//--------------------------------------------------------------------------------------------------
//--- StringTree_Cursor
//--------------------------------------------------------------------------------------------------
bool valueSorter(const AString& lhs, const AString& rhs)
{
    return lhs.CompareTo(rhs, Case::Ignore) < 0 ;
}


UT_CLASS()


template <typename TIterator>
int IteratorCount( TIterator copyOfIt, const TIterator& end, bool debugOutput=false )
{
    if( debugOutput )
        cout << "Dbg output: " << endl;
    int cnt= 0;
    while ( copyOfIt != end )
    {
        if( debugOutput )
            cout << cnt << " D=" << copyOfIt.Depth() << " N= \""<< copyOfIt.Name() <<"\"  V=" << *copyOfIt
                 <<   "  #children=  "<< copyOfIt.Size() <<endl;
        ++cnt;
        ++copyOfIt;
    }
    return cnt;
}

UT_METHOD(StringTree_Cursor)
{
    UT_INIT();

    cout << "\nCursor():" << endl;
    cout << "Build string tree without using cursor navigation" << endl;
    StringTree<const char*> pm;
    auto cursor=   pm.Root();       *cursor= "root";

    cursor= pm.Root();                                    *cursor=  "root" ;
           UT_TRUE( cursor.MoveToChildCreate( "a"    ) ); *cursor= "a--"    ;
           UT_TRUE( cursor.MoveToChildCreate( "A"    ) ); *cursor= "aA-"    ;
           UT_TRUE( cursor.MoveToChildCreate( "1"    ) ); *cursor= "aA1"    ;
    UT_TRUE(  cursor.MoveToParent() ); UT_TRUE( cursor.MoveToChildCreate( "b"    ) ); *cursor= "aab"    ;
    UT_TRUE(  cursor.MoveToParent() ); UT_TRUE( cursor.MoveToChildCreate( "c"    ) ); *cursor= "aac"    ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/B"    ); *cursor= "aB-"   ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/B/1"  ); *cursor= "aB1"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/B/2"  ); *cursor= "aB2"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/B/3"  ); *cursor= "aB3"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/C"    ); *cursor= "aC-"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/C/1"  ); *cursor= "aC1"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/C/2"  ); *cursor= "aC2"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/C/3"  ); *cursor= "aC3"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b"      ); *cursor= "b--"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/A"    ); *cursor= "bA-"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/A/1"  ); *cursor= "bA1"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/A/2"  ); *cursor= "bA2"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/A/3"  ); *cursor= "bA3"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/B"    ); *cursor= "bB-"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/B/1"  ); *cursor= "bB1"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/B/2"  ); *cursor= "bB2"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/B/3"  ); *cursor= "bB3"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/C"    ); *cursor= "bC-"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/C/1"  ); *cursor= "bC1"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/C/2"  ); *cursor= "bC2"  ;
    cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/C/3"  ); *cursor= "bC3"  ;

    cout << "Check construction (sizes of some branches)" << endl;
    auto iter= pm.begin();                                     UT_EQ( 27, IteratorCount( iter, pm.end() ) );
//    iter.SetSorted( SortOrder::Ascending, Case::Sensitive ); UT_TRUE(  iter == pm.begin() );

              cursor= pm.Root();                            cursor.SetIterator( iter, 0 ); UT_EQ( 0, cursor.Depth() ); UT_EQ( 27, IteratorCount( iter, pm.end() ) );
    UT_TRUE( (cursor= pm.Root()).MoveToChild("a"  )    );   cursor.SetIterator( iter, 0 ); UT_EQ( 13, IteratorCount( iter, pm.end() ) );
    UT_TRUE( (cursor= pm.Root()).MoveTo     ("a/B")    );   cursor.SetIterator( iter, 0 ); UT_EQ(  4, IteratorCount( iter, pm.end() ) );
    UT_TRUE( (cursor= pm.Root()).MoveTo     ("a/B/3")  );   cursor.SetIterator( iter, 0 ); UT_EQ(  1, IteratorCount( iter, pm.end() ) );
    UT_FALSE((cursor= pm.Root()).MoveTo     ("a/B/3/e"));   cursor.SetIterator( iter, 0 ); UT_EQ( 27, IteratorCount( iter, pm.end() ) ); UT_TRUE(  iter == pm.begin() );
    UT_FALSE((cursor= pm.Root()).MoveTo     ("ab/ce")  );   cursor.SetIterator( iter, 0 ); UT_EQ( 27, IteratorCount( iter, pm.end() ) ); UT_TRUE(  iter == pm.begin() );


    cout << "Cursor navigation"  << endl;

    cursor= pm.Root(); UT_TRUE(  cursor.MoveTo("a"           )); UT_EQ( 13, IteratorCount(cursor.SetIterator(iter, 0 ), pm.end() ) );
    cursor= pm.Root();                                           UT_EQ(  2, IteratorCount(cursor.SetIterator(iter, 1 ), pm.end() ) );
    cursor= pm.Root(); UT_TRUE(  cursor.MoveTo("a"           )); UT_EQ(  3, IteratorCount(cursor.SetIterator(iter, 1 ), pm.end() ) );
    cursor= pm.Root(); UT_FALSE( cursor.MoveTo("XYZ"         )); UT_EQ( 27, IteratorCount(cursor.SetIterator(iter, 0 ), pm.end() ) );
    cursor= pm.Root(); UT_TRUE ( cursor.MoveTo("b"           )); UT_EQ( 13, IteratorCount(cursor.SetIterator(iter, 0 ), pm.end() ) );
    cursor= pm.Root(); UT_FALSE( cursor.MoveToChildCreate("a")); UT_EQ( 13, IteratorCount(cursor.SetIterator(iter, 0 ), pm.end() ) );

    cursor= pm.Root(); UT_TRUE ( cursor.MoveTo("a/B/./1"     )); UT_EQ(  1, IteratorCount(cursor.SetIterator(iter, 0 ), pm.end() ) );
    cursor= pm.Root(); UT_TRUE ( cursor.MoveTo("a/B/1/../1"  )); UT_EQ(  1, IteratorCount(cursor.SetIterator(iter, 0 ), pm.end() ) );

    cursor= pm.Root(); UT_TRUE ( cursor.MoveTo("a/B/1"  )); UT_EQ(  "aB1", *cursor );
                       UT_TRUE ( cursor.MoveTo("../2"   )); UT_EQ(  "aB2", *cursor );
                       UT_FALSE( cursor.MoveTo("b"      )); UT_EQ(  "aB2", *cursor );
                       UT_TRUE ( cursor.MoveTo("/b"     )); UT_EQ(  "b--", *cursor );
                       UT_TRUE ( cursor.MoveTo("./C"    )); UT_EQ(  "bC-", *cursor );


    cout << "Up"  << endl;
    UT_TRUE( (cursor= pm()).MoveTo( "a/B/3" ) );
                                                UT_EQ( "3",        cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_FALSE( cursor.IsRoot() );
    cursor.MoveToParent();                      UT_EQ( "B"       , cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_FALSE( cursor.IsRoot() );
    cursor.MoveToParent<false>();               UT_EQ( "a"       , cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_FALSE( cursor.IsRoot() );
    cursor.MoveToParent<true>();                UT_EQ( NullString, cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_TRUE(  cursor.IsRoot() );
    cursor.MoveToParent<true>();                UT_EQ( NullString, cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_TRUE(  cursor.IsRoot() );
    cursor.MoveToParent();                      UT_EQ( NullString, cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_TRUE(  cursor.IsRoot() );
    cursor.MoveToParent<false>();  UT_TRUE ( cursor.IsInvalid() );

    cout << "GetPath"  << endl;
    AString path;
    cursor= pm(); cursor.MoveToParentUnchecked(); cursor.SearchPath( path );  UT_TRUE ( path.IsNull() );
    cursor= pm();                                 cursor.SearchPath( path );  UT_FALSE( path.IsNull() ); UT_TRUE( path.IsEmpty() );
    cursor= pm(); cursor.MoveTo("a"      );       cursor.SearchPath( path );  UT_EQ   ( "a"        , path);
    cursor= pm(); cursor.MoveTo("a/b"    );       cursor.SearchPath( path );  UT_EQ   ( ""         , path);
    cursor= pm(); cursor.MoveTo("a/B"    );       cursor.SearchPath( path );  UT_EQ   ( "a/B"      , path);
    cursor= pm(); cursor.MoveTo("a/B/1"  );       cursor.SearchPath( path );  UT_EQ   ( "a/B/1"    , path);

    cout << "Iterators"  << endl;
    {
         cursor= pm.Root(); auto it= cursor.begin( 0 );  UT_EQ( 27, IteratorCount( it, pm.end() ) );

         cursor= pm.Root();                  cursor.SetIterator(it, 0); UT_EQ( 27, IteratorCount( it, pm.end() ) );
         cursor= pm.Root();                  cursor.SetIterator(it,99); UT_EQ( 26, IteratorCount( it, pm.end() ) );
         cursor= pm.Root();                  cursor.SetIterator(it, 3); UT_EQ( 26, IteratorCount( it, pm.end() ) );
         cursor= pm.Root();                  cursor.SetIterator(it, 2); UT_EQ(  8, IteratorCount( it, pm.end() ) );
         cursor= pm.Root();                  cursor.SetIterator(it, 1); UT_EQ(  2, IteratorCount( it, pm.end() ) );

        (cursor= pm.Root()).MoveTo("a"    ); cursor.SetIterator(it, 0); UT_EQ( 13, IteratorCount( it, pm.end() ) );
        (cursor= pm.Root()).MoveTo("a"    ); cursor.SetIterator(it, 2); UT_EQ( 12, IteratorCount( it, pm.end() ) );
        (cursor= pm.Root()).MoveTo("a"    ); cursor.SetIterator(it, 1); UT_EQ(  3, IteratorCount( it, pm.end() ) );
        (cursor= pm.Root()).MoveTo("a/A"  ); cursor.SetIterator(it, 0); UT_EQ(  4, IteratorCount( it, pm.end() ) );
        (cursor= pm.Root()).MoveTo("a/A"  ); cursor.SetIterator(it, 1); UT_EQ(  3, IteratorCount( it, pm.end() ) );
        (cursor= pm.Root()).MoveTo("a/A/1"); cursor.SetIterator(it, 0); UT_EQ(  1, IteratorCount( it, pm.end() ) );
        (cursor= pm.Root()).MoveTo("a/A/1"); cursor.SetIterator(it, 1); UT_EQ(  0, IteratorCount( it, pm.end() ) );

        // quick test for range it on cursor
        {
            (cursor= pm.Root()).MoveTo("a");
            int cnt= 0;
            for( auto rangeIt : cursor )
            {
                (void) rangeIt;
                cnt++;
            }
            UT_EQ(  3, cnt);
            cnt= 0;
            std::for_each( cursor.begin( 5 ), cursor.end(), [&cnt]( const char*& x ) {(void)x; cnt++; } );
            UT_EQ(  12, cnt);
        }

    }


    cout << "Erase nodes" << endl;
    iter= pm.begin(); UT_EQ(27, IteratorCount(iter, pm.end() ) );
    cursor= decltype(pm)::Cursor( iter );
    UT_TRUE(cursor.MoveTo( "a/B/3"  ));               UT_EQ( "3"       , cursor.SearchName() ); UT_EQ( 0, cursor.Size() ); UT_EQ( 1, IteratorCount(cursor.SetIterator(iter, 0), pm.end() ) ); UT_FALSE( cursor.IsRoot() );
    cursor.DeleteChildren();                          UT_EQ( "3"       , cursor.SearchName() ); UT_EQ( 0, cursor.Size() ); UT_EQ( 1, IteratorCount(cursor.SetIterator(iter, 0), pm.end() ) ); UT_FALSE( cursor.IsRoot() );
    cursor.SearchNodeNameAndDeleteNode();             UT_EQ( "B"       , cursor.SearchName() ); UT_EQ( 2, cursor.Size() ); UT_EQ( 3, IteratorCount(cursor.SetIterator(iter, 0), pm.end() ) ); UT_FALSE( cursor.IsRoot() );
    cursor.SearchNodeNameAndDeleteNode();             UT_EQ( "a"       , cursor.SearchName() ); UT_EQ( 2, cursor.Size() ); UT_EQ( 9, IteratorCount(cursor.SetIterator(iter, 0), pm.end() ) ); UT_FALSE( cursor.IsRoot() );
    cursor.MoveToParent(); cursor.DeleteChild("a");   UT_EQ( NullString, cursor.SearchName() ); UT_EQ( 1, cursor.Size() ); UT_EQ(14, IteratorCount(cursor.SetIterator(iter, 0), pm.end() ) ); UT_TRUE ( cursor.IsRoot() );
    cursor.DeleteChildren();                          UT_EQ( NullString, cursor.SearchName() ); UT_EQ( 0, cursor.Size() ); UT_EQ( 1, IteratorCount(cursor.SetIterator(iter, 0), pm.end() ) ); UT_TRUE ( cursor.IsRoot() );
    cursor.SearchNodeNameAndDeleteNode();             UT_EQ( NullString, cursor.SearchName() ); UT_EQ( 0, cursor.Size() ); UT_EQ( 1, IteratorCount(cursor.SetIterator(iter, 0), pm.end() ) ); UT_TRUE ( cursor.IsRoot() );
    cursor.DeleteChildren();                          UT_EQ( NullString, cursor.SearchName() ); UT_EQ( 0, cursor.Size() ); UT_EQ( 1, IteratorCount(cursor.SetIterator(iter, 0), pm.end() ) ); UT_TRUE ( cursor.IsRoot() );
}


//--------------------------------------------------------------------------------------------------
//--- StringTree_Walker
//--------------------------------------------------------------------------------------------------
template <typename TStartValue>
int doWalk( StringTree<AString,aworx::lib::containers::StringTreeConstKeyAllocator<AString>>::Walker& walker, TStartValue startValue )
{
    String spaces= Spaces::Get();

    int cnt= 0;
    for ( walker.SetStart( startValue ); walker.IsValid() ; walker.Next() )
    {
        //cout << walker.GetPath();
        cout << walker.Depth() << ": ";
        cout << String( spaces, 0, 2 * walker.Depth() );
        cout << walker.Name();
        cout << " \""<< *walker << "\"";
        cout << " <"<< walker.GetPathToNode() << ">";
        cout << " #"<< walker.Size() << ">";
        cout << endl;
        ++cnt;
    }

    return cnt;
}

UT_METHOD(StringTree_Walker)
{
    UT_INIT();

    StringTree<AString, aworx::lib::containers::StringTreeConstKeyAllocator<AString>> pm;
    auto cursor=  pm.Root();                      *cursor= "root";

    (cursor= pm()).MoveToAndCreateNonExistingPart( ""            ); *cursor=  "root" ;
    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer"       ); *cursor= AString("aDir"      );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer/inner" ); *cursor= AString("inner"      );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer/xinn1" ); *cursor= AString("inn1"       );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer/inn2"  ); *cursor= AString("inn2"       );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer/Inn3"  ); *cursor= AString("xinn3"      );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer/inn4"  ); *cursor= AString("inn4"       );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer/inn5"  ); *cursor= AString("inn5"       );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer/inner" ); *cursor= AString("Overwritten");
    (cursor= pm()).MoveToAndCreateNonExistingPart( "dir2"        ); *cursor= AString("dir2"       );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "dir2/subd2-a"); *cursor= AString("subd2-a"    );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "dir2/subd2-b"); *cursor= AString("subd2-b"    );

    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer/Inn3/abc"  ); *cursor= AString("abc"      );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer/Inn3/def"  ); *cursor= AString("def"      );
    (cursor= pm()).MoveToAndCreateNonExistingPart( "outer/Inn3/ght"  ); *cursor= AString("ght"      );

    decltype(pm)::Walker walker( &pm );

    // check cursor/iterator creation
    UT_TRUE( walker.GetCursor() == pm.Root() );

    decltype(pm)::StdIterator it( &pm );
    walker.SetIterator( it );
    UT_TRUE( it == pm.begin() );


    walker.PathGeneration( Switch::On );

    cout << endl << "--- non recursive ---" << endl;
    walker.SetRecursionDepth( 1 );
    UT_EQ(  2,  doWalk( walker, &pm ) );

    cout << endl << "--- non recursive ---" << endl;
    decltype(pm)::Cursor start=   pm.Root();
    UT_TRUE( start.MoveTo("outer/Inn3") );
    UT_EQ(  3,  doWalk( walker, start ) );

    cout << endl << "--- non recursive decending---" << endl;
    walker.SortByPathname( SortOrder::Descending, Case::Sensitive );
    UT_EQ(  3,  doWalk( walker, start ) );
    walker.SortByPathname( SortOrder::Ascending, Case::Sensitive );


    cout << endl << "--- ascending ---" << endl;
    walker.SetRecursionDepth( 99 );
    UT_EQ( 13,  doWalk( walker, &pm ) );

    cout << endl << "--- descending ---" << endl;
    walker.SetRecursionDepth( -1 );
    walker.SortByPathname( SortOrder::Descending, Case::Sensitive );
    UT_EQ( 14,  doWalk( walker, &pm ) );

    cout << endl << "--- value ---" << endl;
    walker.SortByValue( valueSorter );
    UT_EQ( 14,  doWalk( walker, &pm ) );

    cout << endl << "--- value ---" << endl;
    walker.SortByValue( valueSorter );
    start=   pm.Root();
    UT_TRUE( start.MoveTo("outer/Inn3") );
    UT_EQ(  4,  doWalk( walker, start ) );

    walker.SetRecursionDepth( 1 );
    UT_EQ(  3,  doWalk( walker, start ) );


    cout << endl << "--- value ---" << endl;
    walker.SetRecursionDepth( -1 );
    UT_TRUE( start.MoveTo("abc") );
    UT_EQ(  1,  doWalk( walker, start ) );

    walker.SetRecursionDepth( 5 );
    UT_EQ(  0,  doWalk( walker, start ) );

}

UT_CLASS_END

}; //namespace



