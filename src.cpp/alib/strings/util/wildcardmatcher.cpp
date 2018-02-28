// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"


#if !defined (HPP_ALIB_STRINGS_UTIL_WILDCARDMATCHER)
    #include "alib/strings/util/wildcardmatcher.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_SUBSTRING)
    #include "alib/strings/substring.hpp"
#endif

namespace aworx { namespace lib { namespace strings { namespace util  {

#define    STRING    -1
#define    ASTERISK  -2

void WildcardMatcher::Compile( const String& pattern )
{
    // Note: The following invariants will be true in the command vector:
    //       - A String-entry will be a non-empty string
    //       - No two * follow each other"
    //       - A ? will not follow an asterisk (combinations of ? and ' will be sorted to "?(n) *"

    commands.clear();

    Substring parser= pattern;
    while(parser.IsNotEmpty())
    {
        // *
        if(parser.CharAtStart() == '*' )
        {
            // add if empty or last is not * already.
             if(   commands.size() == 0
                || commands.back().first != ASTERISK ) commands.emplace_back( ASTERISK, nullptr  );

            parser.ConsumeChar();
            continue;
        }

        // ?
        int qtyQ= 0;
        while( parser.ConsumeChar('?') )
            qtyQ++;

        if( qtyQ )
        {
            // previous is "*" ?
            if(     commands.size() > 1
                    &&  (commands.end()-1)->first == ASTERISK )
            {

                // before * we already have Q? -> add to the Q
                if(     commands.size() >= 2
                        &&  (commands.end()-2)->first > 0 )
                {
                    (commands.end()-2)->first+= qtyQ;
                    continue;
                }

                commands.emplace( commands.end() - 1, qtyQ, nullptr );
                continue;
            }

            // Just add it
            commands.emplace_back( qtyQ, nullptr );
            continue;
        }

        // strings
        integer idx= 1;
        while ( idx < parser.Length() && parser[idx] != '*' && parser[idx] != '?'  )
            idx++;

        commands.emplace_back( STRING, String(parser.Buffer(), idx ) );
        parser.ConsumeChars( idx );
        continue;
    }

}

bool WildcardMatcher::Match( const String& pHaystack, Case sensitivity )
{
    if( commands.size() == 0 )
        return true;

    if( pHaystack.IsNull() )
        return false;

    Substring haystack= pHaystack;
    size_t  actCmd = 0;
    size_t  lastCmd= static_cast<size_t>( commands.size() - 1 );
    bool    lastWasAsterisk= false;

    for( actCmd= 0; actCmd <= lastCmd ; ++actCmd )
    {
        auto& cmd= commands[actCmd];

        // ?
        if( cmd.first > 0 )
        {
            if ( haystack.Length() < cmd.first )
                return false;
            haystack.ConsumeChars<false>( cmd.first );
            continue;
        }

        // *
        if( cmd.first == ASTERISK )
        {
            if ( actCmd == lastCmd )
                return true;

            lastWasAsterisk= true;
            continue;
        }

        // string
        if( cmd.second.Length() > haystack.Length() )
            return false;

        if( lastWasAsterisk )
        {
            integer idx= sensitivity==Case::Sensitive  ?  haystack.IndexOfSubstring<Case::Sensitive, false>( cmd.second )
                                                       :  haystack.IndexOfSubstring<Case::Ignore   , false>( cmd.second );
            if( idx < 0 )
                return false;
            haystack.ConsumeChars( idx + cmd.second.Length() );
            lastWasAsterisk= false;
            continue;
        }

        if( sensitivity==Case::Sensitive ? (!haystack.StartsWith<Case::Sensitive,false>( cmd.second ) )
                                         : (!haystack.StartsWith<Case::Ignore   ,false>( cmd.second ) )  )
            return false;

        haystack.ConsumeChars<false>( cmd.second.Length() );
    }

    return haystack.IsEmpty() || lastWasAsterisk;
}

#undef   STRING
#undef   ASTERISK
}}}} // namespace [aworx::lib::strings::util]
