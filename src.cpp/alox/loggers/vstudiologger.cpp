// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if defined(ALIB_VSTUDIO) && defined(ALIB_DEBUG)

#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

#if !defined (HPP_AWORX_LIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif

#if !defined (HPP_AWORX_LIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif

#if !defined (HPP_AWORX_LIB_SYSTEM_SYSTEMINFO)
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
using namespace aworx::lib;
using namespace aworx::lib::enums;
using namespace aworx::lib::system;
using namespace aworx::lib::strings;
using namespace aworx::lox;
using namespace aworx::lox::core;
using namespace aworx::lox::loggers;


// #################################################################################################
// Constructor/Destructor
// #################################################################################################

VStudioLogger::VStudioLogger( const String&  name )
: PlainTextLogger( name, "VSTUDIO_CONSOLE" )
{
    ALIB_ASSERT_ERROR ( System::IsDebuggerPresent(), "This is not a debug session within Visual Studio" )

    // set default domain level to all: As an app console logger/IDE logger we want to fetch all we can
    RootDomain.SetLevel( Log::DomainLevel::All, Propagation::None );

    // prevent cutting off filenames
    MetaInfo->ConsumableSourcePathPrefix= "";
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

int VStudioLogger::doLogSubstring( const AString& buffer, int start, int length )
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
