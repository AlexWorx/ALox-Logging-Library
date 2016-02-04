// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using cs.aworx.lib.strings;
using System.IO;

namespace cs.aworx.lib {

/** ************************************************************************************************
 *  This class aggregates functionality that is simple and not connected and (in this version
 *  of ALib) did not find a better home.
 **************************************************************************************************/
public class Util
{
    // #############################################################################################
    // static functionality
    // #############################################################################################
        /** The internal string of spaces returned by #GetSpaces and used by #WriteSpaces. */
        private static         AString          theSpaces=                            new AString();

    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         * Receives an AString full of spaces. The AString returned must not be altered.
         * \attention
         *   Parameter \p minSize should be omitted and the size of the object returned accepted.
         *   Requesting a higher size, might result in slightly more efficiency.
         *   In multithreaded processes, changing the size must be performed during bootstrap,
         *   e.g. directly after invoking \ref aworx::lib::ALIB::Init "ALIB.Init" by calling
         *   this method with the appropriate size.
         *
         * @param minSize  The minimum number of spaces that should be available in the returned
         *                 AString. Defaults to 128. See notes in method description!
         *
         * @return A const AString filled with spaces.
         ******************************************************************************************/
        public static AString  GetSpaces(int minSize= 128)
        {
            int spacesLength= Util.theSpaces.Length();
            if ( spacesLength < minSize )
            {
                try { ALIB.Lock.Acquire();
                    spacesLength= Util.theSpaces.Length();
                    if ( spacesLength < minSize )
                        Util.theSpaces.InsertChars( ' ', minSize - spacesLength );
                } finally { ALIB.Lock.Release(); }
            }

            return theSpaces;
        }

        /** ****************************************************************************************
         * Write the given number of spaces to a StreamWriter.
         * @param os    The output stream to write to
         * @param qty   The quantity of spaces to write
         ******************************************************************************************/
        public static void             WriteSpaces( StreamWriter os, int qty )
        {
            AString spaces= GetSpaces();
            int spacesLength= spaces.Length();
            while ( qty > 0 )
            {
                int size= qty < spacesLength ? qty : spacesLength;
                os.Write( spaces.Buffer(), 0, size );
                qty-= size;
            }
        }

        /** ****************************************************************************************
         * Write the given number of spaces to a TextWriter.
         * @param os    The output stream to write to
         * @param qty   The quantity of spaces to write
         ******************************************************************************************/
        public static void             WriteSpaces( TextWriter os, int qty )
        {
            AString spaces= GetSpaces();
            int spacesLength= spaces.Length();
            while ( qty > 0 )
            {
                int size= qty < spacesLength ? qty : spacesLength;
                os.Write( spaces.Buffer(), 0, size );
                qty-= size;
            }
        }

} // class Util


} // namespace / EOF
