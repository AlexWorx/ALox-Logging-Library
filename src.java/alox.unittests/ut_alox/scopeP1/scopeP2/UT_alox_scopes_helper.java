// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_alox.scopeP1.scopeP2;

import com.aworx.lox.*;


public class UT_alox_scopes_helper
{
    public static void help()
    {
        Log.setDomain( "HCLASS",      Scope.CLASS  );
        Log.setDomain( "HMETHOD",     Scope.METHOD      );
        Log.info("");
    }
}
