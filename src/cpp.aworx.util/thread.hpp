// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// include AWXU main header first...
#if !defined (HPP_AWORX_UTIL_AWXU)
    #include "awxu.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_UTIL_THREAD
#define HPP_AWORX_UTIL_THREAD 1



// #################################################################################################
// class Runnable
// #################################################################################################


#ifdef AWXU_FEAT_THREADS


// -------------------------------------------------------------------------------------------------
// --- includes
// -------------------------------------------------------------------------------------------------
#if !defined (HPP_AWORX_UTIL_ASTRING)
    #include "astring.hpp"
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

#endif // AWXU_FEAT_THREADS

namespace aworx {
namespace       util {

/** ************************************************************************************************
 *  This class mimics Interface Runnable of the Java runtime library.
 **************************************************************************************************/
class Runnable
{
    public:
        /**  Destructor. Virtual as this is an abstract interface class.  */
        virtual                    ~Runnable()        {}

        /**  The method invoked by the Thread that this runnable is associated with.  */
        virtual        void        Run()                                    = 0;
};

// #################################################################################################
// class Thread
// #################################################################################################

/** ************************************************************************************************
 *  This class mimics class Thread of the Java runtime library.
 **************************************************************************************************/
class Thread : public Runnable
{
#ifdef AWXU_FEAT_THREADS
    // #############################################################################################
    // AWXU library initialization
    // #############################################################################################
    private:
        friend  class AWXU;

        /**  Initializes AWXU thread logic.   */
        static void _awxu_init_lib_thread();

        /**  Frees resources and shuts down the AWXU thread logic.  */
        static void _awxu_destruct_lib_thread();

    // #############################################################################################
    // static functionality
    // #############################################################################################
    protected:
        /**  A counter to provide thread IDs for System threads  */
        static    int                                     nextSystemThreadId;

        /**  A counter to provide thread IDs for AWXU threads  */
        static    int                                     nextThreadId;

        /**  A mutex to protect the static stuff.  */
        static    std::mutex                              mutex;

        /**  The internal mapping of C++ 11 thread ids to Thread objects.  */
        static    std::map<std::thread::id, Thread*>      threadMap;


    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /**  Indicates that a thread object represents system threads (aka a thread
         * that was not created using AWXU Thread.  */
        bool                        isSystemThread                                          =false;

        /**  The internal C++ 11 thread object.  */
        std::thread*                c11Thread                                               =nullptr;

        /**  The internal C++ 11 thread id.  */
        std::thread::id             c11ID;

        /**  Internal flag to indicate if thread is alive.  */
        bool                        isAliveFlag                                             =false;

        /**  The runnable to execute.  */
        Runnable*                   runnable                                                =0;

        /**  The id of the thread.  */
        int                         id                                                      =0;

        /**  The name of the thread.  */
        AString64                   name;

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
        AWXU_API static    Thread*            CurrentThread();

    // #############################################################################################
    // Constructors, destructor
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  Internal constructor for Thread objects representing system threads (aka threads that
         *  were not created using class Thread from AWXU.
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
        AWXU_API             Thread()                  : Thread( nullptr, "" )       {}

        /** ****************************************************************************************
         *  Constructor without a parameter specifying a Runnable. Such thread will not execute any
         *  code unless a specialized class is derived that overwrites the Run method.
         *
         * @param name The designated name of the thread. If the name provided is empty or,
         *             nullptr, the name of the thread will be set to match a string representation
         *             of the thread id.
         ******************************************************************************************/
        AWXU_API            Thread( const char* name ) : Thread( nullptr, name )     {}

        /** ****************************************************************************************
         *  Constructor with provision of a Runnable 'target'. The Run method of 'target' will be
         *  executed upon thread start, unless this class is specialized an its own Run() method is
         *  overwritten.
         * @param target  The target to execute when the thread runs.
         * @param name    (Optional) The designated name of the thread. If the name provided is,
         *                empty the name of the thread will be set to match a string representation
         *                of the thread id.
         ******************************************************************************************/
        AWXU_API            Thread(Runnable* target , const char* name= "" );


        /** ****************************************************************************************
         *  The destructor blocks, if the thread was started and is still running. Blocking lasts
         *  until the thread's end of execution.
         *  Declared virtual, as inherited from Runnable.
         ******************************************************************************************/
        AWXU_API  virtual   ~Thread();


    // #############################################################################################
    // Runnable Interface implementation
    // #############################################################################################

        /**  If we have a runnable, execute its run() method. Does nothing else.  */
        virtual void        Run()                       { if (runnable)    runnable->Run();    }


    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         *  Returns the id of this Thread. Systems threads have IDs below 0, AWXU generated threads
         *  have positive IDs and start with 1.
         *
         * @return    The AWXU id of the thread.
         ******************************************************************************************/
                  int           GetId()                                 { return id;          }

        /** ****************************************************************************************
         *  Returns the name of the thread. An AWXU thread can have any name that is given to it and
         *  such name can be changed any time. In fact, such names are for debugging and logging
         *  purposes only.
         *
         * @return  Returns the name of the thread.
         ******************************************************************************************/
                  const char*   GetName()                               { return name.Buffer(); }

        /** ****************************************************************************************
         *  Sets the name of the thread. An AWXU thread can have any name that is given to it and
         *  such name can be changed any time. In fact, such names are for debugging and logging
         *  purposes only.
         *
         * @param newName    The name that the Thread should hold.
         ******************************************************************************************/
                  void          SetName( const char* newName )          { name=    newName;   }

        /** ****************************************************************************************
         *  Returns true, if this thread was started and is still running. If false is
         *  returned, the thread object can be safely deleted, without causing a blocking operation.
         *
         * @return True if this thread was started previously and is still running.
         ******************************************************************************************/
                  bool          IsAlive()                               { return isAliveFlag; }

        /** ****************************************************************************************
         *  Starts the execution of the thread. The thread's Run method is invoked, which
         *  (if not overwritten) invokes the Run method of any given Runnable. After returning from
         *  the method, unless the thread #IsAlive will return true.
         ******************************************************************************************/
        AWXU_API  void          Start();


// #############################################################################################
// Unthreaded version
// #############################################################################################
#else
    public:
        AWXU_API static    Thread*            CurrentThread() { return nullptr; };
        AWXU_API           Thread()       {}
        AWXU_API            Thread( const char* )  {}
        AWXU_API            Thread(Runnable*, const char* = "" ) {}
        AWXU_API  virtual   ~Thread()                    {}
        virtual void        Run()            {}
           int           GetId()                                 { return 0; }

             const char*   GetName()                               { return ""; }

                  void          SetName( const char* )          {}
                  bool          IsAlive()                               { return false; }
                  void          Start()                     {}
#endif // AWXU_FEAT_THREADS
};



}}  // namespace aworx::util



#endif // HPP_AWORX_UTIL_THREAD
