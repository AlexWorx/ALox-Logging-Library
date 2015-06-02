// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#include "stdafx_awxu.h"
#include "callerinfo.hpp"

#if !defined (HPP_AWORX_UTIL_THREAD)
    #include "thread.hpp"
#endif


#if !defined(_GLIBCXX_IOSTREAM) && !defined(_IOSTREAM_)
    #include <iostream>
#endif

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif

using namespace std;
using namespace aworx::util;
using namespace aworx::lox::core;


#if defined(AWXU_FEAT_THREADS)

    CallerInfo::CallerInfo( const std::map<int, std::string>&    threadDictionary )
    :    threadDictionary(threadDictionary)
    {
        isFresh=    false;
    }
#else
    CallerInfo::CallerInfo()
    {
        isFresh=    false;
    }
#endif



void CallerInfo::Acquire()
{
    if ( !isFresh )
    {
        TimeStamp.Set();
        isFresh=                        true;
        lazyFlagThreadNameAndID=        false;

        SourceFileName=
        MethodName=                     nullptr;
        LineNumber=                     0;
    }
}

void CallerInfo::SetSourceInfo ( const char* sourceFileName, int lineNumber, const char* methodName )
{
    Acquire();

        this->SourceFileName=    sourceFileName;
        this->LineNumber=        lineNumber;
        this->MethodName=        methodName;
}

#if defined(AWXU_FEAT_THREADS)

    const AString&  CallerInfo::getThreadNameAndID( int* id )
    {
        if ( !lazyFlagThreadNameAndID )
        {
            lazyFlagThreadNameAndID= true;
            threadName.Clear();

            // get current thread
            Thread*    thread=    Thread::CurrentThread();
            threadID=        thread->GetId();

            // do we have a dictionary entry?
            auto it= threadDictionary.find( threadID );
            if (it != threadDictionary.end() )
                threadName << it->second;
            else
                threadName << thread->GetName();
        }

        // return id and name
        if (id != nullptr)
            *id=    threadID;
        return    threadName;
    }

#endif
