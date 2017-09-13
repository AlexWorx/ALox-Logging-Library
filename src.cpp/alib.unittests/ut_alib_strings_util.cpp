// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"

#if !defined (HPP_ALIB_STRINGS_UTIL_SIMPLETEXT)
    #include "alib/strings/util/simpletext.hpp"
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

    String256 exp;

    {
        SimpleText st;
        st.AddIndent(2);

        st.Text._(); st.AddParagraph( ""                  ); exp._()                                     ;    UT_EQ( exp, st.Text );
        st.Text._(); st.AddParagraph( "\n"                ); exp._() <<   "\n"                           ;    UT_EQ( exp, st.Text );
        st.Text._(); st.AddParagraph( "\n\n"              ); exp._() <<   "\n\n"                         ;    UT_EQ( exp, st.Text );
        st.Text._(); st.AddParagraph(     "123\n4567"     ); exp._() <<   "  123\n  4567"      << NewLine;    UT_EQ( exp, st.Text );
        st.Text._(); st.AddParagraph(   "\n123\n4567"     ); exp._() << "\n  123\n  4567"      << NewLine;    UT_EQ( exp, st.Text );
        st.Text._(); st.AddParagraph( "\n\n123\n\n4567"   ); exp._() << "\n\n  123\n\n  4567"  << NewLine;    UT_EQ( exp, st.Text );
    //    UT_TRUE( st.Text.StartsWith(exp) );
    }


    {
        SimpleText st;

        st.LineWidth= 4;
        st.AddParagraph("1 22 333" );
        st.AddParagraph("--" );
        st.LineWidth= 3;
        st.AddParagraph("22 1" );
        st.AddParagraph("--" );
        st.AddParagraph("1 1" );

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
        st.AddParagraph("123456789 123<--------" );
        st.LineWidth= 11;
        st.AddIndent(5);
        st.AddParagraph("1 22 333 4444 55555 666666 55555 4444 333 22 1 22 333 22 1" );

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
        st.AddParagraph("123456789 12345<-------" );
        st.LineWidth= 15;
        st.AddIndent(5);
        st.AddParagraph("1 22 333 4444 55555 666666 55555 4444 333 22 1 22 333 22 1" );

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
        st.Indent._()._("  ");  st.Text._();  st.AddParagraph( ""             );   UT_EQ( ""                          , st.Text );
        st.Indent._()._("XY");  st.Text._();  st.AddParagraph( ""             );   UT_EQ( ""                          , st.Text );
        st.Indent._()._("  ");  st.Text._();  st.AddParagraph( "\n"           );   UT_EQ( "\n"                        , st.Text );
        st.Indent._()._("XY");  st.Text._();  st.AddParagraph( "\n"           );   UT_EQ( "XY\n"                      , st.Text );
        st.Indent._()._("  ");  st.Text._();  st.AddParagraph( "\n1"          );   UT_EQ( "\n  1\n"                   , st.Text );
        st.Indent._()._("  ");  st.Text._();  st.AddParagraph( "\n1"          );   UT_EQ( "\n  1\n"                   , st.Text );
        st.Indent._()._("XY");  st.Text._();  st.AddParagraph( "\n1\n\n\n2"    );   UT_EQ( "XY\nXY1\nXY\nXY\nXY2\n"   , st.Text );
//        st.Indent._()._("XY");  st.Text._();  st.AddParagraph("z" );  UT_EQ( "XYz\n"          , st.Text );
    }

    const String& lorem= "Lorem ipsum dolor sit amet, consetetur.\n"
                         "Sadipscing elitr, sed diam nonumy eirmod tempor.";
    {
        SimpleText st;

        // unchanged
        st.AddParagraph(lorem );
        exp._() << lorem << NewLine;
        UT_EQ( exp, st.Text );
        st.Text._();


        st.AddIndent(2);
        st.LineWidth= 22;
        st.AddParagraph(lorem );
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
        st.AddParagraph(lorem );
        //            123456789 123456789 123456789
        exp._() <<   "  Lorem ipsum dolor sit amet,"    << NewLine
                <<   "  consetetur."                    << NewLine
                <<   "  Sadipscing elitr, sed diam"     << NewLine
                <<   "  nonumy eirmod tempor."          << NewLine
                ;
        UT_EQ( exp, st.Text );

        st.LineWidth= 32;
        st.Text._();
        st.AddParagraph(lorem );
        //            123456789 123456789 123456789 12
        exp._() <<   "  Lorem ipsum dolor sit amet,"    << NewLine
                <<   "  consetetur."                    << NewLine
                <<   "  Sadipscing elitr, sed diam"     << NewLine
                <<   "  nonumy eirmod tempor."          << NewLine
                ;
        UT_EQ( exp, st.Text );


        st.LineWidth= 32;
        st.IndentFirstLine= "* ";
        st.Text._();
        st.AddParagraph(lorem );
        //            123456789 123456789 123456789 12
        exp._() <<   "* Lorem ipsum dolor sit amet,"    << NewLine
                <<   "  consetetur."                    << NewLine
                <<   "  Sadipscing elitr, sed diam"     << NewLine
                <<   "  nonumy eirmod tempor."          << NewLine
                ;
        UT_EQ( exp, st.Text );
    //    UT_TRUE( st.Text.StartsWith(exp) );
    }


    //-------- full justification ("Blocksatz") -------
    {
        SimpleText st;

        st.Justifier= ' ';
        st.LineWidth= 10;
        st.Text._();  st.AddParagraph( "1 0123456789"       );  UT_EQ("1\n0123456789\n"           , st.Text );
        st.Text._();  st.AddParagraph( "1 1 0123456789"     );  UT_EQ("1        1\n0123456789\n"  , st.Text );
        st.Text._();  st.AddParagraph( "1 1 1 0123456789"   );  UT_EQ("1   1    1\n0123456789\n"  , st.Text );
        st.Text._();  st.AddParagraph( "1 1 11 0123456789"  );  UT_EQ("1   1   11\n0123456789\n"  , st.Text );
        st.Text._();  st.AddParagraph( "1 1 111 0123456789" );  UT_EQ("1  1   111\n0123456789\n"  , st.Text );

        st.LineWidth= 32;
        st.AddIndent(2);
        st.IndentFirstLine= nullptr;
        st.Justifier= ' ';
        st.Text._();
        st.AddParagraph(lorem );
        //            123456789 123456789 123456789 12
        exp._() <<   "  Lorem ipsum  dolor  sit  amet,"  << NewLine
                <<   "  consetetur."                    << NewLine
                <<   "  Sadipscing  elitr,  sed   diam"  << NewLine
                <<   "  nonumy eirmod tempor."          << NewLine
                ;
        UT_EQ( exp, st.Text );
    //    UT_TRUE( st.Text.StartsWith(exp) );


        UT_PRINT("'Visual' Tests (no checking rules, last time I saw it, it worked :-)" )
        st.IndentFirstLine= nullptr;
        st.Justifier= ' ';
        st.LineWidth= 32;  st.Text._();   st.AddParagraph( lorem );  UT_PRINT("123456789 123456789 123456789 12|--------\n", st.Text,"\n" );
        st.LineWidth= 33;  st.Text._();   st.AddParagraph( lorem );  UT_PRINT("123456789 123456789 123456789 123|-------\n", st.Text,"\n" );
        st.LineWidth= 34;  st.Text._();   st.AddParagraph( lorem );  UT_PRINT("123456789 123456789 123456789 1234|------\n", st.Text,"\n" );
        st.LineWidth= 35;  st.Text._();   st.AddParagraph( lorem );  UT_PRINT("123456789 123456789 123456789 12345|-----\n", st.Text,"\n" );
        st.LineWidth= 36;  st.Text._();   st.AddParagraph( lorem );  UT_PRINT("123456789 123456789 123456789 123456|----\n", st.Text,"\n" );
        st.LineWidth= 37;  st.Text._();   st.AddParagraph( lorem );  UT_PRINT("123456789 123456789 123456789 1234567|---\n", st.Text,"\n" );
        st.LineWidth= 38;  st.Text._();   st.AddParagraph( lorem );  UT_PRINT("123456789 123456789 123456789 12345678|--\n", st.Text,"\n" );
        st.LineWidth= 39;  st.Text._();   st.AddParagraph( lorem );  UT_PRINT("123456789 123456789 123456789 123456789|-\n", st.Text,"\n" );
        st.LineWidth= 40;  st.Text._();   st.AddParagraph( lorem );  UT_PRINT("123456789 123456789 123456789 123456789 |\n", st.Text,"\n" );
        st.LineWidth= 41;  st.Text._();   st.AddParagraph( lorem );  UT_PRINT("123456789 123456789 123456789 123456789 1|\n", st.Text,"\n" );
    }


}


UT_CLASS_END

} //namespace
