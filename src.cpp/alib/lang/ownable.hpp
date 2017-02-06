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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_LANG_OWNABLE)
    #error "Header already included"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_ALIB_LANG_OWNABLE
//! @cond NO_DOX
#define HPP_ALIB_LANG_OWNABLE 1
//! @endcond NO_DOX


/**
 * @addtogroup GrpALibMacros
 * @{
 * @name Macros Supporting ALib Classes Owner And Ownable
 * The macros listed here have a direct relationship with classes defined in ALib
 * and with their use.
 * @{
 *
 * \def  OWN
 * This preprocessor defines an object of class
 * \ref aworx::lib::lang::Owner "Owner". The special thing about it is, that using this macro
 * there is no need to invent an (otherwise useless) identifier for that definition.
 * Basically, this macro exists, because C++ does not support anonymous objects.<br>
 * As a sample, without using this macros a piece of code code using classes
 * \ref aworx::lib::lang::Owner   "Owner"/
 * \ref aworx::lib::lang::Ownable "Ownable"
 * could look like this:<br>
\verbatim
{
    Owner myOwner( myOwnable );

    // do stuff
    ...
}
\endverbatim
 *  With the use of this macro, the code changes to:<br>
\verbatim
{
    OWN( myOwnable );

    // do stuff
    ...
}
\endverbatim
 *
 * @}
 * @} */ // GrpALibMacros

#if ALIB_DEBUG
    #define   OWN(ownable) aworx::lib::lang::Owner ALIB_IDENTIFIER(owner) (ownable, ALIB_SRC_INFO_PARAMS);
#else
    #define   OWN(ownable) aworx::lib::lang::Owner ALIB_IDENTIFIER(owner) (ownable);
#endif



namespace aworx { namespace lib { namespace lang
{
/** ************************************************************************************************
 * This abstract class represents objects that can be owned by some other instances.
 * 'To own' means an abstract concept of getting 'acquired' and getting 'released' later on.
 * The obvious and well known example are objects that implement a 'mutex' to lock data against
 * concurrent threads.<br>
 * The pattern of having ownership on ownable objects is usable in other areas as well.
 * The C++ language provides the concept of "stack unwinding", which ensures that all objects are
 * destructed, even when exceptions are thrown (that is why C++ does not have a 'finally'
 * keyword).<br>
 * See class \ref Owner and macro \ref OWN for information on how to 'own' an Ownable automatically
 * for exactly one block of code.
 *
 * In debug compilations, the class supports information about the source location where ownership
 * was gained.
 **************************************************************************************************/
class Ownable
{
    protected:
        #if ALIB_DEBUG
            /**  Debug information on acquirement location */
            strings::TString  acquirementSourcefile                                        =nullptr;

            /**  Debug information on acquirement location */
            int               acquirementLineNumber;

            /**  Debug information on acquirement location */
            strings::TString  acquirementMethodName                                        =nullptr;
        #endif

    public:
        /** ****************************************************************************************
         * Virtual destructor
         *****************************************************************************************/
        virtual ~Ownable()  {}

        /** ****************************************************************************************
         * Virtual abstract method. Functionality due to implementation in descendants.
         * @param file  Caller information. Available only in debug compilations.
         * @param line  Caller information. Available only in debug compilations.
         * @param func  Caller information. Available only in debug compilations.
         *****************************************************************************************/
        #if ALIB_DEBUG
            virtual void Acquire(const TString& file, int line, const TString& func)
            {
                acquirementSourcefile= file;
                acquirementLineNumber= line;
                acquirementMethodName= func;
            }
        #else
            virtual void Acquire() {}
        #endif

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
        Ownable&    theOwnable;

    public:

        /** **************************************************************************************
         *  The constructor. Invokes Acquire() on the owner.
         * @param ownable    The ownable to acquire.
         *
         * @param file  Caller information. Available only in debug compilations.
         * @param line  Caller information. Available only in debug compilations.
         * @param func  Caller information. Available only in debug compilations.
         *****************************************************************************************/
         #if ALIB_DEBUG
             Owner( Ownable& ownable, const TString& file, int line, const TString& func)
             : theOwnable(ownable)
             {
                ownable.Acquire( file, line, func );
             }
         #else
             Owner( Ownable& ownable ) : theOwnable(ownable)
             {
                ownable.Acquire();
             }
         #endif

        /** **************************************************************************************
         *  The destructor. Releases the owner by invoking Release().
         *****************************************************************************************/
         ~Owner()                                        { theOwnable.Release(); }
};

}}} // namespace aworx::lib::lang

#endif // HPP_ALIB_LANG_OWNABLE
