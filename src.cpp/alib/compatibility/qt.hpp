// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
//
//  Legal Notice:
//    This is an optional extension header to provide compatiblility between ALib and
//    the QT class library.
//    All information about QT is found under https://www.qt.io
//    ALib otherwise does not use or rely on QT.
//    The use of QT is bound to the QT license restrictions.
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_COMPATIBILITY_QT)
    #error "Header already included"
#endif

#ifndef HPP_ALIB_COMPATIBILITY_QT
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_COMPATIBILITY_QT 1
#endif


#include <QString>
#include <QVector>

// #################################################################################################
// ALib String / QT string classes compatibility support
// #################################################################################################

namespace aworx {
namespace           lib {
namespace                   strings {


    // #############################################################################################
    // QLatin1String
    // #############################################################################################

    /** ********************************************************************************************
     * Specialization of TMP 'function' (struct)
     * \ref aworx::lib::strings::ToStringDefined "ToStringDefined" for type \b QLatin1String.
     * See \ref aworx::lib::strings::ToStringDefined "ToStringDefined" for more information.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     **********************************************************************************************/
    template<>   struct               ToStringDefined<const QLatin1String&>   : public std::true_type {};

    /** ********************************************************************************************
     * Specialization of template function
     * \ref aworx::lib::strings::ToString "ToString" for type \b QLatin1String.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  src The source string to take the buffer from.
     * @return The value of  <em>src.data()</em>.
     **********************************************************************************************/
    template<>   inline   const char* ToString        <const QLatin1String&>( const QLatin1String& src )
    {
        return  (const char*) src.data();
    }

    /** ********************************************************************************************
     * Specialization of template function
     * \ref aworx::lib::strings::ToString "ToString" for type \b QLatin1String.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  src The source string to take the length from.
     * @return The length of \p src.
     **********************************************************************************************/
    template<>   inline   int         ToString        <const QLatin1String&>( const QLatin1String& src )
    {
        return (int) src.size();
    }

    /** ********************************************************************************************
     * Specialization of TMP 'function' (struct)
     * \ref aworx::lib::strings::IsApplicable "IsApplicable" for type \b QLatin1String.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     **********************************************************************************************/
    template<>   struct               IsApplicable<const QLatin1String&>   : public std::true_type {};

    /** ********************************************************************************************
     * Specialization of template method
     * \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type \b QLatin1String.
     * See \ref aworx::lib::strings::ApplyTo "ApplyTo" for general information.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  target The AString to append \p src to.
     * @param  src    The source string to take the buffer from.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>   inline   int         ApplyTo <const QLatin1String&>( AString& target, const QLatin1String& src )
    {
        int len= (int) src.size();
        target.Append( (const char*) src.data(), len );
        return len;
    }

    /** ********************************************************************************************
     * Specialization of (optional) non-checking version of template method
     * \ref aworx::lib::strings::ApplyTo_NC "ApplyTo_NC" for applicable type \b QLatin1String.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  target The AString to append \p src to.
     * @param  src    The source string to take the buffer from.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>   inline   int         ApplyTo_NC <const QLatin1String&>( AString& target, const QLatin1String& src )
    {
        int len= (int) src.size();
        target.Append<false>( (const char*) src.data(), len );
        return len;
    }

    // #############################################################################################
    // QByteArray
    // #############################################################################################

    /** ********************************************************************************************
     * Specialization of TMP 'function' (struct)
     * \ref aworx::lib::strings::ToStringDefined "ToStringDefined" for type \b QByteArray.
     * See \ref aworx::lib::strings::ToStringDefined "ToStringDefined" for more information.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     **********************************************************************************************/
    template<>   struct               ToStringDefined<const QByteArray&>   : public std::true_type {};

    /** ********************************************************************************************
     * Specialization of template function
     * \ref aworx::lib::strings::ToString "ToString" for type \b QByteArray.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  src The source string to take the buffer from.
     * @return The value of  <em>src.data()</em>.
     **********************************************************************************************/
    template<>   inline   const char* ToString        <const QByteArray&>( const QByteArray& src )
    {
        return  (const char*) src.data();
    }

    /** ********************************************************************************************
     * Specialization of template function
     * \ref aworx::lib::strings::ToString "ToString" for type \b QByteArray.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  src The source string to take the length from.
     * @return The length of \p src.
     **********************************************************************************************/
    template<>   inline   int         ToString        <const QByteArray&>( const QByteArray& src )
    {
        return (int) src.length();
    }

    /** ********************************************************************************************
     * Specialization of TMP 'function' (struct)
     * \ref aworx::lib::strings::IsApplicable "IsApplicable" for type \b QByteArray.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     **********************************************************************************************/
    template<>   struct               IsApplicable<const QByteArray&>   : public std::true_type {};

    /** ********************************************************************************************
     * Specialization of template method
     * \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type \b QByteArray.
     * See \ref aworx::lib::strings::ApplyTo "ApplyTo" for general information.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  target The AString to append \p src to.
     * @param  src    The source string to take the buffer from.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>   inline   int         ApplyTo <const QByteArray&>( AString& target, const QByteArray& src )
    {
        int len= (int) src.length();
        target.Append( (const char*) src.data(), len );
        return len;
    }

    /** ********************************************************************************************
     * Specialization of (optional) non-checking version of template method
     *\ref aworx::lib::strings::ApplyTo_NC "ApplyTo_NC" for applicable type \b QByteArray.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  target The AString to append \p src to.
     * @param  src    The source string to take the buffer from.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>   inline   int         ApplyTo_NC <const QByteArray&>( AString& target, const QByteArray& src )
    {
        int len= (int) src.length();
        target.Append<false>( (const char*) src.data(), len );
        return len;
    }


    // #############################################################################################
    // QChar
    // #############################################################################################

    /** ********************************************************************************************
     * Specialization of TMP 'function' (struct)
     * \ref aworx::lib::strings::IsApplicable "IsApplicable" for type \b QChar.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     **********************************************************************************************/
    template<>   struct               IsApplicable<const QChar&>   : public std::true_type {};

    /** ********************************************************************************************
     * Specialization of template method
     * \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type \b QChar.
     * See \ref aworx::lib::strings::ApplyTo "ApplyTo" for general information.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  target The AString to append \p src to.
     * @param  src    The source string to take the buffer from.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>   inline   int         ApplyTo <const QChar&>( AString& target, const QChar& src )
    {
        target._( (wchar_t) src.unicode() );
        return 1;
    }

    /** ********************************************************************************************
     * Specialization of (optional) non-checking version of template method
     * \ref aworx::lib::strings::ApplyTo_NC "ApplyTo_NC" for applicable type \b QChar.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  target The AString to append \p src to.
     * @param  src    The source string to take the buffer from.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>   inline   int         ApplyTo_NC <const QChar&>( AString& target, const QChar& src )
    {
        target._<false>( src.toLatin1() );
        return 1;
    }


    // #############################################################################################
    // QVector<uint>
    // #############################################################################################

    /** ********************************************************************************************
     * Specialization of TMP 'function' (struct)
     * \ref aworx::lib::strings::IsApplicable "IsApplicable" for type \b QVector<uint>.<br>
     * It is expected that the data in the QVector contains UCS4 data, e.g. generated with
     * method \b %QString::toUcs4.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     **********************************************************************************************/
    template<>   struct               IsApplicable<const QVector<uint>&>   : public std::true_type {};

    /** ********************************************************************************************
     * Specialization of template method
     * \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type \b QVector<uint>.
     * It is expected that the data in the QVector contains UCS4 data, e.g. generated with
     * method \b %QString::toUcs4.<br>
     * See \ref aworx::lib::strings::ApplyTo "ApplyTo" for general information.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param  target The AString to append \p src to.
     * @param  src    The source string to take the buffer from.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>   inline   int         ApplyTo <const QVector<uint>&>( AString& target, const QVector<uint>& src )
    {
        target.Append( (wchar_t*) src.data(), src.length() );
        return 0; // avoid null check (already done)
    }


    // #############################################################################################
    // QString
    // #############################################################################################

    /** ********************************************************************************************
     * Specialization of TMP 'function' (struct)
     * \ref aworx::lib::strings::IsApplicable "IsApplicable" for type \b QString.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     **********************************************************************************************/
    template<>   struct               IsApplicable<const QString&>   : public std::true_type {};

    /** ********************************************************************************************
     * Specialization of template method
     * \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type \b QString.
     * See \ref aworx::lib::strings::ApplyTo "ApplyTo" for general information.
     *
     * <b>Information On ALib And QT %String Compatibility:</b><br>
     * ALib string classes are designed to support 3rd-party string types in a non-intrusive
     * fashion. Template meta programming in two areas made this possible:
     * - Implicit conversion of external strings to class
     *   \ref aworx::lib::strings::String "aworx::String", which allows to pass 3rd party strings to
     *   method accepting parameters of type <b>const %aworx::String&</b> without conversion.
     * - \e Application of arbitrary types to objects of class
     *   \ref aworx::lib::strings::AString "aworx::AString". Here, the term \e "application" most
     *   means concatenating a string representation of an object to the \b AString object.
     * (This is all documented in reference manual of namespace \ref aworx::lib::strings.)
     *
     * %String classes of the [QT library](https://www.qt.io) are
     * supported trough header file <em>"alib/compatibility/qt.hpp"</em>.
     *
     * <b>Implicit Conversion:</b><br>
     * Unfortunately, objects of class \b %QString can not be implicitly converted (embedded) in
     * thin and lightweight class \ref aworx::lib::strings::String "aworx::String". The reason
     * for this is, that ALib strings are single byte strings, while \b QString represent
     * (two byte) unicode strings. Therefore, template struct
     * \ref aworx::lib::strings::ToStringDefined "ToStringDefined" and method
     * \ref aworx::lib::strings::ToString "ToString" can not be implemented for class \b QString
     * and objects of this class can not be simply passed to methods accepting parameters of type
     * <b>const %aworx::String&</b>.
     *
     * The way out is the use of classes \b QByteArray and \b QLatin1String. For these QT classes,
     * an implicit conversion exists and this way objects of these types are implicitly converted
     * to \b %aworx::String types. Class \b %QString provides methods to convert to these classes.
     * Passing a \b QString object to a method expecting a <b>const %aworx::String&</b> can be
     * done a follows
     *
     *      MyMethodExpectingALibString( myQString.toLocal8Bit() );
     *      MyMethodExpectingALibString( myQString.toUtf8()      );
     *      MyMethodExpectingALibString( myQString.toLatin1()    );
     *
     * \note
     *   The encoding of strings represented by ALib strings is user defined. Therefore, it
     *   is up to the user to decide which of the above conversion methods of \b QString
     *   is to be used. In most cases, method \b toLocal8Bit should be the right choice. Also,
     *   ALib strings uses the current locale to convert characters of type wchar_t (or arrays of them)
     *   when \e applying to class \b %AString as well.
     *
     * The obvious drawback of this approach is that a conversion has to take place and
     * that this conversion implies a temporary allocation of heap memory for the data stored
     * in the (stack-allocated) \b QByteArray object.
     *
     * <b>Appending QT Strings To %AString Objects (ApplyTo):</b><br>
     * Template method \b %ApplyTo is partial implemented for the following QT types:
     * - <b>ApplyTo<const QString&></b> (this method)
     * - \ref aworx::lib::strings::ApplyTo<const QChar&>(AString&,const QChar&)                 "ApplyTo<const QChar&>"
     * - \ref aworx::lib::strings::ApplyTo<const QLatin1String&>(AString&,const QLatin1String&) "ApplyTo<const QLatin1String&>"
     * - \ref aworx::lib::strings::ApplyTo<const QByteArray&>(AString&,const QByteArray&)       "ApplyTo<const QByteArray&>"
     * - \ref aworx::lib::strings::ApplyTo<const QVector<uint>&>(AString&,const QVector<uint>&) "ApplyTo<const QVector<uint>&>"
     *
     * @param  target The AString to append \p src to.
     * @param  src    The source string to take the buffer from.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>  inline   int         ApplyTo <const QString&>( AString& target, const QString& src )
    {
        int len= (int) src.length();
        wchar_t localBuffer[1024];
        wchar_t* wcBuffer= localBuffer;
        if ( len > 1024 )
            wcBuffer= new wchar_t[len];

        src.toWCharArray( wcBuffer );
        target.Append( wcBuffer, len );

        if ( wcBuffer != localBuffer )
            delete[] wcBuffer;

        return 0; // avoid null check (already done)
    }

    /** ********************************************************************************************
     * Copies or appends a region of a given \ref aworx::lib::strings::String "String" into a QString.
     * The region is adjusted to the length of the %String.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param as            The \ref aworx::lib::strings::String "String" to convert into a QString.
     * @param target        A result QString to copy the specified region into.
     * @param regionStart   The start index of the region to be copied.
     * @param regionLength  The maximum length of the region to be copied.
     *                      Defaults to CString::MaxLen.
     * @param targetData    If \c CurrentData::Keep, the target \c QString is not cleared before
     *                      the result is written. Defaults to \c CurrentData::Clear.
     *
     * @return The (modified) QString& result that was provided (for concatenation of calls).
     **********************************************************************************************/
    inline
    QString& ToQString( const String&      as,
                        QString&           target,
                        int                regionStart,
                        int                regionLength    = CString::MaxLen,
                        enums::CurrentData targetData      = enums::CurrentData::Clear )
    {
        if ( targetData == enums::CurrentData::Clear )
            target.clear();

        // adjust range, if empty return empty string
        if ( as.AdjustRegion( regionStart, regionLength ) )
            return target;

        // copy our buffer into target
        target.fromUtf8( as.Buffer() + regionStart, regionLength - regionStart );
        return  target;
    }

    /** ********************************************************************************************
     * Copies a region of a given \ref aworx::lib::strings::String "String" into a QString which
     * is created.
     * The region is adjusted to the length of the %String.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param as            The \ref aworx::lib::strings::String "String" to convert into a QString.
     * @param regionStart   The start index of the region in this to create the QString from.
     * @param regionLength  The maximum length of the region to be copied.
     *                      Defaults to CString::MaxLen.
     *
     * @return A string that represents the specified sub region of this object.
     **********************************************************************************************/
    inline
    QString  ToQString( const String& as, int regionStart, int regionLength= CString::MaxLen )
    {
        QString retval;
        ToQString( as, retval, regionStart, regionLength, enums::CurrentData::Keep );
        return retval;
    }

    /** ********************************************************************************************
     * Copies the contents of a given \ref aworx::lib::strings::String "String" into the given QString.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param as            The \ref aworx::lib::strings::String "String" to convert into a QString.
     * @return A QString that represents this object.
     **********************************************************************************************/
    inline
    QString  ToQString( const String& as )
    {
        return ToQString( as, 0, as.Length() );
    }


    /** ********************************************************************************************
     * Copies the contents of a given \ref aworx::lib::strings::String "String" into the given QString.<br>
     * For more information about using QT strings with ALib, see
     * \ref aworx::lib::strings::ApplyTo<const QString&>(AString&,const QString&) "ApplyTo<const QString&>"
     *
     * @param as           The \ref aworx::lib::strings::String "String" to convert into a QString.
     * @param target       A target QString to copy the contents of this %String into.
     * @param targetData   If \c CurrentData::Keep, parameter \p target is not cleared before
     *                     the result is written. Defaults to \c CurrentData::Clear.
     * @return The (modified) result that was provided (for concatenation of calls).
     **********************************************************************************************/
    inline
    QString& ToQString( const String&       as,
                        QString&            target,
                        enums::CurrentData  targetData = enums::CurrentData::Clear )
    {
        return ToQString( as, target, 0, as.Length(), targetData );
    }
}}}


#endif // HPP_ALIB_COMPATIBILITY_QT
