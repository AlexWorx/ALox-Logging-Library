// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#if defined (ALOX_DBG_LOG)

    void Log_ScopeDomains_HPPHelper()
    {
        Log_Info("");
    }

#endif

#if defined (ALOX_REL_LOG)

    void Lox_ScopeDomains_HPPHelper(Lox& lox)
    {
        #define LOX_LOX lox
        Lox_Info("");
        #undef LOX_LOX
    }
#endif
