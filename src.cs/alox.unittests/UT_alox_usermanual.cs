// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


using cs.aworx.lox;
using cs.aworx.lib.enums;
using cs.aworx.lox.loggers;

class ManualSampleCode
{


public void LogLevelsAndDomains_Chapter3()
{
//! [Man_LAD_3___1]
Log.SetDomain( "UI",        Log.Scope.None );
Log.SetDomain( "UI/MENU",   Log.Scope.None );
Log.SetDomain( "UI/DLG",    Log.Scope.None );
//! [Man_LAD_3___1]

//! [Man_LAD_3___2]
Log.SetDomain( "UI",        Log.DomainLevel.InfoWarningsAndErrors );
Log.SetDomain( "UI/MENU",   Log.DomainLevel.InfoWarningsAndErrors );
Log.SetDomain( "UI/DLG",    Log.DomainLevel.InfoWarningsAndErrors );
//! [Man_LAD_3___2]

//! [Man_LAD_3___3]
Log.SetDomain( "UI",        Log.DomainLevel.InfoWarningsAndErrors );
//! [Man_LAD_3___3]

//! [Man_LAD_3___4]
Log.SetDomain( "UI",        Log.DomainLevel.InfoWarningsAndErrors );
Log.SetDomain( "UI/DLG",    Log.DomainLevel.Errors );
//! [Man_LAD_3___4]

//! [Man_LAD_3___5]
Log.SetDomain( "UI/DLG",    Log.DomainLevel.Errors );
Log.SetDomain( "UI",        Log.DomainLevel.InfoWarningsAndErrors );
//! [Man_LAD_3___5]

//! [Man_LAD_3___6]
Log.SetDomain( "UI/DLG",    Log.DomainLevel.Errors );
Log.SetDomain( "UI",        Log.DomainLevel.InfoWarningsAndErrors, null, Propagation.None );
//! [Man_LAD_3___6]
}


public void LogLevelsAndDomains_Chapter4()
{
//! [Man_LAD_4___1]
Log.SetDomain( "/", Log.DomainLevel.Off, "Console" );
//! [Man_LAD_4___1]


//! [Man_LAD_4___2]
// our release logger, this is created somewhere in the bootstrap section of our application
Lox releaseLox= new Lox();

TextFileLogger releaseLogger= new TextFileLogger("logs_from_field.txt");
releaseLogger.SetDomain( releaseLox.InternalDomain, Log.DomainLevel.Off );

releaseLox.AddLogger( releaseLogger );

//...
//...
//...

// Somewhere in our application, we can now activate (e.g. based on a 'undocumented'
// configuration parameter) some domain:
releaseLogger.SetDomain( "MYAPP/DATABASE",  Log.DomainLevel.InfoWarningsAndErrors );
//! [Man_LAD_4___2]

}


public void LogLevelsAndDomains_Chapter5()
{
//! [Man_LAD_5___1]
Log.SetDomain( "UI",        Log.Scope.SourceFile );
Log.SetDomain( "UI/MENU",   Log.Scope.None );
Log.SetDomain( "UI/DLG",    Log.Scope.None );
//! [Man_LAD_5___1]

//! [Man_LAD_5___2]
Log.Info( "UI", "User interface initialized" );
Log.Info( "User interface initialized" );
//! [Man_LAD_5___2]
}

public void LogLevelsAndDomains_Chapter6()
{
//! [Man_LAD_6___1]
Log.SetDomain( "UI",        Log.Scope.SourceFile );
Log.SetDomain( "UI/MENU",   Log.Scope.None );
Log.SetDomain( "UI/DLG",    Log.Scope.None );
//! [Man_LAD_6___1]

//! [Man_LAD_6___2]
Log.Info( "UI/DLG", "Dialog opened" );
Log.Info( "~/DLG",  "Dialog opened" );
//! [Man_LAD_6___2]
}

public void LogLevelsAndDomains_Chapter7()
{
//! [Man_LAD_7___1]
Lox aLox= new Lox();
aLox.InternalDomain=    "MYAPP/OTHERS/ALOX";
//! [Man_LAD_7___1]

//! [Man_LAD_7___2]
#if ALOX_DBG_LOG
    Log.LOX.InternalDomain= "MYAPP/OTHERS/ALOX";
#endif
//! [Man_LAD_7___2]

//! [Man_LAD_7___3]
// set internal messages of for all logers in our private Lox
aLox.SetDomain( aLox.InternalDomain,   Log.DomainLevel.Off );

// Observe into ALox configuration changes in our debug logger
#if ALOX_DBG_LOG
    Log.SetDomain( Log.LOX.InternalDomain, Log.DomainLevel.All, "DEBUG_LOGGER" );
#endif
//! [Man_LAD_7___3]
}

}

