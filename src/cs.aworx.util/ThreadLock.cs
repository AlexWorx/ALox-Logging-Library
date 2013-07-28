// #################################################################################################
//  AWorx Util - Classes we need
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:	ThreadLock
//  File:	ThreadLock.cs											Namespace:  com.aworx.util
// #################################################################################################

using System;
using System.Text;
using System.Threading;
using com.aworx.lox;

namespace com.aworx.util  {


/** ***********************************************************************************************
 * <summary>
 *  This class allows *mutual exclusive access* to resources that the using software agrees on
 *  to protect with a certain instance hereof.
 *  In other words, access to certain resources of a software that has to be thread safe, can 
 *  be protected if each thread (aka critical section code) uses the same ThreadLock to control the 
 *  access to.
 *  
 *  If a lock() is not followed by a corresponding unlock(), other threads will not be able to
 *  gain control to this object and will wait endlessly (deadlock situation). To avoid this, 
 *  it is a good practice to embed pairs of lock()/unlock() calls into try/finally statements
 *  as follows:
 *  
 *      try { tl.lock(); ...critical section code .... } finally { tl.unlock() } 
 *      
 *  ThreadLock uses an internal counter to allow multiple calls to lock() and to be freed only
 *  when a same amount of unlock() calls are performed. This behavior can be switched off
 *  by a constructor parameter. If switched off, each recursive lock() calls will not 
 *  be counted and each call to unlock() will instantly free the mutex. This mode is even less
 *  recommended than using this class in recursive mode. 
 *  
 *  Furthermore, ThreadLock allows to disable locking using setUnsafe(). The objective here is
 *  to gain execution speed, as thread synchronization causes relatively expensive system calls.
 *  
 *  Caution: Use this class with great care. Deadlocks are not easy to detect and debug. Use
 *  this class only if standard synchronization of the JAVA language seems too limited and mechanisms
 *  like the class uses internally would need to be implemented.
 * </summary>
 **************************************************************************************************/
public class ThreadLock
{
	// #################################################################################################
	// Public fields 
	// #################################################################################################

	/** <summary> 
	 * Flag to use assert() to detected misuse in debug mode. Default is on, and you should 
	 * keep it on! 
	 * </summary> */
	public	bool 			UseAssertions										= true;
				
	/** <summary> 
	 * This is a threshold that causes lock() to log a warning if acquiring the access using method lock()
	 * takes longer than the given number of milliseconds. To disable such messages, set this value to 0.
	 * Default is 1 sec. Measured in ticks, see class Ticker.
	 * </summary> */
	public	long	 		WaitALoxWarningLimit								= Ticker.FromMillis( 1000 );
				
	/** <summary> 
	 * Limit of recursions. If limit is reached or a multiple of it, an error logged using ALox.  
	 * </summary> */
	public	int	 			RecursionWarningThreshold							= 10;			

	// #################################################################################################
	// Protected fields 
	// #################################################################################################

	/** <summary> Flag if recursion support is on. If not, nested locks are not counted. </summary> */
	protected bool 			recursiveMode;			

	/** <summary> Counter for the number of lock() calls of the current thread. </summary> */
	protected int 			lockCount;
			 
	/** <summary> Counter for the number of lock() calls of the current thread. </summary> */
	protected Thread 		owner;

	/** <summary> The internal object to lock on. </summary> */
	protected Object 		mutex;
				
	// #################################################################################################
	// Constructors 
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>
	 *  Create a ThreadLock that allows recursion. A warning will be given (ALox Error) when the
	 *  given recursion level is reached (and each multiple of it). In addition the lock can be
	 *  initialized to be unsafe, which means the locking critical sections is disabled.
	 * </summary>
	 * <param name="recursiveMode">	(Optional) Flag if recursion support is on. If not, nested locks 
	 * 								are not counted. </param>
	 * <param name="setUnsafeMode">	(Optional) True to set this unsafe. Please don't! </param>
	 **************************************************************************************************/
	public ThreadLock( bool recursiveMode= true, bool setUnsafeMode = false  )
	{
		// save parameters
		this.recursiveMode= 			recursiveMode;
		
		// set safeness
		SetUnsafe( setUnsafeMode );
	}

	// #################################################################################################
	// Interface 
	// #################################################################################################

	
	/** ***********************************************************************************************
	 * <summary>
	 * Thread which invokes this method gets registered  as the current owner of this object, until the 
	 * same thread releases the ownership invoking unlock(). 
	 * In the case that this object is already owned by another thread, the invoking thread is suspended
	 * until ownership can be gained.
	 * Multiple (nested) calls to this method are counted and the object is only released when the same
	 * number of unlock() calls have been made. 
	 * </summary>
	 **************************************************************************************************/
	public void Acquire()		
	{
		// are we in unsafe mode?
		if ( mutex == null )
		{
			// we are still increasing the lockCount  
			lockCount=  recursiveMode 	? lockCount + 1 
										: 1;
			
			// reached warning limit
			if ( lockCount  <= 0  )
			{
				String errmsg= "ThreadLock.lock() unsafe mode: Counter invalid (<= 0): This should never happen. Set lock to safe mode!";
				if ( AWXU.errorHandler != null ) AWXU.errorHandler.error( errmsg );
				System.Diagnostics.Debug.Assert( !UseAssertions, errmsg );
			}
		
			else if ( lockCount % RecursionWarningThreshold == 0  )
			{
				if ( AWXU.errorHandler != null ) 
					AWXU.errorHandler.warning( "ThreadLock.lock() Warning: Recursion depth " + lockCount + ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code!");
			}
										
			// end of unsafe version of this method
			return;
		}

		// get start time		
		long time=  ( WaitALoxWarningLimit > 0)	?	( Ticker.Now() )
												:	0L;

		// get current thread		
		Thread thisThread= Thread.CurrentThread;
			
		// synchronize on mutex
		lock ( mutex )
		{
			// we already own the thread
			if( owner == thisThread ) 
			{
				// we are still increasing the lockCount  
				lockCount=  recursiveMode 	? lockCount + 1 
											: 1;
				// reached warning limit
				if ( lockCount % RecursionWarningThreshold == 0  )
				{
					if ( AWXU.errorHandler != null ) 
						AWXU.errorHandler.warning( "ThreadLock.lock() Warning: Recursion depth " + lockCount + ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code!");
				}
											
				return;
			}
			
			// we do not own this thread, wait until lock is free
			while( owner != null )
			{
				try					  
				{
					Monitor.Wait( mutex );
				}
				catch(Exception e) 
				{
					if ( AWXU.errorHandler != null ) AWXU.errorHandler.warning( "ThreadLock.lock() waiting got interrupted. Exception: " + e.Message );
				}
			}
			
			// take control
			owner=		thisThread;
			lockCount=	1;

		} // synchronized
		
		time=	Ticker.Now() - time;
		if ( WaitALoxWarningLimit > 0 &&  WaitALoxWarningLimit <  time ) 
		{
			if ( AWXU.errorHandler != null ) 
				AWXU.errorHandler.warning( "ThreadLock.lock() took " + time +  "ms, which exceeds given limit of " + WaitALoxWarningLimit 
											+ " ms. Change your codes critical section length if possible. Thread ID/Name: " + thisThread.ManagedThreadId + "/" + thisThread.Name );
		}
		
	}	
	
	/** ***********************************************************************************************
	 * <summary>
	 * Releases ownership of this object. If lock() was called multiple times before, the same number
	 * of calls to this method have to be performed to release ownership.
	 * <summary>
	 **************************************************************************************************/
	public void Release()		
	{
		// are we in unsafe mode?
		if ( mutex == null )
		{
			// not locked
			if( recursiveMode && lockCount == 0 )
			{
				String errmsg= "ThreadLock.unlock() without having the lock (in unsafe mode). This must never happen, check your code, set lock to safe mode!";
				if ( AWXU.errorHandler != null ) AWXU.errorHandler.error( errmsg );
				System.Diagnostics.Debug.Assert( !UseAssertions, errmsg );
			}
		
			// we are still decreasing the lockCount
			lockCount=  recursiveMode 	? lockCount - 1
										: 0;
			
			// end of unsafe version of this method
			return;
		}
		
		// synchronize on mutex
		lock ( mutex )
		{
			// not locked
			if( lockCount == 0 )
			{
				String errmsg= "ThreadLock.unlock() without having the lock. This must never happen, check your code!";
				if ( AWXU.errorHandler != null ) AWXU.errorHandler.error( errmsg );
				System.Diagnostics.Debug.Assert( !UseAssertions, errmsg );
			}
		
			// decreasing the lockCount
			lockCount=  recursiveMode 	? lockCount - 1
										: 0;
			
			// release and notify next waiting thread
			if( lockCount == 0 )
			{
				owner= null;
				Monitor.Pulse( mutex );
			}
		} // synchronized
	}

	/** ***********************************************************************************************
	 * <summary>	Returns a  String that represents this object. </summary>
	 * <returns>	A String that represents this object. </returns>
	 **************************************************************************************************/
	public override String ToString()		
	{
		return 		( owner != null ? owner.ToString() : "null") 
				 +	", locks=" + lockCount 
				 +	", unsafe mode= " + ( mutex==null) 
				 +	", recursive=" +recursiveMode;
	}
	
	/** ***********************************************************************************************
	 * <summary>
	 *  If parameter is true, the whole locking system is disabled. The only objective here is to
	 *  to gain execution speed, as thread synchronization causes relatively expensive system calls.
	 *  Use this method only if you are 100% sure that your (otherwise) critical section are executed
	 *  in a single threaded environment. And: "relative expensive" means: they are not really expensive.
	 *  This only for the rare case that your critical section is very, very frequently executed.
	 * </summary>
	 * <param name="setUnsafe">	If true, ThreadLock is set unsafe, safe otherwise.</param>
	 *************************************************************************************************/
	public void SetUnsafe( bool setUnsafe )		
	{
		// are we in unsafe mode?
		if ( mutex == null )
		{ 
			// already locked? ALox Error
			if( lockCount != 0 )
			{
				String errmsg= "ThreadLock.setUnsafe() while already (unsafely) locked. This must never happen, check your code!";
				if ( AWXU.errorHandler != null ) AWXU.errorHandler.error( errmsg );
				System.Diagnostics.Debug.Assert( !UseAssertions, errmsg );
			}
		
			//  switch on?
			if( ! setUnsafe )
				mutex= new Object();
				
			// end of unsafe version of this method
			return;
		}
		
		// synchronize on mutex
		lock ( mutex )
		{
			// already locked? ALox Error
			if( owner != null )
			{
				String errmsg= "ThreadLock.setUnsafe() while already locked. This must never happen, check your code!";
				if ( AWXU.errorHandler != null ) AWXU.errorHandler.error( errmsg );
				System.Diagnostics.Debug.Assert( !UseAssertions, errmsg );
			}
		
			//  switch off?
			if( setUnsafe )
				mutex= null;
		}
	
	}

	/** ***********************************************************************************************
	 * <summary>	Query if this instance was set to unsafe mode. </summary>
	 * <returns>	True if unsafe, false if not. </returns>
	 **************************************************************************************************/
	public bool IsUnsafe()
	{
		return ( mutex == null );
	}

}// class ThreadLock
	

} // namespace / EOF
