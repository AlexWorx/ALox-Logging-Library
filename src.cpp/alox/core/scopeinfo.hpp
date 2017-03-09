// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include ALox main header first...
#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

// then, set include guard
#ifndef HPP_ALOX_CORE_SCOPEINFO
#define HPP_ALOX_CORE_SCOPEINFO 1

// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALIB_TIME_TICKS)
    #include "alib/time/ticks.hpp"
#endif

#if !defined (HPP_ALIB_THREADS_THREAD)
    #include "thread.hpp"
#endif

#if !defined (HPP_ALIB_SYSTEM_DIRECTORY)
    #include "alib/system/directory.hpp"
#endif


#if !defined (_GLIBCXX_MAP) && !defined(_MAP_)
    #include <map>
#endif

namespace aworx { namespace lox { namespace core {

/** ************************************************************************************************
 *  Encapsulates information of the caller that can be collected. This is platform specific, in
 *  this case, C++. What we receive from the C++ preprocessor, is the source file name
 *  of the calling code, the line number within the source file name and the name of the method
 *  the call is placed in. E.g., wee do not get the class name of the object or even its instance.
 *
 *  The method has a list of interface functions that gets such source information and some derived
 *  variants of it. In addition, thread and timer information is stored and managed.
 *
 *  As far as possible, 'lazy' techniques come to practice with this class. This means, only
 *  the things that are queried in-between to invocations of method #Set are calculated.
 **************************************************************************************************/
class ScopeInfo
{
    /** Class \b %Lox uses and controls this class. */
    friend class aworx::lox::Lox;

    // #############################################################################################
    // Types exposed
    // #############################################################################################
    public:
        /** A std::map we use to translate thread IDs to thread names */
        using ThreadDictionary=   std::map<int, String32>;

        /**
         * The number of source file path and corresponding, evaluated derived values.
         * This might be modified, prior to creating any object of class \b Lox.<br>
         * Defaults to 5.
         */
        ALOX_API
        static  int             DefaultCacheSize;

    // #############################################################################################
    // Protected members
    // #############################################################################################
    private:
        /** Privatized assignment operator for being an Ownable. @param op The operand. @returns Itself. */
        ScopeInfo& operator  =   (const ScopeInfo&  op);

    protected:
        /**  Defines portions of source paths to be ignored  */
        struct SourcePathTrimRule
        {
            AString    Path;             ///< The path string
            bool       IsPrefix;         ///< true if path was not starting with '\*' when provided.
            Inclusion  IncludeString;    ///< Denotes if #Path itself should be included when trimmed
            Case       Sensitivity;      ///< The sensitivity of the comparison when trimming
            int        TrimOffset;       ///< Additional offset of the trim position
            AString    TrimReplacement;  ///< Optional replacement string for trimmed paths'.
            int        Priority;         ///< The priority of the rule. Depends on origin: source code, config...)
        };

        /**  List of trim definitions for portions of source paths to be ignored  */
        ALOX_API
        static std::vector<SourcePathTrimRule>   GlobalSPTRs;

        /**  List of trim definitions for portions of source paths to be ignored  */
               std::vector<SourcePathTrimRule>   LocalSPTRs;

        /**  Flag to determine if global rules have been read from config already  */
        ALOX_API
        static bool                              GlobalSPTRsReadFromConfig;

        /**
         *  If true, next time a source path can not be trimmed successfully with custom
         *  trim information provided with
         *  \ref aworx::lox::Lox::SetSourcePathTrimRule "Lox::SetSourcePathTrimRule"
         *  some trim information is automatically created by comparing such source files' path
         *  with the path of the executable of the current process.
         */
        bool                                     AutoDetectTrimableSourcePath                = true;


    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /** The name of the Lox we are attached to */
        String32                                loxName;

        /** The thread passed with #Set  **/
        Thread*                                 thread                                    = nullptr;

        /** The name of the thread that executed the log.  **/
        String                                  threadName;

        /** The thread dictionary, managed externally, provided as a pointer in the constructor. **/
        const ThreadDictionary&                 threadDictionary;

        /** Information of a single source file. Stored in field #cache */
        struct SourceFile
        {
            /**  'Timestamp' for LRU overwriting (not a time, but using field #cacheRun) */
            uint64_t                            timeStamp       = 0;

            /**  Path and name of source file (given by the C++ preprocessor)  **/
            TString                             origFile;

            /** Full path of source file  (evaluated)  **/
            String                              fullPath;

            /** Trimmed path of source file  (evaluated)  **/
            String                              trimmedPath;

            /** Prefix for the trimmed path taken from trim rule. Has to be added on writing
             *  the trimmed path **/
            String                              trimmedPathPrefix;

            /** File name (evaluated)  **/
            String                              name;

            /** File name without extension (evaluated)  **/
            String                              nameWOExt;

            /** Index of last path separator in #origFile **/
            integer                            origFilePathLength;

            /** Constructor **/
            SourceFile() {  origFile= nullptr; Clear(); }

            /** Clears calculated values. Keeps #origFile intact. **/
            void Clear()
            {
                origFilePathLength= -2;
                fullPath=           nullptr;
                trimmedPath=        nullptr;
                name=               nullptr;
                nameWOExt=          nullptr;
            }

        };


        /** The 'timestamp' used to identify the LRU entry. Incremented, whenever a different source
            file is evaluated.  */
        uint64_t                                cacheRun                                        = 0;

        /**
          * The number of source file path and corresponding, evaluated derived values.
          * Determined in the constructor by reading static field #DefaultCacheSize.
          */
        int                                     cacheSize;

        /** A list of source files. The its size is dependent on static field #DefaultCacheSize. */
        SourceFile*                             cache;

        /**
         * Holds values for the current scope. Because recursive logging might occur (e.g. when
         * parameters rely on method invocations which incorporate log statements), objects of this
         * class are stored in stack #scopes.
         */
        struct Scope
        {
            /**  Time of the call represented by this instance.  **/
            Ticks                               timeStamp;

            /** The entry of the source file cache      */
            SourceFile*                         sourceFile;

            /**  Line number within the source file (given by the C++ preprocessor)  **/
            int                                 origLine;

            /**  Function/method name (given by the C++ preprocessor)  **/
            TString                             origMethod;

        };

        /** A stack of scopes (allows recursive calls/nested logging) */
        std::vector<Scope>                      scopes;

        /** The current depth of recursive invocations. */
        int                                     actScopeDepth                                  = -1;

        /** The last source file used. This is tried first with next invocation. If it does not
         *  match, the cache is searched for another matching one.*/
        SourceFile*                             lastSourceFile;


    // #############################################################################################
    // Constructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Constructs a scope info.
         * @param name              The name of the Lox we belong to.
         *                          Will be converted to upper case.
         * @param threadDictionary  A dictionary to map thread IDs to user friendly names which is
         *                          managed outside of this class.
         ******************************************************************************************/
        ALOX_API
         ScopeInfo( const TString& name, const std::map<int, String32>& threadDictionary );

        ALOX_API
        ~ScopeInfo();

     // #############################################################################################
     // public interface
     // #############################################################################################
    public:
        /** ****************************************************************************************
         * Stores C++ specific caller parameters and some other values like the time stamp.
         * Also, flags thread information as not received, yet.
         * Counts the recursion counter up.
         * @param source      Name, including path, of the source code file of the actual log
         *                    invocation (__FILE__).
         * @param lineNumber  Line number within the source code file of the actual log
         *                    invocation (__LINE__).
         * @param method      Name of method or function of the actual log invocation (mostly
         *                    __func__/ __FUNCTION__).
         * @param thread      The thread. If \c nullptr, it will be determined if needed.
         ******************************************************************************************/
        ALOX_API
        void Set( const TString& source, int lineNumber, const TString& method, Thread* thread );

        /** ****************************************************************************************
         * Releases latest scope information.
         ******************************************************************************************/
        void Release()
        {
            lastSourceFile= scopes[static_cast<size_t>( actScopeDepth )].sourceFile;
            actScopeDepth--;
            ALIB_ASSERT( actScopeDepth >= -1 )
        }


        /** ****************************************************************************************
         * Does the job for
         * \ref aworx::lox::Lox::SetSourcePathTrimRule    "Lox::SetSourcePathTrimRule" and
         * \ref aworx::lox::Lox::ClearSourcePathTrimRules "Lox::ClearSourcePathTrimRules".
         *
         * @param path            The path to search for. If not starting with <c> '*'</c>,
         *                        a prefix is searched.
         * @param includeString   Determines if \p path should be included in the trimmed path or not.
         * @param trimOffset      Adjusts the portion of \p path that is trimmed. 999999 to clear!
         * @param sensitivity     Determines if the comparison of \p path with a source files' path
         *                        is performed case sensitive or not.
         * @param trimReplacement Replacement string for trimmed portion of the path.
         * @param reach           Denotes whether the rule is applied locally (to this \b %Lox only)
         *                        or applies to all instances of class \b %Lox.
         *                        Defaults to \b %Reach::Global.
         * @param priority        The priority of the setting.
        ******************************************************************************************/
        ALOX_API
        void      SetSourcePathTrimRule( const TString& path,
                                         Inclusion      includeString,
                                         int            trimOffset,
                                         Case           sensitivity,
                                         const String&  trimReplacement,
                                         Reach          reach,
                                         int            priority                );

        /** ****************************************************************************************
         * Receives the name of the \b Lox we are belonging to (this is a 1:1 relationship).
         * @return The name of the \b Lox.
         ******************************************************************************************/
        inline
        const TString& GetLoxName()
        {
            return loxName;
        }

        /** ****************************************************************************************
         * Receives the original filename and path of the source file
         * (usually provided by the preprocessor).
         * @return The full path and filename of the source file.
         ******************************************************************************************/
        inline
        const TString& GetOrigFile()
        {
            return scopes[static_cast<size_t>(actScopeDepth)].sourceFile->origFile;
        }

        /** ****************************************************************************************
         * Receives the path of the source file (not trimmed, see #GetTrimmedPath).
         * @return The path of the source file.
         ******************************************************************************************/
        inline
        const String GetFullPath()
        {
            SourceFile* actual= scopes[static_cast<size_t>(actScopeDepth)].sourceFile;
            if( actual->fullPath.IsNull() )
            {
                integer idx= getPathLength();
                if( idx >= 0 )
                    actual->fullPath= String( actual->origFile.Buffer(), idx );
                else
                    actual->fullPath= "";
            }

            return actual->fullPath;
        }

        /** ****************************************************************************************
         * Writes the path of the source file, trimmed according to trim-information provided
         * with #SetSourcePathTrimRule or detected according to #AutoDetectTrimableSourcePath.
         * @param target The target string to append the trimmed path to.
         ******************************************************************************************/
        inline
        void GetTrimmedPath( AString& target )
        {
            SourceFile* actual= scopes[static_cast<size_t>(actScopeDepth)].sourceFile;
            if( actual->trimmedPath.IsNull() )
                trimPath();

            target._( actual->trimmedPathPrefix )
                  ._(actual->trimmedPath );
        }

        /** ****************************************************************************************
         * Receives the source file name excluding the path (usually provided by the preprocessor).
         * @return The source file name excluding the path
         ******************************************************************************************/
        inline
        const String GetFileName()
        {
            SourceFile* actual= scopes[static_cast<size_t>(actScopeDepth)].sourceFile;
            if( actual->name.IsNull() )
            {
                integer idx= getPathLength();
                if( idx >= 0 )
                    actual->name= String( actual->origFile.Buffer() + idx + 1,
                                                           actual->origFile.Length() - idx - 1 );
                else
                    actual->name= "";
            }
            return actual->name;
        }

        /** ****************************************************************************************
         * Receives the source file name excluding the path and without an extension
         * (usually provided by the preprocessor).
         * @return The source file name excluding the path and extension.
         ******************************************************************************************/
        inline
        const String GetFileNameWithoutExtension()
        {
            SourceFile* actual= scopes[static_cast<size_t>(actScopeDepth)].sourceFile;
            if( actual->nameWOExt.IsNull() )
            {
                actual->nameWOExt= GetFileName();
                integer lastDot=   actual->nameWOExt.LastIndexOf( '.' );
                if ( lastDot > 0 )
                    actual->nameWOExt= String( actual->nameWOExt.Buffer(), lastDot );
            }
            return actual->nameWOExt;
        }


        /** ****************************************************************************************
         * Receives the method name (usually provided by the preprocessor).
         * @return The method name.
         ******************************************************************************************/
        inline
        const String GetMethod()
        {
            return scopes[static_cast<size_t>(actScopeDepth)].origMethod;
        }

        /** ****************************************************************************************
         * Receives the source file line number (usually provided by the preprocessor).
         * @return The source file line number.
         ******************************************************************************************/
        inline
        int GetLineNumber()
        {
            return scopes[static_cast<size_t>(actScopeDepth)].origLine;
        }

        /** ****************************************************************************************
         * The timestamp of the last invocation of #Set.
         * @return The latest timestamp.
         ******************************************************************************************/
        inline
        const Ticks& GetTimeStamp()
        {
            return scopes[static_cast<size_t>(actScopeDepth)].timeStamp;
        }

        /** ************************************************************************************
         * Receives the thread ID of the caller.
         * @returns The thread ID.
         **************************************************************************************/
        inline
        int GetThreadID()
        {
            if( thread == nullptr )
                thread= Thread::CurrentThread();
            return thread->GetId();
        }

        /** ************************************************************************************
         * Receives information about the thread that the current call was invoked with.
         * @param id  Output parameter receiving the ALIB thread ID. If nullptr, it will be
         *            ignored.
         * @returns The name of the current thread. The id is stored within the provided
         *          pointer.
         **************************************************************************************/
        inline
        const aworx::String& GetThreadNameAndID( int* id )
        {
            if ( threadName.IsNull() )
            {
                // get current thread, if not passed with set()
                if( thread == nullptr )
                    thread =  Thread::CurrentThread();

                if (id != nullptr)
                    *id=    thread->GetId();

                // do we have a dictionary entry?
                auto it= threadDictionary.find( thread->GetId() );
                if (it != threadDictionary.end() )
                    threadName= it->second;
                else
                    threadName= thread->GetName();
            }

            return    threadName;
        }

    // #############################################################################################
    // Internals
    // #############################################################################################
        protected:

        /** ************************************************************************************
         * Tries to trim the source files' path. Sets variable SourceFile::trimmedPath to either
         * the successfully trimmed path or to the non-trimmed one. This way, it is executed
         * only once, at it is 'lazily' invoked by #GetTrimmedPath()
         **************************************************************************************/
        ALOX_API
        void            trimPath();

        /** ************************************************************************************
         * Gets position of path/filename separator. This is evaluated only once after an
         * invocation of #Set.
         * @return The index of the path separator in SourceFile::origFile.
         **************************************************************************************/
        inline
        integer        getPathLength()
        {
            SourceFile* actual= scopes[static_cast<size_t>(actScopeDepth)].sourceFile;
            if( actual->origFilePathLength == -1 )
                return -1;
            return ( actual->origFilePathLength= actual->origFile.LastIndexOf( aworx::DirectorySeparator ) );
        }
}; // class ScopeInfo

}}} // namespace aworx::lox::utils

#endif // HPP_ALOX_CORE_SCOPEINFO
