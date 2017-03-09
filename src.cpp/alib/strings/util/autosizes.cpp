// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALIB_STRINGS_SUBSTRING)
    #include "alib/strings/substring.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_UTIL_AUTOSIZES)
    #include "alib/strings/util/autosizes.hpp"
#endif


namespace aworx { namespace lib { namespace strings { namespace util  {

int   AutoSizes::Next( integer requestedSize, integer growthPadding )
{
    // grow arrays as needed
    if ( values.size() == static_cast<size_t>(ActualIndex) )
    {
        values          .emplace_back( 0 );
        sessionValues   .emplace_back( 0 );
    }

    // get size as it would be for this session (for saving the session later)
    integer size=    sessionValues[ static_cast<size_t>(ActualIndex) ];
    if ( size <  requestedSize )
        sessionValues[ static_cast<size_t>(ActualIndex) ]=  requestedSize + ( size == 0 ? 0 : growthPadding );


    // get size as it is for actual values (the ones that might have been imported)
    size=    values[ static_cast<size_t>(ActualIndex) ];
    if ( size <  requestedSize )
    {
        size=
        values[ static_cast<size_t>(ActualIndex) ]=         requestedSize + ( size == 0 ? 0 : growthPadding );
    }

    // increase auto tab index
    ActualIndex++;

    return static_cast<int>(size);
}

void    AutoSizes::Export( AString& target  )
{
    for( size_t i= 0; i < values.size() ; i++ )
    {
        if ( i != 0 )
            target._( ' ' );
        target._(        values[ i ] );
        target._( ' ' );
        target._( sessionValues[ i ] );
    }
    while( target.EndsWith(" 0 0" ) )
        target.DeleteEnd<false>(4);
}

void    AutoSizes::Import( const String& sourceString, CurrentData session  )
{
    Substring source(sourceString);
    Reset();
    for(;;)
    {
        integer origLength=     source.Length();
        int   value;          source.ConsumeInt( value       );
        int   sessionValue;   source.ConsumeInt( sessionValue );

        if ( origLength == source.Length() )
            break;

        values       .emplace_back( session == CurrentData::Clear ? sessionValue : value       );
        sessionValues.emplace_back( session == CurrentData::Clear ? 0            : sessionValue );
    }
}


}}}} // namespace [aworx::lib::strings::util]
