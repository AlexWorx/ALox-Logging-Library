// #################################################################################################
//  cs.aworx.lox.detail - ALox Logging Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using cs.aworx.lib.lang;

using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;

using cs.aworx.lib;
using cs.aworx.lox;
using cs.aworx.lox.detail;

namespace cs.aworx.lib.strings.util  {


/** ************************************************************************************************
 * This class stores and manages tabulator positions and field sizes. The class supports a
 * simple session handling, by storing each value once for the actual output session and a
 * second time for a future session. The motivation for writing this class came from the
 * requirements of logging library \alox. The goals here are:
 *
 * - During a logging session, log output should be as much tabular as possible.
 * - On the same time, the log output should be as "narrow" as possible.
 *
 * If used correctly, this class helps to achieve the following:
 * - A new log-output session increases tab stops and field widths during execution as needed.
 * - If values need to be increased, a certain amount of "extra padding" might be
 *   added to avoid too many small increments.
 * - Once all tab stops or fields have been logged with values of their maximum size, the log output
 *   will not vary in respect to tab stops and autosizes any more.
 * - If a subsequent session contains the very same log-output (aka the same requested tab positions
 *   and field width), all extra space is removed and the log output is 100% tabular
 *   beginning with the session start.
 * - If a subsequent session contains smaller values, then this session is formatted with the
 *   (still larger) width of the previous session. After that, the next session will use the smaller
 *   sizes.
 *
 * This approach very well guarantees stable log output widths across sessions. Only if the
 * execution path of a software changes (or logging verbosity setting is changed), adjustments
 * are performed.
 *
 * To preserve the information across <em>sessions</em>, this class provides methods to transform
 * it's information from and to string representations which can be stored in configuration files.
 *
 * As the use case of this class is not restricted to log output, this class is exposed
 * as a general utility class of \alib strings.
 **************************************************************************************************/
public class AutoSizes
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
        /** The entry type, tab stop or field width. */
        public enum Types
        {
            Tabstop, ///< denotes a tab stop entry.
            Field,   ///< denotes a field width entry.
        }

    // #############################################################################################
    // Protected fields
    // #############################################################################################

        /** Actual and current session entries of tab stop indexes, respectively field widths. */
        protected class Entry
        {
            public Types type;         ///< The type of entry.
            public int   actual;       ///< The actually used tab stop or size
            public int   session;      ///< The maximum requested size in actual session.

            /**
             * Constructor.
             * @param t Value for field #type.
             * @param v Value for field #actual.
             * @param s Value for field #session.
             */
            public Entry( Types t, int v, int s )
            {
                type    = t;
                actual  = v;
                session = s;
            }
        }

        /** The current and measured sizes. */
        protected List<Entry>            data                                   = new List<Entry>();

        /** The number of entries used in #data.
         *  (The list is never cleared, instead entries are reused after a reset).  */
        protected int                    dataSize                                               = 0;

    // #############################################################################################
    // Public fields
    // #############################################################################################

        /**  The actual index requested by #Next. This is reset to 0 with every invocation of
         *   #Start. */
        public    int                    ActualIndex;

    // #############################################################################################
    // Protected methods
    // #############################################################################################

    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         * Resets the all values, current ones and the once of the currently measured session.
         ******************************************************************************************/
        public void     Reset ()
        {
            dataSize= 0;
            Start();
        }

        /** ****************************************************************************************
         * Consolidates the values. This method is usually not invoked directly.
         * Instead, it is invoked with method #Import.
         *
         * The method loops through all values and copies the session values to the actual ones.
         * The difference of both values is summed up during the loop and entries of type
         * \alib{strings::util::AutoSizes,Types.Tabstop} are adjusted by that difference.
         * As a result, the new values represent the smallest output format that fits all
         * rows, if the same output is performed as in the previous "session".
         ******************************************************************************************/
        public void    Consolidate()
        {
            int tabDiff     = 0;
            int lastTabStop = 0;
            for( int i= 0; i < dataSize; ++i )
            {
                Entry entry= data[i];
                int actDiff=  entry.session - entry.actual;
                if( actDiff > 0 ) // should never happen. Maybe improper data import?
                    actDiff= 0;
                if( entry.type == Types.Tabstop )
                {
                    // reset tab difference if (for some strange application specific reason) this
                    // tab stop is smaller than the previous one. Obviously some multi-line tab stop
                    // is used (does not happen for example with with ALox)
                    if( entry.actual > lastTabStop )
                    {
                        lastTabStop= entry.actual;
                        entry.actual= entry.session + tabDiff;
                    }
                    else
                    {
                        lastTabStop= entry.actual;
                        tabDiff= 0;
                        entry.actual= entry.session + tabDiff;
                    }
                }
                else
                {
                    entry.actual     = entry.session;
                }
                tabDiff+= actDiff;
                entry.session  = -1;
            }
        }

    /** ****************************************************************************************
         * Initializes a new query sequence, which is a series of invocations of method #Next.
         ******************************************************************************************/
        public void     Start ()
        {
            ActualIndex=   0;
        }

        /** ****************************************************************************************
         * Returns the actual auto value stored, respectively, if the given requested size is
         * higher than what is stored, stores and returns the requested size.
         *
         * In the latter case, the given extra growth is added to the requested size, but only if
         * the value was set at least once before. In other words, the extra size is added only with
         * the second growth and each subsequent one.
         *
         * The requested size in addition replaces the current "session" value if it is higher than
         * the currently stored value. To this value, the growth padding is not added.
         *
         * @param type           The type of entry.
         * @param requestedSize  The minimum size that is requested.
         * @param growthPadding  Added to the new size, if the requested size is greater than
         *                       the stored size and if the stored size does not equal \c -1.
         *
         * @return The (new) size of the auto field.
         ******************************************************************************************/
        public int      Actual  ( Types type, int requestedSize, int growthPadding )
        {
            // grow array as needed
            while ( dataSize <= ActualIndex )
            {
                dataSize++;
                if( dataSize > data.Count )
                    data.Add( new Entry(type, -1, -1 ));
                else
                {
                    Entry newEntry= data[dataSize-1];
                    newEntry.actual = -1;
                    newEntry.session= -1;
                }

            }

            Entry entry= data[ ActualIndex ];
            entry.type= type;

            // set measured size as it would be for the next session
            int session=    entry.session;
            if ( session < requestedSize )
            {
                entry.session =  requestedSize;
            }

            // get size as it is for actual values (the ones that might have been imported)
            int actual=       entry.actual;
            if ( actual <  requestedSize )
            {
                actual=  entry.actual=  (requestedSize + ( actual    < 0 ? 0 : growthPadding ));
            }

            return actual;
        }

        /** ****************************************************************************************
         * Invokes #Actual and then increases the internal position counter.
         *
         * @param type            The type of entry.
         * @param requestedSize   The minimum size that is requested.
         * @param growthPadding   Added to the new size if the requested size is greater than
         *                        the stored size and if the stored size does not equal \c -1.
         *
         * @return The (new) size of the auto field.
         ******************************************************************************************/
        public int      Next  ( Types type, int requestedSize, int growthPadding )
        {
            int result= Actual( type, requestedSize, growthPadding );
            ActualIndex++;
            return result;
        }

        /** ****************************************************************************************
         * Exports the current session values by converting the stored values to a string
         * representation and appending them to the given \alib{strings,AString} object.
         *
         * The format of the entries written into the string is <c>"(T|F,Actual,Measured)</c>
         * which should be self-explanatory.
         *
         * @param target       The \b %AString to receive the our values
         ******************************************************************************************/
        public void     Export( AString target )
        {
            for( int i= 0; i < dataSize; ++i )
            {
                Entry entry= data[i];
                target._( '(' ) ._( entry.type == Types.Tabstop ? 'T' : 'F')._( ',' )
                                ._( entry.actual                           )._( ',' )
                                ._( entry.session                          )         ._( ')' );
            }

            // remove unused entries at the end
            while( target.EndsWith(",0,0)" ) )
                target.DeleteEnd(target.Length() - target.LastIndexOf('('));
        }

        /** ****************************************************************************************
         * Imports values from the given \alib{strings,Substring} by parsing it.
         * Usually, string data are used for importing values was previously generated
         * with method #Export.
         *
         * If parameter \p{session} equals \alib{lang::CurrentData,Clear} (which is the default),
         * then after the import, method #Consolidate is invoked.
         *
         * \note
         *   Parsing is 100% error tolerant. If the given string does not contain what is expected
         *   (see method #Export), then only a part or just nothing is imported.
         *   This is due to the purpose of this class, which is to allow nicer, tabbed output.
         *   If this is not possible due to import problems, the system should work normally still.<br>
         *   In debug compilations, an \ref ALIB_DBG.WARNING is written.
         *
         *
         * @param source    The \b %String that is parsed for the exported data.
         * @param session   Denotes if #Consolidate is to be invoked after import.
         *                  Defaults to \alib{lang::CurrentData,Clear}.
         ******************************************************************************************/
        public void     Import( Substring source, CurrentData session = CurrentData.Clear )
        {
            Reset();

            Substring parser= new Substring( source );
            while(parser.Trim().IsNotEmpty())
            {
                parser.TrimStart();
                Types type;
                if( !parser.ConsumeChar( '(', Case.Sensitive, Whitespaces.Trim ) )
                {
                    ALIB_DBG.WARNING( "Error reading tab stops string {!Q}:\\n   at position {}",
                                      source, source.Length() - parser.Length() );
                    break;
                }

                if( parser.ConsumeChar( 'T', Case.Ignore, Whitespaces.Trim ) )
                    type= Types.Tabstop;
                else if( parser.ConsumeChar( 'F', Case.Ignore, Whitespaces.Trim ) )
                    type= Types.Field;
                else
                {
                    ALIB_DBG.WARNING( "Error reading tab stops string {!Q}:\\n   at position {}",
                                      source, source.Length() - parser.Length() );
                    break;
                }

                if( !parser.ConsumeChar( ',', Case.Sensitive, Whitespaces.Trim ) )
                {
                    ALIB_DBG.WARNING( "Error reading tab stops string {!Q}:\\n   at position {}",
                                      source, source.Length() - parser.Length() );
                    break;
                }


                int   actual;
                parser.ConsumeInt( out actual        );

                if( !parser.ConsumeChar( ',', Case.Sensitive, Whitespaces.Trim ) )
                {
                    ALIB_DBG.WARNING( "Error reading tab stops string {!Q}:\\n   at position {}",
                                      source, source.Length() - parser.Length() );
                    break;
                }


                int   sessionValue;
                parser.ConsumeInt( out sessionValue );

                if( !parser.ConsumeChar( ')', Case.Sensitive, Whitespaces.Trim ) )
                {
                    ALIB_DBG.WARNING( "Error reading tab stops string {!Q}:\\n   at position {}",
                                      source, source.Length() - parser.Length() );
                    break;
                }

                if( dataSize++ == data.Count )
                    data.Add( new Entry(type, actual, sessionValue) );
                else
                {
                    Entry entry= data[dataSize-1];
                    entry.type   = type;
                    entry.actual = actual;
                    entry.session= sessionValue;
                }
            }

            if( session == CurrentData.Clear )
                Consolidate();
        }

        /** ****************************************************************************************
         * Imports values from the given AString by parsing it using overloaded method #Import.
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

