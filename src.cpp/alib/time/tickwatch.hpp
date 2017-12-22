// #################################################################################################
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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_TIME_TICKWATCH)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_TIME_TICKWATCH
//! @cond NO_DOX
#define HPP_ALIB_TIME_TICKWATCH 1
//! @endcond


#if !defined (HPP_ALIB_TIME_TICKS)
    #include "alib/time/ticks.hpp"
#endif

namespace aworx { namespace lib { namespace time
{
/** ************************************************************************************************
 *  This class encapsulates a system dependent time value (Ticks) and provides some basic
 *  interface for measuring time spans, including multiple samples and their average.
 **************************************************************************************************/
class TickWatch
{
    // #############################################################################################
    // Internal fields
    // #############################################################################################
    protected:

        ///  The current start time.
        Ticks        startTime;

        ///  The number of samples performed.
        int          cntSamples                                                                  =0;

        ///  The sum of the samples times.
        Ticks        sum;


    // #############################################################################################
    // Constructors
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Creates a started StopWatch.
         ******************************************************************************************/
        inline
        TickWatch  () : startTime(),  sum(0)        {}

        /** ****************************************************************************************
         * Creates a StopWatch as a copy of another StopWatch.
         * @param copy  The instance to copy value from.
         ******************************************************************************************/
        TickWatch    ( const TickWatch& copy )
        : startTime(0), sum(0)
        {
            startTime    .Set( copy.startTime );
            sum          .Set( copy.sum );
            cntSamples=  copy.cntSamples;
        }

    // #############################################################################################
    // Interface Get/Set/Reset
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Returns the internally stored start time
         * @return    The start time
         ******************************************************************************************/
        inline
        const Ticks&    GetStartTime()    const               { return startTime;                  }

        /** ****************************************************************************************
         * Sets the start time to now.
         * This affects both, the reference value for the calculation of this StopWatch's age in
         * subsequent calls, as well as subsequent sample time spans.
         ******************************************************************************************/
        inline
        void            Start()                               { startTime.Set();                   }

        /** ****************************************************************************************
         * Sets the start time to the given value.
         * @param newStartTime  A new start time for the stopwatch
         ******************************************************************************************/
        inline
        void            SetStartTime( const Ticks newStartTime ) { this->startTime.Set( newStartTime );  }


        /** ****************************************************************************************
         *  Sets the internal value to current system time and clears existing sum and quantity of
         *  samples.
         ******************************************************************************************/
        inline
        void            Reset()                          { sum.Set( 0L ); cntSamples= 0;  Start(); }


    // #############################################################################################
    // Interface to Measurement
    // #############################################################################################

        /** ****************************************************************************************
         *  Returns the time span between the current system time and the internal start value.
         *  In addition this value is added to the sum of sample times and the sample counter is
         *  increased by one. Lastly the internal reference value is set to now. Therefore, a
         *  subsequent call to this function would measure the time span from this call to this
         *  subsequent call (if the internal start time value was not set differently meanwhile).
         *
         * @return The time difference between the current system time and the internal
         *         reference value.
         ******************************************************************************************/
        inline
        const Ticks    Sample    ()
        {
            cntSamples++;
            Time::TRaw st=    startTime.Raw();
            startTime.Set();
            Time::TRaw diff=  startTime.Raw() - st;

            Ticks sample( diff );
            sum.Add( diff );

            return sample;
        }

        /** ****************************************************************************************
         *  Returns the number of calls to #Sample since this instance was created or #Reset was invoked.
         * @return    The number of samples.
         ******************************************************************************************/
        inline
        int      GetSampleCnt()             { return cntSamples; }

        /** ****************************************************************************************
         *  Returns the cumulated time of all samples taken since this instance was created or cleared.
         *  Note: the object returned will be reused in subsequent calls to this method. Hence, previously
         *  returned values will be overwritten!
         *
         * @return  The cumulated measured time.
         ******************************************************************************************/
        inline
        Ticks    GetCumulated()            { return sum; }

        /** ****************************************************************************************
         *  Returns the average time of all samples since this instance was created or reset.
         *  If no measurement was performed, the result value will be set to 0 ticks.
         *
         * @return  The cumulated measured time.
         ******************************************************************************************/
        inline
        Ticks    GetAverage()
        {
            return Ticks ( cntSamples== 0 ? 0L     :    ( sum.Raw() / cntSamples) );
        }
};


}} // namespace lib::time

/** Type alias name in namespace #aworx. */
using     TickWatch=            aworx::lib::time::TickWatch;

}  // namespace aworx

#endif // HPP_ALIB_TIME_TICKWATCH
