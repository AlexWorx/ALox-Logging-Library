// #################################################################################################
//  AWorx Util - Classes we need
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:	MString
//  File:	MString.cs											Namespace:  com.aworx.util
// #################################################################################################

using System;
using System.Text;

namespace com.aworx.util  {

/** ***********************************************************************************************
 * <summary>
 *  A mutable string, that provides public access to its internal buffer and fields and does not
 *  implement thread synchronization.
 *  Unfortunately, the given C#/JAVA StringBuilder/Buffer classes are "sealed" and do not provide direct
 *  access to the internal buffer. Hence, to avoid conversion to new immutable strings in certain
 *  situations, we rebuild a portion of the StringBuilder functionality here. More complex functions,
 *  like C# Format() operations are not supported and remain the domain of String and StringBuffer classes.
 * </summary>
 **************************************************************************************************/
public class MString
{
	// #################################################################################################
	// Public fields
	// #################################################################################################

	/// <summary>The Buffer array. This may but should not be accessed directly. In case of external 
	/// modifications the field hash has to be set to dirty (0).</summary>
	public				char[]				Buffer;

	/// <summary>The actual length of the string stored in the Buffer. In case of external 
	/// modifications the field hash has to be set to dirty (0).</summary>
	public				int					Length;

	/// <summary>The hashvalue. Has to be set dirty (0) whenever String is changed from outside!.</summary>
	public				int					Hash;


	// #################################################################################################
	//  Constructors
	// #################################################################################################

	/** ************************************************************************************************
	 * <summary>	Constructor with specific Buffer size . </summary>
	 *
	 * <param name="size">	(Optional) The size. Defaults to 1024 </param>
	 **************************************************************************************************/
	public MString( int size= 1024  )
	{
		// check
		if ( size <= 0 )
			size= 1024;
		
		// create Buffer
		Buffer=	new char[size];
		Clear();
	}

	/** ************************************************************************************************
	 * <summary> Constructor using a substring of another MString. </summary>
	 *
	 * <param name="ms">	  	The source MString to copy from. </param>
	 * <param name="startIdx">	The start index in ms to append. Defaults to 0. </param>
	 * <param name="length">  	The maximum length of the substring in ms to append.
	 * 							Defaults to int.MaxInt. </param>
	 **************************************************************************************************/
	public MString( MString ms, int startIdx= 0, int length= int.MaxValue )
	{
		// check null argument
		if ( ms == null )
		{
			// create Buffer
			Buffer=	new char[1024];
			Clear();
			return;
		}

		// check
		if (length <= 0)
		{
			length= 0;
			Buffer=	new char[ 1024 ];
		}
		else
		{
			if ( length == int.MaxValue )
				length= ms.Length - startIdx;

			Buffer=	new char[ length > 0 ?  length : 1024 ];
		}
		Clear();

		// copy the source
		Append( ms, startIdx, length );
	}

	/** ************************************************************************************************
	 * <summary> Constructor using with a substring of a String. </summary>
	 *
	 * <param name="s">			The source String to copy from. </param>
	 * <param name="startIdx">	The start index in s to append. Defaults to 0. </param>
	 * <param name="length">  	The maximum length of the substring in s to append.
	 * 							Defaults to int.MaxInt. </param>
	 **************************************************************************************************/
	public MString( String s, int startIdx= 0, int length= int.MaxValue) 
	{
		// check null argument
		if ( s == null )
		{
			// create Buffer
			Buffer=	new char[1024];
			Clear();
			return;
		}

		// check
		if (length <= 0)
		{
			length= 0;
			Buffer=	new char[ 1024 ];
		}
		else
		{
			if ( length == int.MaxValue )
				length= s.Length - startIdx;

			Buffer=	new char[ (length > 0)  ? length : 1024  ];
		}
		Clear();

		// copy the source
		Append( s, startIdx, length );
	}

	/** ************************************************************************************************
	 * <summary> Constructor using a substring of a StringBuilder. </summary>
	 *
	 * <param name="sb">	  	The source Mutable StringBuilder to copy. </param>
	 * <param name="startIdx">	The start index in ms to append. Defaults to 0. </param>
	 * <param name="length">  	The maximum length of the substring in ms to append.
	 * 							Defaults to int.MaxInt. </param>
	 **************************************************************************************************/
	public MString( StringBuilder sb, int startIdx= 0, int length= int.MaxValue )
	{
		// check null argument
		if ( sb == null )
		{
			// create Buffer
			Buffer=	new char[1024];
			Clear();
			return;
		}

		// check
		if (length <= 0)
		{
			length= 0;
			Buffer=	new char[ 1024 ];
		}
		else
		{
			if ( length == int.MaxValue )
				length= sb.Length - startIdx;

			Buffer=	new char[ (length > 0)  ? length : 1024  ];
		}
		Clear();

		// copy the source
		Append( sb, startIdx, length );
	}

	// #################################################################################################
	// Public interface
	// #################################################################################################

	/** ************************************************************************************************
	 * <summary>	Clear the Buffer (just sets Length to 0) </summary>
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Clear()
	{
		// just set length to 0
		Length=	0;

		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append another  MString. </summary>
	 *
	 * <param name="ms">		The MString to append. </param>
	 *
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( MString ms )
	{
		// check null argument
		if ( ms == null )
			return this;

		// get length once
		int msLen= ms.Length;

		// check capacity
		EnsureCapacity( Length + msLen );

		// copy
		if ( msLen > 20 )
			Array.Copy( ms.Buffer, 0, Buffer, Length, msLen );
		else
		{
			char[]	bt= Buffer;
			char[]	bs= ms.Buffer;
			int		ti= Length;	
			for ( int i= 0 ; i < msLen ; i++ )
				bt[ti++] = bs[i];
		}
		Length+= msLen;

		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append a substring of the given MString. </summary>
	 *
	 * <param name="ms">		The MString to append. </param>
	 * <param name="startIdx">	The start index in ms to append. Defaults to 0.</param>
	 * <param name="msLen">	The maximum length of the substring in ms to append. Defaults to 
	 * 							int.MaxInt</param>
	 *
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( MString ms, int startIdx, int msLen= int.MaxValue )
	{
		// check null argument
		if ( ms == null )
			return this;

		// adjust range, if empty do nothing
		if ( adjustRangeAndTestIfEmpty( ms.Length, ref startIdx, ref msLen ) )
			return this;

		// check capacity
		EnsureCapacity( Length + msLen );

		// copy
		if ( msLen > 20 )
			Array.Copy( ms.Buffer, startIdx, Buffer, Length, msLen );
		else
		{
			char[]	bt= Buffer;
			char[]	bs= ms.Buffer;
			int		ti= Length;	
			int		endIdx= startIdx + msLen;
			for ( int i= startIdx ; i < endIdx ; i++ )
				bt[ti++] = bs[i];
		}
		Length+= msLen;

		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append a String. </summary>
	 *
	 * <param name="s">	The String to append. </param>
	 *
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( String s )
	{
		// check null argument
		if ( s == null )
			return this;

		// get length once
		int length= s.Length;

		// check capacity
		EnsureCapacity( Length + length );

		// copy and adjust my length
		s.CopyTo( 0, Buffer, Length, length );
		Length+= length;

		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append a substring of a String. </summary>
	 *
	 * <param name="s">		 	The String to append. </param>
	 * <param name="startIdx">	The start index in s to append. Defaults to 0.</param>
	 * <param name="length">	The maximum length of the substring in s to append. Defaults to 
	 * 							int.MaxInt</param>
	 *
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( String s, int startIdx, int length= int.MaxValue )
	{
		// check null argument
		if ( s == null )
			return this;

		// adjust range, if empty do nothing
		if ( adjustRangeAndTestIfEmpty( s.Length, ref startIdx, ref length ) )
			return this;

		// check capacity
		EnsureCapacity( Length + length );

		// copy and adjust my length
		s.CopyTo( startIdx, Buffer, Length, length );
		Length+= length;

		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append a StringBuilder. </summary>
	 *
	 * <param name="sb">	 	The StringBuilder to append. </param>
	 *
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( StringBuilder sb )
	{
		// check null argument
		if ( sb == null )
			return this;

		// get length once
		int length= sb.Length;

		// check capacity
		EnsureCapacity( Length + length );

		// copy and adjust my length
		#if !ALOX_WP71
			// standard versions
			sb.CopyTo( 0, Buffer, Length, length );
			Length+= length;
		#else
			// Windows Phone 7.1 version (StringBuilder.CopyTo() not available)
			for (int i= 0; i < length; i++ )
				Buffer[ Length++ ]= sb[ i ];
		#endif

		// return me for concatenated operations	
		return this;
	}

	/** ***********************************************************************************************
	 * <summary>	Append a substring of the given StringBuilder. </summary>
	 * <param name="sb">	  	The StringBuilder to append. </param>
	 * <param name="startIdx">	The start index in sb to append. </param>
	 * <param name="length">  	(Optional) The maximum length of the substring in sb to append.
	 * 							Defaults to int.MaxInt. </param>
	 * <returns>	'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( StringBuilder sb, int startIdx, int length= int.MaxValue )
	{
		// check null argument
		if ( sb == null )
			return this;

		// adjust range, if empty do nothing
		if ( adjustRangeAndTestIfEmpty( sb.Length, ref startIdx, ref length ) )
			return this;

		// check capacity
		EnsureCapacity( Length + length );

		// copy and adjust my length
		#if !ALOX_WP71
			// standard versions
			sb.CopyTo( startIdx, Buffer, Length, length );
			Length+= length;
		#else
			// Windows Phone 7.1 version (StringBuilder.CopyTo() not available)
			for (int i= 0; i < length; i++ )
				Buffer[ Length++ ]= sb[ startIdx + i ];
		#endif

		// return me for concatenated operations	
		return this;
	}


	/** ************************************************************************************************
	 * <summary>	Append the given character. </summary>
	 * <param name="c">	The character to append. </param>
	 *
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( char c )
	{
		EnsureCapacity( Length + 1 );
		Buffer[ Length++ ]= c;

		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append the given character repeatedly. </summary>
	 *
	 * <param name="c">  	The character to append. </param>
	 * <param name="qty">	The quantity of characters to append. </param>
	 *
	 * <returns>	'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( char c, int qty )
	{
		EnsureCapacity( Length + qty );
		for ( int i= 0; i< qty; i++ )
			Buffer[Length++]= c;

		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append padding characters and append the given MString. </summary>
	 *
	 * <param name="ms">		The MString to append. </param>
	 * <param name="fieldSize">	The minimum number of characters to append. </param>
	 * <param name="padChar">  	The character to add to the right of the given string src. 
	 * 							Defaults to ' ' (space). </param>
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString AppendPadRight( MString ms, int fieldSize, char padChar= ' ' )
	{
		// check for null parameter
		int sLen;
		if ( ms == null || (sLen= ms.Length) == 0 )
			return Append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.Max ( sLen, fieldSize );
		EnsureCapacity( Length + maxChars );

		// copy string
		for (int i= 0 ; i < sLen ; i++ ) 
			Buffer[ Length++ ]= ms.Buffer[i];

		// add pad characters
		int newLength= Length + ( fieldSize - sLen );
		while ( Length < newLength)
			Buffer[Length++]=	padChar;
		
		// return me for concatenated operations	
		return this;
	}

	/** ***********************************************************************************************
	 * <summary>	Append padding characters and append the given String. </summary>
	 * <param name="s">		   	The String to append. </param>
	 * <param name="fieldSize">	The minimum number of characters to append. </param>
	 * <param name="padChar">  	(Optional) The character to add to the right of the given string src.
	 * 							Defaults to ' ' (space). </param>
	 * <returns>	'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString AppendPadRight( String s, int fieldSize, char padChar= ' ' )
	{
		// check for null parameter
		int sLen;
		if ( s == null || (sLen= s.Length) == 0 )
			return Append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.Max ( sLen, fieldSize );
		EnsureCapacity( Length + maxChars );

		// copy string
		s.CopyTo( 0, Buffer, Length, sLen );
		Length+= sLen;

		// add pad characters
		int newLength= Length + ( fieldSize - sLen );
		while ( Length < newLength)
			Buffer[Length++]=	padChar;
		
		// return me for concatenated operations	
		return this;
	}

	/** ***********************************************************************************************
	 * <summary>	Append padding characters and append the given StringBuilder. </summary>
	 * <param name="sb">		   	The StringBuilder to append. </param>
	 * <param name="fieldSize">	The minimum number of characters to append. </param>
	 * <param name="padChar">  	(Optional) The character to add to the right of the given string src.
	 * 							Defaults to ' ' (space). </param>
	 * <returns>	'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString AppendPadRight( StringBuilder sb, int fieldSize, char padChar= ' ' )
	{
		// check for null parameter
		int sLen;
		if ( sb == null || (sLen= sb.Length) == 0 )
			return Append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.Max ( sLen, fieldSize );
		EnsureCapacity( Length + maxChars );

		// copy and adjust my length
		#if !ALOX_WP71
			// standard versions
			sb.CopyTo( 0, Buffer, Length, sLen );
			Length+= sLen;
		#else
			// Windows Phone 7.1 version (StringBuilder.CopyTo() not available)
			for (int i= 0; i < sLen; i++ )
				Buffer[ Length++ ]= sb[ i ];
		#endif


		// add pad characters
		int newLength= Length + ( fieldSize - sLen );
		while ( Length < newLength)
			Buffer[Length++]=	padChar;
		
		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append the given String and add padding spaces. </summary>
	 *
	 * <param name="ms">		The string to append. </param>
	 * <param name="fieldSize">	The minimum number of characters to append. </param>
	 * <param name="padChar">  	The character to add to the right of the given string src.
	 * 							Defaults to ' ' (space). </param>
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString AppendPadLeft( MString ms, int fieldSize, char padChar= ' ' )
	{
		// ensure capacity
		int sLen=		ms!= null ? ms.Length : 0;
		int maxChars=	Math.Max( sLen, fieldSize );
		EnsureCapacity( Length + maxChars );

		// add pad characters
		int newLength= Length + ( fieldSize - sLen );
		while ( Length < newLength )
			Buffer[Length++] = padChar;

		// copy string
		if ( sLen > 0 )
		{
			for (int i= 0 ; i < sLen ; i++ ) 
				Buffer[ Length++ ]= ms.Buffer[i];
		}

		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append the given String and add padding spaces. </summary>
	 *
	 * <param name="s">		   	The string to append. </param>
	 * <param name="fieldSize">	The minimum number of characters to append. </param>
	 * <param name="padChar">  	The character to add to the right of the given string src.
	 * 							Defaults to ' ' (space). </param>
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString AppendPadLeft( String s, int fieldSize, char padChar= ' ' )
	{
		// ensure capacity
		int sLen=		s != null ? s.Length : 0;
		int maxChars=	Math.Max( sLen, fieldSize );
		EnsureCapacity( Length + maxChars );

		// add pad characters
		int newLength= Length + ( fieldSize - sLen );
		while ( Length < newLength )
			Buffer[Length++] = padChar;

		// copy string
		if ( sLen > 0 )
		{
			s.CopyTo( 0, Buffer, Length, sLen );
			Length+= sLen;
		}

		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append the given StringBuilder and add padding spaces. </summary>
	 *
	 * <param name="sb">		The StringBuilder to append. </param>
	 * <param name="fieldSize">	The minimum number of characters to append. </param>
	 * <param name="padChar">  	The character to add to the right of the given string src.
	 * 							Defaults to ' ' (space). </param>
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString AppendPadLeft( StringBuilder sb, int fieldSize, char padChar= ' ' )
	{
		// ensure capacity
		int sLen=		sb != null ? sb.Length : 0;
		int maxChars=	Math.Max( sLen, fieldSize );
		EnsureCapacity( Length + maxChars );

		// add pad characters
		int newLength= Length + ( fieldSize - sLen );
		while ( Length < newLength )
			Buffer[Length++] = padChar;

		// copy string
		if ( sLen > 0 )
		{
			// copy and adjust my length
			#if !ALOX_WP71
				// standard versions
				sb.CopyTo( 0, Buffer, Length, sLen );
				Length+= sLen;
			#else
				// Windows Phone 7.1 version (StringBuilder.CopyTo() not available)
				for (int i= 0; i < sLen; i++ )
					Buffer[ Length++ ]= sb[ i ];
			#endif
		}



		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Append the given MString and add surrounding padding characters. </summary>
	 *
	 * <param name="ms">		The MString to append. </param>
	 * <param name="fieldSize">	The minimum number of characters to append. </param>
	 * <param name="padChar">  	The character to surround the Mutable string with.
	 * 							Defaults to ' ' (space). </param>
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString AppendPadCenter( MString ms, int fieldSize, char padChar = ' ' )
	{
		// check for null parameter
		int sLen;
		if ( ms == null || (sLen= ms.Length) == 0 )
			return Append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.Max( sLen, fieldSize );
		EnsureCapacity( Length + maxChars );

		// add left characters
		int leftPad= ( fieldSize - sLen ) / 2;
		for ( int i= 0; i < leftPad ; i++ )
			Buffer[Length++]=	padChar;

		// append the rest using AppendPadRight()
		return AppendPadRight( ms, fieldSize - leftPad, padChar );
	}

	/** ************************************************************************************************
	 * <summary>	Append the given String and add surrounding padding characters. </summary>
	 *
	 * <param name="s">		   	The String to append. </param>
	 * <param name="fieldSize">	The minimum number of characters to append. </param>
	 * <param name="padChar">  	The character to surround the Mutable string with.
	 * 							Defaults to ' ' (space). </param>
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString AppendPadCenter( String s, int fieldSize, char padChar = ' ' )
	{
		// check for null parameter
		int sLen;
		if ( s == null || (sLen= s.Length) == 0 )
			return Append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.Max( sLen, fieldSize );
		EnsureCapacity( Length + maxChars );

		// add left characters
		int leftPad= ( fieldSize - sLen ) / 2;
		for ( int i= 0; i < leftPad ; i++ )
			Buffer[Length++]=	padChar;

		// append the rest using AppendPadRight()
		return AppendPadRight( s, fieldSize - leftPad, padChar );
	}

	/** ************************************************************************************************
	 * <summary>	Append the given StringBuilder and add surrounding padding characters. </summary>
	 *
	 * <param name="sb">	   	The StringBuilder to append. </param>
	 * <param name="fieldSize">	The minimum number of characters to append. </param>
	 * <param name="padChar">  	The character to surround the Mutable string with.
	 * 							Defaults to ' ' (space). </param>
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString AppendPadCenter( StringBuilder sb, int fieldSize, char padChar = ' ' )
	{
		// check for null parameter
		int sLen;
		if ( sb == null || (sLen= sb.Length) == 0 )
			return Append( padChar, fieldSize );

		// ensure capacity
		int maxChars=	Math.Max( sLen, fieldSize );
		EnsureCapacity( Length + maxChars );

		// add left characters
		int leftPad= ( fieldSize - sLen ) / 2;
		for ( int i= 0; i < leftPad ; i++ )
			Buffer[Length++]=	padChar;

		// append the rest using AppendPadRight()
		return AppendPadRight( sb, fieldSize - leftPad, padChar );
	}


	/** ************************************************************************************************
	 * <summary>	Append the given 32-Bit integer value. </summary>
	 *
	 * <param name="i">		   	The integer value to append. </param>
	 * <param name="minDigits">	The minimum number of digits to append. Optional, defaults to 0.</param>
	 *
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( int i, int minDigits= 1 )
	{
		// Max/min Value: +/-2147483648
		// ensure capacity
		EnsureCapacity( Length + 11 ); // 10 + minus sign

		if ( i < 0 )
		{
			Buffer[Length++] = '-';
			return Append( (uint) -i, minDigits );
		}

		return Append( (uint) i, minDigits );
	}

	/** ************************************************************************************************
	 * <summary>	Append the given unsigned 32-Bit integer value. </summary>
	 *
	 * <param name="i">		   	the integer value to append. </param>
	 * <param name="minDigits">	The minimum number of digits to append. If the number has less digits
	 * 							than minDigits, then trailing '0's are added.
	 * 							Optional and defaults to 0.</param>
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( uint i, int minDigits= 1 )
	{
		// Max Value: 4294967296
		// ensure capacity
		EnsureCapacity( Length + 10 ); 

		// at least one digit!
		if ( minDigits < 1 ) 
			minDigits= 1;

		// main loop
		int		actDigit=		11; // 10 + 1 for the loop
		uint	actBase=		1000000000;
		bool	isUnder=		false;
		while ( --actDigit > 0)
		{
			// get next d
			uint d=			i / actBase;
			uint actBase2=  actBase;
			actBase/=	10;

			// did we hit i for the first time
			isUnder|= (d != 0);

			// don't print?
			if (!isUnder && actDigit > minDigits )
				continue;

			// print the digit 
			Buffer[ Length++ ]= (char) ( 48 + d ); // 48= '0'

			// next
			i=	i % actBase2;
		}
		
		// return me for concatenated operations	
		return this;
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Append the given double value using the minimum digits before and after the given number of
	 *  digits after dot.
	 * </summary>
	 * <param name="d">						the integer value to append. </param>
	 * <param name="minDigitsBeforeDot">	The minimum number of digits write before the dot. If the
	 * 										number has less digits than minDigits, then trailing '0's  
	 * 										are added. </param>
	 * <param name="digitsAfterDot">		The exact number of digits written after the dot. </param>
	 * <returns>	'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Append( double d, int minDigitsBeforeDot, int digitsAfterDot )
	{
		// negative? -> turn positive
		if ( d < 0d )
		{
			Append( '-' );
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
		int afterDot= (int) Math.Round( d );
		if ( afterDot == overflow )
		{
			afterDot= 0;
			beforeDot++;
		}
		
		// append integer part
		Append( beforeDot, minDigitsBeforeDot ).Append( '.' );
		
		// check for no digits after dot wanted
		if ( digitsAfterDot > 0 )
			Append( afterDot, digitsAfterDot );
		
		// return me for concatenated operations	
		return this;
	}

	/** ***********************************************************************************************
	 * <summary>	Go to the next tab stop by filling in pad characters repeatedly. </summary>
	 * <param name="tabSize">	  	The tab positions are multiples of this parameter. </param>
	 * <param name="tabReference">	(Optional) The tab reference position. has to be smaller than
	 * 								Length. Defaults to 0 (beginning of Buffer). For buffers with
	 * 								multiple lines, this parameter has to be set. </param>
	 * <param name="minPad">	  	(Optional) The minimum pad characters to add. </param>
	 * <param name="padChar">	  	(Optional) The character to add to the right of the given string
	 * 								src. Defaults to ' ' (space). </param>
	 * <returns>	'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString Tab( int tabSize, int tabReference= 0, int minPad= 1, char padChar= ' ')
	{
		// append minimum padding
		Append( padChar, minPad );

		// append characters to meet next tab
		Append( padChar, (tabSize - ( (Length - tabReference) % tabSize ) ) % tabSize );

		// return me for concatenated operations	
		return this;
	}


	/** ***********************************************************************************************
	 * <summary>	Appends platform specific new line character(s). Here: "\r\n" </summary>
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString NewLine()
	{
		// append a new line characters
		return Append( Environment.NewLine );
	}

	/** ***********************************************************************************************
	 * <summary>	Checks if the given String is located at the given position. </summary>
	 * <param name="s">				The string to search. </param>
	 * <param name="pos">			The to look at. </param>
	 * <param name="ignoreCase">	(Optional) If true, the compare is case insensitive. Optional and
	 * 								defaults to false. </param>
	 * <returns>
	 *  True if the given sequence is found at the given position. False otherwise .
	 * </returns>
	 **************************************************************************************************/
	public bool ContainsAt( String s, int pos, bool ignoreCase= false )
	{
		// check null argument or length 0
		int sLen=  	s != null ?  s.Length : 0;
		int cmpEnd= pos + sLen;
		if ( sLen == 0 || pos > Length || pos < 0 || cmpEnd > Length )
			return false;


		// the compare loop 
		int sPos= 0;
		while ( pos < cmpEnd )
		{
			char c1=	s[ sPos ];
			char c2=	Buffer[ pos ];
			if ( ignoreCase )
			{
				c1=	Char.ToLower( c1 );
				c2=	Char.ToLower( c2 );
			}
				
			if ( c1 != c2 )
				return false;
			
			pos++;
			sPos++;
		}
		
		return true;
	}

	/** ***********************************************************************************************
	 * <summary> Checks if this MString starts with the given sequence. </summary>
	 * <param name="s">	The String to search. If s is null or empty, false is returned.</param>
	 * <returns> true if this starts with the given sequence, false if not.</returns>
	 **************************************************************************************************/
	public bool StartsWith( String s )
	{
		return ContainsAt( s, 0, false );
	}

	/** ***********************************************************************************************
	 * <summary> Checks if this MString ends with the given sequence. </summary>
	 * <param name="s">	The String to search. If s is null or empty, false is returned.</param>
	 * <returns> true if this starts with the given sequence, false if not.</returns>
	 **************************************************************************************************/
	public bool EndsWith  ( String s )
	{
		if ( s == null ) 
			return false;

		return ContainsAt( s, Length - s.Length, false );
	}
	
	 
	/** ************************************************************************************************
	 * <summary>	Search the given String in the Buffer. </summary>
	 *
	 * <param name="s">		   	The string to search. </param>
	 * <param name="startIdx">	The index to start the search at. Optional and defaults to 0. </param>
	 *
	 * <returns>	-1 if the String is not found. Otherwise the index of first occurence. </returns>
	 **************************************************************************************************/
	public int IndexOf( String s, int startIdx= 0 )
	{
		// check null argument or length 0
		int sLen=  s != null ?  s.Length : 0;
		if ( sLen == 0 || startIdx > Length)
			return -1;

		// search
		char firstChar= s[ 0 ];	 // get first char once, as [] operation is expensive
		while ( startIdx < Length )
		{
			int		cmpLen= 0;
			char	sc=		firstChar;
			while ( Buffer[ startIdx + cmpLen ] == sc )
			{
				cmpLen++;
				if ( cmpLen == sLen )
					return startIdx;
				sc= s[cmpLen];
			}
			startIdx++;
		}

		// not found
		return -1;
	}
	
	/** ************************************************************************************************
	 * <summary>	Replace one more more occurrences of a string by another string. </summary>
	 *
	 * <param name="searchStr">			The string to be replaced. </param>
	 * <param name="newStr">			The replacement string. </param>
	 * <param name="startIdx">		 	The index where the search starts. Optional and defaults
	 * 									to 0. </param>
	 * <param name="maxReplacements">	The maximum number of replacements to perform. Optional and  
	 * 									defaults to int.MaxValue . </param>
	 *
	 * <returns> The number of replacements that where performed. </returns>
	 **************************************************************************************************/
	public int Replace( String searchStr, String newStr, int startIdx= 0, int maxReplacements= int.MaxValue )
	{
		// check null arguments
		if ( String.IsNullOrEmpty(searchStr) || newStr == null )
			return 0;

		// get some values
		int oLen=				searchStr.Length;
		int rLen=				newStr.Length;
		int diff=				rLen - oLen;
		
		int cntReplacements=	0;

		// replacement loop
		while ( true )
		{
			// search  next occurrence
			int idx= IndexOf( searchStr, startIdx );
			if (idx < 0 )
				return cntReplacements;

			// set dirty
			Hash= 0;
			
			// copy rest up
			if ( diff > 0 )
			{
				if ( Length + diff > Buffer.Length )
					EnsureCapacity( Length + diff );
				for ( int i= Length - 1; i >= idx + oLen; i-- )
					Buffer[ i + diff ]= Buffer[ i ];
				Length+= diff;
			}

			// copy rest down
			else if ( diff < 0 )
			{
				for ( int i= idx ; i < Length + diff ; i++ )
					Buffer[ i ]= Buffer[ i - diff ];
				Length+= diff;
			}

			// fill replacement in
			for ( int i= 0; i < rLen ; i++ )
				Buffer[ idx + i ]= newStr[ i ];

			// set start index to first character behind current replacement
			startIdx= idx+ rLen;

			// increase qty of replacements and check with maximum
			cntReplacements++;
			if ( cntReplacements >= maxReplacements )
				return cntReplacements;
		}
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Compares a given string (or part of it) with the contents of this. If the optionally given
	 *  substring start indices and lengths parameters are out of bounds, they are corrected. This
	 *  could lead to unwanted results in some cases.
	 * </summary>
	 * <remarks>	A, 5/22/2013. </remarks>
	 * <param name="cmp">			An object of type String, StringBuilder or MString that is
	 * 								compared to this. </param>
	 * <param name="ignoreCase">	(Optional) If true, the compare is case insensitive. Optional and
	 * 								defaults to false. </param>
	 * <param name="sStartIdx"> 	(Optional) The start of the substring within the given string
	 * 								that is to be compared to this. Defaults to 0. </param>
	 * <param name="sLen">			(Optional) The length of the substring within the given string
	 * 								that is to be compared to this. Defaults to int.MaxValue. </param>
	 * <param name="startIdx">  	(Optional) The start of the substring within this that is to be
	 * 								compared. Defaults to 0. </param>
	 * <param name="len">			(Optional) The length of the substring within this that is to be
	 * 								compared.
	 * 								 Defaults to int.MaxValue. </param>
	 * <returns>
	 *  0 if string are equal. -1 if the instance precedes given string, 1 the instance follows the
	 *  given string (same as String.CompareTo), or if given string in null.
	 * </returns>
	 **************************************************************************************************/
	public int CompareTo(	Object cmp, bool ignoreCase= false, 
							int sStartIdx=	0,	int sLen=	int.MaxValue, 
							int startIdx=	0,	int len=	int.MaxValue	)
	{
		// check null argument
		if ( cmp == null )	
			return 1;

		// convert object to one of the three supported types
		String			cmpS=	null;
		StringBuilder	cmpSB=	null;
		MString	cmpMS=  cmp as MString;
		if (cmpMS == null )
		{
			cmpSB= cmp as StringBuilder;
			if (cmpSB == null )
			{
				cmpS=	cmp as String;
				if (cmpS == null )
				{
					return 1; // unsupported object type given
				}
			}
		}

		// get length of cmp string
		int sLength= cmpMS != null ?						cmpMS.Length
									: ( cmpSB != null	?	cmpSB.Length 
														:	cmpS .Length  );

		// adjust range of cmp string
		adjustRangeAndTestIfEmpty( sLength, ref sStartIdx, ref sLen );
		adjustRangeAndTestIfEmpty(  Length, ref  startIdx, ref  len );

		// compare loop
		int  idx=  startIdx;	int  end=  startIdx +  len;
		int sIdx= sStartIdx;	int sEnd= sStartIdx + sLen;
		while ( true )
		{
			// end of one of the strings or both?
			bool exceededMe=	(idx  >= end);
			bool exceededExt=	(sIdx >= sEnd);
			if (exceededMe)		return  exceededExt ? 0 :  -1;
			if (exceededExt)	return						1;

			// compare act characters
			char c=  Buffer[ idx  ];
			char sc=	cmpMS != null	?	cmpMS.Buffer[ sIdx ] 
					: ( cmpSB != null	?	cmpSB		[ sIdx ] 
					:						cmpS		[ sIdx ]  );

			// different characters
			if ( c != sc )
			{
				if ( !ignoreCase )
					return c-sc;

				// still different?
				int diff= Char.ToLower( c  ) - Char.ToLower( sc );
				if ( diff != 0 )
					return diff;
			}

			// same char, increase indices
			idx++; sIdx++;
		}
	}

	/** ************************************************************************************************
	 * <summary> Converts all or a region of characters in the Buffer to upper or to lower case. </summary>
	 *
	 * <param name="toUpper">	  	If true, conversion to upper case is performed, to lower else. </param>
	 * <param name="substrStart"> 	Start of the substring to be converted. Defaults to 0 </param>
	 * <param name="substrLength">	Length of the substring to be converted. Defaults to int.MaxValue.</param>
	 *
	 * <returns> 'this' to allow concatenated calls. </returns>
	 **************************************************************************************************/
	public MString ConvertCase( bool toUpper, int substrStart= 0, int substrLength= int.MaxValue )
	{
		// mark has value as dirty
		Hash= 0;
		
		// adjust range
		if ( substrLength == int.MaxValue )			
		{
			if (substrStart < 0 )						
				substrStart=	0;
			substrLength=	Length - substrStart;
		}
		else 
			if (substrStart < 0 )						
			{ 
				substrLength+= substrStart;  
				substrStart=	0; 
			}

		int substrEnd= substrStart + substrLength;
		if ( substrEnd > Length )
			substrEnd= Length;

		// convert
		for ( int i= substrStart; i < substrEnd ; i++ )
			Buffer[ i ]=  toUpper	?	Char.ToUpperInvariant( Buffer[ i ] )
									:	Char.ToLowerInvariant( Buffer[ i ] );

		// return me for concatenated operations	
		return this;
	}

	/** ************************************************************************************************
	 * <summary>	Converts the MString into a String. </summary>
	 *
	 * <returns> A string that represents this object. </returns>
	 **************************************************************************************************/
	public override String ToString()
	{
		return new String( Buffer, 0, Length );
	}

	/** ************************************************************************************************
	 * <summary>	Creates a String from a region within MString. </summary>
	 *
	 * <param name="startIdx">	The start index of the region in this to create the string from. </param>
	 * <param name="length">  	(Optional) The maximum length of the region to create the string from.
	 * 							Defaults to int.MaxInt. </param>
	 *
	 * <returns> A string that represents the specified sub region of this object. </returns>
	 **************************************************************************************************/
	public string ToString( int startIdx, int length= int.MaxValue)
	{
		// adjust range, if empty return empty string
		if ( adjustRangeAndTestIfEmpty( Length, ref startIdx, ref length ) )
			return "";

		// create string
		return new String( Buffer, startIdx, length);
	}

	/** ************************************************************************************************
	 * <summary> 
	 *  Calculates the hash value using the same formula as java.lang.String.
	 * </summary>
	 *
	 * <returns> A hash value for this object. </returns>
	 **************************************************************************************************/
	public override int GetHashCode() 
	{
 		int h;
 		if ((h= Hash) == 0 && Length > 0) 
 		{
     		char[] buf=	Buffer;
     		int  len=	Length;
 
     		for (int i = 0; i < len; i++) 
         		h = 31*h + buf[i++];

     		Hash = h;
 		}
 		return h;
	}
 

	/** ************************************************************************************************
	 * <summary> 
	 *  Compares this to given object. Given object can be MString or String.
	 * </summary>
	 *
	 * <returns> True if given object equals this. </returns>
	 **************************************************************************************************/
	public override bool Equals( Object o )
	{
		// null? -> false
		if ( o == null )
			return false;
			
		// MString?
		if ( o is MString )
		{	
			// cast up
			MString ms=  (MString) o;

			// different length?
			if ( ms.Length != Length )
				return false;
				
			// character compare
			for (int i= Length - 1 ; i >= 0 ; i-- )
				if ( ms.Buffer[i] != Buffer[i] )
					return false;
			
			// equal		
			return true;
		}
		
		// String?
		if ( o is String )
		{	
			// cast up
			String s=  (String) o;

			// different length?
			if ( s.Length != Length )
				return false;
				
			// character compare
			for (int i= Length - 1 ; i >= 0 ; i-- )
				if ( s[ i ] != Buffer[ i ] )
					return false;
			
			// equal		
			return true;
		}
		
		// not a known comparable object
		return false; 
	}

	/** ***********************************************************************************************
	 * <summary>	Ensures that capacity. </summary>
	 * <param name="minLen">	The minimum length. </param>
	 **************************************************************************************************/
	public void EnsureCapacity( int minLen )
	{
		// As a side effect, flag has value as dirty
		Hash= 0;
		
		// big enough?
		if ( Buffer.Length >= minLen )
			return;

		// get new size, increase at least by 50%
		int newLength= Math.Max( minLen, Buffer.Length + (Buffer.Length / 2));

		// create new Buffer
		char[] newBuffer=	new char[ newLength ];

		// copy data
		Array.Copy(Buffer, newBuffer, Length );

		// set new Buffer 
		Buffer=	newBuffer;

/* UnitTest Version: always change size of buf
		// As a side effect, flag has value as dirty
		Hash= 0;
		// get new size, increase at least by 50%
		int newLength= minLen;

		// create new Buffer
		char[] newBuffer=	new char[ newLength ];

		// copy data
		Array.Copy(Buffer, newBuffer, Math.Min(Buffer.Length, newBuffer.Length) );

		// set new Buffer 
		Buffer=	newBuffer;
 */
	}

	// ################################################################################################
	// internals
	// ################################################################################################

 	/** ***********************************************************************************************
 	 * <summary> 
 	 * 	 Adjust a given range within an array to the array bounds and tests if range is empty. 
 	 * </summary>
 	 * <param name="referenceLen">	Length of the zero indexed reference array.  </param>
 	 * <param name="startIdx">	  	[in,out] The start index of the range. Negative values are adjusted
 	 * 								to 0 and length shortened accordingly. Values higher than referenceLen
 	 * 								are not adjusted, but function returns true in this case. </param>
 	 * <param name="len">		  	[in,out] The length of the range to be adjusted to the array 
 	 * 								bounds. A length of int.MaxValue is considered 'infinite' and cut
 	 * 								to maximum length beginning from adjusted startIdx.</param>
 	 * <returns> True if adjusted range is out of bounds or empty </returns>
 	 **************************************************************************************************/
 	protected bool adjustRangeAndTestIfEmpty(int referenceLen, ref int startIdx, ref int len )
	{
		// infinite length given?
		if ( len == int.MaxValue )			
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

		// is empty?
		return  ( startIdx >= referenceLen || len <= 0 );
	}

} // class Mutable String

} // namespace / EOF
