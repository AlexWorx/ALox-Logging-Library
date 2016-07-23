// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.IO;
using System.Collections.Generic;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;

namespace cs.aworx.lib.config  {


/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugin, which holds
 * configuration variables in memory. Instances of this class are used to create two plug-ins
 * within standard configurations:
 * - One with priority
 *   \ref cs::aworx::lib::config::Configuration::PrioDefault "PrioDefault" (low priority)
 *   to store default values not found in other configuration plug-ins and
 * - a second with priority
 *   \ref cs::aworx::lib::config::Configuration::PrioProtected "PrioProtected" (highest priority),
 *   which can be used protect configuration values from external change.
 *
 * This class in addition acts as the parent of class
 * \ref cs::aworx::lib::config::IniFile "IniFile" and potentially other (custom) classes.
 * For this reason, it divides the set of variables into sections (according to the category),
 * allows comment strings for variables and sections, and virtualizes the some key methods to
 * allow descendants to take specific actions.
 *
 * This class offers important internal fields and types for public access (bauhaus code style).
 * However, in standard cases, only the interface methods of this class should be used.
 **************************************************************************************************/
public class InMemoryPlugin : ConfigurationPlugin
{
    // #############################################################################################
    // inner classes
    // #############################################################################################

        /** ****************************************************************************************
         * A configuration sections' entry
         ******************************************************************************************/
        public class Entry
        {
            public AString             Name               = new AString();       ///< The name of the section.
            public AString             Comments           = new AString();       ///< The comments of the section.
            public char                Delim              = '\0';                ///< The delimiter if splitting to multiple lines is wanted.
            public List<AString>       Values             = new List<AString>(); ///< The list of values of the entry of the section.
            public Variable.FormatHint FormatHints        = 0;                   ///< The format hints of the variable
            public String              FormatAttrAlignment= null;                ///< The format attribute alignment hint of the variable

            /**
             * Constructs an Entry
             * @param name    The name of the section.
             */
            public Entry( Object name )
            {
                Name._( name );
            }

            /**
             * Virtual method that copies the values of an entry to the given \p variable.
             *
             * @param parent    The plug-in we belong to.
             * @param variable  The variable to fill with our values.
             */
            public virtual void ToVariable( InMemoryPlugin parent, Variable variable )
            {
                ALIB.ASSERT( Delim != '\0' || Values.Count <= 1);
                if ( Delim != '\0' )
                    variable.Delim= Delim;
                if ( FormatHints != 0 )
                    variable.FormatHints= FormatHints;
                if ( FormatAttrAlignment != null )
                    variable.FormatAttrAlignment= FormatAttrAlignment;

                variable.Comments._()._( Comments );
                foreach( AString val in Values )
                    variable.AddString( val );
            }

            /**
             * Virtual method that copies the values of the given \p variable to us.
             *
             * @param parent    The plug-in we belong to.
             * @param variable  The variable to fill with our values.
             */
            public virtual void FromVariable( InMemoryPlugin parent, Variable variable )
            {
                // copy attributes
                Delim=               variable.Delim;
                FormatHints=         variable.FormatHints;
                FormatAttrAlignment= variable.FormatAttrAlignment;

                if ( Comments.IsEmpty() )    // do not overwrite comments
                    Comments._( variable.Comments );

                // adjust size of value array
                int varSize= variable.Size();
                int valSize= Values.Count;
                while (valSize < varSize )
                {
                    Values.Add( new AString() );
                    valSize++;
                }
                while (valSize > varSize )
                    Values.RemoveAt( --valSize );

                // copy
                for ( int i= 0; i< variable.Size(); i++ )
                    Values[i]._()._( variable.GetString(i) );
            }

        };

        /** ****************************************************************************************
         * A configuration section
         ******************************************************************************************/
        public class Section
        {
            public AString      Name     = new AString();        ///< The name of the section.
            public AString      Comments = new AString();        ///< The comments of the section.
            public List<Entry>  Entries  = new List<Entry>();    ///< The list of variables of the section.
            protected Variable  tmpVar   = new Variable();       ///< A reusable variable.
            protected Tokenizer tmpTknzr = new Tokenizer();      ///< A reusable tokenizer.


            /**
             * Constructs a Section
             * @param name    The name of the section.
             *                (AString compatible type expected.)
            */
            public              Section( Object name )
            {
                Name._( name );
            }

            /**
             * Searches an entry with the given name. The search is performed case insensitive
             * @param name      The name of the variable to be searched.
             * @param create    Denotes if an entry should be created if not found.
             * @return The variable if found, else \c null.
             */
            public Entry     GetEntry    ( Object name, bool create )
            {
                Entry entry= Entries.Find( variable => variable.Name.Equals( name, Case.Ignore ) );

                if( entry == null && create )
                    Entries.Add( entry= createEntry( name ) );

                return entry;
            }

            /**
             * Deletes an entry (if exists)
             * @param name      The name of the variable to be searched.
             * @return \c true if the entry was found and deleted, \c false otherwise.
             */
            public bool    DeleteEntry    ( Object name  )
            {
                for ( int idx= 0; idx < Entries.Count; ++idx )
                {
                    Entry entry= Entries[idx];
                    if ( entry.Name.Equals( name, Case.Ignore ) )
                    {
                        Entries.RemoveAt( idx );
                        return true;
                    }
                }
                return false;
            }

            /** ************************************************************************************
             * Virtual method to create an Entry.
             * (Provided to allow descendant classes to created extended versions of an entry. See
             * also \ref cs::aworx::lib::config::InMemoryPlugin::createSection "InMemoryPlugin.createSection".)
             *
             * @param  name The name of the entry.
             * @return An object of type \ref Entry "InMemoryPlugin.Entry".
             **************************************************************************************/
            protected virtual Entry  createEntry( Object name )
            {
                return new Entry( name );
            }
        };

    // #############################################################################################
    // Public fields
    // #############################################################################################

        /** The list of sections. */
        public List<Section>                    Sections                     = new List<Section>();

    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
        /** ****************************************************************************************
         * Constructor.
         ******************************************************************************************/
        public InMemoryPlugin()
        {
            Reset();
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
        public override bool  Load( Variable variable, bool searchOnly= false )
        {
            ALIB.ASSERT_WARNING( variable.Name.IsNotEmpty(), "Empty name given" );

            Section    section;
            Entry      entry=  null;
            if (    (section= SearchSection    ( variable.Category     ) ) != null
                 && (entry=   section.GetEntry ( variable.Name, false  ) ) != null
                 && !searchOnly                                                     )
            {
                entry.ToVariable( this, variable );
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
        public override bool  Store( Variable variable )
        {
            Section     section= SearchOrCreateSection( variable.Category, null );
            if ( variable.Size() > 0 )
            {
                Entry entry= section.GetEntry( variable.Name, true );
                entry.FromVariable( this, variable );
                return true;
            }

            return  section.DeleteEntry( variable.Name );
        }

    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         * Clears all configuration data and adds a fresh anonymous section
         ******************************************************************************************/
        public virtual void            Reset()
        {
            Sections.Clear();
            Sections.Add( createSection("") );
        }


        /** ****************************************************************************************
         * Searches the \ref cs::aworx::lib::config::InMemoryPlugin::Section "Section" with the given name.
         *
         * @param name      The name of the section to be retrieved.
         * @return Returns the section if it was found, \c null otherwise.
         ******************************************************************************************/
        public Section  SearchSection( Object name )
        {
            // detected nulled ALib strings
            if ( AString.IsNull ( name )  )
                return Sections[0];

            return Sections.Find( x => ( name == null && x.Name.IsEmpty()) ||  x.Name.Equals( name, Case.Ignore ) );
        }

        /** ****************************************************************************************
         * Searches the \ref cs::aworx::lib::config::InMemoryPlugin::Section "Section" with the given name.
         * If the section was not found, it is created.
         * If the section is found and has no comments, then the provided comments are appended.
         * @param name      The name of the section to be retrieved.
         * @param comments  The comment lines for the section, in the case the section is not
         *                  found. If this is null, no section is created.
         * @return Returns the section if it was found or created. \c null otherwise.
         ******************************************************************************************/
        public Section  SearchOrCreateSection( Object name, AString comments )
        {
            Section s= SearchSection( name );
            if ( s == null )
                Sections.Add( s= createSection( name ) );

            if ( s.Comments.IsEmpty() )
                s.Comments._( comments );

            return s;
        }

    // #############################################################################################
    // Internals
    // #############################################################################################

        /** ****************************************************************************************
         * Virtual method to create a section.
         * (Provided to allow descendant classes to created extended versions of an entry.)
         * @param  name The name of the section
         * @return An object of type \ref Section "InMemoryPlugIn.Section".
         ******************************************************************************************/
        protected virtual Section  createSection( Object name )
        {
            return new InMemoryPlugin.Section( name );
        }

} // class

}// namespace

