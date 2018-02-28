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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_TIME_TIMESTAMP)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_TIME_TIMESTAMP
//! @cond NO_DOX
#define HPP_ALIB_TIME_TIMESTAMP 1
//! @endcond

#if !defined (HPP_ALIB_TIME_TIMESPAN)
    #include "alib/time/timespan.hpp"
#endif



namespace aworx { namespace lib { namespace time {

/** ************************************************************************************************
 * This class provides an interface into system dependent timer values (usually 64 bit
 * tick counters that are called \e "ticks" with \alib).
 * Sibling class \alib{time,TimeSpan} and this class allow to store and calculate time
 * values in an efficient and highly accurate way.
 *
 * As ticks are system dependent, they should not be stored and loaded in data files or
 * otherwise shared between systems. Even on the same machine, the values may become
 * incompatible (e.g. after a reboot).
 * Also, in general such values should only be used by methods of
 * this class and classes
 * \alib{time,StopWatch},
 * \alib{time,TimeSpan} and
 * \alib{time,CalendarTime}.
 *
 * To construct an object of this type using calendar date an time values, helper class
 * \b %CalendarTime with its constructor
 * \alib{time,CalendarTime::CalendarTime(int,int,int,int,int,int,int)} is available. A typical
 * construction with this helper could look like this:
 *
 *      TimeStamp myDate= CalendarTime(2018,1,31,14,5).Get( Timezone::UTC );
 *
 *
 * \note
 *   The resolution and accuracy of the values is platform dependent. Especially nanoseconds are
 *   deemed to be not accurate and above 100 ns (this was written and fact in 2013).
 *
 * \attention
 *   The dates storable in objects of this class is limited to a certain time range. In the
 *   current GNU/Linux and Windows implementations the range is roughly <c>+-292.27</c> years before
 *   and after the point in time that the system that the software is running on was initialized
 *   (booted). This value results from dividing <c>2⁶63 bit</c> by the number of nanoseconds of
 *   one year of 365.25 days and the fact that internal, system dependent ticks counters are reset
 *   to \c 0 with the boot of a system.
 **************************************************************************************************/
class TimeStamp
{
    // #############################################################################################
    // protected fields
    // #############################################################################################
    protected:
        /** The internal time value. */
        TimeLib::TRaw                ticks;

    // #############################################################################################
    // Constructors
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Creates an instance representing the point in time when this constructor
         * was invoked.
         ******************************************************************************************/
        inline
        TimeStamp()                     { Set();    }

        /** ****************************************************************************************
         * Defaulted copy constructor
         * @param copy The time stamp to copy.
         ******************************************************************************************/
         TimeStamp( const TimeStamp& copy ) = default;

        /** ****************************************************************************************
         * Defaulted move constructor
         * @param move The time stamp to move.
         ******************************************************************************************/
         inline
         TimeStamp( TimeStamp&& move )= default;

        /** ****************************************************************************************
         * Creates an instance representing a given point in time.
         * @param initialTicks The value to copy into this.
         ******************************************************************************************/
        inline
        TimeStamp( TimeLib::TRaw initialTicks )
        {
            ticks=    initialTicks;
        }

    // #############################################################################################
    // Interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Sets the time of invocation as the value of this instance.
         ******************************************************************************************/
        void  Set()
        {
            #if defined( __GLIBCXX__ ) || defined(__APPLE__)
                struct timespec t;
                ALIB_ASSERT_RESULT_EQUALS( clock_gettime(CLOCK_MONOTONIC, &t),  0 );

                ticks= ( t.tv_sec * TimeLib::NanosPerSecond  ) + t.tv_nsec ;
            #elif defined( _WIN32 )
                    LARGE_INTEGER v;
                    ALIB_ASSERT_RESULT_NOT_EQUALS( QueryPerformanceCounter( &v ) , 0 );
                    ticks= v.QuadPart << 1;
            #else
                #pragma message ("Unknown Platform in file: " __FILE__ )
            #endif
        }

        /** ****************************************************************************************
         * Copies the ticks from the given object.
         * @param other The TimeStamp object to copy.
         ******************************************************************************************/
        inline
        void            Set( const TimeStamp& other )           { ticks=    other.ticks;    }

        /** ****************************************************************************************
         * Sets this object's value to the value specified in raw ticks.
         * @param value The number of ticks this object should represent.
         ******************************************************************************************/
        inline
        void            Set( TimeLib::TRaw value )              { ticks=    value;           }

         /** ****************************************************************************************
          * Gets the internally stored system dependent time in raw ticks.
          * @return  The internal value
          ******************************************************************************************/
         inline
         TimeLib::TRaw  Raw()    const                          { return ticks;                    }


        /** ****************************************************************************************
         * Defaulted copy assignment operator.
         * @param other The time stamp to assign.
         * @return A reference to this object.
         ******************************************************************************************/
        inline
        TimeStamp& operator=( const TimeStamp& other )  = default;

        /** ****************************************************************************************
         * Defaulted move assignment operator.
         * @param other The time stamp to assign.
         * @return A reference to this object.
         ******************************************************************************************/
        TimeStamp& operator=( TimeStamp&& other ) = default;

        /** ****************************************************************************************
         * Addition operator.
         * @param timeSpan The time span to add.
         * @return A time stamp object containing the sum.
         ******************************************************************************************/
        inline
        TimeStamp operator+( const TimeSpan& timeSpan ) const  { return ticks + timeSpan.ticks;     }

        /** ****************************************************************************************
         * Assignment by sum operator.
         * @param timeSpan The time span to add.
         * @return A reference to this object.
         ******************************************************************************************/
        inline
        TimeStamp& operator+=( const TimeSpan& timeSpan )      { ticks+= timeSpan.ticks; return *this;  }

        /** ****************************************************************************************
         * Subtraction operator.
         * @param timeSpan The time span to subtract.
         * @return A time stamp object containing the sum.
         ******************************************************************************************/
        inline
        TimeStamp operator-( const TimeSpan& timeSpan ) const  { return ticks -   timeSpan.ticks;  }

        /** ****************************************************************************************
         * Assignment by difference operator.
         * @param timeSpan The time span to subtract.
         * @return A reference to this object.
         ******************************************************************************************/
        inline
        TimeStamp& operator-=( const TimeSpan& timeSpan )      { ticks-= timeSpan.ticks; return *this;  }

        /** ****************************************************************************************
         * Subtraction operator with other time span argument. If the given time stamp represents
         * a point in type earlier than the one this object represents, the result is positive.
         * @param other The time stamp to subtract.
         * @return A time span object containing the difference.
         ******************************************************************************************/
        inline
        TimeSpan operator-( const TimeStamp& other ) const  { return ticks - other.ticks;   }


        /** ****************************************************************************************
         * Equal to operator.
         * @param other The time stamp to compare.
         * @return The result of the comparison.
         ******************************************************************************************/
        inline
        bool   operator==( const TimeStamp& other ) const    { return ticks == other.ticks;  }


        /** ****************************************************************************************
         * Not equal to operator.
         * @param other The time stamp to compare.
         * @return The result of the comparison.
         ******************************************************************************************/
        inline
        bool   operator!=( const TimeStamp& other ) const    { return ticks != other.ticks;  }

        /** ****************************************************************************************
         * Less than operator.
         * @param other The time stamp to compare.
         * @return A reference to this object.
         ******************************************************************************************/
        inline
        bool   operator<( const TimeStamp& other ) const     { return ticks <  other.ticks;  }

        /** ****************************************************************************************
         * Less than or equal to operator.
         * @param other The time stamp to compare.
         * @return The result of the comparison.
         ******************************************************************************************/
        inline
        bool   operator<=( const TimeStamp& other ) const   { return ticks <=  other.ticks;  }

        /** ****************************************************************************************
         * Greater than operator.
         * @param other The time stamp to compare.
         * @return The result of the comparison.
         ******************************************************************************************/
        inline
        bool   operator>( const TimeStamp& other ) const    { return ticks >  other.ticks;  }

        /** ****************************************************************************************
         * Greater than or equal to operator.
         * @param other The time stamp to compare.
         * @return The result of the comparison.
         ******************************************************************************************/
        inline
        bool   operator>=( const TimeStamp& other ) const   { return ticks >=  other.ticks;  }

    // #############################################################################################
    // Interface Age, Since
    // #############################################################################################

        /** ****************************************************************************************
         * Returns the time span between value represented by this instance and the current system
         * time.
         * If the internal value represents a historic point in time, the result is positive.
         *
         * @return  The age of this instance stored in a new TimeStamp.
         ******************************************************************************************/
        inline
        TimeSpan    Age()                            const
        {
            return TimeStamp() - *this;
        }

        /** ****************************************************************************************
         * Returns the time span between the value represented by this instance and the given
         * other time stamp. If the given time stamp represents an earlier point in time, the result
         * is positive.
         *
         * @param other The value to compare this instance with
         *
         * @return  The age of this instance stored in the given or created object.
         ******************************************************************************************/
        inline
        TimeSpan    Since( const TimeStamp& other )  const
        {
            return (*this) - other;
        }

        /** ****************************************************************************************
         * Determines if this objects' age is higher than a given time span.
         *
         * @param waitTime  A \b %TimeStamp object representing a time span.
         * @return  \c true if the given \b %TimeStamp object representing a time span is smaller
         *          or equal than our age. \c false otherwise.
         ******************************************************************************************/
        inline
        bool   IsOlderThan( TimeSpan waitTime )      const
        {
            return Age()  >  waitTime;
        }

    // #############################################################################################
    // Conversion to/from time values (nanoseconds, milliseconds, microseconds, seconds)
    // #############################################################################################
    public:

        #if ALIB_MODULE_STRINGS
            /** ************************************************************************************
             * Formats the point in time represented by this instance into an AString using the given
             * pattern. The token definitions of the format string is equal to those found in
             * \ref TicksCalendarTime.
             *
             * @param format  The format pattern string.
             * @param target  A reference to an AString that gets the result of the format processing
             *                appended.
             * @returns \p target (for convenience).
             **************************************************************************************/
            ALIB_API
            AString&  Format( const String& format, AString& target );
        #endif

    // #############################################################################################
    // Conversion to time platform/language specific values
    // #############################################################################################
        #if defined (__GLIBCXX__) || defined(__APPLE__)
            /** ************************************************************************************
             * Converts the internal value into seconds since January 1, 1970, 00:00:00 GMT.
             * The conversion is dependent on time zone and system clock setting of the host.
             * Changes in the system clock setting of the host are reflected only with explicit
             * invocation of \alib{time,TimeLib::SyncClock} on the static library singleton.
             * \note  GLib specific. For Windows OS see #InSystemTime and #InFileTime.
             *
             * @return Seconds in the epoch.
             **************************************************************************************/
            ALIB_API  time_t  InEpochSeconds()    const;

            /** ************************************************************************************
             * Sets the internal value by converting the given seconds since January 1,
             * 1970, 00:00:00 GMT. The conversion is dependent on time zone and system clock
             * setting of the host.
             * Changes in the system clock setting of the host are reflected only with explicit
             * invocation of \alib{time,TimeLib::SyncClock} on the static library singleton.
             * \note  GLib specific. For Windows OS see #SetFromSystemTime and #SetFromFileTime.
             *
             * @param epochSeconds The milliseconds in the epoch to convert.
             * @return A reference to this object.
             **************************************************************************************/
            ALIB_API  TimeStamp&  SetFromEpochSeconds ( time_t epochSeconds );

            /** ************************************************************************************
             * Static inline helper function that returns a time stamp set with
             * #SetFromEpochSeconds.
             *
             * @param epochSeconds The milliseconds in the epoch to convert.
             * @return A time stamp value.
             **************************************************************************************/
            inline static TimeStamp  FromEpochSeconds ( time_t epochSeconds )
            {
                return TimeStamp(0).SetFromEpochSeconds( epochSeconds );
            }
        #endif // no else here (doxygen)!

        #if defined (_WIN32)
            /** ************************************************************************************
             * Converts the internal value into windows specific file time, a 64-bit value that
             * represents the number of 100 nanosecond intervals that have elapsed since
             * 12:00 A.M. January 1, 1601 UTC. The conversion is dependent on time zone and system
             * clock setting of the host.
             * Changes in the system clock setting of the host are reflected only with explicit
             * invocation of \alib{time,TimeLib::SyncClock} on the static library singleton.
             * \note  Microsoft Windows specific. On other systems see #InEpochSeconds.
             *
             * @param result Pointer to a FILETIME struct to store the result in.
             **************************************************************************************/
            ALIB_API  void    InFileTime( LPFILETIME result ) const;

            /** ************************************************************************************
             * Converts the internal value into windows specific file time, a 64-bit value that
             * represents the number of 100 nanosecond intervals that have elapsed since
             * 12:00 A.M. January 1, 1601 UTC. The conversion is dependent on time zone and system
             * clock setting of the host.
             * Changes in the system clock setting of the host are reflected only with explicit
             * invocation of \alib{time,TimeLib::SyncClock} on the static library singleton.
             * \note  Microsoft Windows specific. On other systems see #InEpochSeconds.
             *
             * @param result A reference to a LARGE_INTEGER struct to store the result in.
             **************************************************************************************/
            ALIB_API  void    InFileTime( ULARGE_INTEGER& result ) const;

            /** ************************************************************************************
             * Sets the internal value to represent the point in time provided as "file time".
             * File time is a 64-bit value that represents the number of 100 nanosecond intervals
             * that have elapsed since 12:00 A.M. January 1, 1601 UTC.
             * The conversion is dependent on time zone and system clock setting of the host.
             * Changes in the system clock setting of the host are reflected only with explicit
             * invocation of \alib{time,TimeLib::SyncClock} on the static library singleton.
             * \note  Microsoft Windows specific. On other systems see #SetFromEpochSeconds.
             *
             * @param fileTime The file time to set.
             **************************************************************************************/
            ALIB_API  void    SetFromFileTime( const FILETIME& fileTime );

            /** ************************************************************************************
             * Sets the internal value to represent the point in time provided as "file time".
             * File time is a 64-bit value that represents the number of 100 nanosecond intervals
             * that have elapsed since 12:00 A.M. January 1, 1601 UTC.
             * The conversion is dependent on time zone and system clock setting of the host.
             * Changes in the system clock setting of the host are reflected only with explicit
             * invocation of \alib{time,TimeLib::SyncClock} on the static library singleton.
             * \note  Microsoft Windows specific. On other systems see #SetFromEpochSeconds.
             *
             * @param fileTime The file time to set.
             **************************************************************************************/
            ALIB_API  void    SetFromFileTime( const ULARGE_INTEGER& fileTime );

            /** ************************************************************************************
             * Converts the internal value into windows specific system time struct.
             * The conversion is dependent on time zone and system clock setting of the host.
             * Changes in the system clock setting of the host are reflected only with explicit
             * invocation of \alib{time,TimeLib::SyncClock} on the static library singleton.
             * \note  Microsoft Windows specific. On other systems see #SetFromEpochSeconds.
             *
             * @param result   Pointer to a SYSTEMTIME struct to store the result in.
             * @param timezone Denote if the time that is returned should be local or UTC.
             *                 Defaults to \c TimeZone::Local.
             * @return Seconds in the epoch.
             **************************************************************************************/
            ALIB_API  void    InSystemTime( LPSYSTEMTIME result, lang::Timezone timezone =lang::Timezone::Local ) const;

            /** ************************************************************************************
             * Sets the internal value to represent the point in time provided as windows system
             * time. The conversion is dependent on time zone and system clock setting of the host.
             * Changes in the system clock setting of the host are reflected only with explicit
             * invocation of \alib{time,TimeLib::SyncClock} on the static library singleton.
             * \note  Microsoft Windows specific. On other systems see #SetFromEpochSeconds.
             *
             * @param systemTime Pointer to a SYSTEMTIME struct that holds the system time to set.
             * @param timezone Denote if the time is interpreted as local or UTC.
             *                 Defaults to \c TimeZone::Local.
             **************************************************************************************/
            ALIB_API  void    SetFromSystemTime( const SYSTEMTIME& systemTime, lang::Timezone timezone= lang::Timezone::Local );
        #endif


};

}} // namespace lib::time

/** Type alias name in namespace #aworx. */
using     TimeStamp=                aworx::lib::time::TimeStamp;

}  // namespace aworx


#if ALIB_MODULE_BOXING
//! @cond NO_DOX
namespace aworx { namespace lib { namespace boxing  {
ALIB_BOXING_SPECIALIZE_CB_CUB( aworx::lib::time::TimeStamp , aworx::lib::time::TimeStamp , false, true );
inline  void  T_Boxing<aworx::lib::time::TimeStamp>::Boxing(Box& box, const aworx::lib::time::TimeStamp& o)
{
    box.data.Value= static_cast<boxvalue>( o.Raw() );
    box.data.Length= 0;
}

inline  aworx::lib::time::TimeStamp T_Boxing<aworx::lib::time::TimeStamp>::Unboxing( const Box& box )
{
    return aworx::lib::time::TimeStamp( static_cast<time::TimeLib::TRaw>( box.data.Value ) );
}

}}}
//! @endcond

namespace aworx { namespace lib { namespace time {

/**
 * Implementation of \ref aworx::lib::strings::boxing::IFormat "IFormat" for boxable type
 * <c>TimeStamp*</c>.<br>
 * Writes the content of \p box (which is of type \b %TimeStamp*) to the given \b %AString
 * object \p target using a local instance of class \b %TicksCalendarTime and its method
 * \ref aworx::lib::time::TicksCalendarTime::Format "TicksCalendarTime::Format".
 *
 */
class IFormat_TimeStamp: public strings::boxing::IFormat, public Singleton<IFormat_TimeStamp>
{
    /**
     * Interface implementation.
     * @param box        The box that the interface was invoked on.
     * @param formatSpec The specification of the format (type specific)
     * @param target     The AString object receiving the formatted string.
     */
    ALIB_API
    virtual void Invoke( const Box& box, const String& formatSpec, AString& target )       override;
};

}}} // namespace [aworx::lib::time]
#endif //ALIB_MODULE_BOXING

#if ALIB_MODULE_STRINGS
    ALIB_STRINGS_SPECIALIZE_T_APPLY( aworx::lib::time::TimeStamp )
#endif


#endif // HPP_ALIB_TIME_TIMESTAMP
