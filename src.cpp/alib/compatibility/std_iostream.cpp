// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"

#include "alib/compatibility/std_iostream.hpp"


using namespace std;

namespace aworx {
namespace           lib {
namespace                   strings {


// #################################################################################################
// Tab()
// #################################################################################################

template<>  int ApplyTo( AString& target, const ReadLineFromIStream& cparam)
{
    // we are required to write to the param object. So we cast to non-const. This is OK, as
    // the const specifier came through TMP.
    ReadLineFromIStream& param= (ReadLineFromIStream&) cparam;

    if ( param.TargetData == CurrentData::Clear )
        target.Clear();
    int origLength= target.Length();

    // read loop
    while( !param.istream.eof() )
    {
        // calc buffer size (if we hit the overall line width)
        // and check if we reached the limit per line
        int actReadSize= min( param.BufferSize,  param.MaxLineWidth - ( target.Length() - origLength) + 1  );
        if ( actReadSize < 2 )
            return target.Length() - origLength;

        target.EnsureRemainingCapacity( actReadSize );

        // read
        int start= target.Length();
        param.istream.getline( target.VBuffer() + start, actReadSize );
        int gCount= (int) param.istream.gcount();
        int count= (int) strlen( target.Buffer() + start );

        bool lineComplete=  count + 1 == gCount;

        // something read?
        if ( count > 0 )
        {
            // be sure to not have a carriage return at the start
            if( *(target.Buffer() + start) == '\r' )
            {
                target.Delete<false>( start, 1 );
                count--;
            }

            // be sure to not have a carriage return at the end
            start+= count;
            if( *(target.Buffer() + start -1 ) == '\r' )
                start--;

            target.SetLength<false>( start );

            // if we are at the end of the file (without delimiter) we stop now
            if ( param.istream.eof() )
            {
                param.IsEOF= true;
                return target.Length() - origLength;
            }
        }


        // delim read
        if ( lineComplete )
        {
            ALIB_STRING_DBG_UNTERMINATE(target, 0)
            return target.Length() - origLength;
        }

        // buffer was not big enough
        if ( gCount == actReadSize -1)
        {
            if ( param.istream.eof() )
            {
                ALIB_STRING_DBG_UNTERMINATE(target, 0)
                return true;
            }

            // otherwise, it should really have been the buffer size, so let's clear the bit
            // and continue with more buffer space
            ALIB_ASSERT( param.istream.rdstate() == iostream::failbit )
            param.istream.clear();
            continue;
        }

        // the eof just happend now
        if ( param.istream.eof() )
            break;

        if ( param.istream.rdstate() == iostream::failbit )
        {
            ALIB_ERROR( "Unknown Error Reading File. Maybe method implemented incomplete?" );
            break;
        }

        // anything else to add here? I guess not! But you never know with this strange
        // iostream clases!

        //...

        // This happens if \0 is in the file
        ALIB_ERROR( "Unknown Error Reading File. Probably not a text file." );
        break;
    }

    ALIB_STRING_DBG_UNTERMINATE(target, 0)
    param.IsEOF= true;
    return target.Length() - origLength;
}


}}}// namespace aworx::lib::strings
