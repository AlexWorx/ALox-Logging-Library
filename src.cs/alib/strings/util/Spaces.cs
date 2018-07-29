// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using cs.aworx.lib.strings;
using System.IO;
using cs.aworx.lib.lang;
using cs.aworx.lib.threads;

namespace cs.aworx.lib.strings.util  {

/** ************************************************************************************************
 * This is a simple class that provides a string full of spaces. This may be used to avoid
 * memory allocations/initializations.
 **************************************************************************************************/
public class Spaces
{
    // #############################################################################################
    // static functionality
    // #############################################################################################
        /** The internal string of spaces returned by #Get and used by #Write. */
        private static         AString          theSpaces                            =new AString();

    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         * Receives an AString full of spaces. The AString returned must not be altered.
         * \attention
         *   Parameter \p{minSize} should be omitted and the size of the object returned accepted.
         *   Requesting a higher size, might result in slightly more efficiency.
         *   In multithreaded processes, changing the size must be performed during bootstrap,
         *   e.g. directly after invoking \ref cs.aworx.lib.ALIB.Init "ALIB.Init" by calling
         *   this method with the appropriate size.
         *
         * @param minSize  The minimum number of spaces that should be available in the returned
         *                 AString. Defaults to 128. See notes in method description!
         *
         * @return A const AString filled with spaces.
         ******************************************************************************************/
        public static AString  Get(int minSize= 128)
        {
            int spacesLength= Spaces.theSpaces.Length();
            if ( spacesLength < minSize )
            {
                lock(theSpaces)
                {
                    spacesLength= Spaces.theSpaces.Length();
                    if ( spacesLength < minSize )
                        Spaces.theSpaces.InsertChars( ' ', minSize - spacesLength );
                }
            }

            return theSpaces;
        }

        /** ****************************************************************************************
         * Write the given number of spaces to a StreamWriter.
         * @param os    The output stream to write to
         * @param qty   The quantity of spaces to write
         ******************************************************************************************/
        public static void             Write( StreamWriter os, int qty )
        {
            AString spaces= Get();
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
        public static void             Write( TextWriter os, int qty )
        {
            AString spaces= Get();
            int spacesLength= spaces.Length();
            while ( qty > 0 )
            {
                int size= qty < spacesLength ? qty : spacesLength;
                os.Write( spaces.Buffer(), 0, size );
                qty-= size;
            }
        }
}

} // namespace / EOF
