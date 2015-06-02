// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"

#include "awxu.hpp"

#if !defined (HPP_AWORX_UTIL_ASTRING)
    #include "astring.hpp"
#endif

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif
#if !defined (_MATH_H) && !defined(_INC_MATH)
    #include <math.h>
#endif
#if !defined (_STRING_H) && !defined(_INC_STRING)
    #include <string.h>
#endif

using namespace std;


#define        stdMAXINT    std::numeric_limits<int>::max()

// ####################################################################################################
// ASTRING_DEBUG
// ####################################################################################################
#if defined(AWXU_DEBUG_ASTRING)
    bool _astringCheckReported= false;

//AWXU_ASSERT

    #define AString_CHECK                                                      \
    {                                                                          \
        if ( !_astringCheckReported && AWXU::AcquireErrorHandler() )           \
        {                                                                      \
            _astringCheckReported= true;                                       \
            AWXU::DebugMsg( "ATTN: AWXU_DEBUG_ASTRING is ON! To switch off, "  \
                            "unset AWXU_DEBUG_ASTRING_ON at compile time." );  \
        }                                                                      \
        AWXU_ASSERT_MSG( buffer!=nullBuffer ||  length == 0,                   \
                         "Internal AString Error" );                           \
        AWXU_ASSERT_MSG(    length== 0                                                              \
                         || ( buffer[length] == '\0' && ((signed int) strlen(buffer)) == length )   \
                     ,   "Internal AString Error" );                                                \
    }                                                                                               \

#else
    #define AString_CHECK
#endif


namespace aworx {
namespace       util {


// ####################################################################################################
// AString implementation
// ####################################################################################################

// #################################################################################################
//  globals
// #################################################################################################

/// An empty const character array that we will bend to be our non-const buffer if we are
/// initialized to 0 size!
#if !defined( DOXYGEN_OMIT_THIS_PLEASE )
const char* nullBuffer=    "";
#endif

string AString::NEWLINE=
                        #ifdef __unix__
                            "\n";
                        #elif defined(_MSC_VER)
                            "\r\n";
                        #else
                            "\n";
                            #warning "Warning: Unknown Platform"
                        #endif


// ####################################################################################################
// local inlines
// ####################################################################################################

#if !defined( DOXYGEN_OMIT_THIS_PLEASE )
inline bool adjustRegion( int referenceLength, int& regionStart, int& regionLength )
{
    // if start exceeds string, set to empty range at the end of the string and return true
    if (regionStart >= referenceLength)
    {
        regionStart=    referenceLength;
        regionLength=    0;
        return true; // indicate empty
    }

    // if negative start, cut it from the length
    if (regionStart < 0 )
    {
        regionLength+=    regionStart; // this adds a negative value, hence we do not exceed a given MAXINT
        regionStart=    0;
    }

    // adjust length
    int maxLen=  referenceLength - regionStart;
    if ( regionLength > maxLen )
         regionLength=  maxLen;
    if ( regionLength < 0 )
        regionLength= 0;

    // return true if adjusted region is empty
    return  regionLength == 0;
}
#endif



// #################################################################################################
//  Constructors / destructor
// #################################################################################################
AWXU_API
AString::AString()
{
    buffer= (char*) nullBuffer;
}


AString::AString( int size )
{
    buffer= (char*) nullBuffer;
    if ( size > 0 )
        EnsureAllocation( size );
}

void AString::construct( const char* src, int srcLength, int regionStart, int regionLength )
{
    buffer= (char*) nullBuffer;
    AWXU_ASSERT( src != nullptr || srcLength == 0 );

    if ( src == nullptr )
        return;

    if ( srcLength == 0 || adjustRegion( srcLength, regionStart, regionLength ) )
    {
        EnsureAllocation( 15 );
        return;
    }

    // copy the source (this is not calling Append, to avoid double region check)
    EnsureAllocationRelative( regionLength );
    memcpy( buffer, src + regionStart, regionLength  );
    buffer[length+= regionLength]= '\0';
}


AString::~AString()
{
    AString_CHECK
    if ( allocSize > 0 )
        delete[] buffer;
}

// ####################################################################################################
// Buffer, length and allocation
// ####################################################################################################

#if !defined( DOXYGEN_OMIT_THIS_PLEASE )
AWXU_ONE_TIME_WARNING_DEF(AString,SetLength);
#endif

int    AString::SetLength( int newLength )
{
    AWXU_ONE_TIME_WARNING( newLength > length, "AString::SetLength(): increase requested", SetLength )

    if ( newLength < length )
        buffer[length= newLength]= '\0';

    return length;
}

#if !defined( DOXYGEN_OMIT_THIS_PLEASE )
AWXU_ONE_TIME_WARNING_DEF(AString,ReplaceExternalBuffer);
#endif

void AString::SetAllocation( int newSize )
{
    // default parameter -1: -> set to current length
    if ( newSize == -1 )
        newSize= length;

    // check
    if ( allocSize >0 && allocSize == newSize )
        return;

    // set uninitialized
    if ( newSize == 0 )
    {
        if ( allocSize > 0 )
            delete[] buffer;

        buffer= (char*) nullBuffer;
        allocSize=
        length=     0;

        return;
    }

    AWXU_ONE_TIME_WARNING( allocSize < 0, "AString::SetAllocation(): replacing an external buffer. This may not be wanted.", ReplaceExternalBuffer )

    // create new Buffer
    char* newBuffer=    new char[ newSize  + 1 ];

    // if we had a buffer before
    if ( buffer!= nullBuffer)
    {
        // copy data and delete old buffer
        memcpy( newBuffer, buffer, min( length + 1, newSize + 1) );
        if ( allocSize > 0 )
            delete[] buffer;
    }
    else
    {
        AWXU_ASSERT( length == 0 );
        newBuffer[0]= '\0';
    }

    // set new Buffer and adjust length
    buffer=     newBuffer;
    allocSize=  newSize;
    if ( length > allocSize )
        buffer[ length= allocSize ]= '\0';
}

void AString::SetExternalBuffer( char* buffer, int allocSize, int length, bool deleteOnResize )
{
    AWXU_ASSERT_MSG(        !(allocSize == 0 && buffer != nullptr)
                      &&    !(allocSize != 0 && buffer == nullptr) , "AString::SetExternalBuffer(): Given buffer is nullptr while given alloc size is not 0 (or vice versa)" );

    AWXU_ASSERT_MSG( allocSize > length,                 "AString::SetExternalBuffer(): length >= allocation size" );

    // delete any existing
    if ( this->allocSize > 0 )
        delete[] buffer;

    // clear?
    if ( buffer == nullptr )
    {
        this->buffer=       nullptr;
        this->allocSize=
        this->length=       0;
        return;
    }

    // save given buffer
    this->buffer=       buffer;
    allocSize--;        // we count one less
    this->allocSize=   deleteOnResize ? allocSize : -allocSize;
    this->length=       length;
    buffer[length]=     '\0';
}


AString& AString::Clear()
{
    AString_CHECK

    tabReference=
    fieldReference=
    length=            0;
    if( buffer != nullBuffer )
        buffer[length]=    '\0';

    // return me for concatenated operations
    return *this;
}

AString& AString::Delete( int regionStart, int regionLength )
{
    AString_CHECK

    // adjust range, if empty do nothing
    if ( adjustRegion( length, regionStart, regionLength ) )
        return *this;

    int regionEnd= regionStart + regionLength;

    // case: region reaches to the end?
    if ( regionEnd == length )
    {
        if ( tabReference > regionStart )
            tabReference= regionStart;

        buffer[length=    regionStart]= '\0';
        return *this;
    }

    // case: region does not include this strings' end
    if ( tabReference > regionStart  && tabReference < regionEnd )
        tabReference= regionStart;

    memmove( buffer + regionStart,
             buffer + regionEnd,
             length - regionEnd + 1);
    length-= regionLength;

    // return me for concatenated operations
    return *this;
}

AString& AString::Insert( int regionStart, int regionLength, char fillChar )
{
    AString_CHECK

    // check
    if ( regionStart < 0 || regionStart > length || regionLength <= 0 )
        return *this;

    EnsureAllocationRelative( regionLength );

    // adjust tab reference if behind us
    if ( tabReference > regionStart )
        tabReference+= regionLength;

    // move content and fill new region
    memmove( buffer + regionStart + regionLength,
             buffer + regionStart,
             length - regionStart + 1);
    memset ( buffer + regionStart, fillChar, regionLength );
    length+= regionLength;

    // return me for concatenated operations
    return *this;
}

AString& AString::Fill( char c, int regionStart, int regionLength )
{
    // empty region?
    if ( adjustRegion( length, regionStart, regionLength ) )
    {
        // special treatment if currently nothing is allocated
        // we allocate, which means, we are not a null object anymore!
        if ( allocSize == 0 )
        {
            AWXU_ASSERT( length == 0 )
            EnsureAllocation( 15 );
        }
        return *this;
    }

    // set region
    memset ( buffer + regionStart, c, regionLength );
    return *this;
}

AString& AString::NewLine()
{
    AString_CHECK

    tabReference= length + NEWLINE.size();
    return Append( NEWLINE );
}


AString& AString::Tab( int tabSize, int minPad, char tabChar )
{
    AString_CHECK
    int qtyChars= minPad > 0 ? minPad : 0;
    if ( tabSize > 1 )
        qtyChars+= (tabSize - ( (length + qtyChars - tabReference) % tabSize ) ) % tabSize;

    if ( qtyChars <= 0 )    return * this;
    if ( qtyChars == 1 )    return Append ( tabChar );
                            return Append ( tabChar, qtyChars );
}


// #################################################################################################
// Append() - strings
// #################################################################################################

AString& AString::Append( int srcLength, const char* src )
{
    AString_CHECK

    // check parameter
    if ( src == nullptr )
        return *this;
    if ( srcLength == -1 )
        srcLength= strlen( src );
    if ( srcLength == 0 )
    {
        // special treatment if currently nothing is allocated and a blank string ("") is added:
        // we allocate, which means, we are not a null object anymore!
        if ( allocSize == 0 )
        {
            AWXU_ASSERT( length == 0 )
            EnsureAllocation( 15 );
        }
        return *this;
    }

    // check capacity
    EnsureAllocationRelative( srcLength );

    // copy and adjust my length
    memcpy  ( buffer + length,  src, srcLength  );
    length+= srcLength;
    buffer[length]= '\0';

    // return me for concatenated operations
    return *this;
}

AString& AString::Append( int srcLength, const char* src,  int regionStart, int regionLength )
{
    AString_CHECK
    // check null argument
    if ( src == nullptr )
        return *this;

    if ( srcLength == -1 )
        srcLength= strlen( src );

    // adjust range, if empty do nothing
    if ( adjustRegion( srcLength, regionStart, regionLength ) )
        return *this;

    // check capacity
    EnsureAllocationRelative( regionLength );

    // copy and adjust my length
    memcpy  ( buffer + length, src + regionStart, regionLength  );
    length+= regionLength;
    buffer[length]= '\0';

    // return me for concatenated operations
    return *this;
}


AString& AString::Append( char c )
{
    AString_CHECK
    EnsureAllocationRelative( 1 );
    buffer[ length++ ]= c;
    buffer[length]= '\0';

    // return me for concatenated operations
    return *this;
}

AString& AString::Append( char c, int qty )
{
    AString_CHECK
    EnsureAllocationRelative( qty );

    memset ( buffer + length, c, qty );
    length+= qty;

    buffer[length]= '\0';

    // return me for concatenated operations
    return *this;
}


// #################################################################################################
// Append(int)/(double)
// #################################################################################################

#if !defined( DOXYGEN_OMIT_THIS_PLEASE )
char* int64ToString( char* buffer, uint_fast64_t i, int minDigits, int maxDigitsInValueHint )
{
    // main loop
    int             actDigit=       max( minDigits, maxDigitsInValueHint );
    uint_fast64_t   actBase=        1;
    for ( int ii= actDigit -1 ; ii !=0 ; ii-- )
        actBase*= 10;

    actDigit++; // +1 for the loop
    bool isUnder= false;
    while ( --actDigit > 0)
    {
        // get next d
        uint_fast64_t d=         i / actBase;
        uint_fast64_t actBase2=  actBase;
        actBase/=     10;

        // did we hit i for the first time
        isUnder|= (d != 0);

        // don't print?
        if (!isUnder && actDigit > minDigits )
            continue;

        // print the digit
        *buffer++= (char) ( 48 + d ); // 48= '0'

        // next
        i=    i % actBase2;
    }

    return buffer;
}
#endif

AString& AString::Append( int32_t i, int minDigits )
{
    AString_CHECK


    // at least one digit!
    if ( minDigits < 1 )
        minDigits= 1;

    uint_fast64_t    ui;
    if ( i < 0 )
    {
        EnsureAllocationRelative( 1 ); // 10 + minus sign
        buffer[length++] = '-';
        ui=    (uint_fast64_t) - ( (int_fast64_t) i );
    }
    else
        ui=    (uint_fast64_t) i;

    // do some first optimization on the size of i
    int sizeHint= 10; // Max/min Value: +/-2147483648
         if ( ui <    100 )   sizeHint= 2;
    else if ( ui < 100000 )   sizeHint= 5;

    EnsureAllocationRelative( max( minDigits, sizeHint ) );
    char* newEnd= int64ToString( buffer + length,  ui, minDigits, sizeHint );
    *newEnd= '\0';
    length= newEnd - buffer;

    return *this;
}

AString& AString::Append( uint32_t i, int minDigits )
{
    AString_CHECK

    // at least one digit!
    if ( minDigits < 1 )
        minDigits= 1;

    uint_fast64_t    ui= i;

    // do some first optimization on the size of i
    int sizeHint= 10; // Max/min Value: 4294967295
         if ( ui <    100 )   sizeHint= 2;
    else if ( ui < 100000 )   sizeHint= 5;

    EnsureAllocationRelative( max( minDigits, sizeHint ) );
    char* newEnd= int64ToString( buffer + length,  ui, minDigits, sizeHint );
    *newEnd= '\0';
    length= newEnd - buffer;
    return *this;
}

AString& AString::Append( int64_t i, int minDigits )
{
    AString_CHECK

    // at least one digit!
    if ( minDigits < 1 )
        minDigits= 1;

    uint_fast64_t    ui;
    if ( i < 0 )
    {
        EnsureAllocationRelative( 1 ); // 10 + minus sign
        buffer[length++] = '-';
        ui=  -i;
    }
    else
        ui=  i;

    // do some first optimization on the size of i
    int sizeHint= 19; // Max/min Value: +/-9223372036854775808
         if ( ui <        1000 )   sizeHint=  3;
    else if ( ui <     1000000 )   sizeHint=  6;
    else if ( ui < 10000000000 )   sizeHint= 10;

    EnsureAllocationRelative( max( minDigits, sizeHint ) );
    char* newEnd= int64ToString( buffer + length,  ui, minDigits, sizeHint );
    *newEnd= '\0';
    length= newEnd - buffer;

    return *this;
}

AString& AString::Append( uint64_t i, int minDigits )
{
    AString_CHECK

    // at least one digit!
    if ( minDigits < 1 )
        minDigits= 1;

    uint_fast64_t    ui= i;

    // do some first optimization on the size of i
    int sizeHint= 20; // Max/min Value: 18446744073709551615
         if ( ui <        1000)    sizeHint=  3;
    else if ( ui <     1000000 )   sizeHint=  6;
    else if ( ui < 10000000000 )   sizeHint= 10;

    EnsureAllocationRelative( max( minDigits, sizeHint ) );
    char* newEnd= int64ToString( buffer + length,  ui, minDigits, sizeHint );
    *newEnd= '\0';
    length= newEnd - buffer;
    return *this;
}



AString& AString::Append( double d, int minDigitsBeforeDot, int digitsAfterDot )
{
    AString_CHECK
    // negative? -> turn positive
    if ( d < 0.0 )
    {
        Append( '-' );
        d= -d;
    }

    // append integer part plus dot
    int beforeDot= (int) d;

    // subtract integer part
    d-= beforeDot;

    // multiply by 10^digits, and get overflow value
    int i= digitsAfterDot;
    int overflow= 1;
    while ( i-- > 0)
    {
        d*=         10;
        overflow*=     10;
    }

    // round the multiplied rest and check for overflow. This check is necessary
    // for rests with 9er numbers:  sample 999.999  -> 1000.000, this is an "overflow"
    int afterDot= (int) rint( d );
    if ( afterDot == overflow )
    {
        afterDot= 0;
        beforeDot++;
    }

    // append integer part
    if ( minDigitsBeforeDot  != 0 || beforeDot != 0 )
        Append( beforeDot, minDigitsBeforeDot );

    Append( '.' );

    // check for no digits after dot wanted
    if ( digitsAfterDot > 0 )
        Append( afterDot, digitsAfterDot );

    // return me for concatenated operations
    return *this;
}

// #################################################################################################
// Field()
// #################################################################################################

AString& AString::Field( int size, Align alignment, char padChar, int fieldStart )
{
    AString_CHECK

    // if size is -1, this is just a field start marker invocation
    if ( size < 0 )
    {
        fieldReference= length;
        return *this;
    }

    // if no field start is given, use the saved one (default behaviour)
    if ( fieldStart == stdMAXINT )
        fieldStart=        fieldReference;

    // check pad size
    int padSize=    size - (length - fieldStart);
    if (padSize <= 0 )
        return *this;

    // align left
    if ( alignment == Align::LEFT )
    {
        Append( padChar, padSize );
        return *this;
    }

    // align Right
    if ( alignment == Align::RIGHT )
    {
        Insert( fieldStart, padSize, padChar );
        return *this;
    }

    // align Center
    Insert( fieldStart,    padSize >> 1,     padChar );
    Append( padChar, padSize - ( padSize >> 1 ) );
    return *this;
}

// #################################################################################################
//  CompareTo()
// #################################################################################################

int AString::CompareTo( const char*  referenceString,
                        int          referenceStringLength,
                        const char*  compareString,
                        int          compareStringLength,
                        bool         ignoreCase,
                        int          compareStringRegionStart,
                        int          compareStringRegionLength,
                        int          regionStart,
                        int          regionLength                 )
{
    // check null arguments
    if ( referenceString == nullptr)        return  compareString == nullptr ? 0 : -1;
    if ( compareString   == nullptr)        return  +1;

    // adjust source and compare regions
    adjustRegion(   compareStringLength,    compareStringRegionStart,    compareStringRegionLength );
    adjustRegion( referenceStringLength,                 regionStart,                 regionLength );

    // compare loop
    const char* src=        referenceString  +                 regionStart;
    const char* srcEnd=     referenceString  + (               regionStart     +              regionLength );
    const char* cmp=        compareString    +    compareStringRegionStart;
    const char* cmpEnd=     compareString    + (   compareStringRegionStart    + compareStringRegionLength );
    for (;;)
    {
        // end of one of the strings or both?
        if (src >= srcEnd)    return  (cmp >= cmpEnd) ?     0    :    -1;
        if (cmp >= cmpEnd)    return                                 1;

        // compare characters
        if ( *src != *cmp )
        {
            // no match!
            if ( !ignoreCase )
                return *src - *cmp;

            // compare ignore case
            int diff= ( tolower( *src  ) - tolower( *cmp ) );
            if ( diff != 0 )
                return diff;
        }

        // next
        src++; cmp++;
    }
}

bool AString::Equals( const char*   compareString,
                      bool          ignoreCase,
                      int           csLen )
const
{
    if ( compareString == nullptr )
        return allocSize == 0;
    if ( allocSize == 0 )
        return false;

    if (csLen == -1 )
        csLen= strlen( compareString );

    // do obvious pre checks
    if ( csLen != length )                    return false;
    if ( csLen == 0 )                        return true;

    // as chances should be high, we check the first character
    if ( !ignoreCase && *compareString != buffer[0] )    return false;

    return CompareTo(   this->buffer,     this->length,
                        compareString,    csLen,
                        ignoreCase,
                        1,                csLen   -1,
                        1,                length  -1           )     == 0;
}




// #################################################################################################
//  ContainsAt, StartsWith, EndsWith
// #################################################################################################

bool AString::ContainsAt( const char* needle, int pos, bool ignoreCase, int needleLen )
const
{
    AString_CHECK
    // check null argument or length 0
    if ( needleLen < 0)            needleLen= needle ? strlen( needle ) : 0;
    if ( pos < 0 || pos + needleLen > length )
        return false;
    if ( needleLen == 0 )
        return true;

    #if defined (__GLIBCXX__)
        return 0 == ( ignoreCase    ?    strncasecmp    ( buffer + pos,    needle, needleLen  )
                                    :    strncmp        ( buffer + pos,    needle, needleLen) ) ;
    #else
        return 0 == ( ignoreCase    ?    _strnicmp      ( buffer + pos,    needle, needleLen  )
                                    :     strncmp       ( buffer + pos,    needle, needleLen) ) ;
    #endif
}


// #################################################################################################
//  IndexOf()
// #################################################################################################

int AString::IndexOf( char c, int startIdx )
{
    AString_CHECK
    if( !length || startIdx >= length || startIdx < 0 )
        return -1;
    char* result=    strchr( buffer + startIdx, c );

    return result ? result - buffer
                  : -1;
}

int        AString::IndexOf( const char* haystack,  int haystackLen,
                             const char* needle,    int needleLen, int startIdx, bool ignoreCase )
{
    // checks
    if ( startIdx < 0 )                          startIdx= 0;
    if ( startIdx + needleLen > haystackLen )    return -1;
    if ( needleLen == 0  )                       return  startIdx;


    const char*    foundAt;

    #if defined (__GLIBCXX__)
        // use system 'strstr'/strcasestr
        foundAt = ignoreCase ? strcasestr( haystack + startIdx, needle )
                             : strstr    ( haystack + startIdx, needle );
    #else
        // use system 'strstr'/strcasestr
        if ( !ignoreCase )
            foundAt= strstr(haystack + startIdx, needle);
        else
        {
            char firstChar = (char) tolower(needle[0]);
            while ( startIdx < haystackLen )
            {
                int     cmpLen = 0;
                char    sc = firstChar;
                while ( tolower( haystack[startIdx + cmpLen] ) == sc)
                {
                    cmpLen++;
                    if (cmpLen == needleLen)
                        return startIdx;
                    sc = (char) tolower( needle[cmpLen] );
                }
                startIdx++;
            }
            return -1;
        }
    #endif

    // return result as index in haystack
    return    foundAt != nullptr  ?    ( foundAt - haystack )
                                  :    -1;
}

// #################################################################################################
//  Replace()
// #################################################################################################

int AString::ReplaceCount(  const char* searchStr,    int searchStringLength,
                            const char* newStr,       int newStringLength,
                            int startIdx, int maxReplacements, bool ignoreCase )
{
    AString_CHECK
    // check null arguments
    if ( !searchStr || searchStringLength <= 0 || newStringLength <0 || ( newStringLength > 0 && !newStr) )
        return 0;

    int lenDiff=            newStringLength - searchStringLength;

    // replacement loop
    int cntReplacements=    0;
    int idx= -1;
    while ( cntReplacements < maxReplacements && idx < length)
    {
        // search  next occurrence
        if ( ( idx= IndexOf( buffer, length, searchStr, searchStringLength, startIdx, ignoreCase ) ) < 0 )
            break;

        // copy rest up or down
        if ( lenDiff != 0 )
        {
            EnsureAllocationRelative( lenDiff );
            memmove( buffer + idx + searchStringLength + lenDiff,
                     buffer + idx + searchStringLength,
                     length - idx - searchStringLength + 1 );

            length+= lenDiff;
        }

        // fill replacement in
        memcpy  ( buffer + idx, newStr, newStringLength );

        // set start index to first character behind current replacement
        startIdx= idx+ newStringLength;

        // next
        cntReplacements++;
    }

    // that's it
    return cntReplacements;
}

// #################################################################################################
//  ConvertCase
// #################################################################################################
AString& AString::ConvertCase( bool toUpper, int substrStart, int substrLength )
{
    AString_CHECK
    // adjust range
    if ( substrLength == stdMAXINT )
    {
        if (substrStart < 0 )
            substrStart=  0;
        substrLength=  length - substrStart;
    }
    else
        if (substrStart < 0 )
        {
            substrLength+= substrStart;
            substrStart=   0;
        }

    int substrEnd= substrStart + substrLength;
    if ( substrEnd > length )
        substrEnd= length;

    // convert
    for ( int i= substrStart; i < substrEnd ; i++ )
        buffer[ i ]=  (char) ( toUpper ? toupper( buffer[ i ] )
                                       : tolower( buffer[ i ] ) );

    // return me for concatenated operations
    return *this;
}


// #################################################################################################
//  ToString()
// #################################################################################################
string AString::ToString( int regionStart, int regionLength )
const
{
    AString_CHECK
    string retval;

    // adjust range, if empty return empty string
    if ( adjustRegion( this->length, regionStart, regionLength ) )
        return retval;

    // copy our buffer into target
    retval.append( buffer , regionStart, regionLength );
    return retval;
}

string& AString::ToString( string& result, int regionStart, int regionLength, bool appendMode )
const
{
    AString_CHECK
    if ( !appendMode )
        result.clear();

    // adjust range, if empty return empty string
    if ( adjustRegion( length, regionStart, regionLength ) )
        return result;

    // copy our buffer into target
    result.append( buffer , regionStart, regionLength );
    return  result;
}

int64_t    AString::ToLong( int& idx )
const
{
    int64_t  retVal=    0;
    while ( idx < length )
    {
        char  c= buffer[ idx ];
        if ( c < '0' || c > '9' )
            break;

        retVal= ( retVal * 10 ) + ( (int) ( c - '0' ) );
        idx++;
    }

    return retVal;
}



}} // namespace / EOF
