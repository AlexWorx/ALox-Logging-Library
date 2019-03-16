// #################################################################################################
//  ut_com_aworx - AWorx Unit Test Support using ALib and ALox
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
//
//  Relies on ALox logging library, which in turn relies on ALib. Hence, ALibs' unit
//  tests can only be compiled if ALox library is present.
// #################################################################################################
package ut_com_aworx;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;

public class UTSampleWriter
{
    protected PrintStream      origOut;
    protected PrintStream      utWriter;
    protected static String    generatedSamplesDir= null;

    // defaults to "docs/ALox.CS/".
    // Set this to a suitable value in your bootstrap code, before using this class with
    // other projects!
    public    static String    generatedSamplesSearchDir= "docs/ALox.Java";

    public static String getGeneratedSamplesDir()
    {

        // if invoked the first time, search the right directory
        if ( generatedSamplesDir == null )
        {
            generatedSamplesDir= "";
            String testDir= "../" + generatedSamplesSearchDir;
            for( int depth= 0; depth < 10 ; depth++ )
            {
                if ( (new File(testDir)).exists() )
                {
                    generatedSamplesDir= testDir + "/generated";
                    File dir = new File(generatedSamplesDir);
                    if (!dir.exists())
                        try{ dir.mkdir();  }   catch(@SuppressWarnings ("unused") SecurityException se) { /* void */}
                    generatedSamplesDir= generatedSamplesDir + "/";

                    break;
                }
                testDir=  "../" + testDir;
            }
        }
        return generatedSamplesDir;
    }

    public UTSampleWriter(String filename)
    {
        if ( getGeneratedSamplesDir().length() == 0 )
            return;

        origOut= System.out;

        // write
        try
        {
            utWriter= new PrintStream(new BufferedOutputStream(new FileOutputStream(getGeneratedSamplesDir() + filename)));
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }


        System.setOut( utWriter );

        System.out.println( "//! [OUTPUT]" );
    }

    public void flushAndResetSystemOut()
    {
        if ( getGeneratedSamplesDir().length() == 0 )
            return;
        System.out.println( "//! [OUTPUT]" );
        utWriter.close();
        System.setOut(  origOut );
    }



} // class UnitTestSampleWriter

