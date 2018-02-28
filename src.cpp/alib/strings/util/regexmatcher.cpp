// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if ALIB_FEAT_BOOST_REGEX

#if !defined (HPP_ALIB_STRINGS_UTIL_REGEXMATCHER)
    #include "alib/strings/util/regexmatcher.hpp"
#endif

#include <boost/regex.hpp>
#include <string>


namespace aworx { namespace lib { namespace strings { namespace util  {



RegexMatcher::~RegexMatcher()
{
    if( boostRegex )
        delete reinterpret_cast<boost::regex*>( boostRegex );
}

void RegexMatcher::Compile( const String& pattern )
{
    if( pattern.IsNull() )
        return;

    boost::regex* regEx;
    if( !boostRegex )
        boostRegex= (regEx= new  boost::regex() );
    else
        regEx= reinterpret_cast<boost::regex*>( boostRegex );

    regEx->assign( std::string(pattern.Buffer(), static_cast<size_t>( pattern.Length() ) ) );
}

bool RegexMatcher::Match( const String& haystack )
{
    if( !boostRegex )
        return true;

    return boost::regex_match(std::string(haystack.Buffer(), static_cast<size_t>( haystack.Length() )),
                              *reinterpret_cast<boost::regex*>( boostRegex )      );

}

}}}} // namespace [aworx::lib::strings::util]

#endif
