// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using cs.aworx.lib;
using cs.aworx.lox.core;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;
using cs.aworx.lib.threads;
using System.Collections.Generic;


/** ************************************************************************************************
 * This is the C# namespace for internal main classes and other things belonging to
 * the <em>%ALox Logging Library</em>.<p>
 * Types and interfaces found in this namespace are not designed for access by users of the
 * library. However, if extending ALox, e.g. by implementing new custom <em>loggers</em>, things
 * found here provide an important foundation.
 *
 * Developed by A-Worx GmbH and published under Boost Software License.
 **************************************************************************************************/
namespace cs.aworx.lox.core {

/** ************************************************************************************************
 * This is central class of the ALox logging implementation. It is **not** recommended to use this
 * class directly for logging. Instead, use the simple and convenient static interface class
 * Log or, for release logging and other more complex operations use a Lox instance.
 * The class is abstract. To implement an own log stream, derive a new Logger class and implement
 * the abstract method #Log.
 **************************************************************************************************/
public abstract class Logger : SmartLock
{
  #if ALOX_DBG_LOG || ALOX_REL_LOG

    // #############################################################################################
    // protected fields
    // #############################################################################################

        /**
         * The name of the \e Logger. Used as a reference to a logger. All loggers attached to a
         * \b %Lox have to differ in their names.
         * If no name is specified with the constructor, the name will by the same as #TypeName.
         */
        protected    String          Name;

        /**
         *  The type name of the \e Logger. This is set by the derived class similar to the class
         *  name.
         */
        protected    String          TypeName;

    // #############################################################################################
    // public fields
    // #############################################################################################

        /**
         * The number of logs actually performed so far. In a text logger this is similar to the
         * line number, despite the fact that a single log call can produce more than one line.
         */
        public    int             CntLogs;

        /// The creation time of the \e Logger.
        public    Ticks           TimeOfCreation                                      = new Ticks();

        /// Timestamp of  the last log operation.
        public    Ticks           TimeOfLastLog                                       = new Ticks();

    // #############################################################################################
    // Abstract methods (introduced)
    // #############################################################################################

        /** ****************************************************************************************
         * This is the central method that derived logger classes have to implement to log a
         * message. When it is invoked the <em>Log Domains' Verbosity</em> was already checked against
         * parameter \p verbosity. The only action to take is to perform the log itself.<br>
         * Parameter \p logables contains at least one object, the one provided with the log
         * statement. Other objects that might be included in the list, are <em>Prefix Objects</em>
         * corresponding to the \p scope.
         *
         * @param domain    The <em>Log Domain</em>.
         * @param verbosity The verbosity.
         * @param logables  The list of objects to log.
         * @param scope     Information about the scope of the <em>Log Statement</em>.
         ******************************************************************************************/
        abstract public void Log( Domain        domain,
                                  Verbosity     verbosity,
                                  List<Object>  logables,
                                  ScopeInfo     scope       );


    // #############################################################################################
    // constructor(s)
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs a logger.
         * @param name     The name of the \e Logger. If empty, it defaults to the type name.
         *                 Will be converted to upper case.
         * @param typeName The type of the \e Logger.
         *                 Will be converted to upper case.
         ******************************************************************************************/
        protected Logger( String name, String typeName )
        {
            // save parameters
            this.TypeName=  typeName.ToUpper();
            this.Name=      !String.IsNullOrEmpty( name ) ? name.ToUpper() : this.TypeName;
        }

    // #############################################################################################
    // interface
    // #############################################################################################

        /** ****************************************************************************************
         * Returns the name of this logger. The name has to be unique for all \e %Loggers attached
         * to a \b %Lox.
         * @return The loggers name.
         ******************************************************************************************/
        public String GetName()      {     return Name;      }

        /** ****************************************************************************************
         * Returns the constant type name of this logger. The type name is defined by the class
         * and hence provides a sort of runtime type information.
         * @return The loggers type name.
         ******************************************************************************************/
        public String GetTypeName()  {     return TypeName;  }

        /** ****************************************************************************************
         * This is for debugging purposes. E.g. this enables the \e Monodevelop IDE to display
         * object descriptions in the debugger.
         * @returns A human readable string representation of this object.
         ******************************************************************************************/
        public override String ToString()
        {
            String result= Name;
            if (!Name.Equals(TypeName))
                result+= " (" + TypeName + ')';
            return result;
        }


    #endif // ALOX_DBG_LOG || ALOX_REL_LOG


} // class Logger

} // namespace
