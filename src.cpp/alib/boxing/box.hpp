// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen


#if !defined (HPP_ALIB_BOXING)
    #include "alib/boxing/boxing.hpp"
#endif

//  set include guard
#ifndef HPP_ALIB_BOXING_BOX
//! @cond NO_DOX
#define HPP_ALIB_BOXING_BOX 1
//! @endcond NO_DOX


namespace aworx { namespace lib { namespace boxing
{

/** ************************************************************************************************
 * This is the central class of <b>ALib %Boxing</b>. By using template meta programming, an object
 * of this class can be created by passing just any C++ type to the constructor. The passed
 * value will be "boxed" within the instance of this class.
 *
 * Then, the instances of this class support type checking, value extraction ("unboxing") and the
 * invocation of "virtual methods". All features are customizable in detail per "boxable type".
 *
 * A thorough introduction to and documentation of all aspects of <b>ALib %Boxing</b> is given
 * with namespace documentation \ref aworx::lib::boxing.
 **************************************************************************************************/
class Box
{
    // #############################################################################################
    // friends
    // #############################################################################################
                                 friend class     Boxer;


    // #############################################################################################
    // protected fields
    // #############################################################################################
    protected:

        /**
         * The singleton of a class derived from class \b %Boxer which defines our type and
         * behaviour.
         */
        Boxer*      boxer;
public:
        /** The data that we encapsulate. */
        BoxData     data;


    // #############################################################################################
    // Constructors
    // #############################################################################################
    public:

        #if !defined(DOX_PARSER)
            ALIB_WARNINGS_START_TMP
        #endif

        /** ****************************************************************************************
         * Default constructor. Created a nulled box (method #IsNull will return \c true after
         * construction). The box is equivalent to a box that is constructed with \c nullptr.
         *****************************************************************************************/
        inline Box()
        {
            boxer= BoxerT<decltype(nullptr)>::GetSingleton();
            data.Value=  (boxvalue) 0;
            data.Length= 0;
        }


        /** ****************************************************************************************
         * Constructor fetching type \c void* values.
         *
         * @param src The \p void* value to be boxed.
         *****************************************************************************************/
        inline Box( void* src ) // void* would not compile if passed through the TMP constructor.
        {
            if( T_Boxing<void*>::value )
                boxer= BoxerT<T_Boxing<void*>::Type>::GetSingleton();
            else
                boxer= BoxerT<void *>::GetSingleton();
            data.Value=  (boxvalue) src;
            data.Length= 0;
        }

        /** ****************************************************************************************
         * Constructor using template meta programming to fetch any type of ALib Strings,
         * unknown pointer types and nullptr.
         *
         * @tparam TBoxable  Any C++ type to be boxed.
         * @param  src       The src of (template) type \c T.
         *****************************************************************************************/
        template <typename TBoxable>
        inline
        Box(const  TBoxable& src )
        {
            // untyped nullptr
            if (  std::is_same<TBoxable, decltype(nullptr)>::value )
            {
                boxer= BoxerT<decltype(nullptr)>::GetSingleton();
                data.Value=  (boxvalue) 0;
                data.Length= 0;
                return;
            }


            using TPlain= typename std::remove_const    <
                          typename std::remove_pointer  <
                          typename std::remove_reference<
                          typename std::remove_const    < TBoxable >::type>::type>::type>::type;

            //ALIB_TMP_SHOW_TYPE_IN_DEBUGGER(TPlain)

            // array types
            if( std::is_array<TPlain>::value )
            {
                using TAElem= typename std::remove_extent<TPlain>::type;
                //ALIB_TMP_SHOW_TYPE_IN_DEBUGGER(TAElem)

                boxer=          ArrayBoxerT<TAElem>::GetSingleton();
                data.Value=     (boxvalue) &src;
                data.Length=    T_SetArraySize<TAElem>( (integer) ( std::extent<TPlain>::value ) );
                return;
            }

            // boxing a box?
            if( std::is_same<Box, TPlain>::value )
            {
                if( std::is_pointer<TBoxable>::value )
                {
                    ALIB_ASSERT_ERROR( * (TPlain **)  &src != nullptr, "Can't box type Box* of value nullptr." );
                    boxer=        (* (Box **) &src) ->boxer;
                    data.Value=   (* (Box **) &src) ->data.Value;
                    data.Length=  (* (Box **) &src) ->data.Length;
                }
                else
                {
                    ALIB_ERROR( "This can't happen" );
                }
                return;
            }

            // if a pointer was given, try to find boxer for pointer type first
            if( std::is_pointer<TBoxable>::value )
            {
                if( T_Boxing<TPlain*>::value )
                {
                    boxer= T_Boxing<TPlain*>::IsArray()
                              ? (Boxer*) ArrayBoxerT<typename T_Boxing<TPlain*>::Type >::GetSingleton()
                              : (Boxer*)      BoxerT<typename T_Boxing<TPlain*>::Type >::GetSingleton();

                    if( * (TPlain **)  &src )
                    {
                        if(T_Boxing<TPlain*>::HasCustomBoxing() )
                            T_Boxing<TPlain*>::Boxing( *this, * (TPlain **)  &src  );
                        else
                        {
                            if(std::is_pointer<typename T_Boxing<TPlain*>::Type>::value )
                                DefaultBoxing( *this, * ((TPlain **)   &src) );
                            else
                                DefaultBoxing( *this, * ((TPlain *&)     src) );
                        }
                    }
                    else
                    {
                        data.Value=  0;
                        data.Length= 0;
                    }
                    return;
                }

                if( T_Boxing<TPlain>::value )
                {
                    boxer= T_Boxing<TPlain>::IsArray()
                              ? (Boxer*) ArrayBoxerT<typename T_Boxing<TPlain>::Type >::GetSingleton()
                              : (Boxer*)      BoxerT<typename T_Boxing<TPlain>::Type >::GetSingleton();

                    if( * (TPlain **)  &src )
                    {
                        if(T_Boxing<TPlain>::HasCustomBoxing() )
                            T_Boxing<TPlain>::Boxing( *this, * ((TPlain *&)     src) );
                        else
                        {
                            if(std::is_pointer<typename T_Boxing<TPlain>::Type>::value )
                                DefaultBoxing( *this, * ((TPlain **)   &src) );
                            else
                                DefaultBoxing( *this, * ((TPlain *&)     src) );
                        }
                    }
                    else
                    {
                        data.Value=  0;
                        data.Length= 0;
                    }

                    return;
                }
            }

            // if a non-pointer was given, try to find boxer for non-pointer type type first
            else
            {
                if( T_Boxing<TPlain>::value )
                {
                    boxer= T_Boxing<TPlain>::IsArray()
                              ? (Boxer*) ArrayBoxerT<typename T_Boxing<TPlain>::Type >::GetSingleton()
                              : (Boxer*)      BoxerT<typename T_Boxing<TPlain>::Type >::GetSingleton();


                    if(T_Boxing<TPlain>::HasCustomBoxing() )
                        T_Boxing<TPlain>::Boxing( *this, (TPlain&) *(int*)  &src );
                    else
                    {
                        if(std::is_pointer<typename T_Boxing<TPlain>::Type>::value )
                            DefaultBoxing( *this, (typename std::remove_pointer<typename T_Boxing<TPlain>::Type>::type * )          &src );
                        else
                            DefaultBoxing( *this, (typename T_Boxing<TPlain>::Type&) *(int*)  &src );
                    }

                    return;
                }

                if( T_Boxing<TPlain*>::value )
                {
                    boxer= T_Boxing<TPlain*>::IsArray()
                              ? (Boxer*) ArrayBoxerT<typename T_Boxing<TPlain*>::Type >::GetSingleton()
                              : (Boxer*)      BoxerT<typename T_Boxing<TPlain*>::Type >::GetSingleton();
                    if(T_Boxing<TPlain*>::HasCustomBoxing() )
                        T_Boxing<TPlain*>::Boxing( *this, (TPlain * )  &src );
                    else
                    {
                        if(std::is_pointer<typename T_Boxing<TPlain*>::Type>::value )
                            DefaultBoxing( *this, (typename std::remove_pointer<typename T_Boxing<TPlain>::Type>::type * )          &src );
                        else
                            DefaultBoxing( *this, (typename T_Boxing<TPlain>::Type&) *(int*)  &src );
                    }
                    return;
                }
            }

            // Nothing was found: create a generic boxer for the given type (as pointer)
            boxer= BoxerT<TPlain*>::GetSingleton();
            if( std::is_pointer<TBoxable>::value )
            {
                if( * (TPlain **)  &src )
                    DefaultBoxing<TPlain*>( *this, * (TPlain **)  &src  );
                else
                {
                    data.Value=  0;
                    data.Length= 0;
                }
            }
            else
                DefaultBoxing<TPlain*>( *this,   (TPlain * )  &src );
        }



    // #############################################################################################
    // Interface
    // #############################################################################################
        public:
        #if ALIB_DEBUG
            /**
             * Returns type information of the boxer of this instance.
             * Available only in debug compilations. See also static methods
             * \ref aworx::lib::boxing::Boxer::DbgGetInterfaces         "Boxer::DbgGetInterfaces",
             * \ref aworx::lib::boxing::Boxer::DbgGetKnownBoxers        "Boxer::DbgGetKnownBoxers",
             * \ref aworx::lib::boxing::Boxer::DbgGetKnownInterfaces    "Boxer::DbgGetKnownInterfaces",
             * \ref aworx::lib::boxing::Boxer::DbgGetDefaultInterfaces  "Boxer::DbgGetDefaultInterfaces"  and
             * \ref aworx::lib::boxing::Boxer::DbgGetKnownInterfaceImpl "Boxer::DbgGetKnownInterfaceImpl".
             *
             * @return Type information of the boxer of this instance.
             */
            inline
            const std::type_info&    DbgGetBoxerType() const
            {
                return boxer->type;
            }

        #endif

        /** ****************************************************************************************
         * Checks if this box stores a value of type \p TBoxable.
         * @return \c true if this box stores a value of type \p TBoxable, \c false otherwise.
         *****************************************************************************************/
        template<typename TBoxable>
        inline
        bool            IsType()        const
        {
            static_assert(     (     T_Boxing<TBoxable>::value && T_Boxing<TBoxable>::IsUnboxable() )
                            || (    !T_Boxing<TBoxable>::value
                                 && std::is_pointer<TBoxable>::value
                                 && !T_Boxing<typename std::remove_pointer<TBoxable>::type >::value )
                            ||  std::is_same<TBoxable, decltype(nullptr)>::value
                            , "This type can not be unboxed.");
            return boxer ==( T_Boxing<TBoxable>::value
                               ? ( T_Boxing<TBoxable>::IsArray()
                                     ? (Boxer*) ArrayBoxerT<typename T_Boxing<TBoxable>::Type >::GetSingleton()
                                     : (Boxer*)      BoxerT<typename T_Boxing<TBoxable>::Type >::GetSingleton() )
                               : (Boxer*) BoxerT<TBoxable>::GetSingleton() );

        }

        /** ****************************************************************************************
         * Checks if a box does not contain a value. This happens if constructed with
         * \c nullptr or standard constructor. Internally, this method checks if the type of
         * the stored value is <c>decltype(nullptr)</c>.
         *
         * @return \c true if this box does not contain a value.
         *****************************************************************************************/
        inline
        bool            IsNull()        const
        {
            return IsType<decltype(nullptr)>();
        }

        /** ****************************************************************************************
         * Checks if this box stores a value of type \c void*. This special treatment of this type
         * is necessary for technical reasons.
         * To unbox a \c void* use #UnboxRaw().
         * @return \c true if this box stores a value of type \p TBoxable, \c false otherwise.
         *****************************************************************************************/
        inline
        bool            IsVoidPointer()        const
        {
            if( T_Boxing<void*>::value )
                return boxer == BoxerT<T_Boxing<void*>::Type>::GetSingleton();
            else
                return boxer == BoxerT<void *>::GetSingleton();
        }

        #if !defined(DOX_PARSER)
            ALIB_WARNINGS_RESTORE
        #endif


        /** ****************************************************************************************
         * Returns \c true if this box represents an array of objects. In this case, method
         * #Length (usually) will return the length of the array and
         * #UnboxElement may be used to access elements of the array.
         *
         * @return \c true if this box represents an array, \c false otherwise.
         ******************************************************************************************/
        inline
        bool            IsArray()       const
        {
            return boxer->IsArray();
        }

        /** ****************************************************************************************
         * Returns \c true if this objects represents an array and the element type
         * equals template parameter \p TElementType.
         *
         * @tparam TElementType The array element type to compare our element type with.
         * @return \c true if this box represents an array of given type, \c false otherwise.
         ******************************************************************************************/
        template<typename TElementType> inline
        bool            IsArrayOf()     const
        {
            return boxer->elemType == typeid(TElementType);
        }

        /** ****************************************************************************************
         * Returns \c true if \p other and this object share the same boxed type.
         *
         * @param other The box to compare our type with.
         * @return \c true if this box has the same type like \p other, \c false otherwise.
         ******************************************************************************************/
        inline
        bool            IsSameType(const Box& other) const
        {
            return  boxer == other.boxer;
        }

        #if !defined(DOX_PARSER)
            ALIB_WARNINGS_START_TMP
        #endif
        /** ****************************************************************************************
         * Returns the contents of this box converted to type \p TBoxable.
         * By default this is done by invoking template method
         * \ref aworx::lib::boxing::DefaultUnboxing "DefaultUnboxing" and might be customized
         * by specializing struct
         * \ref aworx::lib::boxing::T_Boxing "T_Boxing".
         *
         * In debug compilations, the actual type of this object is asserted to equal the templated
         * return type.
         *
         * For technical reasons, type \c void* can not be unboxed using this method.
         * Use #UnboxRaw() instead.
         *
         * @tparam TBoxable The supported type
         * @return The type ID (BoID) of this object
         ******************************************************************************************/
        template <typename TBoxable> inline
        TBoxable         Unbox()           const
        {
            static_assert(     (     T_Boxing<TBoxable>::value && T_Boxing<TBoxable>::IsUnboxable() )
                            || (    !T_Boxing<TBoxable>::value
                                 && std::is_pointer<TBoxable>::value
                                 && !T_Boxing<typename std::remove_pointer<TBoxable>::type >::value )
                            , "This type can not be unboxed.");

            ALIB_ASSERT_ERROR( IsType<TBoxable>(), "Box::Unbox(): Incompatible type" );

            if(T_Boxing<TBoxable>::HasCustomUnboxing() )
                return T_Boxing<TBoxable>::Unboxing(*this);
            else
                return DefaultUnboxing<TBoxable>(*this);
        }

        #if !defined(DOX_PARSER)
            ALIB_WARNINGS_RESTORE
        #endif

        /** ****************************************************************************************
         * Returns the length of the boxed object. The length is only applicable for array-type
         * objects or for custom-type objects that use this field for arbitrary (in which case
         * the name of this method might be misleading).
         *
         * @return The length of the boxed object.
         *****************************************************************************************/
        inline
        integer         Length()        const
        {
            return data.Length;
        }

        /** ****************************************************************************************
         * Returns the raw value of the contents of this box. The value is declared as type
         * #boxvalue, which usually is an alias to \c uint64_t.
         *
         * In special situations, it might be useful to access the raw value and reinterpret
         * its contents in any proper way.
         *
         * @return The raw contents of this object
         ******************************************************************************************/
        inline
        boxvalue        UnboxRaw()        const
        {
            return data.Value;
        }

        /** ****************************************************************************************
         * Returns the size in bytes of on element of the stored array.
         * This method is applicable only for array types. For non-array types, \c 0 is returned
         * and in debug compilation an ALib assertion is raised.
         *
         * @return The size of elements in the array.
         ******************************************************************************************/
        inline
        size_t        ArrayElementSize()        const
        {
            ALIB_ASSERT_ERROR( IsArray(), "Box::ArrayElementSize(): Not an array type" );
            return boxer->sizeofElemType;
        }


        /** ****************************************************************************************
         * Returns a reference to element \p idx of the boxed array.
         *
         * \note
         *   In debug compilations, it is asserted that #IsArray returns \c true, the stored type
         *   is the same as requested and the provided \p idx is between \c 0 and the length of the
         *   array. In release compilations, no checks are performed!
         *
         * @tparam TElementType The type of array elements
         * @param  idx      The index of the element to receive.
         * @return The value of the element at \p idx.
         ******************************************************************************************/
        template <typename TElementType> inline
        TElementType&    UnboxElement(integer idx)       const
        {
            ALIB_ASSERT_ERROR( IsArray(), "Box::UnboxElement(): Not an array type" );
            ALIB_ASSERT_ERROR( boxer->elemType == typeid(TElementType), "Box::UnboxElement(): Wrong type requested" );
            ALIB_ASSERT_ERROR( idx >= 0 && idx < Length(),              "Box::UnboxElement(): Index out of bounds" );
            return * (reinterpret_cast<TElementType*>(data.Value) + idx );
        }

        /** ****************************************************************************************
         * Returns \c true if this box supports the interface \p IF.
         * See class \ref aworx::lib::boxing::Interface "Interface" for more information
         * about how to enable custom types to support arbitrary method interfaces.
         *
         * \note
         *   This method returns \c false even if a default interface used for any
         *   type is available! In this case, the interface might still be invoked or received
         *   using #Invoke or #GetInterface.
         *   Consequently, this method can be used to detect (and avoid) default behaviour,
         *
         * @tparam TInterface  The interface to receive.
         * @return \c true if a dedicated interface of type \p IF exists for the boxed value.
         ******************************************************************************************/
        template <typename TInterface> inline
        bool             HasInterface()  const
        {
            return boxer->interfaces.find( typeid(TInterface) )  != boxer->interfaces.end();
        }

        /** ****************************************************************************************
         * Invokes method \b %"Invoke" of attached interface type \p TInterface.
         *
         * If no interface is attached to this classes #boxer, then a default value of \p TReturn
         * returned. Hence, type \p TReturn needs to be default constructable.
         * In debug compilations, \ref ALIB_ERROR is used to handle non-existing interface errors.
         *
         * In the case that a default instance of type \p TInterface is not set (see
         * \ref aworx::lib::boxing::Boxer::DefineDefaultInterface "Boxer::DefineDefaultInterface"),
         * method #HasInterface should be used to determine the existence of a specialized interface
         * for the boxed type.
         *
         * If return type of method \b %"Invoke" of interface class \p TInterface is other than
         * \c void, then this return type needs to be explicitly specified as second template
         * parameter.
         *
         * @tparam TInterface  The interface type to receive.
         * @tparam TReturn     The return type of the invocation. Defaults to \c void.
         * @tparam Args        The types of the variadic arguments.
         * @param  args        The variadic arguments to interface methods.
         * @return Nothing in case that \p TReturn is void, otherwise the result of the invocation,
         *         respectively <c>TReturn()</c> if requested interface type was not found for this
         *         \b %Box.
         ******************************************************************************************/
        template <typename TInterface, typename TReturn= void, typename... Args>
        TReturn          Invoke(Args&&... args)  const
        {
            TInterface* interface= GetInterface<TInterface>();
            if( interface != nullptr )
                return interface->Invoke( *this, std::forward<Args>(args)... );


            // not found: In debug mode, check if this interface exists anywhere
            #if ALIB_DEBUG
                Boxer::debugCheckInterfaceExists( typeid(TInterface) );
                ALIB_ERROR( "Interface not found: ", debug::TypeDemangler(typeid(TInterface)).Get() )
            #endif

            return TReturn();
        }

        /** ****************************************************************************************
         * Searches and receives the singleton instance of type \p TInterface (which needs to be of
         * a type derived from class \ref aworx::lib::boxing::Interface  "Interface")
         * defined for boxed types represented by this object.
         *
         * \note
         *   Instead of using this method, it is advised to use method #Invoke instead. The use
         *   of this method and subsequent "manual" invocation of the method named \b "Invoke" on
         *   of the returned interface instance is useful, when multiple invocations of the
         *   interface method are to be done on the same box, like in the following sample:
         *
         *      MyInterface* mIF= aBox.GetInterface<MyInterface>();
         *      if( mIF != nullptr )
         *          for( int i= 0; i< 100; ++i )
         *              mIF->Invoke( aBox, i );
         *
         *
         * @tparam TInterface  The interface type to receive.
         * @return The interface singleton defined. \c nullptr in case that no interface is
         *         available.
         ******************************************************************************************/
        template <typename TInterface>
        TInterface*    GetInterface()  const
        {
            TInterface* interface= nullptr;

            // search in interfaces
            auto entry= boxer->interfaces.find( typeid(TInterface) );
            if ( entry != boxer->interfaces.end() )
                interface=  dynamic_cast<TInterface*>( entry->second );

            // check for default interface (all types)
            else
            {
                entry= Boxer::defaultInterfaces.find( typeid(TInterface) );
                if ( entry !=  Boxer::defaultInterfaces.end() )
                    interface=  dynamic_cast<TInterface*>( entry->second );
            }

            return interface;
        }

}; // class Box


}} // namespace aworx[::lib::boxing]

/** Type alias name in namespace #aworx. */
using     Box=         aworx::lib::boxing::Box;

} // namespace aworx

#endif // HPP_ALIB_BOXING_BOX
