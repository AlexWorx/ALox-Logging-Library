// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include ALox main header first...
#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

// then, set include guard
#ifndef HPP_ALOX_CORE_LOGGER
#define HPP_ALOX_CORE_LOGGER 1


// #################################################################################################
// includes
// #################################################################################################

#if !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
#endif


namespace aworx {
namespace       lox {
/** ************************************************************************************************
 * This is the C++ namespace for internal main classes and other things belonging to
 * the <em>%ALox Logging Library</em>.<p>
 * Types and interfaces found in this namespace are not designed for access by users of the
 * library. However, if extending ALox, e.g. by implementing new custom <em>loggers</em>, things
 * found here provide an important foundation.
 *
 * Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace           core{

// forwards
class Domain;


/** ************************************************************************************************
 * A simple pair of void* and type information, constituting a logable object.
 * Used only internally, not exposed to the user interface.
 **************************************************************************************************/
struct Logable
{
    int           Type;   ///< The type of the object. \c 0 and negative values reserved for ALox
    const void*   Object; ///< The pointer to the object

    /**
     * Default constructor.
     * @param type    Type of the object.
     * @param object  The logable object.
     */
    Logable( int type, const void* object) : Type(type), Object(object) {}

    /**
     * Compares two objects by pointer comparison, in case of type 0 by string comparison.
     * @param comp  The object to compare
     * @return \c true if this and \p comp are equal, \c false otherwise.
     */
    bool Equals( const Logable& comp )
    {
        return        Type == comp.Type
                && (     ( Type != 0 &&  Object == comp.Object )
                      || ( Type == 0 && (   (    Object == nullptr && comp.Object == nullptr )
                                              || ( ((const TString*) Object)->Equals( (const TString*) comp.Object)
                                            )
                                        )
                         )
                  );
    }

    /**
     * Writes a string representation of this object to the given AString.
     * @param target The target
     * @return The target to allow concatenated operations
     */
    AString& ToString( AString& target )
    {
        if ( Type == 0 ||  Type == -1 )
        {
            int idx= target.Length();
            target._('\"')._( (const TString*) Object) ._('\"');
            ESC::ReplaceToReadable( target, idx );
        }
        else
            target._( "<object of type " )._(Type)._('>');
        return target;
    }

};

/**
 * A list of logables as provided to method
 * \ref aworx::lox::core::Logger::Log "Logger::Log".
 */
using Logables= std::vector<core::Logable*>;


/** ************************************************************************************************
 * This is central class of the ALox logging implementation. It is **not** recommended to use this
 * class directly for logging. Instead, use the simple and convenient static interface class
 * Log or, for release logging and other more complex operations use a Lox instance.
 * The class is abstract. To implement an own log stream, derive a new Logger class and implement
 * the abstract method #Log.
 **************************************************************************************************/
class Logger : public aworx::SmartLock
{
    // #############################################################################################
    // Internal fields
    // #############################################################################################

    /**
     *  An utility value. Has to be first in the class. Will be initialized prior to any other
     *  field. For more info see # Log::InitALox()
     */
    private:    bool _apiInitializer;

    protected:
        /**
         * The name of the \e Logger. Used as a reference to a logger. All loggers attached to a
         * \b %Lox have to differ in their names.
         * If no name is specified with the constructor, the name will by the same as #typeName.
         */
        String32                    name;

        /**
         *  The type name of the \e Logger. This is set by the derived class similar to the class
         *  name.
         */
        String32                    typeName;

    // #############################################################################################
    // public fields
    // #############################################################################################
    public:
        /**
         * The number of logs actually performed so far. In a text logger this is similar to the line
         * number, despite the fact that a single log call can produce more than one line.
         */
        int                         CntLogs                                                      =0;

        /**  The creation time of the \e Logger   */
        lib::time::Ticks            TimeOfCreation;

        /**  Timestamp of  the last log operation  */
        lib::time::Ticks            TimeOfLastLog;

    // #############################################################################################
    // Abstract methods
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * This is the central method that derived logger classes have to implement to log a
         * message. When it is invoked the <em>Log Domains' Verbosity</em> was already checked against
         * parameter \p verbosity. The only action to take is to perform the log itself.<br>
         * Parameter \p logables contains at least one object, the one provided with the log
         * statement. Other objects that might be included in the list, are <em>Prefix Objects</em>
         * corresponding to the \p scope.
         *
         * @param dom       The <em>Log Domain</em>.
         * @param verbosity The verbosity of the message.
         * @param logables  The list of objects to log.
         * @param scope     Information about the scope of the <em>Log Statement</em>..
         ******************************************************************************************/
        virtual void   Log( Domain& dom, Verbosity verbosity, Logables& logables, ScopeInfo& scope) =0;

    // #############################################################################################
    // Constructor/Destructor
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Constructs a logger. This constructor is protected because this class is abstract.
         *
         * Note: This constructor is implemented in the header and annotated as inline.
         * This way, the Log::InitALox call receives the size of classes from the compilation unit
         * that invokes the constructor. If different compile options are set, we have a chance to
         * detect them here.
         * @param name     The name of the \e Logger. If empty, it defaults to the type name.
         * @param typeName The type of the \e Logger.
         ******************************************************************************************/
        inline
        Logger( const String& name, const String& typeName )
                                     : _apiInitializer( ALox::Init() )
                                     , name(name)
                                     , typeName(typeName)
                                     , TimeOfCreation ()
                                     , TimeOfLastLog  ()
        {
            if ( this->name.IsEmpty() )
                this->name << typeName;
        }

        /** ****************************************************************************************
         *  Destructs a logger
         ******************************************************************************************/
    public:
        virtual  ~Logger() {};

    // #############################################################################################
    // Interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Returns the name of this logger. The name has to be unique for all \e %Loggers attached
         * to a \b %Lox.
         * @return The loggers name.
         ******************************************************************************************/
        inline
        const TString& GetName()      const  {     return name;      }

        /** ****************************************************************************************
         * Returns the constant type name of this logger. The type name is defined by the class
         * and hence provides a sort of run-time type information.
         * @return The loggers type name.
         ******************************************************************************************/
        inline
        const TString& GetTypeName()  const  {     return typeName;  }


}; // class Logger

}} // namespace lox::core

/** Type alias name in namespace #aworx. */
using     Logger=       aworx::lox::core::Logger;

}  // namespace aworx



namespace aworx {
namespace       lib {
namespace             strings{

    /** ********************************************************************************************
     * Specialization of TMP 'function' (struct)
     * \ref aworx::lib::strings::IsApplicable "IsApplicable" for type \b std::string.
     **********************************************************************************************/
    template<>   struct               IsApplicable<const lox::core::Logger&>   : public std::true_type {};

    /** ********************************************************************************************
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type \b std::string.
     * See \ref aworx::lib::strings::ApplyTo "ApplyTo" for more information
     * @param  target The AString to append \p src to.
     * @param  logger The logger to apply.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>   inline   int         ApplyTo <const lox::core::Logger&>( AString& target, const lox::core::Logger& logger )
    {
        int origTargetLength= target.Length();
        target << logger.GetName();
        if ( !logger.GetName().Equals( logger.GetTypeName() ) )
            target << " (" << logger.GetTypeName() << ")";

        return (int) target.Length() - origTargetLength;
    }
}}} // namespace aworx::lib::strings



#endif // HPP_ALOX_CORE_LOGGER
