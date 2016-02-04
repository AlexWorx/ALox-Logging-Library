// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core;

import java.util.ArrayList;

import com.aworx.lib.ALIB;
import com.aworx.lib.enums.Case;
import com.aworx.lib.enums.Propagation;
import com.aworx.lib.strings.AString;
import com.aworx.lox.Log;
import com.aworx.lox.Log.DomainLevel;

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
    // #############################################################################################
    // static fields
    // #############################################################################################
    /**    Contains all characters allowed for domain separation (slash, backslash and pipe symbol)  */
    public static String                    domainSeparatorChars=        "\\|/";

    // #############################################################################################
    // Public fields
    // #############################################################################################
    /** The name of the domain. For root domains, this is null. */
    public        AString                   name;

    /** The parent domain. For root domains, this is null. */
    public        Domain                    parent;

    /** A list of sub domains (recursion). ArrayList is the unsynchronized version of Vector */
    public        ArrayList<Domain>         subDomains;

    // #############################################################################################
    // Protected fields
    // #############################################################################################

    /** The actual user setting for the log level of the domain.  */
    protected     Log.DomainLevel           level;

    // #############################################################################################
    // Public interface
    // #############################################################################################

    /** ********************************************************************************************
     * Constructor for domain.
     *
     * @param parent    The parent domain. For root domains, this is null.
     * @param name      The name of the domain. For root domains, this is null.
     **********************************************************************************************/
    public Domain( Domain parent,  AString name )
    {
        // store parameters
        this.name=   name;
        this.parent= parent;

        // create sub domain list
        subDomains=        new ArrayList<Domain>();

        // set log level to OFF, if we have no parent, else we inherit from parent
        level= ( parent == null )   ?  Log.DomainLevel.OFF
                                    :  Log.DomainLevel.INHERIT;
    }

    /** ********************************************************************************************
     * Returns the domains log level. If this is set to INHERIT, the effective value is evaluated
     * (recursively) from the parent's domain.
     *
     * @return  The found/defined domain log level.
     **********************************************************************************************/
    public Log.DomainLevel getLevel()
    {
        // recursively find a defined level
        Domain        p=        this.parent;
        Log.DomainLevel  l=        this.level;
        while (l == Log.DomainLevel.INHERIT && p != null )
        {
            l=  p.level;
            p=  p.parent;
        }

        return l;
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
    public void setLevel( Log.DomainLevel domainLevel, Propagation propagation )
    {
        // set it for myself
        if ( parent != null || level != Log.DomainLevel.INHERIT)
            this.level= domainLevel;

        // recursively set level for sub domains
        if ( propagation == Propagation.TO_DESCENDANTS)
        {
            for ( Domain domain : subDomains )
                domain.setLevel( level, Propagation.TO_DESCENDANTS );
        }
    }

    /** ********************************************************************************************
     * Sets the level of this domain and of all its sub domains to the specified value.
     * \note
     *   The root domain's level can not be set to DomainLevel.Inherit.
     *   Such request would be ignored.
     *
     * @param domainLevel The domain level value to set.
     **********************************************************************************************/
    public void setLevel( Log.DomainLevel domainLevel )
    {
        setLevel( domainLevel, Propagation.TO_DESCENDANTS );
    }

    /** ********************************************************************************************
     * Determines if the domain is active in respect to the given Log.Level and the current domain
     * level.
     *
     * @param cmpLevel     The log level to check.
     *
     * @return  True if domain is active (log should be performed)
     **********************************************************************************************/
    public    boolean isActive( Log.Level cmpLevel )
    {
        Log.DomainLevel domainLevel= getLevel();

        ALIB.ASSERT( domainLevel != Log.DomainLevel.INHERIT );

        //                                   Verbose  Info     Warning     Error
        //  -----------------------------------------------------------------
        //    Off                        |     -        -        -           -
        //    Errors                     |     -        -        -           Y
        //    WarningsAndErrors          |     -        -        Y           Y
        //    InfoWarningsAndErrors      |     -        Y        Y           Y
        //    All                        |     Y        Y        Y           Y
        return     ( domainLevel == Log.DomainLevel.ERRORS                     &&        cmpLevel == Log.Level.ERROR )
                || ( domainLevel == Log.DomainLevel.WARNINGS_AND_ERRORS        &&    (   cmpLevel == Log.Level.WARNING || cmpLevel == Log.Level.ERROR ) )
                || ( domainLevel == Log.DomainLevel.INFO_WARNINGS_AND_ERRORS   &&        cmpLevel != Log.Level.VERBOSE )
                ||   domainLevel == Log.DomainLevel.ALL;
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
    public Domain find( AString domainPath, boolean[] wasCreated )
    {
        if ( wasCreated != null )
            wasCreated[0]= false;

        // check if given domain path starts with domain separators
        int     startIdx=            0;
        int     len=                domainPath.length();
        {
            char[]    domainPathBuffer=    domainPath.buffer();
            while (startIdx < len && ( domainSeparatorChars.indexOf( domainPathBuffer[ startIdx ] ) >= 0 ) )
                startIdx++;
        }

        // if string is empty, return ourselves
        if ( startIdx == len )
            return this;

        // Trailing domain separator found: call find on root domain
        Domain startDomain= this;
        if ( startIdx > 0 )
        {
            while (startDomain.parent != null )
                startDomain= startDomain.parent;
        }

        // call find
        return startDomain.findRecursive( domainPath, startIdx, wasCreated );
    }

    /** ********************************************************************************************
     * The internal recursive helper to implement the Find() interface.
     *
     * @param       domainPath  Path to search.
     * @param       dpStartIdx  The current scan position in the domain string.
     * @param[out]  wasCreated  Output parameter that is set \c true if domain was not found
     *                          and hence created.
     * @return    The domain found or created.
     **********************************************************************************************/
    @SuppressWarnings ("null")
    protected Domain findRecursive( AString domainPath, int dpStartIdx, boolean[] wasCreated )
    {
        //--- get act sub-name and rest of path
        int    dsLen=    domainPath.length();
        int    pEnd;
        int    pNext;
        {
            char[]    domainPathBuffer=    domainPath.buffer();

            // adjust start pos (remove trailing "/")
            while (dpStartIdx < dsLen && ( domainSeparatorChars.indexOf( domainPathBuffer[ dpStartIdx ] ) >= 0 ) )
                dpStartIdx++;

            // find end of act name
            pEnd= dpStartIdx + 1;
            while (pEnd < dsLen &&   ( domainSeparatorChars.indexOf( domainPathBuffer[ pEnd ] ) < 0 ) )
                pEnd++;

            // check
            if ( dpStartIdx >= dsLen )
            {
                // we can not even create a domain
                return null;
            }

            // find start of rest, mark as negative pos if empty
            pNext= pEnd + 1;
            while (pNext < dsLen &&  ( domainSeparatorChars.indexOf( domainPathBuffer[ pNext ] ) >= 0 ) )
                pNext++;

            if ( pNext >= dsLen )
                pNext= -1;
        }

        // search act domain
        int          idx=        0;
        Domain    subDomain=  null;
        int          comparison= -1;
        while ( idx < subDomains.size() )
        {
            subDomain=    subDomains.get( idx );
            comparison= subDomain.name.compareTo( domainPath, Case.SENSITIVE, dpStartIdx, pEnd - dpStartIdx);

            if( comparison >= 0 )
                break;

            idx++;
        }

        // domain not found? Then create
        if ( comparison != 0 )
        {
            subDomain= new Domain( this, new AString( domainPath, dpStartIdx, pEnd-dpStartIdx ) );
            subDomains.add( idx, subDomain );
            if ( wasCreated != null )
                wasCreated[0]= true;
        }

        // recursion?
        if ( pNext > 0 )
            return subDomain.findRecursive( domainPath, pNext, wasCreated );

        // that's it
        return subDomain;
    }

    /** ****************************************************************************************
     * This is for debugging purposes. E.g. this enables the \e Eclipse IDE to display
     * object descriptions in the debugger.
     * @returns A human readable string representation of this object.
     ******************************************************************************************/
    @Override
    public String toString()
    {
        String result=  "";

        // get full name
        Domain actDomain= this;
        while( actDomain != null )
        {
            if ( actDomain.name != null )
            {
                if (result != "" )
                    result= "/" + result;
                result= actDomain.name + result;
            }
            actDomain= actDomain.parent;
        }
        result= "/" + result;

        // get level
        DomainLevel dl= getLevel();
        result= result + " <" + dl.toString() + ">";
        if ( level == DomainLevel.INHERIT )
            result= result + " (inherited)";

        return result;
    }
} // class Domain
