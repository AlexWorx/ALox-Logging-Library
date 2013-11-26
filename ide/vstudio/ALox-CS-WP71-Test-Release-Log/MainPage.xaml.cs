using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using Microsoft.Phone.Controls;
using com.aworx.util;
using com.aworx.lox;
using com.aworx.lox.loggers;
using com.aworx.lox.tools;


namespace ALox_CS_WP71_Test
{
	public partial class MainPage : PhoneApplicationPage
	{
		// Constructor
		public MainPage()
		{
			InitializeComponent();
			TestReleaseLogging();
		}

		public void TestReleaseLogging()
		{
			Lox lox= new Lox();
			MemoryLogger ml= new MemoryLogger();
			#if ALOX_REL_LOG
				ml.LineFormatter.Format	= new MString( "[%TE]%L[%O]: ");
			#endif
			lox.AddLogger( ml, Log.DomainLevel.All );

			lox.RegDomain( "RelLog", Log.Scope.SourceFile );
			lox.SetDomain( "RelLog", Log.DomainLevel.All  );

			lox.Info( "Hello ALox, thank you for providing release logging!" );
			lox.Info( "Let's see if LogTools is available." );
			lox.Info( "We need to provide our lox as a parameter to all LogTools methods!" );
			LogTools.Instance( Log.Level.Info, lox, 2, " Logging the Lox:", 0, lox );
			lox.Info( "Logging an Exception" );
			LogTools.Exception( new Exception("This is not a real Exception", new Exception("...unreal inner")), " Logging instance 'this':", 0, lox );
			lox.Info( "That's it for now..." );

			// copy the memory logger's output to the TextBlock
			if ( ml.Buffer.Length > 0 )
				ALoxOutput.Text= ml.Buffer.ToString();
			else
				ALoxOutput.Text= "Obviously, release logging got pruned :-(" + Environment.NewLine + "Set conditional compile symbol ALOX_REL_LOG!";
		}
	}
}