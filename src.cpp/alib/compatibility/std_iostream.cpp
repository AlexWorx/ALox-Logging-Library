// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"
#include "alib/compatibility/std_iostream.hpp"
#if defined(_MSC_VER)
    #include <algorithm>
#endif

#if ALIB_MODULE_STRINGS

namespace aworx { namespace lib { namespace strings {

#if defined(DOX_PARSER)
/**
 * \attention
 *   This is a non-existing namespace! It is exclusively defined for the
 *   [documentation parser](http://www.stack.nl/~dimitri/doxygen).
 *
 * \attention
 *   In this <b>"documentation namespace"</b>, you will find sub namespaces
 *   which in turn are purely created for documentation.
 */
namespace thirdparty {
/**
 * With the inclusion of header file <c>alib/compatibility/std_string.hpp</c>,
 * some compatibility between <b>%ALib Strings</b> and string types of namespace \b std
 * is provided.
 *
 * <b>1. Specializations of  %T_String:</b><br>
 * Specializations of \ref aworx::lib::strings::T_String is given for type
 * \b std::string. This allows to construct objects of class \b %String directly and implicitly
 * from objects and pointers to objects of \b std::string.
 *
 * <b>2. Applicable Types:</b><br>
 * Support for applying (appending contents of objects of the types to objects of class \b %AString)
 * is given. Applicable types are:
 * - \b std::string
 * - \b std::wstring
 * - \b std::u16string
 * - \b std::u32string
 *
 * <b>3. Reading from std::istream:</b><br>
 * Class \ref aworx::lib::strings::thirdparty::std::ReadLineFromIStream "ReadLineFromIStream"
 * is an applicable type used to read lines of textual files from a \b std::istream object into
 * an object of class \b %AString.
 *
 *
 *
 * \attention
 *   The functions \b operator<< and \b operator>> as well as the template specializations, in
 *   reality are located in namespace
 *   \ref aworx::lib::strings
 *   For the [documentation parser](http://www.stack.nl/~dimitri/doxygen) they were moved here
 *   to keep the original namespace documentation clean.
 */
namespace std {

#endif

integer T_Apply<thirdparty::std::ReadLineFromIStream>::Apply( AString& target, const thirdparty::std::ReadLineFromIStream& reader)
{
    // we are required to write to the param object. So we cast to non-const. This is OK, as
    // the const specifier came through TMP.
    thirdparty::std::ReadLineFromIStream& param= const_cast<thirdparty::std::ReadLineFromIStream&>( reader );

    if ( param.TargetData == CurrentData::Clear )
        target.Clear();
    integer origLength= target.Length();

    // read loop
    while( !param.IStream.eof() )
    {
        // calc buffer size (if we hit the overall line width)
        // and check if we reached the limit per line
        integer actReadSize= (std::min)( param.BufferSize,  param.MaxLineWidth - ( target.Length() - origLength) + 1  );
        if ( actReadSize < 2 )
            return target.Length() - origLength;

        target.EnsureRemainingCapacity( actReadSize );

        // read
        int64_t start= target.Length();
        param.IStream.getline( target.VBuffer() + start, actReadSize );
        std::streamsize gCount= param.IStream.gcount();
        std::streamsize count=  static_cast<std::streamsize>(strlen( target.Buffer() + start ));

        bool lineComplete=  count + 1 == gCount;

        // something read?
        if ( count > 0 )
        {
            // be sure to not have a carriage return at the start
            if( *(target.Buffer() + start) == '\r' )
            {
                target.Delete<false>( static_cast<integer>(start), 1 );
                count--;
            }

            // be sure to not have a carriage return at the end
            start+= count;
            if( *(target.Buffer() + start -1 ) == '\r' )
                start--;

            target.SetLength<false>( static_cast<integer>(start) );

            // if we are at the end of the file (without delimiter) we stop now
            if ( param.IStream.eof() )
            {
                param.IsEOF= true;
                return target.Length() - origLength;
            }
        }


        // delim read
        if ( lineComplete )
        {
            ALIB_STRING_DBG_UNTERMINATE(target, 0)
            return target.Length() - origLength;
        }

        // buffer was not big enough
        if ( gCount == actReadSize -1)
        {
            if ( param.IStream.eof() )
            {
                ALIB_STRING_DBG_UNTERMINATE(target, 0)
                return true;
            }

            // otherwise, it should really have been the buffer size, so let's clear the bit
            // and continue with more buffer space
            ALIB_ASSERT( param.IStream.rdstate() == std::iostream::failbit )
            param.IStream.clear();
            continue;
        }

        // the eof just happened now
        if ( param.IStream.eof() )
            break;

        if ( param.IStream.rdstate() == std::iostream::failbit )
        {
            ALIB_ERROR( "Unknown Error Reading File. Maybe method implemented incomplete?" );
            break;
        }

        // anything else to add here? I guess not! But you never know with this strange
        // iostream classes!

        //...

        // This happens if \0 is in the file
        ALIB_ERROR( "Unknown Error Reading File. Probably not a text file." );
        break;
    }

    ALIB_STRING_DBG_UNTERMINATE(target, 0)
    param.IsEOF= true;
    return target.Length() - origLength;
}

// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::apply to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
}}
#endif


}}}// namespace [aworx::lib::strings]
#endif // ALIB_MODULE_STRINGS

