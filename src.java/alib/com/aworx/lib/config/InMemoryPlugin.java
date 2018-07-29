// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import java.util.ArrayList;

import com.aworx.lib.lang.Case;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.util.Tokenizer;

/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugin, which holds
 * configuration variables in memory. Instances of this class are used to create two plug-ins
 * within standard configurations:
 * - One with priority
 *   \ref com.aworx.lib.config.Configuration.PRIO_DEFAULT_VALUES "PRIO_DEFAULT_VALUES" (low priority)
 *   to store default values not found in other configuration plug-ins and
 * - a second with priority
 *   \ref com.aworx.lib.config.Configuration.PRIO_PROTECTED_VALUES "PRIO_PROTECTED_VALUES" (highest priority),
 *   which can be used protect configuration values from external change.
 *
 * This class in addition acts as the parent of class
 * \ref com.aworx.lib.config.IniFile "IniFile" and potentially other (custom) classes.
 * For this reason, it divides the set of variables into sections (according to the category),
 * allows comment strings for variables and sections, and virtualizes the some key methods to
 * allow descendants to take specific actions.
 *
 * This class offers important internal fields and types for public access (bauhaus code style).
 * However, in standard cases, only the interface methods of this class should be used.
 **************************************************************************************************/
public class InMemoryPlugin extends ConfigurationPlugin
{
    // #############################################################################################
    // inner classes
    // #############################################################################################

        /** ****************************************************************************************
         * A configuration sections' entry
         ******************************************************************************************/
        public class Entry
        {
            public AString             name         = new AString();             ///< The name of the section.
            public AString             comments     = new AString();             ///< The comments of the section.
            public char                delim        = '\0';                      ///< The delimiter if splitting to multiple lines is wanted.
            public int                 FormatHints  = 0;                         ///< The format hints of the variable
            public String              FormatAttrAlignment= null;                ///< The format attribute alignment hint of the variable
            public ArrayList<AString>  values       = new ArrayList<AString>(); ///< The list of values of the entry of the section.

            /**
             * Constructs an Entry
             * @param name    The name of the section.
             */
            public Entry( CharSequence name )
            {
                this.name._( name );
            }

            /**
             * Virtual method that copies the values of an entry to the given \p{variable}.
             *
             * @param parent    The plug-in we belong to.
             * @param variable  The variable to fill with our values.
             */
            public void toVariable( InMemoryPlugin parent, Variable variable )
            {
                com.aworx.lib.ALIB_DBG.ASSERT( delim != '\0' || values.size() <= 1);
                if ( delim != '\0' )
                    variable.delim= delim;
                if ( FormatHints != 0 )
                    variable.formatHints= FormatHints;
                if ( FormatAttrAlignment != null )
                    variable.formatAttrAlignment= FormatAttrAlignment;

                variable.comments._()._( comments );
                for( AString val : values )
                    variable.add( val );
            }

            /**
             * Virtual method that copies the values of the given \p{variable} to us.
             *
             * @param parent    The plug-in we belong to.
             * @param variable  The variable to fill with our values.
             */
            public void fromVariable( InMemoryPlugin parent,  Variable variable )
            {
                // copy attributes
                delim=               variable.delim;
                FormatHints=         variable.formatHints;
                FormatAttrAlignment= variable.formatAttrAlignment;

                if ( comments.isEmpty() )    // do not overwrite comments
                    comments._( variable.comments );

                // adjust size of value array
                int varSize= variable.size();
                int valSize= values.size();
                while (valSize < varSize )
                {
                    values.add( new AString() );
                    valSize++;
                }
                while (valSize > varSize )
                    values.remove( --valSize );

                // copy
                for ( int i= 0; i< variable.size(); i++ )
                    values.get(i)._()._( variable.getString(i) );
            }
        }

        /** ****************************************************************************************
         * A configuration section
         ******************************************************************************************/
        public class Section
        {
            public AString          name     = new AString();             ///< The name of the section.
            public AString          comments = new AString();             ///< The comments of the section.
            public ArrayList<Entry> entries  = new ArrayList<Entry>();    ///< The list of variables of the section.

            protected Variable      tmpVar   = new Variable();            ///< A reusable variable.
            protected Tokenizer     tmpTknzr = new Tokenizer();           ///< A reusable tokenizer.

            /** Constructs a Section
             * @param name    The name of the section.
             *                (AString compatible type expected.)
            */
            public              Section( CharSequence name )         { this.name._( name ); }

            /**
             * Searches an entry with the given name. The search is performed case insensitive
             * @param name      The name of the variable to be searched.
             * @param create    Denotes if an entry should be created if not found.
             * @return The variable if found, else \c null.
             */
            @SuppressWarnings ("hiding")
            public Entry     getEntry    ( CharSequence name, boolean create )
            {
                if ( name.length() == 0 )
                {
                    com.aworx.lib.ALIB_DBG.WARNING( "Empty variable name given" );
                    return null;
                }

                for ( Entry entry : entries )
                    if ( entry.name.equals( name, Case.IGNORE ) )
                        return entry;

                if( ! create )
                    return null;

                // not found?
                Entry entry= createEntry( name );
                entries.add( entry );
                return entry;
            }

            /**
             * Deletes an entry (if exists)
             * @param name      The name of the variable to be searched.
             * @return \c true if the entry was found and deleted, \c false otherwise.
             */
            @SuppressWarnings ("hiding")
            public boolean    deleteEntry    ( CharSequence name  )
            {
                for ( int idx= 0; idx < entries.size(); ++idx )
                {
                    Entry entry= entries.get( idx );
                    if ( entry.name.equals( name, Case.IGNORE ) )
                    {
                        entries.remove( idx );
                        return true;
                    }
                }
                return false;
            }

            /** ************************************************************************************
             * Virtual method to create an Entry.
             * (Provided to allow descendant classes to created extended versions of an entry. See
             * also \ref com.aworx.lib.config.InMemoryPlugin.createSection "InMemoryPlugin.createSection".)
             *
             * @param  name The name of the entry.
             * @return An object of type \ref Entry "InMemoryPlugin.Entry".
             **************************************************************************************/
            protected Entry  createEntry( @SuppressWarnings ("hiding") CharSequence name )
            {
                return new Entry( name );
            }

        }

    // #############################################################################################
    // Public fields
    // #############################################################################################

        /** The list of sections. */
        public ArrayList<Section>               sections                     = new ArrayList<Section>();

    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
        /** ****************************************************************************************
         * Constructor.
         ******************************************************************************************/
        public InMemoryPlugin()
        {
            reset();
        }

    // #############################################################################################
    // ConfigurationPlugin interface implementation
    // #############################################################################################
        /** ****************************************************************************************
         * Searches the variable in our storage.
         *
         * @param variable     The variable to retrieve.
         * @param searchOnly   If \c true, the variable is not read. Defaults to \c false.
         * @return \c true if variable was found, \c false if not.
         ******************************************************************************************/
        @Override
        public boolean  load( Variable variable, boolean searchOnly )
        {
            com.aworx.lib.ALIB_DBG.ASSERT_WARNING( variable.name.isNotEmpty(), "Empty name given" );

            Section    section;
            Entry      entry=  null;
            if (    (section= searchSection   ( variable.category    ) ) != null
                 && (entry=   section.getEntry( variable.name, false ) ) != null
                 && !searchOnly                                                   )
            {
                entry.toVariable( this, variable );
            }

            return entry != null;
        }

        /** ****************************************************************************************
         * Creates or replaces existing variable in our storage.
         *
         * @param variable  The variable to retrieve.
         * @return \c true if the variable was written, \c false if not. The latter might only
         *         happen if the variable given was illegal, e.g. empty name.
         ******************************************************************************************/
        @Override
        public boolean  store( Variable variable )
        {
            Section     section= searchOrCreateSection( variable.category, null );

            if ( variable.size() > 0 )
            {
                Entry entry= section.getEntry( variable.name, true );
                entry.fromVariable( this, variable );
                return true;
            }

            return  section.deleteEntry( variable.name );
        }

    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         * Clears all configuration data and adds a fresh anonymous section
         ******************************************************************************************/
        public void            reset()
        {
            sections.clear();
            sections.add( createSection( "" ) );
        }


        /** ****************************************************************************************
         * Searches the \ref com.aworx.lib.config.InMemoryPlugin.Section "Section" with the given name.
         *
         * @param name      The name of the section to be retrieved.
         * @return Returns the section if it was found, \c null otherwise.
         ******************************************************************************************/
        public Section  searchSection( CharSequence name )
        {
            if ( name == null || name.length() == 0 )
                return sections.get( 0 );

            for ( Section s : sections )
                if ( s.name.equals( name, Case.IGNORE ) )
                    return s;
            return null;
        }

        /** ****************************************************************************************
         * Searches the \ref com.aworx.lib.config.InMemoryPlugin.Section "Section" with the given name.
         * If the section was not found, it is created.
         * If the section is found and has no comments, then the provided comments are appended.
         * @param name      The name of the section to be retrieved.
         * @param comments  The comment lines for the section, in the case the section is not
         *                  found. If this is null, no section comments are created.
         * @return Returns the section if it was found or created. null otherwise.
         ******************************************************************************************/
        public Section  searchOrCreateSection( CharSequence name, AString comments )
        {
            // search
            Section s= searchSection( name );
            if ( s == null )
                sections.add( s= createSection( name ) );

            if ( s.comments.isEmpty() )
                s.comments._( comments );

            return s;
        }

    // #############################################################################################
    // Internals
    // #############################################################################################

        /** ****************************************************************************************
         * Virtual method to create a section.
         * (Provided to allow descendant classes to created extended versions of an entry.)
         * @param  name The name of the section
         * @return An object of type \ref Section "InMemoryPlugin.Section".
         ******************************************************************************************/
        protected Section  createSection( CharSequence name )
        {
            return new InMemoryPlugin.Section( name );
        }

} // class




