// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#define TESTCLASSNAME       CPP_ALib__Dox

//--------------------------------------------------------------------------------------------------
//--- DOCUMENTATION SAMPLEs
//--------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
namespace std { stringstream applyto_os; }
#define cout applyto_os


//! [DOX_ALIB_APPLYTO_DEFINITION]
#include "alib/alib.hpp"
#include "alib/time/ticks.hpp"

// get support for  ostream operator<<() on String objects
#include "alib/compatibility/std_string.hpp"
#include "alib/compatibility/std_iostream.hpp"

#include <iostream>
#include <iomanip>

using namespace std;
using namespace aworx;

// Partial template function implementation of ApplyTo for objects of type class Ticks
// (has to be declared in namespace aworx::lib::strings)
namespace aworx { namespace lib { namespace strings {

    // we have to define the helper struct IsApplicable. Its whole reason of existence is
    // to be able to throw compile time errors for types that do not have an ApplyTo
    // specialization
    template<>  struct       IsApplicable<const aworx::lib::time::Ticks&> : public std::true_type {};

    // And now the ApplyTo specialization itself
    template<>  inline   int ApplyTo( AString& target, const aworx::lib::time::Ticks& ticks )
    {
        time::TicksCalendarTime calendarTime;
        calendarTime.Set( ticks, Timezone::UTC );
        calendarTime.Format( "yyyy-MM-dd HH:mm", target );
        return 16; // The exact number not too relevant. But has to be > 0 if something was written!
    }

}}} // closing namespace
//! [DOX_ALIB_APPLYTO_DEFINITION]

void ApplyToSample()
{
//! [DOX_ALIB_APPLYTO_USE]
aworx::AString sample( "Today is: " );
sample <<  Ticks();
cout << sample << endl;
//! [DOX_ALIB_APPLYTO_USE]
}


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
#include "alib/strings/tokenizer.hpp"
#include "alib/strings/numberformat.hpp"


namespace ut_aworx {



UT_CLASS()

UT_METHOD( DOX_ALIB_APPLYTO )
{
    UT_INIT();

    ApplyToSample();
    ut.WriteResultFile( "DOX_ALIB_APPLYTO.txt", applyto_os.str(), "//! [OUTPUT]" );

    //applyto_os.clear();
    applyto_os.str(string());

    FormatFieldSample();
    ut.WriteResultFile( "DOX_ALIB_APPLYTO_FIELD.txt", applyto_os.str(), "//! [OUTPUT]" );
}


UT_CLASS_END

} //namespace
