// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.strings.util;
import com.aworx.lib.strings.AString;
import java.io.IOException;
import java.io.PrintStream;
import java.io.Writer;

/** ************************************************************************************************
 * This is a simple class that provides a string full of spaces. This may be used to avoid
 * memory allocations/initializations.
 **************************************************************************************************/
public class Spaces
{
    // #############################################################################################
    // static functionality
    // #############################################################################################
        /** The internal string of spaces returned by #get and used by #write. */
        private static          AString          theSpaces                           =new AString();

        /**
         * A fixed size byte array of spaces used in #write(PrintStream, int). Unfortunately,
         * Java does not provide a method in PrintStream to write a portion of a character array,
         * therefore this is fixed (and redundant to field #theSpaces).
         */
        private static          byte[]           spacesByte;

   // #############################################################################################
   // Interface
   // #############################################################################################

        /** ****************************************************************************************
         * Receives an AString full of spaces. The AString returned must not be altered.
         * \attention
         *   Parameter \p minSize should be omitted and the size of the object returned accepted.
         *   Requesting a higher size, might result in slightly more efficiency.
         *   In multithreaded processes, changing the size must be performed during bootstrap,
         *   e.g. directly after invoking \ref com.aworx.lib.ALIB.init "ALIB.init" by calling
         *   this method with the appropriate size.
         *
         * @param minSize  The minimum number of spaces that should be available in the returned
         *                 AString. Defaults to 128. See notes in method description!
         *
         * @return A const AString filled with spaces.
         ******************************************************************************************/
        public static AString  get(int minSize)
        {
            int spacesLength= Spaces.theSpaces.length();
            if ( spacesLength < minSize )
            {
                synchronized( Spaces.theSpaces )
                {
                    spacesLength= Spaces.theSpaces.length();
                    if ( spacesLength < minSize )
                        Spaces.theSpaces.insertChars( ' ', minSize - spacesLength );
                }
            }

            return theSpaces;
        }

        /** ****************************************************************************************
         * Overloaded version of #get(int) providing default parameter 128.
         * It is recommended to generally use this method instead of the parameterized.
         *
         * @return A const AString filled with spaces.
         ******************************************************************************************/
        public static AString  get()
        {
            return get(128);
        }

        /** ****************************************************************************************
         * Write the given number of spaces to a Writer.
         * @param os    The output stream to write to
         * @param qty   The quantity of spaces to write
         ******************************************************************************************/
        public static void      write( Writer os, int qty )
        {
            AString spaces= get( 128 );
            int spacesLength= spaces.length();
            try
            {
                while ( qty > 0 )
                {
                    int size= qty < spacesLength ? qty : spacesLength;
                    os.write( spaces.buffer(), 0, size );
                    qty-= size;
                }
            }
            catch(@SuppressWarnings ("unused") IOException e)
            {
                com.aworx.lib.ALIB_DBG.ERROR( "IOException" );
            }
        }

         /** ****************************************************************************************
         * Write the given number of spaces to a PrintStream.
         * @param os    The output stream to write to
         * @param qty   The quantity of spaces to write
         ******************************************************************************************/
        public static void      write( PrintStream os, int qty )
        {
            if ( Spaces.spacesByte == null )
            {
                Spaces.spacesByte= new byte[64];
                for (int i= 0; i< 64; i++ )
                    Spaces.spacesByte[i]= 32;
            }

            while ( qty > 0 )
            {
                int size= qty < 64 ? qty : 64;
                os.write( Spaces.spacesByte, 0, size );
                qty-= size;
            }
        }
}
