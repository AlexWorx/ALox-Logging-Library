// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import com.aworx.lib.Util;
import com.aworx.lib.enums.Case;
import com.aworx.lib.enums.Inclusion;
import com.aworx.lib.enums.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.Tokenizer;

/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugIn, which reads and writes
 * a simple configuration file consisting of key/value pairs.
 *
 * This class is provided for the case that no other configuration mechanism is available.
 * For example, software that uses QT should not use this class but rather implement a
 * #ConfigurationPlugIn which uses a QSettings object to read and store that data to.
 *
 * This class offers all internal fields for public access. However, in standard cases, only
 * the interface methods of this class should be used.
 *
 * Some remarks on the functionality and supported format:
 * - Comment lines at the beginning of the file are associated with the file and are written
 *   back. Such comment block is stopped with a single blank line.
 * - Comment lines before sections and variables are associated with the respective objects
 *   and are written back.
 * - Sections names are enclosed by brackets ('[' and ']).
 * - Section names can be repeated. In this case the corresponding section is continued.
 *   When the file is written, the section are merged. Otherwise the order of sections and
 *   the variables within the section is kept intact.
 * - Variable names and their values are separated by an equal sign ('=').
 * - Whitespace characters (' ', '\\t' ) are removed at the start and end of each line and before
 *   and after the equal sign ('=').
 * - Lines that start (apart from whitespace) with either a double
 *   slash "//", a sharp sign '#' or a semicolon ';' are comment lines.
 * - Comments can not reside in the same line together with section names or variables.
 * - Variables definitions are being continued (values are concatenated) if the line ends
 *   with a backslash ('\'). Whitespaces in continued lines are ignored but can be 'escaped'.
 *   Comment lines in-between continued lines are not recognized as such.
 * - Sequences of blank lines are reduced to one blank line, when writing the file.
 * - Commented variables receive a blank line before the comment.
 * - Commented Sections receive two blank lines before the comment. One if they are not commented.
 **************************************************************************************************/
public class IniFile extends ConfigurationPlugIn
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
         * A configuration section
         ******************************************************************************************/
        public class Variable
        {
            public AString      name        = new AString();  ///< The name of the section
            public AString      comments    = new AString();  ///< The comments of the section
            public AString      value       = new AString();  ///< The list of variables of the section
            public char         delim       = '\0';           ///< The delimiter if splitting to multiple lines is wanted
        };

        /** ****************************************************************************************
         * A configuration section
         ******************************************************************************************/
        public class Section
        {
            public AString             name       = new AString();             ///< The name of the section
            public AString             comments   = new AString();             ///< The comments of the section
            public ArrayList<Variable> variables  = new ArrayList<Variable>(); ///< The list of variables of the section

            /** Constructs a Section
             * @param name    The name of the section.
             *                (AString compatible type expected.)
            */
            public              Section( CharSequence name )         { this.name._( name ); }

            /** Searches a variable with the given name. The search is performed case insensitive
             * @param name    The name of the variable to be searched.
             *                (AString compatible type expected.)
             * @return The variable if found, else null. */
            public Variable     get    ( CharSequence name )
            {
                for ( Variable var : variables )
                    if ( var.name.equals( name, Case.IGNORE ) )
                        return var;
                return null;
            }

            /** Inserts a variable into the section. If the variable exists, the value will be
             * written. If the comments also exist, they will be preserved.
             * @param name      The name of the variable to be inserted or written.
             *                  (AString compatible type expected.)
             * @param value     The value of the variable to be inserted or written.
             * @param comments  Comments that describe the variable (is written to INI file.
             * @return The variable that was created or written. */
            public Variable     insert ( CharSequence name, CharSequence value, AString comments )
            {
                // search
                Variable v= get( name );

                // not found?
                if( v == null )
                {
                    variables.add( v= new Variable() );
                    v.name._( name );
                }

                v.value.clear()._( value );

                // do not overwrite comments
                if ( v.comments.isEmpty() )
                    v.comments._( comments );

                return v;
            }


            /** Inserts a variable into the section. If the variable exists, the value will be
             * written. If the comments also exist, they will be preserved.
             * @param name      The name of the variable to be inserted or written.
             *                  (AString compatible type expected.)
             * @param value     The value of the variable to be inserted or written.
             * @return The variable that was created or written. */
            public Variable     insert ( CharSequence name, CharSequence value  )
            {
                return insert( name, value, null );
            }
        };

    // #############################################################################################
    // Public fields
    // #############################################################################################

        /** If this is set to true, any variable change will lead to writing the file immedeately
            by invoking #writeFile */
        public boolean                          autoSave                     = true;

        /** The standard file extension used for ALib configuration files. Defaults to "ini" */
        public static String                    DefaultFileExtension         = ".ini";

        /** The file name. This might include a path or not. Should be set properly before
            the file is read. */
        public AString                          fileName                     = new AString();

        /** The file header which will be written out as a comment lines with "# " prefixes */
        public AString                          fileComments                 = new AString();

        /** The list of sections. */
        public ArrayList<Section>               sections                     = new ArrayList<Section>();

        /** The status. */
        public  Status                          lastStatus                   = Status.OK;

        /** Is cleared and filled with faulty line numbers when reading the file. (E.g. when a
            line is no section and no comment but still has no equal sign ('=').  */
        public ArrayList<Integer>               linesWithReadErrors          = new ArrayList<Integer>();

        /** Pairs of conversion strings. The first value, is what appears in the file (e.g. >\\<)
            and the second string defines what the replacement character would be (e.g. >\<).

            The vector defaults to have replacements for
            - "\n" A new line character
            - "\r" A carriage return character
            - "\t" A tabulator character
            - "\\" A backslash
            - "\/" To allow the forward slash to be at the start of a line
            - "\#" To allow the "sharp" sign to be at the start of a line
            - "\;" To allow the ";" to be at the start of a line
          */

        public ArrayList<String>                escapeSequences;


        /**
        The prefix that is used for comment lines of sections or variables that have been
         * added 'programmatically', in other words, that have not been read from the file.
         * Comments that were read from the file preserve their prefix. Also, if comments including
         * one of the valid prefixes are added to a variable or section 'programmatically', such
         * prefix is preserved. */
        public String                           defaultCommentPrefix                        =  "# ";

    // #############################################################################################
    // Protected fields
    // #############################################################################################
        /** Characters that start a comment */
        protected   AString commentChars                                    =  new AString( "#;/" );

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
         * If the given file name \p filePathAndName starts with '*', no file is read and field
         * #autoSave is set to \c false.
         *
         * @param filePathAndName  The name (and path) of the file to read and write.
         *                         Provide "*" to suppress reading a file.
         *                         Defaults to \c null.
         ******************************************************************************************/
        public IniFile( String filePathAndName )
        {
            escapeSequences=  new ArrayList<String>();
            escapeSequences.add( "\\\\"); escapeSequences.add( "\\" );
            escapeSequences.add( "\\n" ); escapeSequences.add( "\n" );
            escapeSequences.add( "\\r" ); escapeSequences.add( "\r" );
            escapeSequences.add( "\\t" ); escapeSequences.add( "\t" );
            escapeSequences.add( "\\#" ); escapeSequences.add( "#"  );
            escapeSequences.add( "\\;" ); escapeSequences.add( ";"  );

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
                AString             mainClassName=  new AString( stack[stack.length - 1].getClassName () );
                int dotPos= mainClassName.lastIndexOfAny( ".".toCharArray(), Inclusion.INCLUDE );
                if (dotPos > 0)
                    mainClassName.delete_NC( 0, dotPos + 1 );
                fileName._NC( path )._( File.separatorChar )._NC( mainClassName )._NC( DefaultFileExtension );
            }

            readFile();
        }


    // #############################################################################################
    // ConfigurationPlugIn interface implementation
    // #############################################################################################
        /** ****************************************************************************************
         * Retrieves the string value of a configuration setting.
         * @param category  The category of the  variable.
         *                  (AString compatible type expected.)
         * @param name      The name of the configuration variable to be retrieved.
         *                  (AString compatible type expected.)
         * @param target    A reference to an empty AString to take the result.
         * @return true if variable was found within this configuration source, false if not.
         ******************************************************************************************/
        @Override
        public boolean  get( CharSequence category, CharSequence name, AString target )
        {
            target.clear();
            Section section= searchSection( category );
            if ( section == null )
                return false;

            Variable var=  section.get( name );
            if ( var == null )
                return false;

            target._( var.value );
            return true;
        }

        /** ****************************************************************************************
         * Writes a variable of type string to the configuration.
         * @param category  The category of the  variable.
         *                  (AString compatible type expected.)
         * @param name      The name of the configuration variable to be retrieved.
         *                  (AString compatible type expected.)
         * @param value     The value to write.
         * @param comments  The variable comments. Will be written above the variable.
         *                  Defaults to null.
         * @param delim     This plug-in uses this character to identify variable values that
         *                  are split into different lines within the INI file.
         *                  Lines are continued by adding a backslash at the end.
         *                  Defaults to ','.
         *
         * @return true if the variable was written, false if not.
         ******************************************************************************************/
        @Override
        public boolean  save( CharSequence  category,  CharSequence  name,
                              CharSequence  value,     CharSequence  comments,
                              char   delim                                       )
        {
            // find or create section
            Section     section= searchOrCreateSection( category, null );
            Variable    var=     section.get( name );
            boolean     changed=    false;
            if ( var == null )
            {
                var= section.insert( name, value );
                var.delim= delim;
                changed=   true;
            }
            else
            {
                if ( !var.value.equals( value ) )
                {
                    var.value.clear()._( value );
                    changed= true;
                }
            }

            if ( var.comments.isEmpty() && comments != null && comments.length() != 0  )
            {
                var.comments._( comments );
                changed= true;
            }

            // save file
            if ( changed && autoSave )
                writeFile();

            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref save(CharSequence,CharSequence,CharSequence,CharSequence,char) "save"
         * providing default parameters.
         * @param category  The category of the  variable.
         *                  (AString compatible type expected.)
         * @param name      The name of the configuration variable to be retrieved.
         *                  (AString compatible type expected.)
         * @param value     The value to write.
         * @param comments  The variable comments. Will be written above the variable.
         *                  Defaults to null.
         *
         * @return true if the variable was written, false if not.
         ******************************************************************************************/
        public boolean  save( CharSequence  category,  CharSequence  name,
                              CharSequence  value,     CharSequence  comments   )
        {
            return save( category, name, value, comments, ',');
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref save(CharSequence,CharSequence,CharSequence,CharSequence,char) "save"
         * providing default parameters.
         * @param category  The category of the  variable.
         *                  (AString compatible type expected.)
         * @param name      The name of the configuration variable to be retrieved.
         *                  (AString compatible type expected.)
         * @param value     The value to write.
         *
         * @return true if the variable was written, false if not.
         ******************************************************************************************/
        public boolean  save( CharSequence  category,  CharSequence  name,
                              CharSequence  value )
        {
            return save( category, name, value, null, ',');
        }


    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         * Clears all configuration data.
         ******************************************************************************************/
        public void            clear()
        {
            fileComments.clear();
            sections.clear();
            linesWithReadErrors.clear();
            lastStatus= Status.OK;

            // insert default section without a name as first entry
            sections.add( new Section("") );
        }


        /** ****************************************************************************************
         * Searches the \ref com::aworx::lib::config::IniFile::Section "Section" with the given name.
         *
         * @param name      The name of the section to be retrieved.
         * @return Returns the section if it was found, \c null otherwise.
         ******************************************************************************************/
        public Section  searchSection( CharSequence name )
        {
            for ( Section s : sections )
                if ( s.name.equals( name, Case.IGNORE ) )
                    return s;
            return null;
        }

        /** ****************************************************************************************
         * Searches the \ref com::aworx::lib::config::IniFile::Section "Section" with the given name.
         * If the section was not found, it is created.
         * If the section is found and has no comments, then the provided comments are appended.
         * @param name      The name of the section to be retrieved.
         * @param comments  The comment lines for the section, in the case the section is not
         *                  found. If this is null, no section is created.
         * @return Returns the section if it was found or created. null otherwise.
         ******************************************************************************************/
        public Section  searchOrCreateSection( CharSequence name, AString comments )
        {
            // search
            Section s= searchSection( name );
            if ( s == null )
                sections.add( s= new Section( name ) );

            if ( s.comments.isEmpty() )
                s.comments._( comments );

            return s;
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
        public IniFile.Status  readFile()
        {
            clear();
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
                Section     actSection= sections.get( 0 );
                Substring   line=       new Substring();
                Tokenizer   tn=         new Tokenizer();

                int         lineNo= 0;
                boolean        fileHeaderRead= false;

                linesWithReadErrors.clear();

                while ( (lineS= file.readLine()) != null )
                {
                    lineNo= 0;
                    //  place in AString
                    line.set( lineS ).trim();

                    // empty line?
                    if ( line.isEmpty() )
                    {
                        // already collecting a comment?
                        if ( comments.isNotEmpty() )
                        {
                            // first empty line in file found?
                            if ( !fileHeaderRead )
                            {
                                //store comments belonging to file
                                fileHeaderRead= true;
                                fileComments=   comments;
                                comments=       new AString();
                                continue;
                            }

                            comments.newLine();
                        }
                        continue;
                    }

                    // comments line: find comment character '#', ';' or //
                    if ( startsWithCommentSymbol( line ) )
                    {
                        //gather in comments string
                        if (comments.isNotEmpty())
                            comments.newLine();
                        line.copyTo( comments, true );
                        continue;
                    }

                    // section line
                    if ( line.consume( '[' ) )
                    {
                        fileHeaderRead= true;

                        // we do not care if there is no closing bracket. But if there is one, we remove it.
                        if( !line.consumeFromEnd( ']' ) )
                            linesWithReadErrors.add( lineNo );


                        // search the section in our section list (if section existed already, new comments
                        // are dropped)
                        actSection= searchOrCreateSection( line, comments );
                        comments.clear();

                        continue;
                    }

                    // variable line? If not, we just drop the line!
                    tn.set( line, '=' );
                    tn.next();
                    if ( !tn.hasNext() )
                    {
                        linesWithReadErrors.add( lineNo );
                        continue;
                    }

                    tn.actual.copyTo( name );
                    if ( tn.getRest().isEmpty() )
                    {
                        linesWithReadErrors.add( lineNo );
                        continue;
                    }

                    value.clear();
                    Substring valueRead= tn.actual;

                    // read continues as long as lines end with '\' (must not be '\\')
                    char delim= '\0';
                    while (     valueRead.charAtEnd()  == '\\'
                            &&  valueRead.charAtEnd(1) != '\\' )
                    {
                        // search end before '\'. The first of all broken lines determines the delimiter
                        valueRead.end--;
                        valueRead.trimEnd();

                        if (delim == 0)
                        {
                            delim= valueRead.charAtEnd();
                            if (  delim == '\"' ||  Character.isLetterOrDigit( delim ) )
                                delim= '\0';
                        }

                        removeEscapeSequences ( valueRead, value );
                        if ( (lineS= file.readLine()) == null  )
                        {
                            // last line of the file ended with '\' !
                            valueRead.clear();
                            break;
                        }

                        valueRead.set( lineS ).trim();
                    }
                    removeEscapeSequences ( valueRead, value );

                    actSection.insert( name, value, comments ).delim= delim;
                    comments.clear();
                }

                file.close();
            }
            catch( Exception e )
            {
                return lastStatus= Status.ERROR_OPENING_FILE;
            }


            return lastStatus;
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


                Tokenizer tok=      new Tokenizer();
                AString   tempAS=   new AString();

                // write header
                if ( fileComments.isNotEmpty() )
                {
                    writeComments( file, fileComments, tok );
                    file.newLine();
                }

                // loop over all sections
                for ( Section section : sections )
                {
                    file.newLine();
                    writeComments( file, section.comments, tok );

                    if ( section.name.isNotEmpty() )
                    {
                        file.write('[');
                        file.write( section.name.buffer(), 0, section.name.length() );
                        file.write(']');
                        file.newLine();
                    }

                    int maxVarLength= 0;
                    for ( Variable variable : section.variables )
                        maxVarLength= Math.max( maxVarLength, variable.name.length() );

                    for ( Variable variable : section.variables )
                    {
                        if( variable.comments.isNotEmpty() )
                        {
                            file.newLine();
                            writeComments( file, variable.comments, tok );
                        }
                        file.write( variable.name.buffer(), 0, variable.name.length() );
                        file.write( '=' );
                        Util.writeSpaces( file, maxVarLength - variable.name.length() + 1 );

                        tok.set( variable.value, variable.delim );
                        int      backSlashPos= 0;
                        int      lastLineLen=  0;
                        while( tok.hasNext() )
                        {
                            // write backslash of previous line and spaces of actual line
                            if ( tok.actual.isNotNull() )
                            {
                                if ( backSlashPos < lastLineLen + 1 )
                                     backSlashPos=  lastLineLen + 8;

                                Util.writeSpaces( file, backSlashPos - lastLineLen );

                                file.write( '\\' );
                                file.newLine();

                                Util.writeSpaces( file, maxVarLength + 2 ); // 2 for "= "
                            }

                            // write value
                            tok.next( Whitespaces.KEEP );
                            lastLineLen=  maxVarLength + 2  + tok.actual.length();
                            lastLineLen+= addEscapeSequences( file, tok.actual, tempAS );

                            // write delim
                            if ( tok.hasNext() )
                            {
                                file.write( variable.delim );
                                lastLineLen++;
                            }
                        }
                        file.newLine();
                    }
                }

                file.close();
            }
            catch( Exception e )
            {
                return lastStatus= Status.ERROR_OPENING_FILE;
            }

            return lastStatus;
        }



        /** ****************************************************************************************
         * Helper method used when reading file.
         * @param subs    A sub-string.
         * @return true if provided substring starts with comment character.
         ******************************************************************************************/
        protected boolean startsWithCommentSymbol( Substring subs )
        {
            int i= commentChars.indexOf( subs.charAtStart() );
            return      ( i >= 0 && i < 2)
                    ||  ( i == 2 && subs.charAt(1) == '/'  );
        }

        /** ****************************************************************************************
         * Writes a list of comments to the file. Comment lines are started with '#'.
         * @param os       The output stream to write to.
         * @param comments The comment lines for the section.
         * @param tok      A temporary tokenizer needed internally.
         ******************************************************************************************/
        protected void writeComments( BufferedWriter os, AString comments, Tokenizer tok ) throws IOException
        {
            // is empty when trimmed?
            if ( tok.actual.set( comments ).isEmpty() )
                return;

            // tokenize by NEWLINE character
            tok.set( comments, '\n' );
            char[] oldWhitespaces= tok.whitespaces;
            tok.whitespaces= " \r\t".toCharArray(); // \n is not a whitespace

            while( tok.hasNext() )
            {
                if ( !startsWithCommentSymbol( tok.next() ) )
                    os.write( defaultCommentPrefix );
                os.write( tok.actual.buf, tok.actual.start, tok.actual.length() );
                os.newLine();
            }

            tok.whitespaces= oldWhitespaces;
        }

        /** ****************************************************************************************
         * Converts variable value data. Replaces certain characters by escape sequences.
         * @param os        The output stream to write to.
         * @param value     The value to write
         * @param temp      A temporary AString needed internally.
         * @return The difference of length written and given value length.
         ******************************************************************************************/
        protected int addEscapeSequences( BufferedWriter os, Substring value, AString temp ) throws IOException
        {
            int sizeDiff= 0;
            temp.clear();

            if(     Character.isWhitespace( value.charAtStart() )
                ||  Character.isWhitespace( value.charAtEnd()  ) )
            {
                temp._('\"')._( value )._('\"');
                sizeDiff= 2;
            }
            else
                temp._( value );


            for( int i= 0 ; i < escapeSequences.size();  )
            {
                String replacement= escapeSequences.get( i++ );
                String needle=      escapeSequences.get( i++ );
                sizeDiff+= temp.searchAndReplace( needle, replacement, 0 ) * (replacement.length() - needle.length() );
            }

            os.write( temp.buffer(), 0, temp.length() );
            return sizeDiff;
        }

        /** ****************************************************************************************
         * Converts variable value data provided in the token and appends it to the target
         * variable.
         * Respects (and removes) quotation marks.
         * Replaces certain characters by escape sequences.
         * @param value     The input string.
         * @param target    The AString that gets the converted result appended.
         ******************************************************************************************/
        protected void removeEscapeSequences( Substring value, AString target )
        {
            // remove quotation markes
            if( value.charAtStart() == '\"' &&  value.charAtEnd()  == '\"' )
            {
                value.start++;
                value.end--;
            }

            int regionStart= target.length();
            value.copyTo( target, true );

            for( int i= 0 ; i < escapeSequences.size();  )
            {
                String needle=      escapeSequences.get( i++ );
                String replacement= escapeSequences.get( i++ );
                target.searchAndReplace( needle, replacement, regionStart );
            }
        }
} // class




