// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// include ALox main header first...
#if !defined (HPP_AWORX_ALOX_ALOX)
    #include "alox.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_ALOX_CALLERINFO
#define HPP_AWORX_ALOX_CALLERINFO 1

// -------------------------------------------------------------------------------------------------
// --- includes
// -------------------------------------------------------------------------------------------------
#if !defined (HPP_AWORX_UTIL_ASTRING)
    #include "astring.hpp"
#endif

#if !defined (HPP_AWORX_UTIL_TICKS)
    #include "ticks.hpp"
#endif

#if !defined (HPP_AWORX_UTIL_THREAD)
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
class CallerInfo : public aworx::util::Ownable
{
    private:
        /** Privatized assignment operator for being an Ownable. @param op The operand. @returns Itself. */
        CallerInfo& operator  =   (const CallerInfo&  op);

    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /** If true, thread information was evaluated.  **/
        bool                                lazyFlagThreadNameAndID;

        /** The id of the thread that executed the log.  **/
        int                                 threadID;

        /** The name of the thread that executed the log.  **/
        aworx::util::AString32              threadName;

        /** The thread dictionary, managed externally, provided as a pointer in the constructor. **/
        #if defined(AWXU_FEAT_THREADS)
            const std::map<int, std::string>&   threadDictionary;
        #endif

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /** Flag which is set as soon as a new log operation starts and is cleared at its end.  **/
        bool                            isFresh;

        /**  Time of the call represented by this instance.  **/
        aworx::util::Ticks              TimeStamp;

        /**     Name and path of the source code file the log call is placed in.  **/
        const char*                     SourceFileName;

        /**     Line number within the source code file the log call is placed in.  **/
        int                             LineNumber;

        /**     Name of the method the log call is placed in.  **/
        const char*                     MethodName;

    // #############################################################################################
    // Constructor
    // #############################################################################################
    public:
        #if defined(AWXU_FEAT_THREADS)
        /** ****************************************************************************************
         *  Constructs a caller info.
         *  @param threadDictionary  A dictionary to map thread IDs to user friendly names which is
         *                           managed outside of this class.
         ******************************************************************************************/
            ALOX_API CallerInfo( const  std::map<int, std::string>& threadDictionary );
        #else
            ALOX_API CallerInfo();
        #endif

     // #############################################################################################
     // public interface
     // #############################################################################################


        /** ************************************************************************************
         *    Stores C++ specific caller parameters and invokes Acquire().
         *
         * @param source      Name, including path, of the source code file of the actual log
         *                    invocation (__FILE__).
         * @param lineNumber  Line number within the source code file of the actual log
         *                    invocation (__LINE__).
         * @param method      Name of method or function of the actual log invocation (mostly
         *                    __func__/ __FUNCTION__).
         **************************************************************************************/
        ALOX_API void SetSourceInfo ( const char* source, int lineNumber, const char* method );

        /** ****************************************************************************************
         * Sets the time if this was not done before (e.g by invoking SetSourceInfo). We want to
         * get the log time as early as possible
         ******************************************************************************************/
        ALOX_API void Acquire();

        /** ****************************************************************************************
         *  This flags our data as invalid.
         ******************************************************************************************/
        ALOX_API void Release()        { isFresh= false; }

        #if defined(AWXU_FEAT_THREADS)
            /** ************************************************************************************
             *  Receives information about the thread that the current call was invoked with.
             *  @param id  Output parameter receiving the AWXU thread ID. If nullptr, it will be
             *             ignored.
             *  @returns The name of the current thread. The id is stored within the provided
             *           pointer.
             **************************************************************************************/
            ALOX_API const aworx::util::AString& getThreadNameAndID( int* id );
        #endif

}; // class CallerInfo

}}} // namespace aworx::lox::core

#endif // HPP_AWORX_ALOX_CALLERINFO
