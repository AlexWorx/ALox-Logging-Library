// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// check for alib.hpp already there but not us
#if !defined (HPP_AWORX_LIB_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_AWORX_LIB_COMPATIBILITY_STD_IOSTREAM)
    #error "Header already included"
#endif

#ifndef HPP_AWORX_LIB_COMPATIBILITY_STD_IOSTREAM
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_AWORX_LIB_COMPATIBILITY_STD_IOSTREAM 1
#endif

// #################################################################################################
// includes
// #################################################################################################

#if !defined (_GLIBCXX_IOSTREAM )   && !defined(_IOSTREAM_)
    #include <iostream>
#endif

// #################################################################################################
// AS / AString IO
// #################################################################################################

namespace aworx {
namespace           lib {
namespace                   strings {


    /** ****************************************************************************************
     * Parameter class which is \e 'applicable' to objects of type
     * \ref aworx::lib::strings::ASAlloc "AString" with
     * \ref aworx::lib::strings::ApplyTo(AString&, const ReadLineFromIStream&) "corresponding specialization"
     *  of template function
     * \ref aworx::lib::strings::ApplyTo "ApplyTo".<p>
     *  Reads a line of text from a \b std::istream and appends it to the target AString.<br>
     *  While, of-course, this class can be created 'inline' like most
     *  <em>ApplyTo parameter classes</em>,  if a series of lines are to be read from a
     *  an \b std::istream, a local object of this type might be created before the read loop
     *  and used inside.
     *  In this case, the 'output parameter' #IsEOF, can be used e.g. as a loop criteria.
     *  \see
     *  - \ref operator>>(std::istream&, AString&) and
     *    \ref operator<<(std::ostream& os, const String& as) "operator<<(ostream& os, const String& as)"
     *  - For a sample, refer to source code of ALib class \b %IniFile, method
     *    \ref aworx::lib::config::IniFile::ReadFile "IniFile::ReadFile".
     ******************************************************************************************/
    class ReadLineFromIStream
    {
        public:

        /** The input stream to read from.*/
        std::istream&           istream;

        /** If \c CurrentData::KEEP, the target \c %AString is not cleared before the read operation. */
        enums::CurrentData      TargetData;

        /** The amount of characters that the buffer is increased while reading parts of the line.*/
        int                     BufferSize;

        /** The maximum length of a single line to be read. Longer lines get truncated. */
        int                     MaxLineWidth;

        /**
         * Indicates if the end of the input stream was detected with the last read operation.
         * If so, a next read operation will not change the string (or clear it, if #TargetData is
         * \c false
         */
        bool                    IsEOF           = false;

        /** ****************************************************************************************
         * Constructs this <em>ApplyTo parameter class</em>.
         *  Reads a line of text from a \b std::istream.
         *  @param istream       The input stream to read from.
         *  @param targetData    If \c CurrentData::Keep, the target \c %AString is not cleared before
         *                       the read operation is performed. Defaults to \c CurrentData::Clear.
         *  @param bufferSize    The amount of characters that the buffer is increased while reading
         *                       parts of the line. Defaults to 256 characters.
         *  @param maxLineWidth  The maximum length of a single line to be read. Longer lines
         *                       get truncated. Defaults to 4096 characters.
         ******************************************************************************************/

        ReadLineFromIStream( std::istream&      istream,
                             enums::CurrentData targetData= enums::CurrentData::Clear,
                             int                bufferSize= 256,
                             int                maxLineWidth= 4096              )
          : istream(istream), TargetData(targetData), BufferSize(bufferSize), MaxLineWidth(maxLineWidth)
        {}
    };

    /** ********************************************************************************************
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  \ref aworx::lib::strings::ReadLineFromIStream "ReadLineFromIStream".
     *  If the end of the input stream was reached, field
     *  \ref aworx::lib::strings::ReadLineFromIStream::IsEOF "IsEOF" of parameter \p param  will
     *  be set to \c true what indicates that a next read operation would fail.
     *  \note
     *    For setting field <em>IsEOF</em> the object will be casted to a non-constant reference.
     *    See \ref aworx::lib::strings::ApplyTo "ApplyTo" for an explanation why it is OK to do so.
     *
     * @param  target     The AString object to read into.
     * @param  param      The object holding the \b std::istream and some parameters.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  ALIB_API   int ApplyTo( AString& target, const ReadLineFromIStream& param);
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const ReadLineFromIStream&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  const ReadLineFromIStream& param )
        {  return  ApplyTo<const ReadLineFromIStream&>( target,           param );  }
    #endif

    /** ********************************************************************************************
     * Copies the contents of the given %AS to into the std::ostream given as reference.
     * @param  stream The ostream object to write the given  AS into.
     * @param  string The AS to write into the given ostream.
     * @returns The ostream to allow concatenated operations.
     **********************************************************************************************/
    inline std::ostream& operator<<( std::ostream& stream, const String& string )
    {
        stream.write( string.Buffer(), string.Length() );
        return stream;
    }

    /** ********************************************************************************************
     * Copies the contents of the given %AS to into the std::ostream given as pointer.
     * @param  stream The ostream object to write the given  AS into.
     * @param  string The AS to write into the given ostream.
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
        string << ReadLineFromIStream( stream, enums::CurrentData::Clear );
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
        ALIB_ASSERT_WARNING ( stream != nullptr, "Given std::istream is nullptr" );

        if (stream != nullptr)
            string << ReadLineFromIStream( *stream, enums::CurrentData::Clear );
        return stream;
    }

}}}

#endif // HPP_AWORX_LIB_COMPATIBILITY_STD_IOSTREAM
