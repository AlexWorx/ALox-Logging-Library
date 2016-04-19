// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using cs.aworx.lib;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;
using cs.aworx.lib.threads;
using System.IO;
using System.Diagnostics;
using System.Threading;

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
        protected Dictionary<int, String>          threadDictionary;


        /**  Line number within the source file (given by the diagnostics)  **/
        protected        int                       origLine;

        /**  Function/method name (given by the diagnostics)  **/
        protected        String                    origMethod;



        /** Information of a single source file. Stored in field #cache */
        protected class SourceFile
        {
            /**  'Timestamp' for LRU overwriting (not a time, but using field #cacheRun) */
            public        long                      timeStamp       = 0;

            /**  Path and name of source file (given by the C++ preprocessor)  **/
            public        String                    origFile;

            /** index of last path separator in #origFile **/
            public        int                       origFilePathSeparator;

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

        /** The actual entry of the source file cache      */
        SourceFile                                  actual;


        /** Time of the call represented by this instance.  **/
        protected        Ticks                      timeStamp                          = new Ticks();

        /** The thread that executed the log.  **/
        protected        Thread                     thread;

        /** The id of the thread that executed the log.  **/
        protected        int                        threadID;

        /** The name of the thread that executed the log.  **/
        protected        AString                    threadName                     = new AString(32);

        /**
         *  If true, next time a source path can not be trimmed successfully with custom
         *  trim information provided with
         *  \ref cs::aworx::lox::Lox::SetSourcePathTrimRule "Lox.SetSourcePathTrimRule"
         *  some trim information is automatically created by comparing such source files' path
         *  with the path of the executable of the current process.
         */
        protected bool                              AutoDetectTrimableSourcePath             = true;

    // #############################################################################################
    // Public memebers (in C++ this is protected and Lox is a friend)
    // #############################################################################################
        /**  Defines portions of source paths to be ignored  */
        public class SourcePathTrimRule
        {
            public AString    Path;                    ///< The search string
            public bool       IsPrefix;                ///< true if path was not starting with '\*' when provided.
            public Inclusion  IncludeString;           ///< Denotes if #Path itself should be included when trimmed
            public Case       Sensitivity;             ///< The sensitivity of the comparison when trimming
            public int        TrimOffset;              ///< Additional offset of the trim position
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
         * @param name              The name of the Lox we belong to
         * @param threadDictionary  A dictionary to map thread IDs to user friendly names which is
         *                          managed outside of this class.
         ******************************************************************************************/
        public ScopeInfo( String name,  Dictionary<int, String> threadDictionary )
        {
            loxName= name.ToUpper();
            ALIB.ASSERT_ERROR( !loxName.Equals( "GLOBAL" ), "Name \"GLOBAL\" not allowed for Lox instances" );

            this.threadDictionary= threadDictionary;

            cache=  new SourceFile[cacheSize= DefaultCacheSize];
            for ( int i= 0; i< cacheSize; i++ )
                cache[i]= new SourceFile();
            actual= cache[0];

            // read trim rules from config
            // do 2 times, 0== local list, 1== global list
            List<SourcePathTrimRule> trimInfoList;
            AString rules       = new AString();
            AString variableName= new AString();
            for( int trimInfoNo= 0; trimInfoNo < 2 ; trimInfoNo++ )
            {
                // check if done... or set list
                variableName._();
                if ( trimInfoNo == 0 )
                {
                    trimInfoList= LocalSPTRs;
                    variableName._( loxName );
                }
                else
                {
                    if ( GlobalSPTRsReadFromConfig )
                        continue;
                    GlobalSPTRsReadFromConfig= true;
                    trimInfoList= GlobalSPTRs;
                    variableName._( "GLOBAL" );
                }
                variableName._( "_SOURCE_PATH_TRIM_RULES" );

                // get auto sizes from last session
                rules._();
                if( ALIB.Config.Get( ALox.ConfigCategoryName, variableName, rules ) != 0 )
                {
                    Tokenizer rulesTok= new Tokenizer();
                    Tokenizer ruleTok = new Tokenizer();
                    rulesTok.Set( rules, ';' );
                    Substring ruleStr;
                    while( (ruleStr= rulesTok.Next()).IsNotEmpty() )
                    {
                        try {
                            ruleTok.Set( ruleStr, ',' );
                            SourcePathTrimRule rule= new SourcePathTrimRule();
                            rule.Path= new AString();
                            ruleTok.Next();
                            if( ! ( rule.IsPrefix= !ruleTok.Actual.StartsWith( "*" ) ) )
                                ruleTok.Actual.Consume(1);
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
                                ruleTok.Next().ConsumeInteger( out rule.TrimOffset );

                            rule.Sensitivity = ALIB.ReadCase( ruleTok.Next() );
                            trimInfoList.Add( rule);
                        }
                        catch( Exception )
                        {
                            ALIB.ERROR( "Error reading source path trim rule from configuration. Invalid String: "
                                        + ruleStr.ToString() );
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
        public void Set ( int callerLineNumber, String callerSourceFileName, String callerMemberName,
                          Thread thread )
        {
            // 1) set the actual timestamp as early as possible
            timeStamp.Set();

            // 2) save parameters
            if( actual.origFile != callerSourceFileName )
            {
                int   oldestIdx= -1;
                long  oldestTime= ++cacheRun;

                actual= null;
                for( int i= 0; i < cacheSize; i++ )
                {
                    if ( cache[i].origFile == callerSourceFileName )
                    {
                        actual= cache[i];
                        break;
                    }

                    if( oldestTime > cache[i].timeStamp )
                    {
                        oldestTime= cache[i].timeStamp;
                        oldestIdx= i;
                    }
                }

                // not found? Use the oldest
                if ( actual == null )
                {
                    actual= cache[oldestIdx];

                    actual.origFile=                callerSourceFileName;
                    actual.origFilePathSeparator=   -2;
                    actual.lazyTrimmedPath          =
                    actual.lazyName                 =
                    actual.lazyNameWOExt            =false;
                }

                // mark as used
                actual.timeStamp= cacheRun;
            }



            this.origLine=    callerLineNumber;
            this.origMethod=  callerMemberName;

            // 3) get thread information
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
         * Does the job for
         * \ref cs::aworx::lox::Lox::SetSourcePathTrimRule    "Lox.SetSourcePathTrimRule" and
         * \ref cs::aworx::lox::Lox::ClearSourcePathTrimRules "Lox.ClearSourcePathTrimRules".
         *
         * @param path          The path to search for. If not starting with <c> '*'</c>, a prefix
         *                      is searched.
         * @param includeString Determines if \p path should be included in the trimmed path or not.
         * @param trimOffset    Adjusts the portion of \p path that is trimmed. 999999 to clear!
         * @param sensitivity   Determines if the comparison of \p path with a source files' path
         *                      is performed case sensitive or not.
         * @param global        If Inclusion.Exclude, only this instance is affected. Otherwise
         *                      the setting applies to all instances of class \b Lox.
         ******************************************************************************************/
        public void   SetSourcePathTrimRule( String path, Inclusion includeString, int trimOffset,
                                             Case sensitivity,
                                             Inclusion global )
        {
            // unset current origFile to have lazy variables reset with the next invocation
            for ( int i= 0; i< cacheSize; i++ )
                cache[i].origFile= null;

            // clear command
            if ( trimOffset == 999999 )
            {
                LocalSPTRs.Clear();
                if ( global == Inclusion.Include )
                    GlobalSPTRs.Clear();
                AutoDetectTrimableSourcePath=  (includeString == Inclusion.Include);

                // reset config read flag. This is done for unit testing. Not really
                // useful/needed in real life.
                GlobalSPTRsReadFromConfig= false;
                return;
            }

            // choosel local or global list
            List<SourcePathTrimRule> trimInfoList = global == Inclusion.Include  ? GlobalSPTRs
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

            trimInfoList.Add( rule );
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
            return actual.origFile;
        }

        /** ****************************************************************************************
         * Returns the original path and filename of the source file, togehter with length,
         * of the path within this string (as output parameter) .
         * @param[out] length  Output parameter returning the length of the path string.
         * @return Gets the path of the source file (not trimmed, see #GetTrimmedPath).
         ******************************************************************************************/
        public String GetFullPath( out int length )
        {
            if( actual.origFilePathSeparator == -2 )
                actual.origFilePathSeparator= actual.origFile.LastIndexOf( Path.DirectorySeparatorChar );

            length= actual.origFilePathSeparator >= 0 ? actual.origFilePathSeparator : 0;
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
            if( actual.lazyTrimmedPath )
                return actual.trimmedPath;
            actual.lazyTrimmedPath= true;

            actual.trimmedPath._();

            if( actual.origFilePathSeparator == -2 )
                actual.origFilePathSeparator= actual.origFile.LastIndexOf( Path.DirectorySeparatorChar );
            if( actual.origFilePathSeparator < 0 )
                return actual.trimmedPath;

            // we rather search on an the AString object, because case insensitive search is so much
            // faster as with C# strings. Even if we have to remove a prefix afterwards!
            actual.trimmedPath._( actual.origFile, 0, actual.origFilePathSeparator );

            int trimPos= 0;

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
                        break;
                    }
                }

                if (trimPos > 0)
                    break;
            }

            if ( trimPos > 0 )
                actual.trimmedPath.DeleteStart_NC( trimPos );

            // if nothing was found and the flag is still set, try once to auto-detect rule
            // from the 'difference' of source path and current working directory
            else if( AutoDetectTrimableSourcePath )
            {
                AutoDetectTrimableSourcePath= false; // do this only once

                // get system execution path and compare to file path
                String currentDir= Environment.CurrentDirectory;

                // Get the prefix that is the same in both paths
                int i= 0;
                int maxIdx= currentDir.Length;
                if ( maxIdx > actual.trimmedPath.Length() )
                    maxIdx= actual.trimmedPath.Length();

                while (  i < maxIdx &&  Char.ToUpperInvariant( currentDir[i] ) == Char.ToUpperInvariant( actual.trimmedPath[i] )  )
                    i++;

                if ( i > 1 )
                {
                    String origFile= actual.origFile;
                        SetSourcePathTrimRule( currentDir.Substring( 0, i ), Inclusion.Include, 0, Case.Ignore, Inclusion.Exclude );
                    actual.origFile= origFile;

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
            if( actual.lazyName )
                return actual.name;

            actual.lazyName= true;
            actual.name._();
            if( actual.origFilePathSeparator == -2 )
                actual.origFilePathSeparator= actual.origFile.LastIndexOf( Path.DirectorySeparatorChar );
            if( actual.origFilePathSeparator >= 0 )
                actual.name._( actual.origFile, actual.origFilePathSeparator + 1 );

            return actual.name;
        }

        /** ****************************************************************************************
         * Receives the source file name excluding the path and without an extension
         * (usually provided by System.Runtime.CompilerServices).
         * @return The source file name excluding the path and extension.
         ******************************************************************************************/
        public AString GetFileNameWithoutExtension()
        {
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
            return origMethod;
        }

        /** ****************************************************************************************
         * Receives the source file line number (usually provided by
         * System.Runtime.CompilerServices).
         * @return The source file line number.
         ******************************************************************************************/
        public int GetLineNumber()
        {
            return origLine;
        }

        /** ****************************************************************************************
         * The timestamp of the last invocation of #Set.
         * @return The latest timestamp.
         ******************************************************************************************/
        public Ticks GetTimeStamp()
        {
            return timeStamp;
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
