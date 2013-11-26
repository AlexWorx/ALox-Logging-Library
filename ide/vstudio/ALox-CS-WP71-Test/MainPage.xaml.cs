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

using com.aworx.lox;
using Microsoft.Phone.Testing;

namespace ALox_CS_WP71_Test
{
	public partial class MainPage : PhoneApplicationPage
	{
		// Constructor
		public MainPage()
		{
			InitializeComponent();
			LogTests();
		}

		public void LogTests()
		{
			//Log.AddLogger( new ConsoleLogger( "Console" ) );
			//Log.RegDomain( "WP71", true );
			//Log.Info( "Hallo WP71!" );

			this.Content = UnitTestSystem.CreateTestPage();  
		}
	}
}