// #################################################################################################
//  cs.aworx.lox.tools.json - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#if ( !ALOX_NO_XML )

using System;
using System.Collections.Generic;
using System.Linq;

using System.Collections;
using System.Collections.ObjectModel;
using System.Dynamic;
using System.Web.Script.Serialization;

/** ************************************************************************************************
 * This namespace just contents a single class which provides a quick and easy reader for "unknown"
 * JSON formatted data.
 **************************************************************************************************/
namespace cs.aworx.lox.tools.json
{
    /** ********************************************************************************************
     * Small class which provides a quick and easy reader for "unknown" JSON formatted data.
     * (Copied from a web forum, I would not have been able to get this syntax * done :-P ).
     * The output is basically is a nested dictionary and can nicely be passed into LogTools.Instance()
     * method for reviewing the JSON data contents.
     **********************************************************************************************/
    public sealed class DynamicJSONDeserializer : JavaScriptConverter
{
    // #############################################################################################
    // Interface
    // #############################################################################################

    /** ********************************************************************************************
     * Static method to deserialize a JSON data from a string. Returns a nested dictionary containing
     * the JSON data.
     * @param json  The JSON data as a String.
     *
     * @return  A dictionary representing the values
     **********************************************************************************************/
    public static IDictionary<string, object> FromString( String json )
    {
        var serializer= new JavaScriptSerializer();
        serializer.RegisterConverters(new[] { new DynamicJSONDeserializer() });
        return  ( (DynamicJsonObject) serializer.Deserialize( json, typeof(object) ) ).Dictionary;
    }

    /** ********************************************************************************************
     * See class JavaScriptConverter for more info
     * @param dictionary   See parent class.
     * @param type         See parent class.
     * @param serializer   See parent class.
     * @return  see parent class
     **********************************************************************************************/
    public override object Deserialize(IDictionary<string, object> dictionary, Type type, JavaScriptSerializer serializer)
    {
        if (dictionary == null)
            throw new ArgumentNullException("dictionary");

        return type == typeof(object) ? new DynamicJsonObject(dictionary) : null;
    }

    /** ********************************************************************************************
     * See class JavaScriptConverter for more info
     * @param obj           See parent class.
     * @param serializer    See parent class.
     * @return  see parent class
     **********************************************************************************************/
    public override IDictionary<string, object> Serialize(object obj, JavaScriptSerializer serializer)
    {
        throw new NotImplementedException();
    }

    /** ********************************************************************************************
     * See class JavaScriptConverter for more info
     * @param dictionary    See parent class.
     * @param type          See parent class.
     * @param serializer    See parent class.
     * @return  see parent class
     **********************************************************************************************/
    public override IEnumerable<Type> SupportedTypes
    {
        get { return new ReadOnlyCollection<Type>(new List<Type>(new[] { typeof(object) })); }
    }


    // #############################################################################################
    // inner class DynamicJsonObject
    // #############################################################################################

    /** ********************************************************************************************
     * Inner class that implements the DynamicObject
     **********************************************************************************************/
    private sealed class DynamicJsonObject : DynamicObject
    {
        /** the recursive dictionary to store the data in.  */
        internal readonly    IDictionary<string, object>        Dictionary;

        /** ****************************************************************************************
         * Constructor.
         * <exception cref="ArgumentNullException  Thrown when one or more required arguments are
         *                                          null. </exception>
         * @param dictionary     the recursive dictionary to store the data in.
         ******************************************************************************************/
        public DynamicJsonObject(IDictionary<string, object> dictionary)
        {
            if (dictionary == null)
                throw new ArgumentNullException("dictionary");
            Dictionary= dictionary;
        }



        /** ****************************************************************************************
         * See class DynamicObject for more info
         * @param binder   See parent class.
         * @param result   See parent class.
         * @return  See parent class
         ******************************************************************************************/
        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            if (!Dictionary.TryGetValue(binder.Name, out result))
            {
                // return null to avoid exception.  caller can check for null this way...
                result = null;
                return true;
            }

            result = WrapResultObject(result);
            return true;
        }

        /** ****************************************************************************************
         * See class DynamicObject for more info
         * @param binder    See parent class.
         * @param indexes   See parent class.
         * @param result    See parent class.
         * @return  See parent class
         ******************************************************************************************/
        public override bool TryGetIndex(GetIndexBinder binder, object[] indexes, out object result)
        {
            if (indexes.Length == 1 && indexes[0] != null)
            {
                if (!Dictionary.TryGetValue(indexes[0].ToString(), out result))
                {
                    // return null to avoid exception.  caller can check for null this way...
                    result = null;
                    return true;
                }

                result = WrapResultObject(result);
                return true;
            }

            return base.TryGetIndex(binder, indexes, out result);
        }

        /** ****************************************************************************************
         * See class DynamicObject for more info
         * @param result  See parent class.
         * @return  See parent class
         ******************************************************************************************/
        private static object WrapResultObject(object result)
        {
            var dictionary = result as IDictionary<string, object>;
            if (dictionary != null)
                return new DynamicJsonObject(dictionary);

            var arrayList = result as ArrayList;
            if (arrayList != null && arrayList.Count > 0)
            {
                // This should be made different: manually cast this and remove Linq dependency
                return arrayList[0] is IDictionary<string, object>
                    ? new List<object>(arrayList.Cast<IDictionary<string, object>>().Select(x => new DynamicJsonObject(x)))
                    : new List<object>(arrayList.Cast<object>());
            }

            return result;
        }
    }

} // class
} // namespace
#endif // ( !ALOX_NO_XML )
