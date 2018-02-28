// #################################################################################################
//  cs.aworx.unittests - AWorx Util
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Threading;
using cs.aworx.lib.util;
using cs.aworx.lib.strings;
using ut_cs_aworx;

#if ALIB_NUNIT
    using NUnit.Framework;
#endif
#if ALIB_IDE_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using System.Text;
using cs.aworx.lib;
using cs.aworx.lib.lang;
using cs.aworx.lox;
using cs.aworx.lox.loggers;

namespace ut_cs_aworx_lib
{
    #if ALIB_NUNIT
        [TestFixture ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestClass]
    #endif
    public class CS_StringTree    : AWorxUnitTesting
    {
        int IteratorCount( StringTree<String>.Walker walker, bool debugOutput=false )
        {
            if( debugOutput )
                UT_PRINT(  "Dbg output: " );
            int cnt= 0;
            while ( walker.IsValid() )
            {
                if( debugOutput )
                    UT_PRINT( "" + cnt + " D=" + walker.Depth() + " N= \"" + walker.Name() + "\"  V=" + walker.Value()
                            + "  #children=  " + walker.Size() );
                ++cnt;
                walker.Next();
            }
            return cnt;
        }

        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_StringTree")]
            #endif
        #endif
        public void Cursor()
        {
            UT_INIT();

            UT_PRINT( "Cursor():" );
            UT_PRINT( "Build string tree without using cursor navigation" );

            StringTree<String> pm= new StringTree<String>();
            var cursor=   pm.Root();    cursor.SetValue( "root" );

            cursor= pm.Root();                                    cursor.SetValue( "root"   );
                   UT_TRUE( cursor.MoveToChildCreate( "a"    ) ); cursor.SetValue( "a--"    );
                   UT_TRUE( cursor.MoveToChildCreate( "A"    ) ); cursor.SetValue( "aA-"    );
                   UT_TRUE( cursor.MoveToChildCreate( "1"    ) ); cursor.SetValue( "aA1"    );
            UT_TRUE(  cursor.MoveToParent() ); UT_TRUE( cursor.MoveToChildCreate( "b"    ) ); cursor.SetValue( "aab"  );
            UT_TRUE(  cursor.MoveToParent() ); UT_TRUE( cursor.MoveToChildCreate( "c"    ) ); cursor.SetValue( "aac"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/B"    ); cursor.SetValue( "aB-"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/B/1"  ); cursor.SetValue( "aB1"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/B/2"  ); cursor.SetValue( "aB2"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/B/3"  ); cursor.SetValue( "aB3"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/C"    ); cursor.SetValue( "aC-"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/C/1"  ); cursor.SetValue( "aC1"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/C/2"  ); cursor.SetValue( "aC2"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "a/C/3"  ); cursor.SetValue( "aC3"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b"      ); cursor.SetValue( "b--"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/A"    ); cursor.SetValue( "bA-"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/A/1"  ); cursor.SetValue( "bA1"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/A/2"  ); cursor.SetValue( "bA2"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/A/3"  ); cursor.SetValue( "bA3"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/B"    ); cursor.SetValue( "bB-"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/B/1"  ); cursor.SetValue( "bB1"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/B/2"  ); cursor.SetValue( "bB2"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/B/3"  ); cursor.SetValue( "bB3"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/C"    ); cursor.SetValue( "bC-"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/C/1"  ); cursor.SetValue( "bC1"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/C/2"  ); cursor.SetValue( "bC2"  );
            cursor= pm.Root(); cursor.MoveToAndCreateNonExistingPart ( "b/C/3"  ); cursor.SetValue( "bC3"  );

            UT_PRINT( "Check construction (sizes of some branches)" );
            StringTree<String>.Walker iter= new StringTree<String>.Walker(pm);             UT_EQ( 27, IteratorCount( iter, true ) );

            iter.SetRecursionDepth( 0 );
                      cursor= pm.Root(); UT_EQ( 0, cursor.Depth() );     iter.SetStart( cursor ); UT_EQ( 27, IteratorCount( iter ) );
            UT_TRUE( (cursor= pm.Root()).MoveToChild("a"  )    );        iter.SetStart( cursor ); UT_EQ( 13, IteratorCount( iter ) );
            UT_TRUE( (cursor= pm.Root()).MoveTo     ("a/B")    );        iter.SetStart( cursor ); UT_EQ(  4, IteratorCount( iter ) );
            UT_TRUE( (cursor= pm.Root()).MoveTo     ("a/B/3")  );        iter.SetStart( cursor ); UT_EQ(  1, IteratorCount( iter ) );
            UT_FALSE((cursor= pm.Root()).MoveTo     ("a/B/3/e"));        iter.SetStart( cursor ); UT_EQ( 27, IteratorCount( iter ) );
            UT_FALSE((cursor= pm.Root()).MoveTo     ("ab/ce")  );        iter.SetStart( cursor ); UT_EQ( 27, IteratorCount( iter ) );

            UT_PRINT( "Cursor navigation" );;

            cursor= pm.Root(); UT_TRUE(  cursor.MoveTo("a"           )); iter.SetStart( cursor ); UT_EQ( 13, IteratorCount(iter ) );
            iter.SetRecursionDepth( 1 );
            cursor= pm.Root();                                           iter.SetStart( cursor ); UT_EQ(  2, IteratorCount(iter ) );
            cursor= pm.Root(); UT_TRUE(  cursor.MoveTo("a"           )); iter.SetStart( cursor ); UT_EQ(  3, IteratorCount(iter ) );
            iter.SetRecursionDepth( 0 );
            cursor= pm.Root(); UT_FALSE( cursor.MoveTo("XYZ"         )); iter.SetStart( cursor ); UT_EQ( 27, IteratorCount(iter ) );
            cursor= pm.Root(); UT_TRUE ( cursor.MoveTo("b"           )); iter.SetStart( cursor ); UT_EQ( 13, IteratorCount(iter ) );
            cursor= pm.Root(); UT_FALSE( cursor.MoveToChildCreate("a")); iter.SetStart( cursor ); UT_EQ( 13, IteratorCount(iter ) );

            cursor= pm.Root(); UT_TRUE ( cursor.MoveTo("a/B/./1"     )); iter.SetStart( cursor ); UT_EQ(  1, IteratorCount(iter ) );
            cursor= pm.Root(); UT_TRUE ( cursor.MoveTo("a/B/1/../1"  )); iter.SetStart( cursor ); UT_EQ(  1, IteratorCount(iter ) );

            cursor= pm.Root(); UT_TRUE ( cursor.MoveTo("a/B/1"  )); UT_EQ(  "aB1", cursor.Value() );
                               UT_TRUE ( cursor.MoveTo("../2"   )); UT_EQ(  "aB2", cursor.Value() );
                               UT_FALSE( cursor.MoveTo("b"      )); UT_EQ(  "aB2", cursor.Value() );
                               UT_TRUE ( cursor.MoveTo("/b"     )); UT_EQ(  "b--", cursor.Value() );
                               UT_TRUE ( cursor.MoveTo("./C"    )); UT_EQ(  "bC-", cursor.Value() );


            UT_PRINT( "Up" );;
            UT_TRUE( (cursor= pm.Root()).MoveTo( "a/B/3" ) );
                                                        UT_EQ( "3"     , cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_FALSE( cursor.IsRoot() );
            cursor.MoveToParent();                      UT_EQ( "B"     , cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_FALSE( cursor.IsRoot() );
            cursor.MoveToParentUnchecked();             UT_EQ( "a"     , cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_FALSE( cursor.IsRoot() );
            cursor.MoveToParent();                      UT_TRUE( null == cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_TRUE(  cursor.IsRoot() );
            cursor.MoveToParent();                      UT_TRUE( null == cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_TRUE(  cursor.IsRoot() );
            cursor.MoveToParent();                      UT_TRUE( null == cursor.SearchName() ); UT_FALSE( cursor.IsInvalid() ); UT_TRUE(  cursor.IsRoot() );
            cursor.MoveToParentUnchecked();             UT_TRUE ( cursor.IsInvalid() );

            UT_PRINT( "GetPath" );;
            AString path= new AString();
            cursor= pm.Root(); cursor.MoveToParentUnchecked(); cursor.SearchPath( path );  UT_TRUE ( path.IsNull() );
            cursor= pm.Root();                                 cursor.SearchPath( path );  UT_FALSE( path.IsNull() ); UT_TRUE( path.IsEmpty() );
            cursor= pm.Root(); cursor.MoveTo("a"      );       cursor.SearchPath( path );  UT_EQ   ( "a"        , path);
            cursor= pm.Root(); cursor.MoveTo("a/b"    );       cursor.SearchPath( path );  UT_EQ   ( ""         , path);
            cursor= pm.Root(); cursor.MoveTo("a/B"    );       cursor.SearchPath( path );  UT_EQ   ( "a/B"      , path);
            cursor= pm.Root(); cursor.MoveTo("a/B/1"  );       cursor.SearchPath( path );  UT_EQ   ( "a/B/1"    , path);


            UT_PRINT( "Erase nodes");;
            iter.SetRecursionDepth( 0 );
            cursor= new StringTree<string>.Cursor( pm );
            UT_TRUE(cursor.MoveTo( "a/B/3"  ));               UT_EQ( "3"      , cursor.SearchName() ); UT_EQ( 0, cursor.Size() ); iter.SetStart( cursor ); UT_EQ( 1, IteratorCount(iter) ); UT_FALSE( cursor.IsRoot() );
            cursor.DeleteChildren();                          UT_EQ( "3"      , cursor.SearchName() ); UT_EQ( 0, cursor.Size() ); iter.SetStart( cursor ); UT_EQ( 1, IteratorCount(iter) ); UT_FALSE( cursor.IsRoot() );
            cursor.SearchNodeNameAndDeleteNode();             UT_EQ( "B"      , cursor.SearchName() ); UT_EQ( 2, cursor.Size() ); iter.SetStart( cursor ); UT_EQ( 3, IteratorCount(iter) ); UT_FALSE( cursor.IsRoot() );
            cursor.SearchNodeNameAndDeleteNode();             UT_EQ( "a"      , cursor.SearchName() ); UT_EQ( 2, cursor.Size() ); iter.SetStart( cursor ); UT_EQ( 9, IteratorCount(iter) ); UT_FALSE( cursor.IsRoot() );
            cursor.MoveToParent(); cursor.DeleteChild("a");   UT_TRUE( null ==  cursor.SearchName() ); UT_EQ( 1, cursor.Size() ); iter.SetStart( cursor ); UT_EQ(14, IteratorCount(iter) ); UT_TRUE ( cursor.IsRoot() );
            cursor.DeleteChildren();                          UT_TRUE( null ==  cursor.SearchName() ); UT_EQ( 0, cursor.Size() ); iter.SetStart( cursor ); UT_EQ( 1, IteratorCount(iter) ); UT_TRUE ( cursor.IsRoot() );
            cursor.SearchNodeNameAndDeleteNode();             UT_TRUE( null ==  cursor.SearchName() ); UT_EQ( 0, cursor.Size() ); iter.SetStart( cursor ); UT_EQ( 1, IteratorCount(iter) ); UT_TRUE ( cursor.IsRoot() );
            cursor.DeleteChildren();                          UT_TRUE( null ==  cursor.SearchName() ); UT_EQ( 0, cursor.Size() ); iter.SetStart( cursor ); UT_EQ( 1, IteratorCount(iter) ); UT_TRUE ( cursor.IsRoot() );

            pm.Clear();

        }

int doWalk( StringTree<AString>.Walker walker, StringTree<AString>.Cursor startValue )
{
    AString spaces= cs.aworx.lib.strings.util.Spaces.Get();

    int cnt= 0;
    for ( walker.SetStart( startValue ); walker.IsValid() ; walker.Next() )
    {
        //cout << walker.GetPath();
        UT_PRINT( "" + walker.Depth() + ": "
                  + spaces.ToString( 0, 2 * walker.Depth() )
                  + walker.Name()
                  + " \"" + walker.Value()          + "\""
                  + " <"  + walker.GetPathToNode()  + ">"
                  + " #"  + walker.Size()           + ">"             );
        ++cnt;
    }

    return cnt;
}


        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_StringTree")]
            #endif
        #endif
        public void Walker()
        {

    StringTree<AString> pm = new StringTree<AString>();
    var cursor=  pm.Root();          cursor.SetValue( new AString("root") );

    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( ""                ); cursor.SetValue( new AString("root"       ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer"           ); cursor.SetValue( new AString("aDir"       ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer/inner"     ); cursor.SetValue( new AString("inner"      ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer/xinn1"     ); cursor.SetValue( new AString("inn1"       ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer/inn2"      ); cursor.SetValue( new AString("inn2"       ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer/Inn3"      ); cursor.SetValue( new AString("xinn3"      ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer/inn4"      ); cursor.SetValue( new AString("inn4"       ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer/inn5"      ); cursor.SetValue( new AString("inn5"       ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer/inner"     ); cursor.SetValue( new AString("Overwritten") );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "dir2"            ); cursor.SetValue( new AString("dir2"       ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "dir2/subd2-a"    ); cursor.SetValue( new AString("subd2-a"    ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "dir2/subd2-b"    ); cursor.SetValue( new AString("subd2-b"    ) );

    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer/Inn3/abc"  ); cursor.SetValue( new AString("abc"        ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer/Inn3/def"  ); cursor.SetValue( new AString("def"        ) );
    (cursor= pm.Root()).MoveToAndCreateNonExistingPart( "outer/Inn3/ght"  ); cursor.SetValue( new AString("ght"        ) );

    StringTree<AString>.Walker walker = new StringTree<AString>.Walker( pm );

    // check cursor/iterator creation
    walker.PathGeneration( Switch.On );

    UT_PRINT( "\n--- non recursive ---" );
    walker.SetRecursionDepth( 1 );
    UT_EQ(  2,  doWalk( walker, pm.Root() ) );

    UT_PRINT( "\n--- non recursive ---" );
    StringTree<AString>.Cursor start=   pm.Root();
    UT_TRUE( start.MoveTo("outer/Inn3") );
    UT_EQ(  3,  doWalk( walker, start ) );

    UT_PRINT( "\n--- non recursive decending---" );
    walker.SortByPathname( SortOrder.Descending, StringComparison.InvariantCulture );
    UT_EQ(  3,  doWalk( walker, start ) );
    walker.SortByPathname( SortOrder.Ascending, StringComparison.InvariantCulture );


    UT_PRINT( "\n--- ascending ---" );
    walker.SetRecursionDepth( 99 );
    UT_EQ( 13,  doWalk( walker, pm.Root() ) );

    UT_PRINT( "\n--- descending ---" );
    walker.SetRecursionDepth( -1 );
    walker.SortByPathname( SortOrder.Descending, StringComparison.InvariantCulture );
    UT_EQ( 14,  doWalk( walker, pm.Root() ) );

    Comparison<AString> valueSorter=   delegate (AString as1, AString as2) { return as1.CompareTo(as2, Case.Ignore);  };

    UT_PRINT( "\n--- value ---" );
    walker.SortByValue( valueSorter );
    UT_EQ( 14,  doWalk( walker, pm.Root() ) );

    UT_PRINT( "\n--- value ---" );
    walker.SortByValue( valueSorter );
    start=   pm.Root();
    UT_TRUE( start.MoveTo("outer/Inn3") );
    UT_EQ(  4,  doWalk( walker, start ) );

    walker.SetRecursionDepth( 1 );
    UT_EQ(  3,  doWalk( walker, start ) );


    UT_PRINT( "\n--- value ---" );
    walker.SetRecursionDepth( -1 );
    UT_TRUE( start.MoveTo("abc") );
    UT_EQ(  1,  doWalk( walker, start ) );

    walker.SetRecursionDepth( 5 );
    UT_EQ(  0,  doWalk( walker, start ) );

}



    }
}
