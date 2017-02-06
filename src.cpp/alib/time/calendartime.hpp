#// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_TIME_CALENDARTIME)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_TIME_CALENDARTIME
//! @cond NO_DOX
#define HPP_ALIB_TIME_CALENDARTIME 1
//! @endcond NO_DOX


#if !defined (HPP_ALIB_TIME_TICKS)
    #include "alib/time/ticks.hpp"
#endif

namespace aworx { namespace lib { namespace time
{
/** ************************************************************************************************
 *  This class represents a point in time as a set of calendar values (year, month, day, hour...).
 *  It provides methods to import from and to object of type
 *  \ref aworx::lib::time::Ticks "Ticks".
 *
 *  In addition a method to format the date and time into human readable string value is available.
 *
 *  \note This class is using system specific calendar methods and relies on the locale and time zone
 *  settings of the machine.
 **************************************************************************************************/
class TicksCalendarTime
{
    #if defined (__GLIBCXX__) || defined(__APPLE__)
        protected:
        /// the TM struct field for daylight saving information
        int                     tm_isdst;
    #endif

    public:
        /// The calendar year (e.g. 2017)
        int                     Year;

        /// The calendar month (1..12)
        int                     Month;

        /// The calendar day (1..31)
        int                     Day;

        /// The calendar day of week (this is ignored, when converted back to a time value)
        int                     DayOfWeek;

        /// The calendar hour (0..23)
        int                     Hour;

        /// The calendar minute (0..59)
        int                     Minute;

        /// The calendar second (0..59)
        int                     Second;

        /// The calendar millisecond (0..999)
        int                     Millisecond;

    /** ********************************************************************************************
     * Constructs the object to represent a time span of 0. (Sets all public fields to 0.)
     **********************************************************************************************/
    inline
    TicksCalendarTime()
    {
        Clear();
    }

    /** ********************************************************************************************
     *  Constructs the object using the given Tick objects ticks value.
     *  After construction, the public fields are set properly
     *  @param ticks    The Ticks object to use for setting the public fields
     *  @param timezone Denote if the time that is calculated should be local or UTC.
     *                  Defaults to \c TimeZone::Local.
     **********************************************************************************************/
    inline
     TicksCalendarTime( const Ticks& ticks, lang::Timezone timezone =lang::Timezone::Local )
     {
        Set( ticks.Raw(), timezone );
     }

    /** ********************************************************************************************
     *  Constructs the object using the given ticks value.
     *  After construction, the public fields are set properly
     *  @param ticks    The value in ticks to use for setting the public fields
     *  @param timezone Denote if the time that is calculated should be local or UTC.
     *                  Defaults to \c TimeZone::Local.
     **********************************************************************************************/
    inline
     TicksCalendarTime( rawtime ticks, lang::Timezone timezone =lang::Timezone::Local )
     {
        Set(ticks, timezone);
     }


    /** ********************************************************************************************
     *  Sets the public fields to represent the given Tick objects time value.
     *  @param ticks    The Ticks object to use for setting the public fields
     *  @param timezone Denote if the time that is calculated should be local or UTC.
     *                  Defaults to \c TimeZone::Local.
     **********************************************************************************************/
    inline
    void         Set( const Ticks& ticks, lang::Timezone timezone =lang::Timezone::Local )
    {
        Set( ticks.Raw(), timezone );
    }

    /** ********************************************************************************************
     *  Sets the public fields to represent the given ticks value.
     *  @param ticks    The value in ticks to use for setting the public fields
     *  @param timezone Denote if the time that is calculated should be local or UTC.
     *                  Defaults to \c TimeZone::Local.
     **********************************************************************************************/
    ALIB_API
    void         Set( rawtime ticks, lang::Timezone timezone =lang::Timezone::Local  );

    /** ********************************************************************************************
     *  Takes the current values of the public fields and calculates a raw ticks value.
     *  Such value can be used with class Ticks, e.g. to add or subtract time spans.
     *  \attention The resolution and possible time range of class ticks is platform dependent.
     *             This method must not be used to create ticks on dates which are out of range.
     *
     *  @param timezone Denote if the time that is calculated should be local or UTC.
     *                  Defaults to \c TimeZone::Local.
     *  @returns The time span represented by the public fields of this class.
     **********************************************************************************************/
    ALIB_API
    rawtime Get( lang::Timezone timezone =lang::Timezone::Local );

    /** ********************************************************************************************
     *     Sets all public values to 0.
     **********************************************************************************************/
    ALIB_API
    void         Clear();

    /** ********************************************************************************************
     * Formats the date using a given pattern string. Within the pattern string, different symbols
     * are interpreted as tokens. The format is compatible with C# time format strings, as well as
     * with class SimpleDateFormat of the Java APIs.<br>
     * Strings within the format text that should not be interpreted as tokens may be surrounded
     * by single quotes. Two single quotes in a row, will be replaced by one single quote.<br>
     * The following tokens are supported:
     *
     *  <center>Token</center>  | <center>Description</center>
     *  - - - - -| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     *   y       |The year with as many digits as it has (for current dates this is 4).</TD> </TR>
     *   yy      |The year, truncated to 2 digits (modulo 100).</TD> </TR>
     *   yyy...y |The year with a minimum amount of digits as amount of y-characters given.</TD> </TR>
     *   M       |The month as numbers from 1..12.</TD> </TR>
     *   MM      |The month as numbers from 01..12.</TD> </TR>
     *   MMM     |The month as abbreviated, 3-digit word in English language.</TD> </TR>
     *   MMMM    |The month as word in English language.</TD> </TR>
     *   d       |The day as numbers from 1..31.</TD> </TR>
     *   dd      |The day as numbers from 01..31.</TD> </TR>
     *   ddd     |The day as abbreviated, 3-digit word in English language.</TD> </TR>
     *   dddd    |The day as word in English language.</TD> </TR>
     *   H       |The hour as numbers from 0..23.</TD> </TR>
     *   HH      |The hour as numbers from 00..23.</TD> </TR>
     *   K       |The hour as numbers from 0..11 am/pm.</TD> </TR>
     *   KK      |The hour as numbers from 00..11 am/pm.</TD> </TR>
     *   m       |The minute as numbers from 0..59.</TD> </TR>
     *   mm      |The minute as numbers from 00..59.</TD> </TR>
     *   s       |The second as numbers from 0..59.</TD> </TR>
     *   ss      |The second as numbers from 00..59.</TD> </TR>
     *
     * @param format     The format pattern string.
     * @param target     A reference to an AString that gets the result of the format processing
     *                   appended.
     * @param targetData If \c CurrentData::Keep (the default) the string is appended to \p target.
     *                   if \c CurrentData::Clear, \p target is cleared.
     * @returns \p target (for convenience).
     **********************************************************************************************/
    ALIB_API
    AString&    Format( Substring format, AString& target,
                        lib::lang::CurrentData targetData= lib::lang::CurrentData::Keep  );
};


}} // namespace lib::time

/** Type alias name in namespace #aworx. */
using     TicksCalendarTime=    aworx::lib::time::TicksCalendarTime;

}  // namespace aworx

#endif // HPP_ALIB_TIME_CALENDARTIME
