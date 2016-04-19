// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_alox;

import org.junit.Test;

import ut_com_aworx_uttools.AUnitTest;

import com.aworx.lox.*;


public class UT_dox_reference_manual extends AUnitTest
{

void docSampleESC()
{
//! [DOC_SAMPLES_ALOX_ESC]
Log.info( "The result is " + ESC.RED + "42" );
//! [DOC_SAMPLES_ALOX_ESC]
}

    /** ********************************************************************************************
     *     Log_TestVerbositySetting
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void UT_Doc_Samples()
    {
        UT_INIT();
        
        docSampleESC();
    }
}
