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
#if !defined (HPP_ALIB_SYSTEM_SYSTEM)
    #include "alib/system/system.hpp"
#endif
#if !defined (HPP_ALOX_CORE_TEXTLOGGER_TEXTLOGGER)
    #include "textlogger.hpp"
#endif

#if !defined (HPP_ALIB_COMPATIBILITY_STD_STRING)
    #include "alib/compatibility/std_string.hpp"
#endif
#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif
#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif

using namespace std;

// For code compatibility with ALox Java/C++
#define _NC _<false>


namespace aworx { namespace lox { namespace core { namespace textlogger {

// #################################################################################################
// StringConverter
// #################################################################################################
StringConverter::StringConverter()
{
}

bool StringConverter::ConvertObject( const Logable& logable, AString& target )
{
    if ( logable.Type == 0 || logable.Type == -1 )
    {
        if ( logable.Object != nullptr && ((const TString*) logable.Object)->IsNotNull()  )
            target._NC( (const TString*) logable.Object );
        else
            target._NC( FmtNullObject );
        return true;
    }

    return false;
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

    // increase auto tab index
    ActualIndex++;

    return size;
}

void    AutoSizes::Export( AString& target  )
{
    for( size_t i= 0; i < values.size() ; i++ )
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
int MetaInfo::Write( TextLogger& logger, AString& buf, core::Domain& domain, Verbosity verbosity, ScopeInfo& scope )
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
            qtyTabStops+= processVariable( logger, domain, verbosity, scope, buf, format );
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
                               core::Domain&      domain,
                               Verbosity          verbosity,
                               ScopeInfo&         scope,
                               AString&           dest,
                               Substring&         variable       )

{
    // process commands
    char c2;
    switch ( variable.Consume() )
    {
        // scope info
        case 'S':
        {
            // read sub command
            String val;
            switch( c2= variable.Consume() )
            {
                case 'P':   // SP: full path
                {
                    val= scope.GetFullPath();
                    if ( val.IsEmpty() )
                        val= NoSourceFileInfo;
                } break;

                case 'p':   // Sp: trimmed path
                {
                    val= scope.GetTrimmedPath();
                    if ( val.IsEmpty() )
                        val= NoSourceFileInfo;
                } break;

                case 'F':   // file name
                {
                    val= scope.GetFileName();
                    if ( val.IsEmpty() )
                        val= NoSourceFileInfo;
                } break;

                case 'f':   // file name without extension
                {
                    val= scope.GetFileNameWithoutExtension();
                    if ( val.IsEmpty() )
                        val= NoSourceFileInfo;
                } break;


                case 'M':   // method name
                {
                    val= scope.GetMethod();
                    if ( val.IsEmpty() )
                        val= NoMethodInfo;
                } break;

                case 'L':  // line number
                {
                    dest._NC( scope.GetLineNumber() );
                    return 0;
                }

                default:
                {
                    ALIB_WARN_ONCE( String64( "Unknown format variable '%S" ) <<  c2 << "\' (only one warning)",
                                    *this, FormatWarning);
                    val= "%ERROR";
                } break;
            }
            dest._( val );
            return 0;
        }

        // %Tx: Time
        case 'T':
        {
            c2= variable.Consume();

            // %TD: Date
            if ( c2 == 'D' )
            {
                // get time stamp as TicksCalendarTime once
                if ( callerDateTime.Year == (numeric_limits<int>::min)() )
                    callerDateTime.Set( scope.GetTimeStamp() );

                // if standard format, just write it out
                if ( DateFormat.Equals( "yyyy-MM-dd" ) )
                {
                    dest._NC( Format::Int32( callerDateTime.Year,     4 ) )._NC( '-' )
                        ._NC( Format::Int32( callerDateTime.Month,    2 ) )._NC( '-' )
                        ._NC( Format::Int32( callerDateTime.Day,      2 ) );
                }
                // user defined format
                else
                    callerDateTime.Format( DateFormat, dest  );

                return 0;
            }


            // %TT: Time of Day
            if ( c2 == 'T' )
            {
                // get time stamp as TicksCalendarTime once
                if ( callerDateTime.Year == (numeric_limits<int>::min)() )
                    callerDateTime.Set( scope.GetTimeStamp() );

                // avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!)
                // and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
                if ( TimeOfDayFormat.Equals( "HH:mm:ss" ) )
                {
                    dest ._NC( Format::Int32(callerDateTime.Hour,    2) )._NC( ':' )
                        ._NC( Format::Int32(callerDateTime.Minute,  2) )._NC( ':' )
                        ._NC( Format::Int32(callerDateTime.Second,  2) );
                }

                // user defined format
                else
                    callerDateTime.Format( TimeOfDayFormat, dest  );
            }

            // %TC: Time elapsed since created
            else if ( c2 == 'C' )
            {
                TickSpan elapsed( scope.GetTimeStamp(), logger.TimeOfCreation );

                if ( elapsed.Days  > 0 )    dest._NC( elapsed.Days  )._NC( TimeElapsedDays );
                if ( elapsed.Hours > 0 )    dest._NC( elapsed.Hours )._NC( ':' );

                dest._NC( Format::Int32(elapsed.Minutes,       2) )._NC( ':' )
                   ._NC( Format::Int32(elapsed.Seconds,       2) )._NC( '.' )
                   ._NC( Format::Int32(elapsed.Milliseconds,  3) );
            }

            // %TL: Time elapsed since last log call
            else if ( c2 == 'L' )
                writeTimeDiff( dest, scope.GetTimeStamp().Since( logger.TimeOfLastLog ).InNanos() );

            else
            {
                ALIB_WARN_ONCE( String64( "Unknown format variable '%T" ) <<  c2 << "\' (only one warning)",
                               *this, FormatWarning );
            }
            return 0;
        }


        // Thread
        case 't':
        {
            c2= variable.Consume();

            if ( c2 == 'N' )        // %tN: thread name
            {
                const String& threadName= scope.GetThreadNameAndID(nullptr);
                dest._NC( Format::Field( threadName, logger.AutoSizes.Next( threadName.Length(), 0 ), Alignment::Center ) );
            }
            else if ( c2 == 'I' )   // %tI: thread ID
            {
                String32 threadID; threadID._( scope.GetThreadID() );
                dest._NC( Format::Field( threadID,   logger.AutoSizes.Next( threadID  .Length(), 0 ), Alignment::Center ) );
            }
            else
            {
                ALIB_WARN_ONCE( String64( "Unknown format variable '%t" ) <<  c2 << "\' (only one warning)",
                               *this, FormatWarning );
            }
            return 0;
        }

        case 'L':
        {
            c2= variable.Consume();
                 if ( c2 == 'G' )     dest._NC( logger.GetName() );
            else if ( c2 == 'X' )     dest._NC( scope.GetLoxName() );
            else
            {
                ALIB_WARN_ONCE( String64( "Unknown format variable '%L" ) <<  c2 << "\' (only one warning)",
                               *this, FormatWarning );
            }
            return 0;
        }

        case 'P':
        {
            dest._NC( System::GetProcessName() );
            return 0;
        }

        case 'V':
            dest._NC(  verbosity == Verbosity::Error     ? VerbosityError
                     : verbosity == Verbosity::Warning   ? VerbosityWarning
                     : verbosity == Verbosity::Info      ? VerbosityInfo
                     :                                     VerbosityVerbose    );
            return 0;

        case 'D':
        {
            dest._( Format::Field( domain.FullPath, logger.AutoSizes.Next( domain.FullPath.Length(), 0 ), Alignment::Left ) );
            return 0;
        }

        case '#':

            dest._NC( Format::Int32( logger.CntLogs, LogNumberMinDigits ) );
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

            dest._NC( escseq );
            return 1;
        }

        case 'N':
            dest._NC( logger.GetName() );
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

TextLogger::TextLogger( const String& name, const String& typeName, bool  usesStdStreams  )
: Logger( name, typeName )
, logBuf( 256 )
, msgBuf( 256 )
, usesStdStreams( usesStdStreams )
{
    ObjectConverters.emplace_back(  new textlogger::StringConverter() );
    MetaInfo=        new textlogger::MetaInfo();

    // evaluate config variable <name>_FORMAT / <typeName>_FORMAT
    {
        String64    variableName( name ); variableName._( "_FORMAT" );
        String128   result;
        if ( ALIB::Config.Get( ALox::ConfigCategoryName, variableName, result ) == 0 )
        {
            variableName._()._( typeName )._( "_FORMAT" );
            ALIB::Config.Get( ALox::ConfigCategoryName, variableName, result );
        }

        if( result.IsNotEmpty() )
            MetaInfo->Format._()._( result );
    }

}

TextLogger::~TextLogger()
{
    delete MetaInfo;
    for( auto it : ObjectConverters )
        delete it;
}

int   TextLogger::AddAcquirer( ThreadLock* newAcquirer )
{
    // register with ALIB lockers (if not done yet)
    if ( usesStdStreams )
    {
        int stdStreamLockRegistrationCounter;
        {
            OWN( ALIB::Lock );
            stdStreamLockRegistrationCounter= this->stdStreamLockRegistrationCounter++;
        }
        if ( stdStreamLockRegistrationCounter == 0 )
             ALIB::StdOutputStreamsLock.AddAcquirer( this );
    }

    // import autosizes from configuration
    {
        // get auto sizes from last session
        String64 autoSizes;
        String64 variableName( name ); variableName._( "_AUTO_SIZES" );
        if( ALIB::Config.Get( ALox::ConfigCategoryName, variableName, autoSizes ) != 0 )
            AutoSizes.Import( Substring(autoSizes) );
    }

    // call parents' implementation
    return Logger::AddAcquirer( newAcquirer );
}

int   TextLogger::RemoveAcquirer( ThreadLock* acquirer )
{
    // de-register with ALIB lockers (if not done yet)
    if ( usesStdStreams )
    {
        int stdStreamLockRegistrationCounter;
        {
            OWN( ALIB::Lock );
            stdStreamLockRegistrationCounter= --this->stdStreamLockRegistrationCounter;
        }

        if ( stdStreamLockRegistrationCounter == 0 )
            ALIB::StdOutputStreamsLock.RemoveAcquirer( this );
    }

    // export autosizes to configuration
    {
        String64 autoSizes;
        String64 variableName( name ); variableName._( "_AUTO_SIZES" );
        AutoSizes.Export( autoSizes );
        ALIB::Config.Save( ALox::ConfigCategoryName, variableName, autoSizes,
                            "Auto size values of last run" );
    }


    // call parents' implementation
    return Logger::RemoveAcquirer( acquirer );
}


void TextLogger::SetReplacement( const String& searched, const String& replacement )
{
    // if exists, replace replacement
    for( auto it= replacements.begin(); it < replacements.end(); it+= 2)
        if ( it->Equals( searched ) )
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
// TextLogger::Log()
// #################################################################################################
void TextLogger::Log( Domain& domain, Verbosity verbosity, Logables& logables, ScopeInfo& scope)
{
    // clear Buffers
    logBuf.Clear();

    AutoSizes.Start();

    // meta info << ESC::EOMETA
    int qtyESCTabsWritten= MetaInfo->Write( *this, logBuf, domain, verbosity, scope );
    logBuf._NC( ESC::EOMETA );

    // convert msg object into an AString representation
    msgBuf._();
    for( Logable* logable : logables )
    {
        auto it = ObjectConverters.rbegin();
        for( ; it != ObjectConverters.rend() ; it++ )
            if ( (*it)->ConvertObject( *logable, msgBuf ) )
                break;
        if ( it == ObjectConverters.rend() )
        {
            String128 text( FmtUnknownObject );
            text.SearchAndReplace( "%", String32( logable->Type) );
            msgBuf._NC( text );
        }
    }

    // replace strings in message
    for ( int i= 0; i < ((int) replacements.size()) - 1; i+= 2 )
        msgBuf.SearchAndReplace( replacements[i], replacements[i + 1] );

    // check for empty messages
    if ( msgBuf.IsEmpty() )
    {
        // log empty msg and quit
        if (usesStdStreams) ALIB::StdOutputStreamsLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
            logText( domain, verbosity, logBuf, scope, -1 );
        if (usesStdStreams) ALIB::StdOutputStreamsLock.Release();
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

        // now do the logging by calling our derived classes' logText
        if (usesStdStreams) ALIB::StdOutputStreamsLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
            logText( domain, verbosity, logBuf, scope, -1 );
        if (usesStdStreams) ALIB::StdOutputStreamsLock.Release();

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
                if (usesStdStreams) ALIB::StdOutputStreamsLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
                    logText( domain, verbosity, logBuf, scope, -1 );
                if (usesStdStreams) ALIB::StdOutputStreamsLock.Release();
                // stop here
                return;
            }

            // store actual end
            actEnd= msgBuf.Length();
        }

        // found a delimiter

        // signal start of multi line log
        if ( lineNo == 0 )
        {
            if (usesStdStreams) ALIB::StdOutputStreamsLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
            notifyMultiLineOp( Phase::Begin );
        }

        // in mode 3, 4, meta info is deleted
        if ( lineNo == 0 && ( MultiLineMsgMode == 3 || MultiLineMsgMode == 4 ) )
        {
            // log headline in mode 3
            if ( MultiLineMsgMode == 3 )
            {
                logBuf._NC( FmtMultiLineMsgHeadline );
                AutoSizes.ActualIndex=  qtyTabStops;
                logText( domain, verbosity, logBuf, scope, 0 );
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
        logText( domain, verbosity, logBuf, scope, lineNo );

        // next
        actStart= actEnd + delimLen;
        lineNo++;
    }

    // signal end of multi line log
    if ( lineNo > 0 )
    {
        notifyMultiLineOp( Phase::End );
        if (usesStdStreams) ALIB::StdOutputStreamsLock.Release();
    }
}

}}}}//namespace aworx::lox::core::textlogger

