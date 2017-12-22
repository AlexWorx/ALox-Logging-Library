// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if defined(_WIN32) && ALIB_DEBUG

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_UTIL_TOKENIZER)
    #include "alib/strings/util/tokenizer.hpp"
#endif

#include "alox/loggers/vstudiologger.hpp"


#if !defined (_GLIBCXX_IOSTREAM) && !defined(_IOSTREAM_)
    #include <iostream>
#endif
#if !defined (_STRING_H) && !defined(_INC_STRING)
    #include <string.h>
#endif


using namespace std;
using namespace aworx;
using namespace aworx::lox::core;


// #################################################################################################
// Constructor/Destructor
// #################################################################################################

VStudioLogger::VStudioLogger( const String&  name )
: PlainTextLogger( name, "VSTUDIO_CONSOLE", false )
{
    ALIB_ASSERT_ERROR ( lib::ALIB.IsDebuggerPresent(), "This is not a debug session within Visual Studio" )

    // prevent cutting off filenames
    MetaInfo->Format.SearchAndReplace( "%SF:%SL:", "%SP\\%SF(%SL):" );
}

VStudioLogger::~VStudioLogger()
{
    if ( wCharBuffer != nullptr )
        delete[] wCharBuffer;
}

bool VStudioLogger::notifyLogOp( Phase phase)
{
    if ( phase == Phase::End )
        OutputDebugStringA( "\r\n" );
    return true;
}

integer VStudioLogger::logSubstring( const String& buffer, integer start, integer length )
{
    if ( wCharBuffer == nullptr )
        wCharBuffer= new wchar_t[ wCharBufferSize= 128];

    integer wSize;
    for(;;)
    {
        wSize= buffer.ToWString( wCharBuffer, wCharBufferSize, start, length );
        if ( wSize != -2 )
            break;
        delete[] wCharBuffer;
        wCharBufferSize*= 2;
        wCharBuffer= new wchar_t[wCharBufferSize];
    }

    OutputDebugString ( wCharBuffer );

    return wSize;
}


#endif //defined(_WIN32) &&  ALIB_DEBUG
