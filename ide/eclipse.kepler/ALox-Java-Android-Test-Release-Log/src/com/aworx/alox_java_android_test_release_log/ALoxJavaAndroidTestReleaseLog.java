package com.aworx.alox_java_android_test_release_log;

import android.os.Bundle;
import android.app.Activity;
import android.text.method.ScrollingMovementMethod;
import android.view.Menu;
import android.widget.TextView;

import com.aworx.lox.*;
import com.aworx.lox.loggers.MemoryLogger;
import com.aworx.util.MString;

public class ALoxJavaAndroidTestReleaseLog extends Activity
{

	@Override protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate( savedInstanceState );
		setContentView( R.layout.activity_alox_java_android_test_release_log );
		
		TestReleaseLogging();
	}

	public void TestReleaseLogging()
	{
		Lox lox= new Lox();
		MemoryLogger ml= new MemoryLogger();
		ml.lineFormatter.format	= new MString( "[%TE]%L[%O]: ");
		lox.addLogger( ml, Log.DomainLevel.ALL );

		lox.regDomain( "RelLog", Log.Scope.PACKAGE );
		lox.setDomain( "RelLog", Log.DomainLevel.ALL  );

		lox.info( "Hello ALox, thank you for providing release logging!" );
		lox.info( "Let's see if LogTools is available." );
		lox.info( "We need to provide our lox as a parameter to all LogTools methods!" );
		LogTools.instance( Log.Level.INFO, Log.LOX, 2, " Logging the Lox in Log:", 0, lox );
		lox.info( "But exceptions are: " );
		LogTools.exception( new Exception("This is not a real Exception", new Exception("...unreal inner")), " Logging instance 'this':", 0, lox );
		lox.info( "That's it for now. More release logging tests to come...stay tuned!" );

		// copy the memory logger's output to the TextBlock
		TextView logOutput= (TextView) findViewById( R.id.logOutput );
		logOutput.setMovementMethod(new ScrollingMovementMethod());
		logOutput.setText( ml.buffer.toString() );
	}

	@Override public boolean onCreateOptionsMenu(Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate( R.menu.alox_java_android_test_release_log, menu );
		return true;
	}

}
