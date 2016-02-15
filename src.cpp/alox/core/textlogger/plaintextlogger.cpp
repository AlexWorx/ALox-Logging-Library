// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#if !defined (HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif
#if !defined (HPP_ALIB_SYSTEM_DIRECTORY)
    #include "alib/system/directory.hpp"
#endif


#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

#include "alox/core/textlogger/plaintextlogger.hpp"
#include "alib/core/util.hpp"


using namespace std;
using namespace aworx;
using namespace aworx::lox::core;
using namespace aworx::lox::core::textlogger;

// For code compatibility with ALox Java/C++
#define _NC _<false>

void PlainTextLogger::doTextLog( const TString&           ,   Log::Level  ,
                                       AString&        msg,   int         ,
                                       CallerInfo*        ,   int           )
{
    if ( !notifyLogOp( Phase::Begin ) )
        return;

    // loop over message, print the parts between the escape sequences
    int         msgLength=  msg.Length();
    int         start=      0;
    int         end;
    int         column=     0;
    while( start < msgLength )
    {
        bool foundESC=  true;
        end=    msg.IndexOf<false>( '\x1B', start );
        if( end < 0 )
        {
            foundESC= false;
            end=      msgLength ;
        }

        int logWidth= doLogSubstring( msg,  start, end - start );
        if ( logWidth < 0 )
            return;
        column+= logWidth;

        // interpret escape sequence
        if ( foundESC )
        {
            char c= msg[++end];

            // auto tab or end of meta info part
            if ( c == 't' || c == 'A')
            {
                end++;
                c=  msg[end++];
                int extraSpace=  c >= '0' && c <= '9' ? (int)  ( c - '0' )
                                                      : (int)  ( c - 'A' ) + 10;

                int tabStop= AutoSizes.Next( column, extraSpace );

                if ( tabStop > column )
                {
                    const AString& spaces= lib::Util::GetSpaces();
                    int spacesLength= spaces.Length();
                    int qty= tabStop - column;
                    while ( qty > 0 )
                    {
                        int size= qty < spacesLength ? qty : spacesLength;
                        if( doLogSubstring( spaces, 0, size ) < 0 )
                            return;
                        qty-= size;
                    }
                    column= tabStop;
                }
            }

            // prune or ignore all others
            else
            {
                if ( !PruneESCSequences )
                    if( doLogSubstring( msg, end - 1, 3 ) < 0)
                        return;
                end+= 2;
            }
        }

        // next
        start= end;

    } // write loop

    ALIB_ASSERT_WARNING( start == msgLength, "Loop error when pruning ESC codes" );
    notifyLogOp( Phase::End );
}


