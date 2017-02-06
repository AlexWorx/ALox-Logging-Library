// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_STRINGS_STRINGTUPLES)
    #error "Header already included"
#endif


// then, set include guard
#ifndef HPP_ALIB_STRINGS_STRINGTUPLES
//! @cond NO_DOX
#define HPP_ALIB_STRINGS_STRINGTUPLES 1
//! @endcond NO_DOX

#include "alib/lang/memoryblocks.hpp"

namespace aworx { namespace lib { namespace strings
{

/** ************************************************************************************************
 * Variadic Template class implementing a vector of tuples whose first element is of type
 * \c ref aworx::lib::strings::String "String" and the further elements are
 * the variadic types \p TAssociatedTypes.
 *
 * When new tuples are added with method #Add, then memory for copying the provided string is
 * allocated using an internal field of type
 * \c ref aworx::lib::lang::MemoryBlock "MemoryBlock".
 * This allows to add single strings, which are allocated in bigger memory chunks.
 *
 * Note that standard vector operations, including insertions and deletions are still allowed!
 * In other words, it is allowed to store string objects which are pointing to string data that
 * is \b not allocated in the internal chunks.
 *
 * As with other types of \b %ALib, a (templated) alias name #aworx::StringTuples exists.
 * In addition, non-templated alias name #aworx::Strings is defined which has an empty
 * variadic type list. Therefore, the latter can be used to create simple string vectors without
 * associated values.
 *
 * The associated values are especially useful when the vector is sorted (e.g. using
 * \c std::sort), because such associations will be kept intact and allow referencing back
 * to whatever the strings represent.
 *
 * \note
 *   This class is new with ALib. It is not considered finished, optimized and stable in design.
 **************************************************************************************************/
template< typename... TAssociatedTypes >
class StringTuples  : public std::vector<std::tuple<String, TAssociatedTypes...>>
{
    // #############################################################################################
    // Type definitions
    // #############################################################################################
    public:
        /**
         * This is a shortcut giving the type of the concrete
         * standard <c>std::tuple\<String, ...\></c>  that instantiations of this template class
         * store.
         */
        using ElementType= std::tuple<String, TAssociatedTypes...>;

        /**
         * This is a shortcut giving the type of the vector that this class implements.
         * Used internally to access inherited methods.
         */
        using VectorType = std::vector<ElementType>;


    // #############################################################################################
    // protected fields
    // #############################################################################################
    protected:
        /** The list of allocated memory blocks. */
        MemoryBlocks                                 blocks;

   // #############################################################################################
   // Constructor / Destructor
   // #############################################################################################
   public:
        /** ****************************************************************************************
         * Constructor.
         * Accepts a value \c stdBlockSize to manipulate the standard size of allocated memory
         * chunks. (This value, is forwarded to the constructor of class
         * \ref aworx::lib::lang::MemoryBlocks "MemoryBlocks".)
         *
         * @param stdBlockSize The standard size of memory blocks allocated.
         ******************************************************************************************/
        StringTuples( int stdBlockSize = 8 * 1024 )
        : blocks( stdBlockSize )
        {
        }

   // #############################################################################################
   // Interface
   // #############################################################################################
   public:
        /** ****************************************************************************************
         * Adds a tuple. The contents of the string of the tuple (its first element) is copied
         * from the given string \p src. The memory for this string is allocated using
         * field #blocks.<br>
         * The other members of the tuple added are forwarded from variadic parameter block \p args.
         *
         * @param src   The string to copy into the first member of the tuple.
         * @param args  Variadic arguments to fill the rest of the inserted tuple.
         *
         * @return A reference to the string that was added.
         ******************************************************************************************/
        String& Add( const String& src, TAssociatedTypes... args )
        {
            char* mem= blocks.GetMemory(src.Length());
            VectorType::emplace_back( String( mem, src.CopyTo( mem ) ), args...  );
            return std::get<0>(VectorType::back());
        }


        /** ****************************************************************************************
         * Clears this vector of tuples and frees the allocated block memory, either for reuse
         * or completely. (Parameter \c deallocate is forwarded to
         * \ref aworx::lib::lang::MemoryBlocks::Clear "MemoryBlocks::Clear".)
         *
         * @param deallocate If \c true, all allocated memory chunks are freed. Otherwise, they
         *                   will be reused for future new strings that are added.
         ******************************************************************************************/
        void    Clear( bool deallocate= false )
        {
            VectorType::clear();
            blocks.Clear( deallocate );
        }
};

}} // namespace lib::strings

/** Type alias name in namespace #aworx. */
template< typename... TAssociatedTypes >
using     StringTuples  =   aworx::lib::strings::StringTuples<TAssociatedTypes...>;

/**
 * Type alias name in namespace #aworx which provides an empty list of variadic arguments.
 * Therefor, the string objects are the only element of the tuple stored.
 */
using     Strings       =   aworx::lib::strings::StringTuples<>;


} // namespace aworx

#endif // HPP_ALIB_STRINGS_STRINGTUPLES
