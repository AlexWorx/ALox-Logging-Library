// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include ALox main header first...
#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

// then, set include guard
#ifndef HPP_ALOX_CORE_CALLERINFO
#define HPP_ALOX_CORE_CALLERINFO 1

// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALIB_TIME)
    #include "alib/time/ticks.hpp"
#endif

#if !defined (HPP_ALIB_THREADS_THREAD)
    #include "thread.hpp"
#endif

#if !defined (_GLIBCXX_MAP) && !defined(_MAP_)
    #include <map>
#endif

namespace aworx {
namespace       lox {
namespace           core{

/** ************************************************************************************************
 *  Encapsulates information of the caller that can be collected. This is platform specific, in
 *  this case, .NET 4.5. What we currently can get from the .NET compiler, is the source file name
 *  of the calling code, the line number within the source file name and the name of the method
 *  the call is placed. We do not get the class name of the object or even its instance.
 **************************************************************************************************/
class CallerInfo
{
    public:
        /** A std::map we use to translate thread IDs to thread names */
        using ThreadDictionary=   std::map<int, String32>;

    private:
        /** Privatized assignment operator for being an Ownable. @param op The operand. @returns Itself. */
        CallerInfo& operator  =   (const CallerInfo&  op);

    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /** Counts the number of nested acquirements. Only the first will store the source info. */
        int                                     recursionCounter                            = 0;

        /** If \c true, thread information was evaluated.  **/
        bool                                    lazyFlagThreadNameAndID                     = false;

        /** The id of the thread that executed the log.  **/
        int                                     threadID                                    = 0;

        /** The name of the thread that executed the log.  **/
        String                                  threadName;

        /** The thread dictionary, managed externally, provided as a pointer in the constructor. **/
        #if defined(ALIB_FEAT_THREADS)
            const ThreadDictionary&             threadDictionary;

            //const std::map<int, String32>&    threadDictionary;
        #endif

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**  Time of the call represented by this instance.  **/
        aworx::lib::time::Ticks                 TimeStamp;

        /**     Name and path of the source code file the log call is placed in.  **/
        TString                                 SourceFileName                            = nullptr;

        /**     Line number within the source code file the log call is placed in.  **/
        int                                     LineNumber                                = 0;

        /**     Name of the method the log call is placed in.  **/
        TString                                 MethodName                                = nullptr;

    // #############################################################################################
    // Constructor
    // #############################################################################################
    public:
        #if defined(ALIB_FEAT_THREADS)
        /** ****************************************************************************************
         *  Constructs a caller info.
         *  @param threadDictionary  A dictionary to map thread IDs to user friendly names which is
         *                           managed outside of this class.
         ******************************************************************************************/
            ALOX_API CallerInfo( const std::map<int, String32>& threadDictionary );
        #else
            ALOX_API CallerInfo();
        #endif

     // #############################################################################################
     // public interface
     // #############################################################################################


        /** ************************************************************************************
         *  Stores C++ specific caller parameters and some other values like the time stamp.
         *
         * @param source      Name, including path, of the source code file of the actual log
         *                    invocation (__FILE__).
         * @param lineNumber  Line number within the source code file of the actual log
         *                    invocation (__LINE__).
         * @param method      Name of method or function of the actual log invocation (mostly
         *                    __func__/ __FUNCTION__).
         **************************************************************************************/
        ALOX_API
        void AcquireAndSet ( const TString& source, int lineNumber, const TString& method );

        /** ****************************************************************************************
         *  This is not an ownable, hower with each &aquire of class Lox, we have to count up.
         ******************************************************************************************/
        void Acquire()   { recursionCounter++; ALIB_ASSERT( recursionCounter != 5); }

        /** ****************************************************************************************
         *  This is not an ownable, hower with each &release of class Lox, we have to count down.
         ******************************************************************************************/
        void Release()   { recursionCounter--; ALIB_ASSERT( recursionCounter >= 0 ); }

        #if defined(ALIB_FEAT_THREADS)
            /** ************************************************************************************
             *  Receives information about the thread that the current call was invoked with.
             *  @param id  Output parameter receiving the ALIB thread ID. If nullptr, it will be
             *             ignored.
             *  @returns The name of the current thread. The id is stored within the provided
             *           pointer.
             **************************************************************************************/
            ALOX_API
            const aworx::String& getThreadNameAndID( int* id );
        #endif

}; // class CallerInfo

}}} // namespace aworx::lox::core

#endif // HPP_ALOX_CORE_CALLERINFO
