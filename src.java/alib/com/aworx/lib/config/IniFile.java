// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import java.io.*;
import java.util.ArrayList;

import com.aworx.lib.lang.Inclusion;
import com.aworx.lib.lang.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.util.Tokenizer;
import com.aworx.lib.strings.util.Spaces;

/** ************************************************************************************************
 * Specialization of class #InMemoryPlugin, which reads and writes a simple configuration file
 * consisting of sections containing key/value pairs.
 *
 * This class is provided for the case that no other configuration mechanism is available.
 * In general, application specific configuration mechanisms already exist in other libraries
 * used. Those should be adopted by creating a lean interface plug-in for \b %ALib.
 *
 * Some remarks on the functionality and supported format:
 * - Comments
 *   - Comment lines at the beginning of the file are associated with the file and are written
 *     back. Such comment block is stopped with a single blank line.
 *   - Lines that start (apart from whitespace) with either a double
 *     slash \c "//", a sharp sign \c '#' or a semicolon <c>';'</c> are comment lines.
 *   - Comment lines that are added to variables in the software are using the symbol defined in
 *     filed #defaultCommentPrefix, which defaults to \c '#'. If this is changed in the file,
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
 *     are collected in field #linesWithReadErrors.
 **************************************************************************************************/
public class IniFile extends InMemoryPlugin
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
        public class Entry extends InMemoryPlugin.Entry
        {
            /** The raw string as read from the INI file. Ready to be written back when
             * variable is untouched. */
            public AString       rawValue   = new AString();

            /**
             * Constructs an Entry
             * @param name    The name of the section.
             */
            public Entry( CharSequence name )
            {
                super( name );
            }


            /**
             * Overrides default method. If we have not parsed the INI file text value, yet,
             * we do this now.
             *
             * @param parent    The plug-in we belong to.
             * @param variable  The variable to fill with our values.
             */
            @Override
            public void toVariable( InMemoryPlugin parent, Variable variable )
            {
                // if this had been done before, use base method
                if ( values.size() > 0 )
                {
                    super.toVariable( parent, variable );
                    return;
                }

                // store delim and comment
                delim= variable.delim;
                variable.comments._()._( comments );

                //-----  remove INI-File specific from raw value -----
                AString raw= new AString();
                raw._( rawValue );

                // remove '='
                raw.trimStart();
                if ( raw.charAtStart() == '=' )
                    raw.deleteStart(1).trimStart();
                else
                    com.aworx.lib.ALIB_DBG.WARNING( "No equal sign in variable \"" + variable.fullname + "\" of INI file." );


                // remove "\\n"
                int startIdx= 0;
                while ( (startIdx= raw.indexOf( '\n', startIdx )) >= 0 )
                {
                    // find \\n and trim around this location
                    int delLen= 2;
                    if ( raw.charAt( --startIdx) == '\r' )
                    {
                        delLen= 3;
                        --startIdx;
                    }
                    com.aworx.lib.ALIB_DBG.ASSERT( raw.charAt(startIdx) == '\\' );
                    raw.delete( startIdx, delLen );

                    startIdx= raw.trimAt( startIdx );
                    if( startIdx >= raw.length() )
                        break;

                    // remove endquote of first line and start quote of second
                    if( startIdx >0 && raw.charAt(startIdx-1) == '"' && raw.charAt(startIdx) == '"' )
                    {
                        startIdx--;
                        raw.delete( startIdx, 2);
                    }

                    // if now the next value is starting with a comment symbol, we remove to the next \n
                    for(;;)
                    {
                        char c= raw.charAt( startIdx );
                        if (     c != '#'
                            &&   c != ';'
                            && ( c != '/' || raw.charAt( startIdx + 1 ) != '/' ) )
                            break;

                        int idx= raw.indexOf( '\n' );
                        if (idx < 0 ) idx= raw.length();
                        raw.delete( startIdx, idx - startIdx + 1 );
                        if( startIdx >= raw.length() )
                            break;
                        startIdx= raw.trimAt( startIdx );
                    }
                }

                // now convert
                parent.stringConverter.loadFromString( variable, raw );

                // copy the parsed values back to our entry and store the delimiter
                for( int i= 0; i < variable.size() ; i++ )
                    values.add( new AString( variable.getString( i ) ) );
            }

            /**
             * Overrides default method. Clears the raw value, and calls base method.
             *
             * @param parent    The plug-in we belong to.
             * @param variable  The variable to fill with our values.
             */
            @Override
            public void fromVariable( InMemoryPlugin parent, Variable variable )
            {
                rawValue._();
                super.fromVariable( parent, variable );
            }

        }

        /** ****************************************************************************************
         * A configuration section
         ******************************************************************************************/
        public class Section extends InMemoryPlugin.Section
        {
            /**
             * Constructs a Section
             * @param name    The name of the section.
             *                (AString compatible type expected.)
             */
            public  Section( CharSequence name )  { super(name); }

            /**
             * Overrides base classes method to create an entry of our type.
             * @param name    The name of the entry.
             * @return An object of type \ref Entry "IniFile.Entry".
             */
            @Override
            protected InMemoryPlugin.Entry  createEntry( @SuppressWarnings ("hiding") CharSequence name )
            {
                return new IniFile.Entry( name );
            }
        }

    // #############################################################################################
    // Public fields
    // #############################################################################################

        /** If this is set to true, any variable change will lead to writing the file immediately
            by invoking #writeFile. Defaults to false */
        public boolean                          autoSave                                    = false;

        /** The standard file extension used for \b %ALib configuration files. Defaults to "ini" */
        public static String                    DEFAULT_FILE_EXTENSION                     = ".ini";

        /** The file name. This might include a path or not. Should be set properly before
            the file is read. */
        public AString                          fileName                            = new AString();

        /** The file header which will be written out as a comment lines with "# " prefixes */
        public AString                          fileComments                        = new AString();

        /** The status. */
        public  Status                          lastStatus                              = Status.OK;

        /** Is cleared and filled with faulty line numbers when reading the file. (E.g. when a
            line is no section and no comment but still has no equal sign ('=').  */
        public ArrayList<Integer>               linesWithReadErrors      = new ArrayList<Integer>();

        /**
        The prefix that is used for comment lines of sections or variables that have been
         * added 'in code' (variables that have not been read from the file).
         * Comments that were read from the file preserve their prefix.
         * If comments including one of the valid prefixes are added to a variable or section
         * 'in code', such prefix is preserved. */
        public String                           defaultCommentPrefix                        =  "# ";

        /** Denotes if a space should be written before a delimiter. */
        public boolean                          formatSpaceBeforeDelim                      = false;

        /** Denotes if a space should be written after a delimiter. (Applies only to single
            line mode of writing attributes.)  */
        public boolean                          formatSpaceAfterDelim                       =  true;

        /** Denotes whether the spaces that are inserted when aligning attributes are
         *  located before or behind the delimiter. */
        public boolean                          formatIncludeDelimInAttrAlignment           = false;

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
         * If no file name is given, the file name set to the name of the executed class
         * with extension ".ini". The path is then chosen as follows:
         * - on Unix like systems: if exists, to the folder ".config" in the users home directory
         *   and just to the users home directory otherwise
         * - on Windows OS: if exists, to the folder "AppData/Roaming" in the users home directory
         *   and just to the users home directory otherwise
         *
         *
         * If the given file name \p{filePathAndName} starts with '*', no file is read and field
         * #autoSave is set to \c false.
         *
         * @param filePathAndName  The name (and path) of the file to read and write.
         *                         Provide "*" to suppress reading a file.
         *                         Defaults to \c null.
         ******************************************************************************************/
        public IniFile( String filePathAndName )
        {
            super();
            construct( filePathAndName );
        }


        /** ****************************************************************************************
         * Overloaded constructor providing default value \c null for parameter \p{filePathName}.
         ******************************************************************************************/
        public IniFile()
        {
            super();
            construct( null );
        }

        /** ****************************************************************************************
         * Implementation helper of the constructors.
         *
         * @param filePathAndName  The constructor parameter.
         ******************************************************************************************/
        protected void construct( String filePathAndName )
        {
            if ( filePathAndName != null )
            {
                // dont read anything
                if ( filePathAndName.startsWith( "*" ) )
                {
                    autoSave= false;
                    return;
                }
                fileName._( filePathAndName );
            }
            else
            {
                AString path= new AString( System.getProperty( "user.home" ) );

                // check if ~/.config exists
                int actLen= path.length();
                path._( File.separatorChar )._( ".config" );
                File test = new File( path.toString() );
                if (!test.exists() || !test.isDirectory())
                {
                    path.delete_NC( actLen, 100 );

                    // check if "Appdata\Roaming" exists
                    path._( File.separatorChar )._( "AppData" )._( File.separatorChar )._( "Roaming" );
                    File test2 = new File( path.toString() );
                    if (!test2.exists() || !test2.isDirectory())
                    {
                        path.delete_NC( actLen, 100 );
                    }
                }

                StackTraceElement[] stack=          Thread.currentThread ().getStackTrace ();

                StackTraceElement ste= null;
                for( int i= 0 ; i< stack.length; i++ )
                {
                    ste= stack[i];
                    if( ste.getMethodName().equals("main") )
                        break;
                }
                @SuppressWarnings ("null")
                AString mainClassName=  new AString( ste.getClassName () );

                int dotPos= mainClassName.lastIndexOf( '.' );
                if (dotPos > 0)
                    mainClassName.delete_NC( 0, dotPos + 1 );

                fileName._NC( path )._( File.separatorChar )._NC( mainClassName )._NC( DEFAULT_FILE_EXTENSION );
            }

            readFile();
        }

    // #############################################################################################
    // ConfigurationPlugin interface implementation
    // #############################################################################################

        /** ****************************************************************************************
         * Creates or replaces existing variable in our storage. If #autoSave is set, the file
         * is written
         *
         * @param variable  The variable to retrieve.
         * @return \c true if the variable was written, \c false if not. The latter might only
         *         happen if the variable given was illegal, e.g. empty name.
         ******************************************************************************************/
        @Override
        public boolean  store( Variable variable )
        {
            super.store( variable );
            if ( autoSave )
                writeFile();
            return true;
        }


    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         * Clears all configuration data.
         ******************************************************************************************/
        @Override
        public void            reset()
        {
            super.reset();
            // constructed, yet? (Happens with constructor: super() calling reset() before we are
            // initialized )
            if ( fileComments != null )
            {
                fileComments.clear();
                linesWithReadErrors.clear();
                lastStatus= Status.OK;
            }
        }

    // #############################################################################################
    // file IO
    // #############################################################################################
        /** ****************************************************************************************
         * Clears all configuration data and reads the file. It might happen that lines are
         * ignored or otherwise marked as faulty. All numbers of such lines get collected in
         * field LinesWithReadErrors.
         * @return Returns the \ref IniFile.Status "Status" of the operation.
         ******************************************************************************************/
        @SuppressWarnings ("resource")
        public IniFile.Status  readFile()
        {
            reset();
            lastStatus= Status.OK;

            // read all variables
            BufferedReader file = null;
            try
            {
                file=  new BufferedReader(new FileReader(fileName.toString()));

                String      lineS;
                AString     name=       new AString();
                AString     value=      new AString();
                AString     comments=   new AString();
                Section     actSection= (IniFile.Section) sections.get( 0 );
                Substring   line=       new Substring();

                int         lineNo= 0;
                boolean     fileHeaderRead= false;

                char[]      separatorCharacters= value._( "=" )._( CString.DEFAULT_WHITESPACES)
                                                      .toString().toCharArray();

                linesWithReadErrors.clear();
                while ( (lineS= file.readLine()) != null )
                {
                    lineNo++;

                    boolean isEmpty=       line.set( lineS ).trim().isEmpty();
                    boolean isCommentLine= startsWithCommentSymbol( line );

                    if ( isCommentLine )
                    {
                        if ( comments.isNotEmpty() )
                            comments.newLine();
                        comments._(line);
                        continue;
                    }

                    // still processing file header?
                    if ( !fileHeaderRead )
                    {
                        fileHeaderRead= true;
                        fileComments._()._(comments);
                        comments.clear();
                    }

                    // empty line?
                    if ( isEmpty )
                    {
                        if ( comments.isNotEmpty() )
                            comments.newLine();
                        continue;
                    }

                    // section line
                    if ( line.consumeChar( '[' ) )
                    {
                        fileHeaderRead= true;

                        // we do not care if there is no closing bracket. But if there is one, we remove it.
                        if( !line.consumeCharFromEnd( ']' ) )
                            linesWithReadErrors.add( new Integer( lineNo ) );


                        // search the section in our section list (if section existed already, new comments
                        // are dropped)
                        actSection= (IniFile.Section) searchOrCreateSection( line, comments );
                        comments.clear();

                        continue;
                    }

                    // variable line?
                    value.clear();
                    int idx= line.indexOfAny( separatorCharacters, Inclusion.INCLUDE );
                    if( idx < 0 )
                    {
                        name._()._( line );
                        line.clear();
                    }
                    else
                    {
                        name._()._( line.buf, line.start, idx );
                        line.consumeChars( idx );
                        value._(line);
                    }

                    // read continues as long as lines end with '\' (must not be '\\')
                    while (     line.charAtEnd()  == '\\'
                            &&  line.charAtEnd(1) != '\\' )
                    {
                        value.newLine();

                        if ( (lineS= file.readLine()) == null  )
                        {
                            // last line of the file ended with '\' !
                            line.clear();
                            break;
                        }

                        line.set( lineS ).trimEnd();
                        value._( line );
                    }

                    // insert entry with raw value
                    {
                        IniFile.Entry entry= (IniFile.Entry) actSection.getEntry( name, true );
                        entry.values  .clear();
                        entry.comments._()._( comments );
                        entry.rawValue._()._( value );

                        // if there is just no raw value, we add an empty string to the entries' values
                        if ( value.isEmpty() )
                            entry.values.add( new AString() );
                    }

                    comments.clear();
                }
            }
            catch( @SuppressWarnings ("unused") Exception e )
            {
                lastStatus= Status.ERROR_OPENING_FILE;
            }

            try
            {
                if( file!= null )
                    file.close();
            }catch( @SuppressWarnings ("unused") Exception e ) {/* void */}

            return lastStatus;
        }

        /** ****************************************************************************************
         * Helper method for formatting attributes
         * @param value              The value to check
         * @param alignmentSeparator The string defining the separator.
         * @return Returns the position of the first '=' or ':' character
         ******************************************************************************************/
        protected static int getAssignmentPos( AString value, String alignmentSeparator )
        {
            int idx= value.indexOf( alignmentSeparator );
            if( idx > 0 )
            {
                int idxQuote= value.indexOfOrLength( '"' );
                if ( idxQuote > idx )
                    return idx;
            }
            return -1;
        }

        /** ****************************************************************************************
         * Write all configuration data into the file.
         * @return Returns the \ref IniFile.Status "Status" of the operation.
         ******************************************************************************************/
        public IniFile.Status  writeFile()
        {
            lastStatus= Status.OK;

            // open file
            try
            {
                BufferedWriter file=  new BufferedWriter(new FileWriter(fileName.toString()));


                Tokenizer tknzr=                new Tokenizer();
                AString   externalizedValue=    new AString();

                // write file header
                if ( fileComments.isNotEmpty() )
                {
                    writeComments( file, fileComments, tknzr );
                    file.newLine();
                }

                // loop over all sections
                int cntVars= 0;
                for ( InMemoryPlugin.Section section : sections )
                {
                    if ( cntVars > 0 )
                        file.newLine();

                    // write section comments and name
                    writeComments( file, section.comments, tknzr );
                    if ( section.name.isNotEmpty() )
                    {
                        file.write('[');
                        file.write( section.name.buffer(), 0, section.name.length() );
                        file.write(']');
                        file.newLine();
                    }

                     // variables
                    int maxVarLength= 0;
                    for ( InMemoryPlugin.Entry entry : section.entries )
                        maxVarLength= Math.max( maxVarLength, entry.name.length() );

                    boolean previousVarHasComments= true;
                    for ( InMemoryPlugin.Entry entry : section.entries )
                    {
                        cntVars++;

                        // write comments
                        if( entry.comments.isNotEmpty() )
                        {
                            // we make an extra empty line if previous var had no comments
                            if( !previousVarHasComments)
                                file.newLine();
                            writeComments( file, entry.comments, tknzr );
                        }

                        // write name =
                        file.write( entry.name.buffer(), 0, entry.name.length() );

                        // either write raw value (if it was not used by the application)
                        IniFile.Entry ifEntry= (IniFile.Entry) entry;

                        if ( ifEntry.rawValue.isNotEmpty() )
                        {
                            file.write( ifEntry.rawValue.buffer(), 0, ifEntry.rawValue.length() );
                        }

                        // or write the values parsed by the software
                        else
                        {
                            file.write( '=' );
                            Spaces.write( file, maxVarLength - entry.name.length() + 1 );

                            boolean  isFirst=      true;

                            //-------- write as single-line ----------
                            if ( 0 == ( entry.FormatHints & Variable.FORMAT_HINT_MULTILINE  ) )
                            {
                                boolean delimSpaces=  (0 == ( entry.FormatHints & Variable.FORMAT_HINT_NO_DELIM_SPACES ) );
                                for( AString value : entry.values )
                                {
                                    // write delim and backslash of previous line, newline and then spaces of actual line
                                    if ( !isFirst )
                                    {
                                        com.aworx.lib.ALIB_DBG.ASSERT_ERROR( entry.delim != 0,
                                                           "No delimiter given for multi-value variable \""
                                                            + entry.name + "\"." );

                                        if( delimSpaces && formatSpaceBeforeDelim)
                                            file.write( ' ' );

                                        file.write( entry.delim );

                                        if( delimSpaces && formatSpaceAfterDelim)
                                            file.write( ' ' );
                                    }

                                    // externalize value
                                    externalizedValue._();
                                    stringConverter.externalizeValue( value, externalizedValue, entry.delim );
                                    file.write( externalizedValue.buffer(), 0, externalizedValue.length() );
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
                                boolean allAttrHavePrecedingBlanks= true;
                                if (entry.FormatAttrAlignment != null )
                                {
                                    for( AString value : entry.values )
                                    {
                                        int attributeAssignPos= getAssignmentPos( value, entry.FormatAttrAlignment );
                                        if ( attributeAssignPos > 0 )
                                        {
                                            if ( maxAttributeAssignPos < attributeAssignPos )
                                                maxAttributeAssignPos= attributeAssignPos;
                                            allAttrHavePrecedingBlanks&= value.charAt( attributeAssignPos - 1 ) == ' ';
                                        }
                                    }
                                    if ( !allAttrHavePrecedingBlanks )
                                        maxAttributeAssignPos += 1;
                                }

                                // loop over values of entry
                                for( AString value : entry.values )
                                {

                                    // write delim and backslash of previous line, newline and then spaces of actual line
                                    if ( !isFirst )
                                    {
                                        com.aworx.lib.ALIB_DBG.ASSERT_ERROR( entry.delim != 0,
                                                           "No delimiter given for multi-value variable \""
                                                           + entry.name + "\"." );

                                        file.write( entry.delim );

                                        if ( backSlashPos < lastLineLen + 1 )
                                             backSlashPos=  lastLineLen + 4;
                                        Spaces.write( file, backSlashPos - lastLineLen );

                                        file.write( '\\' );
                                        file.newLine();

                                        Spaces.write( file, maxVarLength + 2 ); // 2 for "= "
                                    }

                                    // externalize value
                                    externalizedValue._();
                                    stringConverter.externalizeValue( value, externalizedValue, entry.delim );

                                    // if first character is a INI comment char, then escape it
                                    char firstChar= externalizedValue.charAt(0);
                                    if( !isFirst && (firstChar == '#' || firstChar == ';' ) )
                                        externalizedValue.insertAt("\\", 0 );

                                    // if assignment, insert spaces to align assignments
                                    if (entry.FormatAttrAlignment != null )
                                    {
                                        int attributeAssignPos= getAssignmentPos( externalizedValue, entry.FormatAttrAlignment );
                                        if ( attributeAssignPos > 0 && attributeAssignPos < maxAttributeAssignPos )
                                            externalizedValue.insertChars( ' ',
                                                                           maxAttributeAssignPos-attributeAssignPos,
                                                                           attributeAssignPos + (formatIncludeDelimInAttrAlignment ?
                                                                                                  0 : entry.FormatAttrAlignment.length() )
                                                                          );
                                    }


                                    file.write( externalizedValue.buffer(), 0, externalizedValue.length() );

                                    lastLineLen=  maxVarLength + 2  + externalizedValue.length();
                                    isFirst= false;
                                }
                            }
                        }
                        file.newLine();

                        // add an empty line if we have comments
                        if( (previousVarHasComments= entry.comments.isNotEmpty() ) == true )
                            file.newLine();
                    }
                }

                file.close();
            }
            catch( @SuppressWarnings ("unused") Exception e )
            {
                return lastStatus= Status.ERROR_OPENING_FILE;
            }

            return lastStatus;
        }



    // #############################################################################################
    // Protected methods
    // #############################################################################################

        /** ****************************************************************************************
         * Overrides base classes method to create a section of our type.
         *
         * @param name    The name of the entry.
         * @return An object of type \ref Section IniFile.Section.
         ******************************************************************************************/
        @Override
        protected InMemoryPlugin.Section  createSection( CharSequence name )
        {
            return new IniFile.Section( name );
        }

        /** ****************************************************************************************
         * Helper method used when reading file.
         * @param subs    A sub-string.
         * @return true if provided substring starts with comment character.
         ******************************************************************************************/
        protected boolean startsWithCommentSymbol( Substring subs )
        {
            int i= commentChars.indexOfOrLength( subs.charAtStart() );
            return       i <  2
                    || ( i == 2 && subs.length() > 1 && subs.charAt(1) == '/'  );
        }

        /** ****************************************************************************************
         * Writes a list of comments to the file. Comment lines are started with '#'.
         * @param os       The output stream to write to.
         * @param comments The comment lines for the section.
         * @param tknzr    A temporary tokenizer needed internally.
         ******************************************************************************************/
        protected void writeComments( BufferedWriter os, AString comments, Tokenizer tknzr ) throws IOException
        {
            // is empty when trimmed? (we are lenting tokeinizers field 'actual' to test)
            if ( tknzr.actual.set( comments ).isEmpty() )
                return;

            // tokenize by NEWLINE character
            tknzr.set( comments, '\n' );
            char[] oldWhitespaces= tknzr.whitespaces;
            tknzr.whitespaces= " \r\t".toCharArray(); // \n is not a whitespace

            while( tknzr.next(Whitespaces.KEEP).isNotNull() )
            {
                if ( !startsWithCommentSymbol( tknzr.actual ) )
                    os.write( defaultCommentPrefix );
                os.write( tknzr.actual.buf, tknzr.actual.start, tknzr.actual.length() );
                os.newLine();
            }

            tknzr.whitespaces= oldWhitespaces;
        }

} // class




