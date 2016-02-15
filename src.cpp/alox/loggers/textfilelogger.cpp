// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALIB_ALIB)
    #include "alib/alib.hpp"
#endif

#include "alib/config/configuration.hpp"
#include "alib/compatibility/std_iostream.hpp"
#include "alox/loggers/textfilelogger.hpp"
#include <fstream>


using namespace std;
using namespace aworx;

void TextFileLogger::openFile()
{
    os= new ofstream( FileName.ToCString(), ios::app );
    if ( !os->is_open() )
    {
        ALIB_WARNING( String512() <<  "Could not open file: \"" << FileName << '\"');
        delete os;  os= nullptr;
        IsDisabled= true;
        return;
    }
}

void TextFileLogger::closeFile()
{
    ALIB_ASSERT( os != nullptr );
    os->close();
    delete os;  os= nullptr;
}


void TextFileLogger::notifyMultiLineOp( Phase phase )
{
    // save state (to have it in doTextLog)
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

    return !IsDisabled;
}

int TextFileLogger::doLogSubstring( const AString& buffer, int start, int length )
{
    *os << String( buffer, start, length );
    return lib::strings::CString::LengthWhenConvertedToWChar( buffer.Buffer() + start, length );
}
