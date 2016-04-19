// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif

#include "alib/config/configuration.hpp"
#include "alib/strings/tokenizer.hpp"
#include "alox/loggers/ansilogger.hpp"
#include "alib/compatibility/std_iostream.hpp"
#include "alib/system/system.hpp"
#include "alib/core/util.hpp"

using namespace std;
using namespace aworx::lox::core;

namespace aworx {
namespace       lox {
namespace           loggers{

// #################################################################################################
// ANSI Escape Codes
// #################################################################################################
 #if defined(_MSC_VER)
// MSC  (as of 12/2015):
// C4579: in-class initialization for type 'const aworx::SLiteral<10>'
// is not yet implemented; static member will remain uninitialized at runtime but
// use in constant-expressions is supported
          SLiteral<5>   AnsiLogger::ANSI_RED              { "\033[31m"       }; ///< Select red as foreground color
          SLiteral<5>   AnsiLogger::ANSI_GREEN            { "\033[32m"       }; ///< Select green as foreground color
          SLiteral<5>   AnsiLogger::ANSI_YELLOW           { "\033[33m"       }; ///< Select yellow as foreground color
          SLiteral<5>   AnsiLogger::ANSI_BLUE             { "\033[34m"       }; ///< Select blue as foreground color
          SLiteral<5>   AnsiLogger::ANSI_MAGENTA          { "\033[35m"       }; ///< Select magenta as foreground color
          SLiteral<5>   AnsiLogger::ANSI_CYAN             { "\033[36m"       }; ///< Select cyan as foreground color
          SLiteral<5>   AnsiLogger::ANSI_BLACK            { "\033[30m"       }; ///< Select black as foreground color
          SLiteral<10>  AnsiLogger::ANSI_WHITE            { "\033[38;5;15m"  }; ///< Select white as foreground color
          SLiteral<11>  AnsiLogger::ANSI_GRAY             { "\033[38;5;240m" }; ///< Select gray as foreground color
          SLiteral<5>   AnsiLogger::ANSI_STD_COL          { "\033[39m"       }; ///< Select standard foreground color

          SLiteral<5>   AnsiLogger::ANSI_BG_RED           { "\033[41m"       }; ///< Select red as background color
          SLiteral<5>   AnsiLogger::ANSI_BG_GREEN         { "\033[42m"       }; ///< Select green as background color
          SLiteral<5>   AnsiLogger::ANSI_BG_YELLOW        { "\033[43m"       }; ///< Select yellow as background color
          SLiteral<5>   AnsiLogger::ANSI_BG_BLUE          { "\033[44m"       }; ///< Select blue as background color
          SLiteral<5>   AnsiLogger::ANSI_BG_MAGENTA       { "\033[45m"       }; ///< Select magenta as background color
          SLiteral<5>   AnsiLogger::ANSI_BG_CYAN          { "\033[46m"       }; ///< Select cyan as background color
          SLiteral<5>   AnsiLogger::ANSI_BG_BLACK         { "\033[40m"       }; ///< Select black as background color
          SLiteral<10>  AnsiLogger::ANSI_BG_WHITE         { "\033[48;5;15m"  }; ///< Select white as background color
          SLiteral<11>  AnsiLogger::ANSI_BG_GRAY          { "\033[48;5;240m" }; ///< Select gray as background color
          SLiteral<5>   AnsiLogger::ANSI_BG_STD_COL       { "\033[49m"       }; ///< Select standard background color

          SLiteral<10>  AnsiLogger::ANSI_LIGHT_RED        { "\033[38;5;09m"  }; ///< Select light red as foreground color
          SLiteral<10>  AnsiLogger::ANSI_LIGHT_GREEN      { "\033[38;5;10m"  }; ///< Select light green as foreground color
          SLiteral<10>  AnsiLogger::ANSI_LIGHT_YELLOW     { "\033[38;5;11m"  }; ///< Select light yellow as foreground color
          SLiteral<10>  AnsiLogger::ANSI_LIGHT_BLUE       { "\033[38;5;12m"  }; ///< Select light blue as foreground color
          SLiteral<10>  AnsiLogger::ANSI_LIGHT_MAGENTA    { "\033[38;5;13m"  }; ///< Select light magenta as foreground color
          SLiteral<10>  AnsiLogger::ANSI_LIGHT_CYAN       { "\033[38;5;14m"  }; ///< Select light cyan as foreground color
          SLiteral<11>  AnsiLogger::ANSI_LIGHT_GRAY       { "\033[38;5;250m" }; ///< Select light gray as foreground color
          SLiteral<5>   AnsiLogger::ANSI_LIGHT_STD_COL    { "\033[39m"       }; ///< Select standard foreground color

          SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_RED     { "\033[48;5;09m"  }; ///< Select light red as background color
          SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_GREEN   { "\033[48;5;10m"  }; ///< Select light green as background color
          SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_YELLOW  { "\033[48;5;11m"  }; ///< Select light yellow as background color
          SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_BLUE    { "\033[48;5;12m"  }; ///< Select light blue as background color
          SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_MAGENTA { "\033[48;5;13m"  }; ///< Select light magenta as background color
          SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_CYAN    { "\033[48;5;14m"  }; ///< Select light cyan as background color
          SLiteral<11>  AnsiLogger::ANSI_BG_LIGHT_GRAY    { "\033[48;5;250m" }; ///< Select light gray as background color
          SLiteral<5>   AnsiLogger::ANSI_BG_LIGHT_STD_COL { "\033[49m"       }; ///< Select standard background color

          SLiteral<4>   AnsiLogger::ANSI_BOLD             { "\033[1m"        }; ///< Select bold font style
          SLiteral<4>   AnsiLogger::ANSI_ITALICS          { "\033[3m"        }; ///< Select italics font style
          SLiteral<4>   AnsiLogger::ANSI_STD_STYLE        { "\033[0m"        }; ///< Select standard font style
          SLiteral<4>   AnsiLogger::ANSI_RESET            { "\033[0m"        }; ///< Reset colors and font style

#else
constexpr SLiteral<5>   AnsiLogger::ANSI_RED             ;
constexpr SLiteral<5>   AnsiLogger::ANSI_GREEN           ;
constexpr SLiteral<5>   AnsiLogger::ANSI_YELLOW          ;
constexpr SLiteral<5>   AnsiLogger::ANSI_BLUE            ;
constexpr SLiteral<5>   AnsiLogger::ANSI_MAGENTA         ;
constexpr SLiteral<5>   AnsiLogger::ANSI_CYAN            ;
constexpr SLiteral<5>   AnsiLogger::ANSI_BLACK           ;
constexpr SLiteral<10>  AnsiLogger::ANSI_WHITE           ;
constexpr SLiteral<11>  AnsiLogger::ANSI_GRAY            ;
constexpr SLiteral<5>   AnsiLogger::ANSI_STD_COL         ;

constexpr SLiteral<5>   AnsiLogger::ANSI_BG_RED          ;
constexpr SLiteral<5>   AnsiLogger::ANSI_BG_GREEN        ;
constexpr SLiteral<5>   AnsiLogger::ANSI_BG_YELLOW       ;
constexpr SLiteral<5>   AnsiLogger::ANSI_BG_BLUE         ;
constexpr SLiteral<5>   AnsiLogger::ANSI_BG_MAGENTA      ;
constexpr SLiteral<5>   AnsiLogger::ANSI_BG_CYAN         ;
constexpr SLiteral<5>   AnsiLogger::ANSI_BG_BLACK        ;
constexpr SLiteral<10>  AnsiLogger::ANSI_BG_WHITE        ;
constexpr SLiteral<11>  AnsiLogger::ANSI_BG_GRAY         ;
constexpr SLiteral<5>   AnsiLogger::ANSI_BG_STD_COL      ;

constexpr SLiteral<10>  AnsiLogger::ANSI_LIGHT_RED       ;
constexpr SLiteral<10>  AnsiLogger::ANSI_LIGHT_GREEN     ;
constexpr SLiteral<10>  AnsiLogger::ANSI_LIGHT_YELLOW    ;
constexpr SLiteral<10>  AnsiLogger::ANSI_LIGHT_BLUE      ;
constexpr SLiteral<10>  AnsiLogger::ANSI_LIGHT_MAGENTA   ;
constexpr SLiteral<10>  AnsiLogger::ANSI_LIGHT_CYAN      ;
constexpr SLiteral<11>  AnsiLogger::ANSI_LIGHT_GRAY      ;
constexpr SLiteral<5>   AnsiLogger::ANSI_LIGHT_STD_COL   ;

constexpr SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_RED    ;
constexpr SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_GREEN  ;
constexpr SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_YELLOW ;
constexpr SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_BLUE   ;
constexpr SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_MAGENTA;
constexpr SLiteral<10>  AnsiLogger::ANSI_BG_LIGHT_CYAN   ;
constexpr SLiteral<11>  AnsiLogger::ANSI_BG_LIGHT_GRAY   ;
constexpr SLiteral<5>   AnsiLogger::ANSI_BG_LIGHT_STD_COL;

constexpr SLiteral<4>   AnsiLogger::ANSI_BOLD            ;
constexpr SLiteral<4>   AnsiLogger::ANSI_ITALICS         ;
constexpr SLiteral<4>   AnsiLogger::ANSI_STD_STYLE       ;
constexpr SLiteral<4>   AnsiLogger::ANSI_RESET           ;
#endif

// #################################################################################################
// Constructor/Destructor
// #################################################################################################
AnsiLogger::AnsiLogger( std::basic_ostream<char>* oStream, bool usesStdStreams,
                        const String&  name, const String&  typeName  )
:    TextLogger( name, typeName, usesStdStreams )
,    oStream( oStream )
{
    // evaluate environment variable "ALOX_CONSOLE_HAS_LIGHT_BACKGROUND"
    int  configVarSet;
    bool configVarTrue= ALIB::Config.IsTrue( ALox::ConfigCategoryName, "CONSOLE_HAS_LIGHT_BACKGROUND", &configVarSet );
    if( configVarSet != 0 )
        IsBackgroundLight=  configVarTrue;
    else
    {
        // default: dark background
        IsBackgroundLight= false;

        // some IDEs have light background output panels
        auto RTE= System::RTE();
        if (      RTE == System::RuntimeEnvironment::QTCreator
              ||  RTE == System::RuntimeEnvironment::EclipseCDT )
              IsBackgroundLight= true;
    }

    //--- modify the default format attributes of the MetaInfo support colors ---

    // remove verbosity information and colorize the whole line
    ALIB_ASSERT_RESULT_NOT_EQUALS( MetaInfo->Format.SearchAndReplace( "]%V[", "][" ), 0);
    if ( IsBackgroundLight )
    {
        MsgPrefixError           = ANSI_RED;
        MsgPrefixWarning         = ANSI_BLUE;
        MsgPrefixVerbose         = ANSI_GRAY;
    }
    else
    {
        MsgPrefixError           = ANSI_LIGHT_RED;
        MsgPrefixWarning         = ANSI_LIGHT_BLUE;
        MsgPrefixVerbose         = ANSI_LIGHT_GRAY;
    }


    // set source file background to gray.
    // Note: We are using the ESC gray here, because only at runtime
    //       it is decided if this will be light or dark gray.
    TString colorize= "%SF(%SL):";
    int idx= MetaInfo->Format.IndexOf( colorize );
    if (idx >= 0 )
    {
        MetaInfo->Format.InsertAt( ESC::BG_GRAY,      idx );
        MetaInfo->Format.InsertAt( ANSI_BG_STD_COL,   idx + 3 + colorize.Length() );
    }

    MetaInfo->NoSourceFileInfo= NoSourceFileInfo._<false>( ANSI_BG_CYAN)
                                                ._<false>( MetaInfo->NoSourceFileInfo )
                                                ._<false>( ANSI_BG_STD_COL );
    MetaInfo->NoMethodInfo=     NoMethodInfo    ._<false>( ANSI_BG_CYAN)
                                                ._<false>( MetaInfo->NoMethodInfo )
                                                ._<false>( ANSI_BG_STD_COL );
}

AnsiLogger::~AnsiLogger()
{
}

// #################################################################################################
// logText
// #################################################################################################


void AnsiLogger::logText( core::Domain&      ,    Verbosity  verbosity,
                          AString&        msg,
                          ScopeInfo&         ,    int                )
{
    // loop over message, print the parts between the escape sequences
    int column= 0;
    Tokenizer msgParts( msg, '\x1B' );
    Substring& actual= msgParts.Actual;
    Substring& rest=   msgParts.Rest;
    for(;;)
    {
        msgParts.Next( Whitespaces::Keep );

        // check if end of actual msg part is an ANSI sequence. If yes, we extend the actual msg
        if ( rest.CharAtStart() == '[' )
        {
            // read the 'm'
            int idx= rest.IndexOf( 'm' );
            if ( idx < 0 ) // unknown ANSI Code
            {
                ALIB_WARNING( "Unknown ANSI ESC Code " );
                oStream->write( actual.Buffer(), actual.Length() );
                continue;
            }

            int wCharLength= lib::strings::CString::LengthWhenConvertedToWChar( actual.Buffer(), actual.Length() );
            column+= wCharLength >= 0 ? wCharLength : actual.Length();

            actual.SetLength<false>( actual.Length() + idx + 2 );
            rest.Consume<false>( idx  + 1 );

            oStream->write( actual.Buffer(), actual.Length() );

            continue;
        }
        else
        {
            if ( actual.IsNotEmpty() )
            {
                oStream->write( actual.Buffer(), actual.Length() );
                column+= lib::strings::CString::LengthWhenConvertedToWChar( actual.Buffer(), actual.Length() );
            }
        }

        // end of loop?
        if ( !msgParts.HasNext() )
            break;

        // found an ESC sequence
        char c= rest.Consume();

        // Colors
        bool isForeGround=  true;
        if( c == 'C' || c == 'c' )
        {
            isForeGround=  c== 'c';

            c= rest.Consume();
            int colNo= c - '0';
            ALIB_ASSERT_WARNING( colNo >=0 && colNo <=9, "AnsiLogger: Unknown ESC-c code" );

            // add bg
            colNo+=  isForeGround ? 0 : 10;

            // add light
            colNo+=  (isForeGround ? !IsBackgroundLight : IsBackgroundLight )  ? 20 : 0;

            String ansiCol;
            switch( colNo)
            {
                case  0: ansiCol= AnsiLogger::ANSI_RED              ; break;
                case  1: ansiCol= AnsiLogger::ANSI_GREEN            ; break;
                case  2: ansiCol= AnsiLogger::ANSI_YELLOW           ; break;
                case  3: ansiCol= AnsiLogger::ANSI_BLUE             ; break;
                case  4: ansiCol= AnsiLogger::ANSI_MAGENTA          ; break;
                case  5: ansiCol= AnsiLogger::ANSI_CYAN             ; break;
                case  6: ansiCol= AnsiLogger::ANSI_BLACK            ; break;
                case  7: ansiCol= AnsiLogger::ANSI_WHITE            ; break;
                case  8: ansiCol= AnsiLogger::ANSI_GRAY             ; break;
                case  9: ansiCol= AnsiLogger::ANSI_STD_COL          ; break;

                case 10: ansiCol= AnsiLogger::ANSI_BG_RED           ; break;
                case 11: ansiCol= AnsiLogger::ANSI_BG_GREEN         ; break;
                case 12: ansiCol= AnsiLogger::ANSI_BG_YELLOW        ; break;
                case 13: ansiCol= AnsiLogger::ANSI_BG_BLUE          ; break;
                case 14: ansiCol= AnsiLogger::ANSI_BG_MAGENTA       ; break;
                case 15: ansiCol= AnsiLogger::ANSI_BG_CYAN          ; break;
                case 16: ansiCol= AnsiLogger::ANSI_BG_BLACK         ; break;
                case 17: ansiCol= AnsiLogger::ANSI_BG_WHITE         ; break;
                case 18: ansiCol= AnsiLogger::ANSI_BG_GRAY          ; break;
                case 19: ansiCol= AnsiLogger::ANSI_BG_STD_COL       ; break;

                case 20: ansiCol= AnsiLogger::ANSI_LIGHT_RED        ; break;
                case 21: ansiCol= AnsiLogger::ANSI_LIGHT_GREEN      ; break;
                case 22: ansiCol= AnsiLogger::ANSI_LIGHT_YELLOW     ; break;
                case 23: ansiCol= AnsiLogger::ANSI_LIGHT_BLUE       ; break;
                case 24: ansiCol= AnsiLogger::ANSI_LIGHT_MAGENTA    ; break;
                case 25: ansiCol= AnsiLogger::ANSI_LIGHT_CYAN       ; break;
                case 26: ansiCol= AnsiLogger::ANSI_BG_BLACK         ; break;
                case 27: ansiCol= AnsiLogger::ANSI_BG_WHITE         ; break;
                case 28: ansiCol= AnsiLogger::ANSI_LIGHT_GRAY       ; break;
                case 29: ansiCol= AnsiLogger::ANSI_STD_COL          ; break;

                case 30: ansiCol= AnsiLogger::ANSI_BG_LIGHT_RED     ; break;
                case 31: ansiCol= AnsiLogger::ANSI_BG_LIGHT_GREEN   ; break;
                case 32: ansiCol= AnsiLogger::ANSI_BG_LIGHT_YELLOW  ; break;
                case 33: ansiCol= AnsiLogger::ANSI_BG_LIGHT_BLUE    ; break;
                case 34: ansiCol= AnsiLogger::ANSI_BG_LIGHT_MAGENTA ; break;
                case 35: ansiCol= AnsiLogger::ANSI_BG_LIGHT_CYAN    ; break;
                case 36: ansiCol= AnsiLogger::ANSI_BG_BLACK         ; break;
                case 37: ansiCol= AnsiLogger::ANSI_BG_WHITE         ; break;
                case 38: ansiCol= AnsiLogger::ANSI_BG_LIGHT_GRAY    ; break;
                case 39: ansiCol= AnsiLogger::ANSI_BG_STD_COL       ; break;
                default: ALIB_ASSERT("Error in ANSI Code")
                         ansiCol= "";
                         break;
            }

            oStream << ansiCol;
        }

        // Styles
        else if ( c == 's' )
        {
            // bold/italics style not supported in Windows console

            // reset all
            if ( rest.Consume() == 'a' )
                oStream << ANSI_RESET;
        }

        // auto tab / end of meta
        else if ( c == 't' || c == 'A' )
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
                lib::Util::WriteSpaces( cout, qtySpaces );
                column+= qtySpaces;
            }

            if ( endOfMeta )
            {
                String msgPrefix;
                switch ( verbosity )
                {
                    case Verbosity::Verbose:   msgPrefix= MsgPrefixVerbose;     break;
                    case Verbosity::Info:      msgPrefix= MsgPrefixInfo;        break;
                    case Verbosity::Warning:   msgPrefix= MsgPrefixWarning;     break;
                    case Verbosity::Error:     msgPrefix= MsgPrefixError;       break;
                    default: msgPrefix= nullptr;
                }
                oStream << msgPrefix;
            }
        }

        // Link (we just colorize links here)
        else if ( c == 'l' )
        {
            if ( rest.Consume() == 'S' )
                oStream << ( IsBackgroundLight ? ANSI_LIGHT_BLUE : ANSI_LIGHT_BLUE );
            else
                oStream << ANSI_STD_COL;
        }

        else
        {
            rest.Consume();
            ALIB_WARNING_S512( "Unknown ESC code '" << c << '\'')
        }

    } // write loop


    (*oStream) << MsgSuffix << endl;
}

// #################################################################################################
// AnsiConsoleLogger
// #################################################################################################
AnsiConsoleLogger::AnsiConsoleLogger( const String&  name )
: AnsiLogger( &cout, true, name, "ANSI_CONSOLE" )
{
}

AnsiConsoleLogger::~AnsiConsoleLogger()
{
}


}}}
