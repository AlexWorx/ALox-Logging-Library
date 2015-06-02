using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;

using com.aworx.util;
using com.aworx.lox;
using com.aworx.lox.tools;
using com.aworx.lox.loggers;


namespace ALox_CS_WP80_Test
{
    public partial class MainPage : PhoneApplicationPage
    {
        // Constructor
        public MainPage()
        {
            InitializeComponent();
            TestALox();
        }

        public void TestALox()
        {
            // do a bit of debug logging
            #if ALOX_DEBUG
                MemoryLogger dbgML= new MemoryLogger();
                dbgML.LineFormatter.Format    = new AString( "[%TE]%L[%O]: ");
                Log.AddLogger( dbgML );
            #endif

            Log.SetDomain( "DbgLog", Log.DomainLevel.All  );
            Log.Info     ( "DbgLog", "Obviously you are running this app...");
            Log.Info     ( "DbgLog", "...in debug mode!");

            // do a bit of release logging
            Lox lox= new Lox();
            MemoryLogger ml= new MemoryLogger();
            ml.LineFormatter.Format    = new AString( "[%TE]%L[%O]: ");
            lox.AddLogger( ml, Log.DomainLevel.All );
            lox.RegDomain( "RelLog", Log.Scope.SourceFile );
            lox.SetDomain( "RelLog", Log.DomainLevel.All  );


            lox.Info( "Hello ALox, thank you for providing release logging!" );
            lox.Info( "Let's see if LogTools is available." );
            lox.Info( "For release logging, we need to provide our lox as a parameter to all LogTools methods!" );
            LogTools.Instance( Log.Level.Info, lox, 2, " Logging the Lox:", 0, lox );
            lox.Info( "Logging an Exception" );
            LogTools.Exception( new Exception("This is not a real Exception", new Exception("...unreal inner")), " Logging instance 'this':", 0, lox );
            lox.Info( "That's it for now..." );

            // copy the memory loggers' output to the TextBlock
            ALoxOutput.Text= "";
            #if ALOX_DEBUG
                ALoxOutput.Text+= dbgML.Buffer.NewLine().ToString();
            #endif
            if ( ml.Buffer.Length() > 0 )
                ALoxOutput.Text+= ml.Buffer.ToString();
            else
                ALoxOutput.Text+= "Obviously, release logging got pruned :-(" + Environment.NewLine + "Set conditional compile symbol ALOX_REL_LOG!";
        }
    }
}
