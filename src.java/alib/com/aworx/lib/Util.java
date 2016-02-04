// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib;

import java.io.IOException;
import java.io.PrintStream;
import java.io.Writer;

import com.aworx.lib.strings.AString;

/** ************************************************************************************************
 *  This class aggregates functionality that is simple and not connected and (in this version
 *  of ALib) did not find a better home.
 **************************************************************************************************/
public class Util
{
    // #############################################################################################
    // static functionality
    // #############################################################################################
        /** The internal string of spaces returned by #getSpaces and used by #writeSpaces. */
        private static          AString          theSpaces=                           new AString();

        /**
         * A fixed size byte array of spaces used in #writeSpaces(PrintStream, int). Unfortunately,
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
         *   e.g. directly after invoking \ref com.aworx::lib::ALIB::init "ALIB.init" by calling
         *   this method with the appropriate size.
         *
         * @param minSize  The minimum number of spaces that should be available in the returned
         *                 AString. Defaults to 128. See notes in method description!
         *
         * @return A const AString filled with spaces.
         ******************************************************************************************/
        public static AString  getSpaces(int minSize)
        {
            int spacesLength= Util.theSpaces.length();
            if ( spacesLength < minSize )
            {
                synchronized( Util.theSpaces )
                {
                    spacesLength= Util.theSpaces.length();
                    if ( spacesLength < minSize )
                        Util.theSpaces.insertChars( ' ', minSize - spacesLength );
                }
            }

            return theSpaces;
        }

        /** ****************************************************************************************
         * Overloaded version of #getSpaces(int) providing default parameter 128.
         * It is recommended to generally use this method instead of the parameterized.
         *
         * @return A const AString filled with spaces.
         ******************************************************************************************/
        public static AString  getSpaces()
        {
            return getSpaces(128);
        }

        /** ****************************************************************************************
         * Write the given number of spaces to a Writer.
         * @param os    The output stream to write to
         * @param qty   The quantity of spaces to write
         ******************************************************************************************/
        public static void      writeSpaces( Writer os, int qty )
        {
            AString spaces= getSpaces( 128 );
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
            catch(IOException e)
            {
                ALIB.ERROR( "IOException" );
            }
        }

         /** ****************************************************************************************
         * Write the given number of spaces to a PrintStream.
         * @param os    The output stream to write to
         * @param qty   The quantity of spaces to write
         ******************************************************************************************/
        public static void      writeSpaces( PrintStream os, int qty )
        {
            if ( Util.spacesByte == null )
            {
                Util.spacesByte= new byte[64];
                for (int i= 0; i< 64; i++ )
                    Util.spacesByte[i]= 32;
            }

            while ( qty > 0 )
            {
                int size= qty < 64 ? qty : 64;
                os.write( Util.spacesByte, 0, size );
                qty-= size;
            }
        }

} // class Util
