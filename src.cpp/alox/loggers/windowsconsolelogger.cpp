// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#include "alib/stdafx_alib.h"

#if defined( _WIN32 )

#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif

#include "alox/loggers/windowsconsolelogger.hpp"
#include "alib/core/util.hpp"

#if !defined (_GLIBCXX_IOSTREAM) && !defined(_IOSTREAM_)
    #include <iostream>
#endif
#if !defined (_STRING_H) && !defined(_INC_STRING)
    #include <string.h>
#endif


using namespace std;
namespace aworx {
    namespace lox   {

    using namespace core;



// #################################################################################################
// Windows Console Colors
// #################################################################################################
 #define W32C_FOREGROUND_MASK   0xFFF0
 #define W32C_BACKGROUND_MASK   0xFF0F

 #define W32C_BLACK          0
 #define W32C_RED            FOREGROUND_RED
 #define W32C_GREEN          FOREGROUND_GREEN
 #define W32C_BLUE           FOREGROUND_BLUE
 #define W32C_CYAN           FOREGROUND_GREEN | FOREGROUND_BLUE
 #define W32C_MAGENTA        FOREGROUND_RED   | FOREGROUND_BLUE
 #define W32C_YELLOW         FOREGROUND_RED   | FOREGROUND_GREEN
 #define W32C_WHITE          FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY

 #define W32C_GRAY_LIGHT     FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE
 #define W32C_GRAY_DARK      FOREGROUND_INTENSITY

#if !defined( IS_DOXYGEN_PARSER)
 WORD win32Cols[]=
 {
    W32C_RED,
    W32C_GREEN,
    W32C_YELLOW,
    W32C_BLUE,
    W32C_MAGENTA,
    W32C_CYAN,
 };
#endif

// #################################################################################################
// Constructor/Destructor
// #################################################################################################
WindowsConsoleLogger::WindowsConsoleLogger( const String&  name )
:    TextLogger( name, "WINDOWS_CONSOLE",  true)
{
    // get actual console attributes
    WORD actualAttributes;
    {
        HANDLE H=    GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo( H, &info );
        actualAttributes= info.wAttributes;
        originalConsoleAttributes= actualAttributes;
    }

    // evaluate environment variable "ALOX_CONSOLE_HAS_LIGHT_BACKGROUND"
    {
        int  configVarSet;
        bool configVarTrue= ALIB::Config.IsTrue( ALox::ConfigCategoryName, "CONSOLE_HAS_LIGHT_BACKGROUND", &configVarSet );
        if( configVarSet != 0 )
            IsBackgroundLight=  configVarTrue;
        else
            IsBackgroundLight=   ( originalConsoleAttributes & ~W32C_FOREGROUND_MASK )        < 7;
    }

    // colorize log verbosity strings.
    ALIB_ASSERT_RESULT_NOT_EQUALS( MetaInfo->Format.SearchAndReplace( "]%V[", "][" ), 0);

    MsgColorInfo            = actualAttributes & ~W32C_FOREGROUND_MASK;
    MsgColorError           = W32C_RED;
    MsgColorWarning         = W32C_BLUE;
    MsgColorVerbose         = W32C_GRAY_DARK;
    if ( !IsBackgroundLight )
    {
        MsgColorError           |= FOREGROUND_INTENSITY;
        MsgColorWarning         |= FOREGROUND_INTENSITY;
        MsgColorVerbose         |= FOREGROUND_INTENSITY;
    }

    // evaluate config variable CODE_PAGE
    {
        int32_t configCodePage;

        if ( ALIB::Config.Get( ALox::ConfigCategoryName, "CODE_PAGE", configCodePage ) != 0 )
            CodePage= (UINT) configCodePage;
    }

}

WindowsConsoleLogger::~WindowsConsoleLogger()
{
}

// #################################################################################################
// logText
// #################################################################################################
void WindowsConsoleLogger::logText( Domain&        ,    Verbosity  verbosity,
                                    AString&    msg,
                                    ScopeInfo&     ,    int                   )
{
    HANDLE H=       GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD ignore;

    // get actual console attributes
    WORD actualAttributes;
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo( H, &info );
        actualAttributes= info.wAttributes;
    }
    WORD previousAttributes= actualAttributes;

    // set codepage;
    if ( CodePage != 0 )
        SetConsoleOutputCP( CodePage );


    // loop over message, print the parts between the escape sequences
    int column= 0;
    Tokenizer msgParts( msg, '\x1B' );
    Substring& actual= msgParts.Actual;
    Substring& rest=   msgParts.Rest;
    for(;;)
    {
        if ( msgParts.Next( Whitespaces::Keep ).IsNotEmpty() )
        {
            WriteFile( H, actual.Buffer(), actual.Length(), &ignore, NULL );
            column+= lib::strings::CString::LengthWhenConvertedToWChar( actual.Buffer(), actual.Length() );
        }

        if ( !msgParts.HasNext() )
            break;

        // found a delimiter: process ESC sequence
        char c= rest.Consume<false>();

        // Colors
        bool isForeGround=  true;
        if( c == 'C' || c == 'c' )
        {
            isForeGround=  c== 'c';

            c= rest.Consume();
            int colNo= c - '0';
            ALIB_ASSERT_WARNING( colNo >=0 && colNo <=9, "ConsoleLogger: Unknown ESC-c code" );

            WORD attr= 0;
            WORD light=  (isForeGround ? !IsBackgroundLight : IsBackgroundLight )  ? FOREGROUND_INTENSITY : 0;

            // 0..5 (red, green, yellow, blue, magenta, cyan)
            if ( colNo >= 0 && colNo < 6)  attr= (win32Cols[colNo] | light);

            else if ( colNo == 6 )         attr= W32C_BLACK;
            else if ( colNo == 7 )         attr= W32C_WHITE;
            else if ( colNo == 8 )         attr=  light ? W32C_GRAY_LIGHT : W32C_GRAY_DARK;
            else if ( colNo == 9 )         attr= isForeGround  ?    originalConsoleAttributes & ~W32C_FOREGROUND_MASK
                                                               :  ( originalConsoleAttributes & ~W32C_BACKGROUND_MASK ) >> 4;

            else
            {
                ALIB_WARNING( "Unknown ESC- code" );
            }

            actualAttributes=  isForeGround  ?  ( actualAttributes & W32C_FOREGROUND_MASK ) |   attr
                                             :  ( actualAttributes & W32C_BACKGROUND_MASK ) |  (attr << 4);
        }

        // Styles
        else if ( c == 's' )
        {
            // bold/italics style not supported in Windows console

            // reset all
            if ( rest.Consume() == 'a' )
                actualAttributes= originalConsoleAttributes;
        }

        // auto tab / end of meta
        else if ( c == 't'  || c == 'A' )
        {
            bool endOfMeta= c == 'A';
            c=  rest.Consume();
            int extraSpace=  c >= '0' && c <= '9' ? (int) ( c - '0' )
                                                  : (int) ( c - 'A' ) + 10;

            // tab stop (write spaces using a growing buffer)
            int tabStop= AutoSizes.Next( column, extraSpace );
            int qtySpaces= tabStop - column;
            if( qtySpaces > 0 )
            {
                column+= qtySpaces;
                const AString& spaces= lib::Util::GetSpaces();
                int spacesLength= spaces.Length();
                while ( qtySpaces > 0 )
                {
                    int nextQty= qtySpaces < spacesLength ? qtySpaces : spacesLength;
                    WriteFile( H, spaces.Buffer(), nextQty, &ignore, NULL );
                    qtySpaces-= nextQty;
                }
            }



            if ( endOfMeta )
            {
                WORD col;
                switch ( verbosity )
                {
                    case Verbosity::Verbose:   col= MsgColorVerbose;     break;
                    case Verbosity::Info:      col= MsgColorInfo;        break;
                    case Verbosity::Warning:   col= MsgColorWarning;     break;
                    case Verbosity::Error:     col= MsgColorError;       break;
                    default: col= 0; break;
                }
                actualAttributes= ( actualAttributes & W32C_FOREGROUND_MASK ) | col;
            }

        }


        // Link (we just colorize links here)
        else if ( c == 'l' )
        {
            if ( rest.Consume() == 'S' )
                actualAttributes=  ( actualAttributes & W32C_FOREGROUND_MASK ) |  W32C_BLUE | ( IsBackgroundLight ? 0 : FOREGROUND_INTENSITY );
            else
                actualAttributes=  ( actualAttributes & W32C_FOREGROUND_MASK ) |  ( originalConsoleAttributes & ~W32C_FOREGROUND_MASK );
        }


        else
        {
            ALIB_WARNING( "WindowsConsoleLogger: Unknown ESC code" );
        }

        // set the attributes
        ALIB_ASSERT_RESULT_NOT_EQUALS( SetConsoleTextAttribute( H, actualAttributes ), 0 );


    } // write loop

    ALIB_ASSERT_RESULT_NOT_EQUALS( SetConsoleTextAttribute( H, previousAttributes ), 0 );

    cout << endl;


}

}}// namespace aworx::lox

#endif // Win32
