// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using cs.aworx.lib;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;



namespace cs.aworx.lox.core {
/** ************************************************************************************************
 * Objects of this class represent a logging Domain. Each log statement refers to
 * such a domain which can be defined specifically for different parts of your application like
 * assemblies, libraries, namespaces, specific code files or even for a single log call.
 * Domains can be created with path separators '/', for example 'COMM/SOCKET' could be the domain
 * for log calls in a socket class, residing within a communication library. The advantage of
 * creating paths and this way trees of domains, is that a whole bunch of logging domains can
 * be altered (in respect of logging verbosity) by just changing their root domain.
 * \note This class should not be used directly. Nevertheless the interface is kept public which is
 *       a general design decision for the classes of ALox libraries.
 **************************************************************************************************/
public class Domain
{

#if ALOX_DBG_LOG || ALOX_REL_LOG

    // #############################################################################################
    // static fields
    // #############################################################################################
    /**
     * Contains all characters allowed for domain separation (slash, backslash and pipe symbol)
     */
    public static   String                  DomainSeparatorChars                            ="\\|/";

    // #############################################################################################
    // Public fields
    // #############################################################################################
    /// The name of the domain. For root domains, this is null.
    public          AString                 Name;

    /// The parent domain. For root domains, this is null.
    public          Domain                  Parent;

    /// A list of sub domains (recursion).
    public          List<Domain>            SubDomains;


    // #############################################################################################
    // Protected fields
    // #############################################################################################
    //
    /// The actual user setting for the log level of the domain.
    protected       Log.DomainLevel         level;


    // #############################################################################################
    // Public interface
    // #############################################################################################

    /** ********************************************************************************************
     * Constructor for domain.
     * @param parent     The parent domain. For root domains, this is null. </param>
     * @param name       The name of the domain. For root domains, this is null. </param>
     **********************************************************************************************/
    public Domain( Domain parent,  AString name )
    {
        // store parameters
        this.Name=        name;
        this.Parent=    parent;

        // create sub domain list
        SubDomains=        new List<Domain>();

        // set log level to Off, if we have no parent, else we inherit from parent
        level= ( parent == null )  ?  Log.DomainLevel.Off
                                   :  Log.DomainLevel.Inherit;
    }

    /** ********************************************************************************************
     * Returns the domains log level. If this is set to INHERIT, the effective value is evaluated
     * (recursively) from the parent's domain.
     *
     * @return The found/defined domain log level.
     **********************************************************************************************/
    public Log.DomainLevel GetLevel()
    {
        // recursively find a defined level
        Domain       parent= this.Parent;
        Log.DomainLevel level=  this.level;
        while (level == Log.DomainLevel.Inherit && parent != null )
        {
            level=  parent.level;
            parent= parent.Parent;
        }

        // return result
        return level;
    }

    /** ********************************************************************************************
     * Sets the level of this domain and optionally of all its sub domains to the specified value.
     * \note
     *   The root domain's level can not be set to DomainLevel.Inherit.
     *   Such request would be ignored.
     *
     * @param domainLevel The domain level value to set.
     * @param propagation If \c Propagation.ToDescendants (the default), the level is set for all
     *                    sub-domains currently existing.
     *                    If \c Propagation.None, then only this domain is changed.
     **********************************************************************************************/
    public void SetLevel( Log.DomainLevel domainLevel, Propagation propagation = Propagation.ToDescendants )
    {
        // set it for myself (only if I am not root domain)
        if ( Parent != null || domainLevel != Log.DomainLevel.Inherit)
            this.level= domainLevel;

        // recursively set level for sub domains
        if ( propagation == Propagation.ToDescendants )
            foreach ( Domain domain in SubDomains )
                domain.SetLevel ( domainLevel, Propagation.ToDescendants );
    }

    /** ********************************************************************************************
     *  Determines if the domain is active in respect to the given Log.Level and the current domain
     *  level.
     *
     * @param level  The log level to check.
     * @return  True if domain is active (log should be performed)
     **********************************************************************************************/
    public    bool IsActive( Log.Level level )
    {
        Log.DomainLevel domainLevel= GetLevel();

        ALIB.ASSERT( domainLevel != Log.DomainLevel.Inherit );

        //    Level / DomainLevel      |   Verbose  Info     Warning     Error
        //  -----------------------------------------------------------------
        //    Off                      |     -        -        -           -
        //    Errors                   |     -        -        -           Y
        //    WarningsAndErrors        |     -        -        Y           Y
        //    InfoWarningsAndErrors    |     -        Y        Y           Y
        //    All                      |     Y        Y        Y           Y
        return        ( domainLevel == Log.DomainLevel.Errors                   &&        level == Log.Level.Error )
                ||    ( domainLevel == Log.DomainLevel.WarningsAndErrors        &&    (   level == Log.Level.Warning || level == Log.Level.Error ) )
                ||    ( domainLevel == Log.DomainLevel.InfoWarningsAndErrors    &&        level != Log.Level.Verbose )
                ||      domainLevel == Log.DomainLevel.All;
    }

    /** ********************************************************************************************
     * Searches a domain. If not found, the domain is (or branch of domains are) created in
     * the domain tree.
     * If the path String starts with a domain separator character, then
     * the search (and creation) is done starting from the root domain of this domain and not
     * from this domain.
     *
     * @param       domainPath  Path and domain to search.
     * @param[out]  wasCreated  Output parameter that is set \c true if domain was not found
     *                          and hence created.
     * @return    The domain found or created.
     **********************************************************************************************/
    public Domain Find( AString domainPath, ref bool wasCreated )
    {
        wasCreated= false;
        // check if given domain path starts with domain separators
        int startIdx= 0;
        int len=      domainPath.Length();
        {
            char[] domainPathBuffer= domainPath.Buffer();
            while (startIdx < len && ( DomainSeparatorChars.IndexOf( domainPathBuffer[ startIdx ] ) >= 0 ) )
                startIdx++;
        }

        // if string is empty, return ourselves
        if ( startIdx == len )
            return this;

        // Trailing domain separator found: call find on root domain
        Domain ld= this;
        if ( startIdx > 0 )
        {
            while (ld.Parent != null )
                ld= ld.Parent;
        }

        // call find
        return ld.findRecursive( domainPath, startIdx, ref wasCreated );
    }

    /** ********************************************************************************************
     * The internal recursive helper to implement the Find() interface.
     *
     * @param       domainPath  Path to search.
     * @param       dpStartIdx  The current scan position in the domain string.
     * @param[out]  wasCreated  Output parameter that is set \c true if domain was not found
     *                          and hence created.
     * @return  The domain found or created.
     **********************************************************************************************/
    protected Domain findRecursive( AString domainPath, int dpStartIdx, ref bool wasCreated )
    {
        //--- get act sub-name and rest of path
        int dsLen=    domainPath.Length();
        int pEnd;
        int pNext;
        {
            char[]    domainPathBuffer=    domainPath.Buffer();

            // adjust start pos (remove trailing "/")
            while (dpStartIdx < dsLen && ( DomainSeparatorChars.IndexOf( domainPathBuffer[ dpStartIdx ] ) >= 0 ) )
                dpStartIdx++;

            // find end of act name
            pEnd= dpStartIdx + 1;
            while (pEnd < dsLen &&   ( DomainSeparatorChars.IndexOf( domainPathBuffer[ pEnd ] ) < 0 ) )
                pEnd++;

            // check
            if ( dpStartIdx >= dsLen )
            {
                // we can not even create a domain
                return null;
            }

            // find start of rest, mark as negative position if empty
            pNext= pEnd + 1;
            while (pNext < dsLen &&  ( DomainSeparatorChars.IndexOf( domainPathBuffer[ pNext ] ) >= 0 ) )
                pNext++;

            if ( pNext >= dsLen )
                pNext= -1;
        }

        // search act domain
        int         idx=        0;
        Domain   subDomain=    null;
        int         comparison= -1;
        while ( idx < SubDomains.Count )
        {
            subDomain=  SubDomains[idx];
            comparison= subDomain.Name.CompareTo( domainPath, Case.Sensitive, dpStartIdx, pEnd - dpStartIdx);

            if( comparison >= 0 )
                break;

            idx++;
        }

        // domain not found? Then create
        if ( comparison != 0 )
        {
            subDomain= new Domain( this, new AString( domainPath, dpStartIdx, pEnd-dpStartIdx ) );
            SubDomains.Insert( idx, subDomain );
            wasCreated= true;
        }

        // recursion?
        if ( pNext > 0 )
            return subDomain.findRecursive( domainPath, pNext, ref wasCreated );

        // that's it
        return subDomain;
    }

    /** ****************************************************************************************
     * This is for debugging purposes. E.g. this enables the \e Monodevelop IDE to display
     * object descriptions in the debugger.
     * @returns A human readable string representation of this object.
     ******************************************************************************************/
    public override String ToString()
    {
        String result=  "";

        // get full name
        Domain actDomain= this;
        while( actDomain != null )
        {
            if ( actDomain.Name != null )
            {
                if (result != "" )
                    result= "/" + result;
                result= actDomain.Name + result;
            }
            actDomain= actDomain.Parent;
        }
        result= "/" + result;

        // get level
        Log.DomainLevel dl= GetLevel();
        result= result + " <" + dl.ToString() + ">";
        if ( level == Log.DomainLevel.Inherit )
            result= result + " (inherited)";

        return result;
    }

    #endif
} // Domain

} // namespace
