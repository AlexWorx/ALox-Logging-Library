// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:	DynamicJSONDeserializer
//  File:	DynamicJSONDeserializer.cs							Namespace:  com.aworx.lox.tools.json
// #################################################################################################

#if ( !ALOX_NO_XML ) 

using System;
using System.Collections.Generic;
using System.Linq;

using System.Collections;
using System.Collections.ObjectModel;
using System.Dynamic;
using System.Web.Script.Serialization;

/** ***********************************************************************************************
 * <summary> 
 * This namespace just contents a single class which provides a quick and easy reader for "unknown" 
 * JSON formatted data. (Copied from a web forum, I would not have been able to get this syntax
 * done :-P )
 *  </summary>
 **************************************************************************************************/
namespace com.aworx.lox.tools.json 
{
	/** ***********************************************************************************************
	 * <summary> 
	 * Small class which provides a quick and easy reader for "unknown" JSON formatted data. 
	 * (Copied from a web forum, I would not have been able to get this syntax * done :-P ).
	 * The output is basically is a nested dictionary and can nicely be passed into LogTools.Instance()
	 * method for reviewing the JSON data contents.
	 *  </summary>
	 **************************************************************************************************/
	public sealed class DynamicJSONDeserializer : JavaScriptConverter
{
	// #################################################################################################
	// Interface
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary> 
	 * 	Static method to deserialize a JSON data from a string. Returns a nested dictionary containing
	 * 	the JSON data.
	 * <param name="json"> The JSON data as a String. </param>
	 * </summary>
	 * <returns> A dictionary representing the values </returns>
	 **************************************************************************************************/
	public static IDictionary<string, object> FromString( String json )
	{
		var serializer= new JavaScriptSerializer();
		serializer.RegisterConverters(new[] { new DynamicJSONDeserializer() });
		DynamicJsonObject obj=  (DynamicJsonObject) serializer.Deserialize( json, typeof(object) );

		return obj.Dictionary;
	}

	/** ***********************************************************************************************
	 * <summary> See class JavaScriptConverter for more info </summary>
	 * <param name="dictionary">	see parent class. </param>
	 * <param name="type">			see parent class. </param>
	 * <param name="serializer">	see parent class. </param>
	 * <returns> see parent class </returns>
	 **************************************************************************************************/
	public override object Deserialize(IDictionary<string, object> dictionary, Type type, JavaScriptSerializer serializer)
	{
		if (dictionary == null)
			throw new ArgumentNullException("dictionary");

		return type == typeof(object) ? new DynamicJsonObject(dictionary) : null;
	}

	/** ***********************************************************************************************
	 * <summary> See class JavaScriptConverter for more info </summary>
	 * <param name="obj">			see parent class. </param>
	 * <param name="serializer">	see parent class. </param>
	 * <returns> see parent class </returns>
	 **************************************************************************************************/
	public override IDictionary<string, object> Serialize(object obj, JavaScriptSerializer serializer)
	{
		throw new NotImplementedException();
	}

	/** ***********************************************************************************************
	 * <summary> See class JavaScriptConverter for more info </summary>
	 * <param name="dictionary">	see parent class. </param>
	 * <param name="type">			see parent class. </param>
	 * <param name="serializer">	see parent class. </param>
	 * <returns> see parent class </returns>
	 **************************************************************************************************/
	public override IEnumerable<Type> SupportedTypes
	{
		get { return new ReadOnlyCollection<Type>(new List<Type>(new[] { typeof(object) })); }
	}


	// #################################################################################################
	// inner class DynamicJsonObject
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary> Inner class that implements the DynamicObject </summary>
	 **************************************************************************************************/
	private sealed class DynamicJsonObject : DynamicObject
	{
		/** <summary>	the recursive dictionary to store the data in. </summary> */
		internal readonly	IDictionary<string, object>		Dictionary;

		/** ***********************************************************************************************
		 * <summary>	Constructor. </summary>
		 * <exception cref="ArgumentNullException"> Thrown when one or more required arguments are null. </exception>
		 * <param name="dictionary">	the recursive dictionary to store the data in. </param>
		 **************************************************************************************************/
		public DynamicJsonObject(IDictionary<string, object> dictionary)
		{
			if (dictionary == null)
				throw new ArgumentNullException("dictionary");
			Dictionary= dictionary;
		}



		/** ***********************************************************************************************
		 * <summary> See class DynamicObject for more info </summary>
		 * <param name="binder">	see parent class. </param>
		 * <param name="result">		see parent class. </param>
		 * <returns> see parent class </returns>
		 **************************************************************************************************/
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

		/** ***********************************************************************************************
		 * <summary> See class DynamicObject for more info </summary>
		 * <param name="binder">	see parent class. </param>
		 * <param name="indexes">	see parent class. </param>
		 * <param name="result">	see parent class. </param>
		 * <returns> see parent class </returns>
		 **************************************************************************************************/
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

		/** ***********************************************************************************************
		 * <summary> See class DynamicObject for more info </summary>
		 * <param name="result"> see parent class. </param>
		 * <returns> see parent class </returns>
		 **************************************************************************************************/
		private static object WrapResultObject(object result)
		{
			var dictionary = result as IDictionary<string, object>;
			if (dictionary != null)
				return new DynamicJsonObject(dictionary);

			var arrayList = result as ArrayList;
			if (arrayList != null && arrayList.Count > 0)
			{
				// TODO: manually cast this and remove Linq dependency
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