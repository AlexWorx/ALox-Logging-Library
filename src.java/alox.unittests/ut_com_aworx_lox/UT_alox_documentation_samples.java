// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_aworx_lox;

import org.junit.Test;
import com.aworx.lox.*;


public class UT_alox_documentation_samples
{

void docSampleESC()
{
//! [DOC_SAMPLES_ALOX_ESC]
Log.info( "The result is " + ESC.RED + "42" );
//! [DOC_SAMPLES_ALOX_ESC]
}

    /** ********************************************************************************************
     *     Log_TestLogLevelSetting
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void UT_Doc_Samples()
    {
        docSampleESC();
    }
}
