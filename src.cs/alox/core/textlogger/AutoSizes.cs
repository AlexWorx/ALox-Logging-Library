// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;

#if (ALOX_DBG_LOG || ALOX_REL_LOG)

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using cs.aworx.lib;
using cs.aworx.lox;
using cs.aworx.lox.core;

namespace cs.aworx.lox.core.textlogger
{


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
        /** The current sizes                                 */
        protected int[]                  values=                                     new int[5];

        /** The sizes measured in this session. These are the ones that will be received in method
         *  #ToString                                         */
        protected int[]                  sessionValues=                              new int[5];

        /**  The number of currently stored values            */
        protected int                    length;

    // #############################################################################################
    // Public fields
    // #############################################################################################

        /**  The actual index requested by #Next. This is reset to 0 with every invocation of
         *   #Start. */
        public    int                    ActualIndex;

    // #############################################################################################
    // Protected methods
    // #############################################################################################
        /** ****************************************************************************************
         *  Resizes our arrays with preserving the current values.
         *
         * @param minArraySize   The minimum size that is requested for the value arrays.
         ******************************************************************************************/
        protected void  ensureArraySize( int minArraySize )
        {
            // grow arrays as needed
            if ( values.Length < minArraySize )
            {
                // create a bigger array and copy old values
                int[] newValues=        new int[ minArraySize * 2];
                int[] newSessionValues= new int[ minArraySize * 2];
                for ( int i= 0; i < values.Length ; i++ )
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
         *  Resets the whole object. All values get deleted.
         ******************************************************************************************/
        public void     Reset ()
        {
            for ( int i= 0; i< values.Length; i++ )
                sessionValues[i]= values[i]= 0;
            length= 0;
        }

        /** ****************************************************************************************
         *  Initializes a new query sequence, which is a series of invocations of method #Next.
         ******************************************************************************************/
        public void     Start ()
        {
            ActualIndex=   0;
        }

        /** ****************************************************************************************
         *  Returns the next auto value stored, respectively, if the given requested size is higher,
         *  then stores and returns the requested size. The given extra growth is added to the
         *  requested size if the currently stored value is unequal to 0. In other words, the extra
         *  size is added only with the second growth and each subsequent one.
         *
         * @param requestedSize   The minimum size that is requested.
         * @param extraGrowth     Added to the new size if the requested size is greater than
         *                        the stored size and if the stored size does not equal 0.
         *
         * @return The (new) size of the auto field.
         ******************************************************************************************/
        public int      Next  ( int requestedSize, int extraGrowth )
        {
            // grow arrays as needed
            ensureArraySize( ActualIndex + 1 );

            // remember the size of the used arrays (for exporting)
            if (length == ActualIndex )
                length++;

            // get size as it would be for this session (for saving the session later)
            int size=    sessionValues[ ActualIndex ];
            if ( size <  requestedSize )
                sessionValues[ ActualIndex ]=  requestedSize + ( size == 0 ? 0 : extraGrowth );

            // get size as it is for actual values (the ones that might have been imported)
            size=    values[ ActualIndex ];
            if ( size <  requestedSize )
            {
                size=
                values[ ActualIndex ]=        requestedSize + ( size == 0 ? 0 : extraGrowth );
            }

            // increase auto tab index
            ActualIndex++;

            return size;

        }

        /** ****************************************************************************************
         *  Imports values from the given substring by parsing it. The numbers in the string have
         *  to be separated by ' ' characters (space).
         *
         * @param source    The Substring that is parsed for the numbers
         * @param session   If \c CurrentData::Clear, which is the default, the current values
         *                  are taken from the last session stored and the sessions data is set to 0.
         *                  If \c CurrentData::Keep, both, current values and
         *                  session values are taken from the string.
         ******************************************************************************************/
        public void     Import( Substring source, CurrentData session = CurrentData.Clear )
        {
            Reset();
            length= 0;
            for(;;)
            {
                int actStart=    source.Start;
                int value;       source.ConsumeInteger( out value );
                int lastSession; source.ConsumeInteger( out lastSession );
                if ( actStart == source.Start )
                    break;
                ensureArraySize( length + 1 );
                values       [length]=   session == CurrentData.Clear ? lastSession : value;
                sessionValues[length]=   session == CurrentData.Clear ? 0           : lastSession;
                length++;
            }
        }

        /** ****************************************************************************************
         *  Imports values from the given AString by parsing it using #Export.
         *
         * @param source    The AString that is parsed for the numbers
         * @param session   If \c CurrentData.Keep the current values are stored to be the last
         *                  sessions' data and current values are set to 0.
         *                  If \c CurrentData.Clear, which is the default, both, current values and
         *                  session values are taken from the string.
         ******************************************************************************************/
        public void     Import( AString source, CurrentData session = CurrentData.Clear )
        {
            Import( new Substring( source ), session );
        }

        /** ****************************************************************************************
         *  Exports the current session values by converting the stored numbers to a string
         *  representation and appending them to the given AString object.
         *  The numbers in the string will be separated by ' ' characters (space).
         *
         * @param target       The Substring that is parsed for the numbers
         ******************************************************************************************/
        public void     Export( AString target )
        {
            for( int i= 0; i < length ; i++ )
            {
                if ( i != 0 )
                    target._( ' ' );
                target._(        values[ i ] );
                target._( ' ' );
                target._( sessionValues[ i ] );
            }
            while( target.EndsWith(" 0 0" ) )
                target.DeleteEnd(4);
        }

        /** ****************************************************************************************
         * This is for debugging purposes. E.g. this enables the \e Monodevelop IDE to display
         * object descriptions in the debugger.
         * @returns A human readable string representation of this object.
         ******************************************************************************************/
        public override String ToString()
        {
            AString target= new AString();
            Export( target );
            return target.ToString();
        }

} // class
} // namespace

#endif
