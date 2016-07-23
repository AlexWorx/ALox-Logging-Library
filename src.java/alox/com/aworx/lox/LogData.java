// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

import com.aworx.lib.strings.AString;

/** ****************************************************************************************
 * Data objects used with
 * \ref com::aworx::lox::Lox::store      "Lox.store" and
 * \ref com::aworx::lox::Lox::retrieve   "Lox.retrieve".
 * 
 * \note With other language implementations of ALox, this class is a public inner class
 *       of class Log. 
 ******************************************************************************************/
public class LogData
{
    /** A string value*/
    public AString     stringValue= new AString();

    /** An integer value */
    public int         integerValue;

    /** Any type of data */
    public Object      objectValue;

    /** Constructs a data object
     *  @param s    String data to store.
     *  @param i    Integer value to store.
     *  @param o    Object to store.          */
    public LogData( CharSequence s, int i, Object o )   { stringValue._(s); integerValue= i; objectValue= o; }

    /** Constructs a data object
     *  @param s    String data to store.
     *  @param i    Integer value to store.   */
    public LogData( CharSequence s, int i           )   { stringValue._(s); integerValue= i;                 }

    /** Constructs a data object
     *  @param s    String data to store.     */
    public LogData( CharSequence s                  )   { stringValue._(s);                                  }

    /** Constructs a data object          */
    public LogData(                                 )   {                                                    }

    /** Constructs a data object
     *  @param s    String data to store.
     *  @param o    Object to store.          */
    public LogData( CharSequence s,        Object o )   { stringValue._(s);                  objectValue= o; }

    /** Constructs a data object
     *  @param i    Integer value to store.
     *  @param o    Object to store.          */
    public LogData(                 int i, Object o )   {                   integerValue= i; objectValue= o; }

    /** Constructs a data object
     *  @param i    Integer value to store. */
    public LogData(                 int i           )   {                   integerValue= i;                 }
    
    /** ****************************************************************************************
     *  Provides a string representation of this object.
     *  @param target  The target AString.
     *  @returns The \p target, with string representation of the provided Scope value
     *           appended
     ******************************************************************************************/
    public AString toString( AString target )
    {
        target._( '[' );
        target._( '\"' )._( stringValue )._( "\"," );
        target._( integerValue );
        if ( objectValue != null )
            target._NC( ",<object>" );
        target._( ']' );

        return target;
    }

    /** ****************************************************************************************
     * This is for debugging purposes and for configuration output.
     * E.g. this enables the \e Eclipse IDE to display object descriptions in the debugger.
     * @returns A human readable string representation of this object.
     ******************************************************************************************/
    @Override 
    public String toString()
    {
        return toString(new AString()).toString();
    }    
}


