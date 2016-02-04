// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/**@file*///<- needed for Doxygen include of the typedefs at the end of the file

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_AWORX_LIB_ALIB) || defined(HPP_AWORX_LIB_STRINGS_ASTRING)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_LIB_STRINGS_ASTRING
#define HPP_AWORX_LIB_STRINGS_ASTRING 1


#if !defined (_STDLIB_H) && !defined(_INC_STDLIB)
    #include <stdlib.h>
#endif


// conditional expression is constant for using our constant template parameters to select
// checking vs. non-checking method versions
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4127 )
#endif


namespace aworx {
namespace           lib {
namespace                   strings {


// #################################################################################################
// forwards
// #################################################################################################
class ASAlloc;
template<typename T>   int ApplyTo   ( ASAlloc& , const T );
template<typename T>   int ApplyTo_NC( ASAlloc& , const T );



/** ************************************************************************************************
 * Specializes class
 * \ref aworx::lib::strings::ASTerminatable "ASTerminatable" to implement mutable, non-constant
 * strings using writable buffer memory.
 *
 * \note This class \b %ASAlloc, when used in source code as well as in documentations, is
 *       mostly referred to using the synonym '<b>%AString</b>'. For more information about the
 *       synonymous names of ALib string classes, refer to
 *       \ref alib_namespace_strings_class_overview "String Classes Overview" and
 *       \ref CPP_AWORX_NS_SHORTCUTS "Type Shortcuts in the aworx Namespace".
 *
 * There are two possible types of buffers:
 * - <b>Internal buffers</b><br>
 *   This is the standard case and implements a buffer that is allocated from
 *   <em>free memory</em> (aka 'the heap') that eventually grows over time and never shrinks, unless
 *   explicitly demanded by the user of the class. Those buffers are deleted when objects
 *   of this type are deleted.
 * - <b>External buffers</b><br>
 *   Set with method #SetBuffer. These buffers don't get deleted. However, if their capacity
 *   is exceeded, they will get automatically replaced by an internal buffer.
 *   (See field #ReplaceExternalBuffer to control warnings on that in debug compilation).
 *
 *<b>Construction/Destruction</b><p>
 * The following ways of construction are provided:
 * - <b>Default construction</b><br>
 *   Does not allocate a character buffer. The allocation is this way deferred to
 *   the first operation that writes data into the object. Alternatively, an external buffer
 *   can be set before such operation is invoked.
 * - <b>Construction with initial capacity</b><br>
 *   With constructor #ASAlloc(int), an initial length can be provided. This construction
 *   variant should be used, if the maximum length the object that will be reached during its
 *   lifetime is predictable, because it avoids iterative, increasing buffer allocations that
 *   otherwise would be performed until that size is reached once.
 *   Furthermore there are constructors
 * - <b>Construction with external buffers</b><br>
 *   With constructor #ASAlloc(char*, int), an external buffer is set. This constructor is
 *   protected and therefore accessible by derived classes' constructors only.
 *   This is to avoid an otherwise likely common misunderstanding  that this constructor would
 *   copy the contents of a provided cstring. For users of this class, the alternative to this
 *   constructor is using a combination of the default constructor and method #SetBuffer which
 *   has exactly the same effect.
 * - <b>Construction with strings</b><br>
 *   Constructors #ASAlloc(const T&), ASAlloc(const AS&, int, int=) and copy constructor
 *   #ASAlloc(const ASAlloc&) will allocate an internal buffer of the capacity needed
 *   and copy the contents of the given string type.
 *
 * Destruction will free internally allocated buffers.
 * \note Method #SetBuffer provides a boolean parameter that also allows to let an object of this
 *       class take control on the provided buffer, namely delete it in the destructor. In this
 *       case, a buffer set with this method is considered an internal buffer, rather than an
 *       external one.
 *
 * \anchor alib_namespace_strings_astring_move
 *<b>Move constructor and move assignment</b><p>
 * This class provides a (noexcept) move constructor which grabs the buffer of a given movable
 * \b %ASAlloc, as long as this given object does not use an external buffer. In the latter case, the
 * contents is copied like in the copy constructor.<br>
 * This class does not provide a move assignment operator. The rational for this is that normally
 * a "more temporary" ASAlloc would be assigned to a "less temporary" one. In this case, it would
 * be not helpful to replace the allocated storage, each time.
 * \note
 *   In general, while assignment of other objects of type \b %ASAlloc is possible through
 *   #operator=(const ASAlloc&), the advised code style is to use a combination of #Clear and
 *   append \ref _ "_()" (e.g. <em>myString._()._(otherString)</em>) to do the assignment instead.
 *   This leads to exactly the same result as long as the \b %ASAlloc that is assigned is not \e nulled.<br>
 * \note
 *   In the case that it is \e nulled, using the assignment operator will set this object also
 *   to \e nulled state, hence dispose any currently allocated buffer. This, for most cases is not
 *   what is wanted.
 *
 * \anchor alib_namespace_strings_astring_write_access
 * <b>Write Access to the Buffer</b><p>
 * Parent class \ref aworx::lib::strings::AS "AS" holds its protected field
 * \ref aworx::lib::strings::AS::buffer "AS::buffer" in an anonymous C++ union of two pointers,
 * one typed <em>const char*</em> and the other <em>char*</em>.
 * This class exposes the non-constant buffer pointer of that union with method #VBuffer.
 * This allows users of this class to <em>freely</em> operate on the buffer with any <em>C</em>
 * or <em>C++</em> algorithm available. Of-course, it is up to the programmer doing this to
 * keep invariants that this class naturally constitutes intact.
 *
 * In addition to this, a bunch of methods allow the modification of characters.
 * #operator[] is returning a reference to a char in contrast to the same operator defined
 * in class \b %AS. This allows assignments of values when using an object with this operator as
 * an lvalue.
 *
 * \anchor  alib_namespace_strings_astring_nullable
 * <b>Nullable AStrings</b><p>
 * As discussed in the namespace documentation (\ref alib_namespace_strings_nullable)
 * parent class
 * \ref aworx::lib::strings::AS "AS" provides an interface to detect <em>\e nulled</em> objects.
 * This concept is duly implemented in this class. An object of type #ASAlloc is <em>\e nulled</em>
 * when no internal buffer is allocated or external buffer is set.
 *
 * If default constructed, constructed  with zero size, a null pointer, or any other string type
 * object which is \e nulled, no buffer is created and hence the new object is in <em>\e nulled</em>
 * state and inherited method
 * aworx::lib::strings::AS::IsNull "IsNull" will return \c true for that object.
 * Consequently, it makes a difference if an \b %ASAlloc is constructed using <em>ASAlloc()</em> or
 * <em>ASAlloc(\"\")</em>.
 * This allows to differentiate between \e nulled AStrings and empty \b %AStrings, which is quite handy
 * in certain situations. An object that was filled already can be reset to represent null by
 * either assigning a nullptr, by invoking
 * \ref SetBuffer "SetBuffer(0)" or by invoking #SetNull on the
 * instance. (See also methods #IsNull, #IsNotNull and #Capacity.)
 * The methods #Equals, #CompareTo and the overloaded comparison #operator== and
 * #operator!= allow nullptr comparisons. e.g. a <em>\e nulled</em> \b %ASAlloc equals to another
 * <em>\e nulled</em> \b %ASAlloc but not to an empty but not <em>\e nulled</em> ASAlloc.
 *
 * To make this more clear, note the following <b>sample code</b> which does not throw an assertion:
 * \snippet "DOX_ALIB_ASTRING.cpp"    DOX_ALIB_ASTRING_NULLED
 *
 * \note
 *   - As mentioned above, to avoid loosing an allocated buffer, use a combination of
 *     #Clear and append \ref _ "_()" to perform assignments with other string types instead of
 *     using one of the assignment operators (#operator=). No check for <em>\e nulled</em> string
 *     is needed when appending them to an object of this type.
 *
 *   - Even if an \b %ASAlloc object is \e nulled, inherited method #ToCString will return a
 *     (zero terminated) valid empty <em>char*</em>.
 *     This has the advantage that in many situations the null-state is not
 *     needed to be handled (for those cases where the difference between a \e nulled and an empty
 *     string is irrelevant).
 *
 * <b>Applying Objects to AStrings</b><p>
 * The concept of appending things to a string is generalized in the C++
 * implementation of this class and named <em>applying</em> instead. While applying string
 * types is the same as appending string types in other language versions of ALib, the
 * '<em>application</em>' of non-string types allows flexible and well readable code design.
 *
 * The central mechanism used to apply arbitrary types is similar to what is used by class
 * \ref aworx::lib::strings::AS "AS" and the partially specialized template function
 * \ref aworx::lib::strings::ToAS "ToAS".
 * By implementing a new specialization of partially specialized template
 *  - function \ref aworx::lib::strings::ApplyTo( ASAlloc& target, const T src ) "ApplyTo" and
 *  - class \ref aworx::lib::strings::IsApplicable "IsApplicable"
 *
 * it is possible to apply objects of 'external', user defined types to objects of this class.
 *
 * These partly specialized templates are used by this classes' method #Apply. Because this
 * method, although declared <em>public</em>, has a more internal character, in standard
 * situations its invocation is performed indirectly through methods:
 * - Constructor #ASAlloc(const T&)
 * - Operator operator <<(const T&)
 * - Method #_(const T&) (which is a synonym for <em>operator << </em> but allowing non-checked invocations)
 * - Operator operator=(const T&)
 *
 * \anchor alib_namespace_strings_astring_application_vs_interface
 * <b>Application Instead of Explicit Interface Methods</b><p>
 * Various methods that exist in the implementations of class \b %ASAlloc in different programming
 * languages versions of ALib, are missing in this C++ implementation.
 * Here, they have been replaced by  the concept of <em>applying</em> types.
 * The following provides a list of predefined applicable types found in ALib:
 *
 * - Characters (<em>char</em>) and character string  <em>([const] char*)</em> types will
 *   be appended.
 * - Wide characters (<em>wchar_t</em>) and wide character strings  <em>([const] wchar_t*)</em>
 *   types. They will be converted to encoded multi-byte character strings according
 *   to the currently set locale and appended. (See
 *   \ref aworx::lib::ALIB::Init "ALIB::Init" for more information about setting locale and
 *   \ref aworx::lib::strings::AS::ToWString "AS::ToWString" for converting in the other
 *   direction.)
 * - Plain types <em>int32_t</em>, <em>uint32_t</em>, <em>int64_t</em>, <em>uint64_t</em>,
 *   <em>float</em> and <em>double</em>. Their value will be converted to
 *   string representations using static object
 *   \ref aworx::lib::strings::NumberFormat::Global "NumberFormat::Global" and appended.
 * - Plain type <em>bool</em> appending the string literal '\c true' respectively
 *   '\c false'
 *
 * - Class \ref aworx::lib::strings::Format "Format", with public inner classes
 *   - \ref aworx::lib::strings::Format::Field   "Format::Field"
 *   - \ref aworx::lib::strings::Format::Tab     "Format::Tab"
 *   - \ref aworx::lib::strings::Format::Int32   "Format::Int32"
 *   - \ref aworx::lib::strings::Format::UInt32  "Format::UInt32"
 *   - \ref aworx::lib::strings::Format::Int64   "Format::Int64"
 *   - \ref aworx::lib::strings::Format::UInt64  "Format::UInt64"
 *   - \ref aworx::lib::strings::Format::Double  "Format::Double"
 *
 * <b>Insert, Replace and Delete</b><p>
 * The following insert, delete and replace operations are provided:
 * - #InsertAt To insert a string at an arbitrary position.
 * - #InsertChars To insert a quantity of characters at an arbitrary position.
 * - \ref ReplaceSubstring(const AS&, int,int) "ReplaceSubstring" To replace a substring with a new string .
 * - \ref ReplaceRegion(char, int,int) "ReplaceRegion" To replace a substring with a given character.
 * - #SearchAndReplace to search all occurrences of a substring and replace by a different string.
 * - #Delete To delete an arbitrary  substring.
 * - #DeleteStart To delete n characters from the start.
 * - #DeleteEnd To delete n characters from the end.
 *
 **************************************************************************************************/
class ASAlloc : public ASTerminatable
{
    // #############################################################################################
    // friends
    // #############################################################################################

        // this is (unfortunately) needed to allow him stealing our buffer in the move constructor
        // of our new friend
        template <const int TCapacity> friend class ASPreAlloc;

    /** ############################################################################################
     * @name Debug Features
     ##@{ ########################################################################################*/


        #if defined(ALIB_DEBUG_STRINGS)
        protected:
            /**
             * Used to check if previous grow request was exactly what is now the length.<br>
             * This is available only if \ref ALIB_DEBUG_STRINGS is set.
             */
            int             debugLastAllocRequest                                                =0;

            /**
             * Used to check if previous grow request was exactly what is now the length.<br>
             * This is available only if \ref ALIB_DEBUG_STRINGS is set.
             */
            bool            debugBufferWithMagicBytePadding                                  =false;

            /**
             *  Checks this objects' state. This method is internally invoked with almost
             *  every other method of this class, but only if compilation symbol
             *  \ref ALIB_DEBUG_STRINGS is defined.
             */
        public:
            void    _dbgCheck()   const;

        #endif

        /**
         *  If \c true, an one-time warning (using
         *  \ref aworx::lib::Report::DoReport "Report::DoReport")
         *  will be issued when an external buffer, whose life-cycle is not controlled by this
         *  instance gets replaced by a new allocation. This normally shall not
         *  happen, but still might be wanted or at least taken into account.
         *
         *  E.g. for \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" objects, that
         *  sometimes may grow more than average, this warning may be disabled after creation
         *  of an instance.
         *
         *  The warning will be issued only once per instance unless the warning gets re-enabled
         *
         *  \note This field can not be accessed directly (For technical reasons, it is
         *        differently declared than stated here in the source documentation).<br>
         *        To change the field use macros
         *        - \ref ALIB_WARN_ONCE_PER_INSTANCE_ENABLE(myinstance, ReplaceExternalBuffer) and
         *        - \ref ALIB_WARN_ONCE_PER_INSTANCE_DISABLE(myinstance, ReplaceExternalBuffer)
         *
         *        where \p myinstance is a reference to the object in question).
         */
        #if defined(IS_DOXYGEN_PARSER)
            bool                              ReplaceExternalBuffer= true;
        #else
            ALIB_WARN_ONCE_PER_INSTANCE_DECL( ReplaceExternalBuffer, true );
        #endif


    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /**
         *  The current size of the buffer excluding the trailing '\0'. If no buffer is allocated,
         *  this is is 0. If an external Buffer is used and if this buffer is not under our control
         *  (we must not delete it), then the size of such buffer is stored as a negative value.
         */
        int                 capacity;

    protected:
        /** ****************************************************************************************
         * Constructs an \b %ASAlloc with the given external buffer.
         * The given buffers' life-cycle is considered to be managed externally.<br>
         * This constructor is protected and provided for derived classes that dispose about
         * their own buffer.
         *
         * \note
         *   Protected access was given to this method also to avoid misunderstandings that this
         *   constructor is not for providing copyable string data. If the functionality of this
         *   constructor is needed, it can simply be imitated by
         *   - default construction and
         *   - immediate invocation of #SetBuffer(char*, int, int, enums::Responsibility).
         *
         * @param extBuffer       The external buffer to use.
         * @param extBufferSize   The capacity of the given buffer.
         ******************************************************************************************/
        constexpr
        explicit ASAlloc( char* extBuffer, int extBufferSize )
        : ASTerminatable( extBuffer, 0)
        , capacity  (- (extBufferSize - 1))
        {}

    /** ############################################################################################
     * @name Constructors, Destructor and Assignment
     ##@{ ########################################################################################*/
    public:
        /** ****************************************************************************************
         *   Constructs an empty, \e nulled \b %ASAlloc (does not allocate a buffer).
         ******************************************************************************************/
        explicit
        constexpr
        ASAlloc()
        : ASTerminatable()
        , capacity  (0)
        {}

        /** ****************************************************************************************
         * Constructor allocating a specific given buffer size
         * (plus one for a potential termination character).
         *
         *  \note This constructor is useful for \b %ASAlloc objects whose minimum future string length
         *        is predictable to avoid recurring incremental allocations up to the known
         *        minimum size.
         *
         * @param initialCapacity  The size of the buffer that is allocated.
         ******************************************************************************************/
        explicit
        ASAlloc( int initialCapacity )
        : ASTerminatable()
        , capacity  (0)
        {
            SetBuffer( initialCapacity );
        }

        /** ****************************************************************************************
         * Copy constructor that allocates memory and copies the contents of the given object.
         * @param copy The object to copy.
         ******************************************************************************************/
        explicit
        ASAlloc( const ASAlloc& copy)
        : ASTerminatable()
        , capacity  (0)
        {
            Apply( copy );
        }

        /** ****************************************************************************************
         * Move constructor.
         * See \ref alib_namespace_strings_astring_move "Move Constructor and Move Assignment"
         * for details.
         * @param move The object to move.
         ******************************************************************************************/
        ASAlloc(ASAlloc&& move) noexcept
        : ASTerminatable()
        {
            // given move object has external buffer: we have to copy
            if ( !move.HasInternalBuffer() )
            {
                capacity=   0;
                Apply( move );
                return;
            }

            // copy values
            buffer=         move.buffer;
            length=         move.length;
            capacity=       move.capacity;

            // prevent moved objects' destructor to delete buffer
            move.capacity=   0;

            // in debug mode, more copying and more destructor prevention is needed
            #if defined(ALIB_DEBUG_STRINGS)
                debugLastAllocRequest=           move.debugLastAllocRequest;
                debugIsTerminated=               move.debugIsTerminated;
                debugBufferWithMagicBytePadding= move.debugBufferWithMagicBytePadding;

                move.buffer=  nullptr;
                move.length=  0;
            #endif
        }

        /** ****************************************************************************************
         *  Constructs the object and uses <em>Apply</em> to append objects of arbitrary
         *  type.
         *  See \ref Apply for more information.
         *
         * @tparam T      The type of parameter \p source.
         * @param  src    The source of type T to append.
         ******************************************************************************************/
        template <class T>
        explicit
        ASAlloc (const  T& src )
        : ASTerminatable()
        , capacity  (0)
        {
            Apply( src );
        }

        /** ****************************************************************************************
         *  Constructor copying a region of an
         * \ref aworx::lib::strings::AS "AS".
         * @param src          The reference to the the \b %AS to copy from.
         * @param regionStart  The start of the region in \p src to append.
         * @param regionLength The length of the region in \p src to append.
         *                     Defaults to CString::MaxLen.
         ******************************************************************************************/
        explicit
        ASAlloc(const AS& src, int regionStart, int regionLength= CString::MaxLen )
        : ASTerminatable()
        , capacity  (0)
        {
            _<true>( src, regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Destructs an \b %ASAlloc object
         ******************************************************************************************/
        ~ASAlloc() noexcept
        {
            ALIB_STRING_DBG_CHK(this)
            if ( HasInternalBuffer() )
                #if !defined(ALIB_DEBUG_STRINGS)
                    delete[] buffer;
                #else
                    delete[] (buffer - (debugBufferWithMagicBytePadding ? 16 : 0) );
                #endif
        }

        /** ****************************************************************************************
         * The <em>default</em> C++ assign operator (ClassT & operator=(const ClassT &) ).
         * Copies the contents of the given object \p copy.
         * \note There is no move assignment operator defined.
         *       In general, it might be advisable to use a combination of #Clear and #_(const T&)
         *       instead of using assignments.
         *       See \ref alib_namespace_strings_astring_move "Move Constructor and Move Assignment"
         *       for an explanation.
         *
         * @param  copy  The object to copy the contents from.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        ASAlloc& operator= (const ASAlloc&  copy)
        {
            if ( copy.IsNull() )
            {
                SetNull();
                return *this;
            }

            Clear().Apply( copy );
            return  *this;
        }

        /** ****************************************************************************************
         *  Clears this object and uses <em>Apply</em> to append objects of arbitrary type.
         *  See \ref Apply for more information.
         *
         * \note In general, it might be advisable to use a combination of #Clear and #_(const T&)
         *       instead of using assignments.
         *       See \ref alib_namespace_strings_astring_move "Move Constructor and Move Assignment"
         *       for an explanation.
         *
         * @tparam TCheck Defaults to \c true which is the normal invocation mode.
         *                If \c \<false\> is added to the method name, checks are omitted as documented.
         * @tparam T      The type of parameter \p source.
         * @param  op     The source of type T to append.
         *
         * @return    \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <class T>
        ASAlloc& operator= (const  T& op )
        {
            Clear();
            if ( Apply<true>( op ) < 0 )
                SetNull();
            return *this;
        }


    /** ############################################################################################
     * @name Memory allocation and buffer access
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         *  Resizes the internal buffer to meet exactly the given size.
         *
         *  The following rules apply:
         *  - The string represented by this instance is copied to the new buffer.
         *    If this is larger than the new buffer size, the string is cut at the end to fit.
         *  - If the desired new size is 0, then the currently allocated buffer will be released
         *    and the objects state is \e \e nulled.
         *  - If the current buffers' life-cycle is managed externally (e.g. was set using
         *    #SetBuffer(char*,int,int, enums::Responsibility)
         *    with parameter \p responsibility being \c Responsibility::KeepWithSender), this method
         *    will replace the buffer by a new one, even if the new requested size is the same as
         *    the external buffers' size. In other words, the only case when this method does not
         *    replace the current buffer is when the current buffers' life-cycle is (already)
         *    internally managed and it has the same size than what is requested.
         *  - In the C++ version of ALib, the \c true allocation size is + 1 of what is given
         *    in parameter \p newSize. This is is to duly apply to a constraint given by parent
         *    #ASTerminatable.
         *
         *  \note Any methods of this class that extend the length of the string represented, will
         *        invoke this method if the current buffer size is not sufficient.
         *        If a future string length of an \b %ASAlloc is predictable, then it is advisable
         *        to allocate such size prior to start appending the data to avoid recurring
         *        allocations (performance optimization).
         *  <p>
         *
         *  \note
         *    If currently an external buffer is set (this means a buffer whose life-cycle
         *    is not controlled by this instance), an one-time warning per instance is
         *    issued.
         *    To enable/disable this warning use macro
         *    - \ref ALIB_WARN_ONCE_PER_INSTANCE_ENABLE(theInstanceInQuestion, ReplaceExternalBuffer) or
         *    - \ref ALIB_WARN_ONCE_PER_INSTANCE_DISABLE(theInstanceInQuestion, ReplaceExternalBuffer).

         *
         * @param newSize    The new size for the allocation buffer.
         ******************************************************************************************/
        ALIB_API  void    SetBuffer( int newSize );



        /** ****************************************************************************************
         *  This methods replaces the current buffer with the one provided.
         *
         *  The following rules apply:
         *  - If a nullptr is provided still, the current buffer is released.
         *  - If provided buffer is not nullptr, its size provided with parameter \p extBufferSize
         *    has to be at least 1 for
         *    providing the space for a termination character.
         *  - After the operation, #Capacity will report \p extBufferSize \p -1.
         *  - Optional parameter \p responsibility can be used to pass the responsibility for the
         *    deletion of the buffer to this object.
         *  - The length of the content provided with parameter \p extLength must not exceed
         *    the value of parameter \p extBufferSize \p -1.
         *  - In no event any data of an existing buffer is copied into the new one. The rationale
         *    here is that in most use cases, this is not needed. Should this be desired,
         *    then the contents has to be copied manually, e.g. by invoking
         *    <code>strcpy( extBuffer, target.ToCString() )</code> prior to invoking this method.
         *
         * @param extBuffer       The external buffer to use.
         * @param extBufferSize   The size of the given buffer.
         * @param extLength       The length of any content located in the given buffer that should
         *                        be used.
         *                        Has to be smaller or equal to extBufferSize -1 to preserve
         *                        space for a trailing '\0'.
         * @param responsibility  If \c Responsibility::Transfer, the given buffer will be deleted
         *                        by this object when a new buffer is set or it is deleted itself.
         *                        Defaults to \c Responsibility::KeepWithSender which denotes that
         *                        the life-cycle of the given external buffer is managed elsewhere.
         ******************************************************************************************/
        ALIB_API
        void     SetBuffer( char*                 extBuffer,
                            int                   extBufferSize,
                            int                   extLength          = 0,
                            enums::Responsibility responsibility     = enums::Responsibility::KeepWithSender );



        /** ****************************************************************************************
         * Sets a new length for this string.
         *
         * The <em>checking version</em> (\p TCheck=\c true) of this method must be used to shorten
         * the string only. If the new length is requested to be higher than the current length,
         * a one time warning is issued. The warning occurs only once for the first
         * occurrence of an invocation of this method with such wrong parameter.
         * To enable/disable this warning use macros
         * - \ref ALIB_WARN_ONCE_PER_TYPE_ENABLE(AS, SetLengthLonger) or
         * - \ref ALIB_WARN_ONCE_PER_TYPE_DISABLE(AS, SetLengthLonger).
         *
         * The <em>non-checking</em> version may be used to increase the length. Here, an
         * assertion is only raised, when the length is negative or greater than the
         * current #Capacity. Therefore, the non-checking version <em>has to</em> be used when
         * external change an \c %AStrings' size.
         * E.g. specializations of function
         * \ref aworx::lib::strings::ApplyTo "ApplyTo" regularly do that.<p>
         * Furthermore, if \ref ALIB_DEBUG_STRINGS is defined, the non-checking version applies
         * \ref  ALIB_STRING_DBG_UNTERMINATE to this object, after the new length was
         * set. Only the, a \ref ALIB_STRING_DBG_CHK is executed.
         *
         * @tparam TCheck    Defaults to \c true which is the normal invocation mode.
         *                   If \c \<false\> is added to the method name, no parameter checks are
         *                   performed.
         * @param newLength  The new length of the \b %ASAlloc. Must be between 0 and the current
         *                   length.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        void    SetLength( int newLength )
        {
            if ( TCheck )
            {
                ALIB_STRING_DBG_CHK(this)
                ALIB_WARN_ONCE_IF_NOT( newLength <= length, "Increase requested", *this, SetLengthLonger )
                ALIB_ASSERT_ERROR(     newLength >= 0,      "Negative length" );
                if ( newLength >= 0 && newLength < length )
                    length= newLength;
                ALIB_STRING_DBG_UNTERMINATE(*this, 0)
            }
            else
            {
                // in the non-checking version, the debug check must be done only after setting the
                // length.
                ALIB_ASSERT_ERROR( newLength >= 0 && newLength <= Capacity(),
                   (ASAlloc("NC: Length out of range. capacity=") << capacity
                                          <<  ", newLength="  << newLength)        )
                length= newLength;
                ALIB_STRING_DBG_UNTERMINATE(*this, 0)
                ALIB_STRING_DBG_CHK(this)
            }
        }

        /** ****************************************************************************************
         * Ensures that the capacity of the internal buffer meets or exceeds the actual length
         * plus the given growth value.
         *
         * @param spaceNeeded  The desired growth of the length of the string represented by this.
         ******************************************************************************************/
        inline
        void     EnsureRemainingCapacity( int spaceNeeded )
        {
            #if !defined(ALIB_DEBUG_STRINGS)
                if ( Capacity() < length + spaceNeeded )
                    GrowBufferAtLeastBy( spaceNeeded );
            #else
                ALIB_ASSERT_ERROR( length <= debugLastAllocRequest,
                    "Previous allocation request was too short" );
                debugLastAllocRequest= length + spaceNeeded;

                if ( Capacity() < length + spaceNeeded )
                    GrowBufferAtLeastBy( spaceNeeded );

                ALIB_STRING_DBG_UNTERMINATE(*this, spaceNeeded)
            #endif
        }

        /** ****************************************************************************************
         * Increases the allocation size at least by the value provided.
         *
         * @param minimumGrowth    The desired minimum growth of length.
         ******************************************************************************************/
        void     GrowBufferAtLeastBy( int minimumGrowth )
        {
            int capacity= Capacity();

            // big enough?
            ALIB_ASSERT_WARNING ( capacity < length + minimumGrowth,
                                      "Unnecessary invocation of Grow()" );

            // first allocation? Go with given growth as size
            if (capacity == 0 )
            {
                SetBuffer( minimumGrowth );
                return;
            }

            // calc new size: in general grow by 50%
            int newSize= capacity + (capacity / 2);
            if ( newSize < length + minimumGrowth )
                newSize+= minimumGrowth;

            if ( newSize < 16 )
                newSize= 16;

            SetBuffer( newSize );
        }

        /** ****************************************************************************************
         *  The current size of the internal buffer (this is excluding the trailing '\0'character)
         *  which is reserved to terminate the represented character array if needed.
         *  In other words, the internal memory allocated is the size returned here plus one.
         *
         * @return The size of the allocated buffer.
         ******************************************************************************************/
        inline
        int   Capacity()  const
        {
            return  capacity >= 0   ?  capacity
                                    : -capacity;
        }

        /** ****************************************************************************************
         *  Returns \c true, if the buffer was allocated by this class itself. If the buffer was
         *  set using #SetBuffer(char*,int,int,enums::Responsibility) with parameter \p responsibility
         *  given as \c Responsibility::KeepWithSender (and not automatically replaced, yet,
         *  because it became too small) then \c false is returned.
         *  \note Derived class
         *        \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" will report \c false here.
         *        This sounds wrong on the first sight, as the buffer is allocated by an 'internal'
         *        member. But from an ASAlloc's perspective, class <em>ASPreAlloc</em> works on
         *        an 'external' buffer.
         *
         * @return \c true if the buffer is internally allocated and will be deleted with the
         *         deletion of this object. False otherwise.
         ******************************************************************************************/
        inline
        bool HasInternalBuffer()
        {
            return  capacity > 0;
        }

        /** ****************************************************************************************
         * Invokes \ref SetBuffer "SetBuffer(0)".
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        void           SetNull()
        {
            SetBuffer( 0 );
        }

    /** ############################################################################################
     * @name Writable Buffer Access
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * The internal buffer character array provided as non constant char pointer.
         * \see Chapter
         * \ref alib_namespace_strings_astring_write_access "Write Access to the Buffer"
         * of the reference documentation of this class.
         *
         * @return The internal buffer array.
         ******************************************************************************************/
        inline
        char*          VBuffer()         const       { return vbuffer;    }

        /** ****************************************************************************************
         * Sets the character at the given index. A range check is performed. If this fails,
         * nothing is done.
         *
         * \note
         *   The C++ language would allow to declare this method const, as it does not
         *   manipulate the data of the class itself but a character in the buffer pointer.<br>
         *   In exclamation cases, to manipulate the contents of <em>const %ASAlloc</em>, use
         *   method VBuffer() like in the following sample:
         *   \snippet "DOX_ALIB_ASTRING.cpp" DOX_ALIB_ASTRING_MODIFY_CONST_BUFFER
         *   <p>
         *
         * @tparam TCheck Performs a range check on the given index and a check for illegal setting
         *                of termination character '\0' anywhere else but at idx==length.
         * @param idx     The index of the character to write.
         * @param c       The character to write.
         ******************************************************************************************/
        template<bool TCheck =true>
        inline
        void        SetCharAt( int idx, char c )
        {
            ALIB_ASSERT_ERROR(  c != '\0' || idx==length, "Can't write character '\0'" );
            if (TCheck)
            {
                if  ( (idx >= 0 && idx < length) || ( c =='\0' && idx == length ) )
                    *(vbuffer + idx )= c;
            }
            else
            {
                ALIB_ASSERT_ERROR(  idx >= 0 && idx < length, "NC: Index out of range" );
                *(vbuffer + idx )= c;
            }
        }

        /** ****************************************************************************************
         * Provides read/write access to single characters.
         * Overwrites
         * \ref aworx::lib::strings::AS::operator[] "AS::operator[]"
         * returning a reference to a char which allows assignments of values when using an
         * object with this operator as lvalue.
         *
         * \attention
         *   Unlike other operator methods in the family of string classes of ALib,  which are doing
         *   parameter checks (in this case a range check), this operator does <em>not</em> do a
         *   check!
         *   The rationale is that, no reference to a character can be given if \p op is out
         *   of range.<br>
         *   This way, this method is equivalent to methods #SetCharAt<false> and #CharAt<false>.
         *   For safe access to characters in the buffer use #SetCharAt and #CharAt
         *   (with template parameter \p TCheck being \c true).
         *
         * @param op The index of the character within this objects' buffer.
         * @returns If the character contained (or, if lvalue the one to set).
         ******************************************************************************************/
        char&    operator[] (int  op)
        {
            ALIB_ASSERT_ERROR( op >= 0  && op < length , "Index out of bounds" );
            return vbuffer[op];
        }


    /** ############################################################################################
     * @name Insert and Delete
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Clear the Buffer. Same as \ref Delete "Delete(0, Length())" (but of-course, without
         * internal region checks).
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        ASAlloc&    Clear()
        {
            ALIB_STRING_DBG_CHK(this)

            length=            0;
            ALIB_STRING_DBG_UNTERMINATE(*this, 0)
            return *this;
        }

        /** ****************************************************************************************
         * Clear the Buffer. Same as #Clear(), really just a synonym to allow short code in
         * alignment with the various "Apply" methods named <em>_(type src)</em>
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        ASAlloc&    _()
        {
            ALIB_STRING_DBG_CHK(this)

            length=            0;
            ALIB_STRING_DBG_UNTERMINATE(*this, 0)
            return *this;
        }

        /** ****************************************************************************************
         * Inserts the given strings at given position.
         * If the position is not between 0 and the length of the target, nothing is inserted.
         *
         * \note
         *   To insert a string with replacing a different one at the same time, use
         *   \ref ReplaceSubstring(const AS&,int,int) "ReplaceSubstring(src, pos, regionLength)".
         *
         * @tparam TCheck   Chooses checking or non-checking implementation. Defaults to true.
         * @param  src      The \b %AS to insert.
         * @param  pos      The position to insert \p src.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        ASAlloc&   InsertAt( const AS& src, int pos )
        {
            ALIB_STRING_DBG_CHK(this)
            int srcLength= src.Length();
            if ( TCheck )
            {
                if ( srcLength == 0 || pos < 0 || pos > length )
                    return *this;
            }
            else
                ALIB_ASSERT_ERROR( srcLength > 0 && pos >=0 && pos <= length,
                                   "NC: Illegal parameters" );

            EnsureRemainingCapacity( srcLength );

            // move content and fill new region
            memmove( vbuffer + pos + srcLength,
                     vbuffer + pos,
                     length -  pos                  );
            memcpy ( vbuffer + pos,  src.Buffer(), srcLength );
            length+= srcLength;

            ALIB_STRING_DBG_UNTERMINATE(*this, 0)
            return *this;
        }

        /** ****************************************************************************************
         * Inserts the given character n-times at a given position.
         * If the given position is out of range, nothing is inserted.
         *
         * The non-checking version does not check the position. However the default value
         * which is appending at the end) is still verfied.
         *
         * @param c     The character to insert \p qty times.
         * @param qty   The quantity of characters to insert.
         * @param pos   The index in this object where \p c is inserted \p qty times.
         *              Defaults to \b CString::MaxLen.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        ASAlloc&   InsertChars( char c, int qty, int pos= CString::MaxLen )
        {
            if (pos == CString::MaxLen )
                pos= length;

            if( TCheck )
            {
                if ( qty <= 0 || pos < 0 ||  pos > length )
                    return *this;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    ALIB_ASSERT_ERROR(  qty >= 0,                   "NC: Illegal qunatity given" )
                    ALIB_ASSERT_ERROR(  pos >= 0 && pos <= length,  "NC: Illegal position given" )
                #endif
            }

            EnsureRemainingCapacity( qty );

            // move content ?
            if ( pos != length )
            {
                memmove( vbuffer + pos + qty,
                         vbuffer + pos,
                         length - pos         );
            }

            //set
            memset ( vbuffer + pos, c, qty );
            SetLength<false>( length +  qty );
            return *this;
        }

        /** ****************************************************************************************
         * Replaces a region in this object by a given string.
         * If the region does not fit to this object, then nothing is done.
         *
         * The non-checking version does not adjust the region.
         *
         * @tparam TCheck   Chooses checking or non-checking implementation. Defaults to true.
         * @param src             The replacement string.
         * @param regionStart     The start of the region.
         * @param regionLength    The length of the region.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        ASAlloc&   ReplaceSubstring( const AS& src, int regionStart, int regionLength )
        {
            ALIB_STRING_DBG_CHK(this)
            int srcLength= src.Length();

            if( TCheck )
            {
                if (    regionStart  < 0
                    ||  regionStart + regionLength > length
                    ||  regionLength < 0
                    ||  srcLength    < 0)
                        return *this;
            }
            else
            {
                ALIB_ASSERT_ERROR( src.IsNotNull(), "NC: Source string is null"  );
                #if defined(ALIB_DEBUG)
                    int rs=  regionStart;
                    int rl=  regionLength;
                    AdjustRegion( rs, rl );
                    ALIB_ASSERT_ERROR(  rs == regionStart && rl == regionLength, "NC: Invalid region given" )
                #endif
            }

            int lenDiff= srcLength - regionLength;

            // check buffer size
            if ( lenDiff > 0 )
                EnsureRemainingCapacity( lenDiff );

            // move content
            if ( lenDiff != 0 )
                memmove( vbuffer + regionStart + srcLength,
                         vbuffer + regionStart + regionLength,
                         length  - (regionStart + regionLength)       );

            // copy the source
            memcpy( vbuffer + regionStart,  src.Buffer(), srcLength );
            length+= lenDiff;

            ALIB_STRING_DBG_UNTERMINATE(*this, 0)
            return *this;
        }

        /** ****************************************************************************************
         * Replaces a region in the string with the given character.
         * The region is adjusted to fit into the current length. In other words, the length
         * of this instances remains the same.
         *
         * \note
         *   To replace a region with a single character (by shrinking the region to this character)
         *   use
         *   \ref ReplaceSubstring(const AS&,int,int) "ReplaceSubstring( String(c), regionStart, regionLength)".
         *
         * The non-checking version does not adjust the region.
         *
         * @tparam TCheck   Chooses checking or non-checking implementation. Defaults to true.
         * @param regionStart     The start of the region
         * @param regionLength    The length of the region
         * @param c               The character to set in the region.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        ASAlloc&   ReplaceRegion( char c, int regionStart, int regionLength )
        {
            if( TCheck )
            {
                if ( AdjustRegion( regionStart, regionLength ) )
                    return *this;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    int rs=  regionStart;
                    int rl=  regionLength;
                    AdjustRegion( rs, rl );
                    ALIB_ASSERT_ERROR(  rs == regionStart && rl == regionLength, "NC: Invalid region given" )
                #endif
            }
            memset ( vbuffer + regionStart, c, regionLength );
            return *this;
        }


        /** ****************************************************************************************
         *  Deletes a region from the Buffer. A range check is performed and the region is cut
         *  to fit to the string.
         *
         *  The non-checking version (\p TCheck = \c false) still allows to leave parameter
         *  \p regionLength as default (respectively allows the sum of parameters
         *  \p regionStart and \p regionLength to be longer than the length of this \b %ASAlloc).
         *   In this case, this string is cut starting from index \p regionStart.
         *
         * \note See also methods #Clear, #DeleteStart and #DeleteEnd.
         *
         * @tparam TCheck       Defaults to \c true which is the normal invocation mode.
         *                      If \c \<false\> is added to the method name, no parameter checks are
         *                      performed.
         * @param regionStart   The start of the region to delete.
         * @param regionLength  The length of the region to delete. Defaults to CString::MaxLen.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true >
        inline
        ASAlloc&    Delete( int regionStart, int regionLength= CString::MaxLen  )
        {
            ALIB_STRING_DBG_CHK(this)

            int regionEnd;

            if ( TCheck )
            {
                if ( AdjustRegion( regionStart, regionLength ) )
                {
                    ALIB_STRING_DBG_UNTERMINATE(*this, 0)
                    return *this;
                }

                // delete over the end?
                if ( (regionEnd= regionStart + regionLength) >= length )
                {
                    length= regionStart;
                    ALIB_STRING_DBG_UNTERMINATE(*this, 0)
                    return *this;
                }
            }
            else
            {
                ALIB_ASSERT_ERROR(      regionStart  >= 0
                                        &&  regionStart  <= length
                                        &&  regionLength >= 0,
                                        "NC: Illegal arguments" );

                // delete over the end?
                if ( (regionEnd= regionStart + regionLength) >= length )
                {
                    length= regionStart;
                    ALIB_STRING_DBG_UNTERMINATE(*this, 0)
                    return *this;
                }
            }

            // both versions
            memmove( vbuffer + regionStart,
                     vbuffer + regionEnd,
                     length  - regionEnd + 1);
            length-= regionLength;
            ALIB_STRING_DBG_UNTERMINATE(*this, 0)
            return *this;
        }

        /** ****************************************************************************************
         *  Deletes the given number of characters from the start of the string.
         *
         * @tparam TCheck       Defaults to \c true which is the normal invocation mode.
         *                      If \c \<false\> is added to the method name, no parameter checks are
         *                      performed.
         *
         * @param regionLength  The length of the region at the start to delete.
         *
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true >
        inline
        ASAlloc&                 DeleteStart( int regionLength )
        {
            ALIB_STRING_DBG_CHK(this)

            if ( TCheck )
            {
                if ( regionLength <= 0 )
                {
                    ALIB_STRING_DBG_CHK(this)
                    ALIB_STRING_DBG_UNTERMINATE(*this, 0)
                    return *this;
                }
                if ( regionLength >= length )
                    return Clear();
            }

            ALIB_ASSERT_ERROR(  regionLength >=0 && regionLength <= length,
                                    "NC: Region length out of range" );

            memmove( vbuffer,
                     buffer + regionLength,
                     length - regionLength + 1);
            length-= regionLength;
            ALIB_STRING_DBG_UNTERMINATE(*this, 0)
            return *this;
        }

        /** ****************************************************************************************
         *  Deletes the given number of characters from the end of the string.
         *
         * @tparam TCheck       Defaults to \c true which is the normal invocation mode.
         *                      If \c \<false\> is added to the method name, no parameter checks are
         *                      performed.
         * @param regionLength  The length of the region at the end to delete.
         *
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true >
        inline
        ASAlloc&                DeleteEnd( int regionLength  )
        {
            ALIB_STRING_DBG_CHK(this)

            if (TCheck)
            {
                if ( regionLength > 0 )
                {
                    if ( regionLength >= length )
                        length= 0;
                    else
                        length-= regionLength;
                }
            }
            else
            {
                ALIB_ASSERT_ERROR(  regionLength >=0 && regionLength <= length,
                                        "NC: Region length out of range" );
                length-= regionLength;
            }

            ALIB_STRING_DBG_UNTERMINATE(*this, 0)
            return *this;
        }

        /** ****************************************************************************************
         * All characters defined in given set are removed at the beginning and at the end of this
         * string.
         *
         * \see Method #TrimAt to remove whitespaces at arbitrary places in the string.
         *
         * @param trimChars   Pointer to a zero terminated set of characters to be omitted.
         *                    Defaults to \ref DefaultWhitespaces.
         * @return  \c *this to allow concatenated calls.
         ******************************************************************************************/
        ALIB_API
        ASAlloc& Trim( const ASTerminatable& trimChars= DefaultWhitespaces );

        /** ****************************************************************************************
         * All characters defined in given set at, left of and right of the given index
         * are removed from the string.
         *
         * @param index       The index to perform the trim operation at. Has to be between zero
         *                    and <em>length -1</em>.
         * @param trimChars   Pointer to a zero terminated set of characters to be omitted.
         *                    Defaults to \ref DefaultWhitespaces.
         * @return  \c *this to allow concatenated calls.
         ******************************************************************************************/
        ALIB_API
        ASAlloc& TrimAt( int index, const ASTerminatable& trimChars= DefaultWhitespaces );

        /** ****************************************************************************************
         * All characters defined in given set are removed at the beginning of this string.
         *
         * \see Method #TrimAt to remove whitespaces at arbitrary places in the string.
         *
         * @param trimChars   Pointer to a zero terminated set of characters to be omitted.
         *                    Defaults to \ref DefaultWhitespaces.
         * @return  \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        ASAlloc& TrimStart( const ASTerminatable& trimChars= DefaultWhitespaces )
        {
            return TrimAt( 0, trimChars );
        }

        /** ****************************************************************************************
         * All characters defined in given set are removed at the end of this string.
         *
         * \see Method #TrimAt to remove whitespaces at arbitrary places in the string.
         *
         * @param trimChars   Pointer to a zero terminated set of characters to be omitted.
         *                    Defaults to \ref DefaultWhitespaces.
         * @return  \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        ASAlloc& TrimEnd( const ASTerminatable& trimChars= DefaultWhitespaces )
        {
            return TrimAt( length - 1, trimChars );
        }

    /** ############################################################################################
     * @name Append and apply
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Appends a portion of a cstring.
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c \<false\> is added to the method name, no nullptr check is done
         *                     on parameter \p src. Also, this object would not loose a \e nulled state
         *                     when the given cstring portion is empty.
         * @param  src         A pointer to the cstring to append.
         * @param  srcLength   The length of the portion of the cstring to append.
         *
         * @return    \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true >
        inline
        ASAlloc& Append( const char* src, int srcLength )
        {
            ALIB_STRING_DBG_CHK(this)

            if( TCheck )
            {
                if (!src)
                    return *this;

                // check empty
                if ( srcLength == 0 )
                {
                    // set "un-nulled"
                    if ( buffer == nullptr )
                        SetBuffer( 15 );

                    return *this;
                }
            }
            else
            {
                ALIB_STRING_DBG_CHK(this)
                ALIB_ASSERT_ERROR( src,  "NC: nullptr passed" )
            }

            EnsureRemainingCapacity( srcLength );
            memcpy( vbuffer + length,  src, srcLength );
            length+= srcLength;

            return *this;
        }

        /** ****************************************************************************************
         *  This generic method allows to apply or 'use' this object with different types of other
         *  objects.
         *  If the given type is a string type, then 'apply' means to append the string.<br>
         *  In detail, the implementation of this method proceeds as follows:
         *  - If a pointer type is detected and value is nullptr, nothing is done and -1 is returned.
         *    This allows the caller to react on nullptr values (e.g. the assignment operator,
         *    would set this object to \e nulled state if -1 was returned).
         *  - If a reference or pointer type of ASLiteral<TLength> or a character string literal
         *    (respectively a fixed size char array) is provided, its contents is appended
         *    to this \b %ASAlloc and the appended length is returned. (The append operation in this case
         *    is implemented using fast inline method
         *    \ref aworx::lib::strings::ASLiteral::Copy "ASLiteral::Copy")
         *  - If above is \c false, using TMP mechanics, the given parameter \p src of type \p T
         *    is converted into a const reference of the original type.<br>
         *    E.g. if a <em>std::string* src</em> was given, it is converted to
         *    <em>const std::string& src</em>.
         *  - This const reference is then passed to partially implemented template function
         *    \ref ApplyTo(ASAlloc& , const T).<br>
         *  - If a matching (partially implemented) template method is found, this method
         *    defines what 'applying' of an object of this type means.
         *  - The default implementation of
         *    \ref ApplyTo(ASAlloc&,const T) determines if \p src is of type AS or derived
         *    from that. If yes, the contents of such \b %AS is appended.
         *  - Furthermore, the default implementation determines if an AS was constructible from
         *    the given \p src object (using TMP 'method'
         *    \ref aworx::lib::strings::ToASDefined "ToASDefined".
         *
         *  See \ref ApplyTo( ASAlloc&,const T) for information on how to implement
         *  a supporting template method to allow the application of user defined types.
         *
         *  \note A static assertion tries to detect unsupported types at compile time. However,
         *        there might be a few types not fetched by this static assert.
         *        In this case an ALIB_WARNING is raised at runtime and 0 is returned.
         *
         * <b>Usage</b><p>
         *  This method not directly used by standard user code. However, indirectly it is used
         *  through:
         *  - constructor ASAlloc(const T& src)
         *  - assignment \ref operator=(const T& src)
         *  - apply operator <<(const T& src).
         *  - apply method _(const T& src)
         *
         *  which therefore each provide huge flexibility in their use.
         *
         * <b>Built-in Applicable Types</b><p>
         * For a list of Bult-in typse that are applicable using this method, respectively the
         * methods listed in the previous section, see
         * \ref alib_namespace_strings_astring_application_vs_interface "Application Instead of Explicit Interface Methods".
         *
         * <b>Non-checking version</b><p>
         * If template parameter \p TCheck is provided as \c false on invocation, two things are
         * omitted:
         * - There is no check for nullptr objects (attention!)
         * - If this is a \e nulled \b %ASAlloc object, and the length of the given parameter \p src
         *   to append is zero (e.g. an empty string), this object would not loose
         *   its \e nulled state. In other words, \e nulled strings keep being \e nulled if empty objects
         *   are appended when invocating this method with \p TCheck= \c false.<p>
         * \note The one and only motivation for using the non-checking version of this method is
         *       to improve performance in critical code sections.
         *
         * \note This method's description may sound (and the code may look) like having quite
         *       some runtime overhead. However, due to TMP, there is no overhead involved with
         *       this mechanism, in respect to the alternative of having overloaded apply methods
         *       implemented.
         *
         * <b>Sample</b><p>
         *  Besides implementations of <em>ApplyTo</em> for various types like integer or double,
         *  ALib provides class \ref aworx::lib::strings::Format "Format" having public
         *  inner classes with simple constructors that are useful to pass to the methods
         *  listed above like in the following sample:
         *
         *  \snippet "DOX_ALIB_ASTRING.cpp"     DOX_ALIB_ASTRING_FORMAT
         *
         *  The output will be:
         *
         *  \snippet "DOX_ALIB_ASTRING_FORMAT.txt"     OUTPUT
         *
         * @tparam TCheck Defaults to \c true which is the normal invocation mode.
         *                If \c \<false\> is added to the method name, checks are omitted as documented.
         * @tparam T      The type of parameter \p source.
         * @param  src    The source of type T to append.
         *
         * @return -1 if the given object represents a \e nulled string. Otherwise 0 or positive
         *         value is returned (indicating the number of characters that were appended,
         *         but not necessarily correct). Depends on the implementation of the template
         *         method \ref ApplyTo( ASAlloc&,const T) which is invoked in turn.
         ******************************************************************************************/
        template <bool TCheck= true, class T>
        int Apply(const  T& src )
        {
            ALIB_STRING_DBG_CHK(this);

            // nullptr ?
            if( std::is_same<T, decltype(nullptr)>::value )
                return -1;


            //---------- single character? ----------
            if( std::is_same<char, typename std::remove_cv<T>::type> ::value  )
            {
                char c= *(char*) &src;
                if ( TCheck && c == '\0' )
                    return -1;

                EnsureRemainingCapacity( 1 );
                vbuffer[ length++ ]= c;
                ALIB_STRING_DBG_UNTERMINATE(*this, 0);
                return 1;
            }

            //---------- single wide character? ----------
            if( std::is_same<wchar_t, typename std::remove_cv<T>::type> ::value  )
            {
                wchar_t wc= *(wchar_t*) &src;
                if ( TCheck && wc == L'\0' )
                    return -1;

                int mbLength;
                #if defined(_WIN32)
                    #pragma warning( push )
                    #pragma warning( disable : 4996 )


                    //does not work need utf8 encoding
                    //mblength= wctomb_s( &mbLength, vbuffer + length, 16, wc);
                    //mbLength= wctomb( nullptr, wc );
                    //mbLength= wctomb( vbuffer + length, wc );
                    EnsureRemainingCapacity( MB_LEN_MAX * 2);
                    mbLength= WideCharToMultiByte( CP_UTF8, NULL, &wc, 1,  vbuffer + length, MB_LEN_MAX * 2, NULL, NULL );
                    if ( mbLength <= 0 )
                    {
                        ALIB_DEBUG_CODE( int error= GetLastError(); )
                        ALIB_WARNING_AS(
                           "ASAlloc: Cannot convert wide character string to UTF-8. (Error: "
                            << (   error == ERROR_INSUFFICIENT_BUFFER    ? "ERROR_INSUFFICIENT_BUFFER"
                                :  error == ERROR_INVALID_FLAGS          ? "ERROR_INVALID_FLAGS."
                                :  error == ERROR_INVALID_PARAMETER      ? "ERROR_INVALID_PARAMETER"
                                :  error == ERROR_NO_UNICODE_TRANSLATION ? "ERROR_NO_UNICODE_TRANSLATION"
                                                                         : (String32()._( error )).ToCString())
                            << ')'   )
                    }
                    #pragma warning( pop )
                #else
                    EnsureRemainingCapacity( MB_CUR_MAX + 1);
                    mbLength= wctomb( vbuffer + length, wc );
                #endif

                if ( mbLength <= 0 )
                {
                    ALIB_WARNING( "Cannot convert WC to MBC." );
                    return 0;
                }

                length+= mbLength;
                ALIB_STRING_DBG_UNTERMINATE(*this, 0);
                return mbLength;
            }

            // Define result and pod type
            int result= -1;
            using TPod= typename std::remove_cv     <
                        typename std::remove_pointer<
                        typename std::remove_const  < T >::type>::type>::type;
            //ALIB::dbgTMPShowTypeInDebugger<TPod>();

            //---------- ASLiteral or string literal (or to be precise: char array of known length)? ----------
            if ( TMPLiteral<TPod>::Length >= 0 )
            {
                constexpr int TLength= TMPLiteral<TPod>::Length;
                result= TLength;
                if ( TLength > 0 )
                {
                    EnsureRemainingCapacity( (int) TLength );

                    ASLiteral<TLength>::Copy(
                            vbuffer + length,
                            TMPLiteral<TPod>::Buffer(  std::is_pointer<T>::value ? (void*) (*((T**) &src))
                                                                                 : (void*) &src )         );
                    // adjust length
                    length+= TLength;
                }
            }

            //---------- pointer type? ----------
            else if ( std::is_pointer<T>::value )
            {
                // nullptr?
                if( TCheck && (*(char**)&src) == nullptr )
                    return -1;

                // pointers to pod?
                if ( std::is_pod<TPod>::value )
                {
                    //ALIB::dbgTMPShowTypeInDebugger<TPod>();

                    // provide char/wchar as pointer
                    if (    std::is_same<TPod, char   >::value
                         || std::is_same<TPod, wchar_t>::value )
                        result= TCheck ? ApplyTo   <const    TPod*>( *this, *(TPod**)       &src )
                                       : ApplyTo_NC<const    TPod*>( *this, *(TPod**)       &src );

                    // provide char** as char*
                    else if (    std::is_same<TPod, const    char*   >::value
                              || std::is_same<TPod,          char*   >::value )
                        result= TCheck ? ApplyTo   <const    char*>( *this, **(char***)     &src )
                                       : ApplyTo_NC<const    char*>( *this, **(char***)     &src );

                    // provide wchar_t** as wchar_t*
                    else if (    std::is_same<TPod, const wchar_t*   >::value
                              || std::is_same<TPod,       wchar_t*   >::value )
                        result= TCheck ? ApplyTo   <const wchar_t*>( *this, **(wchar_t***)  &src )
                                       : ApplyTo_NC<const wchar_t*>( *this, **(wchar_t***)  &src );

                    // other types as value
                    else
                        result= TCheck ? ApplyTo   <        TPod &>( *this, (TPod&) **(int**) &src )
                                       : ApplyTo_NC<        TPod &>( *this, (TPod&) **(int**) &src );
                }

                // pointers to class types?
                else
                    result= TCheck ? ApplyTo   <const TPod &>( *this, *(TPod *&)  src )
                                   : ApplyTo_NC<const TPod &>( *this, *(TPod *&)  src );
            }

            //---------- reference type ----------
            else
            {
                // wchar[] (e.g wide string literal L"xyz")
                if (      std::is_array<TPod>::value
                      &&  std::is_same<typename std::remove_extent<TPod>::type, wchar_t>::value )
                    result= TCheck ? ApplyTo   <const wchar_t*>( *this, (wchar_t*)      &src )
                                   : ApplyTo_NC<const wchar_t*>( *this, (wchar_t*)      &src );

                // references pod types? -> by reference
                else if ( std::is_pod<TPod>::value )
                    result= TCheck ? ApplyTo   <        TPod &>( *this, (TPod&) *(int*) &src )
                                   : ApplyTo_NC<        TPod &>( *this, (TPod&) *(int*) &src );

                // references classtypes? -> by const reference
                else
                    result= TCheck ? ApplyTo   <const   TPod &>( *this, (TPod&) *(int*) &src )
                                   : ApplyTo_NC<const   TPod &>( *this, (TPod&) *(int*) &src );
            }

            //---------- conclude ----------

            // was empty?
            if ( TCheck && result == 0 && IsNull() )
            {
                // special treatment if currently nothing is allocated and a blank string ("") is added:
                // we allocate, which means, we are not a null object anymore!
                // (...also, in this case we check the src parameter)
                SetBuffer( 15 );
            }

            ALIB_STRING_DBG_UNTERMINATE(*this, 0);
            return result;
        }

        /** ****************************************************************************************
         *  Wrapper method around #Apply that returns \c *this to allow concatenated calls.
         *
         *  With template parameter TCheck equal to \c true, this method is equivalent to
         *  invoking #operator<<(const T&).
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, checks are omitted.
         * @tparam T       The type of parameter \p source.
         * @param  src     The source of type \p T to append.
         *
         * @return   \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true, class T >
        ASAlloc& _(const  T& src )
        {
            Apply<TCheck>( src );
            return *this;
        }

        /** ****************************************************************************************
         * Invokes #Append on a region of a reference of \ref aworx::lib::strings::AS "AS".
         * Accepts various types for \p src, due to the flexibility of class \b %AS to implicitly
         * construct.
         *
         * \note When using the non-checking version, parameter \p regionLength must be set
         *       explicitly to the correct value (instead of using the default value).
         *
         * @tparam TCheck        Chooses checking or non-checking implementation. Defaults to true.
         * @param  src           The \b %AS to append.
         * @param  regionStart   The start of the region in src to append.
         * @param  regionLength  The maximum length of the region in src to append.
         *                       Defaults to CString::MaxLen
         *
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        ASAlloc& _( const AS& src, int regionStart, int regionLength =CString::MaxLen )
        {
            if (TCheck)
            {
                if ( src.IsNull() )
                    return *this;
                if ( src.AdjustRegion( regionStart, regionLength ) )
                {
                    // special treatment if currently nothing is allocated and a blank string ("") is added:
                    // we allocate, which means, we are not a null object anymore!
                    // (...also, in this case we check the src parameter)
                    SetBuffer( 15 );
                    return *this;
                }
            }
            else
            {
                //---- non-checking version ----
                ALIB_ASSERT_ERROR(    regionStart >= 0 && regionLength >= 0
                                   && regionLength != CString::MaxLen // has to be separatedly checked!
                                   && regionStart +  regionLength  <= src.Length(),
                                   "NC: Invalid region given" )
            }

            // both versions
            return Append<false>( src.Buffer() + regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Invokes #Apply to append string-type objects and to generically 'apply' objects of
         *  arbitrary type.
         *  This template method wraps an invocation of #Apply, ignoring its return value
         *  and instead returns \c *this to allow concatenated calls.
         *  This operator is equivalent to invoking #_<true>(const T&).
         *  \see Method \ref Apply for more information.
         *
         * @tparam T   The type of parameter \p source.
         * @param  op  The object of type T to append.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <class T>
        inline
        ASAlloc& operator<< (const  T& op )
        {
            Apply<true>(op);
            return *this;
        }

        /** ****************************************************************************************
         *  Appends platform specific new line character(s) by appending literal string
         *  \ref aworx::lib::strings::NewLine "NewLine".
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        ASAlloc&          NewLine()
        {
            return _<false>( strings::NewLine );
        }

    /** ############################################################################################
     * @name Replace
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Replaces one or more occurrences of a terminatable string (
         * \ref aworx::lib::strings::ASTerminatable "ASTerminatable") by a replacement string.
         *
         *
         * @param needle           The terminatable string to be replaced.
         * @param replacement      The replacement string (does not need to be zero terminatable).
         * @param startIdx         The index where the search starts. Optional and defaults 0.
         * @param maxReplacements  The maximum number of replacements to perform.
         *                         Optional and defaults to CString::MaxLen.
         * @param sensitivity      Case sensitivity of the comparison.
         *                         Optional and defaults to Case::Sensitive.
         *
         * @return The number of replacements that where performed.
         ******************************************************************************************/
        ALIB_API
        int SearchAndReplace( const ASTerminatable& needle,
                              const AS&             replacement,
                              int                   startIdx            = 0,
                              int                   maxReplacements     = CString::MaxLen,
                              enums::Case           sensitivity         = enums::Case::Sensitive );

        /** ****************************************************************************************
         * Replaces one or more occurrences of a terminatable string (
         * \ref aworx::lib::strings::ASTerminatable "ASTerminatable") by a replacement string.
         * \note The difference to #SearchAndReplace is that this method returns \b *this to allow
         *       concatenated calls.
         *
         *
         * @param needle           The terminatable string to be replaced.
         * @param replacement      The replacement string (does not need to be zero terminatable).
         * @param startIdx         The index where the search starts. Optional and defaults 0.
         * @param maxReplacements  The maximum number of replacements to perform.
         *                         Optional and defaults to CString::MaxLen.
         * @param sensitivity      Case sensitivity of the comparison.
         *                         Optional and defaults to Case::Sensitive.
         *
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        ASAlloc& SearchAndReplaceAll( const ASTerminatable& needle,
                                      const AS&             replacement,
                                      int                   startIdx            = 0,
                                      int                   maxReplacements     = CString::MaxLen,
                                      enums::Case           sensitivity         = enums::Case::Sensitive )
        {
            SearchAndReplace( needle, replacement, startIdx, maxReplacements, sensitivity );
            return *this;
        }

        /** ****************************************************************************************
         * Converts all or a region of characters in the Buffer to upper case.
         *
         * @param regionStart     Start of the region to be converted. Defaults to 0
         * @param regionLength    Length of the region to be converted. Defaults to CString::MaxLen.
         *
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        ASAlloc& ToUpper( int regionStart= 0, int regionLength= CString::MaxLen )
        {
            if( TCheck )
            {
                if ( AdjustRegion( regionStart, regionLength ) )
                    return *this;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    int rs=  regionStart;
                    int rl=  regionLength;
                    AdjustRegion( rs, rl );
                    ALIB_ASSERT_ERROR(  rs == regionStart && rl == regionLength, "NC: Invalid region given" )
                #endif
            }

            // convert
            char* buf= vbuffer + regionStart;
            char* end= buf     + regionLength;
            while( buf < end )
            {
                *buf=  (char) toupper( *buf );
                buf++;
            }
            return *this;
        }


        /** ****************************************************************************************
         * Converts all or a region of characters in the Buffer to lower case.
         *
         * @param regionStart     Start of the region to be converted. Defaults to 0
         * @param regionLength    Length of the region to be converted. Defaults to CString::MaxLen.
         *
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        ASAlloc& ToLower( int regionStart= 0, int regionLength= CString::MaxLen )
        {
            if( TCheck )
            {
                if ( AdjustRegion( regionStart, regionLength ) )
                    return *this;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    int rs=  regionStart;
                    int rl=  regionLength;
                    AdjustRegion( rs, rl );
                    ALIB_ASSERT_ERROR(  rs == regionStart && rl == regionLength, "NC: Invalid region given" )
                #endif
            }

            // convert
            char* buf= vbuffer + regionStart;
            char* end= buf     + regionLength;
            while( buf < end )
            {
                *buf=  (char) tolower( *buf );
                buf++;
            }
            return *this;
        }



}; // class ASAlloc

// #################################################################################################
// Namespace methods
// #################################################################################################
    /** ********************************************************************************************
     * Partial specialization of struct <em>IsTerminatable</em> which is designed to test objects of
     * arbitrary type if it is allowed in the case that they are not terminated,
     * to write termination character '\0' into their character buffer at the first position after
     * their last character.
     * This implementation inherits from std::true_type for the type ASAlloc
     * as this class always reserves one character in its buffers' capacity.
     *
     * @returns \c true.
     **********************************************************************************************/
    template<>   struct  IsTerminatable<ASAlloc>   : public std::true_type { };


}}} // namespace aworx::lib::strings


#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
#endif // HPP_AWORX_LIB_STRINGS_ASTRING
