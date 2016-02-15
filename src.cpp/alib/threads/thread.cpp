// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALIB_THREADS_THREAD)
    #include "thread.hpp"
#endif

using namespace std;

namespace aworx {
namespace           lib {
namespace                   threads {

// #################################################################################################
// class Thread static part
// #################################################################################################

// static variables
// (attn: these variables have to be placed in the cpp file before the init-function below)
#if defined(ALIB_FEAT_THREADS)
    map<thread::id, Thread*>    Thread::threadMap;
    mutex                       Thread::mutex;
#else
    Thread*                     Thread::noThreadsCompilationMainThread= nullptr;
#endif

int                             Thread::nextSystemThreadId                                     = -1;
int                             Thread::nextThreadId                                           =  1;

// static library initialization code ( invoked by ALIB::Init() )
void Thread::_Init_ALib()
{
    #if !defined( ALIB_FEAT_THREADS )
        Thread::noThreadsCompilationMainThread= new Thread();
        Thread::noThreadsCompilationMainThread->id= -1;
    #endif


    // create the current thread as an object within our thread map
    Thread* main= Thread::CurrentThread();
            main->SetName( "MAIN" );
    ALIB_ASSERT_ERROR( main->GetId() == -1,
       "Error initializing threads. Probably forbidden repeated initialization from different thread." );
}


// static library destruction code ( invoked by ALIB::TerminationCleanUp() )
void Thread::_Terminate_ALib()
{
    #if defined(ALIB_FEAT_THREADS)
        Thread::mutex.lock();
            ALIB_ASSERT_WARNING( Thread::threadMap.size() > 0,
                                 "Thread system deinitialized without prior initialization." );

            // we should have exactly one thread and this is the system thread
            size_t qtyThreads= Thread::threadMap.size();
            ALIB_ASSERT_WARNING( qtyThreads != 0, "ALib termination: main thread not registered." );
            ALIB_ASSERT_WARNING( qtyThreads == 1, "ALib termination: Can not shutdown gracefully due to open threads." );
            if( qtyThreads != 1 )
            {
                Thread::mutex.unlock();
                return;
            }

            Thread* main= Thread::threadMap.begin()->second;
            #if defined(ALIB_DEBUG)
                int mainThreadID= main->id;
                if ( mainThreadID != -1 )
                {
                    Thread::mutex.unlock();
                        ALIB_ASSERT_WARNING( main->id == -1, "ALib Termination: last thread id != -1 (not system thread)" );
                    Thread::mutex.lock();
                }
            #endif
            delete main;

        Thread::mutex.unlock();
    #else
        ALIB_ASSERT_ERROR( Thread::noThreadsCompilationMainThread != nullptr,
                           "Thread system deinitialized without prior initialization." );
        if ( Thread::noThreadsCompilationMainThread != nullptr )
        {
            delete Thread::noThreadsCompilationMainThread;
            Thread::noThreadsCompilationMainThread= nullptr;
        }
    #endif
}

Thread::Thread( bool BecomesInternalThread )
{
    (void) BecomesInternalThread;

    // this is a system thread, no matter what the parameter says. In fact, the parameter is only
    // for providing a different, internal constructor
    ALIB_ASSERT_ERROR ( BecomesInternalThread, "Parameter must not be false. Illegal use" );
}


Thread* Thread::CurrentThread()
{
    Thread* result= nullptr;

    #if defined(ALIB_FEAT_THREADS)
        // search current in map
        auto    c11ID=  this_thread::get_id();
        mutex.lock();
        {
            auto search=  Thread::threadMap.find( c11ID );

            // found
            if ( search != Thread::threadMap.end() )
                result= search->second;

            // not found, this is a system thread!
            else
            {
                result=        new Thread( true );
                result->id=    nextSystemThreadId--;
                result->SetName( String32("SYS_") << result->id );
                Thread::threadMap.insert( make_pair( c11ID, result) );
            }
        }
        mutex.unlock();
    #else
        result= noThreadsCompilationMainThread;
    #endif

    return result;
}

// #################################################################################################
// class Thread
// #################################################################################################
Thread::Thread( Runnable* target , const String& name )
: runnable(target)
, name(name)
{
    // get myself an ID
    #if defined(ALIB_FEAT_THREADS)
    mutex.lock();
    #endif
    {
        id=  nextThreadId++;
        if ( this->name.IsEmpty() )
            this->name << '(' << id << ')';
    }
    #if defined(ALIB_FEAT_THREADS)
    mutex.unlock();
    #endif
}

Thread::~Thread()
{
    #if defined(ALIB_FEAT_THREADS)
    if (c11Thread)
    {
        if( c11Thread->joinable() )
            c11Thread->join();
        mutex.lock();
        {
            ALIB_ASSERT_RESULT_EQUALS( Thread::threadMap.erase( c11ID ), 1);
        }
        mutex.unlock();

        delete c11Thread;
    }
    #endif
}

#if !defined( IS_DOXYGEN_PARSER )
void _Thread__Start( Thread* t )
{
    t->Run();
    t->isAliveFlag= false;
}
#endif

void  Thread::Start()
{
    if ( c11Thread != nullptr )
    {
        ALIB_ERROR_AS( "Thread already started. (" << GetId() <<  '/' << GetName() << ')')
        return;
    }

    if ( id <= 0 )
    {
        ALIB_ERROR_AS( "System threads can not be started. (" << GetId() <<  '/' << GetName() << ')' )
        return;
    }

    isAliveFlag= true;

    #if defined(ALIB_FEAT_THREADS)
        mutex.lock();
        {
            c11Thread=    new std::thread( _Thread__Start, this );
            c11ID=        c11Thread->get_id();

            Thread::threadMap.insert( make_pair( c11ID, this) );
        }
        mutex.unlock();
    #else
            c11Thread=    this;
            isAliveFlag=  false;
            ALIB_WARNING_AS( "Starting Thread not supported. ALib is compiled with compilation symbol ALIB_FEAT_THREADS_OFF" )
    #endif
}


}}}// namespace aworx::lib::threads


