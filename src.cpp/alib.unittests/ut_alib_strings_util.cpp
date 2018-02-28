// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"

#if !defined (HPP_ALIB_STRINGS_FORMAT_SIMPLETEXT)
    #include "alib/strings/format/simpletext.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_UTIL_WILDCARDMATCHER)
    #include "alib/strings/util/wildcardmatcher.hpp"
#endif

#define TESTCLASSNAME       CPP_ALib_Strings_Util
#include "aworx_unittests.hpp"


#include <iostream>
#include <iomanip>


using namespace std;
using namespace aworx;

namespace ut_aworx {

UT_CLASS()

//--------------------------------------------------------------------------------------------------
//--- SimpleText
//--------------------------------------------------------------------------------------------------
UT_METHOD( SimpleText )
{
    UT_INIT();

    AString exp("");

    {
        SimpleText st;
        st.PushIndent(2);

        st.Text._(); st.Add( ""                  ); exp._()                                     ;    UT_EQ( exp, st.Text );
        st.Text._(); st.Add( "\n"                ); exp._() <<   "\n"                           ;    UT_EQ( exp, st.Text );
        st.Text._(); st.Add( "\n\n"              ); exp._() <<   "\n\n"                         ;    UT_EQ( exp, st.Text );
        st.Text._(); st.Add(     "123\n4567"     ); exp._() <<   "  123\n  4567"      << NewLine;    UT_EQ( exp, st.Text );
        st.Text._(); st.Add(   "\n123\n4567"     ); exp._() << "\n  123\n  4567"      << NewLine;    UT_EQ( exp, st.Text );
        st.Text._(); st.Add( "\n\n123\n\n4567"   ); exp._() << "\n\n  123\n\n  4567"  << NewLine;    UT_EQ( exp, st.Text );
    }


    {
        SimpleText st;

        st.LineWidth= 4;
        st.Add("1 22 333" );
        st.Add("--" );
        st.LineWidth= 3;
        st.Add("22 1" );
        st.Add("--" );
        st.Add("1 1" );

        exp._() << "1 22"       << NewLine
                << "333"        << NewLine
                << "--"         << NewLine
                << "22"         << NewLine
                << "1"          << NewLine
                << "--"         << NewLine
                << "1 1"        << NewLine;
        UT_EQ( exp, st.Text );
    }

    {
        SimpleText st;
        st.Add("123456789 123<--------" );
        st.LineWidth= 11;
        st.PushIndent(5);
        st.Add("1 22 333 4444 55555 666666 55555 4444 333 22 1 22 333 22 1" );

        exp._() << "123456789 123<--------"             << NewLine
                << "     1 22"                          << NewLine
                << "     333"                           << NewLine
                << "     4444"                          << NewLine
                << "     55555"                         << NewLine
                << "     666666"                        << NewLine
                << "     55555"                         << NewLine
                << "     4444"                          << NewLine
                << "     333 22"                        << NewLine
                << "     1 22"                          << NewLine
                << "     333 22"                        << NewLine
                << "     1"                             << NewLine
                ;
        UT_EQ( exp, st.Text );
    }

    {
        SimpleText st;
        st.Add("123456789 12345<-------" );
        st.LineWidth= 15;
        st.PushIndent(5);
        st.Add("1 22 333 4444 55555 666666 55555 4444 333 22 1 22 333 22 1" );

        exp._() << "123456789 12345<-------"            << NewLine
                << "     1 22 333"                      << NewLine
                << "     4444 55555"                    << NewLine
                << "     666666"                        << NewLine
                << "     55555 4444"                    << NewLine
                << "     333 22 1"                      << NewLine
                << "     22 333 22"                     << NewLine
                << "     1"                             << NewLine
                ;
        UT_EQ( exp, st.Text );
    //    UT_TRUE( st.Text.StartsWith(exp) );
    }

    // indent
    {
        SimpleText st;
        //st.LineWidth= 15;
        st.PushIndent("  ");  st.Text._();  st.Add( ""             );  st.PopIndent();  UT_EQ( ""                       , st.Text );
        st.PushIndent("XY");  st.Text._();  st.Add( ""             );  st.PopIndent();  UT_EQ( ""                       , st.Text );
        st.PushIndent("  ");  st.Text._();  st.Add( "\n"           );  st.PopIndent();  UT_EQ( "\n"                     , st.Text );
        st.PushIndent("XY");  st.Text._();  st.Add( "\n"           );  st.PopIndent();  UT_EQ( "XY\n"                   , st.Text );
        st.PushIndent("  ");  st.Text._();  st.Add( "\n1"          );  st.PopIndent();  UT_EQ( "\n  1\n"                , st.Text );
        st.PushIndent("  ");  st.Text._();  st.Add( "\n1"          );  st.PopIndent();  UT_EQ( "\n  1\n"                , st.Text );
        st.PushIndent("XY");  st.Text._();  st.Add( "\n1\n\n\n2"   );  st.PopIndent();  UT_EQ( "XY\nXY1\nXY\nXY\nXY2\n" , st.Text );
//        st.Indent._()._("XY");  st.Clear();  st.Add("z" );  UT_EQ( "XYz\n"          , st.Text );
    }

    const String& lorem= "Lorem ipsum dolor sit amet, consetetur.\n"
                         "Sadipscing elitr, sed diam nonumy eirmod tempor.";
    {
        SimpleText st;

        // unchanged
        st.Add(lorem );
        exp._() << lorem << NewLine;
        UT_EQ( exp, st.Text );
        st.Clear();


        st.PushIndent(2);
        st.LineWidth= 22;
        st.Add(lorem );
        //            123456789 123456789 123456789
        exp._() <<   "  Lorem ipsum dolor"    << NewLine
                <<   "  sit amet,"            << NewLine
                <<   "  consetetur."          << NewLine
                <<   "  Sadipscing elitr,"    << NewLine
                <<   "  sed diam nonumy"      << NewLine
                <<   "  eirmod tempor."       << NewLine
                ;
        UT_EQ( exp, st.Text );

        st.LineWidth= 29;
        st.Text._();
        st.Add(lorem );
        //            123456789 123456789 123456789
        exp._() <<   "  Lorem ipsum dolor sit amet,"    << NewLine
                <<   "  consetetur."                    << NewLine
                <<   "  Sadipscing elitr, sed diam"     << NewLine
                <<   "  nonumy eirmod tempor."          << NewLine
                ;
        UT_EQ( exp, st.Text );

        st.LineWidth= 32;
        st.Text._();
        st.Add(lorem );
        //            123456789 123456789 123456789 12
        exp._() <<   "  Lorem ipsum dolor sit amet,"    << NewLine
                <<   "  consetetur."                    << NewLine
                <<   "  Sadipscing elitr, sed diam"     << NewLine
                <<   "  nonumy eirmod tempor."          << NewLine
                ;
        UT_EQ( exp, st.Text );
        st.PopIndent();


        st.LineWidth= 32;
        st.PushIndent( "* ", "  " );
        st.Text._();
        st.Add(lorem );
        //            123456789 123456789 123456789 12
        exp._() <<   "* Lorem ipsum dolor sit amet,"    << NewLine
                <<   "  consetetur."                    << NewLine
                <<   "  Sadipscing elitr, sed diam"     << NewLine
                <<   "  nonumy eirmod tempor."          << NewLine
                ;
        UT_EQ( exp, st.Text );
    //    UT_TRUE( st.Text.StartsWith(exp) );
        st.PopIndent();

    }


    //-------- full justification ("Blocksatz") -------
    {
        SimpleText st;

        st.JustifyChar= ' ';
        st.LineWidth= 10;
        st.Clear();  st.Add( "1 0123456789"       );  UT_EQ("1\n0123456789\n"           , st.Text );
        st.Clear();  st.Add( "1 1 0123456789"     );  UT_EQ("1        1\n0123456789\n"  , st.Text );
        st.Clear();  st.Add( "1 1 1 0123456789"   );  UT_EQ("1   1    1\n0123456789\n"  , st.Text );
        st.Clear();  st.Add( "1 1 11 0123456789"  );  UT_EQ("1   1   11\n0123456789\n"  , st.Text );
        st.Clear();  st.Add( "1 1 111 0123456789" );  UT_EQ("1  1   111\n0123456789\n"  , st.Text );

        st.LineWidth= 32;
        st.PushIndent(2);
        st.JustifyChar= ' ';
        st.Text._();
        st.Add(lorem );
        //            123456789 123456789 123456789 12
        exp._() <<   "  Lorem ipsum  dolor  sit  amet,"  << NewLine
                <<   "  consetetur."                     << NewLine
                <<   "  Sadipscing  elitr,  sed   diam"  << NewLine
                <<   "  nonumy eirmod tempor."           << NewLine
                ;
        UT_EQ( exp, st.Text );
    //    UT_TRUE( st.Text.StartsWith(exp) );


        UT_PRINT("'Visual' Tests (no checking rules, last time we saw it, it worked :-)" )
        st.IndentFirstLine= nullptr;
        st.JustifyChar= ' ';
        st.LineWidth= 32;  st.Clear();   st.Add( lorem );  UT_PRINT("123456789 123456789 123456789 12|--------\n",  st.Text,"\n" );
        st.LineWidth= 33;  st.Clear();   st.Add( lorem );  UT_PRINT("123456789 123456789 123456789 123|-------\n",  st.Text,"\n" );
        st.LineWidth= 34;  st.Clear();   st.Add( lorem );  UT_PRINT("123456789 123456789 123456789 1234|------\n",  st.Text,"\n" );
        st.LineWidth= 35;  st.Clear();   st.Add( lorem );  UT_PRINT("123456789 123456789 123456789 12345|-----\n",  st.Text,"\n" );
        st.LineWidth= 36;  st.Clear();   st.Add( lorem );  UT_PRINT("123456789 123456789 123456789 123456|----\n",  st.Text,"\n" );
        st.LineWidth= 37;  st.Clear();   st.Add( lorem );  UT_PRINT("123456789 123456789 123456789 1234567|---\n",  st.Text,"\n" );
        st.LineWidth= 38;  st.Clear();   st.Add( lorem );  UT_PRINT("123456789 123456789 123456789 12345678|--\n",  st.Text,"\n" );
        st.LineWidth= 39;  st.Clear();   st.Add( lorem );  UT_PRINT("123456789 123456789 123456789 123456789|-\n",  st.Text,"\n" );
        st.LineWidth= 40;  st.Clear();   st.Add( lorem );  UT_PRINT("123456789 123456789 123456789 123456789 |\n",  st.Text,"\n" );
        st.LineWidth= 41;  st.Clear();   st.Add( lorem );  UT_PRINT("123456789 123456789 123456789 123456789 1|\n", st.Text,"\n" );
    }


}

//--------------------------------------------------------------------------------------------------
//--- SimpleTextMarked
//--------------------------------------------------------------------------------------------------
UT_METHOD( SimpleTextMarked )
{
    UT_INIT();

    AString exp("");

    {
        SimpleText st;
        st.Clear().AddMarked("@*>Bullet1@Pxxx@P\nBullet2\n@<*Normal text" );
        UT_PRINT( st.Text );
        exp._() <<   "* Bullet1"     << NewLine
                <<   "  xxx"         << NewLine
                <<   ""              << NewLine
                <<   "* Bullet2"     << NewLine
                <<   "Normal text"   << NewLine;
        UT_EQ( exp, st.Text );


        st.Clear().AddMarked("@*>Outer1\n@*>Inner\nInner2@Pyyy\n@<*Outer2@Pmore\n@<*simple" );
        UT_PRINT( st.Text );

        exp._() <<   "* Outer1"      << NewLine
                <<   "  - Inner"     << NewLine
                <<   "  - Inner2"    << NewLine
                <<   "    yyy"       << NewLine
                <<   "* Outer2"      << NewLine
                <<   "  more"        << NewLine
                <<   "simple"        << NewLine;
        UT_EQ( exp, st.Text );


        bool caught= false;
        try
        {
            st.Clear().AddMarked("This is a maker text with an unknown marker: @<>This is where the exception is raised." );
        }
        catch(Exception e)
        {
            caught= true;
            UT_EQ( Enum(aworx::lib::strings::format::Exceptions::UnknownMarker), e.Code() );
            SimpleText efmt;
            efmt.AddException( e );
            UT_PRINT( efmt.Text );
        }
        UT_TRUE( caught );



        caught= false;
        try
        {
            st.Clear().AddMarked("@*>Outer1\n@<*OK, level 0.\n@<*This is where\nthe exception\nis raised." );
        }
        catch(Exception e)
        {
            caught= true;
            UT_EQ( Enum(aworx::lib::strings::format::Exceptions::EndmarkerWithoutStart), e.Code() );
            SimpleText efmt;
            efmt.AddException( e );
            UT_PRINT( efmt.Text );
        }
        UT_TRUE( caught );



        caught= false;
        try
        {
            st.Clear().AddMarked("We must not unindent @<< prior to indent." );
        }
        catch(Exception e)
        {
            caught= true;
            UT_EQ( Enum(aworx::lib::strings::format::Exceptions::EndmarkerWithoutStart), e.Code() );
            SimpleText efmt;
            efmt.AddException( e );
            UT_PRINT( efmt.Text );
        }
        UT_TRUE( caught );

    }
}

//--------------------------------------------------------------------------------------------------
//--- WildcardMatcher
//--------------------------------------------------------------------------------------------------
WildcardMatcher wildcardMatcher;
void TestMatcher(AWorxUnitTesting& ut, const String& haystack, const String& pattern, bool result )
{
    wildcardMatcher.Compile(pattern);
    UT_EQ( result, wildcardMatcher.Match( haystack ) );
}

UT_METHOD( WildcardMatcher )
{
    UT_INIT();

    TestMatcher( ut, "abc.conf", "abc.conf"       , true    );
    TestMatcher( ut, "abc.conf", "ABC.conf"       , false   );
    TestMatcher( ut, "abc.conf", "abc.c*"         , true    );
    TestMatcher( ut, "abc.conf", "abc.c?*"        , true    );
    TestMatcher( ut, "abc.conf", "abc.c?"         , false   );
    TestMatcher( ut, "abc.conf", "abc.c??"        , false   );
    TestMatcher( ut, "abc.conf", "abc.?c??"       , false   );
    TestMatcher( ut, "abc.conf", "abc.?o??"       , true    );
    TestMatcher( ut, "abc.conf", "*.???"          , false   );
    TestMatcher( ut, "abc.conf", "*.????"         , true    );
    TestMatcher( ut, "abc.conf", "*.????"         , true    );
    TestMatcher( ut, "abc.conf", "*.?*???"        , true    );
    TestMatcher( ut, "abc.conf", "*.?**?*?*?"     , true    );
    TestMatcher( ut, "abc.conf", "*.?**??*?*?"    , false   );
    TestMatcher( ut, "abc.conf", "?b?.*"          , true    );
    TestMatcher( ut, "abc.conf", "a?c.*"          , true    );
    TestMatcher( ut, "abc.conf", "ab?.*"          , true    );
    TestMatcher( ut, "abc.conf", "?b?.*"          , true    );
    TestMatcher( ut, "abc.conf", "??c.*"          , true    );
    TestMatcher( ut, "abc.conf", "???.*"          , true    );
    TestMatcher( ut, "abc.conf", "???*"           , true    );
    TestMatcher( ut, "abc.conf", "????????"       , true    );
    TestMatcher( ut, "abc.conf", "?????????"      , false   );
    TestMatcher( ut, "abc.conf", "??????????"     , false   );
    TestMatcher( ut, "abc.conf", "ab???????"      , false   );
    TestMatcher( ut, "abc.conf", "ab??????"       , true    );
    TestMatcher( ut, "abc.conf", "*bc.conf"       , true    );
    TestMatcher( ut, "abc.conf", "a*bc.conf"      , true    );
    TestMatcher( ut, "abc.conf", "a*c.conf"       , true    );
    TestMatcher( ut, "abc.conf", "a*c*"           , true    );
    TestMatcher( ut, "abc.conf", "a*o*"           , true    );
    TestMatcher( ut, "abc.conf", "a*x*"           , false   );

    // quick test for case insenstive matching:
    WildcardMatcher wcm("*bc.c*"  );
    UT_EQ( true , wcm.Match( "abc.conf" , Case::Ignore ) );
    UT_EQ( true , wcm.Match( "abC.conf" , Case::Ignore ) );
    UT_EQ( true , wcm.Match( "ABC.CONF" , Case::Ignore ) );
    UT_EQ( false, wcm.Match( "ABx.CONF" , Case::Ignore ) );
}

UT_CLASS_END

} //namespace
