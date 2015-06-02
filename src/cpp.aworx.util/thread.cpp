// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#include "stdafx_awxu.h"


#if !defined (HPP_AWORX_UTIL_THREAD)
    #include "thread.hpp"
#endif

#ifdef AWXU_FEAT_THREADS

#if !defined (HPP_AWORX_UTIL_ASTRING)
    #include "astring.hpp"
#endif

using namespace std;

namespace aworx {
namespace       util {


// #################################################################################################
// class Thread static part
// #################################################################################################

// static variables
// (attn: these variables have to be placed in the cpp file before the init-function below)
map<thread::id, Thread*>    Thread::threadMap;
mutex                       Thread::mutex;
int                         Thread::nextSystemThreadId;
int                         Thread::nextThreadId;

// static library initialization code ( invoked by AWXU::Init() )
void Thread::_awxu_init_lib_thread()
{
    Thread::nextSystemThreadId=   -1;
    Thread::nextThreadId=          1;

    // create the current thread as an object within our thread map
    Thread* main= Thread::CurrentThread();
            main->SetName( "MAIN" );
    AWXU_ASSERT( main->GetId() == -1 );
}


// static library destruction code ( invoked by AWXU::TerminationCleanUp() )
void Thread::_awxu_destruct_lib_thread()
{
    Thread::mutex.lock();
        // we should have exactly one thread and this is the system thread
        int qtyThreads= Thread::threadMap.size();
        AWXU_ASSERT_MSG( qtyThreads != 0, "AWXU Termination: main thread not registered." );
        AWXU_ASSERT_MSG( qtyThreads == 1, "AWXU Termination: Can not shutdown gracefully. Due to open threads." );
        if( qtyThreads != 1 )
        {
            Thread::mutex.unlock();
            return;
        }

        Thread* main= Thread::threadMap.begin()->second;
        #if defined(AWXU_DEBUG)
            int mainThreadID= main->id;
            if ( mainThreadID != -1 )
            {
                Thread::mutex.unlock();
                    AWXU_ASSERT_MSG( main->id == -1, "AWXU Termination: last thread id != -1 (not system thread)" );
                Thread::mutex.lock();
            }
        #endif
        delete main;

    Thread::mutex.unlock();
}

Thread::Thread( bool BecomesInternalThread )
{
    // this is a system thread, no matter what the parameter says. In fact, the parameter is only
    // for providing a different, internal constructor
    AWXU_ASSERT_MSG ( BecomesInternalThread, "Parameter must not be false. Illegal use" );
    isSystemThread= BecomesInternalThread;
    if ( isSystemThread == false )
    {
        isSystemThread= true;
        if( AWXU::AcquireErrorHandler() )
            AWXU::Error( "Thread::Thread(false) not supported" );
    }
}


Thread* Thread::CurrentThread()
{
    // search current in map
    Thread* result= nullptr;
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
            result->id=    nextSystemThreadId --;
            result->SetName( (AString16("SYS_") << result->id) .Buffer() );
            Thread::threadMap.insert( make_pair( c11ID, result) );
        }
    }
    mutex.unlock();

    return result;
}

// #################################################################################################
// class Thread
// #################################################################################################
Thread::Thread( Runnable* target , const char* name )
{
    // save parameters
    this->runnable= target;
    this->name.Append( name) ;

    // get myself an ID
    mutex.lock();
    {
        id=  nextThreadId++;
        if ( this->name.Length() == 0 )
            this->name << '(' << id << ')';
    }
    mutex.unlock();

}

Thread::~Thread()
{
    if (c11Thread)
    {
        if( c11Thread->joinable() )
            c11Thread->join();
        mutex.lock();
        {
            AWXU_ASSERT_RESULT_EQUALS( Thread::threadMap.erase( c11ID ), 1);
        }
        mutex.unlock();

        delete c11Thread;
    }
}

#if !defined( DOXYGEN_OMIT_THIS_PLEASE )
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
        if( AWXU::AcquireErrorHandler() )
        {
            AString128  errormsg;
            errormsg << "Thread already started. id=" << GetId() <<  '/' << GetName();
            AWXU::Warning( errormsg.Buffer() );
        }
        return;
    }

    isAliveFlag= true;

    mutex.lock();
    {
        c11Thread=    new std::thread( _Thread__Start, this );
        c11ID=        c11Thread->get_id();

        Thread::threadMap.insert( make_pair( c11ID, this) );
    }
    mutex.unlock();
}


}}// namespace aworx::util


#endif // AWXU_FEAT_THREADS
