// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.strings.util;

import com.aworx.lib.lang.CurrentData;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;

/** ************************************************************************************************
 * Auto sizes are used for tabulator positions and field sizes that expand automatically when they
 * are exceeded. This way, any next line will have that new, expanded tabs and field sizes set
 * leading to a nicely formatted, but still flexible, minimized width of output.
 *
 * To preserve the information across <em>sessions</em>, this class provides methods to transform
 * it's information from and to string representations which can be stored in configuration files.
 *
 * All values are doubly stored: once for the session and once for the last imported values.
 * Those values that were imported are used for getting the actual size. However, those that are
 * stored for the session are the ones that would have been created if there was no import done.
 * This leads to the fact that the session values may be smaller than the actual (imported) ones.
 * This mechanism, in combination with the fact that on importing it can be decided if the session
 * is newly started or not, allows the values to shrink again over different sessions.
 *
 **************************************************************************************************/
public class AutoSizes
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################
        /** The current sizes                                */
        protected int[]                  values=                                     new int[5];

        /** The sizes measured in this session. These are the ones that will be received in method
         *  #toString                                        */
        protected int[]                  sessionValues=                              new int[5];

        /**  The number of currently stored values              */
        protected int                    length;

    // #############################################################################################
    // Public fields
    // #############################################################################################
        /**  The actual index requested by #next. This is reset to 0 with every invocation of
         *   #start. */
        public    int                    actualIndex;

    // #############################################################################################
    // Protected methods
    // #############################################################################################
        /** ****************************************************************************************
         * Resizes our arrays with preserving the current values.
         *
         * @param minArraySize   The minimum size that is requested for the value arrays.
         ******************************************************************************************/
        protected void ensureArraySize( int minArraySize )
        {
            // grow arrays as needed
            if ( values.length < minArraySize )
            {
                // create a bigger array and copy old values
                int[] newValues=        new int[ minArraySize * 2];
                int[] newSessionValues= new int[ minArraySize * 2];
                for ( int i= 0; i < values.length ; i++ )
                {
                    newValues[i]=           values[i];
                    newSessionValues[i]=    sessionValues[i];
                }
                values=         newValues;
                sessionValues=  newSessionValues;
            }
        }

    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         * Resets the whole object. All values get deleted.
         ******************************************************************************************/
        public void        reset ()
        {
            for ( int i= 0; i< values.length; i++ )
                sessionValues[i]= values[i]= 0;
            length= 0;
        }

        /** ****************************************************************************************
         * Initializes a new query sequence, which is a series of invocations of method #next.
         ******************************************************************************************/
        public void        start ()
        {
            actualIndex=   0;
        }

        /** ****************************************************************************************
         * Returns the actual auto value stored, respectively, if the given requested size is
         * higher, stores and returns the requested size. The given extra growth is added to the
         * requested size if the currently stored value is unequal to 0. In other words, the extra
         * size is added only with the second growth and each subsequent one.
         *
         * @param requestedSize   The minimum size that is requested.
         * @param extraGrowth     Added to the new size if the requested size is greater than
         *                        the stored size and if the stored size does not equal 0.
         *
         * @return The (new) size of the auto field.
         ******************************************************************************************/
        public int         actual( int requestedSize, int extraGrowth )
        {
            // grow arrays as needed
            ensureArraySize( actualIndex + 1 );

            // remember the size of the used arrays (for exporting)
            if (length == actualIndex )
                length++;

            // get size as it would be for this session (for saving the session later)
            int size=    sessionValues[ actualIndex ];
            if ( size <  requestedSize )
                sessionValues[ actualIndex ]=  requestedSize + ( size == 0 ? 0 : extraGrowth );

            // get size as it is for actual values (the ones that might have been imported)
            size=    values[ actualIndex ];
            if ( size <  requestedSize )
            {
                size=
                values[ actualIndex ]=        requestedSize + ( size == 0 ? 0 : extraGrowth );
            }

            return size;
        }

        /** ****************************************************************************************
         * Invokes #actual and then increases the internal position counter.
         *
         * @param requestedSize   The minimum size that is requested.
         * @param extraGrowth     Added to the new size if the requested size is greater than
         *                        the stored size and if the stored size does not equal 0.
         *
         * @return The (new) size of the auto field.
         ******************************************************************************************/
        public int         next  ( int requestedSize, int extraGrowth )
        {
            int result= actual( requestedSize, extraGrowth );
            actualIndex++;
            return result;
        }

        /** ****************************************************************************************
         * Imports values from the given substring by parsing it. The numbers in the string have
         * to be separated by ' ' characters (space).
         *
         * @param source    The Substring that is parsed for the numbers
         * @param session   If \c CurrentData.CLEAR, which is the default, the current values
         *                  are taken from the last session stored and the sessions data is set to 0.
         *                  If \c CurrentData.KEEP, both, current values and
         *                  session values are taken from the string.
         ******************************************************************************************/
        public void         importValues( Substring source, CurrentData session )
        {
            reset();
            length= 0;
            for(;;)
            {
                int actStart=    source.start;
                int value;       source.consumeInt(); value=       (int) source.consumedLong;
                int lastSession; source.consumeInt(); lastSession= (int) source.consumedLong;
                if ( actStart == source.start )
                    break;

                ensureArraySize( length + 1 );
                values       [length]=   session == CurrentData.CLEAR ? lastSession : value;
                sessionValues[length]=   session == CurrentData.CLEAR ? 0           : lastSession;
                length++;
            }
        }

        /** ****************************************************************************************
         * Imports values from the given substring by parsing it. The numbers in the string have
         * to be separated by ' ' characters (space).
         * If the provided boolean parameter \p newSession is set to true, then the current
         * session values are set to 0. Else they are set to be the same as the imported values.
         *
         * @param source       The Substring that is parsed for the numbers
         ******************************************************************************************/
        public void         importValues( Substring source )
        {
            importValues( source, CurrentData.CLEAR );
        }

        /** ****************************************************************************************
         * Imports values from the given AString by parsing it. The numbers in the string have
         * to be separated by ' ' characters (space).<br>
         * The session values in the string are ignored (starts a new session).
         *
         * @param source   The AString that is parsed for the numbers
         * @param session   If \c CurrentData.KEEP the current values are stored to be the last
         *                  sessions' data and current values are set to 0.
         *                  If \c CurrentData.CLEAR, which is the default, both, current values and
         *                  session values are taken from the string.
         ******************************************************************************************/
        public void         importValues( AString source, CurrentData session )
        {
            importValues( new Substring( source ), session );
        }

        /** ****************************************************************************************
         * Imports values from the given AString by parsing it. The numbers in the string have
         * to be separated by ' ' characters (space).<br>
         * The session values in the string are ignored (starts a new session).
         *
         * @param source       The AString that is parsed for the numbers
         ******************************************************************************************/
        public void         importValues( AString source )
        {
            importValues( new Substring( source ) );
        }

        /** ****************************************************************************************
         * Exports the current session values by converting the stored numbers to a string
         * representation and appending them to the given AString object.
         * The numbers in the string will be separated by ' ' characters (space).
         *
         * @param target       The Substring that is parsed for the numbers
         ******************************************************************************************/
        public void         exportValues( AString target )
        {
            for( int i= 0; i < length ; i++ )
            {
                if ( i != 0 )
                    target._( ' ' );
                target._(        values[ i ] );
                target._( ' ' );
                target._( sessionValues[ i ] );
            }

            while( target.endsWith(" 0 0" ) )
                target.deleteEnd(4);
        }

        /** ****************************************************************************************
         * This is for debugging purposes. E.g. this enables the \e Eclipse IDE to display
         * object descriptions in the debugger.
         * @returns A human readable string representation of this object.
         ******************************************************************************************/
        @Override
        public String toString()
        {
            AString target= new AString();
            exportValues( target );
            return target.toString();
        }
}
