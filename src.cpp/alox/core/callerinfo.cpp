// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "callerinfo.hpp"
#include <iostream>

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif

using namespace std;
using namespace aworx;
using namespace aworx::lib;
using namespace aworx::lib::strings;
using namespace aworx::lox::core;


#if defined(ALIB_FEAT_THREADS)
    CallerInfo::CallerInfo( const std::map<int, String32>&  threadDictionary )
    :    threadDictionary(threadDictionary)
    {
    }
#else
    CallerInfo::CallerInfo()
    {
    }
#endif



void CallerInfo::AcquireAndSet ( const TString& sourceFileName, int lineNumber, const TString& methodName )
{
    recursionCounter++;

    ALIB_ASSERT( recursionCounter != 4 );

    // only the first call will store the values
    if ( recursionCounter == 1 )
    {
        TimeStamp.Set();
        lazyFlagThreadNameAndID=        false;

        this->SourceFileName=    sourceFileName;
        this->LineNumber=        lineNumber;
        this->MethodName=        methodName;
    }
}

#if defined(ALIB_FEAT_THREADS)

    const String&  CallerInfo::getThreadNameAndID( int* id )
    {
        if ( !lazyFlagThreadNameAndID )
        {
            lazyFlagThreadNameAndID= true;

            // get current thread
            threads::Thread* thread=    threads::Thread::CurrentThread();
            threadID=        thread->GetId();

            // do we have a dictionary entry?
            auto it= threadDictionary.find( threadID );
            if (it != threadDictionary.end() )
                threadName= it->second;
            else
                threadName= thread->GetName();
        }

        // return id and name
        if (id != nullptr)
            *id=    threadID;
        return    threadName;
    }

#endif
