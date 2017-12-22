// #################################################################################################
//  com.aworx.alox_java_android_test_release_log  - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.alox_java_android_test_release_log;

import android.os.Bundle;
import android.app.Activity;
import android.text.method.ScrollingMovementMethod;
import android.view.Menu;
import android.widget.TextView;

import com.aworx.lox.*;
import com.aworx.lox.tools.LogTools;
import com.aworx.lox.android.AndroidLogCatLogger;
import com.aworx.lox.loggers.MemoryLogger;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;

public class ALoxJavaAndroidTestReleaseLog extends Activity
{

    @Override protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate( savedInstanceState );
        setContentView( R.layout.activity_alox_java_android_test_release_log );

        testReleaseLogging();
    }

    public void testReleaseLogging()
    {
        // Initialize ALox
        ALox.init();

        // create a lox for release logging
        Lox lox= new Lox("Release");

        // add and configure a memory logger
        MemoryLogger ml=           new MemoryLogger();
        ml.metaInfo.format=   new AString( "[%TC]%V[%D]: ");
        //lox.setVerbosity( ml, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );
        lox.setVerbosity( ml, Verbosity.VERBOSE  );

        // add and configure a log cat logger
        AndroidLogCatLogger lcl= new AndroidLogCatLogger();
        lox.setVerbosity( lcl, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );
        lox.setVerbosity( lcl, Verbosity.VERBOSE  );

        // We do not work with scope domains, as we will obfuscate the code.
        // Obfuscated code and release logging does not allow scope domains, because
        // the rely on scope information and reasonable package, class and method names
        lox.setDomain( "RelLog",    Scope.GLOBAL );

        lox.info( "Hello ALox, thank you for providing release logging!" );
        lox.info( "Let's see if LogTools are available." );
        lox.info( "We need to provide our lox as a parameter to all LogTools methods!" );

        // instance() will not give very nice member names, if obfuscated!
        LogTools.instance( "/RelLog", Verbosity.INFO, lox, 2, " Logging the Lox:", lox );

        // also, the exception stack trace should be not too easy to read. Proguard provides a tool "retrace"...
        lox.info( "RelLog", "Logging exceptions: " );
        LogTools.exception( "/RelLog", Verbosity.ERROR,
                            new Exception("This is not a real Exception", new Exception("...unreal inner")),
                            " Logging instance 'this':", lox );

        lox.info( "That's it for now. Have fun with ALox for Android!" );

        // copy the memory loggers' output to the TextBlock
        TextView logOutput= (TextView) findViewById( R.id.logOutput );
        logOutput.setMovementMethod(new ScrollingMovementMethod());

        // copy the memory loggers' output to the view
        if ( ml.memoryLog.length() > 0 )
            logOutput.setText( ml.memoryLog.toString() );
        else
            logOutput.setText( "No output" + CString.NEW_LINE_CHARS + "obiously ALox was" + CString.NEW_LINE_CHARS + "fully pruned!" );


    }

    @Override public boolean onCreateOptionsMenu(Menu menu)
    {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate( R.menu.alox_java_android_test_release_log, menu );
        return true;
    }

}
