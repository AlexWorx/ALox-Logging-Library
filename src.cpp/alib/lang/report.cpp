// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#include "alib/compatibility/std_iostream.hpp"

#if !defined (HPP_ALIB_THREADS_SMARTLOCK)
    #include "alib/threads/smartlock.hpp"
#endif

#if !defined(HPP_ALIB_STRINGS_FORMAT_FORMATTER_PYTHONSTYLE)
    #include "alib/strings/format/formatterpythonstyle.hpp"
#endif

#if !defined(HPP_ALIB_STRINGS_FORMAT_FORMATTER)
    #include "alib/strings/format/formatter.hpp"
#endif


namespace aworx { namespace lib { namespace lang
{

// #################################################################################################
// static objects
// #################################################################################################
Report* Report::defaultReport                                                             = nullptr;

// #################################################################################################
// class Report
// #################################################################################################
Report::Report()
{
    lock= new ThreadLock();
    PushHaltFlags( true, false );
    PushWriter( ReportWriterStdIO::GetSingleton() );
}

Report::~Report()
{
    PopWriter( ReportWriterStdIO::GetSingleton() );
    delete lock;
}

void Report::TerminationCleanUp()
{
    if ( defaultReport != nullptr )
        delete defaultReport;
    if( ReportWriterStdIO::singleton )
        delete ReportWriterStdIO::singleton;
}


void Report::PushHaltFlags( bool haltOnErrors, bool haltOnWarnings )
{
    OWN(*lock);
    haltAfterReport.push(    (haltOnErrors   ? 1 : 0)
                           + (haltOnWarnings ? 2 : 0));
}
void Report::PopHaltFlags()
{
    #if ALIB_DEBUG
        bool stackEmptyError;
    #endif

    {
        OWN(*lock);
        haltAfterReport.pop();

        #if ALIB_DEBUG
            stackEmptyError= haltAfterReport.size() == 0;
        #endif
    }

    #if ALIB_DEBUG
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

void Report::DoReport( const Message& message )
{
    OWN(*lock);
    if (recursionBlocker)
        return;
    recursionBlocker= true;

        if ( writers.size() > 0 )
            writers.top()->Report( message  );

        #if ALIB_DEBUG
            int haltFlags= haltAfterReport.top();
            bool halt=     (message.Type == 0 && ( (haltFlags & 1) != 0) )
                        || (message.Type == 1 && ( (haltFlags & 2) != 0) );

            #if defined( _WIN32 )
                if( halt )
                {
                    if ( ALIB::IsDebuggerPresent() )
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


void ReportWriterStdIO::NotifyActivation( lang::Phase phase )
{
    if ( phase == Phase::Begin )
        ALIB::StdOutputStreamsLock.AddAcquirer   ( nullptr );
    else
        ALIB::StdOutputStreamsLock.RemoveAcquirer( nullptr );
}


void ReportWriterStdIO::Report( const Report::Message& msg )
{
    ALIB::StdOutputStreamsLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);

        String512 buffer( "ALib " );
             if (  msg.Type == 0 )   buffer._( "Error:   " );
        else if (  msg.Type == 1 )   buffer._( "Warning: " );
        else                         buffer._( "Report (type=" )._( msg.Type )._("): ");


        auto& out   = msg.Type == 0 || msg.Type == 1 ? std::cerr : std::cout;
        auto& other = msg.Type == 0 || msg.Type == 1 ? std::cout : std::cerr;

        Formatter::AcquireDefault().Format( buffer, dynamic_cast<const Boxes&>( msg ) );
        Formatter::ReleaseDefault();

        out  .flush();
        other.flush();
        out << std::endl;
        out.write( buffer.Buffer(), buffer.Length() );
        out << std::endl;
        out  .flush();
        other.flush();


        #if defined( _WIN32 )
            if ( ALIB::IsDebuggerPresent() )
            {
                OutputDebugStringA( buffer.ToCString() );
                OutputDebugStringA( "\r\n" );
            }
        #endif
    ALIB::StdOutputStreamsLock.Release();
}


}}}// namespace aworx::lib::lang

