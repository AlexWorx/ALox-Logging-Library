// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif
#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif


using namespace aworx;
namespace aworx { namespace lox {




// #################################################################################################
// ESC codes
// #################################################################################################
#if defined(_MSC_VER)
// MSC  (as of 12/2015):
// C4579: in-class initialization for type 'const aworx::SLiteral<10>'
// is not yet implemented; static member will remain uninitialized at runtime but
// use in constant-expressions is supported
          SLiteral<3>  ESC::RED        { "\033c0" }; ///< Select red color for foreground.
          SLiteral<3>  ESC::GREEN      { "\033c1" }; ///< Select green color for foreground.
          SLiteral<3>  ESC::YELLOW     { "\033c2" }; ///< Select yellow color for foreground.
          SLiteral<3>  ESC::BLUE       { "\033c3" }; ///< Select blue color for foreground.
          SLiteral<3>  ESC::MAGENTA    { "\033c4" }; ///< Select magenta color for foreground.
          SLiteral<3>  ESC::CYAN       { "\033c5" }; ///< Select cyan color for foreground.
          SLiteral<3>  ESC::BLACK      { "\033c6" }; ///< Select black color for foreground.
          SLiteral<3>  ESC::WHITE      { "\033c7" }; ///< Select white color for foreground.
          SLiteral<3>  ESC::GRAY       { "\033c8" }; ///< Select gray color for foreground.
          SLiteral<3>  ESC::FG_RESET   { "\033c9" }; ///< Select std color for foreground.4

          SLiteral<3>  ESC::BG_RED     { "\033C0" }; ///< Select red color for background.
          SLiteral<3>  ESC::BG_GREEN   { "\033C1" }; ///< Select green color for background.
          SLiteral<3>  ESC::BG_YELLOW  { "\033C2" }; ///< Select yellow color for background.
          SLiteral<3>  ESC::BG_BLUE    { "\033C3" }; ///< Select blue color for background.
          SLiteral<3>  ESC::BG_MAGENTA { "\033C4" }; ///< Select blue color for background.
          SLiteral<3>  ESC::BG_CYAN    { "\033C5" }; ///< Select blue color for background.
          SLiteral<3>  ESC::BG_BLACK   { "\033C6" }; ///< Select red color for background.
          SLiteral<3>  ESC::BG_WHITE   { "\033C7" }; ///< Select blue color for background.
          SLiteral<3>  ESC::BG_GRAY    { "\033C8" }; ///< Select gray color for background.
          SLiteral<3>  ESC::BG_RESET   { "\033C9" }; ///< Select std color for background.

          SLiteral<3>  ESC::BOLD       { "\033sB" }; ///< Select bold font style.
          SLiteral<3>  ESC::ITALICS    { "\033sI" }; ///< Select italics font style.
          SLiteral<3>  ESC::STYLE_RESET{ "\033sr" }; ///< Select standard font style.
          SLiteral<3>  ESC::RESET      { "\033sa" }; ///< Reset color and style.

          SLiteral<3>  ESC::URL_START  { "\033lS" }; ///< Mark the start of an URL.
          SLiteral<3>  ESC::URL_END    { "\033lE" }; ///< Mark the end of an URL.
          SLiteral<3>  ESC::TAB        { "\033t0" }; ///< Go to next tab. Usually, text loggers will increase the tab position automatically.

          SLiteral<3>  ESC::EOMETA     { "\033A0" }; ///< End of meta information in log string

#else
constexpr SLiteral<3>  ESC::RED          ;
constexpr SLiteral<3>  ESC::GREEN        ;
constexpr SLiteral<3>  ESC::YELLOW       ;
constexpr SLiteral<3>  ESC::BLUE         ;
constexpr SLiteral<3>  ESC::MAGENTA      ;
constexpr SLiteral<3>  ESC::CYAN         ;
constexpr SLiteral<3>  ESC::BLACK        ;
constexpr SLiteral<3>  ESC::WHITE        ;
constexpr SLiteral<3>  ESC::GRAY         ;
constexpr SLiteral<3>  ESC::FG_RESET     ;

constexpr SLiteral<3>  ESC::BG_RED       ;
constexpr SLiteral<3>  ESC::BG_GREEN     ;
constexpr SLiteral<3>  ESC::BG_YELLOW    ;
constexpr SLiteral<3>  ESC::BG_BLUE      ;
constexpr SLiteral<3>  ESC::BG_MAGENTA   ;
constexpr SLiteral<3>  ESC::BG_CYAN      ;
constexpr SLiteral<3>  ESC::BG_BLACK     ;
constexpr SLiteral<3>  ESC::BG_WHITE     ;
constexpr SLiteral<3>  ESC::BG_GRAY      ;
constexpr SLiteral<3>  ESC::BG_RESET     ;

constexpr SLiteral<3>  ESC::BOLD         ;
constexpr SLiteral<3>  ESC::ITALICS      ;
constexpr SLiteral<3>  ESC::STYLE_RESET  ;
constexpr SLiteral<3>  ESC::RESET        ;

constexpr SLiteral<3>  ESC::URL_START    ;
constexpr SLiteral<3>  ESC::URL_END      ;
constexpr SLiteral<3>  ESC::TAB          ;

constexpr SLiteral<3>  ESC::EOMETA       ;
#endif

void ESC::ReplaceToReadable( AString& target, integer startIdx )
{
    while( (startIdx= target.IndexOf( '\033', startIdx ) ) >= 0 )
    {
        String32 val("{ESC::");
        char c=  target.CharAt( startIdx + 1 );
        char c2= target.CharAt( startIdx + 2 );

        const char* code= "ERROR";

        // colors
        if( c == 'c' || c == 'C' )
        {
            if ( c == 'C' )
                val._<false>( "BG_" );
            switch( c2 - '0' )
            {
                case 0:  code= "RED"     ; break;
                case 1:  code= "GREEN"   ; break;
                case 2:  code= "YELLOW"  ; break;
                case 3:  code= "BLUE"    ; break;
                case 4:  code= "MAGENTA" ; break;
                case 5:  code= "CYAN"    ; break;
                case 6:  code= "BLACK"   ; break;
                case 7:  code= "WHITE"   ; break;
                case 8:  code= "GRAY"    ; break;
                case 9:  code= "RESET"   ; break;
                default: code= "COL_ERR"; break;
            }

        }

        // styles
        else if( c == 's' )
        {
            switch( c2 )
            {
                case 'B': code= "BOLD"         ; break;
                case 'I': code= "ITALICS"      ; break;
                case 'r': code= "STYLE_RESET"  ; break;
                case 'a': code= "RESET"        ; break;
                default:  code= "STYLE_ERR"    ; break;
            }
        }

        // styles
        else if( c == 'l' )
        {
            switch( c2 )
            {
                case 'S': code= "URL_START"    ; break;
                case 'E': code= "URL_END"      ; break;
                default:  code= "URL_ERR"      ; break;
            }
        }

        // others
        else if( c == 't' && c2 == '0' )    code= "TAB";
        else if( c == 'A' && c2 == '0' )    code= "EOMETA";

        // Replace
        val._<false>(code)._('}');
        target.ReplaceSubstring( val, startIdx, 3 );
        startIdx+= 3;
    }
}

}} //namespace aworx::lox
