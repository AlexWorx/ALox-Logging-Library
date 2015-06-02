// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ //<- needed for Doxygen include of the typedefs at the end of the file

// include AWXU main header first...
#if !defined (HPP_AWORX_UTIL_AWXU)
    #include "awxu.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_UTIL_ASTRING
#define HPP_AWORX_UTIL_ASTRING 1

// -------------------------------------------------------------------------------------------------
// --- includes
// -------------------------------------------------------------------------------------------------
#if !defined (_GLIBCXX_CSTRING) && !defined( _CSTRING_ )
    #include <cstring>
#endif

#if !defined (_GLIBCXX_ALGORITHM) && !defined (_ALGORITHM_)
    #include <algorithm>
#endif


// local defines (will be undef at the end of this header)
#if !defined( DOXYGEN_OMIT_THIS_PLEASE )
    #if defined(MAX_INT)
        #define MAX_INT___WAS_DEFINED
        #pragma push_macro("MAX_INT")
        #undef MAX_INT
    #endif

    #define        MAX_INT    std::numeric_limits<int>::max()
#endif

namespace aworx {
namespace       util {

/** ************************************************************************************************
 *  A mutable string, that provides public access to its internal buffer and fields.
 *  First of all, the existence of this class is motivated to reach a certain level of compatibility
 *  between source code that uses the
 *  \ref aworx::util "AWXU library" across different languages (currently Java, C#
 *  and C++) that all share a similar %AString class.
 *
 *  The given C#/Java StringBuilder/Buffer classes are "sealed" and do not provide direct
 *  access to the internal buffer. Hence, to avoid conversion to new immutable strings in certain
 *  situations, we rebuild a portion of the StringBuilder functionality here. More complex
 *  functions, like formatting operations are not supported and remain the domain language specific
 *  classes.
 *
 *  If constructed  with zero size or a null pointer string (but not a zero length string), the
 *  allocation size is 0. Nevertheless, method #Buffer will return a (zero terminated) valid empty
 *  cstring (a static singleton). This has the advantage that %Buffer will always return a valid
 *  (empty) character array but still allocations are avoided, at least deferred.
 *  Furthermore, it makes a difference if an %AString is constructed using AString() or
 *  \ref aworx::util::AString::AString(const char*,int,int) "AString(\"\").
 *  This allows to differentiate between 'nulled' AStrings and empty AStrings, which is quite handy
 *  in certain situations. An object that was filled already can be reset to represent null by
 *  either using the assignment operator (= nullptr) or by invoking SetAllocation(0) on the object.
 *  The methods Equals, CompareTo and the overloaded comparison operators == and != consequently
 *  do allow nullptr comparisons. An %AString with zero allocation is equals to a nullptr of type
 *  <em>const char*</em>. <br>
 *  To make this more clear, note the following source code taken from the unit tests:

 \verbatim
{
    char*   nullCString= nullptr;

    AString aString;
    EXPECT_TRUE( aString.CompareTo( nullCString) == 0 );
    EXPECT_TRUE( aString.Equals( nullCString) );
    EXPECT_TRUE( aString == nullptr );

    aString= "";
    EXPECT_TRUE( aString.CompareTo( nullCString) != 0 );
    EXPECT_TRUE( !aString.Equals( nullCString) );
    EXPECT_TRUE( aString != nullptr );

    aString= nullCString;
    EXPECT_TRUE( aString.CompareTo( nullCString) == 0 );
    EXPECT_TRUE( aString.Equals( nullCString) );
    EXPECT_TRUE( aString == nullptr );
}
 \endverbatim

 *  A memory-efficient specialization of this class is provided with class
 *  \ref aworx::util::AStringPreAlloc "AStringPreAlloc"
 *  and its convenient typedefs #AString16, #AString32 ... #AString1K.
 **************************************************************************************************/
class AString
{
    // #############################################################################################
    // Public enums
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Field alignment (used by method #Field)
         ******************************************************************************************/
        enum class Align
        {
            /**  Align the contents of the field at the right.*/
            RIGHT,

            /**  Align the contents of the field at the left.*/
            LEFT,

            /**  Center the contents of the field.*/
            CENTER
        };

    // #############################################################################################
    // Public static fields
    // #############################################################################################
    public:

        /** The system depended new line character code(s) retrieved statically (once) when the
         *  library is initialized. */
        AWXU_API  static std::string    NEWLINE;


        /**
         *  If true, a one time
         *  \ref aworx::util::AWXU::Warning "AWXU::Warning"
         *  will be issued if {@link #SetLength(int)} is invoked with a wrong parameter.
         *  The warning will be issued only once (unless this static field is reset to true).
         */
        AWXU_ONE_TIME_WARNING_DECL(AWXU_API, SetLength);

        /**
         *  If true, a one time
         *  \ref aworx::util::AWXU::Warning "AWXU::Warning"
         *  will be issued when an external buffer, which was set
         *  using SetExternalBuffer() gets replaced by a new allocation. This normally shall not
         *  happen, but still might be wanted or at least taken into account. If your software
         *  takes such behavior into account, you should set this static field to false on process
         *  start-up.
         *  If not, it is very useful in debug mode to see if any of your instances of
         *  \ref aworx::util::AStringPreAlloc "AStringPreAlloc"
         *  located on the stack are too small and cause unwanted heap allocations.
         *  The warning will be issued only once (unless this static field is reset to true).
         */
        AWXU_ONE_TIME_WARNING_DECL(AWXU_API, ReplaceExternalBuffer);


    // #############################################################################################
    // Private fields
    // #############################################################################################
    protected:
        /** The Buffer array. This may but should not be accessed directly. In case of external
         * modifications the field hash has to be set to dirty (0). */
        char*               buffer                                               =nullptr;

        /**
         *  The current size of the buffer excluding the trailing '\0'. If no buffer is allocated,
         *  this is is 0. If an external Buffer is used and if this buffer is not under our control
         *  (we must not delete it), then the size of such buffer is stored as a negative value.
         */
        int                 allocSize                                            =0;

        /**  The actual length of the string stored in the Buffer. In case of external
         *   modifications the field hash has to be set to dirty (0). */
        int                 length                                               =0;

        /**  The tab reference position. This is set when #NewLine is invoked. */
        int                 tabReference                                         =0;

        /**   A marker for the start of the actual field. */
        int                 fieldReference                                       =0;

    // #############################################################################################
    //  Constructors/Destructor
    // #############################################################################################

    public:
        /** ****************************************************************************************
         *     Constructs an empty %AString. Does not allocate a buffer.
         ******************************************************************************************/
        AWXU_API      AString();

        /** ****************************************************************************************
         *     Constructor with specific Buffer size .
         *
         * @param size  The initial size of the internal buffer. If less or equal to 0, no internal
         *              allocation is performed.
         ******************************************************************************************/
        AWXU_API      AString( int size );

        /** ****************************************************************************************
         *  Constructor copying a substring of another %AString.
         *
         * @param src          The reference to the %AString to copy from.
         * @param regionStart  The start of the region in ms to append. Defaults to 0.
         * @param regionLength The length of the region in src to append.
         *                     Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
        AString(const AString& src, int regionStart = 0, int regionLength= MAX_INT)
        {
            construct( src.Buffer(), src.Length(),regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Constructor copying a substring of another %AString, given as pointer.
         *
         * @param src          The pointer to the %AString to copy from.
         * @param regionStart  The start of the region in ms to append. Defaults to 0.
         * @param regionLength The length of the region in src to append.
         *                     Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
        AString( const AString* src, int regionStart= 0, int regionLength= MAX_INT )
        {
            if ( src != nullptr )
                construct( src->Buffer(), src->Length(),regionStart, regionLength );
            else
                construct( nullptr,       0,            regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Constructor copying a substring of a std::string.
         *
         * @param src          The reference to std::string to copy from.
         * @param regionStart  The start of the region in s to append. Defaults to 0.
         * @param regionLength The length of the region in src to append.
         *                     Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
        AString( const std::string& src, int regionStart= 0, int regionLength= MAX_INT)
        {
            construct( src.c_str(), src.size(),    regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Constructor copying a substring of a std::string, given as pointer.
         *
         * @param src          The pointer to the std::string to copy from.
         * @param regionStart  The start of the region in s to append. Defaults to 0.
         * @param regionLength The length of the region in src to append.
         *                     Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
        AString( const std::string* src, int regionStart= 0, int regionLength= MAX_INT)
        {
            if ( src != nullptr )
                construct( src->c_str(), src->size(),    regionStart, regionLength );
            else
                construct( nullptr,         0,                regionStart, regionLength );
        }


        /** ****************************************************************************************
         *  Constructor copying a substring of a char *.
         *
         * @param src          The source Mutable StringBuilder to copy.
         * @param regionStart  The start of the region in ms to append. Defaults to 0.
         * @param regionLength The length of the region in src to append.
         *                     Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
        AString( const char* src, int regionStart= 0, int regionLength= MAX_INT )
        {
            construct( src, src != nullptr ? strlen(src) : 0, regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  The helper method defining the behavior for all constructors that provide some
         *  string parameter. This behavior is: allocate the exactly length of the string. If string
         *  is empty or nullptr, then no allocation is done. The latter means that #GetAllocation returns 0
         *  after the %AString is constructed. Nevertheless, Buffer() will return a pointer to an empty
         *  constant character array, even if no allocation was performed.
         *
         * @param src          The source Mutable StringBuilder to copy.
         * @param srcLength    The length of the source string.
         * @param regionStart  The start of the region in ms to append. Defaults to 0.
         * @param regionLength The length of the region in src to append.
         *                     Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
    protected:
        AWXU_API  void construct( const char* src, int srcLength, int regionStart, int regionLength );

        /** ****************************************************************************************
         *  Destructs an %AString object
         ******************************************************************************************/
    public:
        AWXU_API  ~AString();


    // #############################################################################################
    // Buffer, length and allocation
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  The internal buffer character array. The Buffer is always zero terminated, hence
         *  compatible to any cstring.
         *  In case of external modifications (to do this, you have to cast it away from being
         *  const!) be sure to adjust the length of this %AString using #SetLength.
         *
         * @return The internal buffer array.
         ******************************************************************************************/
        const char* Buffer()         const    { return buffer;    }

        /** ****************************************************************************************
         *  Returns the actual length of the cstring stored in this %AString. This number is smaller
         *  or equals the number returned by #GetAllocation.
         *
         * @return The new length of the cstring represented by this.
         ******************************************************************************************/
        int         Length()         const    { return length;    }

        /** ****************************************************************************************
         *  The current size of the internal buffer (this is excluding the trailing '\0'character)
         *  which is reserved to terminate the represented cstring. In other words, the internal
         *  memory allocated is the size returned here plus one.
         *
         * @return The size of the allocated buffer.
         ******************************************************************************************/
        int         GetAllocation() const    { return allocSize < 0 ? -allocSize : allocSize;    }

        /** ****************************************************************************************
         *  Resizes the internal buffer to meet exactly the given size. Attn: If the current string
         *  represented by this instance is larger, the string is cut. This method is deemed for
         *  internal use or very special situations when used from outside.
         *
         *  Note: The true allocation size is + 1 of what is given here. This is to always be able
         *  to append the trailing '\0' character that makes our buffer compatible with cstring
         *  objects.
         *  If the desired new size is 0, then any allocated buffer will be released. However, the
         *  method Buffer() will  still return a pointer to an empty  constant character array
         *  (using an internal singleton).
         *
         *  Note: If the actual buffer was previously set using SetExternalBuffer(), this method
         *  will replace the buffer by a newly created, even if the same size was requested then
         *  what is in place.
         *
         * @param newSize  The new size for the allocation buffer. Defaults to -1 which will shrink
         *                 the buffer to fit exactly the current string length.
         ******************************************************************************************/
        AWXU_API  void    SetAllocation( int newSize= -1);

        /** ****************************************************************************************
         *  Ensures that the capacity of the internal buffer meets or exceeds the given value.
         * @param minLen    The minimum length.
         ******************************************************************************************/
        void        EnsureAllocation( int minLen )
        {
            // big enough? if not, increase at least by 50%
            int as= allocSize < 0 ? -allocSize : allocSize;
            if ( as < minLen ) // add 1 to the minimum length for the trailing '\0' character
                SetAllocation(  std::max( minLen, as + (as / 2) ) );
        }

        /** ****************************************************************************************
         *  Ensures that the capacity of the internal buffer meets or exceeds the actual length
         * plus the given growth value.
         *
         * @param growth    The desired growth of length.
         ******************************************************************************************/
        void        EnsureAllocationRelative( int growth )
        {
            // big enough? if not, increase at least by 50%
            int as= allocSize < 0 ? -allocSize : allocSize;
            if ( as < length + growth ) // add 1 to the minimum length for the trailing '\0' character
                SetAllocation(  std::max( length + growth, as + (allocSize / 2) ) );
        }

        /** ****************************************************************************************
         *  This methods sets an external character array as the buffer to use by this %AString.
         *  This is useful a) If certain operations on external strings should be performed, b) if
         *  already allocated memory should be reused or c) for using stack memory as the internal
         *  buffer to avoid heap allocations. For the latter, see class template AStringPreAlloc and
         *  corresponding easy to use type definitions, e.g.
         *  \ref aworx::util::AString256.
         *
         *  If a nullptr is provided and the allocation size is 0, then the actual buffer is
         *  released.
         *
         *  Should the buffer's size not be sufficient for future modifications of this object, then
         *  a new buffer will be allocated internally. The parameter 'deleteOnResize' determines, if
         *  the given buffer should be deleted in this case.
         *
         *  Any Previously allocated or provided buffers will be released. Existing content will not
         *  be copied into the external buffer.
         *
         * @param buffer          The external buffer to use.
         * @param allocSize       The size of the given buffer.
         * @param length          The length of any content already located in the given buffer.
         *                        Has to be smaller or equal to allocSize -1 to preserve space for a
         *                        trailing '\0'. Defaults to 0.
         * @param deleteOnResize  If true, the given buffer will be deleted when a new allocation is
         *                        performed for any reason. Defaults to false, which means deletion
         *                        is due to caller (or buffer is a stack object).
         ******************************************************************************************/
        AWXU_API void        SetExternalBuffer( char* buffer, int allocSize, int length= 0, bool deleteOnResize= false );

        /** ****************************************************************************************
         *  Set the actual length of the stored cstring. The string can only be shortened.
         *  To increase the length, use one of the Append methods, e.g. Append( char, int ). To change
         *  the internal allocation size, see #SetAllocation.
         *
         * @param newLength    The new length of the %AString. Must be smaller than the current length.
         * @return The new length of the cstring represented by this.
         ******************************************************************************************/
        AWXU_API int         SetLength( int newLength );

        /** ****************************************************************************************
         *    Clear the Buffer. Same as #Delete (0, Length()) but without internal region checks.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString&    Clear();

        /** ****************************************************************************************
         *  Deletes a region from the Buffer.
         *  Note: To delete all contents use #Clear.
         *
         * @param regionStart   The start of the region to delete.
         * @param regionLength  The length of the region to delete. Defaults to
         *                      std::numeric_limits<int>::max().
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString&    Delete( int regionStart, int regionLength= MAX_INT  );

        /** ****************************************************************************************
         * Inserts a region into the Buffer. The region gets filled with the given character.
         *
         *
         * @param regionStart   The start of the region to insert. If this is out of the string
         *                      bounds (hence less than 0 or greater then #Length, nothing is done.
         *
         * @param regionLength  The length of the region to insert.
         * @param fillChar      (Optional) The character to fill the new region with.
         *                      Defaults to ' ' (space).
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString&    Insert( int regionStart, int regionLength, char fillChar= ' ');

        /** ****************************************************************************************
         *  Fills a region of this %AString with the given character
         *  If out of bounds, the given region is adjusted. The length of this remains unchanged.
         *
         * @param c             The character to set.
         * @param regionStart   The start of the region in this to set.
         * @param regionLength  The length of the region in this to set.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API  AString& Fill( char c, int regionStart= 0, int regionLength= MAX_INT );

        /** ****************************************************************************************
         *  Appends platform specific new line character(s). ( "\\r\\n", "\\r", etc.). The new
         *  length of the string is recorded as the reference position for #Tab.
         * @return 'this' to allow concatenated calls.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString&    NewLine();

        /** ****************************************************************************************
         *  Go to the next tab stop by filling in pad characters repeatedly. The tab position is relative
         *  to the starting of the current line (if subsequent calls to #NewLine where performed).
         *
         * @param tabSize  The tab positions are multiples of this parameter.
         * @param minPad   (Optional) The minimum pad characters to add. Defaults to 1.
         * @param tabChar  (Optional) The character to insert to reach the tab position.
         *                 Defaults to ' ' (space).
         * @return    '*this' to            allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString&    Tab( int tabSize, int minPad= 1, char tabChar= ' ');

    // #############################################################################################
    // C++ specific operator overloading
    // #############################################################################################
    public:
        /** Assign char as string. If operand is nullptr, the string gets cleared and memory freed
         *  with 0 allocation size. This enables a reset into the null state.
         *  @param op The operand
         *  @returns Itself.
         */
        AString& operator=  (const char*           op)
        {

           if( op == nullptr )
           {
               SetAllocation(0);
               return *this;
           }
           Clear();
           return Append( op );
        }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator=  (const AString&        op)   { Clear();  return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator=  (const std::string     op)   { Clear();  return Append( op ); }

        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator+= (const AString&        op)   {           return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator+= (const std::string&    op)   {           return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator+= (const char*           op)   {           return Append( op ); }

        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator<< (const AString&        op)   {           return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator<< (const std::string&    op)   {           return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator<< (const char*           op)   {           return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator<< (const char            op)   {           return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator<< (const int32_t         op)   {           return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator<< (const uint32_t        op)   {           return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator<< (const int64_t         op)   {           return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator<< (const uint64_t        op)   {           return Append( op ); }
        /** Append operand as string. @param op The operand @returns Itself. */ AString& operator<< (const double          op)   {           return Append( op ); }

        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator<  (const AString&     op) const { return CompareTo( op ) <  0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator<  (const std::string& op) const { return CompareTo( op ) <  0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator<  (const char*        op) const { return CompareTo( op ) <  0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator>  (const AString&     op) const { return CompareTo( op ) >  0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator>  (const std::string& op) const { return CompareTo( op ) >  0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator>  (const char*        op) const { return CompareTo( op ) >  0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator== (const AString&     op) const { return CompareTo( op ) == 0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator== (const std::string& op) const { return CompareTo( op ) == 0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator== (const char*        op) const { return CompareTo( op ) == 0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator!= (const AString&     op) const { return CompareTo( op ) != 0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator!= (const std::string& op) const { return CompareTo( op ) != 0 ;  }
        /** Compare operator. @param op The operand @returns The result of the comparison. */ bool     operator!= (const char*        op) const { return CompareTo( op ) != 0 ;  }

        /// Access single characters. Attn: no range check is performed.
                                char&    operator[] (int                op)       { return buffer[op];             }
    // #############################################################################################
    // Append
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  Append the given cstring. If the length of the string is not known, -1 can be passed.
         *  In this case, the length of the string is evaluated using strlen().
         *
         * @param srcLength  The length of the cstring. If -1 is provided, the length is determined.
         *
         * @param src  A pointer to the cstring to append.
         *
         * @return    '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString& Append(  int srcLength, const char* src );

        /** ****************************************************************************************
         *    Append a region of the given cstring. If the length of the string is not known, -1 can
         *  be passed. In this case, the length of the string is evaluated using strlen().
         *
         * @param srcLength      The length of the cstring.
         * @param src            The cstring to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max()
         *
         * @return    '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString& Append(  int srcLength, const char* src, int regionStart, int regionLength= MAX_INT );

        /** ****************************************************************************************
         *  Append a cstring. Note: if the length of the cstring is known, it is recommended to use the
         *  variant of this method that receives the cstring length as its first parameter.
         *
         * @param src            The cstring to append.
         * @return    '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Append( const char* src )
        {
            return Append( -1, src );
        }

        /** ****************************************************************************************
         *  Append a region of the given cstring.
         *
         * @param src            The cstring to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max()
         *
         * @return    '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Append( const char* src, int regionStart, int regionLength= MAX_INT )
        {
            return Append( -1, src, regionStart, regionLength );
        }

        /** ****************************************************************************************
         *     Append the given %AString.
         * @param src The %AString to append.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Append( const AString& src )
        {
            return Append( src.Length(), src.Buffer() );
        }

        /** ****************************************************************************************
         *  Append a substring of the given %AString.
         *
         * @param src            The %AString to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max()
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Append( const AString& src, int regionStart, int regionLength= MAX_INT )
        {
            return Append( src.Length(), src.Buffer(), regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Append a substring of a %AString provided as pointer.
         * @param src The pointer to the %AString to append.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Append( const AString* src )
        {
            return ( src != nullptr )   ?  Append( src->Length(), src->Buffer() )
                                        :  *this;
        }

        /** ****************************************************************************************
         *  Append a substring of a %AString provided as pointer.
         *
         * @param src            The pointer to the %AString to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max()
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Append( const AString* src, int regionStart, int regionLength= MAX_INT )
        {
            return ( src != nullptr )   ?  Append( src->Length(), src->Buffer(), regionStart, regionLength )
                                        :  *this;
        }

        /** ****************************************************************************************
         *  Append a std::string.
         * @param src    A std::string reference to append.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Append( const std::string& src )
        {
            return Append( src.size(), src.c_str() );
        }

        /** ****************************************************************************************
         *  Append a substring of a std::string.
         *
         * @param src            The std::string to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max()
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Append( const std::string& src, int regionStart, int regionLength= MAX_INT )
        {
            return Append( src.size(), src.c_str(), regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Append a substring of a std::string provided as pointer.
         * @param src    The pointer to the std::string to append.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Append( const std::string* src )
        {
            return ( src != nullptr )   ?  Append( src->size(), src->c_str() )
                                        :  *this;
        }

        /** ****************************************************************************************
         *  Append a substring of a std::string provided as pointer.
         *
         * @param src            The pointer to the std::string to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max()
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Append( const std::string* src, int regionStart, int regionLength= MAX_INT )
        {
            return ( src != nullptr )   ?  Append( src->size(), src->c_str(), regionStart, regionLength )
                                        :  *this;
        }

        /** ****************************************************************************************
         *  Append the given character.
         * @param c    The character to append.
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API  AString& Append( char c );

        /** ****************************************************************************************
         *  Append the given character repeatedly.
         *
         * @param c      The character to append.
         * @param qty    The quantity of characters to append.
         *
         * @return    '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API  AString& Append( char c, int qty );

        /** ****************************************************************************************
         * Append the given 32-Bit integer value.
         *
         * @param i            The integer value to append.
         * @param minDigits    The minimum number of digits to append. If given value has less digits,
         *                     '0' characters are prepended. Optional, defaults to 0.
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString& Append( int32_t i, int minDigits= 1 );

        /** ****************************************************************************************
         *  Append the given unsigned 32-Bit integer value.
         *
         * @param i            the integer value to append.
         * @param minDigits    The minimum number of digits to append. If given value has less digits,
         *                     '0' characters are prepended. Optional, defaults to 0.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString& Append( uint32_t i, int minDigits= 1 );

        /** ****************************************************************************************
         * Append the given 32-Bit integer value.
         *
         * @param i            The integer value to append.
         * @param minDigits    The minimum number of digits to append. If given value has less digits,
         *                     '0' characters are prepended. Optional, defaults to 0.
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString& Append( int64_t i, int minDigits= 1 );

        /** ****************************************************************************************
         *  Append the given unsigned 32-Bit integer value.
         *
         * @param i            the integer value to append.
         * @param minDigits    The minimum number of digits to append. If given value has less digits,
         *                     '0' characters are prepended.
         *                     Optional, defaults to 0.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString& Append( uint64_t i, int minDigits= 1 );

        /** ****************************************************************************************
         *  Append the given double value using the minimum digits before and after the given number of
         *  digits after dot.
         *
         * @param d                     the integer value to append.
         * @param minDigitsBeforeDot    The minimum number of digits write before the dot. If the
         *                              number has less digits than minDigits, then trailing '0's
         *                              are added. Defaults to 0
         * @param digitsAfterDot        The exact number of digits written after the dot.
                                        Defaults to 5.
         * @return    '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString& Append( double d, int minDigitsBeforeDot= 0, int digitsAfterDot= 5 );

    // #############################################################################################
    // Fields
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * If invoked without parameters, the start of a field is marked at the current end of the string.
         * Otherwise the end of a field is set and the contents between the field start marker and the
         * current end of the string is aligned within the field using the given pad character.
         * Note: To implement nested fields, the outer fields have to be set by providing the start marker
         * by using the parameter fieldStart. Hence, only the starting points of the most inner fields
         * can be set using this method without parameters.
         *
         *
         * @param size            The field size in relation to the starting index of the field, defined
         *                        either by using %Field() prior to this invocation or by providing the
         *                        parameter fieldStart. The field gets filled with the given pad character
         *                        to meet the size while the content gets aligned left, right or centered.
         *                        If the content exceeds the size, then no alignment takes place.
         *
         * @param alignment       The alignment of the contents within the field.
         *                        Defaults to
         *                        \ref aworx::util::AString::Align "Align::RIGHT"
         *                        Other options are
         *                        \ref aworx::util::AString::Align "Align::LEFT" and
         *                        \ref aworx::util::AString::Align "Align::CENTER".
         *
         * @param padChar         The character used to fill the field up to its size.
         *                        Defaults to ' ' (space).
         *
         * @param fieldStart      This parameter, if given, overwrites the start index of the field.
         *                        The invocation of #Field can be omitted, when this value is explicitly
         *                        provided.
         *                        Defaults to std::numeric_limits<int>::max().
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API AString& Field( int size=-1, Align alignment= Align::RIGHT, char padChar= ' ', int fieldStart= MAX_INT );

    // #############################################################################################
    // Compare, ContainsAt, Starts-/EndsWith
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Static method that compares two cstrings (zero terminated character arrays). For both character
         * arrays a region for comparison can be specified. Regions that are out of bounds get adjusted and
         * then compared. If this behavior is not what is wanted, a separate region check and corresponding
         * compare result evaluation has to be performed.
         *
         * @param referenceString           The reference cstring that is compared to the second string
         *                                  provided.
         * @param referenceStringLength     The length of the referenceString. Has to be the same as
         *                                  strlen(referenceString).
         * @param compareString             A cstring that is compared to first cstring provided.
         * @param compareStringLength       The length of the compareString. Has to be the same as
         *                                  strlen(compareString).
         * @param ignoreCase                If true, the compare is case insensitive. Optional and defaults
         *                                  to false.
         * @param compareStringRegionStart  The start of the substring within the given cstring that is to be compared
         *                                  to this. Defaults to 0.
         * @param compareStringRegionLength The length of the substring within the given cstring that is to
         *                                  be compared to this. Defaults to Integer.MAX_VALUE.
         * @param regionStart               The start of the substring within this cstring that is to be.
         *                                  compared Defaults to 0.
         * @param regionLength              The length of the substring within this cstring that is to be
         *                                  compared. Defaults to Integer.MAX_VALUE.
         *
         * @return
         *   0 if the contents of the cstring regions are equal (or if both regions are empty or out of range).
         *   -1 if the instance is less than the given cstring.
         *   +1 if the instance is greater than the given cstring or if given cstring is null.
         *
         ******************************************************************************************/
        AWXU_API
        static int CompareTo(   const char*        referenceString,
                                int                referenceStringLength,
                                const char*        compareString,
                                int                compareStringLength,
                                bool               ignoreCase=                 false,
                                int                compareStringRegionStart=   0,
                                int                compareStringRegionLength=  MAX_INT,
                                int                regionStart=                0,
                                int                regionLength=               MAX_INT );


        /** ****************************************************************************************
         * Compares a given region of a given cstring with the a region of this instance. Regions
         * that are out of bounds get adjusted and then compared. If this behavior is not what is
         * wanted, a separate region check and corresponding compare result evaluation has to be
         * performed.
         *
         * @param compareString
         *   An cstring that is compared to this %AString.
         * @param ignoreCase                If true, the compare is case insensitive. Optional
         *                                  and defaults to false.
         * @param compareStringRegionStart  The start of the substring within the given cstring
         *                                  that is to be compared to this. Defaults to 0.
         * @param compareStringRegionLength The length of the substring within the given cstring
         *                                  that is to be compared to this.
         *                                  Defaults to Integer.MAX_VALUE.
         * @param regionStart               The start of the substring within this %AString that is
         *                                  to be compared. Defaults to 0.
         * @param regionLength              The length of the substring within this %AString that
         *                                  is to be compared.
         *                                  Defaults to Integer.MAX_VALUE.
         *
         * @return
         *   0 if the contents of the regions are equal (or if both regions are empty or out of
         *     range).
         *  -1 if the instance is less than the given cstring.
         *  +1 if the instance is greater than the given cstring or if given cstring is null.
         *
         ******************************************************************************************/
        AWXU_API
        int CompareTo(  const char*     compareString,
                        bool            ignoreCase=                 false,
                        int             compareStringRegionStart=   0,
                        int             compareStringRegionLength=  MAX_INT,
                        int             regionStart=                0,
                        int             regionLength=               MAX_INT )
        const
        {
            return CompareTo( allocSize ? this->buffer : nullptr, this->length,
                              compareString,                      ( compareString ? strlen(compareString) : 0 ),
                              ignoreCase,
                              compareStringRegionStart,           compareStringRegionLength,
                              regionStart,                        regionLength );
        }


        /** ****************************************************************************************
         * Compares a given region of a given %AString with the a region of this instance. Regions
         * that areout of bounds get adjusted and then compared. If this behavior is not what is
         * wanted, a separate region check and corresponding compare result evaluation has to be
         * performed.
         *
         * @param compareString             The %AString reference that is compared to this %AString.
         * @param ignoreCase                If true, the compare is case insensitive. Optional and
         *                                  defaults to false.
         * @param compareStringRegionStart  The start of the substring within the given %AString that
         *                                  is to be compared to this.
         *                                  Defaults to 0.
         * @param compareStringRegionLength The length of the substring within the given %AString
         *                                  that is to be compared to this.
         *                                  Defaults to Integer.MAX_VALUE.
         * @param regionStart               The start of the substring within this %AString that is
         *                                  to be compared. Defaults to 0.
         * @param regionLength              The length of the substring within this %AString that is
         *                                  to be compared. Defaults to Integer.MAX_VALUE.
         *
         * @return
         *   0 if the contents of the regions are equal (or if both regions are empty or out of range).
         *      -1 if the instance is less than the given %AString.
         *      +1 if the instance is greater than the given %AString or if given %AString is null.
         *
         ******************************************************************************************/
        int CompareTo(  const AString&    compareString,
                        bool              ignoreCase=                 false,
                        int               compareStringRegionStart=   0,
                        int               compareStringRegionLength=  MAX_INT,
                        int               regionStart=                0,
                        int               regionLength=               MAX_INT )
        const
        {
            return CompareTo(               allocSize ?         this->buffer : nullptr,  this->length,
                              compareString.allocSize ? compareString.buffer : nullptr,  compareString.length,
                              ignoreCase,
                              compareStringRegionStart,   compareStringRegionLength,
                              regionStart,                regionLength );
        }


        /** ****************************************************************************************
         * Compares a given region of a given %AString with the a region of this instance. Regions
         * that are out of bounds get adjusted and then compared. If this behavior is not what is
         * wanted, a separate region check and corresponding compare result evaluation has to be
         * performed.
         *
         * @param compareString             A pointer to the %AString that is compared to this
         *                                  %AString.
         * @param ignoreCase                If true, the compare is case insensitive. Optional and
         *                                  defaults to false.
         * @param compareStringRegionStart  The start of the substring within the given %AString that
         *                                  is to be compared
         *   to this.                       Defaults to 0.
         * @param compareStringRegionLength The length of the substring within the given %AString that
         *                                  is to be compared to this.
         *   Defaults to                    Integer.MAX_VALUE.
         * @param regionStart               The start of the substring within this %AString that is
         *                                  to be compared. Defaults to 0.
         * @param regionLength              The length of the substring within this %AString that is
         *                                  to be compared. Defaults to Integer.MAX_VALUE.
         *
         * @return
         *   0 if the contents of the regions are equal (or if both regions are empty or out of range).
         *      -1 if the instance is less than the given %AString.
         *      +1 if the instance is greater than the given %AString or if given %AString is null.
         *
         ******************************************************************************************/
        int CompareTo(  const AString*  compareString,
                        bool            ignoreCase=                 false,
                        int             compareStringRegionStart=   0,
                        int             compareStringRegionLength=  MAX_INT,
                        int             regionStart=                0,
                        int             regionLength=               MAX_INT )
        const
        {
            const char* thisBuffer= allocSize ? this->buffer : nullptr;
            return (compareString != nullptr)
                   ?  CompareTo(   thisBuffer,                                                  this->length,
                                   compareString->allocSize? compareString->buffer : nullptr,   compareString->length,
                                   ignoreCase,
                                   compareStringRegionStart,    compareStringRegionLength,
                                   regionStart,                 regionLength )
                   :  CompareTo(   thisBuffer,                  this->length,
                                   nullptr,                     0,
                                   ignoreCase,
                                   compareStringRegionStart,    compareStringRegionLength,
                                   regionStart,                 regionLength );
        }


        /** ****************************************************************************************
         * Compares a given region of a given std::string with the a region of this instance. Regions that are
         * out of bounds get adjusted and then compared. If this behavior is not what is wanted, a separate
         * region check and corresponding compare result evaluation has to be performed.
         *
         * @param compareString
         *   The std::string reference that is compared to this %AString.
         * @param ignoreCase
         *   If true, the compare is case insensitive. Optional and defaults to false.
         * @param compareStringRegionStart
         *   The start of the substring within the given std::string that is to be compared
         *   to this. Defaults to 0.
         * @param compareStringRegionLength
         *   The length of the substring within the given std::string that is to be compared to this.
         *   Defaults to Integer.MAX_VALUE.
         * @param regionStart
         *   The start of the substring within this %AString that is to be compared. Defaults    to 0.
         * @param regionLength
         *   The length of the substring within this %AString that is to be compared. Defaults to
         *     Integer.MAX_VALUE.
         *
         * @return
         *   0 if the contents of the regions are equal (or if both regions are empty or out of range).
         *      -1 if the instance is less than the given std::string.
         *      +1 if the instance is greater than the given std::string or if given std::string is null.
         *
         ******************************************************************************************/
        int CompareTo(  const std::string*    compareString,
                        bool                  ignoreCase=                 false,
                        int                   compareStringRegionStart=   0,
                        int                   compareStringRegionLength=  MAX_INT,
                        int                   regionStart=                0,
                        int                   regionLength=               MAX_INT )
        const
        {
            const char* thisBuffer= allocSize ? this->buffer : nullptr;
            return (compareString != nullptr)    ?   CompareTo( thisBuffer,                 this->length,
                                                                compareString->c_str(),     compareString->size(),
                                                                ignoreCase,
                                                                compareStringRegionStart,   compareStringRegionLength,
                                                                regionStart,                regionLength )
                                                :    CompareTo( thisBuffer,                 this->length,
                                                                nullptr,                    0,
                                                                ignoreCase,
                                                                compareStringRegionStart,   compareStringRegionLength,
                                                                regionStart,                regionLength );
        }


        /** ****************************************************************************************
         * Compares a given region of a given std::string with the a region of this instance.
         * Regions that are out of bounds get adjusted and then compared. If this behavior is not
         * what is wanted, a separate region check and corresponding compare result evaluation has
         * to be performed.
         *
         * @param compareString             Pointer to the std::string that is compared to this
         *                                  %AString.
         * @param ignoreCase                If true, the compare is case insensitive. Optional and
         *                                  defaults to false.
         * @param compareStringRegionStart  The start of the substring within the given std::string
         *                                  that is to be compared to this.
         *                                  Defaults to 0.
         * @param compareStringRegionLength The length of the substring within the given std::string
         *                                  that is to be compared to this.
         *                                  Defaults to Integer.MAX_VALUE.
         * @param regionStart               The start of the substring within this %AString that
         *                                  is to be compared. Defaults    to 0.
         * @param regionLength              The length of the substring within this %AString that
         *                                  is to be compared. Defaults to Integer.MAX_VALUE.
         *
         * @return
         *   0 if the contents of the regions are equal (or if both regions are empty or out of range).
         *      -1 if the instance is less than the given std::string.
         *      +1 if the instance is greater than the given std::string or if given std::string is null.
         *
         ******************************************************************************************/
        int CompareTo(  const std::string&  compareString,
                        bool                ignoreCase=                 false,
                        int                 compareStringRegionStart=   0,
                        int                 compareStringRegionLength=  MAX_INT,
                        int                 regionStart=                0,
                        int                 regionLength=               MAX_INT )
        const
        {
            return CompareTo( allocSize ? this->buffer : nullptr,  this->length,
                              compareString.c_str(),               compareString.size(),
                              ignoreCase,
                              compareStringRegionStart,            compareStringRegionLength,
                              regionStart,                         regionLength );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given string representation equals to what this object
         * represents. True is returned if both are zero length or nullptr.
         *
         * @param compareString         A cstring that is compared to this %AString.
         * @param ignoreCase            If true, the compare is case insensitive. Optional and
         *                              defaults to false.
         * @param compareStringLength   The length of the given cstring. If -1 (default), the length
         *                              will be evaluated using strlen().
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        AWXU_API
        bool Equals( const char*     compareString,
                     bool            ignoreCase=         false,
                     int             compareStringLength=  -1        )           const;


        /** ****************************************************************************************
         * Tests and returns true, if the given string representation equals to what this object
         * represents. True is returned if both are zero length or nullptr.
         *
         * @param compareString A %AString that is compared to this %AString.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        bool Equals( const AString&  compareString, bool ignoreCase= false )        const
        {
            return Equals( compareString.Buffer(), ignoreCase, compareString.Length() );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given string representation equals to what this object
         * represents. True is returned if both are zero length or nullptr.
         *
         * @param compareString A pointer to a %AString that is compared to this %AString.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        bool Equals( const AString*  compareString, bool ignoreCase= false )        const
        {
            if ( compareString == nullptr )
                return ( allocSize ==0 );
            return Equals( compareString->Buffer(), ignoreCase, compareString->Length() );
        }


        /** ****************************************************************************************
         * Tests and returns true, if the given string representation equals to what this object
         * represents. True is returned if both are zero length or nullptr.
         *
         * @param compareString A std::string that is compared to this %AString.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        bool Equals( const std::string& compareString, bool ignoreCase= false )     const
        {
            return Equals( compareString.c_str(), ignoreCase, compareString.size() );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given string representation equals to what this object
         * represents. True is returned if both are zero length or nullptr.
         *
         * @param compareString A pointer to a std::string that is compared to this %AString.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        bool Equals( std::string* compareString, bool ignoreCase= false )           const
        {
            if ( compareString == nullptr )
                return ( allocSize == 0 );
            return Equals( compareString->c_str(), ignoreCase, compareString->size() );
        }

        /** ****************************************************************************************
         *  Checks if the given cstring is located at the given position within this %AString.
         *
         * @param needle     The cstring to search for. If s is null or empty, true is returned.
         * @param pos        The position to search for needle.
         * @param ignoreCase If true, the compare is case insensitive. Optional and defaults to
         *                   false.
         * @param needleLen  Optionally restricts the length of needle that is compared to with this
         *                   %AString buffer. If -1 (default), the whole string sequence will be
         *                   matched, the first needleLen characters otherwise. Furthermore, if the
         *                   length of needle is known, it is a good practice to provide it here to
         *                   save the costs of determining it inside of this function.
         * @return True if the given cstring is found at the given position. False otherwise .
         ******************************************************************************************/
        AWXU_API
        bool ContainsAt( const char* needle, int pos, bool ignoreCase= false, int needleLen= -1 )    const;

        /** ****************************************************************************************
         *  Checks if the given %AString is located at the given position within this.
         * @param needle        The %AString reference to search. If is null or empty, true is returned.
         * @param pos            The position to search for needle.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to
         *                                false.
         * @return True if the given std::string is found at the given position. False otherwise. *
         ******************************************************************************************/
        bool ContainsAt( const AString& needle, int pos, bool ignoreCase= false )    const { return  ContainsAt( needle.buffer, pos, ignoreCase, needle.length ); }

        /** ****************************************************************************************
         *     Checks if the given %AString is located at the given position within this.
         * @param needle     Pointer to an %AString to search. If is null or empty, true is returned.
         * @param pos        The position to search for needle.
         * @param ignoreCase If true, the compare is case insensitive. Optional and defaults to
         *                   false.
         * @return True if the given std::string is found at the given position. False otherwise. *
         ******************************************************************************************/
        bool ContainsAt( const AString* needle, int pos, bool ignoreCase= false )    const
        {
            return  needle != nullptr   ?  ContainsAt( needle->buffer,    pos, ignoreCase, needle->length )
                                        :  ContainsAt( nullptr,            pos, ignoreCase, 0 );
        }

        /** ****************************************************************************************
         *  Checks if the given std::string is located at the given position within this.
         * @param needle     The std::string to search. If is null or empty, true is returned.
         * @param pos        The position to search for needle.
         * @param ignoreCase If true, the compare is case insensitive. Optional and defaults to
         *                   false.
         * @return True if the given std::string is found at the given position. False otherwise. *
         ******************************************************************************************/
        bool ContainsAt( const std::string& needle, int pos, bool ignoreCase= false )    const { return  ContainsAt( needle.c_str(), pos, ignoreCase, needle.size() ); }

        /** ****************************************************************************************
         *     Checks if the given std::string is located at the given position within this.
         * @param needle        Pointer to a std::string to search. If is null or empty, true is returned.
         * @param pos           The position to search for needle.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to
         *                      false.
         * @return True if the given std::string is found at the given position. False otherwise. *
         ******************************************************************************************/
        bool ContainsAt( const std::string* needle, int pos, bool ignoreCase= false )    const
        {
            return  needle != nullptr   ?  ContainsAt( needle->c_str(),    pos, ignoreCase, needle->size() )
                                        :  ContainsAt( nullptr,            pos, ignoreCase, 0 );
        }

        /** ****************************************************************************************
         *  Checks if this %AString starts with the given cstring.
         * @param needle        The cstring to be compared with the start of this %AString.
         *                      If this is null or empty, true is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to
         *                      false.
         * @param needleLen     Optionally restricts the length of needle that is compared to with this
         *                      %AString buffer. If -1 (default), the whole string sequence will be
         *                      matched, the first needleLen characters otherwise.
         *                      Furthermore, if the length of needle is known, it is a good practice to
         *                      provide it here    to save the costs of determining it inside of this
         *                      function.
         * @return true if this starts with the given cstring, false if not.
         ******************************************************************************************/
        bool StartsWith( const char* needle, bool ignoreCase= false, int needleLen= -1 )const { return  ContainsAt( needle, 0, ignoreCase, needleLen ); }

        /** ****************************************************************************************
         *  Checks if this %AString starts with the given std::string reference.
         * @param needle        The std::string to be compared with the start of this %AString.
         *                      If this is empty, true is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to
         *                      false.
         * @return true if this starts with the given std::string, false if not.
         ******************************************************************************************/
        bool StartsWith( const std::string& needle, bool ignoreCase= false )            const { return  ContainsAt( needle.c_str(), 0, ignoreCase, needle.size() ); }

        /** ****************************************************************************************
         *  Checks if this %AString starts with the given std::string.
         * @param needle        The std::string to be compared with the start of this %AString.
         *                      If this is empty, true is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         * @return true if this starts with the given std::string, false if not.
         ******************************************************************************************/
        bool StartsWith( const std::string* needle, bool ignoreCase= false )            const { return  ( needle == 0 ) || ContainsAt( needle->c_str(), 0, ignoreCase, needle->size() ); }

        /** ****************************************************************************************
         *  Checks if this %AString starts with the given %AString.
         * @param needle        The %AString to be compared with the start of this %AString.
         *                      If this is empty, true is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         * @return true if this starts with the given %AString, false if not.
         ******************************************************************************************/
        bool StartsWith( const AString& needle, bool ignoreCase= false )                const { return  ContainsAt( needle.Buffer(), 0, ignoreCase, needle.Length() ); }

        /** ****************************************************************************************
         *  Checks if this %AString starts with the given %AString.
         * @param needle        The %AString to be compared with the start of this %AString.
         *                      If this is empty, true is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         *                      false.
         * @return true if this starts with the given %AString, false if not.
         ******************************************************************************************/
        bool StartsWith( const AString* needle, bool ignoreCase= false )                const { return  ( needle == 0 ) ||  ContainsAt( needle->buffer, 0, ignoreCase, needle->length ); }

        /** ****************************************************************************************
         *  Checks if this %AString ends with the given cstring.
         * @param needle        The cstring to be compared with the end of this %AString.
         *                      If this is null or empty, true is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to
         *                      false.
         * @param needleLen     Optionally restricts the length of needle that is compared to with this
         *                      %AString buffer. If -1 (default), the whole string sequence will be
         *                      matched, the first needleLen characters otherwise.
         *                      Furthermore, if the length of needle is known, it is a good practice to
         *                      provide it here    to save the costs of determining it inside of this
         *                      function.
         * @return true if this starts with the given cstring, false if not.
         ******************************************************************************************/
        bool EndsWith  ( const char* needle, bool ignoreCase= false, int needleLen= -1 )
        const
        {
            if (needle == nullptr) return true;
            if (needleLen < 0 ) needleLen= strlen( needle );
            return ContainsAt( needle, length - needleLen, ignoreCase, needleLen );
        }

        /** ****************************************************************************************
         *  Checks if this %AString ends with the given %AString.
         * @param needle        The %AString to be compared with the end of this %AString.
         *                      If this is empty, true is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         * @return true if this starts with the given %AString, false if not.
         ******************************************************************************************/
        bool EndsWith  ( const AString& needle, bool ignoreCase= false )            const { int nl= needle.Length(); return  ContainsAt( needle.Buffer(), length - nl, ignoreCase, nl ); }

        /** ****************************************************************************************
         *  Checks if this %AString ends with the given %AString.
         * @param needle        The %AString to be compared with the end of this %AString.
         *                      If this is empty, true is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         * @return true if this starts with the given %AString, false if not.
         ******************************************************************************************/
        bool EndsWith  ( const AString* needle, bool ignoreCase= false )            const { if (needle==0) return true; int nl= needle->length; return  ContainsAt( needle->buffer, length - nl, ignoreCase, nl ); }

        /** ****************************************************************************************
         *  Checks if this %AString ends with the given std::string.
         * @param needle        The std::string to be compared with the end of this %AString.
         *                      If this is empty, true is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         * @return true if this starts with the given std::string, false if not.
         ******************************************************************************************/
        bool EndsWith  ( const std::string& needle, bool ignoreCase= false )        const { int nl= needle.size(); return  ContainsAt( needle.c_str(), length - nl, ignoreCase, nl ); }

        /** ****************************************************************************************
         *  Checks if this %AString ends with the given std::string.
         * @param needle        The std::string to be compared with the end of this %AString.
         *                      If this is empty, true is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         * @return true if this starts with the given std::string, false if not.
         ******************************************************************************************/
        bool EndsWith  ( const std::string* needle, bool ignoreCase= false )        const { if (needle==0) return true; int nl= needle->size(); return  ContainsAt( needle->c_str(), length - nl, ignoreCase, nl ); }

    // #############################################################################################
    // IndexOf
    // #############################################################################################

        /** ****************************************************************************************
         *  Static version of IndexOf() that take cstring parameters (character arrays with '\\0'
         * terminated strings) as arguments. An optional start index can restrict the search to start
         * searching from an offset.
         * Exact match as well as case insensitive match are supported.
         * If the length of the strings is provided as -1, the length will be determined. The parameter is
         * just for optimization purposes in the case the length is known.
         *
         *
         * @param haystack       The cstring to be searched in.
         * @param haystackLen    The length of haystack. If provided as -1, the length is determined
         *                       at the start step.
         * @param needle         The cstring to be searched for.
         * @param needleLen      The length of the cstring that is searched for. If provided as -1, the
         *                       length is determined at the start step.
         * @param startIdx       An optional offset that determines where in haystack the search should
         *                       start.
         * @param ignoreCase     If true, a case insensitive search is performed.
         *
         * @return    -1 if the string is not found. Otherwise the index of its first occurrence.
         ******************************************************************************************/
        AWXU_API
        static int    IndexOf( const char* haystack,  int haystackLen,
                               const char* needle,    int needleLen, int startIdx= 0, bool ignoreCase= false );

        /** ****************************************************************************************
         *     Search the given %AString in the Buffer.
         *
         * @param needle        The std::string to search for.
         * @param startIdx      The index to start the search at. Optional and defaults to 0.
         * @param ignoreCase    If true, a case insensitive search is performed.
         *
         * @return    -1 if the std::string is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        int            IndexOf( const AString& needle, int startIdx= 0, bool ignoreCase= false  )    const { return IndexOf( buffer, length, needle.Buffer(), needle.Length(), startIdx, ignoreCase ); }

        /** ****************************************************************************************
         *     Search the given std::string in the Buffer.
         *
         * @param needle        The std::string to search for.
         * @param startIdx      The index to start the search at. Optional and defaults to 0.
         * @param ignoreCase    If true, a case insensitive search is performed.
         *
         * @return    -1 if the std::string is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        int            IndexOf( const std::string& needle, int startIdx= 0, bool ignoreCase= false ) const { return IndexOf( buffer, length, needle.c_str(), needle.size(), startIdx, ignoreCase ); }

        /** ****************************************************************************************
         *     Search the given string in the Buffer.
         *
         * @param needle        The cstring to search for.
         * @param startIdx      The index to start the search at. Optional and defaults to 0.
         * @param ignoreCase    If true, a case insensitive search is performed.
         *
         * @return    -1 if the string represented by the char* is not found. Otherwise the index of
         * first occurrence.
         ******************************************************************************************/
        int            IndexOf( const char* needle, int startIdx= 0, bool ignoreCase= false )        const { return IndexOf( buffer, length, needle, needle ? strlen( needle ) : 0, startIdx, ignoreCase );       }


        /** ****************************************************************************************
         *  Search the given char in the Buffer.
         *
         * @param c            The char to search for.
         * @param startIdx     The index to start the search at. Optional and defaults to 0.
         *
         * @return    -1 if the char is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        AWXU_API
        int            IndexOf( char c, int startIdx= 0 );


    // #############################################################################################
    // Replace, ConvertCase
    // #############################################################################################

        /** ****************************************************************************************
         *  Replace one or more occurrences of one cstring by another cstring. Along with the character
         *  pointers, the correct length of the cstrings has to be provided. For convenience, a variant
         *  of this method exists, that determines the length of the strings internally.
         *
         * @param searchStr          The cstring to be replaced.
         * @param searchStringLength The length of searchStr.
         * @param newStr             The replacement cstring.
         * @param newStringLength    The length of newString.
         * @param startIdx           The index where the search starts. Optional and defaults 0.
         * @param maxReplacements    The maximum number of replacements to perform.
         *                           Optional and defaults to std::numeric_limits<int>::max().
         * @param ignoreCase         If true, a case insensitive search is performed. Defaults to false.
         *
         * @return The number of replacements that where performed.
         ******************************************************************************************/
        AWXU_API
        int ReplaceCount( const char* searchStr, int searchStringLength,
                          const char* newStr,     int newStringLength,
                          int    startIdx= 0,         int maxReplacements= MAX_INT,
                          bool    ignoreCase= false );

        /** ****************************************************************************************
         *
         *  Replace one or more occurrences of one cstring by another cstring. The length of the cstrings
         *  is determined internally. Note: If these lengths, or one of them, are already known, for
         *  efficiency reasons it is advised to use the variant of this method that offers to provide these
         *  lengths as parameters.
         *
         *
         * @param searchStr       The cstring to be searched for.
         * @param newStr          The replacement for searchStr.
         * @param startIdx        The index where the search and replace should start.
         *                        Optional and defaults to 0.
         * @param maxReplacements The maximum number of replacements to perform. Optional and
         *                        defaults to std::numeric_limits<int>::max() .
         * @param ignoreCase      If true, a case insensitive search is performed. Defaults to false.
         *
         *
         * @return The number of replacements that where performed.
         ******************************************************************************************/
        int ReplaceCount( const char* searchStr,
                          const char* newStr,
                          int    startIdx= 0, int maxReplacements= MAX_INT,
                          bool    ignoreCase= false )
        {
            return ReplaceCount(    searchStr,    searchStr ? strlen( searchStr ) : 0,
                                       newStr,       newStr ? strlen(    newStr ) : 0,
                                    startIdx, maxReplacements,
                                    ignoreCase );
        }

        /** ****************************************************************************************
         *
         *  Replace one or more occurrences of a std::string by another std::string. Returns the number
         *  of replacements.
         *
         *
         * @param searchStr       The std::string to be searched for.
         * @param newStr          The replacement std::string for searchStr.
         * @param startIdx        The index where the search and replace should start.
         *                        Optional and defaults to 0.
         * @param maxReplacements The maximum number of replacements to perform. Optional and
         *                        defaults to std::numeric_limits<int>::max() .
         * @param ignoreCase      If true, a case insensitive search is performed. Defaults to false.
         *
         *
         * @return The number of replacements that where performed.
         ******************************************************************************************/
        int ReplaceCount( const std::string& searchStr,
                          const std::string& newStr,
                          int    startIdx= 0, int maxReplacements= MAX_INT,
                          bool    ignoreCase= false )
        {
            return ReplaceCount(    searchStr.c_str(), searchStr.size(),
                                       newStr.c_str(),      newStr.size(),
                                    startIdx, maxReplacements,
                                    ignoreCase );
        }

        /** ****************************************************************************************
         *
         *  Replace one or more occurrences of a %AString by another %AString. Returns the number
         *  of replacements.
         *
         *
         * @param searchStr       The %AString to be searched for.
         * @param newStr          The replacement %AString for searchStr.
         * @param startIdx        The index where the search and replace should start.
         *                        Optional and defaults to 0.
         * @param maxReplacements The maximum number of replacements to perform. Optional and
         *                        defaults to std::numeric_limits<int>::max() .
         * @param ignoreCase      If true, a case insensitive search is performed. Defaults to false.
         *
         *
         * @return The number of replacements that where performed.
         ******************************************************************************************/
        int ReplaceCount( const AString& searchStr,
                          const AString& newStr,
                          int    startIdx= 0, int maxReplacements= MAX_INT,
                          bool    ignoreCase= false )
        {
            return ReplaceCount(    searchStr.Buffer(), searchStr.Length(),
                                       newStr.Buffer(),      newStr.Length(),
                                    startIdx, maxReplacements,
                                    ignoreCase );
        }

        /** ****************************************************************************************
         *
         *  Replace one or more occurrences of one cstring by another cstring. Along with the character
         *  pointers, the correct length of the cstrings has to be provided. For convenience, a variant
         *  of this method exists, that determines the length of the strings internally.
         *  Note: To receive the number of replacements, see alternative method #ReplaceCount().
         *
         *
         * @param searchStr          The cstring to be replaced.
         * @param searchStringLength The length of searchStr.
         * @param newStr             The replacement cstring.
         * @param newStringLength    The length of newString.
         * @param startIdx           The index where the search starts. Optional and defaults to 0.
         * @param maxReplacements    The maximum number of replacements to perform.
         *                           Optional and defaults to std::numeric_limits<int>::max().
         * @param ignoreCase         If true, a case insensitive search is performed. Defaults to false.
         *
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Replace( const char* searchStr, int searchStringLength,
                          const char* newStr,     int newStringLength,
                          int    startIdx= 0, int maxReplacements= MAX_INT,
                          bool    ignoreCase= false )
        {
            ReplaceCount( searchStr,    searchStringLength,
                             newStr,       newStringLength,
                          startIdx,        maxReplacements,
                          ignoreCase );
            return *this;
        }

        /** ****************************************************************************************
         *
         *  Replace one or more occurrences of one cstring by another cstring. The length of the cstrings
         *  is determined internally. Note: If these lengths, or one of them, are already known, for
         *  efficiency reasons it is advised to use the variant of this method that offers to provide these lengths
         *  as parameters. Also, to receive the number of replacements, see alternative method #ReplaceCount().
         *
         *
         * @param searchStr        The cstring to be replaced.
         * @param newStr           The replacement cstring.
         * @param startIdx         The index where the search starts. Optional and defaults
         *                         to 0.
         * @param maxReplacements  The maximum number of replacements to perform. Optional and
         *                         defaults to std::numeric_limits<int>::max() .
         * @param ignoreCase       If true, a case insensitive search is performed. Defaults to false.
         *
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Replace( const char* searchStr,
                          const char* newStr,
                          int startIdx= 0, int maxReplacements= MAX_INT,
                          bool    ignoreCase= false )
        {
            ReplaceCount( searchStr, newStr, startIdx, maxReplacements, ignoreCase );
            return *this;
        }

        /** ****************************************************************************************
         *
         *  Replace one or more occurrences of a std::string by another std::string.
         *  Note: To receive the number of replacements, see alternative method #ReplaceCount().
         *
         *
         * @param searchStr         The std::string to be replaced.
         * @param newStr            The replacement std::string for searchStr.
         * @param startIdx          The index where the search starts. Optional and defaults
         *                          to 0.
         * @param maxReplacements   The maximum number of replacements to perform. Optional and
         *                          defaults to std::numeric_limits<int>::max() .
         * @param ignoreCase        If true, a case insensitive search is performed. Defaults to false.
         *
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Replace( const std::string& searchStr,
                          const std::string& newStr,
                          int startIdx= 0, int maxReplacements= MAX_INT,
                          bool ignoreCase= false )
        {
            ReplaceCount( searchStr.c_str(), searchStr.size(),
                             newStr.c_str(),    newStr.size(),
                          startIdx, maxReplacements,
                          ignoreCase );
            return *this;
        }

        /** ****************************************************************************************
         *
         *  Replace one or more occurrences of one %AString by another %AString. Along with the character
         *  pointers, the correct length of the cstrings has to be provided. For convenience, a variant
         *  of this method exists, that determines the length of the strings internally.
         *  Note: To receive the number of replacements, see alternative method #ReplaceCount().
         *
         *
         * @param searchStr         The %AString to be replaced.
         * @param newStr            The replacement %AString.
         * @param startIdx          The index where the search starts. Optional and defaults
         *                          to 0.
         * @param maxReplacements   The maximum number of replacements to perform. Optional and
         *                          defaults to std::numeric_limits<int>::max() .
         * @param ignoreCase        If true, a case insensitive search is performed. Defaults to false.
         *
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AString& Replace( const AString& searchStr,
                          const AString& newStr,
                          int    startIdx= 0, int maxReplacements= MAX_INT,
                          bool    ignoreCase= false )
        {
            ReplaceCount( searchStr.Buffer(),    searchStr.Length(),
                             newStr.Buffer(),       newStr.Length(),
                          startIdx,                maxReplacements,
                          ignoreCase );
            return *this;
        }

        /** ****************************************************************************************
         *  Converts all or a region of characters in the Buffer to upper or to lower case.
         *
         * @param toUpper         If true, conversion to upper case is performed, to lower else.
         * @param regionStart     Start of the substring to be converted. Defaults to 0
         * @param regionLength    Length of the substring to be converted. Defaults to
         *                        std::numeric_limits<int>::max().
         *
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        AWXU_API
        AString& ConvertCase( bool toUpper, int regionStart= 0, int regionLength= MAX_INT );


    // #############################################################################################
    // ToString, Equals
    // #############################################################################################

        /** ****************************************************************************************
         *     Creates a std::string containing a copy of the contents of this %AString.
         *
         * @return A std::string that represents this object.
         ******************************************************************************************/
        std::string  ToString()                    const { return ToString( 0, length ); }

        /** ****************************************************************************************
         *  Creates a std::string containing a copy of a region of the contents of this
         *    %AString.
         *
         * @param regionStart    The start index of the region in this to create the std::string from.
         * @param regionLength   (Optional) The maximum length of the region to create the std::string from.
         *                       Defaults to std::numeric_limits<int>::max().
         *
         * @return A string that represents the specified sub region of this object.
         ******************************************************************************************/
        AWXU_API
        std::string  ToString( int regionStart, int regionLength= MAX_INT ) const;

        /** ****************************************************************************************
         *  Copies the contents of this %AString into the given std::string.
         *
         * @param result        A result std::string to copy the contents of this %AString into.
         * @param appendMode    Optional: If true, any contents in the result is preserved. Otherwise
         *                      such content gets replaced (default).
         * @return The (modified) result that was provided (for concatenation of calls).
         ******************************************************************************************/
        std::string& ToString( std::string& result, bool appendMode= false ) const { return ToString( result, 0, length, appendMode ); }

        /** ****************************************************************************************
         *  Copies a region of the contents of this %AString into the given std::string.
         *
         * @param result        A result std::string to copy the specified region into.
         * @param regionStart   The start index of the region to be copied.
         * @param regionLength  The maximum length of the region to be copied.
         *                      Defaults to std::numeric_limits<int>::max().
         * @param appendMode    Optional: If true, any contents in the result is preserved. Otherwise
         *                      such content gets replaced (default).
         *
         * @return The (modified) std::string& result that was provided (for concatenation of calls).
         ******************************************************************************************/
        AWXU_API
        std::string& ToString( std::string& result, int regionStart, int regionLength= MAX_INT, bool appendMode= false ) const;

        /** ****************************************************************************************
         * Reads a long from the %AString at the given position. The given index is increased to point to
         * first character that is not a number. If no number is found a the given index, zero is returned
         * and the provided index is not increased.
         *
         * @param idx   The start point from where the long value is tried to be read. This is provided
         *              as reference and will be increased if an integer is found.
         *
         * @return  The parsed value. In addition, the input parameter startIdx is moved to point to the
         *             first character behind any found long number.
         ******************************************************************************************/
        int64_t        ToLong( int& idx ) const;

        /** ****************************************************************************************
         * Reads an integer from the %AString at the given position. The given index is increased to point to
         * first character that is not a number. If no number is found a the given index, zero is returned
         * and the provided index is not increased.
         *
         * @param idx   The start point from where the long value is tried to be read. This is provided
         *              as reference and will be increased if an integer is found.
         *
         * @return  The parsed value. In addition, the input parameter startIdx is moved to point to the
         *             first character behind any found long number.
         ******************************************************************************************/
        int            ToInt( int& idx ) const        {    return (int) ToLong( idx );     }


    // #############################################################################################
    //  Static string utilities
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Checks if a given pointer to a std::string is null or if the referenced std::string has a
         * length of zero.
         * @param s  The std::string pointer to check.
         * @return   Returns true if given std::string is empty or nullptr.
         ******************************************************************************************/
        static bool IsNullOrEmpty( const std::string* s )    { return s == nullptr || s->size() == 0; }

        /** ****************************************************************************************
         * Checks if a given pointer to a %AString is null or if the referenced %AString has a length of zero.
         * @param ms   The %AString pointer to check.
         * @return  Returns true if given %AString pointer is empty or nullptr.
         ******************************************************************************************/
        static bool IsNullOrEmpty( const AString*     ms )    { return ms == nullptr || ms->Length() == 0; }

        /** ****************************************************************************************
         * Checks if a given pointer to a cstring is null or or if the referenced character array has a
         * length of zero.
         * @param cs   The cstring pointer to check.
         * @return  Returns true if given %AString pointer is empty or nullptr.
         ******************************************************************************************/
        static bool IsNullOrEmpty( const char*         cs )    { return cs == nullptr || *cs == '\0'; }

}; // class AString


/** ************************************************************************************************
 *  A simple class template specializing %AString. All it does, is providing an internal character
 *  array as the default buffer to %AString. If an instance of this class is allocated on the stack,
 *  all allocation and deallocation is performed in O(1).
 *  If an instance of this class is allocated on the heap (using new), then still some performance
 *  improvements apply, because besides the class object itself, no second memory allocation is
 *  performed<p>
 *
 *  If during the use of an instance of this class a bigger buffer is needed, such buffer will get
 *  allocated from the heap. This means, the use of this class is safe and no restrictions apply.
 *  Of-course, for performance critical code sections, the predefined size should be chosen large
 *  enough to allow the internal buffer to survive the use.<br>
 *  %AString optionally raises a one-time
 *  \ref aworx::util::AWXU::Warning "AWXU::Warning" if an external buffer is replaced by a
 *  new (heap) allocation. (From an %AString perspective, this classes' internal buffer is an
 *  external one). For more information,  see
 *  \ref aworx::util::AString::SetExternalBuffer "AString::SetExternalBuffer".<p>
 *
 *  For commonly used sizes, some convenient typedefs exists:
 *  See #AString16, #AString32 ... #AString1K.
 **************************************************************************************************/
template <const size_t BUFFER_SIZE>
class AStringPreAlloc : public AString
{
    // #############################################################################################
    //  protected fields
    // #############################################################################################
    protected:
        /// The internal buffer with size specified by the template parameter
        char         internalBuf[BUFFER_SIZE];

    // #############################################################################################
    //  Constructors/Destructor
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  Constructs an object by invoking the AString(0) parent constructor (which prevents the
         *  allocation of a buffer) and then sets our internal character array as an external buffer
         *  to AString.
         ******************************************************************************************/
        AStringPreAlloc()
        : AString(0)
        {
            SetExternalBuffer( internalBuf, BUFFER_SIZE );
        }

        /** ****************************************************************************************
         *  Constructor copying a substring of another AString.
         *
         * @param src            The reference to the %AString to copy from.
         * @param regionStart    The start of the region in ms to append. Defaults to 0.
         *                       Defaults to std::numeric_limits<int>::max().
         * @param regionLength   The length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
        AStringPreAlloc( const AString& src, int regionStart= 0, int regionLength= MAX_INT )
        : AString(0)
        {
            SetExternalBuffer( internalBuf, BUFFER_SIZE );
            Append( src.Length(), src.Buffer(), regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Constructor copying a substring of another AString, given as pointer.
         *
         * @param src            The pointer to the %AString to copy from.
         * @param regionStart    The start of the region in ms to append. Defaults to 0.
         *                       Defaults to std::numeric_limits<int>::max().
         * @param regionLength   The length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
        AStringPreAlloc( const AString* src, int regionStart= 0, int regionLength= MAX_INT )
        : AString(0)
        {
            SetExternalBuffer( internalBuf, BUFFER_SIZE );
            if ( src != nullptr )
                Append( src->Length(), src->Buffer(), regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Constructor copying a substring of a std::string.
         *
         * @param src            The reference to std::string to copy from.
         * @param regionStart    The start of the region in s to append. Defaults to 0.
         * @param regionLength   The length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
        AStringPreAlloc( const std::string& src, int regionStart= 0, int regionLength= MAX_INT)
        : AString(0)
        {
            SetExternalBuffer( internalBuf, BUFFER_SIZE );
            Append( src.size(), src.c_str(), regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Constructor copying a substring of a std::string, given as pointer.
         *
         * @param src            The pointer to the std::string to copy from.
         * @param regionStart    The start of the region in s to append. Defaults to 0.
         * @param regionLength   The length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
        AStringPreAlloc( const std::string* src, int regionStart= 0, int regionLength= MAX_INT)
        : AString(0)
        {
            SetExternalBuffer( internalBuf, BUFFER_SIZE );

            if ( src != nullptr )
                Append( src->size(), src->c_str(), regionStart, regionLength );
        }


        /** ****************************************************************************************
         *  Constructor copying a substring of a char *.
         *
         * @param src            The source Mutable StringBuilder to copy.
         * @param regionStart    The start of the region in ms to append. Defaults to 0.
         * @param regionLength   The length of the region in src to append.
         *                       Defaults to std::numeric_limits<int>::max().
         ******************************************************************************************/
        AStringPreAlloc( const char* src, int regionStart= 0, int regionLength= MAX_INT )
        : AString(0)
        {
            SetExternalBuffer( internalBuf, BUFFER_SIZE );
            Append( -1, src, regionStart, regionLength );
        }

    // #############################################################################################
    //  operators (we have to reimplement the assign operators)
    // #############################################################################################
    public:
        /// Sets the contents of this to equal the given cstring
        AString&    operator=( const char*          src)    { Clear();  return Append( src ); }

        /// Sets the contents of this to equal the given AString
        AString&    operator=( const AString&       src)    { Clear();  return Append( src ); }

        /// Sets the contents of this to equal the given std::string
        AString&    operator=( const std::string    src)    { Clear();  return Append( src ); }

};

// #################################################################################################
//  Fixed sized preallocated AStrings
// #################################################################################################


    /// A shortcut to \ref aworx::util::AStringPreAlloc "AStringPreAlloc" providing an internal preallocated buffer of size 16.
    typedef             AStringPreAlloc< 16>             AString16;

    /// A shortcut to \ref aworx::util::AStringPreAlloc "AStringPreAlloc" providing an internal preallocated buffer of size 32.
    typedef             AStringPreAlloc< 32>             AString32;

    /// A shortcut to \ref aworx::util::AStringPreAlloc "AStringPreAlloc" providing an internal preallocated buffer of size 64.
    typedef             AStringPreAlloc< 64>             AString64;

    /// A shortcut to \ref aworx::util::AStringPreAlloc "AStringPreAlloc" providing an internal preallocated buffer of size 128.
    typedef             AStringPreAlloc<128>             AString128;

    /// A shortcut to \ref aworx::util::AStringPreAlloc "AStringPreAlloc" providing an internal preallocated buffer of size 256.
    typedef             AStringPreAlloc<256>             AString256;

    /// A shortcut to \ref aworx::util::AStringPreAlloc "AStringPreAlloc" providing an internal preallocated buffer of size 512.
    typedef             AStringPreAlloc<512>             AString512;

    /// A shortcut to \ref aworx::util::AStringPreAlloc "AStringPreAlloc" providing an internal preallocated buffer of size 1024.
    typedef             AStringPreAlloc<1024>            AString1K;


}} // namespace / EOF

// temporary defines
#undef MAX_INT
#if MAX_INT___WAS_DEFINED
    #pragma pop_macro("MAX_INT")
#endif

#endif // HPP_AWORX_UTIL_ASTRING
