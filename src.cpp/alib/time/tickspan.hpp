// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_TIME_TICKSPAN)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_TIME_TICKSPAN
//! @cond NO_DOX
#define HPP_ALIB_TIME_TICKSPAN 1
//! @endcond



#if !defined (HPP_ALIB_TIME_TICKS)
    #include "alib/time/ticks.hpp"
#endif

namespace aworx { namespace lib { namespace time
{

/** ************************************************************************************************
 *  This class represents a time span, measured in days, hours, minutes and so on.
 *  It provides methods to import from and to an object of type
 *  \ref aworx::lib::time::Ticks "Ticks".<br>
 *  (Note: Objects of type <em>%Ticks</em> may represent a point in time or a time span, dependent
 *  on what value they have set to).
 **************************************************************************************************/
class TickSpan
{
    public:
        /** The number of days within the time span  */
        int                     Days;

        /** The number of hours (not the total, hence 0-23) within the time span.    */
        int                     Hours;

        /** The number of minutes (not the total, hence 0-59) within the time span.  */
        int                     Minutes;

        /** The number of seconds (not the total, hence 0-59) within the time span.  */
        int                     Seconds;

        /** The number of milliseconds (not the total, hence 0-999) within the time span. */
        int                     Milliseconds;

        /** The number of microseconds (not the total, hence 0-999) within the time span. */
        int                     Microseconds;

        /** The number of nanoseconds (not the total, hence 0-999) within the time span.  */
        int                     Nanoseconds;

    /** ********************************************************************************************
     *  Constructs the object to represent a time span of 0. (Sets all public fields to 0.)
     **********************************************************************************************/
    inline
    TickSpan()                                             { Clear(); }

    /** ********************************************************************************************
     *  Constructs the object using the given Tick objects ticks value.
     *  After construction, the public fields are set properly
     *  @param ticks The Ticks object to use for setting the public fields
     **********************************************************************************************/
    inline
    TickSpan( const Ticks& ticks )                         { Set( ticks.Raw() ); }

    /** ********************************************************************************************
     *  Constructs the object using the given ticks value.
     *  After construction, the public fields are set properly
     *  @param ticks The value in ticks to use for setting the public fields
     **********************************************************************************************/
    inline
    TickSpan( TimeLib::TRaw ticks )                         { Set(ticks); }

    /** ********************************************************************************************
     *  Constructs the object using the two Tick objects that mark the start and end points in time
     *  of the span.
     *  @param first   The Ticks object that marks the beginning of the time span
     *  @param second  The Ticks object that marks the end of the time span
     **********************************************************************************************/
    inline
    TickSpan( const Ticks& first,  const Ticks& second )   { Set( first.Raw() - second.Raw() ); }

    /** ********************************************************************************************
     *  Sets the public fields to represent the given Tick objects ticks value.
     *  The state of the object will hereafter be the same as it was when constructed with the same
     *  parameter.
     *  @param ticks The Ticks object to use for setting the public fields
     **********************************************************************************************/
    inline
             void               Set( const Ticks& ticks )   { Set( ticks.Raw() ); }

    /** ********************************************************************************************
     *  Sets the public fields to represent the given ticks value.
     *  The state of the object will hereafter be the same as it was when constructed with the same
     *  parameter.
     *  @param ticks The value in ticks to use for setting the public fields
     **********************************************************************************************/
    ALIB_API void               Set( TimeLib::TRaw ticks );

    /** ********************************************************************************************
     *  Takes the current values of the public fields and calculates a time span value in ticks.
     *  Such value can be used with class Ticks, e.g. to add or subtract time spans.
     *  @returns The time span represented by the public fields of this class.
     **********************************************************************************************/
    ALIB_API TimeLib::TRaw         Get();

    /** ********************************************************************************************
     *  Sets all public values to 0.
     **********************************************************************************************/
    ALIB_API void               Clear();
};



}} // namespace lib::time

/** Type alias name in namespace #aworx. */
using     TickSpan=             aworx::lib::time::TickSpan;

}  // namespace aworx

#endif // HPP_ALIB_TIME_TICKSPAN
