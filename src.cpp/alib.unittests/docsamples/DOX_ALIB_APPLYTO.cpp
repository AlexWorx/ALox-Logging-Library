// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"

#define TESTCLASSNAME       CPP_ALib_Dox_ApplyTo

//--------------------------------------------------------------------------------------------------
//--- DOCUMENTATION SAMPLES
//--------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
namespace std
{
    extern stringstream applyto_os; // declaration (needed when clang warnings are on)
    stringstream applyto_os;
}
#define cout applyto_os

void ApplyToSample();


//! [DOX_ALIB_APPLYTO_DEFINITION]
#include "alib/alib.hpp"
#include "alib/strings/numberformat.hpp"

// get support for  ostream operator<<() on String objects
#include "alib/compatibility/std_string.hpp"
#include "alib/compatibility/std_iostream.hpp"

#if !defined (HPP_ALIB_TIME_CALENDARTIME)
    #include "alib/time/calendartime.hpp"
#endif

#include <iostream>
#include <iomanip>

using namespace std;
using namespace aworx;

// Partial template function implementation of struct T_Apply for objects of type class Ticks
// (has to be declared in namespace aworx::lib::strings)
namespace aworx { namespace lib { namespace strings {

    // We have to specialize the helper struct T_Apply.
    template<> struct T_Apply<aworx::lib::time::Ticks> : public std::true_type
    {
        // And with it, method Apply
        static inline integer Apply( AString& target, const aworx::lib::time::Ticks& ticks )
        {
            time::TicksCalendarTime calendarTime;
            calendarTime.Set( ticks, Timezone::UTC );
            calendarTime.Format( "yyyy-MM-dd HH:mm", target );
            return 16; // The exact number is not too relevant. But has to be > 0 if something was written!
        }
    };

}}} // closing namespace
//! [DOX_ALIB_APPLYTO_DEFINITION]

void ApplyToSample();
void ApplyToSample()
{
//! [DOX_ALIB_APPLYTO_USE]
aworx::AString sample( "Today is: " );
sample <<  Ticks();
cout << sample << endl;
//! [DOX_ALIB_APPLYTO_USE]
}

void FormatSample1();
void FormatSample1()
{
//! [DOX_ALIB_APPLYTO_FORMAT1]
aworx::AString sample;
sample << 1234.56;
cout << sample << endl;
//! [DOX_ALIB_APPLYTO_FORMAT1]
}

void FormatSample2();
void FormatSample2()
{
    char oldDecPointChar= aworx::NumberFormat::Global.DecimalPointChar;
    char oldTGroupChar=   aworx::NumberFormat::Global.ThousandsGroupChar;
                          aworx::NumberFormat::Global.DecimalPointChar    =',';
                          aworx::NumberFormat::Global.ThousandsGroupChar  ='.';

//! [DOX_ALIB_APPLYTO_FORMAT2]
aworx::AString sample;
sample << Format( 1234.56 , &aworx::NumberFormat::Global );
cout << sample << endl;
//! [DOX_ALIB_APPLYTO_FORMAT2]

    aworx::NumberFormat::Global.DecimalPointChar   = oldDecPointChar;
    aworx::NumberFormat::Global.ThousandsGroupChar = oldTGroupChar;
}


void FormatFieldSample();
void FormatFieldSample()
{
//! [DOX_ALIB_APPLYTO_FIELD]
aworx::AString centered;
centered << '*' << Format::Field( "Hello", 15, Alignment::Center ) << '*';
cout << centered << endl;
//! [DOX_ALIB_APPLYTO_FIELD]
}


#undef cout

//----------- Now to the unit tests -------------
#include "alib.unittests/aworx_unittests.hpp"


namespace ut_aworx {



UT_CLASS()

UT_METHOD( DOX_ALIB_APPLYTO )
{
    UT_INIT();

    ApplyToSample();
    ut.WriteResultFile( "DOX_ALIB_APPLYTO.txt", applyto_os.str(), "//! [OUTPUT]" );

    applyto_os.str(string());
    FormatFieldSample();
    ut.WriteResultFile( "DOX_ALIB_APPLYTO_FIELD.txt", applyto_os.str(), "//! [OUTPUT]" );


    applyto_os.str(string());
    FormatSample1();
    ut.WriteResultFile( "DOX_ALIB_APPLYTO_FORMAT1.txt", applyto_os.str(), "//! [OUTPUT]" );

    applyto_os.str(string());
    FormatSample2();
    ut.WriteResultFile( "DOX_ALIB_APPLYTO_FORMAT2.txt", applyto_os.str(), "//! [OUTPUT]" );
}


UT_CLASS_END

} //namespace
