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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_LANG_MEMORYBLOCKS)
    #error "Header already included"
#endif


// then, set include guard
#ifndef HPP_ALIB_LANG_MEMORYBLOCKS
//! @cond NO_DOX
#define HPP_ALIB_LANG_MEMORYBLOCKS 1
//! @endcond

#if !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
#endif


namespace aworx { namespace lib { namespace util {

/** ************************************************************************************************
 * Simple class that allocates a series of bigger memory blocks  and provides sequential
 * allocation of sub-ranges of those. Furthermore, the allocations can be reset and the
 * allocated blocks reused.
 *
 * The size of the blocks allocated is defined with constructor parameter \p pSize. If an invocation
 * to #GetMemory is requesting a bigger allocation, then a new block with that given size is
 * created.
 *
 * \note
 *   This class is new with \b %ALib. It is not considered finished, optimized and stable in design.
 **************************************************************************************************/
class MemoryBlocks
{
    // #############################################################################################
    // inner types
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Internal type defining an allocated memory chunk.
         ******************************************************************************************/
        struct Block
        {
            char*       mem;  ///< The allocated memory
            integer    size; ///< The size of the block
            integer    fill; ///< The current fill

            /** ************************************************************************************
             * Constructor allocating the given \p pSize of memory.
             * This memory is not deallocated with a destructor, therefore
             * objects of this type need to be deleted manually.
             *
             * @param pSize  The size of memory chunk to allocate
             **************************************************************************************/
            inline Block( integer pSize )
            : size(pSize)
            , fill(0)
            {
                mem= new char[static_cast<size_t>(pSize)];
            }

            /** ************************************************************************************
             * Returns \c nullptr if the requested size is not available in the block.
             * Otherwise, the pointer to the now allocated memory inside the block is returned.
             *
             * @param requestedSize The size to allocate.
             * @return \c nullptr on failure, otherwise pointer to the requested memory.
             **************************************************************************************/
            inline char* Allocate( integer requestedSize )
            {
                if( size-fill < requestedSize )
                    return nullptr;

                char* result= mem + fill;
                fill+= requestedSize;
                return result;
            }
        };

    // #############################################################################################
    // protected fields
    // #############################################################################################
    protected:
        /** The list of allocated memory blocks. */
        std::vector<MemoryBlocks::Block>                        blocks;

        /** The actual block iterator. */
        typename std::vector<MemoryBlocks::Block>::iterator     actBlock;

        /** The standard allocation size. Blocks may be bigger in the case that
         *  a string added is longer than this value. */
        integer                                                blockAllocationSize;

   // #############################################################################################
   // Constructor / Destructor
   // #############################################################################################
   public:
        /** ****************************************************************************************
         * Constructor.
         * Accepts a value to manipulate #blockAllocationSize.
         *
         * @param stdBlockSize The size of memory blocks allocated.
         ******************************************************************************************/
        ALIB_API MemoryBlocks( int stdBlockSize );

        /** ****************************************************************************************
         * Destructor.
         * Invokes \ref Clear "Clear(true)".
         ******************************************************************************************/
        ALIB_API ~MemoryBlocks();


   // #############################################################################################
   // Interface
   // #############################################################################################
   public:
        /** ****************************************************************************************
         * Allocates memory of size \p size.
         *
         * @param size The size of the memory to allocate.
         * @return A pointer to the allocated memory.
         ******************************************************************************************/
        ALIB_API char*   GetMemory(integer size);

        /** ****************************************************************************************
         * Clears the allocation information.
         * The allocated memory blocks will be freed only if parameter \p deallocate is \c true.
         * In this case, future invocations of #GetMemory will allocate new blocks.
         *
         * @param deallocate If \c true, all allocated memory chunks are freed. Otherwise, they
         *                   will be reused with future #GetMemory invocations.
         ******************************************************************************************/
        ALIB_API void    Clear( bool deallocate );


        #if ALIB_MODULE_STRINGS
            /** ****************************************************************************************
             * Returns a copy of the given string.
             *
             * @param src The source string to copy
             * @return A string object representing the copy.
             ******************************************************************************************/
            inline
            String Copy( const String& src )
            {
                char* mem= GetMemory( src.Length() );
                src.CopyTo( mem );
                return String(mem, src.Length() );
            }
        #endif


};

}} // namespace aworx[::lib::util]

/** Type alias name in namespace #aworx. */
using     MemoryBlocks   =   aworx::lib::util::MemoryBlocks;

} // namespace aworx

#endif // HPP_ALIB_LANG_MEMORYBLOCKS
