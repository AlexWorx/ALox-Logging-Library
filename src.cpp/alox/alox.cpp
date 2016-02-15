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
          SLiteral<3>  ESC::FG_RESET   { "\033c9" }; ///< Select std color for foreground.

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

}} //namespace aworx::lox