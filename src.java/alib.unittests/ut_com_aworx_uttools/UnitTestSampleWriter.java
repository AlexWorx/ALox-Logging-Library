// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_aworx_uttools;

import java.io.*;

public class UnitTestSampleWriter
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
                        try{ dir.mkdir();  }   catch(SecurityException se) { }        
                    generatedSamplesDir= generatedSamplesDir + "/";

                    break;
                }
                testDir=  "../" + testDir;
            }
        }
        return generatedSamplesDir;
    }
    
    public UnitTestSampleWriter(String filename)
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
    
