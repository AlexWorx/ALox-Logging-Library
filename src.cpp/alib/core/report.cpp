// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif

#include "alib/compatibility/std_iostream.hpp"

#if !defined (HPP_ALIB_SYSTEM_SYSTEM)
    #include "alib/system/system.hpp"
#endif

#if !defined (HPP_ALIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
#endif

#include <iostream>


using namespace std;

namespace aworx {
namespace           lib {


// #################################################################################################
// static objects
// #################################################################################################
Report* Report::defaultReport   = nullptr;


// #################################################################################################
// class ConsoleReportWriter
// #################################################################################################
ConsoleReportWriter ConsoleReportWriter::Singleton;

void ConsoleReportWriter::NotifyActivation( enums::Phase phase )
{
    if ( phase == Phase::Begin )
        ALIB::StdOutputStreamsLock.AddAcquirer   ( nullptr );
    else
        ALIB::StdOutputStreamsLock.RemoveAcquirer( nullptr );
}

void ConsoleReportWriter::Report( const Report::Message& msg )
{
    ALIB::StdOutputStreamsLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
        String64 prefix( "ALib " );
             if (  msg.Type == 0 )   prefix._( "Error:   " );
        else if (  msg.Type == 1 )   prefix._( "Warning: " );
        else                         prefix._( "Report (type=" )._( msg.Type )._("): ");


        auto out = msg.Type == 0 || msg.Type == 1 ? &cerr : &cout;
        out->flush();
        out->write(       prefix.Buffer(),       prefix.Length() );
        out->write( msg.Contents.Buffer(), msg.Contents.Length() );
        (*out) << endl;
        out->flush();

        #if defined( _WIN32 )
            if ( System::IsDebuggerPresent() )
            {
                OutputDebugStringA( prefix.ToCString() );
                OutputDebugStringA( msg.Contents.ToCString() );
                OutputDebugStringA( "\r\n" );
            }
        #endif
    ALIB::StdOutputStreamsLock.Release();
}


// #################################################################################################
// class Report::Message
// #################################################################################################
Report::Message::Message( int type, const TString& msg,
                          const strings::TString& file, int line, const strings::TString& func   )
: Type(type),
  Contents(msg),
  File(file),  Line(line), Func(func)
{
}

// #################################################################################################
// class Report
// #################################################################################################
Report::Report()
{
    lock= new ThreadLock();
    PushHaltFlags( true, false );
    PushWriter( &ConsoleReportWriter::Singleton );
}

Report::~Report()
{
    PopWriter( &ConsoleReportWriter::Singleton );
    delete lock;
}

void Report::PushHaltFlags( bool haltOnErrors, bool haltOnWarnings )
{
    OWN(*lock);
    haltAfterReport.push(    (haltOnErrors   ? 1 : 0)
                           + (haltOnWarnings ? 2 : 0));
}
void Report::PopHaltFlags()
{
    #if defined(ALIB_DEBUG)
        bool stackEmptyError;
    #endif

    {
        OWN(*lock);
        haltAfterReport.pop();

        #if defined(ALIB_DEBUG)
            stackEmptyError= haltAfterReport.size() == 0;
        #endif
    }

    #if defined(ALIB_DEBUG)
        if ( stackEmptyError )
        {
            PushHaltFlags( true, true );
            ALIB_ERROR( "Stack empty, too many pop operations" );
        }
    #endif
}

void Report::PushWriter( ReportWriter* newReportWriter )
{
    OWN(*lock);
    if ( writers.size() > 0 )
        writers.top()->NotifyActivation( Phase::End );
    writers.push( newReportWriter );
    newReportWriter->NotifyActivation( Phase::Begin );
}

void Report::PopWriter( ReportWriter* checkWriter )
{
    OWN(*lock);
    if ( writers.size() == 0 )             {  ALIB_ERROR( "No Writer to remove" );         return; }
    if ( writers.top()  != checkWriter )   {  ALIB_ERROR( "Report Writer is not actual" ); return; }
    writers.top()->NotifyActivation( Phase::End );
    writers.pop();
    if ( writers.size() > 0 )
        writers.top()->NotifyActivation( Phase::Begin );
}

ReportWriter* Report::PeekWriter()
{
    OWN(*lock);
    return writers.top();
}

void Report::DoReport( int type, const TString& msg,
                       const strings::TString& file, int line, const strings::TString& func  )
{
    OWN(*lock);
    if (recursionBlocker)
        return;
    recursionBlocker= true;
        Message message(  type, msg, file, line, func );

        if ( writers.size() > 0 )
            writers.top()->Report( message );

        #if defined(ALIB_DEBUG)
            int haltFlags= haltAfterReport.top();
            bool halt=     (type == 0 && ( (haltFlags & 1) != 0) )
                        || (type == 1 && ( (haltFlags & 2) != 0) );

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


}}// namespace aworx::lib

