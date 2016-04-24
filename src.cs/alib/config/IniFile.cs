// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.IO;
using System.Collections.Generic;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;

namespace cs.aworx.lib.config  {


    /** ************************************************************************************************
     *  Specialization of abstract interface class #ConfigurationPlugIn, which reads and writes
     *  a simple configuration file consisting of key/value pairs.
     *
     *  This class is provided for the case that no other configuration mechanism is available.
     *  For example, software that uses QT should not use this class but rather implement a
     *  #ConfigurationPlugIn which uses a QSettings object to read and store that data to.
     *
     *  This class offers all internal fields for public access. However, in standard cases, only
     *  the interface methods of this class should be used.
     *
     *  Some remarks on the functionality and supported format:
     *  - Comment lines at the beginning of the file are associated with the file and are written
     *    back. Such comment block is stopped with a single blank line.
     *  - Comment lines before sections and variables are associated with the respective objects
     *    and are written back.
     *  - Sections names are enclosed by brackets ('[' and ']).
     *  - Section names can be repeated. In this case the corresponding section is continued.
     *    When the file is written, the section are merged. Otherwise the order of sections and
     *    the variables within the section is kept intact.
     *  - Variable names and their values are separated by an equal sign ('=').
     *  - Whitespace characters (' ', '\\t' ) are removed at the start and end of each line and before
     *    and after the equal sign ('=').
     *  - Lines that start (apart from whitespace) with either a double
     *    slash "//", a sharp sign '#' or a semicolon ';' are comment lines.
     *  - Comments can not reside in the same line together with section names or variables.
     *  - Variables definitions are being continued (values are concatenated) if the line ends
     *    with a backslash ('\'). Whitespaces in continued lines are ignored but can be 'escaped'.
     *    Comment lines in-between continued lines are not recognized as such.
     *  - Sequences of blank lines are reduced to one blank line, when writing the file.
     *  - Commented variables receive a blank line before the comment.
     *  - Commented Sections receive two blank lines before the comment. One if they are not commented.
     **************************************************************************************************/
    public class IniFile : ConfigurationPlugIn
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
         *  A configuration section
         ******************************************************************************************/
        public class Variable
        {
            public AString      Name        = new AString();  ///< The name of the section
            public AString      Comments    = new AString();  ///< The comments of the section
            public AString      Value       = new AString();  ///< The list of variables of the section
            public char         Delim       = '\0';           ///< The delimiter if splitting to multiple lines is wanted
        };

        /** ****************************************************************************************
         *  A configuration section
         ******************************************************************************************/
        public class Section
        {
            public AString            Name       = new AString();         ///< The name of the section
            public AString            Comments   = new AString();         ///< The comments of the section
            public List<Variable>     Variables  = new List<Variable>();  ///< The list of variables of the section

            /** Constructs a Section
             *  @param name    The name of the section.
             *                 (AString compatible type expected.)
            */
            public              Section( Object name )         { this.Name._( name ); }

            /** Searches a variable with the given name. The search is performed case insensitive
             *  @param name    The name of the variable to be searched.
             *                 (AString compatible type expected.)
             *  @return The variable if found, else null. */
            public Variable     Get    ( Object name )
            {
                return Variables.Find( variable => variable.Name.Equals( name, Case.Ignore ) );
            }

            /** Inserts a variable into the section. If the variable exists, the value will be
             *  written. If the comments also exist, they will be preserved.
             *  @param name      The name of the variable to be inserted or written.
             *                   (AString compatible type expected.)
             *  @param value     The value of the variable to be inserted or written.
             *  @param comments  Comments that describe the variable (is written to INI-file.
             *  @return The variable that was created or written. */
            public Variable     Insert ( Object name, Object value, AString comments= null )
            {
                // search
                Variable v= Variables.Find( variable => variable.Name.Equals( name, Case.Ignore ) );

                // not found?
                if( v == null )
                {
                    Variables.Add( v= new Variable() );
                    v.Name._( name );
                }

                v.Value.Clear()._( value );

                // do not overwrite comments
                if ( v.Comments.IsEmpty() )
                    v.Comments._( comments );

                return v;
            }
        };

    // #############################################################################################
    // Public fields
    // #############################################################################################

        /** If this is set to true, any variable change will lead to writing the file immediately
            by invoking #WriteFile */
        public bool                             AutoSave                     = true;

        /** The file name. This might include a path or not. Should be set properly before
            the file is read. */
        public AString                          FileName                     = new AString();

        /** The standard file extension used for ALib configuration files. Defaults to ".ini" */
        public static String                    DefaultFileExtension         = ".ini";

        /** The file header which will be written out as a comment lines with "# " prefixes */
        public AString                          FileComments                 = new AString();

        /** The list of sections. */
        public List<Section>                    Sections                     = new List<Section>();

        /** The status. */
        public  Status                          LastStatus                   = Status.OK;

        /** Is cleared and filled with faulty line numbers when reading the file. (E.g. when a
            line is no section and no comment but still has no equal sign ('=').  */
        public List<int>                        LinesWithReadErrors          = new List<int>();

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

        public List<String>                     EscapeSequences;


        /** The prefix that is used for comment lines of sections or variables that have been
         *  added 'programmatically', in other words, that have not been read from the file.
         *  Comments that were read from the file preserve their prefix. Also, if comments including
         *  one of the valid prefixes are added to a variable or section 'programmatically', such
         *  prefix is preserved. */
        public String                           DefaultCommentPrefix                        =  "# ";

    // #############################################################################################
    // Protected fields
    // #############################################################################################
        /** Characters that start a comment */
        protected   AString commentChars                                    =  new AString( "#;/" );

    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
        /** ****************************************************************************************
         *  Constructs an instance of this class and reads the file.
         *  If no file name is given, the file name set to the process name with extension
         *  ".ini" while the file path is retrieved using
         *  <em>Environment.GetFolderPath( Environment.SpecialFolder.ApplicationData )</em>.
         *
         *  If the given file name \p filePathAndName starts with '*', no file is read and field
         *  #AutoSave is set to \c false.
         *
         *  @param filePathAndName  The name (and path) of the file to read and write.
         *                          Provide "*" to suppress reading a file.
         *                          Defaults to \c null.
         ******************************************************************************************/
        public IniFile( String filePathAndName=  null )
        {
            EscapeSequences=  new List<String>
                              {
                                     "\\\\",  "\\",
                                     "\\n",   "\n",
                                     "\\r",   "\r",
                                     "\\t",   "\t",
                                     "\\#",   "#",
                                     "\\;",   ";"
                               };


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
                String path= Environment.GetFolderPath( Environment.SpecialFolder.ApplicationData );
                if ( !Directory.Exists( path ) )
                    path=  Environment.GetFolderPath( Environment.SpecialFolder.UserProfile );

                FileName._( path )
                        ._( Path.DirectorySeparatorChar )
                        ._( Util.GetProcessName() )
                        ._( DefaultFileExtension  );
            }

            ReadFile();
        }


    // #############################################################################################
    // ConfigurationPlugIn interface implementation
    // #############################################################################################
        /** ****************************************************************************************
         *  Retrieves the string value of a configuration setting.
         *  @param category  The category of the  variable.
         *                   (AString compatible type expected.)
         *  @param name      The name of the configuration variable to be retrieved.
         *                   (AString compatible type expected.)
         *  @param target    A reference to an empty AString to take the result.
         *  @return true if variable was found within this configuration source, false if not.
         ******************************************************************************************/
        public override bool  Get( Object   category, Object name,
                                   AString  target                           )
        {
            target.Clear();
            Section section= SearchSectionX( category );
            if ( section == null )
                return false;

            Variable var=  section.Get( name );
            if ( var == null )
                return false;

            target._( var.Value );
            return true;
        }

        /** ****************************************************************************************
         *  Writes a value to the configuration.
         *  @param category  The category of the  variable.
         *                   (AString compatible type expected.)
         *  @param name      The name of the configuration variable to be retrieved.
         *                   (AString compatible type expected.)
         *  @param value     The value to write.
         *  @param comments  The variable comments. Will be written above the variable.
         *                   Defaults to null.
         *  @param delim     This plug-in uses this character to identify variable values that
         *                   are split into different lines within the INI file.
         *                   Lines are continued by adding a backslash at the end.
         *                   Defaults to ','.
         *
         *  @return true if the variable was written, false if not.
         ******************************************************************************************/
        public override bool  Save( Object  category,  Object  name,
                                    Object  value,     Object  comments= null,
                                    char    delim= ','                       )
        {
            // find or create section
            Section     section= SearchOrCreateSection( category, null );
            Variable    var=     section.Get( name );
            bool        changed=    false;

            if ( var == null )
            {
                var= section.Insert( name, value );
                var.Delim= delim;
                changed= true;
            }
            else
            {
                if ( !var.Value.Equals( value ) )
                {
                    var.Value.Clear()._( value );
                    changed= true;
                }
            }

            if ( var.Comments.IsEmpty() && comments != null )
            {
                var.Comments._( comments );
                changed= true;
            }

            // save file
            if ( changed && AutoSave )
                WriteFile();

            return true;
        }


    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         *  Clears all configuration data.
         ******************************************************************************************/
        public void            Clear()
        {
            FileComments.Clear();
            Sections.Clear();
            LinesWithReadErrors.Clear();
            LastStatus= Status.OK;

            // insert default section without a name as first entry
            Sections.Add( new Section("") );
        }


        /** ****************************************************************************************
         *  Searches the \ref cs::aworx::lib::config::IniFile::Section "Section" with the given name.
         *
         *  @param name      The name of the section to be retrieved.
         *  @return Returns the section if it was found, \c null otherwise.
         ******************************************************************************************/
        public Section  SearchSectionX( Object name )
        {
            return Sections.Find( x => x.Name.Equals( name, Case.Ignore ) );
        }

        /** ****************************************************************************************
         *  Searches the \ref cs::aworx::lib::config::IniFile::Section "Section" with the given name.
         *  If the section was not found, it is created.
         *  If the section is found and has no comments, then the provided comments are appended.
         *  @param name      The name of the section to be retrieved.
         *  @param comments  The comment lines for the section, in the case the section is not
         *                   found. If this is null, no section is created.
         *  @return Returns the section if it was found or created. \c null otherwise.
         ******************************************************************************************/
        public Section  SearchOrCreateSection( Object name, AString comments )
        {
            Section s= SearchSectionX( name );
            if ( s == null )
                Sections.Add( s= new Section( name ) );

            if ( s.Comments.IsEmpty() )
                s.Comments._( comments );

            return s;
        }

    // #############################################################################################
    // file IO
    // #############################################################################################
        /** ****************************************************************************************
         *  Clears all configuration data and reads the file. It might happen that lines are
         *  ignored or otherwise marked as faulty. All numbers of such lines get collected in
         *  field LinesWithReadErrors.
         *  @return Returns the #Status of the operation.
         ******************************************************************************************/
        public IniFile.Status  ReadFile()
        {
            Clear();
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
            Section     actSection= Sections[0];
            Substring   line=       new Substring();
            Tokenizer   tn=         new Tokenizer();

            int         lineNo= 0;
            bool        fileHeaderRead= false;

            LinesWithReadErrors.Clear();

            while ( (lineS= file.ReadLine()) != null )
            {
                lineNo= 0;
                //  place in AString
                line.Set( lineS ).Trim();

                // empty line?
                if ( line.IsEmpty() )
                {
                    // already collecting a comment?
                    if ( comments.IsNotEmpty() )
                    {
                        // first empty line in file found?
                        if ( !fileHeaderRead )
                        {
                            //store comments belonging to file
                            fileHeaderRead= true;
                            FileComments=   comments;
                            comments=       new AString();
                            continue;
                        }

                        comments.NewLine();
                    }
                    continue;
                }

                // comments line: find comment character '#', ';' or //
                if ( startsWithCommentSymbol( line ) )
                {
                    //gather in comments string
                    if (comments.IsNotEmpty() )
                        comments.NewLine();
                    line.CopyTo( comments, true );
                    continue;
                }

                // section line
                if ( line.Consume( '[' ) )
                {
                    fileHeaderRead= true;

                    // we do not care if there is no closing bracket. But if there is one, we remove it.
                    if( !line.ConsumeFromEnd(']') )
                        LinesWithReadErrors.Add( lineNo );

                    // search the section in our section list (if section existed already, new comments
                    // are dropped)
                    actSection= SearchOrCreateSection( line, comments);
                    comments.Clear();

                    continue;
                }

                // variable line? If not, we just drop the line!
                tn.Set( line, '=' );
                tn.Next();
                if ( !tn.HasNext() )
                {
                    LinesWithReadErrors.Add( lineNo );
                    continue;
                }

                tn.Actual.CopyTo( name );
                if ( tn.GetRest().IsEmpty() )
                {
                    LinesWithReadErrors.Add( lineNo );
                    continue;
                }

                value.Clear();
                Substring valueRead= tn.Actual;

                // read continues as long as lines end with '\' (must not be '\\')
                char delim= '\0';
                while (     valueRead.CharAtEnd()  == '\\'
                        &&  valueRead.CharAtEnd(1) != '\\' )
                {
                    // search end before '\'. The first of all broken lines determines the delimiter
                    valueRead.End--;
                    valueRead.TrimEnd();

                    if (delim == 0)
                    {
                        delim= valueRead.CharAtEnd();
                        if (  delim == '\"' ||  char.IsLetterOrDigit( delim ) )
                            delim= '\0';
                    }

                    removeEscapeSequences ( valueRead, value );
                    if ( (lineS= file.ReadLine()) == null  )
                    {
                        // last line of the file ended with '\' !
                        valueRead.Clear();
                        break;
                    }

                    valueRead.Set( lineS ).Trim();
                }
                removeEscapeSequences ( valueRead, value );

                actSection.Insert( name, value, comments ).Delim= delim;
                comments.Clear();

            }
            file.Close();

            return LastStatus;
        }

        /** ****************************************************************************************
         *  Write all configuration data into the file.
         *  @return Returns the #Status of the operation.
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

            Tokenizer tok=      new Tokenizer();
            AString   tempAS=   new AString();

            // write header
            if ( FileComments.IsNotEmpty() )
            {
                writeComments( file, FileComments, tok );
                file.WriteLine();
            }

            // loop over all sections
            foreach ( Section section in Sections )
            {
                file.WriteLine();
                writeComments( file, section.Comments, tok );

                if ( section.Name.IsNotEmpty() )
                {
                    file.Write('[');
                    file.Write( section.Name.Buffer(), 0, section.Name.Length() );
                    file.WriteLine(']');
                }

                int maxVarLength= 0;
                foreach ( Variable variable in section.Variables )
                    maxVarLength= Math.Max( maxVarLength, variable.Name.Length() );

                foreach ( Variable variable in section.Variables )
                {
                    if( variable.Comments.IsNotEmpty() )
                    {
                        file.WriteLine();
                        writeComments( file, variable.Comments, tok );
                    }
                    file.Write( variable.Name.Buffer(), 0, variable.Name.Length() );
                    file.Write( '=' );
                    Util.WriteSpaces( file, maxVarLength - variable.Name.Length() + 1 );

                    tok.Set( variable.Value, variable.Delim );
                    int      backSlashPos= 0;
                    int      lastLineLen=  0;
                    while( tok.HasNext() )
                    {
                        // write backslash of previous line and spaces of actual line
                        if (tok.Actual.IsNotNull() )
                        {
                            if ( backSlashPos < lastLineLen + 1  )
                                 backSlashPos=  lastLineLen + 8;

                            Util.WriteSpaces( file, backSlashPos - lastLineLen );

                            file.WriteLine( '\\' );

                            Util.WriteSpaces( file, maxVarLength + 2 ); // 2 for "= "
                        }

                        // write value
                        tok.Next( Whitespaces.Keep );
                        lastLineLen=  maxVarLength + 2  + tok.Actual.Length();
                        lastLineLen+= addEscapeSequences( file, tok.Actual, tempAS );

                        // write delim
                        if ( tok.HasNext() )
                        {
                            file.Write( variable.Delim );
                            lastLineLen++;
                        }
                    }
                    file.WriteLine();
                }
            }

            // close file
            file.Close();

            return LastStatus;
        }

        /** ****************************************************************************************
         *  Helper method used when reading file.
         *  @param subs    A sub-string.
         *  @return true if provided substring starts with comment character.
         ******************************************************************************************/
        protected bool startsWithCommentSymbol( Substring subs )
        {
            int i= commentChars.IndexOf( subs.CharAtStart() );
            return      ( i >= 0 && i < 2)
                    ||  ( i == 2 && subs.CharAt(1) == '/'  );
        }

        /** ****************************************************************************************
         *  Writes a list of comments to the file. Comment lines are started with '#'.
         *  @param os       The output stream to write to.
         *  @param comments The comment lines for the section.
         *  @param tok      A temporary tokenizer needed internally.
         ******************************************************************************************/
        protected void writeComments( TextWriter os, AString comments, Tokenizer tok )
        {
            // is empty when trimmed?
            if ( tok.Actual.Set( comments ).Trim().IsEmpty() )
                return;

            // tokenize by NEWLINE character
            tok.Set( comments, '\n' );
            char[] oldWhiteSpaces= tok.Whitespaces;
            tok.Whitespaces=  " \r\t".ToCharArray(); // \n is not a whitespace

            while( tok.HasNext() )
            {
                if ( !startsWithCommentSymbol( tok.Next() ) )
                    os.Write( DefaultCommentPrefix );
                os.WriteLine( tok.Actual.Buf, tok.Actual.Start, tok.Actual.Length() );
            }
            tok.Whitespaces= oldWhiteSpaces;
        }

        /** ****************************************************************************************
         *  Converts variable value data. Replaces certain characters by escape sequences.
         *  @param os        The output stream to write to.
         *  @param value     The value to write
         *  @param temp      A temporary AString needed internally.
         *  @return The difference of length written and given value length.
         ******************************************************************************************/
        protected int addEscapeSequences( TextWriter os, Substring value, AString temp )
        {
            int sizeDiff= 0;
            temp.Clear();

            if(     char.IsWhiteSpace( value.CharAtStart() )
                ||  char.IsWhiteSpace( value.CharAtEnd  () ) )
            {
                temp._('\"')._( value )._('\"');
                sizeDiff= 2;
            }
            else
                temp._( value );


            for( int i= 0 ; i < EscapeSequences.Count;  )
            {
                String replacement= EscapeSequences[i++];
                String needle=      EscapeSequences[i++];
                sizeDiff+= temp.SearchAndReplace( needle, replacement, 0 ) * (replacement.Length - needle.Length );
            }

            os.Write( temp.Buffer(), 0, temp.Length() );
            return sizeDiff;
        }

        /** ****************************************************************************************
         *  Converts variable value data provided in the token and appends it to the target
         *  variable.
         *  Respects (and removes) quotation marks.
         *  Replaces certain characters by escape sequences.
         *  @param value     The input string.
         *  @param target    The AString that gets the converted result appended.
         ******************************************************************************************/
        protected void removeEscapeSequences( Substring value, AString target )
        {
            // remove quotation markes
            if(     value.CharAtStart() == '\"'
                &&  value.CharAtEnd  () == '\"' )
            {
                value.Start++;
                value.End--;
            }

            int regionStart= target.Length();
            value.CopyTo( target, true );

            for( int i= 0 ; i < EscapeSequences.Count;  )
            {
                String needle=      EscapeSequences[i++];
                String replacement= EscapeSequences[i++];
                target.SearchAndReplace( needle, replacement, regionStart );
            }
        }
    } // class

}// namespace

