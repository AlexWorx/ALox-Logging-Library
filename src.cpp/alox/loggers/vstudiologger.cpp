// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if defined(ALIB_VSTUDIO) && defined(ALIB_DEBUG)

#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif

#if !defined (HPP_ALIB_SYSTEM_SYSTEM)
    #include "alib/system/system.hpp"
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
    ALIB_ASSERT_ERROR ( System::IsDebuggerPresent(), "This is not a debug session within Visual Studio" )

    // prevent cutting off filenames
    MetaInfo->Format.SearchAndReplace( "%Sp", "%SP" );
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

int VStudioLogger::logSubstring( const AString& buffer, int start, int length )
{
    if ( wCharBuffer == nullptr )
        wCharBuffer= new wchar_t[ wCharBufferSize= 128];

    int wSize;
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


#endif //defined(ALIB_VSTUDIO) &&  defined(ALIB_DEBUG)
