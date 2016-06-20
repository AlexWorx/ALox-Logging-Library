// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "alib/strings/tokenizer.hpp"
#include "alib/strings/numberformat.hpp"
#include "alib/time/ticks.hpp"
#include "alib/compatibility/std_iostream.hpp"
#include "alib/compatibility/qt.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>


#include "aworx_unittests.hpp"

#include <qt/QtCore/QString>
#include <qt/QtCore/QVector>
#include <qt/QtCore/QRect>

#define TESTCLASSNAME       CPP_ALib_Compatiblity_QT


using namespace std;
using namespace aworx;

namespace ut_aworx {


UT_CLASS()

//--------------------------------------------------------------------------------------------------
//--- Explicit constructors
//--------------------------------------------------------------------------------------------------
UT_METHOD( QT_String )
{
    UT_INIT();


    QString qts( "QString" );
    AString test( qts );        UT_EQ( "QString", test );
    test._()._<true> (qts);     UT_EQ( "QString", test );
    test._()._<false>(qts);     UT_EQ( "QString", test );

    QByteArray qba= QString ( "QByteArray" ).toLocal8Bit();
    String s( &qba );
    test._()._<true> (s);       UT_EQ( "QByteArray", test );
    test._()._<false>(s);       UT_EQ( "QByteArray", test );

    QVector<uint> qv4=  QString( "QVector<uint>" ).toUcs4();
    AString test4( qv4 );       UT_EQ( "QVector<uint>", test4 );
    test4._()._<true> (qv4);    UT_EQ( "QVector<uint>", test4 );
    test4._()._<false>(qv4);    UT_EQ( "QVector<uint>", test4 );


    QLatin1String ql1s( "Latin1String" );
    test._()._<true> (ql1s);    UT_EQ( "Latin1String", test );
    test._()._<false>(ql1s);    UT_EQ( "Latin1String", test );

    QChar qc= 'c';
    test._()._<true> (qc);      UT_EQ( "c", test );
    test._()._<false>(qc);      UT_EQ( "c", test );


    UT_PRINT( String128() << "QString toUtf8() " );
    UT_PRINT( String128() << "  QString: German:  " << QString("ÄÜÖäüöß").toLocal8Bit() );
    UT_PRINT( String128() << "  QString: Greek:   " << QString().fromStdWString(L"\u03B1\u03B2\u03B3\u03B4\u03B5").toLocal8Bit() );
    UT_PRINT( String128() << "  QString: Smileys: " << QString().fromStdWString(L"\U0001F609 * \U0001F607 * \U0001F603 * \U0001F60E * "
                                                                         "\U00000361\U000000b0\U0000035c\U00000296\U00000361\U000000b0").toLocal8Bit() );
    UT_PRINT( String128() << "QString directly " );
    UT_PRINT( String128() << "  QString: German:  " << QString().fromLocal8Bit("ÄÜÖäüöß") );
    UT_PRINT( String128() << "  QString: Greek:   " << QString().fromStdWString(L"\u03B1\u03B2\u03B3\u03B4\u03B5") );

}

UT_CLASS_END

} //namespace
