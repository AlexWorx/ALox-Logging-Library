// #################################################################################################
//  com.aworx.alox_java_android_test_release_log  - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
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
import com.aworx.util.AString;

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
        // create a lox for release logging
        Lox lox= new Lox();

        // add and configure a memory logger
        MemoryLogger ml=           new MemoryLogger();
        ml.lineFormatter.format=   new AString( "[%TE]%L[%O]: ");
        lox.addLogger( ml,   Log.DomainLevel.ALL );

        // add and configure a log cat logger
        AndroidLogCatLogger lcl= new AndroidLogCatLogger();
        lox.addLogger( lcl,  Log.DomainLevel.ALL );

        // We do not work with default domains, as we will obfuscate the code.
        // Obfuscated code and release logging does not allow default domains, because
        // the rely on caller information and reasonable package, class and method names
        lox.regDomain( "RelLog",    Log.Scope.NONE );
        lox.setDomain( "RelLog",    Log.DomainLevel.ALL  );

        // all log invocations provide the "domain" parameter explicitly to be safe when
        // obfuscation is enabled!
        lox.info( "RelLog", "Hello ALox, thank you for providing release logging!" );
        lox.info( "RelLog", "Let's see if LogTools is available." );
        lox.info( "RelLog", "We need to provide our lox as a parameter to all LogTools methods!" );

        // instance() will not give very nice member names, if obfuscated!
        LogTools.instance( "RelLog", Log.Level.INFO, Log.LOX, 2, " Logging the Lox:", 0, lox );

        // also, the exception stack trace should be not too easy to read. Proguard provides a tool "retrace"...
        lox.info( "RelLog", "Logging exceptions: " );
        LogTools.exception( "RelLog", Log.Level.ERROR, new Exception("This is not a real Exception", new Exception("...unreal inner")), " Logging instance 'this':", 0, lox );

        lox.info( "RelLog", "That's it for now. More release logging tests to come...stay tuned!" );

        // copy the memory logger's output to the TextBlock
        TextView logOutput= (TextView) findViewById( R.id.logOutput );
        logOutput.setMovementMethod(new ScrollingMovementMethod());

        // copy the memory logger's output to the view
        if ( ml.buffer.length() > 0 )
            logOutput.setText( ml.buffer.toString() );
        else
            logOutput.setText( "No output" + AString.NEWLINE + "obiously ALox was" + AString.NEWLINE + "fully pruned!" );


    }

    @Override public boolean onCreateOptionsMenu(Menu menu)
    {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate( R.menu.alox_java_android_test_release_log, menu );
        return true;
    }

}
