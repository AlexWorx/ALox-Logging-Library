// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.time;


/** ************************************************************************************************
 *  This class encapsulates a system dependent time value (Ticks) and provides some basic
 *  interface for measuring time spans, including multiple samples and their average.
 *
 *  The interface does provide nanosecond versions the methods. However, the internal resolution
 *  of the used timer is system dependent and might be lower than nanoseconds.
 **************************************************************************************************/
public class TickWatch
{
    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /**    The value. */
        protected        Ticks        ticks                    = new Ticks( 0L );

        /** The number of samples performed. */
        protected        int          cntSamples;

        /** The sum of the samples times. */
        protected        Ticks        sum                      = new Ticks( 0L );

        /** A temporary Ticks used as a return value */
        protected        Ticks        tempTicks;

    // #############################################################################################
    // Constructors
    // #############################################################################################

        /** ****************************************************************************************
         * Creates a TickWatch representing the current point in time.
         ******************************************************************************************/
        public           TickWatch    ()                    {    reset();        }

        /** ****************************************************************************************
         * Creates a TickWatch as a copy of another TickWatch.
         *
         * @param copy  The instance to copy value from.
         ******************************************************************************************/
        public           TickWatch    ( TickWatch copy )
        {
            ticks        .set( copy.ticks );
            sum          .set( copy.sum );
            cntSamples=  copy.cntSamples;
        }


    // #############################################################################################
    // Interface Get/Set/Clear
    // #############################################################################################

        /** ****************************************************************************************
         * Returns the internally stored value.
         * @return  the internally stored Ticks value.
         ******************************************************************************************/
        public  Ticks    getStartTime()            { return ticks;        }

        /** ****************************************************************************************
         * Sets the internal value to current system time.
         * This affects both, the reference value for the calculation of this TickWatchs age in
         * subsequent calls, as well as subsequent sample time spans.
         ******************************************************************************************/
        public  void     start()                   { ticks.set();         }

        /** ****************************************************************************************
         * Sets the internal time value.
         * This affects both, the reference value for the calculation of this TickWatchs age in
         * subsequent calls, as well as subsequent sample time spans.
         *
         * @param t The value.
         ******************************************************************************************/
        public  void     setStartTime( Ticks t )   { ticks.set( t );      }

        /** ****************************************************************************************
         *  Sets the internal value to current system time and clears any existing sum and quantity
         *  of samples.
         ******************************************************************************************/
        public  void     reset()                   { sum.setRaw( 0L ) ; cntSamples= 0;  start(); }



    // #############################################################################################
    // Interface to Measurement
    // #############################################################################################

        /** ****************************************************************************************
         *  Returns the time span between the current system time and the internal reference value.
         *  In addition this value is added to the sum of sample times and the sample counter is
         *  increased by one. Lastly the internal reference value is set to now. Therefore, a
         *  subsequent call to this function would measure the time span from this call to this
         *  subsequent call (if the internal reference value was not set differently meanwhile).
         *  Other interface methods dealing with samples are #getSampleCnt, #getCumulated and
         *  #getAverage.
         *
         * @return The time difference between the current system time and the internal
         *         reference value.
         ******************************************************************************************/
        public  Ticks    sample    ()
        {
            if (tempTicks == null )
                tempTicks= new Ticks( 0L );

            cntSamples++;
            long old=    ticks.raw();
            ticks.set();
            long diff=   ticks.raw() - old;

            tempTicks.setRaw( diff );
            sum.add( tempTicks );

            return tempTicks;
        }

        /** ****************************************************************************************
         * Returns the number of calls to #sample since this instance was created or #reset was
         * invoked.
         *
         * @return  The number of samples.
         ******************************************************************************************/
        public  int    getSampleCnt()        { return cntSamples; }

        /** ****************************************************************************************
         * Returns the cumulated length of all samples taken since this instance was created or
         * cleared.
         * Note: the object returned will be reused in subsequent calls to this method. Hence,
         * previously returned values will be overwritten!
         * @return  The cumulated length of all samples taken since the last reset.
         ******************************************************************************************/
        public  Ticks  getCumulated()        { return sum; }

        /** ****************************************************************************************
         * Returns the average time of all samples since this instance was created or reset.
         * If no measurement was performed, the result value will be set to 0 ticks.
         *
         * Note: Attention: The object returned is a temporary object, deemed to be reused by other
         * interface methods of this instance. Therefore, it must be used only until subsequent
         * method invocations on this instance are performed (hence, also not thread safe!)
         * Use #getAverage(Ticks result) to provide a dedicated external result instance.
         *
         * @return  The average length of all samples taken since the last reset.
         ******************************************************************************************/
        public  Ticks  getAverage()
        {
            if (tempTicks == null )
                tempTicks= new Ticks( 0L );
            return getAverage( tempTicks );
        }

        /** ****************************************************************************************
         * Returns the average time of all samples since this instance was created or reset.
         * If no measurement was performed, the result value will be set to 0 ticks.
         *
         * @param result   An object to store the result in. If not provided (null), a result
         *                 object is created.
         * @return  The average sample time within the given or created object.
         ******************************************************************************************/
        public  Ticks  getAverage( Ticks result )
        {
            if ( result == null )
                result= new Ticks();

            result.setRaw( cntSamples== 0 ? 0L   :    (sum.raw() / cntSamples) );
            return  result;
        }
}

