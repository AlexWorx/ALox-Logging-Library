// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#if !defined (HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif
#if !defined (HPP_ALIB_SYSTEM_DIRECTORY)
    #include "alib/system/directory.hpp"
#endif


#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

#include "textlogger.hpp"

#include "alib/compatibility/std_string.hpp"
#include "alib/strings/numberformat.hpp"

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif

using namespace std;

// For code compatibility with ALox Java/C++
#define _NC _<false>


namespace aworx { namespace lox { namespace core { namespace textlogger {

// #################################################################################################
// ObjectConverter
// #################################################################################################
ObjectConverter::ObjectConverter()
{
}

bool ObjectConverter::ConvertObject( const void* o, int typeInfo, AString& result )
{
    // copy the string into our internal Buffer
    if ( o == nullptr  )
    {
        String128 text( FmtNullObject );
        text.SearchAndReplace( "%", String32(typeInfo) );
        result._NC( FmtNullObject );
    }

    else if ( typeInfo == 0 )       result._( (const TString*)    o );

    // default
    else
    {
        String128 text( FmtUnknownObject );
        text.SearchAndReplace( "%", String32(typeInfo) );
        result._NC( text );
        return false;
    }
    return true;
}

// #################################################################################################
// TextLoggerAutoTab
// #################################################################################################

int     AutoSizes::Next( int requestedSize, int extraGrowth )
{
    // grow arrays as needed
    if ( (int) values.size() == ActualIndex )
    {
        values          .emplace_back( 0 );
        sessionValues   .emplace_back( 0 );
    }

    // get size as it would be for this session (for saving the session later)
    int size=    sessionValues[ ActualIndex ];
    if ( size <  requestedSize )
        sessionValues[ ActualIndex ]=  requestedSize + ( size == 0 ? 0 : extraGrowth );


    // get size as it is for actual values (the ones that might have been imported)
    size=    values[ ActualIndex ];
    if ( size <  requestedSize )
    {
        size=
        values[ ActualIndex ]=        requestedSize + ( size == 0 ? 0 : extraGrowth );
    }

    // increase auto tab index for next 'A' command
    ActualIndex++;

    return size;
}

void    AutoSizes::Export( AString& target  )
{

    for( unsigned int i= 0; i < values.size() ; i++ )
    {
        if ( i != 0 )
            target._( ' ' );
        target._(        values[ i ] );
        target._( ' ' );
        target._( sessionValues[ i ] );
    }
    while( target.EndsWith(" 0 0" ) )
        target.DeleteEnd<false>(4);
}

void    AutoSizes::Import( const String& sourceString, CurrentData session  )
{
    Substring source(sourceString);
    Reset();
    for(;;)
    {
        int origLength=     source.Length();
        int value;          source.ConsumeInteger( value       );
        int sessionValue;   source.ConsumeInteger( sessionValue );

        if ( origLength == source.Length() )
            break;

        values       .emplace_back( session == CurrentData::Clear ? sessionValue : value       );
        sessionValues.emplace_back( session == CurrentData::Clear ? 0            : sessionValue );
    }
}



// #################################################################################################
// MetaInfo
// #################################################################################################
int MetaInfo::Write( TextLogger& logger, AString& buf, const TString& domain, Log::Level level, CallerInfo* caller )
{
    int qtyTabStops= 0;

    // check
    if ( Format.IsEmpty() )
        return 0;

    // clear DateTime singleton
    callerDateTime.Year= (numeric_limits<int>::min)();

    Substring format( Format );
    for(;;)
    {
        // get next and log substring between commands
        int idx= format.IndexOf( '%' );
        if ( idx >= 0 )
        {
            format.Consume<false>( idx, buf, 1, CurrentData::Keep );
            qtyTabStops+= processVariable( logger, domain, level, caller, buf, format );
        }
        else
        {
            buf._NC( format );
            break;
        }
    }
    return qtyTabStops;
}

int MetaInfo::processVariable( TextLogger&        logger,
                               const TString&     domain,
                               Log::Level         level,
                               CallerInfo*        caller,
                               AString&           buf,
                               Substring&         variable       )

{
    // process commands
    switch ( variable.Consume() )
    {
        // caller info
        case 'C':
        {
            // read sub command
            char s= variable.Consume();

            // add source file including path
            if ( s == 'F' )
            {
                const TString& sourceFileName=  caller->SourceFileName;
                if ( sourceFileName.IsNotNull() )
                {
                    // detect cutable prefix from the file name path and current working directory
                    // Note: we do this only once. And we do not use the prefix here
                    //       This is up to the derived logger to do so.
                    if ( ConsumableSourcePathPrefix.IsNull() )
                    {
                        // get system execution path and compare to file path
                        String256 currentDir;
                        ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( currentDir,  ReplaceExternalBuffer );

                        Directory::CurrentDirectory( currentDir );
                        sourceFileName.Terminate();
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
                            ConsumableSourcePathPrefix._NC( currentDir, 0, i );
                            #if defined ( _MSC_VER ) // MS Compiler delivers __FILE__ in lower case
                                ConsumableSourcePathPrefix.ToLower();
                            #endif
                        }
                        else
                            ConsumableSourcePathPrefix= ""; // mark as not null
                    }

                    // can we cut the source file name by a prefix?
                    int appendStart= sourceFileName.StartsWith( ConsumableSourcePathPrefix )
                                     ? ConsumableSourcePathPrefix.Length()
                                     : 0;

                    buf._NC( sourceFileName, appendStart, sourceFileName.Length() - appendStart );
                }
                else
                    buf._NC( NoSourceFileInfo );
            }

            // add source file excluding path
            else if ( s == 'f' )
            {
                const String& sourceFileName=   caller->SourceFileName;
                if ( sourceFileName.IsNotNull() )
                {
                    int appendStart=  sourceFileName.LastIndexOf( PathSeparator ) + 1;
                    buf._NC( sourceFileName, appendStart, sourceFileName.Length() - appendStart );
                }
                else
                    buf._NC( NoSourceFileInfo );
            }

            // add line number or method name
            else if ( s == 'L' )  buf._  ( caller->LineNumber );
            else if ( s == 'M' )  buf._NC( caller->MethodName.IsNotNull() ? caller->MethodName : NoMethodInfo );
            else
            {
                ALIB_WARN_ONCE( String64( "Unknown format character 'C" ) <<  s << "\' (only one warning)",
                                *this, FormatWarning);
            }

            return 0;
        }

        // Date
        case 'D':
        {
            // get time stamp as TicksCalendarTime once
            if ( callerDateTime.Year == (numeric_limits<int>::min)() )
                callerDateTime.Set( caller->TimeStamp );

            // if standard format, just write it out
            if ( DateFormat.Equals( "yyyy-MM-dd" ) )
            {
                buf._NC( Format::Int32( callerDateTime.Year,     4 ) )._NC( '-' )
                   ._NC( Format::Int32( callerDateTime.Month,    2 ) )._NC( '-' )
                   ._NC( Format::Int32( callerDateTime.Day,      2 ) );
            }
            // user defined format
            else
                callerDateTime.Format( DateFormat, buf  );

            return 0;
        }

        // %Tx: Time
        case 'T':
        {
            // read sub command
            char s= variable.Consume();

            // %TD: Time of Day
            if ( s == 'D' )
            {
                // get time stamp as TicksCalendarTime once
                if ( callerDateTime.Year == (numeric_limits<int>::min)() )
                    callerDateTime.Set( caller->TimeStamp );

                // avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!)
                // and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
                if ( TimeOfDayFormat.Equals( "HH:mm:ss" ) )
                {
                    buf ._NC( Format::Int32(callerDateTime.Hour,    2) )._NC( ':' )
                        ._NC( Format::Int32(callerDateTime.Minute,  2) )._NC( ':' )
                        ._NC( Format::Int32(callerDateTime.Second,  2) );
                }

                // user defined format
                else
                    callerDateTime.Format( TimeOfDayFormat, buf  );
            }

            // %TE: Time Elapsed
            else if ( s == 'E' )
            {
                TickSpan elapsed( caller->TimeStamp, logger.TimeOfCreation );

                if ( elapsed.Days  > 0 )    buf._NC( elapsed.Days  )._NC( TimeElapsedDays );
                if ( elapsed.Hours > 0 )    buf._NC( elapsed.Hours )._NC( ':' );

                buf._NC( Format::Int32(elapsed.Minutes,       2) )._NC( ':' )
                   ._NC( Format::Int32(elapsed.Seconds,       2) )._NC( '.' )
                   ._NC( Format::Int32(elapsed.Milliseconds,  3) );
            }

            // %TE: Time Diff
            else
            {
                writeTimeDiff( buf, caller->TimeStamp.Since( logger.TimeOfLastLog ).InNanos() );
            }
            return 0;
        }


        // Thread
        case 't':
        {
            #if defined(ALIB_FEAT_THREADS)
                const String& threadName= caller->getThreadNameAndID(nullptr);
                buf._NC( Format::Field( threadName, logger.AutoSizes.Next( threadName.Length(), 0 ), Alignment::Center ) );
            #endif
            return 0;
        }

        case 'L':
            buf._NC(   level == Log::Level::Error     ? LogLevelError
                     : level == Log::Level::Warning   ? LogLevelWarning
                     : level == Log::Level::Info      ? LogLevelInfo
                     :                                  LogLevelVerbose    );
            return 0;

        case 'O':
            // If no domain logged yet and domain name is empty, we omit it
            buf._( Format::Field( domain, logger.AutoSizes.Next( domain.Length(), 0 ), Alignment::Center ) );
            return 0;

        case '#':

            buf._NC( Format::Int32( logger.CntLogs, LogNumberMinDigits ) );
            return 0;

        // A: Auto tab
        case 'A':
        {
            // read extra space from format string
            int idx= 0;
            int extraSpace= (int) NumberFormat::Global.StringToInteger( variable, idx );
            if (idx == 0 )
                extraSpace=   1;
            else
                variable.Consume(idx);

            // insert ESC code to jump to next tab level
            extraSpace= min( extraSpace, 10 + ('Z'-'A') );
            char escseq[4]= {'\x1B', 't' }; // 3 + one (unused termination character)
            escseq[2]= extraSpace < 10 ?   (char) ('0' + extraSpace )
                                       :   (char) ('A' + extraSpace );

            buf._NC( escseq );
            return 1;
        }

        case 'N':
            buf._NC( logger.Name );
            return 0;

        default:
            ALIB_WARN_ONCE( String64( "Unknown format character \'" ) << *( variable.Buffer() -1 )
                                   << "\' (only one warning)",
                            *this, FormatWarning );
            return 0;
   }// switch
}

void MetaInfo::writeTimeDiff( AString& buf, int_fast64_t diffNanos )
{
    // unmeasurable?
    if ( diffNanos < TimeDiffMinimum )
    {
        buf._NC( TimeDiffNone );
        return;
    }

    if ( diffNanos < 1000 )
    {
        buf._NC( Format::Int32( (int) diffNanos, 3 ) )._NC( TimeDiffNanos );
        return;
    }

    // we continue with micros
    int_fast64_t diffMicros= diffNanos / 1000L;

    // below 1000 microseconds?
    if ( diffMicros < 1000 )
    {
        buf._NC( Format::Int32( (int) diffMicros, 3 ) );
        buf._NC( TimeDiffMicros );
        return;
    }

    // below 1000 ms?
    if ( diffMicros < 1000000 )
    {
        buf._NC( Format::Int32( (int) (diffMicros / 1000), 3 ) )._NC( TimeDiffMillis );
        return;
    }


    // below 10 secs (rounded) ?
    if ( diffMicros < 9995000 )
    {
        // convert to hundredth of secs
        int_fast64_t hundredthSecs=  ((diffMicros / 1000) + 5) / 10;

        // print two digits after dot x.xx
        buf._NC( Format::Int32( (int) (hundredthSecs / 100), 1 ) )
           ._NC( '.' )
           ._NC( Format::Int32( (int) (hundredthSecs % 100), 2 ) )
           ._NC( TimeDiffSecs );
        return;
    }

    // convert to tenth of secs
    int_fast64_t tenthSecs=  ((diffMicros / 10000) + 5) / 10 ;

    // below 100 secs ?
    if ( tenthSecs < 1000 )
    {
        // print one digits after dot xx.x (round value by adding 5 hundredth)
        buf._NC( Format::Int32( (int) ( tenthSecs / 10 ), 2 ) )
           ._NC( '.' )
           ._NC( Format::Int32( (int) ( tenthSecs % 10 ), 1 ) )
           ._NC( TimeDiffSecs );
        return;
    }

    //     below 10 mins ?
    if ( tenthSecs < 6000 )
    {
        // convert to hundredth of minutes
        int_fast64_t hundredthMins=  tenthSecs / 6;

        // print two digits after dot x.xx
        buf._NC( Format::Int32( (int) (hundredthMins / 100), 1 ) )
           ._NC( '.' )
           ._NC( Format::Int32( (int) (hundredthMins % 100), 2 ) )
           ._NC( TimeDiffMins );
        return;
    }

    // convert to tenth of minutes
    int_fast64_t tenthMins=  tenthSecs / 60;

    // below 100 mins ?
    if ( tenthMins < 1000 )
    {
        // print one digits after dot xx.x (round value by adding 5 hundredth)
        buf._NC( Format::Int32( (int) (tenthMins / 10), 2 ) )
           ._NC( '.' )
           ._NC( Format::Int32( (int) (tenthMins % 10), 1 ) )
           ._NC( TimeDiffMins );
        return;
    }

    // below ten hours?
    if ( tenthMins < 6000 )
    {
        // convert to hundredth of hours
        int_fast64_t hundredthHours=  tenthMins / 6;

        // print two digits after dot x.xx
        buf._NC( Format::Int32( (int) (hundredthHours / 100), 1 ) )
           ._NC( '.' )
           ._NC( Format::Int32( (int) (hundredthHours % 100), 2 ))
           ._NC( TimeDiffHours );
        return;
    }

    // convert to tenth of minutes
    int_fast64_t tenthHours=  tenthMins / 60;

    // below 10 hours ?
    if ( tenthHours < 1000 )
    {
        // print two digits after dot x.xx
        buf._NC( Format::Int32( (int) (tenthHours / 10), 2 ) )
           ._NC( '.' )
           ._NC( Format::Int32( (int) (tenthHours % 10), 1 ) )
           ._NC( TimeDiffHours );
        return;
    }

    // below 100 hours ?
    if ( tenthHours < 1000 )
    {
        // print one digits after dot xx.x (round value by adding 5 hundredth)
        buf._NC( Format::Int32( (int) (tenthHours / 10), 2 ) )
           ._NC( '.' )
           ._NC( Format::Int32( (int) ((tenthHours / 10) % 10), 1 ) )
           ._NC( TimeDiffHours );
        return;
    }

    // convert to hundredth of days
    int_fast64_t hundredthDays=  tenthHours * 10 / 24;

    // below 10 days ?
    if ( hundredthDays < 1000 )
    {
        // print two digits after dot x.xx
        buf._NC( Format::Int32( (int) (hundredthDays / 100), 1 ) )
           ._NC( '.' )
           ._NC( Format::Int32( (int) (hundredthDays % 100), 2 ) )
           ._NC( TimeDiffDays );
        return;
    }

    // 10 days or more (print days plus one digit after the comma)
    // print one digits after dot xx.x (round value by adding 5 hundredth)
    buf ._NC( Format::Int32( (int) (hundredthDays / 100), 2 ) )
        ._NC( '.' )
        ._NC( Format::Int32( (int) ((hundredthDays / 10) % 10), 1 ) )
        ._NC( TimeDiffDays );
}


// #################################################################################################
// TextLogger
// #################################################################################################

TextLogger::TextLogger( const String& name, const String& typeName )
: Logger( name, typeName )
, logBuf( 256 )
, msgBuf( 256 )
{
    ObjectConverter= new textlogger::ObjectConverter();
    MetaInfo=        new textlogger::MetaInfo();
}

TextLogger::~TextLogger()
{
    delete MetaInfo;
    delete ObjectConverter;
}

void TextLogger::SetReplacement( const String& searched, const String& replacement )
{
    // if exists, replace replacement
    for( auto it= replacements.begin(); it < replacements.end(); it+= 2)
        if ( (*it).Equals( searched ) )
        {
            if ( replacement.IsNotNull() )
            {
                it++;
                *it= replacement;
                return;
            }
            else
            {
                replacements.erase( it );
                replacements.erase( it );
                return;
            }
        }

    // append at the end
    if ( replacement != nullptr )
    {
        replacements.insert( replacements.end(), AString(searched   ) );
        replacements.insert( replacements.end(), AString(replacement) );
    }
}

void TextLogger::ClearReplacements()
{
    replacements.clear();
}


// #################################################################################################
// TextLogger::doLog()
// #################################################################################################
void TextLogger::doLog( const TString&  domain,     Log::Level    level,
                        const void*     msgObject,  int           typeInfo,
                        int             indent,     CallerInfo*   caller )
{
    // clear Buffers
    logBuf.Clear();
    msgBuf.Clear();

    AutoSizes.Start();

    // meta info << ESC::EOMETA << indent
    int qtyESCTabsWritten= MetaInfo->Write( *this, logBuf, domain, level, caller );


    logBuf._NC( ESC::EOMETA );

    for (int i= indent; i > 0 ; i--)
        logBuf._NC( FmtIndentString );

    // convert msg object into a AString representation

    ObjectConverter->ConvertObject( msgObject, typeInfo, msgBuf );

    // replace strings in message
    for ( int i= 0; i < ((int) replacements.size()) - 1; i+= 2 )
        msgBuf.SearchAndReplace( replacements[i], replacements[i + 1] );

    // check for empty messages
    if ( msgBuf.IsEmpty() )
    {
        // log empty msg and quit
        doTextLog( domain, level, logBuf, indent, caller, -1 );
        return;
    }

    // single line output
    if ( MultiLineMsgMode == 0 )
    {
        // replace line separators
        int cntReplacements=0;
        if ( MultiLineDelimiter.IsNotNull() )
            cntReplacements+=    msgBuf.SearchAndReplace( MultiLineDelimiter, MultiLineDelimiterRepl );
        else
        {
            // explicit cast terminates AString
            String& replacement= MultiLineDelimiterRepl;
            cntReplacements+=    msgBuf.SearchAndReplace( "\r\n", replacement );
            cntReplacements+=    msgBuf.SearchAndReplace( "\r",   replacement );
            cntReplacements+=    msgBuf.SearchAndReplace( "\n",   replacement );
        }

        // append msg to logBuf
        if ( cntReplacements == 0 )
        {
            logBuf._NC( msgBuf );
        }
        else
        {
            logBuf._NC( FmtMultiLinePrefix );
            logBuf._NC( msgBuf );
            logBuf._NC( FmtMultiLineSuffix );
        }

        // now do the logging by calling our derived classes' doTextLog
        doTextLog( domain, level, logBuf, indent, caller, -1 );

        // stop here
        return;
    }

    // multiple line output
    int qtyTabStops= AutoSizes.ActualIndex;
    int actStart=0;
    int lineNo=0;
    int lbLenBeforeMsgPart=logBuf.Length();

    // loop over lines in msg
    while ( actStart < msgBuf.Length() )
    {
        // find next end
        int delimLen;
        int actEnd;

        // no delimiter given: search '\n' and then see if it is "\r\n" in fact
        if ( MultiLineDelimiter.IsEmpty() )
        {
            delimLen= 1;
            actEnd= msgBuf.IndexOf<false>( '\n', actStart );
            if( actEnd > actStart )
            {
                if( msgBuf.CharAt<false>(actEnd - 1) == '\r' )
                {
                    actEnd--;
                    delimLen= 2;
                }
            }
        }
        else
        {
            delimLen=  MultiLineDelimiter.Length();
            actEnd=    msgBuf.IndexOf<false>( MultiLineDelimiter, actStart );
        }

        // not found a delimiter? - log the rest
        if ( actEnd < 0 )
        {
            // single line?
            if ( lineNo == 0 )
            {
                logBuf._NC( msgBuf );
                doTextLog( domain, level, logBuf, indent, caller, -1 );

                // stop here
                return;
            }

            // store actual end
            actEnd= msgBuf.Length();
        }

        // found a delimiter

        // signal start of multi line log
        if ( lineNo == 0 )
            notifyMultiLineOp( Phase::Begin );

        // in mode 3, 4, meta info is deleted
        if ( lineNo == 0 && ( MultiLineMsgMode == 3 || MultiLineMsgMode == 4 ) )
        {
            // log headline in mode 3
            if ( MultiLineMsgMode == 3 )
            {
                logBuf._NC( FmtMultiLineMsgHeadline );
                AutoSizes.ActualIndex=  qtyTabStops;
                doTextLog( domain, level, logBuf, indent, caller, 0 );
            }

            // remember zero as offset
            lbLenBeforeMsgPart=0;
        }

        // clear meta information?
        if ( MultiLineMsgMode == 2 )
        {
            if (lineNo != 0 )
            {
                logBuf.Clear()._( ESC::EOMETA );
                AutoSizes.ActualIndex=  qtyTabStops + qtyESCTabsWritten;
            }
        }
        // reset logBuf length to marked position
        else
        {
            logBuf.SetLength<false>( lbLenBeforeMsgPart );
            AutoSizes.ActualIndex=  qtyTabStops;
        }

        // append message and do the log
        logBuf._NC( FmtMultiLinePrefix );
          logBuf._NC( msgBuf,  actStart, actEnd - actStart  );
        logBuf._NC( FmtMultiLineSuffix );
        doTextLog( domain, level, logBuf, indent, MultiLineMsgMode != 4 ? caller : nullptr, lineNo );

        // next
        actStart= actEnd + delimLen;
        lineNo++;
    }

    // signal end of multi line log
    if ( lineNo > 0 )
        notifyMultiLineOp( Phase::End );
}

}}}}//namespace aworx::lox::core::textlogger

