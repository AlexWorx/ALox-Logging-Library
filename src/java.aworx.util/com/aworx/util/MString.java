// #################################################################################################
//  AWorx Util - Classes we need
//  (c) 2013 A-Worx GmbH
//  
//  Class:	MString
//  
//  File:	MString.cs											Namespace:  com.aworx.util
// #################################################################################################

package com.aworx.util;

/**********************************************************************************************//**
 * A mutable string, that provides public access to its internal buffer and fields and does not
 * implement thread synchronization. Unfortunately, the given C#/JAVA StringBuilder/Buffer
 * classes are "sealed" and do not provide direct access to the internal buffer. Hence, to avoid
 * conversion to new immutable strings in certain situations, we rebuild a portion of the
 * StringBuilder functionality here. More complex functions, like C# Format() operations are not
 * supported and remain the domain of String and StringBuffer classes.
 **************************************************************************************************/
public class MString implements CharSequence
{
	// #################################################################################################
	// Java CharSequence implementation
	// #################################################################################################

	/**********************************************************************************************//**
	 * Returns a character of the sequence.
	 * @param index     The index of the character to return.
	 * @return          The character at the given index.
	 **************************************************************************************************/
	@Override public char 	charAt(int index)						{	return buffer[ index ];	}

	/**********************************************************************************************//**
	 * Gets the length of the sequence.
	 * @return  The length of the sequence.
	 **************************************************************************************************/
	@Override public int 	length()								{	return length;		}

	/**********************************************************************************************//**
	 * Throws an AWXU error (using the AWXU.errorHandler) and returns null. The reason for this 
	 * behavior is to disallow the usage of MString within (system) methods that create sub sequences.
	 * This would be in contrast to the design goal of MString.
	 *
	 * @param beginIndex    The start of the sequence (not used)
	 * @param endIndex      The length of the sequence (not used)
	 *
	 * @return  null (!).
	 **************************************************************************************************/
	@Override public CharSequence subSequence(int beginIndex, int endIndex)
	{
		// this function should never be used
		AWXU.errorHandler.error( "MString.subSequence() called. This is not supported" );
		return null;
	}

	// #################################################################################################
	// Public static fields
	// #################################################################################################

	/** The system depended new line character codes retrieved statically (once) using
		"System.getProperty("line.separator");" */
	public static		String				NEWLINE					= System.getProperty("line.separator");
	
	// #################################################################################################
	// Public fields
	// #################################################################################################

	/** The Buffer array. This may but should not be accessed directly. In case of external 
	 *   modifications the field hash has to be set to dirty (0). */
	public				char[]				buffer;

	/** The actual length of the string stored in the Buffer. In case of external 
		modifications the field hash has to be set to dirty (0). */
	public				int					length;

	/** The hashvalue. Has to be set dirty (0) whenever String is changed from outside!. */
	public				int					hash;


	// #################################################################################################
	//  Constructors
	// #################################################################################################

	/**********************************************************************************************//**
	 * Constructor without specific Buffer size, default buffer size to 1 kb.
	 **************************************************************************************************/
	public MString( )
	{
		// create Buffer
		buffer=	new char[1024];
		clear();
	}

	/**********************************************************************************************//**
	 * Constructor with specific Buffer size .
	 *
	 * @param size  The initial size of the internal buffer
	 **************************************************************************************************/
	public MString( int size  )
	{
		// check
		if ( size <= 0 )
			size= 1024;
		
		// create Buffer
		buffer=	new char[size];
		clear();
	}

	/**********************************************************************************************//**
	 * Constructor copying a MString.
	 *
	 * @param ms    The source MString to copy from.
	 *
	 **************************************************************************************************/
	public MString( MString ms ) 
	{
		// check null argument
		if ( ms == null )
		{
			// create Buffer
			buffer=	new char[1024];
			clear();
			return;
		}

		// check
		buffer=	new char[ ms.length ];
		clear();

		// copy the source
		append( ms );
	}

	/**********************************************************************************************//**
	 * Constructor copying a substring of a MString.
	 *
	 * @param ms        The source MString to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 **************************************************************************************************/
	public MString( MString ms, int startIdx) 
	{
		// check null argument
		if ( ms == null )
		{
			// create Buffer
			buffer=	new char[1024];
			clear();
			return;
		}

		// check
		int len= ms.length - startIdx;
		if (len <= 0)
		{
			len= 0;
			buffer=	new char[ 1024 ];
			clear();
			return;
		}

		
		buffer=	new char[ len ];
		clear();

		// copy the source
		append( ms, startIdx, len );
	}

	/**********************************************************************************************//**
	 * Constructor copying a substring of a MString.
	 *
	 * @param ms        The source MString to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 * @param len		The maximum length of the substring in s to append. Defaults to
	 *                  Integer.MAX_VALUE.
	 **************************************************************************************************/
	public MString( MString ms, int startIdx, int len) 
	{
		// check null argument
		if ( ms == null )
		{
			// create Buffer
			buffer=	new char[1024];
			clear();
			return;
		}

		// check
		if (len <= 0)
		{
			len= 0;
			buffer=	new char[ 1024 ];
		}
		else
		{
			if ( len == Integer.MAX_VALUE )
				len= ms.length - startIdx;

			buffer=	new char[ (len > 0)  ? len : 1024  ];
		}
		clear();

		// copy the source
		append( ms, startIdx, len );
	}

	/**********************************************************************************************//**
	 * Constructor copying String.
	 *
	 * @param s The source String to copy from.
	 **************************************************************************************************/
	public MString( String s) 
	{
		// check null argument
		if ( s == null )
		{
			// create Buffer
			buffer=	new char[1024];
			clear();
			return;
		}

		// check
		buffer=	new char[ s.length() ];
		clear();

		// copy the source
		append( s );
	}

	/**********************************************************************************************//**
	 * Constructor copying a substring of a String.
	 *
	 * @param s         The source String to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 **************************************************************************************************/
	public MString( String s, int startIdx) 
	{
		// check null argument
		if ( s == null )
		{
			// create Buffer
			buffer=	new char[1024];
			clear();
			return;
		}

		// check
		int len= s.length() - startIdx;
		if (len <= 0)
		{
			len= 0;
			buffer=	new char[ 1024 ];
			clear();
			return;
		}

		
		buffer=	new char[ len ];
		clear();

		// copy the source
		append( s, startIdx, len );
	}

	/**********************************************************************************************//**
	 * Constructor copying a substring of a String.
	 *
	 * @param s   		The source String to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 * @param len		The maximum length of the substring in s to append. Defaults to
	 *                  Integer.MAX_VALUE.
	 **************************************************************************************************/
	public MString( String s, int startIdx, int len) 
	{
		// check null argument
		if ( s == null )
		{
			// create Buffer
			buffer=	new char[1024];
			clear();
			return;
		}

		// check
		if (len <= 0)
		{
			len= 0;
			buffer=	new char[ 1024 ];
		}
		else
		{
			if ( len == Integer.MAX_VALUE )
				len= s.length() - startIdx;

			buffer=	new char[ (len > 0)  ? len : 1024  ];
		}
		clear();

		// copy the source
		append( s, startIdx, len );
	}

	/**********************************************************************************************//**
	 * Constructor copying a StringBuffer.
	 *
	 * @param s The source StringBuffer to copy from.
	 **************************************************************************************************/
	public MString( StringBuffer s ) 
	{
		// check null argument
		if ( s == null )
		{
			// create Buffer
			buffer=	new char[1024];
			clear();
			return;
		}

		// check
		buffer=	new char[ s.length() ];
		clear();

		// copy the source
		append( s, 0, s.length() );
	}

	/**********************************************************************************************//**
	 * Constructor copying a substring of a StringBuffer.
	 *
	 * @param s         The source StringBuffer to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 **************************************************************************************************/
	public MString( StringBuffer s, int startIdx) 
	{
		// check null argument
		if ( s == null )
		{
			// create Buffer
			buffer=	new char[1024];
			clear();
			return;
		}

		// check
		int len= s.length() - startIdx;
		if (len <= 0)
		{
			len= 0;
			buffer=	new char[ 1024 ];
			clear();
			return;
		}

		buffer=	new char[ len ];
		clear();

		// copy the source
		append( s, startIdx, len );
	}

	/**********************************************************************************************//**
	 * Constructor copying a substring of a StringBuffer.
	 *
	 * @param s         The source StringBuffer to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 * @param len    The maximum length of the substring in s to append. Defaults to
	 *                  Integer.MAX_VALUE.
	 **************************************************************************************************/
	public MString( StringBuffer s, int startIdx, int len) 
	{
		// check null argument
		if ( s == null )
		{
			// create Buffer
			buffer=	new char[1024];
			clear();
			return;
		}

		// check
		if (len <= 0)
		{
			len= 0;
			buffer=	new char[ 1024 ];
		}
		else
		{
			if ( len == Integer.MAX_VALUE )
				len= s.length() - startIdx;

			buffer=	new char[ (len > 0)  ? len : 1024  ];
		}
		clear();

		// copy the source
		append( s, startIdx, len );
	}

	// #################################################################################################
	// Public interface
	// #################################################################################################

	/**********************************************************************************************//**
	 * Clear the Buffer (just sets Length to 0)
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString clear()
	{
		// just set length to 0
		length=	0;

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append another MString.
	 *
	 * @param ms    The MString to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( MString ms )				
	{
		// check null argument
		if ( ms == null )
			return this;
		
		// get length once
		int len= ms.length;
		
		// check capacity
		ensureCapacity( length + len );

		// copy
		if ( len > 20 )
		{
			System.arraycopy( ms.buffer, 0, buffer, length, len );
			length+= len;
		}
		else
		{
			for ( int i= 0 ; i < len ; i++ )
				buffer[length++] = ms.buffer[i];
		}

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append a substring of another MString.
	 *
	 * @param ms        The MString to append.
	 * @param startIdx  The index in ms to start from.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( MString ms, int startIdx)
	{
		return append( ms, startIdx, Integer.MAX_VALUE);	
	}

	/**********************************************************************************************//**
	 * Append a substring of another MString.
	 *
	 * @param ms        The MString to append.
	 * @param startIdx  The index in ms to start from.
	 * @param len		The maximum length of the substring in ms to append. Defaults to
	 *                  Integer.MAX_VALUE.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( MString ms, int startIdx, int len )
	{
		// check null argument
		if ( ms == null )
			return this;
		
		// adjust range, if empty do nothing
		if ( adjustRangeAndTestIfEmpty( ms.length, startIdx, len ) )
			return this;

		startIdx= adjStartIdx;
		len=   adjLength;
		
		// check capacity
		ensureCapacity( length + len );

		// copy
		if ( len > 20 )
		{
			System.arraycopy( ms.buffer, startIdx, buffer, length, len );
			length+= len;
		}
		else
		{
			int endIdx= startIdx + len;
			for ( int i= startIdx ; i < endIdx ; i++ )
				buffer[length++] = ms.buffer[i];
		}

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append a String.
	 *
	 * @param s The String to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( String s )
	{
		// check null argument
		if ( s == null )
			return this;

		// get length once
		int leh= s.length();

		// check capacity
		ensureCapacity( length + leh );

		// copy and adjust my length
		s.getChars( 0, leh, buffer, length );

		length+= leh;

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append a substring of a String.
	 *
	 * @param s         The String to append.
	 * @param startIdx  The start index in s to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( String s, int startIdx)				
	{
		return append( s, startIdx, Integer.MAX_VALUE );	
	}

	/**********************************************************************************************//**
	 * Append a substring of a String.
	 *
	 * @param s         The String to append.
	 * @param startIdx  The index in s to start with.
	 * @param len	    The maximum length of the substring in s to append..
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( String s, int startIdx, int len )
	{
		// check null argument
		if ( s == null )
			return this;

		// adjust range, if empty do nothing
		if ( adjustRangeAndTestIfEmpty( s.length(), startIdx, len ) )
			return this;
		
		startIdx= adjStartIdx;
		len=   adjLength;
		
		// check capacity
		ensureCapacity( length + len );

		// copy and adjust my length
		s.getChars( startIdx, startIdx + len, buffer, length );
		length+= len;

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append a StringBuffer.
	 *
	 * @param sb    The StringBuffer to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( StringBuffer sb )
	{
		// check null argument
		if ( sb == null )
			return this;

		// get length once
		int len= sb.length();

		// check capacity
		ensureCapacity( length + len );

		// copy and adjust my length
		sb.getChars( 0, len, buffer, length );
		length+= len;

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append a substring of a StringBuffer.
	 *
	 * @param sb        The StringBuffer to append.
	 * @param startIdx  The index in sb to start from.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( StringBuffer sb, int startIdx )
	{
		return append( sb, startIdx, Integer.MAX_VALUE ); 
	}

	/**********************************************************************************************//**
	 * Append a substring of a StringBuffer.
	 *
	 * @param sb        The StringBuffer to append.
	 * @param startIdx  The start index in sb start from.
	 * @param len		The maximum length of the substring in sb to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( StringBuffer sb, int startIdx, int len )
	{
		// check null argument
		if ( sb == null )
			return this;

		// adjust range, if empty do nothing
		if ( adjustRangeAndTestIfEmpty( sb.length(), startIdx, len ) )
			return this;
		
		startIdx= adjStartIdx;
		len=   adjLength;

		// check capacity
		ensureCapacity( length + len );

		// copy and adjust my length
		sb.getChars( startIdx, startIdx + len, buffer, length );
		length+= len;

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append a StringBuilder.
	 *
	 * @param sb    The StringBuilder to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( StringBuilder sb )
	{
		// check null argument
		if ( sb == null )
			return this;

		// get length once
		int len= sb.length();

		// check capacity
		ensureCapacity( length + len );

		// copy and adjust my length
		sb.getChars( 0, len, buffer, length );
		length+= len;

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append a substring of a StringBuilder.
	 *
	 * @param sb        The StringBuilder to append.
	 * @param startIdx  The index in sb to start from.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( StringBuilder sb, int startIdx )
	{
		return append( sb, startIdx, Integer.MAX_VALUE ); 
	}

	/**********************************************************************************************//**
	 * Append a substring of a StringBuilder.
	 *
	 * @param sb        The StringBuilder to append.
	 * @param startIdx  The start index in sb start from.
	 * @param len		The maximum length of the substring in sb to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( StringBuilder sb, int startIdx, int len )
	{
		// check null argument
		if ( sb == null )
			return this;

		// adjust range, if empty do nothing
		if ( adjustRangeAndTestIfEmpty( sb.length(), startIdx, len ) )
			return this;
		
		startIdx= adjStartIdx;
		len=   adjLength;

		// check capacity
		ensureCapacity( length + len );

		// copy and adjust my length
		sb.getChars( startIdx, startIdx + len, buffer, length );
		length+= len;

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append a CharSequence.
	 *
	 * @param sb    The CharSequence to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( CharSequence sb )
	{
		// check null argument
		if ( sb == null )
			return this;

		// get length once
		int len= sb.length();

		// check capacity
		ensureCapacity( length + len );

		// copy and adjust my length
		int idx= length;
		length+= len;
		for (int i= 0; i < len ; i++ )
			buffer[idx++]= sb.charAt( i );

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append a substring of a CharSequence.
	 *
	 * @param sb        The CharSequence to append.
	 * @param startIdx  The index in sb to start from.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( CharSequence sb, int startIdx )
	{
		return append( sb, startIdx, Integer.MAX_VALUE ); 
	}

	/**********************************************************************************************//**
	 * Append a substring of a CharSequence.
	 *
	 * @param sb        The CharSequence to append.
	 * @param startIdx  The start index in sb start from.
	 * @param len    The maximum length of the substring in sb to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( CharSequence sb, int startIdx, int len )
	{
		// check null argument
		if ( sb == null )
			return this;

		// adjust range, if empty do nothing
		if ( adjustRangeAndTestIfEmpty( sb.length(), startIdx, len ) )
			return this;
		
		startIdx=	adjStartIdx;
		len=		adjLength;

		// check capacity
		ensureCapacity( length + len );

		// copy and adjust my length
		int idx= length;
		length+= len;
		int endIdx= startIdx + len;
		for (int i= startIdx; i < endIdx ; i++ )
			buffer[idx++]= sb.charAt( i );

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append the given character.
	 *
	 * @param c The character to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( char c )
	{
		ensureCapacity( length + 1 );
		buffer[ length++ ]= c;

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append the given character repeatedly.
	 *
	 * @param c     The character to append.
	 * @param qty   The quantity of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( char c, int qty )
	{
		ensureCapacity( length + qty );
		for ( int i= 0; i< qty; i++ )
			buffer[length++]= c;

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append padding spaces and append the given MString.
	 *
	 * @param ms        The MString to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadRight( MString ms, int fieldSize ) { return appendPadRight( ms, fieldSize, ' ' ); }

	/**********************************************************************************************//**
	 * Append padding characters and append the given MString.
	 *
	 * @param ms        The MString to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to add to the right of the given string src. Defaults to ' '
	 *                  (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadRight( MString ms, int fieldSize, char padChar )
	{
		// check for null parameter
		int sLen;
		if ( ms == null || (sLen= ms.length) == 0 )
			return append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.max ( sLen, fieldSize );
		ensureCapacity( length + maxChars );

		// copy string
		for (int i= 0 ; i < sLen ; i++ ) 
			buffer[ length++ ]= ms.buffer[i];

		// add pad characters
		int newLength= length + ( fieldSize - sLen );
		while ( length < newLength)
			buffer[length++]=	padChar;
		
		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append padding spaces and append the given String.
	 *
	 * @param s         The String to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadRight( String s, int fieldSize ) { return appendPadRight( s, fieldSize, ' ' ); }

	/**********************************************************************************************//**
	 * Append padding characters and append the given String.
	 *
	 * @param s         The String to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to add to the right of the given string src. Defaults to ' '
	 *                  (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadRight( String s, int fieldSize, char padChar )
	{
		// check for null parameter
		int sLen;
		if ( s == null || (sLen= s.length() ) == 0 )
			return append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.max ( sLen, fieldSize );
		ensureCapacity( length + maxChars );

		// copy string
		s.getChars( 0, sLen, buffer, length );
		length+= sLen;

		// add pad characters
		int newLength= length + ( fieldSize - sLen );
		while ( length < newLength)
			buffer[length++]=	padChar;
		
		// return me for concatenated operations	
		return this;

	}

	/**********************************************************************************************//**
	 * Append padding spaces and append the given StringBuffer.
	 *
	 * @param sb        The StringBuffer to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadRight( StringBuffer sb, int fieldSize ) { return appendPadRight( sb, fieldSize, ' ' ); }

	/**********************************************************************************************//**
	 * Append padding characters and append the given StringBuffer.
	 *
	 * @param sb        The StringBuffer to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to add to the right of the given string src. Defaults to ' '
	 *                  (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadRight( StringBuffer sb, int fieldSize, char padChar )
	{
		// check for null parameter
		int sLen;
		if ( sb == null || (sLen= sb.length() ) == 0 )
			return append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.max ( sLen, fieldSize );
		ensureCapacity( length + maxChars );

		// copy string
		sb.getChars( 0, sLen, buffer, length );
		length+= sLen;

		// add pad characters
		int newLength= length + ( fieldSize - sLen );
		while ( length < newLength)
			buffer[length++]=	padChar;
		
		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append the given MString and add padding spaces behind the string.
	 *
	 * @param ms        The string to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadLeft( MString ms, int fieldSize ) { return appendPadLeft( ms, fieldSize, ' ' ); }
	@SuppressWarnings ("null") 

	/**********************************************************************************************//**
	 * Append the given MString and add padding characters behind the string.
	 *
	 * @param ms        The string to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to add to the right of the given string src. Defaults to ' '
	 *                  (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadLeft( MString ms, int fieldSize, char padChar )
	{
		// ensure capacity
		int sLen=		ms!= null ? ms.length : 0;
		int maxChars=	Math.max( sLen, fieldSize );
		ensureCapacity( length + maxChars );

		// add pad characters
		int newLength= length + ( fieldSize - sLen );
		while ( length < newLength )
			buffer[length++] = padChar;

		// copy string
		if ( sLen > 0 )
		{
			for (int i= 0 ; i < sLen ; i++ ) 
				buffer[ length++ ]= ms.buffer[i];
		}

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append the given String and add padding spaces behind the string.
	 *
	 * @param s         The string to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadLeft( String s, int fieldSize ) 	{ return appendPadLeft( s, fieldSize, ' ' ); }

	/**********************************************************************************************//**
	 * Append the given String and add padding characters behind the string.
	 *
	 * @param s         The String to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to add to the right of the given string src. Defaults to ' '
	 *                  (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	@SuppressWarnings ("null") 
	public MString appendPadLeft( String s, int fieldSize, char padChar )
	{
		// ensure capacity
		int sLen=		s != null ? s.length() : 0;
		int maxChars=	Math.max( sLen, fieldSize );
		ensureCapacity( length + maxChars );

		// add pad characters
		int newLength= length + ( fieldSize - sLen );
		while ( length < newLength )
			buffer[length++] = padChar;

		// copy string
		if ( sLen > 0 )
		{
			s.getChars( 0, sLen, buffer, length );
			length+= sLen;
		}

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append the given StringBuffer and add padding spaces behind the string.
	 *
	 * @param sb        The StringBuffer to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadLeft( StringBuffer sb, int fieldSize ) 	{ return appendPadLeft( sb, fieldSize, ' ' ); }

	/**********************************************************************************************//**
	 * Append the given StringBuffer and add padding characters behind the string.
	 *
	 * @param sb        The StringBuffer to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to add to the right of the given string src. Defaults to ' '
	 *                  (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	@SuppressWarnings ("null") 
	public MString appendPadLeft( StringBuffer sb, int fieldSize, char padChar )
	{
		// ensure capacity
		int sLen=		sb != null ? sb.length() : 0;
		int maxChars=	Math.max( sLen, fieldSize );
		ensureCapacity( length + maxChars );

		// add pad characters
		int newLength= length + ( fieldSize - sLen );
		while ( length < newLength )
			buffer[length++] = padChar;

		// copy string
		if ( sLen > 0 )
		{
			sb.getChars( 0, sLen, buffer, length );
			length+= sLen;
		}

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append the given MString and add surrounding padding spaces.
	 *
	 * @param ms        The MString to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadCenter( MString ms, int fieldSize ) { return appendPadCenter( ms, fieldSize, ' '); }

	/**********************************************************************************************//**
	 * Append the given MString and add surrounding padding characters.
	 *
	 * @param ms        The MString to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to surround the Mutable string with. Defaults to ' ' (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadCenter( MString ms, int fieldSize, char padChar )
	{
		// check for null parameter
		int sLen;
		if ( ms == null || (sLen= ms.length) == 0 )
			return append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.max( sLen, fieldSize );
		ensureCapacity( length + maxChars );

		// add left characters
		int leftPad= ( fieldSize - sLen ) / 2;
		for ( int i= 0; i < leftPad ; i++ )
			buffer[length++]=	padChar;

		// append the rest using AppendPadRight()
		return appendPadRight( ms, fieldSize - leftPad, padChar );
	}

	/**********************************************************************************************//**
	 * Append the given String and add surrounding padding spaces.
	 *
	 * @param s         the string to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadCenter( String s, int fieldSize ) { return appendPadCenter( s, fieldSize, ' ' ); }

	/**********************************************************************************************//**
	 * Append the given String and add surrounding padding characters.
	 *
	 * @param s         the string to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to surround the Mutable string with. Defaults to ' ' (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadCenter( String s, int fieldSize, char padChar )
	{
		// check for null parameter
		int sLen;
		if ( s == null || (sLen= s.length() ) == 0 )
			return append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.max( sLen, fieldSize );
		ensureCapacity( length + maxChars );

		// add left characters
		int leftPad= ( fieldSize - sLen ) / 2;
		for ( int i= 0; i < leftPad ; i++ )
			buffer[length++]=	padChar;

		// append the rest using AppendPadRight()
		return appendPadRight( s, fieldSize - leftPad, padChar );
	}

	/**********************************************************************************************//**
	 * Append the given StringBuffer and add surrounding padding spaces.
	 *
	 * @param sb        the StringBuffer to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadCenter( StringBuffer sb, int fieldSize ) { return appendPadCenter( sb, fieldSize, ' ' ); }

	/**********************************************************************************************//**
	 * Append the given StringBuffer and add surrounding padding characters.
	 *
	 * @param sb        the StringBuffer to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to surround the Mutable string with. Defaults to ' ' (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString appendPadCenter( StringBuffer sb, int fieldSize, char padChar )
	{
		// check for null parameter
		int sLen;
		if ( sb == null || (sLen= sb.length() ) == 0 )
			return append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.max( sLen, fieldSize );
		ensureCapacity( length + maxChars );

		// add left characters
		int leftPad= ( fieldSize - sLen ) / 2;
		for ( int i= 0; i < leftPad ; i++ )
			buffer[length++]=	padChar;

		// append the rest using AppendPadRight()
		return appendPadRight( sb, fieldSize - leftPad, padChar );
	}

	/**********************************************************************************************//**
	 * Append the given unsigned 32-Bit integer value using a minimum number of digits.
	 *
	 * @param i         The integer value to append.
	 * @param minDigits The minimum number of digits to append. If the number has less digits than
	 *                  minDigits, then trailing '0's are added. Optional and defaults to 0.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( int i, int minDigits )
	{
		// Max Value: 4294967296
		// ensure capacity
		ensureCapacity( length + 11 ); // 10 plus minus sign
		
		// negative?
		if ( i < 0 )
		{
			buffer[length++] = '-';
			i= -i;
		}
			
		// at least one digit!
		if ( minDigits < 1 ) 
			minDigits= 1;

		// main loop
		int		actDigit=		11; // 10 + 1 for the loop
		int		actBase=		1000000000;
		boolean	isUnder=		false;
		while ( --actDigit > 0)
		{
			// get next d
			int d=			i / actBase;
			int actBase2=  	actBase;
			actBase/=	10;

			// did we hit i for the first time
			isUnder|= (d != 0);

			// don't print?
			if (!isUnder && actDigit > minDigits )
				continue;

			// print the digit 
			buffer[ length++ ]= (char) ( 48 + d ); // 48= '0'

			// next
			i=	i % actBase2;
		}
		
		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Append the given unsigned 32-Bit integer value.
	 *
	 * @param i     The integer value to append.
	 * @return      'this' to allow concatenated calls.
	 **************************************************************************************************/

	public MString append( int i ) { return append( i, 1 ); }

	/**********************************************************************************************//**
	 * Append the given double value using the minimum digits before and after the given number of
	 * digits after dot.
	 *
	 * @param d                     the integer value to append.
	 * @param minDigitsBeforeDot    The minimum number of digits write before the dot. If the number
	 *                              has less digits than minDigits, then trailing '0's  
	 *                              are added.
	 * @param digitsAfterDot        The exact number of digits written after the dot.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString append( double d, int minDigitsBeforeDot, int digitsAfterDot )
	{
		// negative? -> turn positive
		if ( d < 0d )
		{
			append( '-' );
			d= -d;
		}
		
		// append integer part plus dot
		int beforeDot= (int) d;
		
		// subtract integer part
		d-= beforeDot;
		
		// multiply by 10^digits, and get overflow value
		int i= digitsAfterDot;
		int overflow= 1;
		while ( i-- > 0)
		{
			d*= 		10;
			overflow*= 	10;
		}

		// round the multiplied rest and check for overflow. This check is necessary
		// for rests with 9er numbers:  sample 999.999  -> 1000.000, this is an "overflow" 		
		int afterDot= (int) Math.round( d );
		if ( afterDot == overflow )
		{
			afterDot= 0;
			beforeDot++;
		}
		
		// append integer part
		append( beforeDot, minDigitsBeforeDot ).append( '.' );
		
		// check for no digits after dot wanted
		if ( digitsAfterDot > 0 )
			append( afterDot, digitsAfterDot );
		
		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Go to the next tab stop by filling in pad characters repeatedly.
	 *
	 * @param tabSize   The tab positions are multiples of this parameter.
	 *
	 * @return  'this' to allow concatenated calls.
	 *
	 **************************************************************************************************/
	public MString tab( int tabSize ) 									{ return tab( tabSize, 0, 			 1,		 ' ' ); }

	/**********************************************************************************************//**
	 * Go to the next tab stop by filling in pad characters repeatedly.
	 *
	 * @param tabSize       The tab positions are multiples of this parameter.
	 * @param tabReference  The tab reference position. has to be smaller than Length. Defaults to 0
	 *                      (beginning of Buffer). For buffers with multiple lines, this parameter
	 *                      has to be set.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString tab( int tabSize, int tabReference)					{ return tab( tabSize, tabReference, 1, 	 ' ' ); }

	/**********************************************************************************************//**
	 * Go to the next tab stop by filling in pad characters repeatedly.
	 *
	 * @param tabSize       The tab positions are multiples of this parameter.
	 * @param tabReference  The tab reference position. has to be smaller than Length. Defaults to 0
	 *                      (beginning of Buffer). For buffers with multiple lines, this parameter
	 *                      has to be set.
	 * @param minPad        The minimum pad characters to add.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString tab( int tabSize, int tabReference, int minPad)		{ return tab( tabSize, tabReference, minPad, ' ' ); }

	/**********************************************************************************************//**
	 * Go to the next tab stop by filling in pad characters repeatedly.
	 *
	 * @param tabSize       The tab positions are multiples of this parameter.
	 * @param tabReference  The tab reference position. has to be smaller than Length. Defaults to 0
	 *                      (beginning of Buffer). For buffers with multiple lines, this parameter
	 *                      has to be set.
	 * @param minPad        The minimum pad characters to add.
	 * @param padChar       The character to add to the right of the given string src. Defaults to '
	 *                      ' (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString tab( int tabSize, int tabReference, int minPad, char padChar)
	{
		// append minimum padding
		append( padChar, minPad );

		// append characters to meet next tab
		append( padChar, (tabSize - ( (length - tabReference) % tabSize ) ) % tabSize );

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Appends platform specific new line character(s). ( "\\r\\n", "\\r", etc.) 
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString newLine()
	{
		// append new line characters. 
		return append( NEWLINE ); 
	}

	/**********************************************************************************************//**
	 * Checks if the given String is located at the given position.
	 *
	 * @param s             The string to search.
	 * @param pos           The to look at.
	 * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
	 *
	 * @return  True if the given sequence is found at the given position. False otherwise .
	 **************************************************************************************************/
	@SuppressWarnings ("null") 
	public boolean containsAt( CharSequence s, int pos, boolean ignoreCase )
	{
		// check null argument or length 0
		int sLen=  	s != null ?  s.length() : 0;
		int cmpEnd= pos + sLen;
		if ( sLen == 0 || pos > length || pos < 0 || cmpEnd > length )
			return false;


		// the compare loop 
		int sPos= 0;
		while ( pos < cmpEnd )
		{
			char c1=	s.charAt( sPos );
			char c2=	buffer[ pos ];
			if ( ignoreCase )
			{
				c1=	Character.toLowerCase( c1 );
				c2=	Character.toLowerCase( c2 );
			}
				
			if ( c1 != c2 )
				return false;
			
			pos++;
			sPos++;
		}
		
		return true;
	}

	/**********************************************************************************************//**
	 * Checks if the given String is located at the given position.
	 *
	 * @param s             The string to search.
	 * @param pos           The to look at.
	 *
	 * @return  True if the given sequence is found at the given position. False otherwise .
	 **************************************************************************************************/
	public boolean containsAt( CharSequence s, int pos )		{ return containsAt( s, pos, false ); }

	/**********************************************************************************************//**
	 * Checks if this MString starts with the given sequence.
	 *
	 * @param s The String to search. If s is null or empty, false is returned.
	 *
	 * @return  true if this starts with the given sequence, false if not.
	 **************************************************************************************************/
	public boolean startsWith( CharSequence s )
	{
		return containsAt( s, 0, false );
	}

	/**********************************************************************************************//**
	 * Checks if this MString ends with the given sequence.
	 *
	 * @param s The String to search. If s is null or empty, false is returned.
	 *
	 * @return  true if this starts with the given sequence, false if not.
	 **************************************************************************************************/
	public boolean endsWith  ( CharSequence s )
	{
		if ( s == null ) 
			return false;

		return containsAt( s, length - s.length(), false );
	}

	/**********************************************************************************************//**
	 * Search the given String in the Buffer starting at a given position.
	 *
	 * @param s         The string to search.
	 * @param startIdx  The index to start the search at. Optional and defaults to 0.
	 *
	 * @return  -1 if the String is not found. Otherwise the index of first occurrence.
	 **************************************************************************************************/
	public int indexOf( CharSequence s, int startIdx )
	{
		// check null argument or length 0
		int sLen=  s != null ?  s.length() : 0;
		if ( sLen == 0 || startIdx > length)
			return -1;

		// search
		@SuppressWarnings ("null") 			// why doesn't Eclipse analyzer get it? 
		char firstChar= s.charAt( 0 );		// get first char once, as [] operation is expensive
		while ( startIdx < length )
		{
			int		cmpLen= 0;
			char	sc=		firstChar;
			while ( buffer[ startIdx + cmpLen ] == sc )
			{
				cmpLen++;
				if ( cmpLen == sLen )
					return startIdx;
				sc= s.charAt( cmpLen );
			}
			startIdx++;
		}

		// not found
		return -1;
	}

	/**********************************************************************************************//**
	 * Search the given String in the Buffer.
	 *
	 * @param s         The string to search.
	 * @return  -1 if the String is not found. Otherwise the index of first occurrence.
	 **************************************************************************************************/
	public int indexOf( CharSequence s )				{ return indexOf( s, 0 ); }

	/**********************************************************************************************//**
	 * Replace one more more occurrences of a string by another string.
	 *
	 * @param searchStr         The string to be replaced.
	 * @param newStr            The replacement string.
	 * @param startIdx          The index where the search starts. Optional and defaults to 0.
	 * @param maxReplacements   The maximum number of replacements to perform. Optional and  
	 *                          defaults to Integer.MAX_VALUE .
	 *
	 * @return  The number of replacements that where performed.
	 **************************************************************************************************/
	public int replace( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements )
	{
		// check null arguments
		if ( MString.isNullOrEmpty(searchStr) || newStr == null )
			return 0;

		// get some values
		int oLen=				searchStr.length();
		int rLen=				newStr.length();
		int diff=				rLen - oLen;
		
		int cntReplacements=	0;

		// replacement loop
		while ( true )
		{
			// search  next occurrence
			int idx= indexOf( searchStr, startIdx );
			if (idx < 0 )
				return cntReplacements;

			// set dirty
			hash= 0;
			
			// copy rest up
			if ( diff > 0 )
			{
				if ( length + diff > buffer.length )
					ensureCapacity( length + diff );
				for ( int i= length - 1; i >= idx + oLen; i-- )
					buffer[ i + diff ]= buffer[ i ];
				length+= diff;
			}

			// copy rest down
			else if ( diff < 0 )
			{
				for ( int i= idx ; i < length + diff ; i++ )
					buffer[ i ]= buffer[ i - diff ];
				length+= diff;
			}

			// fill replacement in
			for ( int i= 0; i < rLen ; i++ )
				buffer[ idx + i ]= newStr.charAt( i );

			// set start index to first character behind current replacement
			startIdx= idx+ rLen;

			// increase qty of replacements and check with maximum
			cntReplacements++;
			if ( cntReplacements >= maxReplacements )
				return cntReplacements;
		}
	}

	/**********************************************************************************************//**
	 * Replace one more more occurrences of a string by another string.
	 *
	 * @param searchStr The string to be replaced.
	 * @param newStr    The replacement string.
	 * @param startIdx  The index where the search starts. Optional and defaults to 0.
	 *
	 * @return  The number of replacements that where performed.
	 **************************************************************************************************/
	public int replace( CharSequence searchStr, CharSequence newStr, int startIdx ) { return replace( searchStr, newStr, startIdx, Integer.MAX_VALUE); }

	/**********************************************************************************************//**
	 * Replace one more more occurrences of a string by another string.
	 *
	 * @param searchStr The string to be replaced.
	 * @param newStr    The replacement string.
	 *
	 * @return  The number of replacements that where performed.
	 **************************************************************************************************/
	public int replace( CharSequence searchStr, CharSequence newStr) 				{ return replace( searchStr, newStr, 0, 	   Integer.MAX_VALUE); }

	/**********************************************************************************************//**
	 * Compares a given string (or part of it) with the contents of this. If the optionally given
	 * substring start indices and lengths parameters are out of bounds, they are corrected. This
	 * could lead to unwanted results in some cases.
	 *
	 * @param cmp   An object of type String, StringBuffer or MString that is compared to this.
	 *
	 * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
	 *         follows the given string (same as String.CompareTo), or if given string in null.
	 **************************************************************************************************/
	public int compareTo(	CharSequence cmp )																
	{
		return compareTo( cmp, false, 	 0, 		Integer.MAX_VALUE, 	0, 			Integer.MAX_VALUE ); 
	}

	/**********************************************************************************************//**
	 * Compares a given string (or part of it) with the contents of this. If the optionally given
	 * substring start indices and lengths parameters are out of bounds, they are corrected. This
	 * could lead to unwanted results in some cases.
	 *
	 * @param cmp           An object of type String, StringBuffer or MString that is compared to
	 *                      this.
	 * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
	 *
	 * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
	 *         follows the given string (same as String.CompareTo), or if given string in null.
	 **************************************************************************************************/
	public int compareTo(	CharSequence cmp, boolean ignoreCase )											
	{
		return compareTo( cmp, ignoreCase, 0, 		Integer.MAX_VALUE, 	0, 			Integer.MAX_VALUE ); 
	}

	/**********************************************************************************************//**
	 * Compares a given string (or part of it) with the contents of this. If the optionally given
	 * substring start indices and lengths parameters are out of bounds, they are corrected. This
	 * could lead to unwanted results in some cases.
	 *
	 * @param cmp           An object of type String, StringBuffer or MString that is compared to
	 *                      this.
	 * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
	 * @param sStartIdx     The start of the substring within the given string that is to be compared
	 *                      to this. Defaults to 0.
	 *
	 * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
	 *         follows the given string (same as String.CompareTo), or if given string in null.
	 **************************************************************************************************/
	public int compareTo(	CharSequence cmp, boolean ignoreCase, int sStartIdx )								
	{
		return compareTo( cmp, ignoreCase, sStartIdx, Integer.MAX_VALUE, 	0,			Integer.MAX_VALUE ); 
	}

	/**********************************************************************************************//**
	 * Compares a given string (or part of it) with the contents of this. If the optionally given
	 * substring start indices and lengths parameters are out of bounds, they are corrected. This
	 * could lead to unwanted results in some cases.
	 *
	 * @param cmp           An object of type String, StringBuffer or MString that is compared to
	 *                      this.
	 * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
	 * @param sStartIdx     The start of the substring within the given string that is to be compared
	 *                      to this. Defaults to 0.
	 * @param sLen          The length of the substring within the given string that is to be
	 *                      compared to this. Defaults to Integer.MAX_VALUE.
	 *
	 * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
	 *         follows the given string (same as String.CompareTo), or if given string in null.
	 **************************************************************************************************/
	public int compareTo(	CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen )					
	{
		return compareTo( cmp, ignoreCase, sStartIdx, sLen, 				0,			Integer.MAX_VALUE ); 
	}

	/**********************************************************************************************//**
	 * Compares a given string (or part of it) with the contents of this. If the optionally given
	 * substring start indices and lengths parameters are out of bounds, they are corrected. This
	 * could lead to unwanted results in some cases.
	 *
	 * @param cmp           An object of type String, StringBuffer or MString that is compared to
	 *                      this.
	 * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
	 * @param sStartIdx     The start of the substring within the given string that is to be compared
	 *                      to this. Defaults to 0.
	 * @param sLen          The length of the substring within the given string that is to be
	 *                      compared to this. Defaults to Integer.MAX_VALUE.
	 * @param startIdx      The start of the substring within this that is to be compared. Defaults
	 *                      to 0.
	 *
	 * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
	 *         follows the given string (same as String.CompareTo), or if given string in null.
	 **************************************************************************************************/
	public int compareTo(	CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen, int startIdx )		
	{
		return compareTo( cmp, ignoreCase, sStartIdx, sLen, 				startIdx,	Integer.MAX_VALUE ); 
	}

	/**********************************************************************************************//**
	 * Compares a given string (or part of it) with the contents of this. If the optionally given
	 * substring start indices and lengths parameters are out of bounds, they are corrected. This
	 * could lead to unwanted results in some cases.
	 *
	 * @param cmp           An object of type String, StringBuffer or MString that is compared to
	 *                      this.
	 * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
	 * @param sStartIdx     The start of the substring within the given string that is to be compared
	 *                      to this. Defaults to 0.
	 * @param sLen          The length of the substring within the given string that is to be
	 *                      compared to this. Defaults to Integer.MAX_VALUE.
	 * @param startIdx      The start of the substring within this that is to be compared. Defaults
	 *                      to 0.
	 * @param len           The length of the substring within this that is to be compared.
	 *                       Defaults to Integer.MAX_VALUE.
	 *
	 * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
	 *         follows the given string (same as String.CompareTo), or if given string in null.
	 **************************************************************************************************/
	public int compareTo(	CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen, int startIdx, int len )
	{
		// check null argument
		if ( cmp == null )	
			return 1;

		// get length of cmp string
		int sLength= 	cmp.length();

		// adjust range of cmp string
		adjustRangeAndTestIfEmpty( sLength, sStartIdx, sLen );
		sStartIdx=	adjStartIdx;
		sLen=   	adjLength;

		adjustRangeAndTestIfEmpty(  length,  startIdx,  len );
		 startIdx= 	adjStartIdx;
		 len=  	adjLength;

		// compare loop
		int  idx=  startIdx;	int  end=  startIdx +  len;
		int sIdx= sStartIdx;	int sEnd= sStartIdx + sLen;
		while ( true )
		{
			// end of one of the strings or both?
			boolean exceededMe=		(idx  >= end);
			boolean exceededExt=	(sIdx >= sEnd);
			if (exceededMe)		return  exceededExt ? 0 :  -1;
			if (exceededExt)	return						1;

			// get act characters
			char c=  buffer[ idx  ];
			char sc=  cmp.charAt( sIdx );

			// to upper?
			// different characters
			if ( c != sc )
			{
				if ( !ignoreCase )
					return c-sc;
					
				// compare
				int diff= ( Character.toLowerCase( c ) - Character.toLowerCase( sc ) );
				if ( diff != 0 )
					return diff;
			}

			// same char, increase indices
			idx++; sIdx++;
		}
	}

	/**********************************************************************************************//**
	 * Converts all or a region of characters in the Buffer to upper or to lower case.
	 *
	 * @param toUpper   If true, conversion to upper case is performed, to lower else.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString convertCase( boolean toUpper )									{ return convertCase( toUpper, 0,			Integer.MAX_VALUE ); }

	/**********************************************************************************************//**
	 * Converts all or a region of characters in the Buffer to upper or to lower case.
	 *
	 * @param toUpper       If true, conversion to upper case is performed, to lower else.
	 * @param substrStart   Start of the substring to be converted. Defaults to 0.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString convertCase( boolean toUpper, int substrStart  )					{ return convertCase( toUpper, substrStart,	Integer.MAX_VALUE ); }

	/**********************************************************************************************//**
	 * Converts all or a region of characters in the Buffer to upper or to lower case.
	 *
	 * @param toUpper       If true, conversion to upper case is performed, to lower else.
	 * @param substrStart   Start of the substring to be converted. Defaults to 0.
	 * @param substrLength  Length of the substring to be converted. Defaults to Integer.MAX_VALUE.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public MString convertCase( boolean toUpper, int substrStart, int substrLength )
	{
		// mark has value as dirty
		hash= 0;
		
		// adjust range
		if ( substrLength == Integer.MAX_VALUE )			
		{
			if (substrStart < 0 )						
				substrStart=	0;
			substrLength=	length - substrStart;
		}
		else 
			if (substrStart < 0 )						
			{ 
				substrLength+= substrStart;  
				substrStart=	0; 
			}

		int substrEnd= substrStart + substrLength;
		if ( substrEnd > length )
			substrEnd= length;

		// convert
		for ( int i= substrStart; i < substrEnd ; i++ )
			buffer[ i ]=  toUpper	?	Character.toUpperCase( buffer[ i ] )
									:	Character.toLowerCase( buffer[ i ] );

		// return me for concatenated operations	
		return this;
	}

	/**********************************************************************************************//**
	 * Converts the MString into a String.
	 *
	 * @return  A string that represents this object.
	 **************************************************************************************************/
	@Override public String toString()
	{
		return new String( buffer, 0, length );
	}

	/**********************************************************************************************//**
	 * Creates a String from a region within this MString.
	 *
	 * @param startIdx  The start index of the region in this to create the string from.
	 *
	 * @return  A string that represents the specified sub region of this object.
	 **************************************************************************************************/
	public String toString( int startIdx )	{ return toString( startIdx, Integer.MAX_VALUE ); }

	/**********************************************************************************************//**
	 * Creates a String from a region within this MString.
	 *
	 * @param startIdx	The start index of the region in this to create the string from.
	 * @param len		The maximum length of the region to create the string from. Defaults to
	 *                  Integer.MAX_VALUE.
	 *
	 * @return  A string that represents the specified sub region of this object.
	 **************************************************************************************************/
	public String toString( int startIdx, int len )
	{
		// adjust range, if empty return empty string
		if ( adjustRangeAndTestIfEmpty( length, startIdx, len ) )
			return empty;

		// create string
		return new String( buffer, adjStartIdx, adjLength);
	}

	/**********************************************************************************************//**
	 * Calculates the hash value using the same formula as java.lang.String.
	 *
	 * @return  A hash value for this object.
	 **************************************************************************************************/
	@Override  public int hashCode() 
	{
		int h;
		if ((h= hash) == 0 && length > 0) 
		{
			char buf[]=	buffer;
			int  len=	length;
 
			for (int i = 0; i < len; i++) 
				h = 31*h + buf[i++];

			hash = h;
		}
		return h;
	}

	/**********************************************************************************************//**
	 * Compares this to the given object. Given object can be MString or CharSequence (e.g. String).
	 *
	 * @param o The object to compare to this instance.
	 *
	 * @return  True if given object equals this.
	 **************************************************************************************************/
	@Override public boolean equals( Object o )
	{
		// null? -> false
		if ( o == null )
			return false;
			
		// MString?
		if ( o instanceof MString)
		{	
			// cast up
			MString ms= ( MString ) o;
			
			// different length?
			if ( ms.length != length )
				return false;
				
			// character compare
			for (int i= length - 1 ; i >= 0 ; i-- )
				if ( ms.buffer[i] != buffer[i] )
					return false;
			
			// equal		
			return true;
		}
		
		// CharSequence?
		if ( o instanceof CharSequence )
		{	
			// cast up
			CharSequence cs= ( CharSequence ) o;
			
			// different length?
			if ( cs.length() != length )
				return false;
				
			// character compare
			for (int i= length - 1 ; i >= 0 ; i-- )
				if ( cs.charAt( i ) != buffer[i] )
					return false;
			
			// equal		
			return true;
		}
		
		// not a known comparable object
		return false; 
	}

	/**********************************************************************************************//**
	 * Ensures that the capacity of the internal buffer meets or exceeds the given value.
	 *
	 * @param minLen    The minimum length.
	 **************************************************************************************************/
	public void ensureCapacity( int minLen )
	{
		// As a side effect, flag has value as dirty
		hash= 0;
		
		// big enough?
		if ( buffer.length >= minLen )
			return;

		// get new size, increase at least by 50%
		int newLength= Math.max( minLen, buffer.length + (buffer.length / 2));

		// create new Buffer
		char[] newBuffer=	new char[ newLength ];

		// copy data
		System.arraycopy(buffer, 0, newBuffer, 0, length );

		// set new Buffer 
		buffer=	newBuffer;
	}

	// ################################################################################################
	// internals
	// ################################################################################################

   	/** Used as a return value of method adjustRangeAndTestIfEmpty() as Java does not allow to pass
        parameters by reference */
	protected int adjStartIdx;

   	/** Used as a return value of method adjustRangeAndTestIfEmpty() as Java does not allow to pass
        parameters by reference */
	protected int adjLength;

	/**********************************************************************************************//**
	 * Adjust a given range within an array to the array bounds and tests if range is empty.
	 *
	 * @param referenceLen  Length of the zero indexed reference array.
	 * @param startIdx      The start index of the range. Negative values are adjusted to 0 and
	 *                      length shortened accordingly. Values higher than referenceLen are not
	 *                      adjusted, but function returns true in this case.
	 * @param len        The length of the range to be adjusted to the array bounds. A length of
	 *                      Integer.MAX_VALUE is considered 'infinite' and cut to maximum length
	 *                      beginning from adjusted startIdx.
	 *
	 * @return  True if adjusted range is out of bounds or empty.
	 **************************************************************************************************/
	protected boolean adjustRangeAndTestIfEmpty(int referenceLen, int startIdx, int len )
	{
		// infinite lenght given?
		if ( len == Integer.MAX_VALUE )			
		{
			// cut any negative start without subtracting it from length
			if ( startIdx < 0 )						
				 startIdx=   0;

			// set length to maximum 
			len=	referenceLen - startIdx;
		}

		// not infinite
		else 
		{
			// if negative start, cut it from the length
			if (startIdx < 0 )						
			{ 
				len+=		startIdx;  
				startIdx=	0; 
			}

			// adjust length
			int maxLen=  referenceLen - startIdx;
			if ( len > maxLen )
				 len=  maxLen;
		}

		// save return values
		adjStartIdx= startIdx;
		adjLength=	 len;
		
		// return is empty?
		return  ( startIdx >= referenceLen || len <= 0 );
	}


	// #################################################################################################
	//  Static String Utilities
	// #################################################################################################
	
	/**   An empty String singleton */
	public static final String empty=					"";

	/**********************************************************************************************//**
	 * Checks if a given CharSequence is empty or has a length of zero.
	 *
	 * @param jString   The java String to check.
	 *
	 * @return  Returns true if given String is empty or 0.
	 **************************************************************************************************/
	public static boolean isNullOrEmpty( CharSequence jString )	{ return jString == null || jString.length() == 0; }

	/**********************************************************************************************//**
	 * Search the given String in the Buffer starting at the given position.
	 *
	 * @param sIn       The string to search in.
	 * @param sFor      The string to search for.
	 * @param startIdx  The index to start the search at. Optional and defaults to 0.
	 *
	 * @return  -1 if the String is not found. Otherwise the index of first occurrence.
	 **************************************************************************************************/
	public static int indexOfIgnoreCase( CharSequence sIn, CharSequence sFor, int startIdx )
	{
		// check s1
		if ( sIn == null )
			return -1;
		int sInLen= sIn.length();
		
		// check s2 null argument or length 0
		int sForLen=  sFor != null ?  sFor.length() : 0;
		if ( sForLen == 0 || startIdx > sInLen)
			return -1;

		// check start idx < 0
		if ( startIdx < 0 )
			startIdx= 0;

		// search
		@SuppressWarnings ("null") 			// why doesn't Eclipse analyzer get it? 
		char firstChar= Character.toLowerCase( sFor.charAt( 0 ) );		// get first char once, as [] operation is expensive
		while ( startIdx < sInLen )
		{
			int		cmpLen= 0;
			char	cFor=	firstChar;
			while ( Character.toLowerCase( sIn.charAt( startIdx + cmpLen )) == cFor )
			{
				cmpLen++;
				if ( cmpLen == sForLen )
					return startIdx;
				cFor= Character.toLowerCase( sFor.charAt( cmpLen ) );
			}
			startIdx++;
		}

		// not found
		return -1;
	}

	/**********************************************************************************************//**
	 * Search the given String in the Buffer.
	 *
	 * @param sIn   The string to search in.
	 * @param sFor  The string to search for.
	 *
	 * @return  -1 if the String is not found. Otherwise the index of first occurrence.
	 **************************************************************************************************/
	public static int indexOfIgnoreCase( CharSequence sIn, CharSequence sFor )		{ return indexOfIgnoreCase( sIn, sFor, 0); }

	/**********************************************************************************************//**
	 * Static utility function that to check if a string starts with another string with case
	 * insensitive compare. Using this function avoids to create two converted (lowered)
	 * temporary strings.
	 *
	 * @param s         The string to search in.
	 * @param prefix    The string to search for.
	 *
	 * @return  true, if given string s starts with given string prefix, false otherwise.
	 **************************************************************************************************/
	@SuppressWarnings ("null") 
	public static boolean startsWithIgnoreCase( CharSequence s, CharSequence prefix )
	{
		// check s
		if ( s == null )
			return false;
		int sLen= s.length();
		
		// check s2 null argument or length 0
		int prefixLen=  prefix != null ?  prefix.length() : 0;
		if ( prefixLen == 0 )
			return true;
			
		// s smaller than prefix
		if ( sLen < prefixLen )
			return false; 

		// comparison loop
		for (int i= 0; i< prefixLen; i++ )
			if ( Character.toLowerCase( s.charAt( i ) ) != Character.toLowerCase( prefix.charAt( i ) )) 
				return false;
		
		// no differences found
		return true;
	}

	/**********************************************************************************************//**
	 * Static utility function that to check if a string ends with another string with case
	 * insensitive compare. Using this function avoids to create two converted (lowered) temporary
	 * strings.
	 *
	 * @param s         The string to search in.
	 * @param postfix   The string to search for.
	 *
	 * @return  true, if given string s ends with given string prefix, false otherwise.
	 **************************************************************************************************/
	@SuppressWarnings ("null") 
	public static boolean endsWithIgnoreCase( CharSequence s, CharSequence postfix )
	{
		// check s
		if ( s == null )
			return false;
		int sLen= s.length();
		
		// check s2 null argument or length 0
		int postfixLen=  postfix != null ?  postfix.length() : 0;
		if ( postfixLen == 0 )
			return true;
			
		// s smaller than prefix
		if ( sLen < postfixLen )
			return false; 

		// comparison loop
		int sIdx= sLen - postfixLen;		
		for (int postfixIdx= 0; postfixIdx< postfixLen; postfixIdx++ )
			if ( Character.toLowerCase( s.charAt( sIdx++ ) ) != Character.toLowerCase( postfix.charAt( postfixIdx ) )) 
				return false;
		
		// no differences found
		return true;
	}
} // class Mutable String


