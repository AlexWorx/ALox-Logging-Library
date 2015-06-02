// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"
#include "textlogger.hpp"


#if !defined (HPP_AWORX_UTIL_ENVIRONMENT)
    #include "environment.hpp"
#endif

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif

using namespace std;
using namespace aworx::util;
using namespace aworx::lox;
using namespace aworx::lox::core;


// #################################################################################################
// TextLoggerLineFormatter
// #################################################################################################

void TextLoggerLineFormatter::WriteMetaInfo( Logger& logger, AString& buf, const AString& domain, Log::Level level, int indent, CallerInfo* caller )
{
    // check
    if ( Format.Length() == 0 )
        return;

    // clear DateTime singleton
    callerDateTime.Year= numeric_limits<int>::min();

    // loop/switch over content specified in configuration array
    int         si=          0;
    int         ei=          0;
    const char* lf=          Format.Buffer();
    int         lfLen=       Format.Length();
    char        c;
                autoTabNo=   0;
    for(;;)
    {
        // search the next %
        while ( ( c= lf[ei] ) != '%' &&  ++ei < lfLen ) {}

        // log substring between commands
        buf.Append( Format, si, ei - si );

        // not found a %? -> quit
        if ( c != '%' )
            break;

        // process the found variable
        ei= processVariable( logger, domain, level, caller, buf, ++ei );

        // next
        si= ++ei;
    }

    // add indent spaces
    for (int i= indent; i > 0 ; i--)
        buf.Append( IndentString );
}

int TextLoggerLineFormatter::processVariable( Logger&logger, const AString& domain, Log::Level level, CallerInfo* caller, AString& buf, int formatStringIdx )
{
    // process commands
    switch ( Format[formatStringIdx] )
    {
        // caller info
        case 'C':
        {
            // read sub command
            char s= Format[++formatStringIdx];

            // add source file
            if ( s == 'F' )
            {
                const char* sourceFileName=        caller->SourceFileName;
                if ( sourceFileName != nullptr )
                {
                    // detect cutable prefix from the filename path and current working directory
                    // Note: we do this only once. And we do not use the prefix here
                    //       This is up to the derived logger to do so.
                    if ( ConsumableSourcePathPrefix.GetAllocation() == 0 )
                    {
                        // get system execution path and compare to file path
                        AString currentDir( Environment::CurrentDirectory() );

                        // Get the prefix that is the same in both paths
                        int i= 0;
                        while (     i < currentDir.Length()
                                &&  sourceFileName[i] != '\0'
                                #if defined ( _MSC_VER ) // MS Compiler delivers __FILE__ in lower case
                                    &&  tolower( currentDir[i] ) == tolower( sourceFileName[i] )
                                #else
                                    &&           currentDir[i]   ==          sourceFileName[i]
                                #endif
                                )
                            i++;

                        // store consumable prefix and its length. If unsuccessful, "" is stored to prevent searching again
                        if ( i > 1 )
                        {
                            ConsumableSourcePathPrefix.Append( currentDir, 0, i );
                            #if defined ( _MSC_VER ) // MS Compiler delivers __FILE__ in lower case
                                ConsumableSourcePathPrefix.ConvertCase( false );
                            #endif
                        }
                        else
                            ConsumableSourcePathPrefix= ""; // mark as not null
                    }

                    // can we cut the source file name by a prefix?
                    int sfnLen= strlen( sourceFileName );
                    int appendStart= ConsumableSourcePathPrefix.ContainsAt( sourceFileName, 0, false, ConsumableSourcePathPrefix.Length() )
                                        ? ConsumableSourcePathPrefix.Length()
                                        : 0;
                    buf.Append( sfnLen, sourceFileName, appendStart );
                }
                else
                    buf.Append( NoSourceFileInfo );
            }

            // add line number or method name
            else if ( s == 'L' )  buf.Append( caller->LineNumber );
            else if ( s == 'M' )  buf.Append( caller->MethodName ? caller->MethodName :  NoMethodInfo );
        }
        break;

        // Date
        case 'D':
        {
            // get time stamp as TicksCalendarTime once
            if ( callerDateTime.Year == numeric_limits<int>::min() )
                callerDateTime.Set( caller->TimeStamp );

            // if standard format, just write it out
            if ( strcmp( DateFormat, "yyyy-MM-dd" ) == 0 )
            {
                buf.Append( callerDateTime.Year,     4 ).Append( '-' )
                   .Append( callerDateTime.Month,    2 ).Append( '-' )
                   .Append( callerDateTime.Day,      2 );
            }
            // user defined format
            else
                callerDateTime.Format( DateFormat, buf  );
        }
        break;

        // %Tx: Time
        case 'T':
        {
            // read sub command
            char s= Format[++formatStringIdx];

            // %TD: Time of Day
            if ( s == 'D' )
            {
                // get time stamp as TicksCalendarTime once
                if ( callerDateTime.Year == numeric_limits<int>::min() )
                    callerDateTime.Set( caller->TimeStamp );

                // avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!)
                // and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
                if ( strcmp( TimeOfDayFormat, "HH:mm:ss" ) == 0 )
                {
                    buf .Append( callerDateTime.Hour,    2 ).Append( ':' )
                        .Append( callerDateTime.Minute,  2 ).Append( ':' )
                        .Append( callerDateTime.Second,  2 );
                }

                // user defined format
                else
                    callerDateTime.Format( TimeOfDayFormat, buf  );
            }

            // %TE: Time Elapsed
            else if ( s == 'E' )
            {
                TicksSpan elapsed( caller->TimeStamp, logger.TimeOfCreation );

                if ( elapsed.Days  > 0 )    buf.Append( elapsed.Days  ).Append( TimeElapsedDays );
                if ( elapsed.Hours > 0 )    buf.Append( elapsed.Hours ).Append( ':' );

                buf.Append( elapsed.Minutes,       2).Append( ':' )
                   .Append( elapsed.Seconds,       2).Append( '.' )
                   .Append( elapsed.Milliseconds,  3);
            }

            // %TE: Time Diff
            else
            {
                writeTimeDiff( buf, caller->TimeStamp.Since( logger.TimeOfLastLog ).InNanos() );
            }
        }
        break;


        // Thread
        case 't':
        {
            #if defined(AWXU_FEAT_THREADS)
                // get name length and store max value
                const AString& threadName= caller->getThreadNameAndID(nullptr);
                if ( AutoGrowThreadNameLength < threadName.Length() )
                     AutoGrowThreadNameLength=  threadName.Length();

                // append thread name
                buf.Field().Append( threadName ).Field( AutoGrowThreadNameLength, AString::Align::CENTER );
            #endif
        }
        break;

        case 'L':    buf.Append(   level == Log::Level::ERROR      ? LogLevelError
                                 : level == Log::Level::WARNING   ? LogLevelWarning
                                 : level == Log::Level::INFO      ? LogLevelInfo
                                 :                                  LogLevelVerbose    );
                    break;
        case 'O':
        {
            // save the maximum length of any domain name
            if ( AutoGrowDomainNameLength < domain.Length() )
                AutoGrowDomainNameLength= domain.Length();

            // If no domain logged yet and domain name is empty, we omit it
            buf.Field().Append( domain ).Field( AutoGrowDomainNameLength, AString::Align::CENTER );
        }
        break;

        case '#':    buf.Append( logger.CntLogs, LogNumberMinDigits );
        break;

        // A: Auto tab
        case 'A':
        {
            // read extra space from format string
            int newIdx=     formatStringIdx + 1;
            int extraSpace= Format.ToInt( newIdx );
            if ( newIdx == formatStringIdx + 1 )
                extraSpace=         1;
            else
                formatStringIdx=    newIdx - 1;

            // grow tab array as needed
            if ( (int) AutoTabs.size() == autoTabNo )
                AutoTabs.emplace_back( 0 );

            // increase tab? If yes, add some extra space to avoid too many increases
            int bufLen=    buf.Length();
            int tab=    AutoTabs[ autoTabNo ];
            if ( tab <= bufLen )
                tab=
                AutoTabs[ autoTabNo ]=    bufLen + ( tab == 0 ? 1 : extraSpace);

            // jump to next tab level
            buf.Append( ' ', tab - bufLen );

            // increase auto tab index for next 'A' command
            autoTabNo++;
        }
        break;

        case 'N':    buf.Append( logger.Name );
        break;

        default:    if( AWXU::AcquireErrorHandler() )
                        AWXU::Error( AString("TextLoggerLineFormatter: Unknown format character \'").Append(Format[formatStringIdx]).Append("\'").Buffer() );
                    break;
    }

    // return the new index in format string
    return formatStringIdx;
}

void TextLoggerLineFormatter::writeTimeDiff( AString& buf, int_fast64_t diffNanos )
{
    // unmeasurable?
    if ( diffNanos < TimeDiffMinimum )
    {
        buf.Append( TimeDiffNone );
        return;
    }

    if ( diffNanos < 1000 )
    {
        buf.Append( (int) diffNanos, 3 ).Append( TimeDiffNanos );
        return;
    }

    // we continue with micros
    int_fast64_t diffMicros= diffNanos / 1000L;

    // below 1000 microseconds?
    if ( diffMicros < 1000 )
    {
        buf.Append( (int) diffMicros, 3 ).Append( TimeDiffMicros );
        return;
    }

    // below 1000 ms?
    if ( diffMicros < 1000000 )
    {
        buf.Append( (int) (diffMicros / 1000), 3 ).Append( TimeDiffMillis );
        return;
    }


    // below 10 secs (rounded) ?
    if ( diffMicros < 9995000 )
    {
        // convert to hundredth of secs
        int_fast64_t hundredthSecs=  ((diffMicros / 1000) + 5) / 10;

        // print two digits after dot x.xx
        buf.Append( (int) (hundredthSecs / 100), 1 )
           .Append( '.' )
           .Append( (int) (hundredthSecs % 100), 2 )
           .Append( TimeDiffSecs );
        return;
    }

    // convert to tenth of secs
    int_fast64_t tenthSecs=  ((diffMicros / 10000) + 5) / 10 ;

    // below 100 secs ?
    if ( tenthSecs < 1000 )
    {
        // print one digits after dot xx.x (round value by adding 5 hundredth)
        buf.Append( (int) ( tenthSecs / 10 ), 2 )
           .Append( '.' )
           .Append( (int) ( tenthSecs % 10 ), 1 )
           .Append( TimeDiffSecs );
        return;
    }

    //     below 10 mins ?
    if ( tenthSecs < 6000 )
    {
        // convert to hundredth of minutes
        int_fast64_t hundredthMins=  tenthSecs / 6;

        // print two digits after dot x.xx
        buf.Append( (int) (hundredthMins / 100), 1 )
           .Append( '.' )
           .Append( (int) (hundredthMins % 100), 2 )
           .Append( TimeDiffMins );
        return;
    }

    // convert to tenth of minutes
    int_fast64_t tenthMins=  tenthSecs / 60;

    // below 100 mins ?
    if ( tenthMins < 1000 )
    {
        // print one digits after dot xx.x (round value by adding 5 hundredth)
        buf.Append( (int) (tenthMins / 10), 2 )
           .Append( '.' )
           .Append( (int) (tenthMins % 10), 1 )
           .Append( TimeDiffMins );
        return;
    }

    // below ten hours?
    if ( tenthMins < 6000 )
    {
        // convert to hundredth of hours
        int_fast64_t hundredthHours=  tenthMins / 6;

        // print two digits after dot x.xx
        buf.Append( (int) (hundredthHours / 100), 1 )
           .Append( '.' )
           .Append( (int) (hundredthHours % 100), 2 )
           .Append( TimeDiffHours );
        return;
    }

    // convert to tenth of minutes
    int_fast64_t tenthHours=  tenthMins / 60;

    // below 10 hours ?
    if ( tenthHours < 1000 )
    {
        // print two digits after dot x.xx
        buf.Append( (int) (tenthHours / 10), 2 )
           .Append( '.' )
           .Append( (int) (tenthHours % 10), 1 )
           .Append( TimeDiffHours );
        return;
    }

    // below 100 hours ?
    if ( tenthHours < 1000 )
    {
        // print one digits after dot xx.x (round value by adding 5 hundredth)
        buf.Append( (int) (tenthHours / 10), 2 )
           .Append( '.' )
           .Append( (int) ((tenthHours / 10) % 10), 1 )
           .Append( TimeDiffHours );
        return;
    }

    // convert to hundredth of days
    int_fast64_t hundredthDays=  tenthHours * 10 / 24;

    // below 10 days ?
    if ( hundredthDays < 1000 )
    {
        // print two digits after dot x.xx
        buf.Append( (int) (hundredthDays / 100), 1 )
           .Append( '.' )
           .Append( (int) (hundredthDays % 100), 2 )
           .Append( TimeDiffDays );
        return;
    }

    // 10 days or more (print days plus one digit after the comma)
    // print one digits after dot xx.x (round value by adding 5 hundredth)
    buf .Append( (int) (hundredthDays / 100), 2 )
        .Append( '.' )
        .Append( (int) ((hundredthDays / 10) % 10), 1 )
        .Append( TimeDiffDays );
}





// #################################################################################################
// TextLoggerObjectConverter
// #################################################################################################

TextLoggerObjectConverter::TextLoggerObjectConverter()
: buffer( 256 )
{
}

AString& TextLoggerObjectConverter::ConvertObject( const void* o, int typeInfo )
{
    // copy the string into our internal Buffer
    buffer.Clear();
    AString* msg=     &buffer;
         if ( o == nullptr  )
    {
        AString32 text( FmtNullObject );
        AString16 typeNumber;
        typeNumber.Append( typeInfo );
        text.Replace( "%", typeNumber.Buffer() );
        msg->Append( FmtNullObject );
    }
    else if ( typeInfo == 1 )       msg->Append( (const char*)    o );
    else if ( typeInfo == 2 )       msg->Append( (const string*)  o );
    else if ( typeInfo == 3 )       msg->Append( (const AString*) o );

    // default
    else
    {
        AString32 text( FmtUnknownObject );
        AString16 typeNumber;
        typeNumber.Append( typeInfo );
        text.Replace( "%", typeNumber.Buffer() );
        msg->Append( FmtNullObject );
    }

    return *msg;
}

// #################################################################################################
// TextLogger
// #################################################################################################

TextLogger::TextLogger( const char* name )
: Logger( name )
, logBuf( 256 )
,    MultiLineDelimiter(0) // this is similar to nullptr
{
    ObjectConverter= new TextLoggerObjectConverter();
    LineFormatter=   new TextLoggerLineFormatter();
}

TextLogger::~TextLogger()
{
    delete LineFormatter;
    delete ObjectConverter;
}

void TextLogger::doLog( const AString&  domain,     Log::Level    level,
                        const void*     msgObject,  int           typeInfo,
                        int             indent,     CallerInfo*   caller )
{
    // clear Buffer
    logBuf.Clear();

    // process log line format
    LineFormatter->WriteMetaInfo( *this, logBuf, domain, level, indent, caller );

    // convert msg object into a AString representation
    AString& msg=  ObjectConverter->ConvertObject( msgObject, typeInfo );


    // replace strings in message
    for ( int i= 0; i < ((int) Replacements.size()) - 1; i+= 2 )
        msg.Replace( Replacements[i], Replacements[i + 1] );

    // check for empty messages
    if ( msg.Length() == 0 )
    {
        // log empty msg and quit
        doTextLog( domain, level, msg, indent, caller, -1 );
        return;
    }

    // single line output
    if ( MultiLineMsgMode == 0 )
    {
        // replace line separators
        int cntReplacements=0;
        if ( MultiLineDelimiter.GetAllocation() > 0 )
            cntReplacements+=    msg.ReplaceCount( MultiLineDelimiter, MultiLineDelimiterRepl );
        else
        {
            cntReplacements+=    msg.ReplaceCount( "\r\n", MultiLineDelimiterRepl );
            cntReplacements+=    msg.ReplaceCount( "\r", MultiLineDelimiterRepl );
            cntReplacements+=    msg.ReplaceCount( "\n", MultiLineDelimiterRepl );
        }

        // append msg to logBuf
        if ( cntReplacements == 0 )
            logBuf.Append( msg );
        else
        {
            logBuf.Append( FmtMultiLinePrefix );
            logBuf.Append( msg );
            logBuf.Append( FmtMultiLinePostfix );
        }

        // now do the logging by calling our derived classes' doTextLog
        doTextLog( domain, level, logBuf, indent, caller, -1 );

        // stop here
        return;
    }

    // multiple line output
    int actStart=0;
    int lineNo=0;
    int lbLenBeforeMsgPart=logBuf.Length();

    // loop over lines in msg
    while ( actStart < msg.Length() )
    {
        // find next end
        int delimLen;
        int actEnd;

        // no delimiter given: search "\r\n", then '\r', then '\n'
        if ( MultiLineDelimiter.Length() == 0 )
        {
            delimLen=2;
            actEnd=msg.IndexOf( "\r\n", actStart );
            if ( actEnd < 0 )
            {
                delimLen=1;
                actEnd=msg.IndexOf( "\r", actStart );

                if ( actEnd < 0 )
                    actEnd=msg.IndexOf( "\n", actStart );
            }
        }
        else
        {
            delimLen=  MultiLineDelimiter.Length();
            actEnd=    msg.IndexOf( MultiLineDelimiter, actStart );
        }

        // not found a delimiter? - log the rest
        if ( actEnd < 0 )
        {
            // single line?
            if ( lineNo == 0 )
            {
                // append msg to logBuf
                logBuf.Append( msg );

                // now do the logging by calling our derived classes' doLog
                doTextLog( domain, level, logBuf, indent, caller, -1 );

                // stop here
                return;
            }

            // store actual end
            actEnd=msg.Length();
        }

        // found a delimiter

        // signal start of multi line log
        if ( lineNo == 0 )
            notifyMultiLineOp( true );

        // in mode 3, 4, when meta info is deleted, we log a separate line first!
        if ( lineNo == 0 && ( MultiLineMsgMode == 3 || MultiLineMsgMode == 4 ) )
        {
            // log headline
            if ( MultiLineMsgMode == 3 )
            {
                logBuf.Append( FmtMultiLineMsgHeadline );
                doTextLog( domain, level, logBuf, indent, caller, 0 );
            }

            // remember zero as offset
            lbLenBeforeMsgPart=0;
        }

        // blank out meta information? (do this exactly in 2nd line once)
        if ( lineNo == 1 && MultiLineMsgMode == 2 )
            logBuf.Fill(' ', 0, lbLenBeforeMsgPart );

        // reset logBuf length to marked position
        logBuf.SetLength( lbLenBeforeMsgPart );

        // append message
        logBuf.Append( FmtMultiLinePrefix );
          logBuf.Append( msg, actStart, actEnd - actStart  );
        logBuf.Append( FmtMultiLinePostfix );

        // now do the logging by calling our derived classes' doLog
        doTextLog( domain, level, logBuf, indent, MultiLineMsgMode != 4 ? caller : nullptr, lineNo );

        // next
        actStart= actEnd + delimLen;
        lineNo++;
    }

    // signal end of multi line log
    if ( lineNo > 0 )
        notifyMultiLineOp( false );
}

