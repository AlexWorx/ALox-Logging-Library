// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_CONFIG_INI_FILE)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_CONFIG_INI_FILE
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_CONFIG_INI_FILE 1
#endif


// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALIB_STRINGS_ASSUBSTRING)
    #include "alib/strings/substring.hpp"
#endif
#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif


#if !defined (_GLIBCXX_VECTOR ) && !defined(_VECTOR_)
    #include <vector>
#endif


// #################################################################################################
// forwards
// #################################################################################################
namespace aworx { namespace lib { namespace strings { class Substring; } } }


namespace aworx {
namespace           lib {
namespace                   config {

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
 *  - Comments can not stay in a the same line with section names or variables.
 *  - Variables definitions are being continued (values are concatenated) if the line ends
 *    with a backslash ('\'). Whitespaces in continued lines are ignored but can be 'escaped'.
 *    Comment lines in-between continued lines are not recognized as such.
 *  - Sequences of blank lines are reduced to one blank line, when writing the file.
 *  - Commented variables receive a blank line before the comment.
 *  - Commented Sections receive two blank lines before the comment. One if they are not commented.
 **************************************************************************************************/
 class IniFile : public ConfigurationPlugIn
{
    // #############################################################################################
    // Public enums
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Status codes
         ******************************************************************************************/
        enum class Status
        {
            /**  All went well */
            Ok,

            /**  File not found when reading. This is not necessarily an error.*/
            ErrorOpeningFile,

            /**  An error occurred writing the file .*/
            ErorWritingFile
        };


    // #############################################################################################
    // inner classes
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  A configuration section
         ******************************************************************************************/
        class Variable
        {
            public:
                String32  Name;          ///< The name of the section
                String32  Value;         ///< The list of variables of the section
                AString   Comments;      ///< The comments of the section
                char      Delim = '\0';  ///< The delimiter (for splitting output into to multiple lines)

                Variable()
                {
                    ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( Name,  ReplaceExternalBuffer );
                    ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( Value, ReplaceExternalBuffer );
                }
        };

        /** ****************************************************************************************
         *  A configuration section
         ******************************************************************************************/
        class Section
        {
            public:

                String32     Name;                  ///< The name of the section
                AString      Comments;              ///< The comments of the section

                std::vector<Variable*> Variables;   ///< The list of variables of the section

            /**
             * Constructs a Section
             *  @param name    The name of the section.
             */
            Section( const String& name )
            : Name( name )
            {
                ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( Name,  ReplaceExternalBuffer);
            }

            /**
             * Destructs a Section
             */
            ~Section()
            {
                for ( Variable* var : Variables )
                    delete var;
            }

            /**
             * Searches a variable with the given name. The search is performed case insensitive
             *  @param name The name of the variable to be searched.
             *  @return The variable if found, else nullptr.
             */
            Variable*     Get    ( const String& name );

            /**
             * Inserts a variable into the section. If the variable exists, the value will be
             *  written. If the comments also exist, they will be preserved.
             *  @param name      The name of the variable to be inserted or written.
             *  @param value     The value of the variable to be inserted or written.
             *  @param comments  Comments that describe the variable (is written to INI-file.
             *  @return The variable that was created or written.
             */
            Variable*     Insert ( const String& name, const String& value, const String& comments= "" );
        };

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /** If this is set to \c true, any variable change will lead to writing the file immedeately
            by invoking #WriteFile */
        bool                             AutoSave                                           = true;

        /** The standard file extension used for ALib configuration files. Defaults to ".alib.ini" */
        static String                    DefaultFileExtension;

        /** The file name. This might include a path or not. Should be set properly before
            the file is read. */
        AString                          FileName;

        /** The file header which will be written out as a comment lines with "# " prefixes */
        AString                          FileComments;

        /** The list of sections. */
        std::vector<Section*>            Sections;

        /** The status. */
        Status                           LastStatus;

        /** Is cleared and filled with faulty line numbers when reading the file. (E.g. when a
            line is no section and no comment but still has no equal sign ('=').  */
        std::vector<int>                 LinesWithReadErrors;

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

        std::vector<TString>             EscapeSequences;


        /** The prefix that is used for comment lines of sections or variables that have been
         *  added 'programmatically', in other words, that have not been read from the file.
         *  Comments that were read from the file preserve their prefix. Also, if comments including
         *  one of the valid prefixes are added to a variable or section 'programmatically', such
         *  prefix is preserved. */
        String                           DefaultCommentPrefix                               =  "# ";

    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Constructs an instance of this class and reads the file.
         *  If no file name is given, the file name is set to the process name with extension
         *  found in public static field #DefaultFileExtension and the file path will be set to
         *  \ref aworx::lib::system::Directory::SpecialFolder::HOME_CONFIG "Directory::SpecialFolder::HOME_CONFIG".
         *
         *  @param filePathAndName  The name (and path) of the file to read and write.
         *                          Defaults to nullptr.
         ******************************************************************************************/
        ALIB_API               IniFile( const String& filePathAndName= nullptr );

        /** ****************************************************************************************
         *  Virtual Destructor.
         ******************************************************************************************/
        virtual      ~IniFile()
        {
           for ( Section* section : Sections )
                delete section;
        }

    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         *  Clears all configuration data.
         ******************************************************************************************/
        ALIB_API
        void          Clear();

        /** ****************************************************************************************
         *  Searches the \ref aworx::lib::config::IniFile::Section "Section" with the given name.
         *
         *  @param name      The name of the section to be retrieved.
         *  @return Returns the section if it was found, nullptr otherwise.
         ******************************************************************************************/
        ALIB_API
        Section*      SearchSection( const String& name);

        /** ****************************************************************************************
         *  Searches the \ref aworx::lib::config::IniFile::Section "Section" with the given name.
         *  If the section was not found, it is created.
         *  If the section is found and has no comments, then the provided comments are appended.
         *  @param name      The name of the section to be retrieved.
         *  @param comments  The comment lines for the section, in the case the section is not
         *                   found. If this is null, no section is created.
         *  @return Returns the section if it was found or created. nullptr otherwise.
         ******************************************************************************************/
        ALIB_API
        Section*      SearchOrCreateSection( const String& name, const String& comments );

    // #############################################################################################
    // ConfigurationPlugIn interface implementation
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  Retrieves the string value of a configuration setting.
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param target    A reference to an empty AString to take the result.
         *  @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        ALIB_API
        virtual bool  Get( const String& category, const String& name, AString& target );

        /** ****************************************************************************************
         *  Returns the int value of a configuration setting.
         *  This method invokes the default implementation
         *  \ref aworx::lib::config::ConfigurationPlugIn::Get(const String&, const String&, int32_t&) "ConfigurationPlugIn::Get".
         *
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param target    A reference to an integer variable to take the result.
         *  @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        virtual bool  Get( const String& category, const String& name, int32_t& target )
        {
            return ConfigurationPlugIn::Get( category, name, target );
        }

        /** ****************************************************************************************
         *  Returns the floating point value of a configuration setting.
         *  This method invokes the default implementation
         *  \ref aworx::lib::config::ConfigurationPlugIn::Get(const String&, const String&, double&) "ConfigurationPlugIn::Get".
         *
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param target    A reference to an double variable to take the result.
         *  @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        virtual bool  Get( const String& category, const String& name, double& target )
        {
            return ConfigurationPlugIn::Get( category, name, target );
        }

        /** ****************************************************************************************
         *  Writes a variable of type string to the configuration.
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param value     The value to write.
         *  @param comments  The variable comments. Will be written above the variable.
         *                   Defaults to NullString.
         *  @param delim     This plug-in uses this character to identify variable values that
         *                   are split into different lines within the INI file.
         *                   Lines are continued by adding a backslash at the end.
         *                   Defaults to ','.
         *
         *  @return \c true if the variable was written, \c false if not.
         ******************************************************************************************/
        ALIB_API
        virtual bool  Save( const String& category,  const String& name,
                            const String& value,     const String& comments = NullString,
                            char          delim= ',' );

        /** ****************************************************************************************
         *  Writes a variable of type integer to the configuration.
         *  This method invokes the default implementation
         *  \ref aworx::lib::config::ConfigurationPlugIn::Save(const String&, const String&, int, const String& ) "ConfigurationPlugIn::Save".
         *
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param value     The value to write.
         *  @param comments  The variable comments. Will be written above the variable.
         *                   Defaults to NullString.
         *  @return \c true if the variable was written, \c false if not.
         ******************************************************************************************/
        virtual bool  Save( const String& category, const String& name,
                            int           value,    const String& comments = NullString )
        {
            return ConfigurationPlugIn::Save( category, name, value, comments );
        }

        /** ****************************************************************************************
         *  Writes a variable of type double to the configuration.
         *  This method invokes the default implementation
         *  \ref aworx::lib::config::ConfigurationPlugIn::Save(const String&, const String&, double, const String& ) "ConfigurationPlugIn::Save".
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param value     The value to write.
         *  @param comments  The variable comments. Will be written above the variable.
         *                   Defaults to NullString.
         *  @return \c true if the variable was written, \c false if not.
         ******************************************************************************************/
        virtual bool  Save( const String& category, const String& name,
                            double        value,    const String& comments = NullString )
        {
            return ConfigurationPlugIn::Save( category, name, value, comments );
        }


    // #############################################################################################
    // File IO
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Clears all configuration data and reads the file. It might happen that lines are
         *  ignored or otherwise marked as faulty. All numbers of such lines get collected in
         *  field LinesWithReadErrors.
         *  @return Returns the #Status of the operation.
         ******************************************************************************************/
        ALIB_API
        IniFile::Status  ReadFile();

        /** ****************************************************************************************
         *  Write all configuration data into the file.
         *  @return Returns the #Status of the operation.
         ******************************************************************************************/
        ALIB_API
        IniFile::Status  WriteFile();

    protected:

        /** ****************************************************************************************
         *  Writes a list of comments to the file. Comment lines are started with '#'.
         *  @param os       The output stream to write to.
         *  @param comments The comment lines for the section.
         ******************************************************************************************/
        ALIB_API
        void writeComments( std::ostream& os, const AString& comments );

        /** ****************************************************************************************
         *  Converts variable value data. Replaces certain characters by escape sequences.
         *  @param os        The output stream to write to.
         *  @param value     The value to write
         *  @return The difference of length written and given value length.
         ******************************************************************************************/
        ALIB_API
        int addEscapeSequences  ( std::ostream& os, const Substring& value );

        /** ****************************************************************************************
         *  Converts variable value data provided in the token and appends it to the target
         *  variable.
         *  Respects (and removes) quotation marks.
         *  Replaces certain characters by escape sequences.
         *  @param value     The input token.
         *  @param target    The AString that gets the converted result appended.
         ******************************************************************************************/
        ALIB_API
        void removeEscapeSequences( strings::Substring& value, AString& target );

};


}} // namespace lib::config

/** Type alias name in namespace #aworx. */
using     IniFile=       aworx::lib::config::IniFile;

}  // namespace aworx

#endif // HPP_ALIB_CONFIG_INI_FILE
