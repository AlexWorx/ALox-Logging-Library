package com.aworx.lox.core;

import java.util.ArrayList;

import com.aworx.lox.Log;
import com.aworx.util.MString;

/**********************************************************************************************//**
 * Class LogDomain represents a logging domain. Each log statement refers to such a
 * domain which can be defined specifically for different parts of your application like
 * assemblies, libraries, namespaces, specific code files or even for a single log call. Domains
 * can be created with path separators '/', for example 'COMM/SOCKET' could be the domain for
 * log calls in a socket class, residing within a communication library. The advantage of
 * creating paths and this way "sub domains", is that a whole bunch of logging domains can be
 * altered (on/off)
 * by just altering their root domain. Note: This class should not be used directly.
 * Nevertheless the interface is kept public which is a general design decision for the classes
 * of ALox libraries.
 **************************************************************************************************/
public class LogDomain
{
//#if ALOX_DEBUG || ALOX_REL_LOG

	// #################################################################################################
	// static fields
	// #################################################################################################
	/**	Contains all characters allowed for domain separation (slash, backslash and pipe symbol)  */
	public static	String				domainSeparatorChars=		"\\|/";

	// #################################################################################################
	// Public fields
	// #################################################################################################
	/** The name of the domain. For root domains, this is null. */
	public		MString					name;

	/** The parent domain. For root domains, this is null. */
	public	 	LogDomain				parent;

	/** A list of sub domains (recursion). ArrayList is the unsynchronized version of Vector */
	public		ArrayList<LogDomain>	subDomains;

	// #################################################################################################
	// Protected fields
	// #################################################################################################

	/** The actual user setting for the log level of the domain.  */
	protected	Log.DomainLevel			level;


	// #################################################################################################
	// Public interface
	// #################################################################################################

	/**********************************************************************************************//**
	 * Constructor for domain.
	 *
	 * @param parent    The parent domain. For root domains, this is null.
	 * @param name      The name of the domain. For root domains, this is null.
	 **************************************************************************************************/
	public LogDomain( LogDomain parent,  MString name )
	{
		// store parameters
		this.name=		name; 
		this.parent=	parent;

		// create sub domain list
		subDomains=		new ArrayList<LogDomain>();

		// set log level to All, if we have no parent, else we inherit from parent
		level= ( parent == null )	?  Log.DomainLevel.OFF
									:  Log.DomainLevel.INHERIT;
	}

	/**********************************************************************************************//**
	 * String representation of LogDomain, needed for debugger.
	 *
	 * @return  A string that represents this instance.
	 **************************************************************************************************/
	@Override public String toString()
	{
		return (  name != null  ? name.toString() : "ROOT" )
				+ ", level = "			+ level 
				+ ", #sub domains: "	+ subDomains.size();
	}

	/**********************************************************************************************//**
	 * Returns the domain log level. If set to _INHERIT, recursion with parent domain is performed.
	 *
	 * @return  The found/defined domain log level.
	 **************************************************************************************************/
	public Log.DomainLevel getLevel()
	{
		// recursively find a defined level
		LogDomain		p=		this.parent;
		Log.DomainLevel	l=		this.level;
		while (l == Log.DomainLevel.INHERIT && p != null )
		{
			l=		p.level;
			p=		p.parent;
		}

		// return result
		return l;
	}

	/**********************************************************************************************//**
	 * Sets the level of the this domain and optionally for all sub domains to the specified value.
	 * The root domain's level is always set to All and can not be changed.
	 *
	 * @param domainLevel   The domain level value to set.
	 * @param recursive     true to process recursively, false to process locally only.
	 **************************************************************************************************/
	public void setLevel( Log.DomainLevel domainLevel, boolean recursive )
	{
		// set it for myself (only if I am not root domain)
		this.level= domainLevel;

		// recursively set level for sub domains
		if ( recursive )
		{
			for ( LogDomain domain : subDomains )
				domain.setLevel( level, true );
		}
	}

	/**********************************************************************************************//**
	 * Determines if the domain is active in respect to the given Log.Level and the current domain
	 * level.
	 *
	 * @param cmpLevel     The log level to check.
	 *
	 * @return  True if domain is active (log should be performed)
	 **************************************************************************************************/
	public	boolean isActive( Log.Level cmpLevel )
	{
		Log.DomainLevel domainLevel= getLevel();

		assert ( domainLevel != Log.DomainLevel.INHERIT );

		//	Log/Domain Level	Log.DomainLevelVerbose  Info     Warning     Error
		//  -----------------------------------------------------------------
		//	Off						|     -        -        -           -
		//	Errors					|     -        -        -           Y
		//	WarningsAndErrors		|     -        -        Y           Y
		//	InfoWarningsAndErrors	|     -        Y        Y           Y
		//	All						|     Y        Y        Y           Y
		return		( domainLevel == Log.DomainLevel.ERRORS						&&		cmpLevel == Log.Level.ERROR )
				||	( domainLevel == Log.DomainLevel.WARNINGS_AND_ERRORS		&&    (	cmpLevel == Log.Level.WARNING || cmpLevel == Log.Level.ERROR ) )
				||	( domainLevel == Log.DomainLevel.INFO_WARNINGS_AND_ERRORS	&&		cmpLevel != Log.Level.VERBOSE )
				||	  domainLevel == Log.DomainLevel.ALL;
	}

	/**********************************************************************************************//**
	 * Searches a domain. If the flag createIfNotExistant is set, then one or more sub domains are
	 * created as needed. If the path String starts with a domain separator character, then the
	 * search (and creation) is done starting from the root domain of this domain and not from this
	 * domain.
	 *
	 * @param domainPath            Path and domain to search.
	 * @param createIfNotExistant   If set true, domains in the path that are not found are created.
	 *
	 * @return  The domain found or created.
	 **************************************************************************************************/
	public LogDomain findOrCreate( MString domainPath, boolean createIfNotExistant)
	{
		// check if given domain path starts with domain separators
		int startIdx= 0;
		int len=	domainPath.length;
		while (startIdx < len && ( domainSeparatorChars.indexOf( domainPath.buffer[ startIdx ] ) >= 0 ) )
			startIdx++;

		// if string is empty, return ourselves
		if ( startIdx == len )
			return this;

		// Trailing domain separator found: call find on root domain
		LogDomain ld= this;
		if ( startIdx > 0 ) 				
		{
			while (ld.parent != null )
				ld= ld.parent;
		}

		// call find
		return ld.findOrCreateInternal( domainPath, startIdx, createIfNotExistant );
	}

	/**********************************************************************************************//**
	 * The internal recursive helper to implement the FindOrCreate() interface.
	 *
	 * @param domainPath            Path to search.
	 * @param dpStartIdx            The current scan position in the domain string.
	 * @param createIfNotExistant   Create domain if not found on the path.
	 *
	 * @return  The found domain.
	 **************************************************************************************************/
	@SuppressWarnings ("null") 
	protected LogDomain findOrCreateInternal( MString	domainPath,	int dpStartIdx, boolean createIfNotExistant)
	{
		//--- get act sub-name and rest of path
		int dsLen=	domainPath.length;
		int pEnd;
		int pNext;
		{
			// adjust start pos (remove trailing "/")
			while (dpStartIdx < dsLen && ( domainSeparatorChars.indexOf( domainPath.buffer[ dpStartIdx ] ) >= 0 ) )
				dpStartIdx++;

			// find end of act name
			pEnd= dpStartIdx + 1;
			while (pEnd < dsLen &&   ( domainSeparatorChars.indexOf( domainPath.buffer[ pEnd ] ) < 0 ) )
				pEnd++;

			// check
			if ( dpStartIdx >= dsLen )
			{
				// we can not even create a domain
				return null;
			}

			// find start of rest, mark as negative pos if empty
			pNext= pEnd + 1;
			while (pNext < dsLen &&  ( domainSeparatorChars.indexOf( domainPath.buffer[ pNext ] ) >= 0 ) )
				pNext++;

			if ( pNext >= dsLen )
				pNext= -1;
		}
		
		// search act domain
		int			idx=		0;
		LogDomain	subDomain=	null;
		int			comparison= -1;
		while ( idx < subDomains.size() )
		{
			subDomain=	subDomains.get( idx );
			comparison= subDomain.name.compareTo( domainPath, false, dpStartIdx, pEnd - dpStartIdx);

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
			subDomains.add( idx, subDomain );
		}

		// recursion? 
		if ( pNext > 0 )
			return subDomain.findOrCreateInternal( domainPath, pNext, createIfNotExistant );

		// that's it
		return subDomain;
	}

	//#endif
} // LogDomain
