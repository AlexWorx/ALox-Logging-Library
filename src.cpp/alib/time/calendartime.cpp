// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

#include "alib/alib.hpp"

#if !defined (HPP_ALIB_TIME_CALENDARTIME)
    #include "alib/time/calendartime.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_SUBSTRING)
    #include "alib/strings/substring.hpp"
#endif
#if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif

// For code compatibility with ALox Java/C++
// We have to use underscore as the start of the name and for this have to disable a compiler
// warning. But this is a local code (cpp file) anyhow.
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif

    #define _NC _<false>

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif


namespace aworx { namespace lib { namespace time
{
void TicksCalendarTime::Clear()
{
    Year=
    Month=
    Day=
    DayOfWeek=
    Hour=
    Minute=
    Second=
    Millisecond=    0;

    #if defined (__GLIBCXX__) || defined(__APPLE__)
        tm_isdst= -1; // auto detect
    #endif

}

void TicksCalendarTime::Set( rawtime ticks, Timezone timezone )
{
    Clear();
    Ticks t(ticks);

    #if defined (__GLIBCXX__) || defined(__APPLE__)
        struct tm  tm;
        time_t tt= t.InEpochSeconds();
        if ( timezone == Timezone::UTC )
            gmtime_r( &tt, &tm );
        else
            localtime_r( &tt, &tm );

        Year=       tm.tm_year + 1900;
        Day=        tm.tm_mday;
        DayOfWeek=  tm.tm_wday;
        Month=      tm.tm_mon + 1;
        Second=     tm.tm_sec;
        Hour=       tm.tm_hour;
        Minute=     tm.tm_min;
        tm_isdst=   tm.tm_isdst;

    #elif defined( _WIN32 )
        SYSTEMTIME st;
        t.InSystemTime( &st, timezone );

        Year=       st.wYear;
        Day=        st.wDay;
        DayOfWeek=  st.wDayOfWeek;
        Month=      st.wMonth;
        Hour=       st.wHour;
        Minute=     st.wMinute;
        Second=     st.wSecond;

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif
}

rawtime  TicksCalendarTime::Get( Timezone timezone )
{
    Ticks t(0);

    #if defined (__GLIBCXX__) || defined(__APPLE__)
        struct tm  tm;
        tm.tm_year=       Year - 1900;
        tm.tm_mday=       Day;
        tm.tm_mon=        Month -1;
        tm.tm_hour=       Hour;
        tm.tm_min=        Minute;
        tm.tm_sec=        Second;
        tm.tm_isdst=      tm_isdst;

        time_t tt;
        if ( timezone == Timezone::UTC )
            tt= timegm( &tm );
        else
            tt= mktime( &tm );

        t.SetFromEpochSeconds( tt );


    #elif defined( _WIN32 )

        SYSTEMTIME st;
        st.wYear=           (WORD) Year;
        st.wDay=            (WORD) Day;
        st.wDayOfWeek=      (WORD) DayOfWeek;
        st.wMonth=          (WORD) Month;
        st.wHour=           (WORD) Hour;
        st.wMinute=         (WORD) Minute;
        st.wSecond=         (WORD) Second;
        st.wMilliseconds=   0;

        t.SetFromSystemTime( st, timezone );

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif

    return t.Raw();
}



//! @cond NO_DOX
const TString months[]= { "January", "February", "March", "April", "May", "June",
                          "July", "August",  "September", "October", "November", "December"   };
const TString   days[]= { "Sunday", "Monday", "Tuesday", "Wednesday",
                          "Thursday", "Friday", "Saturday"                                    };
//! @endcond NO_DOX

AString& TicksCalendarTime::Format( Substring format, AString& target, CurrentData targetData )
{
    if ( targetData == CurrentData::Clear )
        target.Clear();

    // this ensures that target is not nulled, as all other appends are NC-versions
    target._("");
    NumberFormat* nf= &NumberFormat::Computational;

    while ( format.IsNotEmpty() )
    {
        // read n equal characters
        int  n=  1;
        char c=  format.ConsumeChar();
        while (  format.ConsumeChar(c) )
            n++;

        switch (c)
        {
            case '\'': // single quotes
            {
                // one or more pairs of single quotes?
                if ( n > 1 )
                {
                    int pairs= n >> 1;
                    target.InsertChars<false>( '\'', pairs );
                    n-= (pairs << 1);
                }

                // one single quote?
                if ( n == 1 )
                {
                    // search end
                    integer end= format.IndexOf( '\'' );
                    if ( end < 1 )
                    {
                        ALIB_WARNING( "Format Error: Missing single Quote" );
                        target << "Format Error: Missing single Quote";
                        return target;
                    }

                    target._NC( format, 0, end );
                    format.ConsumeChars<false>( end + 1 );
                }

            } break;

            case 's': // second
                target._NC( strings::Format( Second, n, nf ) );
                break;

            case 'm': //minute
                target._NC( strings::Format( Minute, n, nf ) );
                break;

            case 'K': // hour 0..11
                target._NC( strings::Format( Hour % 12, n, nf ) );
                target._NC( Hour < 12 ? " am" : " pm" );
                break;

            case 'H': // hour 0..23
                target._NC( strings::Format( Hour,   n, nf ) );
                break;

            case 'd': // day
                     if ( n <= 2 )     target._NC( strings::Format( Day, n, nf) );
                else if ( n == 3 )     target._NC( days[DayOfWeek], 0, 3 );
                else                   target._NC( days[DayOfWeek]    );
                break;

            case 'M': // month
                     if ( n <= 2 )     target._NC( strings::Format( Month, n, nf ) );
                else if ( n == 3 )     target._NC( months[Month-1], 0, 3 );
                else                   target._NC( months[Month-1]     );
                break;

            case 'y': // year
                     if ( n == 1 )     target._NC( strings::Format(Year,        1, nf) );
                else if ( n == 2 )     target._NC( strings::Format(Year %  100, 2, nf) );
                else                   target._NC( strings::Format(Year,        n, nf) );
                break;

            default: // otherwise: copy what was in
                target.InsertChars<false>( c, n );
                break;
        }

    }

    return target;
}


}}}// namespace aworx::lib::time

