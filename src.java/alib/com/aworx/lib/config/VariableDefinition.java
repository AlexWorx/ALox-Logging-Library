// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import com.aworx.lib.strings.AString;

/** ************************************************************************************************
 * A data record used to define an
 * \ref com::aworx::lib::config::Variable "ALib Configuration Variable".
 * While variables can also defined by setting their attributes individually, it is recommended to
 * define all external configuration variables in a central place, using statically or dynamically
 * allocated objects of this type.<br>
 * Objects of class \b %Variable can be constructed and existing objects can be reused by invoking
 * \ref com::aworx::lib::config::Variable::define "Variable.define". Both construction and
 * re-definition support to pass objects of this type.
 *
 * All fields (except #delim) support placeholders \c "%1", \c "%2" ... \c "%N", which are
 * replaced with the constructor of class \b %Variable and method
 * \ref com::aworx::lib::config::Variable::define "Variable.define".
 * This allows to define a series of variables whose category, name, description and value is
 * dependent on runtime information.
 *
 * Besides the use for passing parameters into objects of type Variable, this
 * class provides no further logic.
 **************************************************************************************************/
public class VariableDefinition
{
    /**
     * Simple constructor copying values
     * @param categoryFallback     Value for field #categoryFallback (treated as reference, value not copied)
     * @param category             Value for field #category
     * @param name                 Value for field #name
     * @param defaultValue         Value for field #defaultValue
     * @param delim                Value for field #delim
     * @param formatAttrAlignment  Value for field #formatAttrAlignment
     * @param formatHints          Value for field #formatHints
     * @param comments             Value for field #comments
     */
    public VariableDefinition(AString categoryFallback, String category, String name, String defaultValue, char delim,
            String formatAttrAlignment, int formatHints, String comments)
    {
        this.categoryFallback=    categoryFallback;
        this.category=            category;
        this.name=                name;
        this.defaultValue=        defaultValue;
        this.delim=               delim;
        this.formatAttrAlignment= formatAttrAlignment;
        this.formatHints=         formatHints;
        this.comments=            comments;
    }

    /**
     * Reference to a category string which is used as fallback if field #category is nulled.
     * This is useful as usually most variables share one general application specific
     * category. With the combination of fields #categoryFallback and #category,
     * the user (of a library) is be entitled to change single variables
     * or all at once. In the latter case, field #category is left nulled, while this field
     * is set to a global default value (which also can be changed, therefore a pointer).
     */
    public AString categoryFallback;

    /** The category for this value. May be left nulled in which case field
     *  #categoryFallback is applied. */
    public String  category;

    /** The name of the variable. */
    public String  name;

    /**
     * The default value. If this is \c null, no variable will be created with method
     * \ref com::aworx::lib::config::Configuration::load "Configuration.load".
     * \note
     *   The field is ignored when using the plug-in interface
     *   \ref com::aworx::lib::config::ConfigurationPlugin::load "ConfigurationPlugin.load".
     */
    public String  defaultValue;

    /** The (preferred) delimiter of values when represented in external strings.  */
    public char    delim;

    /** If set attributes written in multi-lines are vertically aligned by this character or
     *  string. Use cases are "=", ":" or "->".<br> Used by
     *  \ref com::aworx::lib::config::IniFile "IniFile" and potentially by custom plug-ins. */
    public String  formatAttrAlignment;

    /** Hints for formatting textual configuration files. (Used by class
        \ref com::aworx::lib::config::IniFile "IniFile" and potentially by custom plug-ins.*/
    public int     formatHints;

    /** Comments for the variable. Some plug-ins allow to store comments along with the
     *  variable (e.g. class \ref com::aworx::lib::config::IniFile).*/
    public String  comments;
}
