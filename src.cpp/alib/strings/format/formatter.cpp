// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"


#if !defined (HPP_ALIB_STRINGS_FORMAT_FORMATTER_PYTHONSTYLE)
    #include "alib/strings/format/formatterpythonstyle.hpp"
#endif


#if !defined (_GLIBCXX_CMATH) && !defined (_CMATH_)
    #include <cmath>
#endif


// For code compatibility with ALox Java/C++
// We have to use underscore as the start of the name and for this have to disable a compiler
// warning. But this is a local code (cpp file) anyhow.
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif

#define _NC _<false>

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif


namespace aworx { namespace lib { namespace strings { namespace format {

void Formatter::Format( AString& target, const Boxes&  args )
{
    // initialize formatters
    Formatter* formatter= this;
    do
        formatter->initializeFormat();
    while( (formatter= formatter->Next) != nullptr );

    // loop over boxes
    size_t argIdx= 0;
    while ( argIdx < args.size() - 1 )
    {
        String formatString;

        // any sort of string?
        const Box& actual= args[argIdx++];
        if( actual.IsArray() )
        {
            if( actual.IsArrayOf<char   >() )
                formatString= actual.Unbox<String>();
            else if(   actual.IsArrayOf<wchar_t  >()
                    || actual.IsArrayOf<char16_t >()
                    || actual.IsArrayOf<char32_t >() )
            {
                formatString= mbsFormatString.Clear() << actual;
            }
        }

        if( formatString.IsNotNull() )
        {
            // try each formatter unless one succeeds
            int  qtyConsume= 0;
            formatter= this;
            while(    ( qtyConsume= formatter->format( target, formatString, args, static_cast<int>( argIdx ) ) ) == 0
                   &&  (formatter= formatter->Next) != nullptr )
            {}

            // no formatter reacted?
            if( qtyConsume == 0 )
                // we just append the string...
                target._NC( formatString );
            else
                // ...otherwise arguments were consumed
                argIdx+= static_cast<size_t>( qtyConsume );
        }

        // not a string: use ToString method, which might have been overwritten by the user.
        // (if not, a default implementation exists, writing the type name and the pointer address)
        else if( !actual.IsNull() )
            actual.Invoke<aworx::IApply>( target );
    }

    // the last argument was not consumed?
    if ( argIdx==args.size() - 1 && !args.back().IsNull() )
        target._NC( args.back() );

}


// #############################################################################################
//  static interface
// #############################################################################################
//! @cond NO_DOX

Formatter*      Formatter::defaultFormatter         = nullptr;
#if ALIB_MODULE_ALL && !defined(DOX_PARSER)
    ThreadLock      Formatter::defaultFormatterLock;
#endif

ALIB_REL_DBG(
Formatter& Formatter::AcquireDefault() ,
Formatter& Formatter::AcquireDefault(  const TString& file, int line, const TString& func  )
)
{
#if ALIB_MODULE_ALL
ALIB_REL_DBG(
    Formatter::defaultFormatterLock.Acquire();
    ,
    defaultFormatterLock.RecursionWarningThreshold= 4;
    Formatter::defaultFormatterLock.Acquire( file, line, func );
)
#endif
    if (!Formatter::defaultFormatter)
        Formatter::defaultFormatter= new FormatterPythonStyle();

    return *Formatter::defaultFormatter;
}

void Formatter::ReleaseDefault()
{
#if ALIB_MODULE_ALL
    if( Formatter::defaultFormatterLock.WillRelease() )
#endif
        Formatter::defaultFormatter->Reset();

#if ALIB_MODULE_ALL
    Formatter::defaultFormatterLock.Release();
#endif
}

//! @endcond

}}}} // namespace [aworx::lib::strings::format]
