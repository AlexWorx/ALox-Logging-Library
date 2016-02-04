// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/**@file*///<- needed for Doxygen include of the using statements at the end of the file

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_AWORX_LIB_ALIB) || defined(HPP_AWORX_LIB_STRINGS_ASPREALLOC)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_LIB_STRINGS_ASPREALLOC
#define HPP_AWORX_LIB_STRINGS_ASPREALLOC 1


// #################################################################################################
// forwards
// #################################################################################################
namespace aworx {
namespace           lib {
namespace                   strings {


/** ************************************************************************************************
 *  A simple class template specializing
 *  \ref aworx::lib::strings::ASAlloc "ASAlloc". All it does, is providing an internal character
 *  array of \e 'templated' as the default buffer to \b %ASAlloc. If an instance of this class
 *  is allocated on the stack, allocation and deallocation is performed in \e O(1).
 *  If an instance of this class is allocated on the heap (using new), then still some performance
 *  improvements apply, because besides the class object itself, no second memory allocation for
 *  the string buffer is performed.
 *
 *  If during the use of an instance of this class a larger buffer is needed, such buffer will get
 *  allocated from the heap. This means, the use of this class is safe and no restrictions apply.
 *  Of-course, for performance critical code sections, the predefined size should be chosen large
 *  enough to allow the internal buffer to survive the use.<br>
 *
 *  In debug compilations of ALib, parent class #ASAlloc optionally raises an one-time warning
 *  (using
 *  \ref aworx::lib::Report::DoReport "Report::DoReport") if an external buffer is replaced by a
 *  new (heap) allocation. (From an \b %ASAlloc perspective, this classes' internal buffer is an
 *  external one). For more information,  see
 *  \ref aworx::lib::strings::ASAlloc::SetBuffer "ASAlloc::SetBuffer".<p>
 *
 *  \note For commonly used sizes, some convenient typedefs exists in namespace aworx.
 *        (See \ref CPP_AWORX_NS_SHORTCUTS "Type Shortcuts in the aworx Namespace".)
 *        Type definitions are #String16, #String32, #String64 ... #String1K, #String2K, #String4K.
 *  <p>
 *
 *  \note The move constructor of this class will copy the buffer of the movable \b %ASAlloc or
 *        \b %ASPreAlloc object rather, instead of moving it. This is to keep the statically allocated
 *        buffer in place. Only if the contents does fit into our TCapacity, the buffer is '\e stolen'
 *        (and an one-time warning is issued in debug compilations).<br>
 *        Like parent class \b %ASAlloc, this class does not provide move assignment. See
 *        \ref aworx::lib::strings::ASAlloc "ASAlloc" for the rational of this design decision.
 *
 * @tparam TCapacity The capacity of the buffer allocated inside the class with member #preAllocBuf.
 **************************************************************************************************/
template <int TCapacity>
class ASPreAlloc : public ASAlloc
{
    // #############################################################################################
    //  protected fields
    // #############################################################################################
    protected:
        /// The internal buffer with size specified by the template parameter \p TCapacity.
        char         preAllocBuf[TCapacity];

    // #############################################################################################
    //  Constructors/Destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Constructs an empty \b %ASPreAlloc with an internal buffer of size \p TCapacity.
         ******************************************************************************************/
        constexpr
        ASPreAlloc()
        : ASAlloc( preAllocBuf, TCapacity )
        , preAllocBuf {""}  // MSC 2015 wants that, but generates no code with "" as init value
        {}

        /** ****************************************************************************************
         *  Copy constructor.
         *  Constructs an \b ASPreAlloc<TCapacity> and invokes
         *  \ref aworx::lib::strings::ASAlloc::Apply "ASAlloc::Apply"
         *  to copy the contents of parameter \p copy.
         * @param copy The object to copy the contents from.
         ******************************************************************************************/
        ASPreAlloc(const ASPreAlloc& copy)
        : ASAlloc( preAllocBuf, TCapacity )
        {
            Apply( copy );
        }

        /** ****************************************************************************************
         * Move constructor.
         * @param move The object to copy.
         ******************************************************************************************/
        ASPreAlloc( ASPreAlloc&& move) noexcept
        : ASAlloc( preAllocBuf, TCapacity )
        {
            // we copy when contents fits or move has an external buffer
            if ( move.Length() < TCapacity  ||  !move.HasInternalBuffer() )
            {
                Apply( move );
                return;
            }

            ALIB_WARN_ONCE_IF_NOT( false,
                             "Replacing preallocated buffer on move construction.",
                             *this, ReplaceExternalBuffer );

            // copy values
            buffer=     move.buffer;
            length=     move.length;
            capacity=   move.capacity;

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
         * Move constructor.
         * @param move The object to copy.
         ******************************************************************************************/
        ASPreAlloc( ASAlloc&& move) noexcept
        : ASAlloc( preAllocBuf, TCapacity )
        {
            // we copy when contents fits or move has an external buffer
            if ( move.length < TCapacity  ||  !move.HasInternalBuffer() )
            {
                Apply( move );
                return;
            }

            ALIB_WARN_ONCE( "Replacing preallocated buffer on move construction.",
                            *this, ReplaceExternalBuffer );

            // copy values
            buffer=     move.buffer;
            length=     move.length;
            capacity=   move.capacity;

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
         * Constructs the object and uses parents' method \e %Apply
         * to append objects of arbitrary
         * type.
         * See \ref aworx::lib::strings::ASAlloc::Apply "ASAlloc::Apply" for more information
         * about which types are supported and how external, user defined types can be made
         * compatible to this implicit constructor.
         *
         * @param src  The source to take the buffer and length from of template type T.
         ******************************************************************************************/
        template <class T>
        ASPreAlloc (const  T& src )
        : ASAlloc( preAllocBuf, TCapacity )
        {
            Apply( src );
        }

        /** ****************************************************************************************
         * Constructor copying a region of an \ref aworx::lib::strings::AS "AS".
         * @param src          The reference to the \b %AS to copy from.
         * @param regionStart  The start of the region in \p src to append.
         * @param regionLength The length of the region in \p src to append.
         *                     Defaults to CString::MaxLen.
         ******************************************************************************************/
        ASPreAlloc(const AS& src, int regionStart, int regionLength= CString::MaxLen )
        : ASAlloc( preAllocBuf, TCapacity )
        {
            if ( src.IsNotNull() )
                _( src, regionStart, regionLength );
        }


    // #################################################################################################
    //  Inherit operator=
    // #################################################################################################

        /** ****************************************************************************************
         * The <em>default C++ assign operator</em> (<code>ClassT & operator=(const ClassT &)</code>).<br>
         * Copies the contents of the given object \p copy.
         * Other assignment operators are inherited (with <em>using</em> statement) from
         * parent \b %ASAlloc.
         *
         * @param  copy  The object to copy the contents from.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        ASPreAlloc<TCapacity>& operator= (const ASPreAlloc&  copy)
        {
            if ( copy.IsNull())
            {
                SetNull();
                return *this;
            }
            Clear();
            return (ASPreAlloc<TCapacity>&) Append<false>( copy.Buffer(), copy.Length() );
        }

        using ASAlloc::operator=;
}; // class ASPreAlloc

// #################################################################################################
// Namespace methods
// #################################################################################################
    /** ********************************************************************************************
     * Partial specialization of struct <em>IsTerminatable</em> which is designed to test objects of
     * arbitrary type if it is allowed in the case that they are not terminated,
     * to write termination character '\0' into their character buffer at the first position after
     * their last character.
     * This implementation inherits from std::true_type for all sizes of type
     * ASPreAlloc<TCapacity> as they always reserve one character in their buffers' capacity.
     **********************************************************************************************/
    template<const int TCapacity>   struct  IsTerminatable<ASPreAlloc<TCapacity>>   : public std::true_type { };

}}} // namespace aworx::lib::strings

#endif // HPP_AWORX_LIB_STRINGS_ASPREALLOC
