// #################################################################################################
//  Unit Tests - AWorx Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package ut_alib;
import com.aworx.lib.ALIB;
import com.aworx.lib.strings.*;
import com.aworx.lib.lang.*;
import com.aworx.lib.time.*;
import com.aworx.lib.util.StringTree;
import org.junit.Test;
import ut_com_aworx.AWorxUnitTesting;
import java.util.*;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;


public class UT_alib_util_stringtree extends AWorxUnitTesting
{
    int IteratorCount( StringTree<String>.Walker walker ) { return IteratorCount( walker, false ); }
    int IteratorCount( StringTree<String>.Walker walker, boolean debugOutput )
    {
        if( debugOutput )
            UT_PRINT(  "Dbg output: " );
        int cnt= 0;
        while ( walker.isValid() )
        {
            if( debugOutput )
                UT_PRINT( "" + cnt + " D=" + walker.depth() + " N= \"" + walker.name() + "\"  V=" + walker.value()
                        + "  #children=  " + walker.size() );
            ++cnt;
            walker.next();
        }
        return cnt;
    }

    @SuppressWarnings("static-method")
    @Test
    public void StringTree_Cursor()
    {
        UT_INIT();

            UT_PRINT( "Cursor():" );
            UT_PRINT( "Build string tree without using cursor navigation" );

            StringTree<String> pm= new StringTree<String>();
            StringTree<String>.Cursor cursor=   pm.root();    cursor.setValue( "root" );

            cursor= pm.root();                                    cursor.setValue( "root"   );
                   UT_TRUE( cursor.moveToChildCreate( "a"    ) ); cursor.setValue( "a--"    );
                   UT_TRUE( cursor.moveToChildCreate( "A"    ) ); cursor.setValue( "aA-"    );
                   UT_TRUE( cursor.moveToChildCreate( "1"    ) ); cursor.setValue( "aA1"    );
            UT_TRUE(  cursor.moveToParent() ); UT_TRUE( cursor.moveToChildCreate( "b"    ) ); cursor.setValue( "aab"  );
            UT_TRUE(  cursor.moveToParent() ); UT_TRUE( cursor.moveToChildCreate( "c"    ) ); cursor.setValue( "aac"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "a/B"    ); cursor.setValue( "aB-"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "a/B/1"  ); cursor.setValue( "aB1"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "a/B/2"  ); cursor.setValue( "aB2"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "a/B/3"  ); cursor.setValue( "aB3"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "a/C"    ); cursor.setValue( "aC-"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "a/C/1"  ); cursor.setValue( "aC1"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "a/C/2"  ); cursor.setValue( "aC2"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "a/C/3"  ); cursor.setValue( "aC3"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b"      ); cursor.setValue( "b--"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/A"    ); cursor.setValue( "bA-"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/A/1"  ); cursor.setValue( "bA1"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/A/2"  ); cursor.setValue( "bA2"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/A/3"  ); cursor.setValue( "bA3"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/B"    ); cursor.setValue( "bB-"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/B/1"  ); cursor.setValue( "bB1"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/B/2"  ); cursor.setValue( "bB2"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/B/3"  ); cursor.setValue( "bB3"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/C"    ); cursor.setValue( "bC-"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/C/1"  ); cursor.setValue( "bC1"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/C/2"  ); cursor.setValue( "bC2"  );
            cursor= pm.root(); cursor.moveToAndCreateNonExistingPart ( "b/C/3"  ); cursor.setValue( "bC3"  );

            UT_PRINT( "Check construction (sizes of some branches)" );
            StringTree<String>.Walker iter= pm.new Walker();             UT_EQ( 27, IteratorCount( iter, true ) );

            iter.setRecursionDepth( 0 );
                      cursor= pm.root(); UT_EQ( 0, cursor.depth() );     iter.setStart( cursor ); UT_EQ( 27, IteratorCount( iter ) );
            UT_TRUE( (cursor= pm.root()).moveToChild("a"  )    );        iter.setStart( cursor ); UT_EQ( 13, IteratorCount( iter ) );
            UT_TRUE( (cursor= pm.root()).moveTo     ("a/B")    );        iter.setStart( cursor ); UT_EQ(  4, IteratorCount( iter ) );
            UT_TRUE( (cursor= pm.root()).moveTo     ("a/B/3")  );        iter.setStart( cursor ); UT_EQ(  1, IteratorCount( iter ) );
            UT_FALSE((cursor= pm.root()).moveTo     ("a/B/3/e"));        iter.setStart( cursor ); UT_EQ( 27, IteratorCount( iter ) );
            UT_FALSE((cursor= pm.root()).moveTo     ("ab/ce")  );        iter.setStart( cursor ); UT_EQ( 27, IteratorCount( iter ) );

            UT_PRINT( "Cursor navigation" );;

            cursor= pm.root(); UT_TRUE(  cursor.moveTo("a"           )); iter.setStart( cursor ); UT_EQ( 13, IteratorCount(iter ) );
            iter.setRecursionDepth( 1 );
            cursor= pm.root();                                           iter.setStart( cursor ); UT_EQ(  2, IteratorCount(iter ) );
            cursor= pm.root(); UT_TRUE(  cursor.moveTo("a"           )); iter.setStart( cursor ); UT_EQ(  3, IteratorCount(iter ) );
            iter.setRecursionDepth( 0 );
            cursor= pm.root(); UT_FALSE( cursor.moveTo("XYZ"         )); iter.setStart( cursor ); UT_EQ( 27, IteratorCount(iter ) );
            cursor= pm.root(); UT_TRUE ( cursor.moveTo("b"           )); iter.setStart( cursor ); UT_EQ( 13, IteratorCount(iter ) );
            cursor= pm.root(); UT_FALSE( cursor.moveToChildCreate("a")); iter.setStart( cursor ); UT_EQ( 13, IteratorCount(iter ) );

            cursor= pm.root(); UT_TRUE ( cursor.moveTo("a/B/./1"     )); iter.setStart( cursor ); UT_EQ(  1, IteratorCount(iter ) );
            cursor= pm.root(); UT_TRUE ( cursor.moveTo("a/B/1/../1"  )); iter.setStart( cursor ); UT_EQ(  1, IteratorCount(iter ) );

            cursor= pm.root(); UT_TRUE ( cursor.moveTo("a/B/1"  )); UT_EQ(  "aB1", cursor.value() );
                               UT_TRUE ( cursor.moveTo("../2"   )); UT_EQ(  "aB2", cursor.value() );
                               UT_FALSE( cursor.moveTo("b"      )); UT_EQ(  "aB2", cursor.value() );
                               UT_TRUE ( cursor.moveTo("/b"     )); UT_EQ(  "b--", cursor.value() );
                               UT_TRUE ( cursor.moveTo("./C"    )); UT_EQ(  "bC-", cursor.value() );


            UT_PRINT( "Up" );;
            UT_TRUE( (cursor= pm.root()).moveTo( "a/B/3" ) );
                                                        UT_EQ( "3"     , cursor.searchName() ); UT_FALSE( cursor.isInvalid() ); UT_FALSE( cursor.isRoot() );
            cursor.moveToParent();                      UT_EQ( "B"     , cursor.searchName() ); UT_FALSE( cursor.isInvalid() ); UT_FALSE( cursor.isRoot() );
            cursor.moveToParentUnchecked();             UT_EQ( "a"     , cursor.searchName() ); UT_FALSE( cursor.isInvalid() ); UT_FALSE( cursor.isRoot() );
            cursor.moveToParent();                      UT_TRUE( null == cursor.searchName() ); UT_FALSE( cursor.isInvalid() ); UT_TRUE(  cursor.isRoot() );
            cursor.moveToParent();                      UT_TRUE( null == cursor.searchName() ); UT_FALSE( cursor.isInvalid() ); UT_TRUE(  cursor.isRoot() );
            cursor.moveToParent();                      UT_TRUE( null == cursor.searchName() ); UT_FALSE( cursor.isInvalid() ); UT_TRUE(  cursor.isRoot() );
            cursor.moveToParentUnchecked();             UT_TRUE ( cursor.isInvalid() );

            UT_PRINT( "GetPath" );;
            AString path= new AString();
            cursor= pm.root(); cursor.moveToParentUnchecked(); cursor.searchPath( path );  UT_TRUE ( path.isNull() );
            cursor= pm.root();                                 cursor.searchPath( path );  UT_FALSE( path.isNull() ); UT_TRUE( path.isEmpty() );
            cursor= pm.root(); cursor.moveTo("a"      );       cursor.searchPath( path );  UT_EQ   ( "a"        , path);
            cursor= pm.root(); cursor.moveTo("a/b"    );       cursor.searchPath( path );  UT_EQ   ( ""         , path);
            cursor= pm.root(); cursor.moveTo("a/B"    );       cursor.searchPath( path );  UT_EQ   ( "a/B"      , path);
            cursor= pm.root(); cursor.moveTo("a/B/1"  );       cursor.searchPath( path );  UT_EQ   ( "a/B/1"    , path);


            UT_PRINT( "Erase nodes");;
            iter.setRecursionDepth( 0 );
            cursor= pm.new Cursor();
            UT_TRUE(cursor.moveTo( "a/B/3"  ));               UT_EQ( "3"      , cursor.searchName() ); UT_EQ( 0, cursor.size() ); iter.setStart( cursor ); UT_EQ( 1, IteratorCount(iter) ); UT_FALSE( cursor.isRoot() );
            cursor.deleteChildren();                          UT_EQ( "3"      , cursor.searchName() ); UT_EQ( 0, cursor.size() ); iter.setStart( cursor ); UT_EQ( 1, IteratorCount(iter) ); UT_FALSE( cursor.isRoot() );
            cursor.searchNodeNameAndDeleteNode();             UT_EQ( "B"      , cursor.searchName() ); UT_EQ( 2, cursor.size() ); iter.setStart( cursor ); UT_EQ( 3, IteratorCount(iter) ); UT_FALSE( cursor.isRoot() );
            cursor.searchNodeNameAndDeleteNode();             UT_EQ( "a"      , cursor.searchName() ); UT_EQ( 2, cursor.size() ); iter.setStart( cursor ); UT_EQ( 9, IteratorCount(iter) ); UT_FALSE( cursor.isRoot() );
            cursor.moveToParent(); cursor.deleteChild("a");   UT_TRUE( null ==  cursor.searchName() ); UT_EQ( 1, cursor.size() ); iter.setStart( cursor ); UT_EQ(14, IteratorCount(iter) ); UT_TRUE ( cursor.isRoot() );
            cursor.deleteChildren();                          UT_TRUE( null ==  cursor.searchName() ); UT_EQ( 0, cursor.size() ); iter.setStart( cursor ); UT_EQ( 1, IteratorCount(iter) ); UT_TRUE ( cursor.isRoot() );
            cursor.searchNodeNameAndDeleteNode();             UT_TRUE( null ==  cursor.searchName() ); UT_EQ( 0, cursor.size() ); iter.setStart( cursor ); UT_EQ( 1, IteratorCount(iter) ); UT_TRUE ( cursor.isRoot() );
            cursor.deleteChildren();                          UT_TRUE( null ==  cursor.searchName() ); UT_EQ( 0, cursor.size() ); iter.setStart( cursor ); UT_EQ( 1, IteratorCount(iter) ); UT_TRUE ( cursor.isRoot() );

            pm.clear();

        }

        int doWalk( StringTree<AString>.Walker walker, StringTree<AString>.Cursor startValue )
        {
            AString spaces= com.aworx.lib.strings.util.Spaces.get();

            int cnt= 0;
            for ( walker.setStart( startValue ); walker.isValid() ; walker.next() )
            {
                //cout << walker.GetPath();
                UT_PRINT( "" + walker.depth() + ": "
                          + spaces.toString( 0, 2 * walker.depth() )
                          + walker.name()
                          + " \"" + walker.value()          + "\""
                          + " <"  + walker.getPathToNode()  + ">"
                          + " #"  + walker.size()           + ">"             );
                ++cnt;
            }

            return cnt;
        }


            @SuppressWarnings("static-method")
            @Test
        public void StringTree_Walker()
        {

            StringTree<AString> pm = new StringTree<AString>();
            StringTree<AString>.Cursor cursor=  pm.root();          cursor.setValue( new AString("root") );

            (cursor= pm.root()).moveToAndCreateNonExistingPart( ""                ); cursor.setValue( new AString("root"       ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer"           ); cursor.setValue( new AString("aDir"       ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer/inner"     ); cursor.setValue( new AString("inner"      ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer/xinn1"     ); cursor.setValue( new AString("inn1"       ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer/inn2"      ); cursor.setValue( new AString("inn2"       ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer/Inn3"      ); cursor.setValue( new AString("xinn3"      ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer/inn4"      ); cursor.setValue( new AString("inn4"       ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer/inn5"      ); cursor.setValue( new AString("inn5"       ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer/inner"     ); cursor.setValue( new AString("Overwritten") );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "dir2"            ); cursor.setValue( new AString("dir2"       ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "dir2/subd2-a"    ); cursor.setValue( new AString("subd2-a"    ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "dir2/subd2-b"    ); cursor.setValue( new AString("subd2-b"    ) );

            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer/Inn3/abc"  ); cursor.setValue( new AString("abc"        ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer/Inn3/def"  ); cursor.setValue( new AString("def"        ) );
            (cursor= pm.root()).moveToAndCreateNonExistingPart( "outer/Inn3/ght"  ); cursor.setValue( new AString("ght"        ) );

            StringTree<AString>.Walker walker = pm.new Walker();

            // check cursor/iterator creation
            walker.pathGeneration( Switch.ON );

            UT_PRINT( "\n--- non recursive ---" );
            walker.setRecursionDepth( 1 );
            UT_EQ(  2,  doWalk( walker, pm.root() ) );

            UT_PRINT( "\n--- non recursive ---" );
            StringTree<AString>.Cursor start=   pm.root();
            UT_TRUE( start.moveTo("outer/Inn3") );
            UT_EQ(  3,  doWalk( walker, start ) );

            UT_PRINT( "\n--- non recursive decending---" );
            walker.sortByPathname(SortOrder.DESCENDING, Case.IGNORE );
            UT_EQ(  3,  doWalk( walker, start ) );
            walker.sortByPathname( SortOrder.ASCENDING, Case.IGNORE );


            UT_PRINT( "\n--- ascending ---" );
            walker.setRecursionDepth( 99 );
            UT_EQ( 13,  doWalk( walker, pm.root() ) );

            UT_PRINT( "\n--- descending ---" );
            walker.setRecursionDepth( -1 );
            walker.sortByPathname( SortOrder.DESCENDING, Case.IGNORE );
            UT_EQ( 14,  doWalk( walker, pm.root() ) );

            Comparator<AString> valueSorter= new Comparator<AString>()
            {
                @Override
                public int compare(AString as1, AString as2)
                {
                    return  as1.compareTo( as2, Case.IGNORE );
                }
            };

            UT_PRINT( "\n--- value ---" );
            walker.sortByValue( valueSorter );
            UT_EQ( 14,  doWalk( walker, pm.root() ) );

            UT_PRINT( "\n--- value ---" );
            walker.sortByValue( valueSorter );
            start=   pm.root();
            UT_TRUE( start.moveTo("outer/Inn3") );
            UT_EQ(  4,  doWalk( walker, start ) );

            walker.setRecursionDepth( 1 );
            UT_EQ(  3,  doWalk( walker, start ) );


            UT_PRINT( "\n--- value ---" );
            walker.setRecursionDepth( -1 );
            UT_TRUE( start.moveTo("abc") );
            UT_EQ(  1,  doWalk( walker, start ) );

            walker.setRecursionDepth( 5 );
            UT_EQ(  0,  doWalk( walker, start ) );

}


}
