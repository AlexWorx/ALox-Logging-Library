// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.IO;
using System.Collections.Generic;
using cs.aworx.lib.strings;
using cs.aworx.lib.strings.util;
using cs.aworx.lib.lang;
using cs.aworx.lib.system;

namespace cs.aworx.lib.config  {


/** ************************************************************************************************
 * Specialization of class #InMemoryPlugin, which reads and writes a simple configuration file
 * consisting of sections containing key/value pairs.
 *
 * This class is provided for the case that no other configuration mechanism is available.
 * In general, application specific configuration mechanisms already exist in other libraries
 * used. Those should be adopted by creating a lean interface plug-in for ALib.
 *
 * Some remarks on the functionality and supported format:
 * - Comments
 *   - Comment lines at the beginning of the file are associated with the file and are written
 *     back. Such comment block is stopped with a single blank line.
 *   - Lines that start (apart from whitespace) with either a double
 *     slash \c "//", a sharp sign \c '#' or a semicolon <c>';'</c> are comment lines.
 *   - Comment lines that are added to variables in the software are using the symbol defined in
 *     filed #DefaultCommentPrefix, which defaults to \c '#'. If this is changed in the file,
 *     such changes are preserved.
 *   - Comment lines before sections and variables are associated with the respective objects
 *     and are not overwritten by comments set in the code. However, variables without
 *     comments which are overwritten in code including comments, get such comment appended.
 *   - Comments can not reside in the same line together with section names or variables.
 *   - Commented variables receive a blank line before the comment.
 *   - Commented Sections receive two blank lines before the comment. One if they are not commented.
 *
 * - Sections:
 *   - Sections names are enclosed by brackets \c '[' and \c ']'.
 *   - Section names can be repeated. In this case the corresponding section is continued.
 *     When the file is written, the sections are merged. Otherwise the order of sections and
 *     the variables within the section is kept intact on writing.
 *
 * - Variables
 *   - Variable names and their values are separated by an equal sign \c '='.
 *   - New variables inserted are formatted according to other variables found. E.g. the
 *     equal sign of all variables within a section are aligned on the same column.
 *   - Formats of variables added or changed by the user are kept intact, as long as the
 *     software does not store a value.
 *
 * - Continued Lines:
 *   - Variables definition are being continued (values are concatenated) if the line ends
 *     with a backslash \c '\\'.
 *   - Comment lines in-between continued lines are recognized as such. To continue a variable
 *     after a 'continued' comment line, the comment line needs to end with a backslash \c '\\'.
 *   - Variables with multiple values created (or modified) in the software, are written
 *     in continued lines, with each line showing one value, ending with the variables'
 *     delimiter character and a trailing \c '\\'.
 *   - Comment lines within Variables defined in multiple lines are removed when a variable
 *     is written back.
 *
 * - Escaping values
 *   - Spaces <c>' '</c> and tabulators \c '\\t' are ignored at the start and end of each line and before
 *     and after the equal sign \c '='.
 *   - Consequently, whitespaces at the start or end of a value either need to be escaped
 *     using <c>'\\ '</c> or the whole value has to be surrounded by double quotes \c ".
 *   - Values added or modified by the software that contain spaces at the start or end
 *     are surrounded by double quotes (instead of escaping them)
 *   - Double quotes in values are always escaped when writing values and have to be escaped
 *     when editing the file.
 *   - Values may consist of a list of double quoted values. Whitespaces between such
 *     values are ignored. Consequently, long strings may be enclosed in double quotes
 *     and continued in the next line when the line ends with a backslash \c '\\'.
 *   - Almost any character can be escaped. E.g \c "\a" is read as \c 'a'.
 *   - On writing only non-printable characters and double quotation marks are escaped.
 *
 * - Other remarks
 *   - Sequences of blank lines are reduced to one blank line, when writing the file.
 *   - Erroneous lines are ignored and not written back. Line numbers with erroneous lines
 *     are collected in field #LinesWithReadErrors.
 **************************************************************************************************/
public class IniFile : InMemoryPlugin
{
    // #############################################################################################
    // Public enums
    // #############################################################################################
        /** ****************************************************************************************
         * Status codes
         ******************************************************************************************/
        public enum Status
        {
            /**  All went well */
            OK,

            /**  File not found when reading. This is not necessarily an error.*/
            ERROR_OPENING_FILE,

            /**  An error occurred writing the file .*/
            ERROR_WRITING_FILE
        }

    // #############################################################################################
    // inner classes
    // #############################################################################################

        /** ****************************************************************************************
         * A configuration sections' entry
         ******************************************************************************************/
        public new class Entry : InMemoryPlugin.Entry
        {
            /** The raw string as read from the INI file. Ready to be written back when
             * variable is untouched. */
            public AString       RawValue   = new AString();

            /**
             * Constructs an Entry
             * @param name    The name of the section.
             */
            public Entry( Object name ) : base(name)
            {
            }

            /**
             * Overrides default method. If we have not parsed the INI file text value, yet,
             * we do this now.
             *
             * @param parent    The plug-in we belong to.
             * @param variable  The variable to fill with our values.
             */
            public override void ToVariable( InMemoryPlugin parent, Variable variable )
            {
                // if this had been done before, use base method
                if ( Values.Count > 0  )
                {
                    base.ToVariable( parent, variable );
                    return;
                }

                // store delim and comment
                Delim= variable.Delim;
                variable.Comments._()._( Comments );

                //-----  remove INI-File specific from raw value -----
                AString raw= new AString();
                raw._( RawValue );

                // remove '='
                raw.TrimStart();
                if ( raw.CharAtStart() == '=' )
                    raw.DeleteStart(1).TrimStart();
                else
                    ALIB_DBG.WARNING( "No equal sign in variable \"" + variable.Fullname + "\" of INI file." );


                // remove "\\n"
                int startIdx= 0;
                while ( (startIdx= raw.IndexOf( '\n', startIdx )) >= 0 )
                {
                    // find \\n and trim around this location
                    int delLen= 2;
                    if ( raw.CharAt( --startIdx) == '\r' )
                    {
                        delLen= 3;
                        --startIdx;
                    }
                    ALIB_DBG.ASSERT( raw.CharAt(startIdx) == '\\' );
                    raw.Delete( startIdx, delLen );

                    startIdx= raw.TrimAt( startIdx );
                    if( startIdx >= raw.Length() )
                        break;

                    // remove endquote of first line and start quote of second
                    if( startIdx >0 && raw[startIdx-1] == '"' && raw[startIdx] == '"' )
                    {
                        startIdx--;
                        raw.Delete( startIdx, 2);
                    }

                    // if now the next value is starting with a comment symbol, we remove to the next \n
                    for(;;)
                    {
                        char c= raw.CharAt( startIdx );
                        if (     c != '#'
                            &&   c != ';'
                            && ( c != '/' || raw.CharAt( startIdx + 1 ) != '/' ) )
                            break;

                        int idx= raw.IndexOf( '\n' );
                        if (idx < 0 ) idx= raw.Length();
                        raw.Delete( startIdx, idx - startIdx + 1 );
                        if( startIdx >= raw.Length() )
                            break;
                        startIdx= raw.TrimAt( startIdx );
                    }
                }

                // now convert
                parent.StringConverter.LoadFromString( variable, raw );

                // copy the parsed values back to our entry and store the delimiter
                for( int i= 0; i < variable.Size() ; i++ )
                    Values.Add( new AString( variable.GetString( i ) ) );
            }

            /**
             * Overrides default method. Clears the raw value, and calls base method.
             *
             * @param parent    The plug-in we belong to.
             * @param variable  The variable to fill with our values.
             */
            public override void FromVariable( InMemoryPlugin parent, Variable variable )
            {
                RawValue._();
                base.FromVariable( parent, variable );
            }
        }

        /** ****************************************************************************************
         * A configuration section
         ******************************************************************************************/
        public new class Section : InMemoryPlugin.Section
        {
            /**
             * Constructs a Section
             * @param name    The name of the section.
             *                (AString compatible type expected.)
             */
            public  Section( Object name ) :base(name) {}

            /**
             * Overrides base classes method to create an entry of our type.
             * @param name    The name of the entry.
             * @return An object of type \ref Entry "IniFile.Entry".
             */
            protected override InMemoryPlugin.Entry  createEntry( Object name )
            {
                return new IniFile.Entry( name );
            }
        }

    // #############################################################################################
    // Public fields
    // #############################################################################################

        /** If this is set to true, any variable change will lead to writing the file immediately
            by invoking #WriteFile. Defaults to false */
        public bool                             AutoSave                                    = false;

        /** The file name. This might include a path or not. Should be set properly before
            the file is read. */
        public AString                          FileName                            = new AString();

        /** The standard file extension used for ALib configuration files. Defaults to ".ini" */
        public static String                    DefaultFileExtension                       = ".ini";

        /** The file header which will be written out as a comment lines with "# " prefixes */
        public AString                          FileComments                        = new AString();

        /** The status. */
        public  Status                          LastStatus                              = Status.OK;

        /** Is cleared and filled with faulty line numbers when reading the file. (E.g. when a
            line is no section and no comment but still has no equal sign ('=').  */
        public List<int>                        LinesWithReadErrors               = new List<int>();

        /**
         * The prefix that is used for comment lines of sections or variables that have been
         * added 'in code' (variables that have not been read from the file).
         * Comments that were read from the file preserve their prefix.
         * If comments including one of the valid prefixes are added to a variable or section
         * 'in code', such prefix is preserved. */
        public String                           DefaultCommentPrefix                        =  "# ";

        /** Denotes if a space should be written before a delimiter. */
        public bool                             FormatSpaceBeforeDelim                      = false;

        /** Denotes if a space should be written after a delimiter. (Applies only to single
            line mode of writing attributes.)  */
        public bool                             FormatSpaceAfterDelim                       =  true;

        /** Denotes whether the spaces that are inserted when aligning attributes are
         *  located before or behind the delimiter. */
        public bool                             FormatIncludeDelimInAttrAlignment           = false;

    // #############################################################################################
    // Protected fields
    // #############################################################################################
        /** Characters that start a comment */
        protected   AString                     commentChars                =  new AString( "#;/" );

    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
        /** ****************************************************************************************
         * Constructs an instance of this class and reads the file.
         * If no file name is given, the file name set to the process name with extension
         * ".ini" while the file path is retrieved using
         * <em>Environment.GetFolderPath( Environment.SpecialFolder.ApplicationData )</em>.
         *
         * If the given file name \p{filePathAndName} starts with '*', no file is read and field
         * #AutoSave is set to \c false.
         *
         * @param filePathAndName  The name (and path) of the file to read and write.
         *                         Provide "*" to suppress reading a file.
         *                         Defaults to \c null.
         ******************************************************************************************/
        public IniFile( String filePathAndName=  null )
        : base()
        {
            if ( filePathAndName != null )
            {
                // dont read anything
                if ( filePathAndName.StartsWith( "*" ) )
                {
                    AutoSave= false;
                    return;
                }

                FileName._( filePathAndName );
            }
            else
            {
                String path= System.Environment.GetFolderPath( System.Environment.SpecialFolder.ApplicationData );
                if ( !Directory.Exists( path ) )
                    path=  System.Environment.GetFolderPath( System.Environment.SpecialFolder.UserProfile );

                FileName._( path )
                        ._( Path.DirectorySeparatorChar )
                        ._( ProcessInfo.GetCurrentProcessName() )
                        ._( DefaultFileExtension  );
            }

            ReadFile();
        }


    // #############################################################################################
    // ConfigurationPlugin interface implementation
    // #############################################################################################
        /** ****************************************************************************************
         * Creates or replaces existing variable in our storage. If #AutoSave is set, the file
         * is written
         *
         * @param variable  The variable to retrieve.
         * @return \c true if the variable was written, \c false if not. The latter might only
         *         happen if the variable given was illegal, e.g. empty name.
         ******************************************************************************************/
        public override bool  Store( Variable variable )
        {
            base.Store( variable );
            if ( AutoSave )
                WriteFile();
            return true;
        }


    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         * Clears all configuration data.
         ******************************************************************************************/
        public override void            Reset()
        {
            base.Reset();
            FileComments.Clear();
            LinesWithReadErrors.Clear();
            LastStatus= Status.OK;
        }

    // #############################################################################################
    // file IO
    // #############################################################################################

        /** ****************************************************************************************
         * Clears all configuration data and reads the file. It might happen that lines are
         * ignored or otherwise marked as faulty. All numbers of such lines get collected in
         * field LinesWithReadErrors.
         * @return Returns the #Status of the operation.
         ******************************************************************************************/
        public IniFile.Status  ReadFile()
        {
            Reset();
            LastStatus= Status.OK;

            // read all variables
            StreamReader file;
            try
            {
                file= new StreamReader( FileName.ToString() );
            }
            catch( Exception )
            {
                return LastStatus= Status.ERROR_OPENING_FILE;
            }

            String      lineS;
            AString     name=       new AString();
            AString     value=      new AString();
            AString     comments=   new AString();
            Section     actSection= (IniFile.Section) Sections[0];
            Substring   line=       new Substring();

            int         lineNo= 0;
            bool        fileHeaderRead= false;

            char[]      separatorCharacters= value._( "=" )._( CString.DefaultWhitespaces )
                                                  .ToString().ToCharArray();

            LinesWithReadErrors.Clear();
            while ( (lineS= file.ReadLine()) != null )
            {
                lineNo++;

                bool isEmpty=       line.Set( lineS ).Trim().IsEmpty();
                bool isCommentLine= startsWithCommentSymbol( line );

                if ( isCommentLine )
                {
                    if ( comments.IsNotEmpty() )
                        comments.NewLine();
                    comments._(line);
                    continue;
                }

                // still processing file header?
                if ( !fileHeaderRead )
                {
                    fileHeaderRead= true;
                    FileComments._()._( comments );
                    comments.Clear();
                }

                // empty line?
                if ( isEmpty )
                {
                    if ( comments.IsNotEmpty() )
                        comments.NewLine();
                    continue;
                }

                // section line
                if ( line.ConsumeChar( '[' ) )
                {
                    fileHeaderRead= true;

                    // we do not care if there is no closing bracket. But if there is one, we remove it.
                    if( !line.ConsumeCharFromEnd(']') )
                        LinesWithReadErrors.Add( lineNo );

                    // search the section in our section list (if section existed already, new comments
                    // are dropped)
                    actSection= (IniFile.Section) SearchOrCreateSection( line, comments);
                    comments.Clear();

                    continue;
                }

                // variable line?
                value.Clear();
                int idx= line.IndexOfAny( separatorCharacters, Inclusion.Include );
                if( idx < 0 )
                {
                    name._()._( line );
                    line.Clear();
                }
                else
                {
                    name._()._( line.Buf, line.Start, idx );
                    line.ConsumeChars( idx );
                    value._(line);
                }

                // read continues as long as lines end with '\' (must not be '\\')
                while (     line.CharAtEnd()  == '\\'
                        &&  line.CharAtEnd(1) != '\\' )
                {
                    value.NewLine();

                    if ( (lineS= file.ReadLine()) == null  )
                    {
                        // last line of the file ended with '\' !
                        line.Clear();
                        break;
                    }
                    line.Set( lineS ).TrimEnd();
                    value._( line );
                }

                // insert entry with raw value
                {
                    IniFile.Entry entry= (IniFile.Entry) actSection.GetEntry( name, true );
                    entry.Values  .Clear();
                    entry.Comments._()._( comments );
                    entry.RawValue._()._( value );

                    // if there is just no raw value, we add an empty string to the entries' values
                    if ( value.IsEmpty() )
                        entry.Values.Add( new AString() );
                }

                comments.Clear();

            }
            file.Close();

            return LastStatus;
        }


        /** ****************************************************************************************
         * Helper method for formatting attributes
         * @param value              The value to check
         * @param alignmentSeparator The string defining the separator.
         * @return Returns the position of the first '=' or ':' character
         ******************************************************************************************/
        protected static int getAssignmentPos( AString value, String alignmentSeparator )
        {
            int idx= value.IndexOf( alignmentSeparator );
            if( idx > 0 )
            {
                int idxQuote= value.IndexOfOrLength( '"' );
                if (idxQuote > idx )
                    return idx;
            }
            return -1;
        }

        /** ****************************************************************************************
         * Write all configuration data into the file.
         * @return Returns the #Status of the operation.
         ******************************************************************************************/
        public IniFile.Status  WriteFile()
        {
            LastStatus= Status.OK;

            // open file
            StreamWriter file;
            try
            {
                file= new StreamWriter( FileName.ToString() );
            }
            catch( Exception )
            {
                return LastStatus= Status.ERROR_OPENING_FILE;
            }

            Tokenizer tknzr=               new Tokenizer();
            AString   externalizedValue=   new AString();

            // write file header
            if ( FileComments.IsNotEmpty() )
            {
                writeComments( file, FileComments, tknzr );
                file.WriteLine();
            }

            // loop over all sections
            int cntVars= 0;
            foreach ( Section section in Sections )
            {
                if ( cntVars > 0 )
                    file.WriteLine();

                // write section comments and name
                writeComments( file, section.Comments, tknzr );
                if ( section.Name.IsNotEmpty() )
                {
                    file.Write('[');
                    file.Write( section.Name.Buffer(), 0, section.Name.Length() );
                    file.WriteLine(']');
                }

                // variables
                int maxVarLength= 0;
                foreach ( Entry entry in section.Entries )
                    maxVarLength= Math.Max( maxVarLength, entry.Name.Length() );

                bool previousVarHasComments= true;
                foreach ( Entry entry in section.Entries )
                {
                    cntVars++;

                    // write comments
                    if( entry.Comments.IsNotEmpty() )
                    {
                        // we make an extra empty line if previous var had no comments
                        if( !previousVarHasComments)
                            file.WriteLine();
                        writeComments( file, entry.Comments, tknzr );
                    }

                    // write name =
                    file.Write( entry.Name.Buffer(), 0, entry.Name.Length() );

                    // either write raw value (if it was not used by the application)
                    IniFile.Entry ifEntry= (IniFile.Entry) entry;
                    if ( ifEntry.RawValue.IsNotEmpty() )
                    {
                        file.Write( ifEntry.RawValue.Buffer(), 0, ifEntry.RawValue.Length() );
                    }

                    // or write the values parsed by the software
                    else
                    {
                        file.Write( '=' );
                        Spaces.Write( file, maxVarLength - entry.Name.Length() + 1 );

                        bool     isFirst=      true;

                        //-------- write as single-line ----------
                        if ( 0 == ( entry.FormatHints & Variable.FormatHint.MultLine  ) )
                        {
                            bool delimSpaces=  (0 == ( entry.FormatHints & Variable.FormatHint.NoDelimSpaces ) );
                            foreach( AString value in entry.Values )
                            {
                                // write delim and backslash of previous line, newline and then spaces of actual line
                                if ( !isFirst )
                                {
                                    ALIB_DBG.ASSERT_ERROR( entry.Delim != 0,
                                                       "No delimiter given for multi-value variable \""
                                                       + entry.Name + "\"." );

                                    if( delimSpaces && FormatSpaceBeforeDelim)
                                        file.Write( ' ' );

                                    file.Write( entry.Delim );

                                    if( delimSpaces && FormatSpaceAfterDelim)
                                        file.Write( ' ' );
                                }

                                // externalize value
                                externalizedValue._();
                                StringConverter.ExternalizeValue( value, externalizedValue, entry.Delim );
                                file.Write( externalizedValue.Buffer(), 0, externalizedValue.Length() );
                                isFirst= false;
                            }
                        }

                        // ---------- write as multi-line ----------
                        else
                        {
                            int      backSlashPos= 0;
                            int      lastLineLen=  0;

                            // Get maximum position of attribute assignment char '=' or ':' (if exists)
                            int maxAttributeAssignPos= 0;
                            bool allAttrHavePrecedingBlanks= true;
                            if (entry.FormatAttrAlignment != null )
                            {
                                foreach( AString value in entry.Values )
                                {
                                    int attributeAssignPos= getAssignmentPos( value, entry.FormatAttrAlignment );
                                    if ( attributeAssignPos > 0 )
                                    {
                                        if ( maxAttributeAssignPos < attributeAssignPos )
                                            maxAttributeAssignPos= attributeAssignPos;
                                        allAttrHavePrecedingBlanks&= value.CharAt( attributeAssignPos - 1 ) == ' ';
                                    }
                                }
                                if ( !allAttrHavePrecedingBlanks )
                                    maxAttributeAssignPos += 1;
                            }

                            // loop over values of entry
                            foreach( AString value in entry.Values )
                            {

                                // write delim and backslash of previous line, newline and then spaces of actual line
                                if ( !isFirst )
                                {
                                    ALIB_DBG.ASSERT_ERROR( entry.Delim != 0,
                                                       "No delimiter given for multi-value variable \""
                                                       + entry.Name + "\"." );

                                    file.Write( entry.Delim );

                                    if ( backSlashPos < lastLineLen + 1  )
                                         backSlashPos=  lastLineLen + 4;

                                    Spaces.Write( file, backSlashPos - lastLineLen );

                                    file.WriteLine( '\\' );

                                    Spaces.Write( file, maxVarLength + 2 ); // 2 for "= "
                                }

                                // externalize value
                                externalizedValue._();
                                StringConverter.ExternalizeValue( value, externalizedValue, entry.Delim );

                                // if first character is a INI comment char, then escape it
                                char firstChar= externalizedValue.CharAt(0);
                                if( !isFirst && (firstChar == '#' || firstChar == ';' ) )
                                    externalizedValue.InsertAt("\\", 0 );

                                // if assignment, insert spaces to align assignments
                                if (entry.FormatAttrAlignment != null )
                                {
                                    int attributeAssignPos= getAssignmentPos( externalizedValue, entry.FormatAttrAlignment );
                                    if ( attributeAssignPos > 0 && attributeAssignPos < maxAttributeAssignPos )
                                        externalizedValue.InsertChars( ' ',
                                                                       maxAttributeAssignPos-attributeAssignPos,
                                                                       attributeAssignPos + (FormatIncludeDelimInAttrAlignment ?
                                                                                              0 : entry.FormatAttrAlignment.Length )
                                                                      );
                                }

                                file.Write( externalizedValue.Buffer(), 0, externalizedValue.Length() );

                                lastLineLen=  maxVarLength + 2  + externalizedValue.Length();
                                isFirst= false;
                            }
                        }
                    }
                    file.WriteLine();

                    // add an empty line if we have comments
                    if( (previousVarHasComments= entry.Comments.IsNotEmpty() ) == true )
                        file.WriteLine();
                }
            }

            // close file
            file.Close();

            return LastStatus;
        }

    // #############################################################################################
    // Protected methods
    // #############################################################################################

        /** ****************************************************************************************
         * Overrides base classes method to create a section of our type.
         *
         * @param name    The name of the section.
         * @return An object of type \ref Section "IniFile.Section".
         ******************************************************************************************/
        protected override InMemoryPlugin.Section  createSection( Object name )
        {
            return new IniFile.Section( name );
        }

        /** ****************************************************************************************
         * Helper method used when reading file.
         * @param subs    A sub-string.
         * @return true if provided substring starts with comment character.
         ******************************************************************************************/
        protected bool startsWithCommentSymbol( Substring subs )
        {
            int i= commentChars.IndexOfOrLength( subs.CharAtStart() );
            return       i <  2
                    || ( i == 2 && subs.Length() > 1 && subs.CharAt(1) == '/'  );
        }

        /** ****************************************************************************************
         * Writes a list of comments to the file. Comment lines are started with '#'.
         * @param os       The output stream to write to.
         * @param comments The comment lines for the section.
         * @param tknzr    A temporary tokenizer needed internally.
         ******************************************************************************************/
        protected void writeComments( TextWriter os, AString comments, Tokenizer tknzr )
        {
            // is empty when trimmed? (we are lenting tokeinizers field 'actual' to test)
            if ( tknzr.Actual.Set( comments ).Trim().IsEmpty() )
                return;

            // tokenize by NEWLINE character
            tknzr.Set( comments, '\n' );
            char[] oldWhiteSpaces= tknzr.Whitespaces;
            tknzr.Whitespaces=  " \r\t".ToCharArray(); // \n is not a whitespace

            while( tknzr.Next(Whitespaces.Keep).IsNotNull() )
            {
                if ( !startsWithCommentSymbol( tknzr.Actual ) )
                    os.Write( DefaultCommentPrefix );
                os.WriteLine( tknzr.Actual.Buf, tknzr.Actual.Start, tknzr.Actual.Length() );
            }
            tknzr.Whitespaces= oldWhiteSpaces;
        }

} // class

}// namespace

