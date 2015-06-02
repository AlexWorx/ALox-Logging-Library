// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// include AWXU main header first...
#if !defined (HPP_AWORX_UTIL_AWXU)
    #include "awxu.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_UTIL_OWNABLE
#define HPP_AWORX_UTIL_OWNABLE 1


namespace aworx {
namespace       util {

/** ************************************************************************************************
 *  This interface class (which means, it has only abstract virtual methods) represents objects
 *  that can be owned by some other instances. Here, the verb 'to own' denotes an abstract concept
 *  of getting 'acquired' and getting 'released' later on. The obvious and well known example are
 *  objects that implement a 'mutex' to lock data against concurrent threads.<br>
 *  But pattern of having ownership on ownable objects is usable in other areas as well.
 *  The C++ language provides the concept of "stack unwinding", which ensures that all objects are
 *  destructed, even when exceptions are thrown (that is why C++ does not have a 'finally'
 *  keyword).<br>
 *  See class \ref Owner and macro \ref OWN for information on how to 'own' an Ownable automatically
 *  for exactly one block of code.
 **************************************************************************************************/
class Ownable
{
    public:
        /** ****************************************************************************************
         *  Virtual abstract method. Functionality due to implementation in descendants.
         *****************************************************************************************/
        virtual void Acquire()    =0;

        /** **************************************************************************************
         *  Virtual abstract method. Functionality due to implementation in descendants.
         *****************************************************************************************/
        virtual void Release()    =0;
};

/** ************************************************************************************************
 *  Ensures that an object of type \ref Ownable is acquired and properly released when unwinding the
 *  stack.  This class is meant to be allocated only on the stack and not on the heap. Therefore,
 *  the new operators are declared private.<br>
 *  See preprocessor macro \ref OWN for a convenient way to use this class.
 **************************************************************************************************/
struct Owner
{
    // #############################################################################################
    // Disallow new operations.
    // #############################################################################################
    private:
        /** Private declared new, to disallow heap allocation */       void* operator new  (size_t);
        /** Private declared new, to disallow heap allocation */       void* operator new  (size_t, void*);
        /** Private declared new, to disallow heap allocation */       void* operator new[](size_t);
        /** Private declared new, to disallow heap allocation */       void* operator new[](size_t, void*);
        /** Private declared assignment operator. @returns Itself. */ Owner& operator =    (const Owner& );

    protected:
        /**  All we own is this */
        Ownable&    ownable;

    public:

        /** **************************************************************************************
         *  The constructor. Invokes Acquire() on the owner.
         * @param ownable    The ownable to acquire.
         *****************************************************************************************/
         Owner( Ownable& ownable ) : ownable(ownable)    { ownable.Acquire();  }

        /** **************************************************************************************
         *  The destructor. Releases the owner by invoking Release().
         *****************************************************************************************/
         ~Owner()                                        { ownable.Release(); }
};


}} // namespace aworx::util

#endif // HPP_AWORX_UTIL_OWNABLE
