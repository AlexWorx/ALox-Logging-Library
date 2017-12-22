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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_COMPATIBILITY_STD_IOSTREAM)
    #error "Header already included"
#endif

#ifndef HPP_ALIB_COMPATIBILITY_STD_IOSTREAM
//! @cond NO_DOX
#define HPP_ALIB_COMPATIBILITY_STD_IOSTREAM 1
//! @endcond

#if ALIB_MODULE_STRINGS

// #################################################################################################
// includes
// #################################################################################################

#if !defined (_GLIBCXX_IOSTREAM )   && !defined(_IOSTREAM_)
    #include <iostream>
#endif

// #################################################################################################
// String / AString IO
// #################################################################################################

namespace aworx { namespace lib { namespace strings
{
    namespace thirdparty { namespace std {

    /** ****************************************************************************************
     * Parameter class used for \e application to objects of type
     * \ref aworx::lib::strings::AString "AString" with specialization of template struct
     * \ref aworx::lib::strings::thirdparty::std::T_Apply<thirdparty::std::ReadLineFromIStream> "T_Apply<ReadLineFromIStream>".<br>
     * Reads a line of text from a \b std::istream and appends it to the target \b %AString.<br>
     * While, of-course, this class can be created 'inline' (similar objects of parameter classes
     * found in \ref aworx::lib::strings::Format "Format"), if a series of lines are to be read
     * from a \b std::istream, a local object of this type might be created outside the loop
     * and used inside.
     * In this case, the 'output parameter' #IsEOF, can be used e.g. as a loop criteria.
     * \see
     * - \alib{strings::thirdparty::std,operator>>(std::istream&, AString&)}  and
     *   \alib{strings::thirdparty::std,operator<<(std::ostream&, const String& as)}
     * - For a sample, refer to source code of \b %ALib class \b %IniFile, method
     *   \ref aworx::lib::config::IniFile::ReadFile "IniFile::ReadFile".
     ******************************************************************************************/
    class ReadLineFromIStream
    {
        public:

        /** The input stream to read from.*/
        ::std::istream&        IStream;

        /** If \c CurrentData::KEEP, the target \c %AString is not cleared before the read operation. */
        lang::CurrentData      TargetData;

        /** The amount of characters that the buffer is increased while reading parts of the line.*/
        integer                BufferSize;

        /** The maximum length of a single line to be read. Longer lines get truncated. */
        integer                MaxLineWidth;

        /**
         * Indicates if the end of the input stream was detected with the last read operation.
         * If so, a next read operation will not change the string (or clear it, if #TargetData is
         * \c false
         */
        bool                    IsEOF           = false;

        /** ****************************************************************************************
         * Constructor.
         *
         * @param istream       The input stream to read from.
         * @param targetData    If \c CurrentData::Keep, the target \c %AString is not cleared
         *                      before the read operation is performed.
         *                      Defaults to \c CurrentData::Clear.
         * @param bufferSize    The amount of characters that the buffer is increased while reading
         *                      parts of the line. Defaults to 256 characters.
         * @param maxLineWidth  The maximum length of a single line to be read. Longer lines
         *                      get truncated. Defaults to 4096 characters.
         ******************************************************************************************/
        ReadLineFromIStream( ::std::istream&   istream,
                             lang::CurrentData targetData   = lang::CurrentData::Clear,
                             integer           bufferSize   = 256,
                             integer           maxLineWidth = 4096                        )
        : IStream     (istream),
          TargetData  (targetData),
          BufferSize  (bufferSize),
          MaxLineWidth(maxLineWidth)
        {}
    };

    // We are faking all template specializations of namespace strings for doxygen into namespace
    // strings::apply to keep the documentation of namespace string clean!
    #if !defined(DOX_PARSER)
      }} //namespace aworx::lib::strings [::thirdparty::std]
    #endif


    /** ********************************************************************************************
     * Copies the contents of the given %String to into the \c std::ostream given as reference.
     * @param  stream The ostream object to write the given  String into.
     * @param  string The String to write into the given ostream.
     * @returns The ostream to allow concatenated operations.
     **********************************************************************************************/
    inline std::ostream& operator<<( std::ostream& stream, const String& string )
    {
        if ( string.IsNotEmpty() )
            stream.write( string.Buffer(), string.Length() );
        return stream;
    }

    /** ********************************************************************************************
     * Copies the contents of the given %String to into the \c std::ostream given as pointer.
     * @param  stream The ostream object to write the given  String into.
     * @param  string The String to write into the given ostream.
     * @returns The ostream to allow concatenated operations.
     **********************************************************************************************/
    inline std::ostream* operator<<( std::ostream* stream, const String& string )
    {
        stream->write( string.Buffer(), string.Length() );
        return stream;
    }


    /** ********************************************************************************************
     * Clears the given %AString and extracts data from the std::istream into it. The extractions
     * ends with either the end of the std::istream or when reading a newline character.
     * @param  stream The istream object to extract data from.
     * @param  string The AString to receive data.
     * @returns The ostream to allow concatenated operations.
     **********************************************************************************************/
    inline std::istream& operator>>( std::istream& stream, AString& string )
    {
        string << thirdparty::std::ReadLineFromIStream( stream, lang::CurrentData::Clear );
        return stream;
    }

    /** ********************************************************************************************
     * Clears the given %AString and extracts data from the std::istream into it. The extractions
     * ends with either the end of the std::istream or when reading a newline character.
     * @param  stream The istream object to extract data from.
     * @param  string The AString to receive data.
     * @returns The ostream to allow concatenated operations.
     **********************************************************************************************/
    inline std::istream* operator>>( std::istream* stream, AString& string )
    {
        ALIB_ASSERT_WARNING ( stream != nullptr, "Given std::IStream is nullptr" );

        if (stream != nullptr)
            string << thirdparty::std::ReadLineFromIStream( *stream, lang::CurrentData::Clear );
        return stream;
    }


    /** Specialization of template struct \ref T_Apply for type \c thirdparty::std::ReadLineFromIStream.   */
    template<> struct T_Apply<thirdparty::std::ReadLineFromIStream> : public std::true_type
    {
        /** ****************************************************************************************
         * Reads a line from a text file and appends the contents to \p target.
         * If the end of the input stream was reached, field
         * \ref aworx::lib::strings::thirdparty::std::ReadLineFromIStream::IsEOF "IsEOF"
         * of parameter \p reader will be set to \c true what indicates that a next read operation
         * would fail if it was performed.
         *
         * \note
         *   For setting field <em>IsEOF</em> the object will be casted to a non-constant reference.
         *   See \ref aworx::lib::strings::T_Apply "T_Apply" for an explanation why it is OK to
         *   do so.
         *
         * @param  target     The AString object to read into.
         * @param  reader     The object holding the \b std::istream and some parameters.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static  ALIB_API   integer Apply( AString& target, const thirdparty::std::ReadLineFromIStream& reader);
    };

    // We are faking all template specializations of namespace strings for doxygen into namespace
    // aworx::lib::strings::thirdparty::std to keep the documentation of namespace string clean!

    #if !defined(DOX_PARSER)
    }} // namespace aworx[::lib::strings]
    #endif

    /** ********************************************************************************************
     * Copies the contents of the given \alib{strings,T_Apply,applicable type}
     * the \c std::ostream given as reference.
     *
     * \note Unlike this documentation states, this operator is defined in namespace #aworx.
     *
     * @param  stream     The \c std::ostream object to write the given  String into.
     * @param  applicable The object whose contents is to be written into the given \p stream.
     * @returns The ostream to allow concatenated operations.
     **********************************************************************************************/
    template<typename TApplicable,
             typename  TEnableIf= typename  std::enable_if<aworx::lib::strings::T_Apply<TApplicable>::value>::type >

    std::ostream& operator<<( std::ostream& stream, const TApplicable& applicable )
    {
        String256 buf;
        ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( buf, ReplaceExternalBuffer );

        if ( buf._(applicable).IsNotEmpty() )
            stream.write( buf.Buffer(), buf.Length() );
        return stream;
    }

    /** ********************************************************************************************
     * Copies the contents of the given \alib{strings,T_Apply,applicable type}
     * the \c std::ostream given as pointer.
     *
     * \note Unlike this documentation states, this operator is defined in namespace #aworx.
     *
     * @param  stream     The \c std::ostream object to write the given  String into.
     * @param  applicable The object whose contents is to be written into the given \p stream.
     * @returns The ostream to allow concatenated operations.
     **********************************************************************************************/
    template<typename TApplicable,
             typename  TEnableIf= typename  std::enable_if<aworx::lib::strings::T_Apply<TApplicable>::value>::type >

    std::ostream* operator<<( std::ostream* stream, const TApplicable& applicable )
    {
        if (stream != nullptr)
            aworx::operator<<( * stream, applicable );
        return stream;
    }



// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::apply to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
}}}} // for doxygen this is now aworx[::lib::strings::thirdparty::std]
#endif

} // namespace [aworx]

#endif // ALIB_MODULE_STRINGS


#endif // HPP_ALIB_COMPATIBILITY_STD_IOSTREAM
