// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "alib/compatibility/std_string.hpp"
#include "alib/compatibility/std_iostream.hpp"

#include "alox/alox_console_loggers.hpp"
#include "alox/loggers/memorylogger.hpp"

#include <iostream>
#include <string>
#include <vector>

#define TESTCLASSNAME       CPP_Dox_ReferenceManual
#include "alib.unittests/aworx_unittests.hpp"

using namespace std;
using namespace ut_aworx;

using namespace aworx;

namespace ut_alox {


UT_CLASS()

//##################################################################################################
// SAMPLE code of class ESC documentation
//##################################################################################################

void docSampleESC()
{

//! [DOX_ALOX_ESC]
Log_Info( String32( "The result is ") << ESC::RED << "42" )
 //! [DOX_ALOX_ESC]
}


UT_METHOD( ALoxDocSamples )
{
    UT_INIT();

    UT_PRINT("*** ALox Sample tests: ESC ***")
    docSampleESC();
}


//##################################################################################################
// SAMPLE code installing a report writer
//##################################################################################################

void docSampleInstallReportWriter()
{
Log_Prune( Lox lox("RELEASE");               )
Log_Prune( Logger* myReleaseLogger= nullptr; )

#define LOX_LOX lox

//! [DOX_ALOX_INSTALL_REPORT_WRITER]
Log_Prune( Log::AddALibReportWriter( &LOX_LOX ); )
Log_Prune( Lox_SetVerbosity( myReleaseLogger, Verbosity::Verbose, lox::ALoxReportWriter::LogDomain() ); )
//! [DOX_ALOX_INSTALL_REPORT_WRITER]

//! [DOX_ALOX_INSTALL_REPORT_WRITER_2]
Log_Prune( Log::RemoveALibReportWriter() );
//! [DOX_ALOX_INSTALL_REPORT_WRITER_2]

}



UT_CLASS_END
} // namespace


