package com.aworx.util;


/**********************************************************************************************//**
 * This class allows *mutal exclusive access* to resources that the using software agrees on to
 * protect with a certain instance hereof. In other words, access to certain resources of a
 * software that has to be thread safe, can be protected if each thread (aka critical section
 * code) uses the same ThreadLock to control the access to.
 * 
 * If a lock() is not followed by a corresponding unlock(), other threads will not be able to
 * gain control to this object and will wait endlessly (deadlock situation). To avoid this, it
 * is a good practice to embed pairs of lock()/unlock() calls into try/finaly statements as
 * follows:
 * 
 *     try { tl.lock(); ...critical section code .... } finally { tl.unlock() }
 * 
 * ThreadLock uses an internal counter to allow multiple calls to lock() and to be freed only
 * when a same amount of unlock() calls are performed. This behavior can be switched off by a
 * constructor parameter. If switched off, each recursive lock() calls will not be counted and
 * each call to unlock() will instantly free the mutex. This mode is even less recommended than
 * using this class in recursive mode.
 * 
 * Furthermore, ThreadLock allows to disable locking using setUnsafe(). The objective here is to
 * gain execution speed, as thread synchronization causes relatively expensive system calls.
 * 
 * Caution: Use this class with great care. Deadlocks are not easy to detect and debug. Use this
 * class only if standard synchronization of the JAVA language seems too limited and mechanisms
 * like the class uses internally would need to be implemented.
 **************************************************************************************************/
public class ThreadLock
{
	// #################################################################################################
	// Public fields 
	// #################################################################################################

	/**
     * Flag to use assert() to detected misuse in debug mode. Default is on, and you should 
	 * keep it on! 
	 */
	public	boolean			useAssertions										= true;
				
	/**
	 * This is a threshold that causes lock() to log a warning if acquiring the access using method lock()
	 * takes longer than the given number of milliseconds. To disable such messages, set this value to 0.
	 * Default is 1 second. Measured in ticks, see class Ticker.
	 */
	public	long	 		waitALoxWarningLimit								= Ticker.fromMillis( 1000 );
				
	/**
	 * Limit of recursions. If limit is reached or a multiple of it, an error logged using ALox.  
	 */
	public	int	 			recursionWarningThreshold							= 10;			

	// #################################################################################################
	// Protected fields 
	// #################################################################################################

	/**  Flag if recursion support is on. If not, nested locks are not counted. */
	protected boolean 		recursiveMode;			

	/**  Counter for the number of lock() calls of the current thread. */
	protected int 			lockCount;
			 
	/**  Counter for the number of lock() calls of the current thread. */
	protected Thread 		owner;

	/**  The internal object to lock on. */
	protected Object 		mutex;
				
	// #################################################################################################
	// Constructors 
	// #################################################################################################

    /**********************************************************************************************//**
     * Create a ThreadLock that allows recursion.
     **************************************************************************************************/
	public ThreadLock()
	{
		constructor( true, false);	
	}

    /**********************************************************************************************//**
     * Create a ThreadLock that allows recursion. A warning will be given (ALox Error) when the
     * given recursion level is reached (and each multiple of it).
     *
     * @param recursiveMode Flag if recursion support is on. If not, nested locks are not counted.
     **************************************************************************************************/
	public ThreadLock( boolean recursiveMode )
	{
		constructor( recursiveMode, false);	
	}

    /**********************************************************************************************//**
     * Create a ThreadLock that allows recursion. A warning will be given (ALox Error) when the
     * given recursion level is reached (and each multiple of it). In addition the lock can be
     * initialized to be unsafe, which means the locking critical sections is disabled.
     *
     * @param recursiveMode Flag if recursion support is on. If not, nested locks are not counted.
     * @param setUnsafeMode True to set this unsafe. Please don't!
     **************************************************************************************************/
	public ThreadLock( boolean recursiveMode, boolean setUnsafeMode  )
	{
		constructor( recursiveMode, setUnsafeMode);	
	}

    /**********************************************************************************************//**
     * Used by the Constructors to create an instance.
     *
     * @param recursiveMode Flag if recursion support is on. If not, nested locks are not counted.
     * @param setUnsafeMode True to set this unsafe. Please don't!
     **************************************************************************************************/
	@SuppressWarnings ("hiding") protected 
	void constructor( boolean recursiveMode, boolean setUnsafeMode )
	{
		// save parameters
		this.recursiveMode= 			recursiveMode;
		
		// set safeness
		setUnsafe( setUnsafeMode );
	}

	// #################################################################################################
	// Interface 
	// #################################################################################################

    /**********************************************************************************************//**
     * Thread which invokes this method gets registered  as the current owner of this object, until
     * the same thread releases the ownership invoking unlock(). In the case that this object is
     * already owned by another thread, the invoking thread is suspended until ownership can be
     * gained. Multiple (nested) calls to this method are counted and the object is only released
     * when the same number of unlock() calls have been made.
     **************************************************************************************************/
	public void aquire()		
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
				assert !useAssertions : errmsg;
			}
		
			else if ( lockCount % recursionWarningThreshold == 0  )
			{
				if ( AWXU.errorHandler != null ) 
					AWXU.errorHandler.warning( "ThreadLock.lock() Warning: Recursion depth " + lockCount + " To prevent this, change ThreadSafe.recursionWarningThreshold." );
			}
										
			// end of unsafe version of this method
			return;
		}

		// get start time		
		long time=  ( waitALoxWarningLimit > 0)	?	( Ticker.now() )
												:	0L;

		// get current thread		
		Thread thisThread= Thread.currentThread();
			
		// synchronize on mutex
		synchronized ( mutex )
		{
			// we already own the thread
			if( owner == thisThread ) 
			{
				// we are still increasing the lockCount  
				lockCount=  recursiveMode 	? lockCount + 1 
											: 1;
				// reached warning limit
				if ( lockCount % recursionWarningThreshold == 0  )
				{
					if ( AWXU.errorHandler != null ) 
						AWXU.errorHandler.warning( "ThreadLock.lock() Warning: Recursion depth " + lockCount + " To prevent this, change ThreadSafe.recursionWarningThreshold.");
				}
											
				return;
			}
			
			// we do not own this thread, wait until lock is free
			while( owner != null )
			{
				try					  
				{
					mutex.wait();
				}
				catch(InterruptedException e) 
				{
					if ( AWXU.errorHandler != null ) 
						AWXU.errorHandler.warning( "ThreadLock.lock() waiting got interrupted. Exception: " + e.getMessage() );
				}
			}
			
			// take control
			owner=		thisThread;
			lockCount=	1;

		} // synchronized
		
		time= Ticker.now() - time; 
		if ( waitALoxWarningLimit > 0 &&  waitALoxWarningLimit <  time ) 
		{
			if ( AWXU.errorHandler != null ) 
				AWXU.errorHandler.warning( "ThreadLock.lock() took " + time +  "ms, which exceeds given limit of " + waitALoxWarningLimit 
											+ " ms. Change your codes critical section length if possible. Thread ID/Name: " + thisThread.getId() + "/" + thisThread.getName() );
		}
		
	}	

    /**********************************************************************************************//**
     * Releases ownership of this object. If lock() was called multiple times before, the same
     * number of calls to this method have to be performed to release ownership.
     **************************************************************************************************/
	public void release()		
	{
		// are we in unsafe mode?
		if ( mutex == null )
		{
			// not locked
			if( recursiveMode && lockCount == 0 )
			{
				String errmsg= "ThreadLock.unlock() without having the lock (in unsafe mode). This must never happen, check your code, set lock to safe mode!";
				if ( AWXU.errorHandler != null ) AWXU.errorHandler.error( errmsg );
				assert !useAssertions : errmsg;
			}
		
			// we are still decreasing the lockCount
			lockCount=  recursiveMode 	? lockCount - 1
										: 0;
			
			// end of unsafe version of this method
			return;
		}
		
		// synchronize on mutex
		synchronized ( mutex )
		{
			// not locked
			if( lockCount == 0 )
			{
				String errmsg= "ThreadLock.unlock() without having the lock. This must never happen, check your code!";
				if ( AWXU.errorHandler != null ) AWXU.errorHandler.error( errmsg );
				assert !useAssertions : errmsg;
			}
		
			// decreasing the lockCount
			lockCount=  recursiveMode 	? lockCount - 1
										: 0;
			
			// release and notify next waiting thread
			if( lockCount == 0 )
			{
				owner= null;
				mutex.notify();
			}
		} // synchronized
	}

    /**********************************************************************************************//**
     * Returns the current owner of the thread. This method should not be used to check if a lock is
     * used or not. However, it can. But software should be designed in a way that ownership does
     * not need to be tested. This method is build in for debugging purposes only.
     *
     * @return  A String that represents this instance.
     **************************************************************************************************/
	@Override public String toString()		
	{
		return 		( owner != null ? owner.toString() : "null") 
				 +	", locks=" + lockCount 
				 +	", unsafe mode= " + ( mutex==null) 
				 +	", recursive=" +recursiveMode;
	}

    /**********************************************************************************************//**
     * If parameter is true, the whole locking system is disabled. The only objective here is to to
     * gain execution speed, as thread synchronization causes relatively expensive system calls. Use
     * this method only if you are 100% sure that your (otherwise) critical section are executed in
     * a single threaded environment. And: "relative expensive" means: they are not really
     * expensive. This only for the rare case that your critical section is very, very frequently
     * executed.
     *
     * @param setUnsafe true to set unsafe.
     **************************************************************************************************/
	public void setUnsafe( boolean setUnsafe )		
	{
		// are we in unsafe mode?
		if ( mutex == null )
		{ 
			// already locked? ALox Error
			if( lockCount != 0 )
			{
				String errmsg= "ThreadLock.setUnsafe() while already (unsafely) locked. This must never happen, check your code!";
				if ( AWXU.errorHandler != null ) AWXU.errorHandler.error( errmsg );
				assert !useAssertions : errmsg;
			}
		
			//  switch on?
			if( ! setUnsafe )
				mutex= new Object();
				
			// end of unsafe version of this method
			return;
		}
		
		// synchronize on mutex
		synchronized ( mutex )
		{
			// already locked? ALox Error
			if( owner != null )
			{
				String errmsg= "ThreadLock.setUnsafe() while already locked. This must never happen, check your code!";
				if ( AWXU.errorHandler != null ) AWXU.errorHandler.error( errmsg );
				assert !useAssertions : errmsg;
			}
		
			//  switch off?
			if( setUnsafe )
				mutex= null;
		}
	
	}

    /**********************************************************************************************//**
     * Query if this instance was set to unsafe mode.
     *
     * @return  True if unsafe, false if not.
     **************************************************************************************************/
	public boolean IsUnsafe()
	{
		return ( mutex == null );
	}

}// class ThreadLock
	
