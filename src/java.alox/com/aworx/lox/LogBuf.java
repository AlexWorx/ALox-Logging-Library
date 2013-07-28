package com.aworx.lox;


import com.aworx.util.MString;


/**********************************************************************************************//**
 *  This class encapsulates a MString and mimics the interface into it. The reason to have this, 
 *  is to allow a java byte code tool to prune all code related to this class. Hence, for debug 
 *  logging an instance of this class can be filled and logged and the appropriate byte code tool 
 *  can be configured to prune this code away. 
 *
 *  Class Log provides a static instance of LogBuf, accessible in a thread safe way, through
 *  method Log.buf(). 
 **************************************************************************************************/
public class LogBuf 
{
	/**********************************************************************************************//**
	 * The encapsulated MString
	 **************************************************************************************************/
	public MString b;

	/**********************************************************************************************//**
	 * Constructor without specific Buffer size, default buffer size to 1 kb.
	 **************************************************************************************************/
	public LogBuf() 									{ b= new MString(128); }

	/**********************************************************************************************//**
	 * Constructor with specific Buffer size .
	 *
	 * @param size  The initial size of the internal buffer
	 **************************************************************************************************/
	public LogBuf( int size ) 							{ b= new MString(size); }
	
	/**********************************************************************************************//**
	 * Constructor copying a MString.
	 *
	 * @param ms    The source MString to copy from.
	 **************************************************************************************************/
	public LogBuf( MString ms ) 						{ b= new MString( ms ); }

	/**********************************************************************************************//**
	 * Constructor copying a substring of a MString.
	 *
	 * @param ms        The source MString to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 **************************************************************************************************/
	public LogBuf( MString ms, int startIdx) 			{ b= new MString( ms, startIdx ); }

	/**********************************************************************************************//**
	 * Constructor copying a substring of a MString.
	 *
	 * @param ms        The source MString to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 * @param len		The maximum length of the substring in s to append. Defaults to
	 *                  Integer.MAX_VALUE.
	 **************************************************************************************************/
	public LogBuf( MString ms, int startIdx, int len)	{ b= new MString( ms, startIdx, len ); } 

	/**********************************************************************************************//**
	 * Constructor copying String.
	 *
	 * @param s The source String to copy from.
	 **************************************************************************************************/
	public LogBuf( String s)							{ b= new MString( s ); } 

	/**********************************************************************************************//**
	 * Constructor copying a substring of a String.
	 *
	 * @param s         The source String to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 **************************************************************************************************/
	public LogBuf( String s, int startIdx)				{ b= new MString( s, startIdx ); } 

	/**********************************************************************************************//**
	 * Constructor copying a substring of a String.
	 *
	 * @param s   		The source String to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 * @param len		The maximum length of the substring in s to append. Defaults to
	 *                  Integer.MAX_VALUE.
	 **************************************************************************************************/
	public LogBuf( String s, int startIdx, int len) 	{ b= new MString( s, startIdx, len ); }
	/**********************************************************************************************//**
	 * Constructor copying a StringBuffer.
	 *
	 * @param s The source StringBuffer to copy from.
	 **************************************************************************************************/
	public LogBuf( StringBuffer s ) 					{ b= new MString( s ); } 

	/**********************************************************************************************//**
	 * Constructor copying a substring of a StringBuffer.
	 *
	 * @param s         The source StringBuffer to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 **************************************************************************************************/
	public LogBuf( StringBuffer s, int startIdx) 		{ b= new MString( s, startIdx ); } 

	/**********************************************************************************************//**
	 * Constructor copying a substring of a StringBuffer.
	 *
	 * @param s         The source StringBuffer to copy from.
	 * @param startIdx  The start index in s to append. Defaults to 0.
	 * @param len    The maximum length of the substring in s to append. Defaults to
	 *                  Integer.MAX_VALUE.
	 **************************************************************************************************/
	public LogBuf( StringBuffer s, int startIdx, int len) { b= new MString( s, startIdx, len ); }

	// #################################################################################################
	// Public interface
	// #################################################################################################

	/**********************************************************************************************//**
	 * Clear the Buffer (just sets Length to 0)
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf clear()	 									{ b.clear();					return this; }

	/**********************************************************************************************//**
	 * Append another MString.
	 *
	 * @param ms    The MString to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( MString ms )							{ b.append( ms );				return this; }			

	/**********************************************************************************************//**
	 * Append a substring of another MString.
	 *
	 * @param ms        The MString to append.
	 * @param startIdx  The index in ms to start from.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( MString ms, int startIdx)				{ b.append( ms, startIdx );		return this; }
	
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
	public LogBuf append( MString ms, int startIdx, int len )	{ b.append( ms, startIdx, len );		return this; }

	/**********************************************************************************************//**
	 * Append a String.
	 *
	 * @param s The String to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( String s )					 		{ b.append( s);						return this; }

	/**********************************************************************************************//**
	 * Append a substring of a String.
	 *
	 * @param s         The String to append.
	 * @param startIdx  The start index in s to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( String s, int startIdx)				{ b.append( s, startIdx );		return this; }

	/**********************************************************************************************//**
	 * Append a substring of a String.
	 *
	 * @param s         The String to append.
	 * @param startIdx  The index in s to start with.
	 * @param len	    The maximum length of the substring in s to append..
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( String s, int startIdx, int len ) 	{ b.append( s, startIdx, len );		return this; }

	/**********************************************************************************************//**
	 * Append a StringBuffer.
	 *
	 * @param sb    The StringBuffer to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( StringBuffer sb)					 	{ b.append( sb);					return this; }

	/**********************************************************************************************//**
	 * Append a substring of a StringBuffer.
	 *
	 * @param sb        The StringBuffer to append.
	 * @param startIdx  The index in sb to start from.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( StringBuffer sb, int startIdx ) 		{ b.append( sb, startIdx );		return this; }

	/**********************************************************************************************//**
	 * Append a substring of a StringBuffer.
	 *
	 * @param sb        The StringBuffer to append.
	 * @param startIdx  The start index in sb start from.
	 * @param len		The maximum length of the substring in sb to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( StringBuffer sb, int startIdx, int len ) 	{ b.append( sb, startIdx, len );		return this; }

	/**********************************************************************************************//**
	 * Append a StringBuilder.
	 *
	 * @param sb    The StringBuilder to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( StringBuilder sb)					 	{ b.append( sb);					return this; }

	/**********************************************************************************************//**
	 * Append a substring of a StringBuilder.
	 *
	 * @param sb        The StringBuilder to append.
	 * @param startIdx  The index in sb to start from.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( StringBuilder sb, int startIdx ) 		{ b.append( sb, startIdx );		return this; }

	/**********************************************************************************************//**
	 * Append a substring of a StringBuilder.
	 *
	 * @param sb        The StringBuilder to append.
	 * @param startIdx  The start index in sb start from.
	 * @param len		The maximum length of the substring in sb to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( StringBuilder sb, int startIdx, int len )	{ b.append( sb, startIdx, len );		return this; }

	/**********************************************************************************************//**
	 * Append a CharSequence.
	 *
	 * @param sb    The CharSequence to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( CharSequence sb)					 	{ b.append( sb);							return this; }

	/**********************************************************************************************//**
	 * Append a substring of a CharSequence.
	 *
	 * @param sb        The CharSequence to append.
	 * @param startIdx  The index in sb to start from.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( CharSequence sb, int startIdx ) 		{ b.append( sb, startIdx );					return this; }
		
	/**********************************************************************************************//**
	 * Append a substring of a CharSequence.
	 *
	 * @param sb        The CharSequence to append.
	 * @param startIdx  The start index in sb start from.
	 * @param len    The maximum length of the substring in sb to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( CharSequence sb, int startIdx, int len )	{ b.append( sb, startIdx, len );		return this; }

	/**********************************************************************************************//**
	 * Append the given character.
	 *
	 * @param c The character to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( char c )						 			{ b.append( c );						return this; }

	/**********************************************************************************************//**
	 * Append the given character repeatedly.
	 *
	 * @param c     The character to append.
	 * @param qty   The quantity of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( char c, int qty )							{ b.append( c, qty );						return this; }

	/**********************************************************************************************//**
	 * Append padding spaces and append the given MString.
	 *
	 * @param ms        The MString to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadRight( MString ms, int fieldSize ) 		{ b.appendPadRight( ms, fieldSize, ' ' ); return this; }

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
	public LogBuf appendPadRight( MString ms, int fieldSize, char padChar ) { b.appendPadRight( ms, fieldSize, padChar); return this; }

	/**********************************************************************************************//**
	 * Append padding spaces and append the given String.
	 *
	 * @param s         The String to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadRight( String s, int fieldSize ) 				{ b.appendPadRight( s, fieldSize, ' ' );	return this; }

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
	public LogBuf appendPadRight( String s, int fieldSize, char padChar ) 	{ b.appendPadRight( s, fieldSize, padChar );	return this; }

	/**********************************************************************************************//**
	 * Append padding spaces and append the given StringBuffer.
	 *
	 * @param sb        The StringBuffer to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadRight( StringBuffer sb, int fieldSize )			{ return appendPadRight( sb, fieldSize, ' ' ); }

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
	public LogBuf appendPadRight( StringBuffer sb, int fieldSize, char padChar ){ b.appendPadRight( sb, fieldSize, padChar );	return this; }

	/**********************************************************************************************//**
	 * Append the given MString and add padding spaces behind the string.
	 *
	 * @param ms        The string to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadLeft( MString ms, int fieldSize )				{ b.appendPadLeft( ms, fieldSize, ' ' ); return this;}

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
	@SuppressWarnings ("null")
	public LogBuf appendPadLeft( MString ms, int fieldSize, char padChar )	{ b.appendPadLeft( ms, fieldSize, padChar );	return this; }

	/**********************************************************************************************//**
	 * Append the given String and add padding spaces behind the string.
	 *
	 * @param s         The string to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadLeft( String s, int fieldSize ) 					{ b.appendPadLeft( s, fieldSize, ' ' );	return this; }

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
	public LogBuf appendPadLeft( String s, int fieldSize, char padChar ) 	{ b.appendPadLeft( s, fieldSize, padChar );	return this; }

	/**********************************************************************************************//**
	 * Append the given StringBuffer and add padding spaces behind the string.
	 *
	 * @param sb        The StringBuffer to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadLeft( StringBuffer sb, int fieldSize ) 			{ b.appendPadLeft( sb, fieldSize, ' ' );	return this; }

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
	public LogBuf appendPadLeft( StringBuffer sb, int fieldSize, char padChar ) { b.appendPadLeft( sb, fieldSize, padChar );	return this; }

	/**********************************************************************************************//**
	 * Append the given MString and add surrounding padding spaces.
	 *
	 * @param ms        The MString to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadCenter( MString ms, int fieldSize )				{ b.appendPadCenter( ms, fieldSize, ' '); 		return this; }

	/**********************************************************************************************//**
	 * Append the given MString and add surrounding padding characters.
	 *
	 * @param ms        The MString to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to surround the Mutable string with. Defaults to ' ' (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadCenter( MString ms, int fieldSize, char padChar ){ b.appendPadCenter( ms, fieldSize, padChar); 	return this; }

	/**********************************************************************************************//**
	 * Append the given String and add surrounding padding spaces.
	 *
	 * @param s         the string to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadCenter( String s, int fieldSize ) 				{ b.appendPadCenter( s, fieldSize, ' '); 	return this; }

	/**********************************************************************************************//**
	 * Append the given String and add surrounding padding characters.
	 *
	 * @param s         the string to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to surround the Mutable string with. Defaults to ' ' (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadCenter( String s, int fieldSize, char padChar )	{ b.appendPadCenter( s, fieldSize, padChar); 	return this; }

	/**********************************************************************************************//**
	 * Append the given StringBuffer and add surrounding padding spaces.
	 *
	 * @param sb        the StringBuffer to append.
	 * @param fieldSize The minimum number of characters to append.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadCenter( StringBuffer sb, int fieldSize ) 		{ b.appendPadCenter( sb, fieldSize, ' '); 	return this; }

	/**********************************************************************************************//**
	 * Append the given StringBuffer and add surrounding padding characters.
	 *
	 * @param sb        the StringBuffer to append.
	 * @param fieldSize The minimum number of characters to append.
	 * @param padChar   The character to surround the Mutable string with. Defaults to ' ' (space).
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf appendPadCenter( StringBuffer sb, int fieldSize, char padChar ) { b.appendPadCenter( sb, fieldSize, padChar); 	return this; }

	/**********************************************************************************************//**
	 * Append the given unsigned 32-Bit integer value using a minimum number of digits.
	 *
	 * @param i         The integer value to append.
	 * @param minDigits The minimum number of digits to append. If the number has less digits than
	 *                  minDigits, then trailing '0's are added. Optional and defaults to 0.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf append( int i, int minDigits )							{ b.append( i, minDigits ); 	return this; }

	/**********************************************************************************************//**
	 * Append the given unsigned 32-Bit integer value.
	 *
	 * @param i     The integer value to append.
	 * @return      'this' to allow concatenated calls.
	 **************************************************************************************************/

	public LogBuf append( int i ) 											{ b.append( i, 1 ); return this;}

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
	public LogBuf append( double d, int minDigitsBeforeDot, int digitsAfterDot ) { b.append( d, minDigitsBeforeDot, digitsAfterDot ); return this;}

	/**********************************************************************************************//**
	 * Go to the next tab stop by filling in pad characters repeatedly.
	 *
	 * @param tabSize   The tab positions are multiples of this parameter.
	 *
	 * @return  'this' to allow concatenated calls.
	 *
	 **************************************************************************************************/
	public LogBuf tab( int tabSize ) 									{  b.tab( tabSize, 0, 			 1,		 ' ' ); return this; }

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
	public LogBuf tab( int tabSize, int tabReference)					{ b.tab( tabSize, tabReference, 1, 	 ' ' ); return this; }

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
	public LogBuf tab( int tabSize, int tabReference, int minPad)		{ b.tab( tabSize, tabReference, minPad, ' ' ); return this; }

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
	public LogBuf tab( int tabSize, int tabReference, int minPad, char padChar)	{ b.tab( tabSize, tabReference, minPad, padChar ); return this; }

	/**********************************************************************************************//**
	 * Appends platform specific new line character(s). ( "\\r\\n", "\\r", etc.) 
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf newLine()												{ b.append( MString.NEWLINE ); 		return this; }

	/**********************************************************************************************//**
	 * Checks if the given String is located at the given position.
	 *
	 * @param s             The string to search.
	 * @param pos           The to look at.
	 * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
	 *
	 * @return  True if the given sequence is found at the given position. False otherwise .
	 **************************************************************************************************/
	public boolean containsAt( CharSequence s, int pos, boolean ignoreCase ){ return b.containsAt( s, pos, ignoreCase); }

	/**********************************************************************************************//**
	 * Checks if the given String is located at the given position.
	 *
	 * @param s             The string to search.
	 * @param pos           The to look at.
	 *
	 * @return  True if the given sequence is found at the given position. False otherwise .
	 **************************************************************************************************/
	public boolean containsAt( CharSequence s, int pos )				{ return b.containsAt( s, pos, false ); }

	/**********************************************************************************************//**
	 * Checks if this MString starts with the given sequence.
	 *
	 * @param s The String to search. If s is null or empty, false is returned.
	 *
	 * @return  true if this starts with the given sequence, false if not.
	 **************************************************************************************************/
	public boolean startsWith( CharSequence s )							{ return b.containsAt( s, 0, false );	}

	/**********************************************************************************************//**
	 * Checks if this MString ends with the given sequence.
	 *
	 * @param s The String to search. If s is null or empty, false is returned.
	 *
	 * @return  true if this starts with the given sequence, false if not.
	 **************************************************************************************************/
	public boolean endsWith  ( CharSequence s )							{ return b.endsWith( s ); }

	/**********************************************************************************************//**
	 * Search the given String in the Buffer starting at a given position.
	 *
	 * @param s         The string to search.
	 * @param startIdx  The index to start the search at. Optional and defaults to 0.
	 *
	 * @return  -1 if the String is not found. Otherwise the index of first occurrence.
	 **************************************************************************************************/
	public int indexOf( CharSequence s, int startIdx )					{ return b.indexOf( s, startIdx ); }

	/**********************************************************************************************//**
	 * Search the given String in the Buffer.
	 *
	 * @param s         The string to search.
	 * @return  -1 if the String is not found. Otherwise the index of first occurrence.
	 **************************************************************************************************/
	public int indexOf( CharSequence s )								{ return b.indexOf( s, 0 ); }

	/**********************************************************************************************//**
	 * 	Replace one more more occurrences of a string by another string. Returns the number
	 * 	of replacements. Use #replace() to allow concatenated operations.
	 *
	 * @param searchStr         The string to be replaced.
	 * @param newStr            The replacement string.
	 * @param startIdx          The index where the search starts. Optional and defaults to 0.
	 * @param maxReplacements   The maximum number of replacements to perform. Optional and  
	 *                          defaults to Integer.MAX_VALUE .
	 *
	 * @return  The number of replacements that where performed.
	 **************************************************************************************************/
	public int replaceCount( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements ) { return b.replaceCount( searchStr, newStr, startIdx, maxReplacements); }

	/**********************************************************************************************//**
	 * 	Replace one more more occurrences of a string by another string. Returns the number
	 * 	of replacements. Use #replace() to allow concatenated operations.
	 *
	 * @param searchStr The string to be replaced.
	 * @param newStr    The replacement string.
	 * @param startIdx  The index where the search starts. Optional and defaults to 0.
	 *
	 * @return  The number of replacements that where performed.
	 **************************************************************************************************/
	public int replaceCount( CharSequence searchStr, CharSequence newStr, int startIdx ) { return b.replaceCount( searchStr, newStr, startIdx, Integer.MAX_VALUE); }

	/**********************************************************************************************//**
	 * 	Replace one more more occurrences of a string by another string. Returns the number
	 * 	of replacements. Use #replace() to allow concatenated operations.
	 *
	 * @param searchStr The string to be replaced.
	 * @param newStr    The replacement string.
	 *
	 * @return  The number of replacements that where performed.
	 **************************************************************************************************/
	public int replaceCount( CharSequence searchStr, CharSequence newStr) 				{ return b.replaceCount( searchStr, newStr, 0, 	   Integer.MAX_VALUE); }

	/**********************************************************************************************//**
	 * 	Replace one more more occurrences of a string by another string. To receive the number of 
	 * 	replacements, see alternative method #ReplaceCount().
	 *
	 * @param searchStr         The string to be replaced.
	 * @param newStr            The replacement string.
	 * @param startIdx          The index where the search starts. Optional and defaults to 0.
	 * @param maxReplacements   The maximum number of replacements to perform. Optional and  
	 *                          defaults to Integer.MAX_VALUE .
	 *
	 * @return  The number of replacements that where performed.
	 **************************************************************************************************/
	public LogBuf replace( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements ) { b.replaceCount( searchStr, newStr, startIdx, maxReplacements); return this; }

	/**********************************************************************************************//**
	 * 	Replace one more more occurrences of a string by another string. To receive the number of 
	 * 	replacements, see alternative method #ReplaceCount().
	 *
	 * @param searchStr The string to be replaced.
	 * @param newStr    The replacement string.
	 * @param startIdx  The index where the search starts. Optional and defaults to 0.
	 *
	 * @return  The number of replacements that where performed.
	 **************************************************************************************************/
	public LogBuf replace( CharSequence searchStr, CharSequence newStr, int startIdx )	{ b.replaceCount( searchStr, newStr, startIdx, Integer.MAX_VALUE); return this; }

	/**********************************************************************************************//**
	 * 	Replace one more more occurrences of a string by another string. To receive the number of 
	 * 	replacements, see alternative method #ReplaceCount().
	 *
	 * @param searchStr The string to be replaced.
	 * @param newStr    The replacement string.
	 *
	 * @return  The number of replacements that where performed.
	 **************************************************************************************************/
	public LogBuf replace( CharSequence searchStr, CharSequence newStr) 				{ b.replaceCount( searchStr, newStr, 0, Integer.MAX_VALUE); return this; }

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
	public int compareTo(	CharSequence cmp )										{ return b.compareTo( cmp ); }						

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
	public int compareTo(	CharSequence cmp, boolean ignoreCase )					{ return b.compareTo( cmp, ignoreCase, 0, Integer.MAX_VALUE, 0, Integer.MAX_VALUE ); }

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
	public int compareTo(	CharSequence cmp, boolean ignoreCase, int sStartIdx )	{ return b.compareTo( cmp, ignoreCase, sStartIdx, Integer.MAX_VALUE, 0, Integer.MAX_VALUE ); 
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
	public int compareTo(	CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen )	{ return b.compareTo( cmp, ignoreCase, sStartIdx, sLen, 0, Integer.MAX_VALUE );	}

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
	public int compareTo(	CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen, int startIdx )	{	return b.compareTo( cmp, ignoreCase, sStartIdx, sLen, startIdx, Integer.MAX_VALUE ); }

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
	public int compareTo(	CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen, int startIdx, int len ){	return b.compareTo( cmp, ignoreCase, sStartIdx, sLen, startIdx,	len ); }

	/**********************************************************************************************//**
	 * Converts all or a region of characters in the Buffer to upper or to lower case.
	 *
	 * @param toUpper   If true, conversion to upper case is performed, to lower else.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf convertCase( boolean toUpper )									{ b.convertCase( toUpper, 0,			Integer.MAX_VALUE ); return this;}

	/**********************************************************************************************//**
	 * Converts all or a region of characters in the Buffer to upper or to lower case.
	 *
	 * @param toUpper       If true, conversion to upper case is performed, to lower else.
	 * @param substrStart   Start of the substring to be converted. Defaults to 0.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf convertCase( boolean toUpper, int substrStart  )					{ b.convertCase( toUpper, substrStart,	Integer.MAX_VALUE ); return this;}

	/**********************************************************************************************//**
	 * Converts all or a region of characters in the Buffer to upper or to lower case.
	 *
	 * @param toUpper       If true, conversion to upper case is performed, to lower else.
	 * @param substrStart   Start of the substring to be converted. Defaults to 0.
	 * @param substrLength  Length of the substring to be converted. Defaults to Integer.MAX_VALUE.
	 *
	 * @return  'this' to allow concatenated calls.
	 **************************************************************************************************/
	public LogBuf convertCase( boolean toUpper, int substrStart, int substrLength ){ b.convertCase( toUpper, substrStart,	substrLength); return this;}

	/**********************************************************************************************//**
	 * Converts the MString into a String.
	 *
	 * @return  A string that represents this object.
	 **************************************************************************************************/
	@Override public String toString()
	{
		return b.toString();
	}

}
 
