// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_STRINGS_UTIL_SIMPLETEXT)
    #error "Header already included"
#endif


// then, set include guard
#ifndef HPP_ALIB_STRINGS_UTIL_SIMPLETEXT
//! @cond NO_DOX
#define HPP_ALIB_STRINGS_UTIL_SIMPLETEXT 1
//! @endcond NO_DOX

// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALIB_STRINGS_FORMATTER_PYTHONSTYLE)
    #include "alib/strings/format/formatterpythonstyle.hpp"
#endif


namespace aworx { namespace lib { namespace strings { namespace util  {

/** ************************************************************************************************
 * The class provides static method #FormatParagraph to format a "paragraph"
 * that starts at a certain index of an  \b %AString buffer and reaches to its end.
 *
 * When an instance of the class is created, the (public) members of the class provide the text
 * buffer and the parameters which are needed for the static method. With methods
 * #AddParagraph, member #Formatter is used to append the given parameters and then format the
 * new paragraph. This way, a longer text might be built by repetitive calls.
 **************************************************************************************************/
class SimpleText
{
    // #############################################################################################
    // Fields
    // #############################################################################################
    public:
        /** The text buffer. */
        AString                         Text;

        /** The main formatter. */
        FormatterPythonStyle            Formatter;

        /** Used as parameter \p lineWidth of static method invocations. */
        integer                         LineWidth                                               = 0;

        /** Used as parameter \p justifier of static method invocations. */
        char                            Justifier                                            = '\0';


        /**
         * Used as parameter \p indent of static method invocations.
         * This field can either be manipulated by direct access or with overloaded methods
         * #AddIndent.
         */
        String64                        Indent;

        /**
         * Used as parameter \p indentFirstLine of static method invocations.
         * Defaults to \e nulled string, which means that the first line has the same indent as the
         * other lines.
         */
        String                          IndentFirstLine;

    protected:
        /** Internally reused list of boxes. */
        Boxes                           boxes;


    // #############################################################################################
    // Constructor/Destructor
    // #############################################################################################
    public:

            SimpleText()    : Text(2048)  {}

    // #############################################################################################
    // Interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Formats a paragraph by three optional things:
         * - Adding an indentation to each line with an optionally different indentation for
         *   the first line
         * - Wrapping of lines longer than lineWidth (word wrap)
         * - Justify the text, which here means "full justification", i.e. format the text to have
         *   left and right aligned paragraphs.
         *
         * The paragraph starts at \p startIdx and all of the rest of the string is treated
         * as one paragraph. New-line character sequences found within the paragraph are considered
         * manual line ends. Hence, no block formatting for lines ending with a new line character
         * is performed.
         *
         * The method is static and hence can be used with arbitrary buffers.
         * Non-static methods #AddParagraph invoke this methods after adding the given content
         * to the internal buffer.
         *
         * @param text             The text containing the paragraph to format.
         * @param startIdx         The start of the paragraph.
         * @param lineWidth        The width of the line. If \c 0 or negative, no line wrap is
         *                         performed.
         * @param justifier        If this is unequal to \c '\0' (the default),  denotes the fill
         *                         character used to justify the paragraph.
         * @param indent           The indent string.
         * @param indentFirstLine  The indent string of the first line. If this is \e nulled, than
         *                         \p indent is used.
         *******************************************************************************************/
        ALIB_API
        static
        void    FormatParagraph( AString& text, integer startIdx, integer lineWidth, char justifier,
                                 String indent, const String& indentFirstLine  );

        /** ****************************************************************************************
         * Appends the given objects \p args to the internal buffer #Text with the help of member
         * #Formatter. Then, static method #FormatParagraph is invoked, providing our public
         * members as parameters. Finally, a newline sequence is added to #Text, but only if the
         * buffer is not empty and if it does not already end with a newline sequence.
         *
         * @param args   The list of arguments to add.
         *******************************************************************************************/
        ALIB_API
        void    AddParagraph( const Boxes&  args );

        /** ****************************************************************************************
         * Variadic argument version of #AddParagraph.
         *
         * @param args   The variadic list of arguments to add.
         ******************************************************************************************/
        template <typename... BoxedObjects>
        void    AddParagraph( const BoxedObjects&... args )
        {
            boxes.clear();
            boxes.Add( args... );
            AddParagraph( boxes );
        }

        /** ****************************************************************************************
         * Add a given number of characters (default is spaces) to the indentation string #Indent.
         * If parameter \p qty is negative, -qty characters are removed from the end of #Indent.
         *
         * @param qty       The quantity of characters to add or remove
         * @param fillChar  The character (used only if \p qty is positive).
         ******************************************************************************************/
        void AddIndent( int qty, char fillChar = ' ' );

        /** ****************************************************************************************
         * Add the given string to member #Indent.
         *
         * @param increment   The string to add to the current indentation stored in #Indent.
         ******************************************************************************************/
        void    AddIndent( const String& increment );
};


}}} // namespace aworx[::lib::strings::util]


/** Type alias name in namespace #aworx. */
using     SimpleText=           aworx::lib::strings::util::SimpleText;

}  // namespace aworx

#endif // HPP_ALIB_STRINGS_UTIL_SIMPLETEXT
