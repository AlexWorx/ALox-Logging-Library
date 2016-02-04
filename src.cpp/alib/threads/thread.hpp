// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// check for alib.hpp already there but not us
#if !defined (HPP_AWORX_LIB_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_AWORX_LIB_THREADS_THREAD)
    #error "Header already included"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif



// then, set include guard
#ifndef HPP_AWORX_LIB_THREADS_THREAD
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_AWORX_LIB_THREADS_THREAD 1
#endif


// #################################################################################################
// class Runnable
// #################################################################################################


// #################################################################################################
// includes
// #################################################################################################
#if defined(ALIB_FEAT_THREADS)

    #if !defined (HPP_AWORX_LIB_STRINGS_ASPREALLOC)
        #include "alib/strings/asprealloc.hpp"
    #endif

    #if !defined (_GLIBCXX_MAP) && !defined(_MAP_)
        #include <map>
    #endif

    #if !defined (_GLIBCXX_MUTEX) && !defined(_MUTEX_)
        #include <mutex>
    #endif

    #if !defined (_GLIBCXX_CONDITION_VARIABLE) && !defined(_CONDITION_VARIABLE_)
        #include <condition_variable>
    #endif

    #if !defined (_GLIBCXX_THREAD) && !defined (_THREAD_ )
        #include <thread>
    #endif

#endif // ALIB_FEAT_THREADS

namespace aworx {
namespace           lib {


/**
 *  This namespace of ALib holds classes that are providing an interface into
 *  multi threaded programming. The design of the classes tries to mimic the basic thread
 *  interface of the Java language.
 *
 *  It is important to understand that
 *  (following \ref aworx::lib "the principle design goals of ALib")
 *  multi threading support of ALib is non intrusive in respect to multi-threading
 *  mechanisms of other C++ libraries and/or the underlying operating system.
 *  This means that a software entity that uses this library is not at all bound to use the thread
 *  classes found within this namespace.
 *
 *  In contrast, using the classes found here, is of-course optional. ALib usually
 *  provides a certain level of "source compatibility" between the programming languages
 *  C#, Java and C++.
 *
 *  It is no problem, to have threads started using different methods and libraries than the
 *  one found here, as long that such threads become "native" operation system threads.
 *  If later such a thread uses method
 *  \ref aworx::lib::threads::Thread::CurrentThread() "Thread::CurrentThread()",
 *  a corresponding \ref aworx::lib::threads::Thread "Thread" object of ALib
 *  is created internally and returned.
 *  This way, the externally created thread is automatically "registered" with ALib.
 *  If not stated differently in the detailed documentation, from this point in time,
 *  the thread can be interfaced with ALib classes in the same manner as if it was created
 *  using them. The same or similar should be \c true for the opposite situation.
 *
 *  Thread support of ALib can be disabled, respectively enabled, using compiler symbols
 *  #ALIB_FEAT_THREADS_OFF and #ALIB_FEAT_THREADS_ON.
 *  When support is switched off, classes
 *  \ref aworx::lib::threads::Thread "Thread" and
 *  \ref aworx::lib::threads::Runnable "Runnable" are not available. However, the classes
 *  \ref aworx::lib::threads::ThreadLockNR "ThreadLockNR" and
 *  \ref aworx::lib::threads::ThreadLock "ThreadLock" are!
 *  Their interface remains the same, but they do not perform any locking. Due to this behavior,
 *  it is possible to write code that performs due locking while still, in single threaded
 *  compilation, the code does not suffer any performance drawbacks, because lock code  will be
 *  <em>pruned</em>.
 *
 */
namespace                   threads {

/** ************************************************************************************************
 *  This class mimics Interface Runnable of the Java runtime library.
 **************************************************************************************************/
class Runnable
{
    public:
        /**  Destructor. Virtual as this is an abstract interface class.  */
        virtual                   ~Runnable()        {}

        /**  The method invoked by the Thread that this runnable is associated with.  */
        virtual        void        Run()                                    = 0;
};

// #################################################################################################
// class Thread
// #################################################################################################

/** ************************************************************************************************
 *  This class mimics class Thread of the Java runtime library. For general information of
 *  multi-threading support provided by ALib, see #aworx::lib::threads.
 **************************************************************************************************/
class Thread : public Runnable
{
    // #############################################################################################
    // ALib Threads initialization
    // #############################################################################################
    public:
        /**
         * Initializes ALib thread logic.
         * This method should not be called directly. use
         * \ref aworx::lib::ALIB::Init "ALIB::Init" to initialize ALib
         */
        static void _Init_ALib();

        /**
         * Frees resources and shuts down ALib thread logic.
         * This method should not be called directly. use
         * \ref aworx::lib::ALIB::TerminationCleanUp "ALIB::TerminationCleanUp" to de-initialize ALib
         */
        static void _Terminate_ALib();

    // #############################################################################################
    // static functionality
    // #############################################################################################
    protected:
        /**  A counter to provide thread IDs for System threads  */
        static    int                                     nextSystemThreadId;

        /**  A counter to provide thread IDs for ALIB threads  */
        static    int                                     nextThreadId;

        #if defined(ALIB_FEAT_THREADS)
            /**  A mutex to protect the static stuff.  */
            static    std::mutex                          mutex;

            /**  The internal mapping of C++ 11 thread ids to Thread objects.  */
            static    std::map<std::thread::id, Thread*>  threadMap;
        #else
            static    Thread*                             noThreadsCompilationMainThread;
        #endif

    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        #if defined(ALIB_FEAT_THREADS)
            /**  The internal C++ 11 thread object.  */
            std::thread*        c11Thread                                                  =nullptr;

            /**  The internal C++ 11 thread id.  */
            std::thread::id     c11ID;
        #else
            void*               c11Thread                                                  =nullptr;
        #endif

        /**  Internal flag to indicate if thread is alive.  */
        bool                    isAliveFlag                                                  =false;

        /**  The runnable to execute.  */
        Runnable*               runnable                                                         =0;

        /**  The id of the thread.  */
        int                     id                                                               =0;

        /**  The name of the thread.  */
        String64                name;

        /** ****************************************************************************************
         *  Our best friend: the c function that starts us
         * @param t    Internal parameter
         ******************************************************************************************/
        friend    void _Thread__Start( Thread* t );


    // #############################################################################################
    // Public static interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Returns an object representing the thread that invoke this call.
         *
         * @return A pointer to the current Thread.
         ******************************************************************************************/
        ALIB_API static    Thread*            CurrentThread();

    // #############################################################################################
    // Constructors, destructor
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  Internal constructor for Thread objects representing system threads (aka threads that
         *  were not created using class Thread from ALIB.
         *
         * @param internal    An internal value.
         ******************************************************************************************/
        Thread( bool internal );

    public:
        /** ****************************************************************************************
         *  Constructor without parameters. As no runnable was provided, such thread will not
         *  execute any code unless a specialized class is derived that overwrites the Run method.
         *  The name of the thread will be set to match a string representation of the thread id.
         ******************************************************************************************/
        ALIB_API            Thread()                     : Thread( nullptr, "" )       {}

        /** ****************************************************************************************
         *  Constructor without a parameter specifying a Runnable. Such thread will not execute any
         *  code unless a specialized class is derived that overwrites the Run method.
         *
         * @param name The designated name of the thread. If the name provided is empty or,
         *             nullptr, the name of the thread will be set to match a string representation
         *             of the thread id.
         ******************************************************************************************/
        ALIB_API            Thread( const String& name ) : Thread( nullptr, name )     {}

        /** ****************************************************************************************
         *  Constructor with provision of a Runnable 'target'. The Run method of 'target' will be
         *  executed upon thread start, unless this class is specialized an its own Run() method is
         *  overwritten.
         * @param target  The target to execute when the thread runs.
         * @param name    (Optional) The designated name of the thread. If the name provided is,
         *                empty the name of the thread will be set to match a string representation
         *                of the thread id.
         ******************************************************************************************/
        ALIB_API            Thread(Runnable* target , const String& name= EmptyString );


        /** ****************************************************************************************
         *  The destructor blocks, if the thread was started and is still running. Blocking lasts
         *  until the thread's end of execution.
         *  Declared virtual, as inherited from Runnable.
         ******************************************************************************************/
        ALIB_API  virtual   ~Thread();


    // #############################################################################################
    // Runnable Interface implementation
    // #############################################################################################

        /**  If we have a runnable, execute its run() method. Does nothing else.  */
        virtual void        Run()                       { if (runnable)    runnable->Run();    }


    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         *  Returns the id of this Thread. Systems threads have IDs below 0, ALIB generated threads
         *  have positive IDs and start with 1.
         *
         * @return    The ALib id of the thread.
         ******************************************************************************************/
                  int           GetId()                                 { return id;          }

        /** ****************************************************************************************
         *  Returns the name of the thread. An ALIB thread can have any name that is given to it and
         *  such name can be changed any time. In fact, such names are for debugging and logging
         *  purposes only.
         *
         * @return  Returns the name of the thread.
         ******************************************************************************************/
                  const String& GetName()                               { return name; }

        /** ****************************************************************************************
         *  Sets the name of the thread. An ALIB thread can have any name that is given to it and
         *  such name can be changed any time. In fact, such names are for debugging and logging
         *  purposes only.
         *
         * @param newName    The name that the Thread should hold.
         ******************************************************************************************/
                  void          SetName( const String& newName )        { name= newName;   }

        /** ****************************************************************************************
         * Returns \c true, if this thread was started and is still running. If \c false is
         * returned, the thread object can be safely deleted, without causing a blocking operation.
         * \note
         *   For system threads (those not created using ALib thread features) \c true is
         *   returned. It can't be determined if the thread is still alive or not.
         *
         *
         * @return \c true if this thread was started previously and is still running.
         ******************************************************************************************/
                  bool          IsAlive()                               { return id <= 0 || isAliveFlag; }

        /** ****************************************************************************************
         *  Starts the execution of the thread. The thread's Run method is invoked, which
         *  (if not overwritten) invokes the Run method of any given Runnable. After returning from
         *  the method, unless the thread #IsAlive will return \c true.
         ******************************************************************************************/
        ALIB_API  void          Start();
};


}}}  // namespace aworx::lib::threads

#endif // HPP_AWORX_LIB_THREADS_THREAD
