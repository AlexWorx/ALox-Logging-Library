// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.time;


/** ************************************************************************************************
 *  This class splits a given Ticks object (representing a time span) into the amount of days,
 *  hours, minutes, seconds and so on. Consequently, it takes a Ticks object as a parameter.
 *  This class can be seen as an extension to the Ticks class which provides methods to get
 *  the total number of these values. In addition, the reverse calculation can be performed,
 *  which means, the field values can be set and the corresponding time span in ticks
 *  received.
 **************************************************************************************************/
public class TickSpan
{
        /// The time value received from the
        protected long            ticks;

        /// The number of days within the time span
        public int                days;

        /// The number of hours (not the total, hence 0-23) within the time span
        public int                hours;

        /// The number of minutes (not the total, hence 0-59) within the time span
        public int                minutes;

        /// The number of seconds (not the total, hence 0-59) within the time span
        public int                seconds;

        /// The number of milliseconds (not the total, hence 0-999) within the time span
        public int                milliseconds;

        /// The number of microseconds (not the total, hence 0-999) within the time span
        public int                microseconds;

        /// The number of nanoseconds (not the total, hence 0-999) within the time span
        public int                nanoseconds;

    /** ********************************************************************************************
     *     Constructs the object using the given Tick objects ticks value.
     *  After construction, the public fields are set properly
     *  @param ticks The Ticks object to use for setting the public fields
     **********************************************************************************************/
    public            TickSpan( Ticks ticks )     { set( ticks.raw() ); }

    /** ********************************************************************************************
     *     Constructs the object using the given ticks value.
     *  After construction, the public fields are set properly
     *  @param ticks The value in ticks to use for setting the public fields
     **********************************************************************************************/
    public            TickSpan( long ticks )       { set( ticks ); }

    /** ********************************************************************************************
     *     Constructs the object to represent a time span of 0. (Sets all public fields to 0.)
     **********************************************************************************************/
    public            TickSpan()                   { clear(); }

    /** ********************************************************************************************
     *     Sets the public fields to represent the given Tick objects ticks value.
     *  The state of the object will hereafter be the same as it was when constructed with the same
     *  parameter.
     *  @param ticks The Ticks object to use for setting the public fields
     **********************************************************************************************/
    public void       set( Ticks ticks )            { set( ticks.raw() ); }

    /** ********************************************************************************************
     *     Sets the public fields to represent the given ticks value.
     *  The state of the object will hereafter be the same as it was when constructed with the same
     *  parameter.
     *  @param ticks The value in ticks to use for setting the public fields
     **********************************************************************************************/
    public    void    set( long ticks )
    {
        clear();
        this.ticks=    ticks;
        long fract;
        if ( ticks >  86400000000000L )    {    fract= ticks /  86400000000000L;    days=           (int) fract;        ticks-= fract *  86400000000000L;    }
        if ( ticks >   3600000000000L )    {    fract= ticks /   3600000000000L;    hours=          (int) fract;        ticks-= fract *   3600000000000L;    }
        if ( ticks >     60000000000L )    {    fract= ticks /     60000000000L;    minutes=        (int) fract;        ticks-= fract *     60000000000L;    }
        if ( ticks >      1000000000L )    {    fract= ticks /      1000000000L;    seconds=        (int) fract;        ticks-= fract *      1000000000L;    }
        if ( ticks >         1000000L )    {    fract= ticks /         1000000L;    milliseconds=   (int) fract;        ticks-= fract *         1000000L;    }
        if ( ticks >            1000L )    {    fract= ticks /            1000L;    microseconds=   (int) fract;        ticks-= fract *            1000L;    }
    }

    /** ********************************************************************************************
     *  Takes the current values of the public fields and calculates a time span value in ticks.
     *  Such value can be used with class Ticks, e.g. to add or subtract time spans.
     *  @returns The time span represented by the current values of the public fields.
     **********************************************************************************************/
    public    long    get()
    {
        return     days         *      86400000000000L
                +  hours        *       3600000000000L
                +  minutes      *         60000000000L
                +  seconds      *          1000000000L
                +  milliseconds *             1000000L
                +  microseconds *                1000L
                +  nanoseconds  ;
    }

    /** ********************************************************************************************
     *     Sets all public values to 0.
     **********************************************************************************************/
    public    void    clear()
    {
        days=
        hours=
        minutes=
        seconds=
        milliseconds=
        microseconds=
        nanoseconds=    0;
    }
}



