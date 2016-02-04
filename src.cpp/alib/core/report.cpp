// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

#include "alib/compatibility/std_iostream.hpp"

#if !defined (HPP_AWORX_LIB_SYSTEM_SYSTEMINFO)
    #include "alib/system/system.hpp"
#endif

#if !defined (HPP_AWORX_LIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
#endif

#include <iostream>


using namespace std;
using namespace aworx::lib::strings;
using namespace aworx::lib::system;
using namespace aworx::lib::threads;

namespace aworx {
namespace           lib {


// #################################################################################################
// static objects
// #################################################################################################
Report Report::defaultReport;


// #################################################################################################
// class ConsoleReportWriter
// #################################################################################################
void ConsoleReportWriter::Report   ( const Report::Message& msg )
{
    cerr << "ALib Report ";
    cerr << (msg.Type == 0 ? "Error: "
                           : "Warng: " );
    cerr.write( msg.Contents.Buffer(), msg.Contents.Length() );
    cerr << endl;

    #if defined( _WIN32 )
        if ( System::IsDebuggerPresent() )
        {
            OutputDebugStringA( "ALib Report " );
            OutputDebugStringA( msg.Type == 0 ? "Error: "
                                              : "Warng: " );
            OutputDebugStringA( msg.Contents.ToCString() );
            OutputDebugStringA( "\r\n" );
        }
    #endif
}


// #################################################################################################
// class Report::Message
// #################################################################################################
Report::Message::Message( ALIB_DBG_SRC_INFO_PARAMS_DECL  int type, const TString& msg  )
: ALIB_DEBUG_CODE( File(file),  Line(line), Func(func), )
  Type(type),
  Contents(msg)
{
}

// #################################################################################################
// class Report
// #################################################################################################
Report::Report()
{
    lock= new ThreadLockNR();
    ReplaceReportWriter( nullptr, false );
}

Report::~Report()
{
    if (reportWriter) delete reportWriter;
    delete lock;
}

void Report::DoReport( ALIB_DBG_SRC_INFO_PARAMS_DECL   int type, const TString& msg )
{
    OWN(*lock);
    if (recursionBlocker)
        return;
    recursionBlocker= true;
        Message message(  ALIB_DEBUG_CODE( file, line, func, )
                          type,
                          msg                                       );

        reportWriter->Report( message );

        #if defined(ALIB_DEBUG)

            bool halt=     (type == 0 && HaltOnError)
                        || (type != 0 && HaltOnWarning);

            #if defined( _WIN32 )
                if( halt )
                {
                    if ( System::IsDebuggerPresent() )
                        DebugBreak();
                    else
                        assert( false );
                }
            #else
                assert( !halt );
            #endif

        #endif
    recursionBlocker= false;
}

ReportWriter* Report::ReplaceReportWriter( ReportWriter* newReportWriter, bool deleteOld )
{
    OWN(*lock);
    ReportWriter* oldReportWriter=    reportWriter;
    if ( deleteOld && oldReportWriter )
        delete oldReportWriter;
    reportWriter=     newReportWriter ? newReportWriter : new ConsoleReportWriter();
    return deleteOld ? nullptr : oldReportWriter;
}


}}// namespace aworx::lib

