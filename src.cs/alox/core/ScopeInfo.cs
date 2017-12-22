// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using cs.aworx.lib;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lib.strings.util;
using cs.aworx.lib.lang;
using cs.aworx.lib.threads;
using System.IO;
using System.Diagnostics;
using System.Threading;
using cs.aworx.lib.config;

namespace cs.aworx.lox.core {
/** ************************************************************************************************
 * Encapsulates information of the caller that can be collected. This is platform specific, in
 * this case, .NET 4.5. What we currently can get from the .NET compiler, is the source file name
 * of the calling code, the line number within the source file name and the name of the method
 * the call is placed. We do not get the class name of the object or even its instance.
 **************************************************************************************************/
#if ALOX_DBG_LOG || ALOX_REL_LOG

public class ScopeInfo
{
    // #############################################################################################
    // Protected members
    // #############################################################################################

        /** The name of the Lox we are attached to */
        protected        String                    loxName;

        /** The dictionary for thread names (a copy of that from our Lox)  */
        protected        Dictionary<int, String>   threadDictionary;



        /** Information of a single source file. Stored in field #cache */
        protected class SourceFile
        {
            /**  'Timestamp' for LRU overwriting (not a time, but using field #cacheRun) */
            public        long                      timeStamp       = 0;

            /**  Path and name of source file (given by the C++ preprocessor)  **/
            public        String                    origFile;

            /** index of last path separator in #origFile **/
            public        int                       origFilePathLength;

            /** Trimmed path of source file  (evaluated)  **/
            public        AString                   trimmedPath                  = new AString();

            /** File name (evaluated)  **/
            public        AString                   name                         = new AString();

            /** File name without extension (evaluated)  **/
            public        AString                   nameWOExt                    = new AString();


            /** Flag to lazily create #trimmedPath  **/
            public        bool                      lazyTrimmedPath;

            /** Flag to lazily create #name  **/
            public        bool                      lazyName;

            /** Flag to lazily create #nameWOExt  **/
            public        bool                      lazyNameWOExt;
        }


        /**
         * The number of source file path and corresponding, evaluated derived values.
         * This might be modified, prior to creating any object of class \b Lox.<br>
         * Defaults to 5.
         */
        public  static    int DefaultCacheSize=     5;

        /**
          * The number of source file path and corresponding, evaluated derived values.
          * Determined in the constructor by reading static field #DefaultCacheSize.
          */
        protected         int                       cacheSize;

        /** The 'timestamp' used to identify the LRU entry. Incremented, whenever a different source
            file is evaluated.  */
        protected         long                      cacheRun=   0;

        /** A list of source files. The its size is dependent on static field #DefaultCacheSize. */
        protected         SourceFile[]              cache;

        /** The thread that executed the log.  **/
        protected        Thread                     thread;

        /** The id of the thread that executed the log.  **/
        protected        int                        threadID;

        /** The name of the thread that executed the log.  **/
        protected        AString                    threadName                     = new AString(32);

        /**
         *  If true, next time a source path can not be trimmed successfully with custom
         *  trim information provided with
         *  \ref cs.aworx.lox.Lox.SetSourcePathTrimRule "Lox.SetSourcePathTrimRule"
         *  some trim information is automatically created by comparing such source files' path
         *  with the path of the executable of the current process.
         */
        protected bool                              AutoDetectTrimableSourcePath             = true;

        /** Information of a single source file. Stored in field #cache */

            /**
         * Holds values for the current scope. Because recursive logging might occur (e.g. when
         * parameters rely on method invocations wich incorporate log statements), objects of this
         * class are stored in stack #scopes.
         */
    protected class Scope
        {
            /** Time of the call represented by this instance.  **/
            public           Ticks                  timeStamp                     = new Ticks();

            /**  Line number within the source file (given by the diagnostics)  **/
            public           int                    origLine;

            /**  Function/method name (given by the diagnostics)  **/
            public           String                 origMethod;

            /** The entry of the source file cache      */
            public           SourceFile             sourceFile;
        }

        /** A stack of scopes (allows recursive calls/nested logging) */
        protected        List<Scope>                scopes                      = new List<Scope>();

        /** The current depth of recursive invocations. */
        protected        int                        actScopeDepth                              = -1;

        /** The last source file used. This is tried first with next invocation. If it does not
         *  match, the cache is searched for another matching one.*/
        protected        SourceFile                 lastSourceFile;

    // #############################################################################################
    // Public memebers (in C++ this is protected and Lox is a friend)
    // #############################################################################################
        /**  Defines portions of source paths to be ignored  */
        public class SourcePathTrimRule
        {
            public AString    Path;             ///< The search string
            public bool       IsPrefix;         ///< true if path was not starting with '\*' when provided.
            public Inclusion  IncludeString;    ///< Denotes if #Path itself should be included when trimmed
            public Case       Sensitivity;      ///< The sensitivity of the comparison when trimming
            public int        TrimOffset;       ///< Additional offset of the trim position
            public String     TrimReplacement;  ///< Optional replacement string for trimmed paths'.
            public int        Priority;         ///< The priority of the rule. Depends on origin: source code, config...)
        }

        /**  List of trim definitions for portions of source paths to be ignored  */
        public  static List<SourcePathTrimRule> GlobalSPTRs= new List<SourcePathTrimRule>();

        /**  List of trim definitions for portions of source paths to be ignored  */
        public         List<SourcePathTrimRule> LocalSPTRs = new List<SourcePathTrimRule>();

        /**  Flag to determine if global rules have been read from config already  */
        public static bool                      GlobalSPTRsReadFromConfig           = false;

    // #############################################################################################
    // public interface
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs a scope info.
         * @param name              The name of the Lox we belong to.
         *                          Will be converted to upper case.
         * @param threadDictionary  A dictionary to map thread IDs to user friendly names which is
         *                          managed outside of this class.
         ******************************************************************************************/
        public ScopeInfo( String name,  Dictionary<int, String> threadDictionary )
        {
            loxName= name.ToUpper();
            ALIB_DBG.ASSERT_ERROR( !loxName.Equals( "GLOBAL" ), "Name \"GLOBAL\" not allowed for Lox instances" );

            this.threadDictionary= threadDictionary;

            cache=  new SourceFile[cacheSize= DefaultCacheSize];
            for ( int i= 0; i< cacheSize; i++ )
                cache[i]= new SourceFile();
            lastSourceFile= cache[0];

            // read trim rules from config
            // do 2 times, 0== local list, 1== global list
            List<SourcePathTrimRule> trimInfoList;
            for( int trimInfoNo= 0; trimInfoNo < 2 ; trimInfoNo++ )
            {
                // check if done... or set list
                Variable variable= new Variable();
                if ( trimInfoNo == 0 )
                {
                    trimInfoList= LocalSPTRs;
                    variable.Declare(ALox.SPTR_LOX, loxName);
                }
                else
                {
                    if ( GlobalSPTRsReadFromConfig )
                        continue;
                    GlobalSPTRsReadFromConfig= true;
                    trimInfoList= GlobalSPTRs;
                    variable.Declare(ALox.SPTR_GLOBAL);
                }
                ALox.Config.Load(variable);

                if( variable.Priority != 0 )
                {
                    Tokenizer ruleTok = new Tokenizer();
                    for( int ruleNo= 0; ruleNo< variable.Size(); ruleNo++ )
                    {
                        try {
                            ruleTok.Set( variable.GetString( ruleNo ), ',' );
                            SourcePathTrimRule rule= new SourcePathTrimRule();
                            rule.Priority= variable.Priority;
                            rule.Path= new AString();
                            ruleTok.Next();
                            if( ! ( rule.IsPrefix= !ruleTok.Actual.StartsWith( "*" ) ) )
                                ruleTok.Actual.ConsumeChars(1);
                            rule.Path._( ruleTok.Actual );
                            if ( rule.Path.CharAtEnd() == '*' )
                                rule.Path.DeleteEnd( 1 );
                            if ( rule.Path.IsEmpty() )
                                continue;

                            if( Path.DirectorySeparatorChar == '/' )
                                rule.Path.SearchAndReplaceAll( "\\", "/"  );
                            else
                                rule.Path.SearchAndReplaceAll( "/" , "\\" );


                            rule.IncludeString = ALIB.ReadInclusion( ruleTok.Next() );

                            if ( ruleTok.HasNext () )
                                ruleTok.Next().ConsumeInt( out rule.TrimOffset );

                            rule.Sensitivity = ALIB.ReadCase( ruleTok.Next() );

                            if ( ruleTok.HasNext () )
                                rule.TrimReplacement= ruleTok.Next().ToString();

                            trimInfoList.Add( rule );
                        }
                        catch( Exception )
                        {
                            ALIB_DBG.ERROR( "Error reading source path trim rule from configuration. Invalid String: "
                                        + variable.GetString( ruleNo ).ToString() );
                        }
                    }
                }
            }
        }

        /** ****************************************************************************************
         * Stores caller parameters, sets actual time stamp and receives thread information
         * @param callerLineNumber       Line number within the source code file the log call is
         *                               placed in.
         * @param callerSourceFileName   Name and path of the source code file the log call is
         *                               placed in.
         * @param callerMemberName       Name of the method the log call is placed in.
         * @param thread                 The thread. If \c null, it will be determined if needed.
         ******************************************************************************************/
        public void Set( int callerLineNumber, String callerSourceFileName, String callerMemberName,
                         Thread thread )
        {
            actScopeDepth++;
            if( scopes.Count == actScopeDepth )
            {
                ALIB_DBG.ASSERT( actScopeDepth < 8 );
                scopes.Add( new Scope() );
            }
            Scope scope = scopes[actScopeDepth];

            // 1) set the actual timestamp as early as possible
            scope.timeStamp.Set();

            // 2) save parameters
            scope.origLine=    callerLineNumber;
            scope.origMethod=  callerMemberName;
            scope.sourceFile=  lastSourceFile;

            // 3) find matching source file info record
            if( scope.sourceFile.origFile != callerSourceFileName )
            {
                int   oldestIdx= -1;
                long  oldestTime= ++cacheRun;

                scope.sourceFile= null;
                for( int i= 0; i < cacheSize; i++ )
                {
                    if ( cache[i].origFile == callerSourceFileName )
                    {
                        scope.sourceFile= cache[i];
                        break;
                    }

                    if( oldestTime > cache[i].timeStamp )
                    {
                        oldestTime= cache[i].timeStamp;
                        oldestIdx= i;
                    }
                }

                // not found? Use the oldest
                if ( scope.sourceFile == null )
                {
                    scope.sourceFile= cache[oldestIdx];

                    scope.sourceFile.origFile=                callerSourceFileName;
                    scope.sourceFile.origFilePathLength=      -2;
                    scope.sourceFile.lazyTrimmedPath          =
                    scope.sourceFile.lazyName                 =
                    scope.sourceFile.lazyNameWOExt            =false;
                }

                // mark as used
                scope.sourceFile.timeStamp= cacheRun;
            }

            // 4) get thread information
            threadName._();

            // get current thread
            if ( thread == null )
                thread=     Thread.CurrentThread;
            this.thread= thread;
            threadID=   thread.ManagedThreadId;

            // do we have a dictionary entry?
            String threadDictName;
            if( threadDictionary.TryGetValue( threadID,  out threadDictName) )
                threadName._( threadDictName );
            else
            {
                if ( String.IsNullOrEmpty ( thread.Name ) )
                    threadName._( threadID );
                else
                    threadName._( thread.Name )._( '(' )._( threadID )._( ')' );
            }
        }

        /** ****************************************************************************************
         * Releases latest scope information.
         ******************************************************************************************/
        public void Release()
        {
            lastSourceFile= scopes[actScopeDepth].sourceFile;
            actScopeDepth--;
            ALIB_DBG.ASSERT( actScopeDepth >=-1 );
        }


        /** ****************************************************************************************
         * Does the job for
         * \ref cs.aworx.lox.Lox.SetSourcePathTrimRule    "Lox.SetSourcePathTrimRule" and
         * \ref cs.aworx.lox.Lox.ClearSourcePathTrimRules "Lox.ClearSourcePathTrimRules".
         *
         * @param path            The path to search for. If not starting with <c> '*'</c>,
         *                        a prefix is searched.
         * @param includeString   Determines if \p path should be included in the trimmed path
         *                        or not.
         * @param trimOffset      Adjusts the portion of \p path that is trimmed. 999999 to clear!
         * @param sensitivity     Determines if the comparison of \p path with a source files' path
         *                        is performed case sensitive or not.
         * @param trimReplacement Replacement string for trimmed portion of the path.
         * @param reach           Denotes whether the rule is applied locally (to this \b %Lox only)
         *                        or applies to all instances of class \b %Lox.
         * @param priority        The priority of the setting.
         ******************************************************************************************/
        public void   SetSourcePathTrimRule( String     path,
                                             Inclusion  includeString,
                                             int        trimOffset,
                                             Case       sensitivity,
                                             String     trimReplacement,
                                             Reach      reach,
                                             int        priority            )
        {
            // unset current cache objects to have lazy variables reset with the next invocation
            for (int i = 0; i < cacheSize; i++)
            {
                cache[i].origFilePathLength=      -2;
                cache[i].lazyTrimmedPath          =
                cache[i].lazyName                 =
                cache[i].lazyNameWOExt            =false;
            }

            // clear command
            if ( trimOffset == 999999 )
            {
                LocalSPTRs.Clear();
                if ( reach == Reach.Global )
                    GlobalSPTRs.Clear();
                AutoDetectTrimableSourcePath=  (includeString == Inclusion.Include);

                // reset config read flag. This is done for unit testing. Not really
                // useful/needed in real life.
                GlobalSPTRsReadFromConfig= false;
                return;
            }

            // choosel local or global list
            List<SourcePathTrimRule> trimInfoList = reach == Reach.Global  ? GlobalSPTRs
                                                                           : LocalSPTRs;

            // add new entry
            SourcePathTrimRule rule= new SourcePathTrimRule();

            // if path starts with '*', it is not a prefix. We store without *
            rule.Path= new AString( (rule.IsPrefix= !path.StartsWith("*")) ? path : path.Substring( 1 ) );
            if ( rule.Path.CharAtEnd() == '*' )
                rule.Path.DeleteEnd( 1 );
            if ( rule.Path.IsEmpty() )
                return;

            if( Path.DirectorySeparatorChar == '/' )
                rule.Path.SearchAndReplaceAll( "\\", "/"  );
            else
                rule.Path.SearchAndReplaceAll( "/" , "\\" );

            rule.IncludeString=   includeString;
            rule.TrimOffset=      trimOffset;
            rule.Sensitivity=     sensitivity;
            rule.TrimReplacement= trimReplacement;

            // add rule ordered by priority
            rule.Priority= priority;
            int pos= 0;
            while( pos < trimInfoList.Count && priority < trimInfoList[pos].Priority )
                ++pos;

            trimInfoList.Insert( pos, rule );
        }


        /** ****************************************************************************************
         * Receives the name of the \b Lox we are belonging to (this is a 1:1 relationship).
         * @return The name of the \b Lox.
         ******************************************************************************************/
        public String GetLoxName()
        {
            return loxName;
        }

        /** ****************************************************************************************
         * Receives the original filename and path of the source file
         * (usually provided by ).
         * @return The full path and filename of the source file.
         ******************************************************************************************/
        public String GetOrigFile()
        {
            return scopes[actScopeDepth].sourceFile.origFile;
        }

        /** ****************************************************************************************
         * Returns the original path and filename of the source file, togehter with length,
         * of the path within this string (as output parameter) .
         * @param[out] length  Output parameter returning the length of the path string.
         * @return Gets the path of the source file (not trimmed, see #GetTrimmedPath).
         ******************************************************************************************/
        public String GetFullPath( out int length )
        {
            SourceFile actual= scopes[actScopeDepth].sourceFile;
            if( actual.origFilePathLength == -2 )
                actual.origFilePathLength= actual.origFile.LastIndexOf( Path.DirectorySeparatorChar );

            length= actual.origFilePathLength >= 0 ? actual.origFilePathLength : 0;
            return  actual.origFile;
        }

        /** ****************************************************************************************
         * Tries to trim the source files' path. Sets variable SourceFile.trimmedPath to either
         * the successfully trimmed path or to the non-trimmed one. This way, it is executed
         * only once, at it is 'lazily' invoked by #GetTrimmedPath()
         *
         * @return The path of the source file, trimmed according to trim-information provided
         *      with #SetSourcePathTrimRule or detected according to #AutoDetectTrimableSourcePath.
         ******************************************************************************************/
        public AString GetTrimmedPath()
        {
            SourceFile actual= scopes[actScopeDepth].sourceFile;
            if( actual.lazyTrimmedPath )
                return actual.trimmedPath;
            actual.lazyTrimmedPath= true;

            actual.trimmedPath._();

            if( actual.origFilePathLength == -2 )
                actual.origFilePathLength= actual.origFile.LastIndexOf( Path.DirectorySeparatorChar );
            if( actual.origFilePathLength < 0 )
                return actual.trimmedPath;

            // we rather search on an the AString object, because case insensitive search is so much
            // faster as with C# strings. Even if we have to remove a prefix afterwards!
            actual.trimmedPath._( actual.origFile, 0, actual.origFilePathLength );

            int trimPos= 0;
            String  trimPrefix= null;
            // do 2 times, 0== local list, 1== global list
            for( int trimRuleNo= 0; trimRuleNo < 2 ; trimRuleNo++ )
            {
                // choosel local or global list
                List<SourcePathTrimRule> trimRulesList = trimRuleNo == 0 ? LocalSPTRs
                                                                         : GlobalSPTRs;
                // loop over trimInfo
                foreach ( SourcePathTrimRule rule in trimRulesList )
                {
                    int idx;

                    if( rule.IsPrefix )
                        idx= actual.trimmedPath.StartsWith( rule.Path, rule.Sensitivity ) ? 0 : -1;
                    else
                        idx= actual.trimmedPath.IndexOf( rule.Path, 0, rule.Sensitivity );

                    if ( idx >= 0 )
                    {
                        trimPos= idx + ( rule.IncludeString == Inclusion.Include ? rule.Path.Length() : 0 ) + rule.TrimOffset;
                        trimPrefix= rule.TrimReplacement;
                        break;
                    }
                }

                if (trimPos > 0)
                    break;
            }

            if ( trimPos > 0 )
            {
                actual.trimmedPath.DeleteStart_NC( trimPos );
                if( trimPrefix != null )
                    actual.trimmedPath.InsertAt( trimPrefix, 0 );
            }

            // if nothing was found and the flag is still set, try once to auto-detect rule
            // from the 'difference' of source path and current working directory
            else if( AutoDetectTrimableSourcePath )
            {
                AutoDetectTrimableSourcePath= false; // do this only once

                // get system execution path and compare to file path
                String currentDir= System.Environment.CurrentDirectory;

                // Get the prefix that is the same in both paths
                int i= 0;
                int maxIdx= currentDir.Length;
                if ( maxIdx > actual.trimmedPath.Length() )
                    maxIdx= actual.trimmedPath.Length();

                while (  i < maxIdx &&  Char.ToUpperInvariant( currentDir[i] ) == Char.ToUpperInvariant( actual.trimmedPath[i] )  )
                    i++;

                if ( i > 1 )
                {
                    SetSourcePathTrimRule( currentDir.Substring( 0, i ), Inclusion.Include, 0, Case.Ignore,  "", Reach.Local,
                                           Configuration.PrioDefaultValues - 1 );

                    // one recursive call
                    actual.lazyTrimmedPath= false;
                    return GetTrimmedPath();
                }
            }

            return actual.trimmedPath;
        }

        /** ****************************************************************************************
         * Receives the source file name excluding the path
         * (usually provided by System.Runtime.CompilerServices).
         * @return The source file name excluding the path
         ******************************************************************************************/
        public AString GetFileName()
        {
            SourceFile actual= scopes[actScopeDepth].sourceFile;
            if( actual.lazyName )
                return actual.name;

            actual.lazyName= true;
            actual.name._();
            if( actual.origFilePathLength == -2 )
                actual.origFilePathLength= actual.origFile.LastIndexOf( Path.DirectorySeparatorChar );
            if( actual.origFilePathLength >= 0 )
                actual.name._( actual.origFile, actual.origFilePathLength + 1 );

            return actual.name;
        }

        /** ****************************************************************************************
         * Receives the source file name excluding the path and without an extension
         * (usually provided by System.Runtime.CompilerServices).
         * @return The source file name excluding the path and extension.
         ******************************************************************************************/
        public AString GetFileNameWithoutExtension()
        {
            SourceFile actual= scopes[actScopeDepth].sourceFile;
            if( actual.lazyNameWOExt )
                return actual.nameWOExt;
            actual.lazyNameWOExt= true;

            actual.nameWOExt._()._( GetFileName() );
            int lastDot=   actual.nameWOExt.LastIndexOf( '.' );
            if ( lastDot > 0 )
                actual.nameWOExt.SetLength_NC( lastDot );
            return actual.nameWOExt;
        }


        /** ****************************************************************************************
         * Receives the method name (usually provided by System.Runtime.CompilerServices).
         * @return The method name.
         ******************************************************************************************/
        public String GetMethod()
        {
            return scopes[actScopeDepth].origMethod;
        }

        /** ****************************************************************************************
         * Receives the source file line number (usually provided by
         * System.Runtime.CompilerServices).
         * @return The source file line number.
         ******************************************************************************************/
        public int GetLineNumber()
        {
            return scopes[actScopeDepth].origLine;
        }

        /** ****************************************************************************************
         * The timestamp of the last invocation of #Set.
         * @return The latest timestamp.
         ******************************************************************************************/
        public Ticks GetTimeStamp()
        {
            return scopes[actScopeDepth].timeStamp;
        }

        /** ************************************************************************************
         * Receives the thread of the caller.
         * @returns The thread ID.
         **************************************************************************************/
        public Thread GetThread()
        {
            return thread;
        }

        /** ************************************************************************************
         * Receives the thread ID of the caller.
         * @returns The thread ID.
         **************************************************************************************/
        public int GetThreadID()
        {
            return threadID;
        }

        /** ************************************************************************************
         * Receives the translated name or, if not translated, "name(ID)" of the caller.
         * @returns The thread ID.
         **************************************************************************************/
        public AString GetThreadName()
        {
            return threadName;
        }

} // class ScopeInfo

#endif // ALOX_DBG_LOG || ALOX_REL_LOG ,started before class ScopeInfo


} // namespace
