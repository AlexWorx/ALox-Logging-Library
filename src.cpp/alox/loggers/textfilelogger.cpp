// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
#   include "alib/config/configuration.hpp"
#endif
#if !defined (HPP_ALIB_COMPATIBILITY_STD_IOSTREAM)
#   include "alib/compatibility/std_iostream.hpp"
#endif
#if !defined (HPP_ALOX_TEXT_FILE_LOGGER)
#   include "alox/loggers/textfilelogger.hpp"
#endif

#if !defined (_GLIBCXX_FSTREAM) && !defined(_FSTREAM_)
#include <fstream>
#endif


using namespace std;
using namespace aworx;

void TextFileLogger::openFile()
{
    os= new ofstream( FileName.ToCString(), ios::app );
    if ( !os->is_open() )
    {
        ALIB_WARNING( "Could not open file: '{}'.", FileName);
        delete os;  os= nullptr;
        hasIoError= true;
        return;
    }
    hasIoError= false;
}

void TextFileLogger::closeFile()
{
    ALIB_ASSERT( os != nullptr );
    os->close();
    delete os;  os= nullptr;
}


void TextFileLogger::notifyMultiLineOp( Phase phase )
{
    // save state (to have it in logText)
    currentlyInMultiLineOp= (phase == Phase::Begin);

    // open/close the file
    if ( phase == Phase::Begin )
        openFile();
    else
        closeFile();
}

bool TextFileLogger::notifyLogOp( Phase phase )
{
    if ( phase == Phase::End )
        *os << endl;

    // open/close
    if( !currentlyInMultiLineOp )
    {
        if ( phase == Phase::Begin )
            openFile();
        else
            closeFile();
    }

    return !hasIoError;
}

integer TextFileLogger::logSubstring( const String& buffer, integer start, integer length )
{
    if (!hasIoError)
        *os << String( buffer, start, length );
    return lib::strings::CString::LengthWhenConvertedToWChar( buffer.Buffer() + start, length );
}
