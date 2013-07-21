using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using com.aworx.lox;
using com.aworx.util;
using com.aworx.lox.loggers;

namespace ALox_CS_Test_Perf	 {

class ReleaseLogTest
{
	// #################################################################################################
	// static entrance (Main)
	// #################################################################################################
	static void Main( string[] args )
	{
		ReleaseLogTest test= new ReleaseLogTest();
		test.test();
	}

	// #################################################################################################
	// Fields
	// #################################################################################################
	ConsoleLogger cl;

	// #################################################################################################
	// Test functions
	// #################################################################################################
	
	void test()
	{
		Lox lox= new Lox();
		lox.AddLogger(	cl=	new ConsoleLogger( "Console" ) );

		cl.EnableAppConsole= true;

		lox.RegDomain( "RelLog", Log.Scope.SourceFile );
		lox.SetDomain( "RelLog", Log.DomainLevel.All  );

		lox.Info( "Hello ALox, thank you for providing release logging!" );
		lox.Info( "Let's see if LogTools is available. We need to provide our lox as a parameter to all LogTools methods!" );
		LogTools.Instance( Log.Level.Info, this, 2, " Logging instance 'this':", 0, lox );
		lox.Info( "That's it for now. More release logging tests to come...stay tuned!" );
	}
} // class
} // namespace
