// #################################################################################################
//  Unit Tests - AWorx Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
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
