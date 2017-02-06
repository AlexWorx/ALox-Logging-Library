// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"
#include "alib/lang/memoryblocks.hpp"
#include <algorithm>


using namespace std;

namespace aworx { namespace lib { namespace lang
{

MemoryBlocks::MemoryBlocks( int stdBlockSize )
: blockAllocationSize( stdBlockSize )
{
    actBlock= blocks.begin();
}

MemoryBlocks::~MemoryBlocks()
{
    Clear( true );
}

void MemoryBlocks::Clear( bool deallocate )
{
    if( deallocate )
    {
        for ( auto& block : blocks )
            delete[] block.mem;
        blocks.clear();
    }
    else
    {
        for ( auto& block : blocks )
            block.fill= 0;
    }

    actBlock= blocks.begin();
}

char*  MemoryBlocks::GetMemory(integer size)
{
    for(;;)
    {
        if( actBlock == blocks.end()  )
        {
            blocks.emplace_back( Block( (std::max)( size, blockAllocationSize ) ) );
            actBlock= blocks.end() - 1;
            return actBlock->Allocate( size );
        }

        char* mem= actBlock->Allocate( size );
        if( mem )
            return mem;

        actBlock++;
    }
}



}}}// namespace aworx::lib::strings

