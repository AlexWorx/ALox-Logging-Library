// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif


using namespace aworx;
using namespace aworx::lox;

// #################################################################################################
// ESC codes
// #################################################################################################
#if defined(_MSC_VER)
// MSC  (as of 12/2015):
// C4579: in-class initialization for type 'const aworx::StringLiteral<10>'
// is not yet implemented; static member will remain uninitialized at runtime but
// use in constant-expressions is supported
          StringLiteral<3>  ESC::RED        { "\033c0" }; ///< Select red color for foreground.
          StringLiteral<3>  ESC::GREEN      { "\033c1" }; ///< Select green color for foreground.
          StringLiteral<3>  ESC::YELLOW     { "\033c2" }; ///< Select yellow color for foreground.
          StringLiteral<3>  ESC::BLUE       { "\033c3" }; ///< Select blue color for foreground.
          StringLiteral<3>  ESC::MAGENTA    { "\033c4" }; ///< Select magenta color for foreground.
          StringLiteral<3>  ESC::CYAN       { "\033c5" }; ///< Select cyan color for foreground.
          StringLiteral<3>  ESC::BLACK      { "\033c6" }; ///< Select black color for foreground.
          StringLiteral<3>  ESC::WHITE      { "\033c7" }; ///< Select white color for foreground.
          StringLiteral<3>  ESC::GRAY       { "\033c8" }; ///< Select gray color for foreground.
          StringLiteral<3>  ESC::FG_RESET   { "\033c9" }; ///< Select std color for foreground.

          StringLiteral<3>  ESC::BG_RED     { "\033C0" }; ///< Select red color for background.
          StringLiteral<3>  ESC::BG_GREEN   { "\033C1" }; ///< Select green color for background.
          StringLiteral<3>  ESC::BG_YELLOW  { "\033C2" }; ///< Select yellow color for background.
          StringLiteral<3>  ESC::BG_BLUE    { "\033C3" }; ///< Select blue color for background.
          StringLiteral<3>  ESC::BG_MAGENTA { "\033C4" }; ///< Select blue color for background.
          StringLiteral<3>  ESC::BG_CYAN    { "\033C5" }; ///< Select blue color for background.
          StringLiteral<3>  ESC::BG_BLACK   { "\033C6" }; ///< Select red color for background.
          StringLiteral<3>  ESC::BG_WHITE   { "\033C7" }; ///< Select blue color for background.
          StringLiteral<3>  ESC::BG_GRAY    { "\033C8" }; ///< Select gray color for background.
          StringLiteral<3>  ESC::BG_RESET   { "\033C9" }; ///< Select std color for background.

          StringLiteral<3>  ESC::BOLD       { "\033sB" }; ///< Select bold font style.
          StringLiteral<3>  ESC::ITALICS    { "\033sI" }; ///< Select italics font style.
          StringLiteral<3>  ESC::STYLE_RESET{ "\033sr" }; ///< Select standard font style.
          StringLiteral<3>  ESC::RESET      { "\033sa" }; ///< Reset color and style.

          StringLiteral<3>  ESC::URL_START  { "\033lS" }; ///< Mark the start of an URL.
          StringLiteral<3>  ESC::URL_END    { "\033lE" }; ///< Mark the end of an URL.
          StringLiteral<3>  ESC::TAB        { "\033t0" }; ///< Go to next tab. Usually, text loggers will increase the tab position automatically.

          StringLiteral<3>  ESC::EOMETA     { "\033A0" }; ///< End of meta information in log string

#else
constexpr StringLiteral<3>  ESC::RED          ;
constexpr StringLiteral<3>  ESC::GREEN        ;
constexpr StringLiteral<3>  ESC::YELLOW       ;
constexpr StringLiteral<3>  ESC::BLUE         ;
constexpr StringLiteral<3>  ESC::MAGENTA      ;
constexpr StringLiteral<3>  ESC::CYAN         ;
constexpr StringLiteral<3>  ESC::BLACK        ;
constexpr StringLiteral<3>  ESC::WHITE        ;
constexpr StringLiteral<3>  ESC::GRAY         ;
constexpr StringLiteral<3>  ESC::FG_RESET     ;

constexpr StringLiteral<3>  ESC::BG_RED       ;
constexpr StringLiteral<3>  ESC::BG_GREEN     ;
constexpr StringLiteral<3>  ESC::BG_YELLOW    ;
constexpr StringLiteral<3>  ESC::BG_BLUE      ;
constexpr StringLiteral<3>  ESC::BG_MAGENTA   ;
constexpr StringLiteral<3>  ESC::BG_CYAN      ;
constexpr StringLiteral<3>  ESC::BG_BLACK     ;
constexpr StringLiteral<3>  ESC::BG_WHITE     ;
constexpr StringLiteral<3>  ESC::BG_GRAY      ;
constexpr StringLiteral<3>  ESC::BG_RESET     ;

constexpr StringLiteral<3>  ESC::BOLD         ;
constexpr StringLiteral<3>  ESC::ITALICS      ;
constexpr StringLiteral<3>  ESC::STYLE_RESET  ;
constexpr StringLiteral<3>  ESC::RESET        ;

constexpr StringLiteral<3>  ESC::URL_START    ;
constexpr StringLiteral<3>  ESC::URL_END      ;
constexpr StringLiteral<3>  ESC::TAB          ;

constexpr StringLiteral<3>  ESC::EOMETA       ;
#endif
