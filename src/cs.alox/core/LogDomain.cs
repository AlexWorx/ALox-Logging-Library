// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Classes:	LogDomain
//  File:		LogDomain.cs										Namespace:  com.aworx.lox.core
// #################################################################################################

using System;
using System.Collections.Generic;
using com.aworx.util;



namespace com.aworx.lox.core {
/** ***********************************************************************************************
 * <summary>
 *  Class <c>LogDomain</c> represents a logging Domain. Each log statement refers to
 *  such a domain which can be defined specifically for different parts of your application like
 *  assemblies, libraries, namespaces, specific code files or even for a single log call.
 *  Domains can be created with path separators '/', for example 'COMM/SOCKET' could be the domain
 *  for log calls in a socket class, residing within a communication library. The advantage of creating 
 *  paths and this way "sub domains", is that a whole bunch of logging domains can be altered (on/off)
 *  by just altering their root domain. 
 *  Note: This class should not be used directly. Nevertheless the interface is kept public which is
 *  a general design decision for the classes of ALox libraries.
 * </summary>
 **************************************************************************************************/
public class LogDomain
{

#if ALOX_DEBUG || ALOX_REL_LOG

	// #################################################################################################
	// static fields
	// #################################################################################################
	/** <summary>
	 * 	Contains all characters allowed for domain separation (slash, backslash and pipe symbol)
	 * </summary> */
	public static	String			DomainSeparatorChars=		"\\|/";

	// #################################################################################################
	// Public fields
	// #################################################################################################
	/// <summary> The name of the domain. For root domains, this is null.</summary>
	public		MString		Name;

	/// <summary> The parent domain. For root domains, this is null.</summary>
	public	 	LogDomain			Parent;

	/// <summary> A list of sub domains (recursion).</summary>
	public		List<LogDomain>		SubDomains;


	// #################################################################################################
	// Protected fields
	// #################################################################################################
	// 
	/// <summary> The actual user setting for the log level of the domain. </summary>
	protected	Log.DomainLevel		level;


	// #################################################################################################
	// Public interface
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>	Constructor for domain. </summary>
	 * <param name="parent">	The parent domain. For root domains, this is null. </param>
	 * <param name="name">  	The name of the domain. For root domains, this is null. </param>
	 **************************************************************************************************/
	public LogDomain( LogDomain parent,  MString name )
	{


		// store parameters
		this.Name=		name; 
		this.Parent=	parent;

		// create sub domain list
		SubDomains=		new List<LogDomain>();

		// set log level to All, if we have no parent, else we inherit from parent
		level= ( parent == null )	?  Log.DomainLevel.Off
									:  Log.DomainLevel.Inherit;
	}

	/** ***********************************************************************************************
	 * <summary>	String representation of LogDomain, needed for debugger. </summary>
	 * <returns>	A string that represents this instance. </returns>
	 **************************************************************************************************/
	public override String ToString()
	{
		return (  Name != null  ? Name.ToString() : "ROOT" )
				+ ", level = "			+ level 
				+ ", #sub domains: "	+ SubDomains.Count;
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Returns the domain log level. If set to Inherit, recursion with parent domain is performed.
	 * </summary>
	 * <returns>The found/defined domain log level. </returns>
	 **************************************************************************************************/
	public Log.DomainLevel GetLevel()
	{
		// recursively find a defined level
		LogDomain			parent=		this.Parent;
		Log.DomainLevel		level=		this.level;
		while (level == Log.DomainLevel.Inherit && parent != null )
		{
			level=		parent.level;
			parent=		parent.Parent;
		}

		// return result
		return level;
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Sets the level of the this domain and optionally for all sub domains to the specified value.
	 *  The root domain's level is always set to All and can not be changed.
	 * </summary>
	 * <param name="level">		The domain level value to set.  </param>
	 * <param name="recursive">	true to process recursively, false to process locally only. </param>
	 **************************************************************************************************/
	public void SetLevel( Log.DomainLevel level, bool recursive )
	{
		// set it for myself (only if I am not root domain)
		this.level= level;

		// recursively set level for sub domains
		if ( recursive )
			foreach ( LogDomain domain in SubDomains )
				domain.SetLevel ( level, true );
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Determines if the domain is active in respect to the given Log.Level and the current domain 
	 *  level.
	 * </summary>
	 * <param name="level">	The log level to check . </param>
	 * <returns>	True if domain is active (log should be performed) </returns>
	 **************************************************************************************************/
	public	bool IsActive( Log.Level level )
	{
		Log.DomainLevel domainLevel= GetLevel();

		System.Diagnostics.Debug.Assert ( domainLevel != Log.DomainLevel.Inherit );

		//	Level / DomainLevel		|   Verbose  Info     Warning     Error
		//  -----------------------------------------------------------------
		//	Off						|     -        -        -           -
		//	Errors					|     -        -        -           Y
		//	WarningsAndErrors		|     -        -        Y           Y
		//	InfoWarningsAndErrors	|     -        Y        Y           Y
		//	All						|     Y        Y        Y           Y
		return		( domainLevel == Log.DomainLevel.Errors					&&		level == Log.Level.Error )
				||	( domainLevel == Log.DomainLevel.WarningsAndErrors		&&    (	level == Log.Level.Warning || level == Log.Level.Error ) )
				||	( domainLevel == Log.DomainLevel.InfoWarningsAndErrors	&&		level != Log.Level.Verbose )
				||	  domainLevel == Log.DomainLevel.All;
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Searches a domain. If the flag createIfNotExistant is set, then one or more sub domains are
	 *  created as needed. If the path String starts with a domain separator character, then the
	 *  search (and creation) is done starting from the root domain of this domain and not from this
	 *  domain.
	 * </summary>
	 * <param name="domainPath">		 	Path and domain to search. </param>
	 * <param name="createIfNotExistant">	If set true, domains in the path that are not found are
	 * 										created. </param>
	 * <returns>	The domain found or created. </returns>
	 **************************************************************************************************/
	public LogDomain FindOrCreate( MString domainPath, bool createIfNotExistant)
	{
		// check if given domain path starts with domain separators
		int startIdx= 0;
		int len=	domainPath.Length;
		while (startIdx < len && ( DomainSeparatorChars.IndexOf( domainPath.Buffer[ startIdx ] ) >= 0 ) )
			startIdx++;

		// if string is empty, return ourselves
		if ( startIdx == len )
			return this;

		// Trailing domain separator found: call find on root domain
		LogDomain ld= this;
		if ( startIdx > 0 ) 				
		{
			while (ld.Parent != null )
				ld= ld.Parent;
		}

		// call find
		return ld.findOrCreateInternal( domainPath, startIdx, createIfNotExistant );
	}

	/** ***********************************************************************************************
	 * <summary>	The internal recursive helper to implement the FindOrCreate() interface. </summary>
	 * <param name="domainPath">		 	Path to search. </param>
	 * <param name="dpStartIdx">		 	The current scan position in the domain string. </param>
	 * <param name="createIfNotExistant">	Create domain if not found on the path. </param>
	 * <returns>	The found domain. </returns>
	 **************************************************************************************************/
	protected LogDomain findOrCreateInternal( MString	domainPath,	int dpStartIdx, bool createIfNotExistant)
	{
		//--- get act sub-name and rest of path
		int dsLen=	domainPath.Length;
		int pEnd;
		int pNext;
		{
			// adjust start pos (remove trailing "/")
			while (dpStartIdx < dsLen && ( DomainSeparatorChars.IndexOf( domainPath.Buffer[ dpStartIdx ] ) >= 0 ) )
				dpStartIdx++;

			// find end of act name
			pEnd= dpStartIdx + 1;
			while (pEnd < dsLen &&   ( DomainSeparatorChars.IndexOf( domainPath.Buffer[ pEnd ] ) < 0 ) )
				pEnd++;

			// check
			if ( dpStartIdx >= dsLen )
			{
				// we can not even create a domain
				return null;
			}

			// find start of rest, mark as negative pos if empty
			pNext= pEnd + 1;
			while (pNext < dsLen &&  ( DomainSeparatorChars.IndexOf( domainPath.Buffer[ pNext ] ) >= 0 ) )
				pNext++;

			if ( pNext >= dsLen )
				pNext= -1;
		}
		
		// search act domain
		int			idx=		0;
		LogDomain	subDomain=	null;
		int			comparison= -1;
		while ( idx < SubDomains.Count )
		{
			subDomain=	SubDomains[idx];
			comparison= subDomain.Name.CompareTo( domainPath, false, dpStartIdx, pEnd - dpStartIdx);

			if( comparison >= 0 )
				break;

			idx++;
		}

		// domain not found
		if ( comparison != 0 )
		{
			// return null if we are not asked to create 
			if ( !createIfNotExistant )
				return null;

			// create domain
			subDomain= new LogDomain( this, new MString( domainPath, dpStartIdx, pEnd-dpStartIdx ) );
			SubDomains.Insert( idx, subDomain );
		}

		// recursion? 
		if ( pNext > 0 )
			return subDomain.findOrCreateInternal( domainPath, pNext, createIfNotExistant );

		// that's it
		return subDomain;
	}

	#endif
} // LogDomain

} // namespace
