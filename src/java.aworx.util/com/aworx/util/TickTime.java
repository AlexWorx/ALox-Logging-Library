package com.aworx.util;

import java.util.Calendar;
import java.util.Date;



/**********************************************************************************************//**
 * <summary>	
 * 	This class encapsulates a system dependent time value (ticks) and uses the static class Ticker to
 * 	get and manipulate it.  See class Ticker to learn about system dependent time values (ticks)
 * 	and their usage.
 * 	
 *  The interface does not provide explicit nanosecond versions the methods. However, you can work with
 *  nanoseconds, by using the system dependent ticks versions of the interface functions use class 
 *  Ticker to convert to nanoseconds.
 * 	
 *  In addition this class provides an interface to do a series of time measurements, getting the sum 
 *  and average values (similar to stopwatch or time keeper).
 * </summary>
 **************************************************************************************************/
public class TickTime
{
	// #################################################################################################
	// Internal fields
	// #################################################################################################

	/**	The value. */
	private			long				ticks;
		
	/** The sum of the measurements. */
	private			long				sum;

	/** The number of measurements performed. */
	private			int					cntMeasures; 
		

	// #################################################################################################
	// Constructors
	// #################################################################################################

    /**********************************************************************************************//**
     * Creates a TickTime with internal tick time of 0.
     **************************************************************************************************/
	public 		 		TickTime	( )			
	{
		ticks=			0L;			
		sum=			0L; 
		cntMeasures=	0;	
	}

    /**********************************************************************************************//**
     * Creates a TickTime from a given time value in ticks.
     *
     * @param otherTicks    The value to copy into this.
     **************************************************************************************************/
	public 		 	TickTime	( long otherTicks )			
	{
		ticks=			otherTicks;			
		sum=			0L; 
		cntMeasures=	0;	
	}

    /**********************************************************************************************//**
     * Creates a TickTime as a copy of another TickTime.
     *
     * @param copy  The instance to copy value from.
     **************************************************************************************************/
	public 		 	TickTime	( TickTime copy )		
	{
		ticks=			copy.ticks; 
		sum=			copy.sum; 
		cntMeasures=	copy.cntMeasures;	
	}

	// #################################################################################################
	// Conversion to platform specific objects
	// #################################################################################################
	
    /**********************************************************************************************//**
     * Convert this instance into a string representation.
     *
     * @return  A String that represents this instance.
     **************************************************************************************************/
	@Override public  String		toString()
	{
		return Ticker.toJavaCalendar( ticks, null ).toString();
	}

	// #################################################################################################
	// Interface Get/Set/Clear
	// #################################################################################################

    /**********************************************************************************************//**
     * Returns the internally stored value (in ticks).
     *
     * @return  the internally stored value (in ticks).
     **************************************************************************************************/
	public	long	get()						{ return ticks;					}

    /**********************************************************************************************//**
     * Sets the internal value to the given value in ticks.
     *
     * @param value The value.
     **************************************************************************************************/
	public	void	setTo( long value )			{ this.ticks= value;			}

    /**********************************************************************************************//**
     * Sets the internal value to current system time. This affects reference value for the
     * subsequent measurements.
     **************************************************************************************************/
	public	void	setToNow()					{ ticks= Ticker.now();		}

	/**********************************************************************************************//**
	 * <summary>
	 *  Sets the internal value to current system time and clears existing sum and quantity of
	 *  measurements.
	 * </summary>
	 **************************************************************************************************/
	public	 void	clear()						{ setToNow(); sum= 0L; cntMeasures= 0;  }
		

	// #################################################################################################
	// Interface Since
	// #################################################################################################

    /**********************************************************************************************//**
     * Returns the time difference between the current system time and the time value represented by
     * this instance in (system dependent) ticks. If internal value represents a historic point in
     * time, the result is positive.
     *
     * @return  .
     **************************************************************************************************/
	public 	long	age()						{ return Ticker.now() - ticks;	}

    /**********************************************************************************************//**
     * Returns the time difference between the current system time and the time value represented by
     * this instance in milliseconds. If internal value represents a historic point in time, the
     * result is positive.
     *
     * @return  .
     **************************************************************************************************/
	public 	int		ageInMillis()				{ return (int) Ticker.toMillis  ( Ticker.now() - ticks );	}

    /**********************************************************************************************//**
     * Returns the time difference between the current system time and the time value represented by
     * this instance in microseconds. If internal value represents a historic point in time, the
     * result is positive.
     *
     * @return  .
     **************************************************************************************************/
	public 	long	ageInMicros()				{ return Ticker.toMicros( Ticker.now() - ticks );	}

    /**********************************************************************************************//**
     * Returns the time span between the given TickTime and this instances value in (system
     * dependent) ticks. If the given TickTime represents a later point in time than the point in
     * time this instance represents, the result is positive.
     *
     * @param newerTime The value to compare this instance with.
     *
     * @return The time difference in ticks.
     **************************************************************************************************/
	public 	long	span( TickTime newerTime )			{ return						newerTime.ticks - ticks;	}

    /**********************************************************************************************//**
     * Returns the time span between the given TickTime and this instances value in milliseconds. If
     * the given TickTime represents a later point in time than the point in time this instance
     * represents, the result is positive.
     *
     * @param newerTime The value to compare this instance with.
     *
     * @return  The time difference in milliseconds.
     **************************************************************************************************/
	public 	int		spanInMillis ( TickTime newerTime )	{ return (int) Ticker.toMillis( newerTime.ticks - ticks );	}

    /**********************************************************************************************//**
     * Returns the time span between the given TickTime and this instances value in microseconds. If
     * the given TickTime represents a later point in time than the point in time this instance
     * represents, the result is positive.
     *
     * @param newerTime The value to compare this instance with.
     *
     * @return  The time difference in microseconds.
     **************************************************************************************************/
	public 	long	spanInMicros ( TickTime newerTime )	{ return	  Ticker.toMicros( newerTime.ticks - ticks );	}


	// #################################################################################################
	// Interface to Measurement
	// #################################################################################################

    /**********************************************************************************************//**
     * Returns a (system dependent) time difference between the current system time and the internal
     * reference value. In addition this value is added to the sum of measurement time and the
     * measurement counter is increased by one. Lastly the internal reference value is set to now.
     * Therefore, a subsequent call to this function would measure the time span from this call to
     * this subsequent call (if the internal reference value was not set differently meanwhile).
     *
     * @return The time difference between the current system time and the the internal reference
     *         value in ticks.
     **************************************************************************************************/
	public		 long	measure	()
	{
		cntMeasures++; 
		long diff= ( Ticker.now() - ticks ); 
		sum+= diff; 
		return diff;
	}

    /**********************************************************************************************//**
     * Returns the number of calls to Measure since object was created or clear() was invoked.
     *
     * @return  Returns the number of calls to Measure since object was created or clear() was invoked.
     **************************************************************************************************/
	public		 int	getMeasureCnt()			{ return cntMeasures; }

    /**********************************************************************************************//**
     * Returns the cumulated time of all measurements since object was created or cleared in (system
     * dependent) ticks.
     *
     * @return  The cumulated measured ticks.
     **************************************************************************************************/
	public		long	getCumulatedTicks()		{ return sum; }

    /**********************************************************************************************//**
     * Returns the average time of all measurements since object was created or cleared in (system
     * dependent) ticks. If no measurement was performed, this method returns 0.
     *
     * @return  The average measured ticks.
     **************************************************************************************************/
	public		long	getAverageTicks()		{ return  cntMeasures== 0 ? 0L	 :	(sum / cntMeasures); }

    /**********************************************************************************************//**
     * Returns the average time of all measurements since object was created or cleared in
     * milliseconds. If no measurement was performed, this method returns 0.
     *
     * @return  The average measured milliseconds.
     **************************************************************************************************/
	public		long	getAverageMillis()		{ return  Ticker.toMillis( getAverageTicks() ); }

    /**********************************************************************************************//**
     * Returns  one divided by the average time, hence the number of Hertz that correspond to the
     * average measured time.
     *
     * @return  The Hertz value corresponding to the average measured time.
     **************************************************************************************************/
	public		double	getAverageHertz()		{ return  cntMeasures== 0 ? 0d	 :	(1000000000d * cntMeasures / sum); }
	
	// #################################################################################################
	// Conversion to time platform/language specific objects
	// #################################################################################################

    /**********************************************************************************************//**
     * Sets the given java.util.Calendar object to correspond to this instance.
     *
     * @param result    The java.util.Calendar object to set. If null, this is created.
     *
     * @return  The date object given or created.
     **************************************************************************************************/
	public 	Calendar	toJavaCalendar	 ( Calendar result )  
	{ 
		return Ticker.toJavaCalendar( ticks, result ); 
	}	

    /**********************************************************************************************//**
     * Sets this instance to the time represented by the given java.util.Calendar.
     *
     * @param javaCalendar  The java.util.Calendar object to read the time from.
     **************************************************************************************************/
	public 	void 		fromJavaCalendar	 ( Calendar javaCalendar )	
	{
		ticks=	Ticker.fromJavaCalendar( javaCalendar );
	}

    /**********************************************************************************************//**
     * Sets the given java.util.Date object to correspond to this instance.
     *
     * @param result    The java.util.Date object to set. If null, this is created.
     *
     * @return  The date object given or created.
     **************************************************************************************************/
	public 	Date		toJavaDate	 ( Date result )	
	{ 
		return Ticker.toJavaDate( ticks, result ); 
	}	

    /**********************************************************************************************//**
     * Sets this instance to the time represented by the given java.util.Date.
     *
     * @param javaDate  The java.util.Date object object to read the time from.
     **************************************************************************************************/
	public void			fromJavaDate	 ( Date javaDate )	
	{
		ticks=	Ticker.fromJavaDate( javaDate );
	}
	
}

