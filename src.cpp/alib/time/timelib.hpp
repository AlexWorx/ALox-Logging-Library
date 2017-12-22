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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_TIME_LIB)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_TIME_LIB
//! @cond NO_DOX
#define HPP_ALIB_TIME_LIB 1
//! @endcond



// #################################################################################################
// includes
// #################################################################################################
#if ALIB_MODULE_STRINGS

    #if !defined (HPP_ALIB_STRINGS_SUBSTRING)
        #include "alib/strings/substring.hpp"
    #endif
    #if !defined (_GLIBCXX_CTIME) && !defined(_CTIME_)
        #include <ctime>
    #endif

#endif




namespace aworx { namespace lib {
/**
 * This namespace of \b %ALib holds classes that are providing methods for
 * measuring time spans and conversion of dates and time values.
 */
namespace time {


/** ************************************************************************************************
 * The library class for namespace \ref aworx::lib::time.
 **************************************************************************************************/
class Time  : public lang::Library
{
    /** Friend class Ticks accesses internals.  */
    friend class aworx::lib::time::Ticks;


    // #############################################################################################
    // Types & constants
    // #############################################################################################
    public:
        /** 64-bit integer value used to store raw tick values.  */
        using   TRaw =             int64_t;

        static constexpr auto NanosPerDay         =  INT64_C( 86400000000000 ); ///< Constant denoting number of nanoseconds of a day.
        static constexpr auto NanosPerHour        =  INT64_C(  3600000000000 ); ///< Constant denoting number of nanoseconds of a hour.
        static constexpr auto NanosPerMinute      =  INT64_C(    60000000000 ); ///< Constant denoting number of nanoseconds of a minute.
        static constexpr auto NanosPerSecond      =  INT64_C(     1000000000 ); ///< Constant denoting number of nanoseconds of a second.
        static constexpr auto NanosPerMillisecond =  INT64_C(        1000000 ); ///< Constant denoting number of nanoseconds of a millisecond.
        static constexpr auto NanosPerMicrosecond =  INT64_C(           1000 ); ///< Constant denoting number of nanoseconds of a microsecond.



    // #############################################################################################
    // internals
    // #############################################################################################
    protected:
        /** The ticks when the library was initialized. */
        Ticks*                     creationTime;

        /** The frequency of the system timer*/
        int64_t                    inaccuracy;

        #if defined( __GLIBCXX__ ) || defined(__APPLE__)
            /** Used for conversion of clock times and monotonic clock timer.
             *  (Not defined under Windows OS) */
            TRaw                   diffOfMonotonicClockAndNow;

        #elif defined( _WIN32 )
            /** Used for conversion of clock times and monotonic clock timer.
             *  (Only defined under Windows OS) */
            int64_t                ticksPerSecond;
        #endif

    // #############################################################################################
    // Constructor
    // #############################################################################################
    public:
        inline  Time()
        : lang::Library( ALIB_VERSION, ALIB_REVISION, "ALIB_TIME" )
        {}


    // #############################################################################################
    // Interface methods
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * This method needs to be invoked when values of type \ref Ticks are to be converted to "real"
         * clock time values. Whenever the system clock is changed, such change is reflected by class
         * \b %Ticks and its conversion methods
         * \alib{time,Ticks::InEpochSeconds},
         * \alib{time,Ticks::SetFromEpochSeconds},
         * \alib{time,Ticks::SetFromEpochSeconds},
         * \alib{time,Ticks::SetFromEpochSeconds},
         * \alib{time,Ticks::SetFromEpochSeconds} and
         * \alib{time,Ticks::SetFromEpochSeconds},
         * <b>only after</b> the invocation of this method.<br>
         *
         * The advantages of this approach are:
         * - As long as this method is not called, changes of the system clock do not affect the display
         *   of time values measured with class \b %Ticks. They will continue to display clock time values
         *   which are in alignment with the system clock setting as it was when this method was invoked
         *   last (e.g. the bootstrap of the process).
         * - Round-trip calculations from \b %Ticks to clock times and back are consistent when this method
         *   is not invoked.
         *
         * Of-course, the drawback is: to ensure that the actual clock setting is reflected, the method
         * has to be invoked 'manually' prior to using one of the methods listed above.
         *
         * The method is invoked by #init.
         ******************************************************************************************/
        ALIB_API
        void SyncClock();

        /** ****************************************************************************************
         * The time (in ticks) when the ticker library containing the ticker (ALIB) was initialized.
         * This might be useful to measure the time since the process was started.
         *
         * @return  Initialization time of the library or process
         ******************************************************************************************/
        inline const Ticks&             CreationTime()
        {
            return *creationTime;
        }


        /** ****************************************************************************************
         * The reciprocal value of the frequency of the internal tick timer measured in nanoseconds.
         * This value gives an indication of the (in-)accuracy of the time intervals measured
         * with this class (at least if the  underlying system library is reasonably well
         * working in this respect).
         *
         * @return  The minimum number of nanoseconds between two ticks.
         ******************************************************************************************/
        inline int64_t                  Inaccuracy()
        {
            return inaccuracy;
        }


    // #############################################################################################
    // Internal methods
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Initializes \b %ALib time logic.
         *
         * Dependend on \ref ALIB_MODULE_BOXING, initializes the <b>%ALib %Boxing</b> system by
         * registering interface class
         * \ref aworx::lib::time::IFormat_TTicks "IFormat_TTicks".
         *
         * @param phase  The initialization phase to perform.
         ******************************************************************************************/
        virtual void        init( Phases phase )                                           override;

        /** ****************************************************************************************
         * Frees resources and shuts down \b %ALib time logic.
         ******************************************************************************************/
        virtual void        terminationCleanUp()                                           override;

}; // class time::Library

} // namespace aworx::lib[::time]

/** ************************************************************************************************
 * The static library singleton of namespace #aworx::lib::time.
 **************************************************************************************************/
ALIB_API
extern time::Time TIME;

} // namespace aworx[::lib]

/** Type alias name in namespace #aworx. */
using     Time=                 aworx::lib::time::Time;

} // namespace [aworx]


#endif // HPP_ALIB_TIME_LIB
