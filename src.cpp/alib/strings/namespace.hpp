// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_AWORX_LIB_ALIB) || defined(HPP_AWORX_LIB_STRINGS_ASTRING)
    #error "include alib/alib.hpp instead of this header"
#endif


// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_LIB_STRINGS_NAMESPACE
#define HPP_AWORX_LIB_STRINGS_NAMESPACE 1


// AS.hpp is already included, prior to ALIB class declaration


// #################################################################################################
// Include Terminatable, Literal
// #################################################################################################
#include "alib/strings/asterminatable.hpp"
#include "alib/strings/asliteral.hpp"


// #################################################################################################
// Namespace ASLiteral Singletons: ASNull, ASEmpty
// #################################################################################################

namespace aworx { namespace lib { namespace strings {

        /**
         * The system depended new line character code(s).
         */
        #ifdef __unix__

            constexpr static       ASLiteral<1>   NewLine { "\n" };

        #elif defined(_WIN32)

            constexpr static       ASLiteral<2>   NewLine { "\r\n" };

        #else
            #warning "Warning: Unknown Platform"
        #endif

        /**
         * Characters that are usually ignored or trimmed.
         */
        constexpr     static      ASLiteral<4>    DefaultWhitespaces { " \n\r\t" };
}}}


// #################################################################################################
// ALib does not work without strings. So, we include them
// #################################################################################################
#include "alib/strings/asalloc.hpp"
#include "alib/strings/asprealloc.hpp"
#include "alib/strings/applyto.hpp"
#include "alib/strings/applyformat.hpp"

namespace aworx { namespace  lib {

/** ************************************************************************************************

# Introduction # {#alib_namespace_strings_intro}

This namespace of ALib provides classes that operate on character strings
(following \ref aworx::lib "the principle design goals of ALib").
As the given C#/Java StringBuilder/Buffer classes are either "sealed" and/or do not provide
direct access to the internal buffer, to avoid conversion to new immutable strings in certain
situations, ALib implements its own string class. More complex
functions, like extended formatting operations are not supported and remain the domain of the
language specific class libraries.

In contrast to the Java and C# versions of ALib, which  merely provide a central string class named
\b %AString along with \b %Substring, things became a little more complex in ALib for C++.
The following feature overview illustrate the reasons for this:

- Implicit conversion of external, user defined string types when passing data into ALib. This
  includes of-course compatibility with <em>std::string</em> and <em>cstrings</em> (<em>char*</em>),
  but also 3rd party types like e.g. \e QString.
- Conversion/construction through template meta programming, with minimum (almost no)
  runtime overhead.
- Support for user defined types that get 'applied' to strings. (Mostly concatenated, but also
  more complex string algorithms can be implemented without changing ALib sources.)
- Stack allocated strings that avoid overhead of dynamic memory allocation, but in case of
  unexpected capacity demands, automatically switch to a dynamic data model.
- Fast processing of C++ string literals and other string types whose length is known at compile
  time (no strlen(), for short types no memcpy() ).
- Zero terminated and non-zero-terminated strings with mostly implicit termination.
- 'Nullable' state that avoids nullptr checks and enables to work with references everywhere.
- Conversion to and from wide character strings.
- 'Non-checking' versions of many string methods are available to avoid redundant parameter checks.
- Built-in debugging mechanics.
- But still: as much as possible/reasonable compatibility with strings in ALib for JAVA/C#.


# Classes overview # {#alib_namespace_strings_class_overview}
To understand the rationale behind introducing different string types, it is easiest to
go quickly through them one by one. The classes are:
- \ref aworx::lib::strings::AS "AS"
- \ref aworx::lib::strings::ASTerminatable "ASTerminatable"
- \ref aworx::lib::strings::ASAlloc "ASAlloc"
- \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc"
- \ref aworx::lib::strings::ASLiteral "ASLiteral"
- \ref aworx::lib::strings::ASSubstring "ASSubstring"

As usual with class libraries, to avoid conflicts even when residing in own namespaces these
classes have a quite unique name. The good news is, that in namespace #aworx, \e shortcuts
and new names are defined. The translation is as follows:

<table border="1" >
    <tr>
         <th>   Type            </th>
         <th>   <b>Shortcut</b> </th>
    </tr>

    <tr>   <td>aworx::lib::strings::AS              </td>    <td>aworx::String        </td>  </tr>
    <tr>   <td>aworx::lib::strings::ASTerminatable  </td>    <td>aworx::TString       </td>  </tr>
    <tr>   <td>aworx::lib::strings::ASAlloc         </td>    <td>aworx::AString      </td>  </tr>
    <tr>   <td>aworx::lib::strings::ASLiteral       </td>    <td>aworx::StringLiteral </td>  </tr>
    <tr>   <td>\ref aworx::lib::strings::ASPreAlloc "aworx::lib::strings::ASPreAlloc<N>"  </td>    <td>String16, String32,...,String4K  </td>  </tr>

</table>

\attention
  In this namespace description, where the family of string classes of ALib is introduced, the
  \e 'original' names are used most times. However, in most of other documentation the \e 'synonyms'
  are used. Often, there are even links that in their "display name" use the synonym but in fact link to
  the documentation of the class like in the following link sample:
  \ref aworx::lib::strings::AS "String".

This might on the first sight seem a little confusing, however once this is understood it
makes the code very readable. And, as explained in
\ref CPP_AWORX_NS_SHORTCUTS "Type Shortcuts in the aworx Namespace", it does not introduce
any conflicts even if this way very general and readable names are available.

## Class AS ##  {#alib_namespace_strings_class_overview_as}
The most basic class is
\ref aworx::lib::strings::AS "AS" (aka \b aworx::String). It just contains a character pointer and the length of the
data that should be represented by this object. Class \b %AS does not allocate any string data and
with the exclamation of assigning something (completely) different, does not allow to change the
pointer to its buffer or its length.

Objects of type \b %AS are implicitly constructed or assigned to from other string types like
- C++ string literals
- <em>char* / wchar_t*</em> pointers
- <em>std::string</em> objects
- derived \b %AS types or
- external, user defined types.

The use cases of the class concentrate on two scenarios:

<em>1. Using class AS for String Constants:</em><p>
Often, some constant string data is needed. For example, let's look at class ALib and it's
field \ref aworx::lib::ALIB::ConfigCategoryName "ALIB::ConfigCategoryName". This field is used
by ALib when getting configuration parameters, e.g. from environment variables.
By default, this field is set to "ALIB", but an application might want to change it to
something like "MYAPP". By having this field of type \c %AS, just any string type can be
assigned to it. The user of ALib must not explicitly convert '\e his' string type to ALib types
but just using the assignment operator \e '='.
Furthermore, in advantage to type <em>const char*</em>, along with the pointer, the length of
the string is stored. This gives a good performance improvement, as e.g. no \e strlen() call
has to be made prior to copying this string to some other place.<br>
\attention Same as with a use of <em>const char*</em>, when assigning a string to an \c AS object, it has
           to be made sure that this string is kept intact during the life-time of the target.

<em>2. Using 'const AS&' as Method Parameter Type:</em><p>
All ALib interface methods that need some string input use a constant reference to \c %AS
as parameter type (or to derived type \c %ASTerminatable, discussed later).
Again, the using code does not need to care about conversion. References
or pointers to any sort of string classes might be passed.
In this case lifetime is deemed to be rather short, local and stack allocated. With
having C++ 11 move constructor and assignment in place, no destructor, no virtual methods and just
two members, objects of type \c %AS are a very lightweight and perfect candidates to be
constructed implicitly for method parameter passing.<br>
As a sample, see constructor of class
\ref aworx::lib::system::Directory::Directory(const String&) "Directory". It is declared as:
\code{.cpp}
Directory( const aworx::String& path );
\endcode
With this declaration, it is possible to invoke that constructor passing using just any type of strings:
\snippet "DOX_ALIB_TOAS.cpp"     DOX_ALIB_AS_DIRECTORY

\note ALib methods that continue to need the string data after their execution will create a copy
      of it. In other words, they will never expect that the buffer received in a parameter of type \c %AS
      still exists after the method exits.


### Binding user types to ALib strings ###
With a little one-time effort of implementing two small template methods, also user defined
string types (or types from other 3rd party library) can be made compatible easily. Due to
template meta programming, variations of these types, like pointers or references, const or
non-const, etc. will be accepted with minimum (mostly no) runtime impact, because TMP hook
in at compile time.<br>
For more information on how to make ALib support user defined types see partially specialized
template function
\ref aworx::lib::strings::ToAS "ToAS".<br>

\anchor alib_namespace_strings_nullable
### Nullable Strings ###
Another important note is the fact that class \b %AS are 'nullable'. This term means here, that
when they got constructed with no value, with <em>nullptr</em>, with other \e nulled ALib strings,
etc., this state is detectable and is different from representing an empty string of zero length.
This is very important for lean and clean user code.

Derived mutable class \b %ASAlloc (which is discussed below in more detail) inherits this ability
See the sample exposed in \ref alib_namespace_strings_astring_nullable "Nullable AStrings"
to get a better understanding of this concept.

### Not Zero-Terminated ###
Strings represented by this class may be zero terminated. E.g. when constructed from a string literal
they definitely are (as C++ string literals are zero terminated an not writable). However,
class \b %AS does not count on that and treats its content as not zero-terminated. Therefore, the
interface methods provided implement those standard string operations that are allowed
(or can be implemented efficiently) on non-zero-terminated strings.

For further information about this type, note the reference documentation
\ref aworx::lib::strings::AS "class AS".

### Lightweight and Volatile ###
Due to the minimum footprint (a pointer to the string buffer and an integer value for
the strings' length), move construction and assignment is compiler defined and very fast.
Even passing objects as value has a very limited (and sometimes no) performance impact.


## Class ASTerminatable ##  {#alib_namespace_strings_class_overview_asterminatable}
A first specialization of class
\ref aworx::lib::strings::AS "AS" is class
\ref aworx::lib::strings::ASTerminatable "ASTerminatable" which is representing strings that - other
than the name might indicate - either
- <b>are</b> terminated with a trailing '\0' character, or
- <b>can be</b>  terminated by writing a trailing '\0' into the
  \ref aworx::lib::strings::AS::buffer "buffer" at position
  \ref aworx::lib::strings::AS::length "length".

This is important to understand. For example, a C++ string literal like <em>"Hello"</em> is
zero terminated. If it was not, it could not be terminated explicitly because write access is not
allowed.

The important design decision made here is that the constructing objects this class is still
implicit. This is sometimes a little dangerous, but runtime checks are provided
to detect illegal construction with data that either is not terminated or can't be terminated.
(For details, refer to
\ref aworx::lib::strings::ASTerminatable "ASTerminatable"'s reference documentation.)

The interface of class \b %ASTerminatable extends the set of methods provided by parent class \b %AS,
by those standard string operations that can be implemented more efficiently on
zero-terminated strings. This includes search operations for other strings and for
single characters taken from a choice of characters.


## Class ASAlloc ##  {#alib_namespace_strings_class_overview_astring}
Class
\ref aworx::lib::strings::ASAlloc "ASAlloc" which specializes class
\ref aworx::lib::strings::ASTerminatable "ASTerminatable" disposes of an allocation mechanism
to allow the creation and manipulation of strings. Therefore, this is the central class to
assemble strings at runtime. Whenever append operations exceed the existing buffer, the contents
is copied to a new, bigger buffer and the old one is disposed.

Conceptually, the difference to parent classes \b %AS and \b %ASTerminatable is that
those <em>represent</em> (constant) string objects, while this class might be considered of
<em>being</em> a non-constant string.

\anchor alib_namespace_strings_class_overview_astring_construction
### Construction ###
Class \b %ASAlloc hides all parent constructors and offers re-implementations of these
that <b>copy</b> the data that is passed. Consequently - as this copying is not considered a lightweight
operation - all constructors are explicit. If, for example, a function expects a constant
\b %ASAlloc reference, such \b %ASAlloc has to be created explicitly before or inside the function
invocation. Consequently the assignment operator is not applicable with initializations as well.
The following code will not compile:
\verbatim
ASAlloc as=  "This will not compile";
\endverbatim
 * Instead, explicit creation has to be made, as shown here:
\verbatim
ASAlloc as("This will compile");

// or alternatively
ASAlloc as;
as= "This will compile";
\endverbatim


With constructor
\ref aworx::lib::strings::ASAlloc::ASAlloc (const T&) "ASAlloc(const T&)", class \b %ASAlloc
provides the same the flexibility like parent class
\ref aworx::lib::strings::AS "AS" in respect to the ability to take just anything that is a
string, including 'external' user defined types as an initial value.

Copy constructor, move constructor and move assignment are well defined, which allows \b %ASAlloc
objects to be used (as efficiently as possible) e.g. in std::vector instantiations.


### Buffer Management ###
As mentioned before, class \b %ASAlloc provides logic to manage its own buffer.
Furthermore, it is also possible to have objects of class \b %ASAlloc work on 'external' buffers, hence
buffers that are not bound to the \b %ASAllocs' life-cycle. For details on this see method
\ref aworx::lib::strings::ASAlloc::SetBuffer(char*,int,int, enums::Responsibility) "ASAlloc::SetBuffer". Class
\ref aworx::lib::strings::ASPreAlloc "ASPreAlloc", which is discussed below, makes use
of this feature and provides the possibility to have local (stack based) allocations of strings.


### Appending and Applying Objects ###
Similar to parent class
\ref aworx::lib::strings::AS "AS" for construction, class \b %ASAlloc provides a template meta
programming based method to "apply" any type of object to an \b %ASAlloc after its construction.
For many types, e.g. string types or integer and floating point types, the term '<em>applying</em>'
is means nothing else than '<em>appending</em>'. If a string gets applied to an object of type
\b %ASAlloc, the string is appended. However, as almost any type, including 'external', user defined types
might be applied and such application is performed in a specialized template method, the operation
associated with the <em>application</em> of an object of a certain type is not limited to appending data.

As an example, the concept of \e 'applying' is used to add 'fields' to an \b AString.
To achieve this, a special \e 'applicable' type named
\ref aworx::lib::strings::Format::Field "Format::Field" is defined. Appending a field
is done as follows:
\snippet "DOX_ALIB_APPLYTO.cpp"     DOX_ALIB_APPLYTO_FIELD
which produces the following output:
\snippet "DOX_ALIB_APPLYTO_FIELD.txt"     OUTPUT


For more information on how to make \b %ASAlloc support user defined applicable types see method
\ref aworx::lib::strings::ASAlloc::Apply "ASAlloc::Apply" and partially specialized template function
\ref aworx::lib::strings::ApplyTo( ASAlloc& target, const T src ) "ApplyTo".


## Class ASPreAlloc ##  {#alib_namespace_strings_class_overview_asprealoc}

Template class
\ref aworx::lib::strings::ASPreAlloc "ASPreAlloc<int TCapacity>", derived from class \b %ASAlloc
uses an internal member of type <em>char[TCapacity]</em> with templated size to store the string data.
The huge benefit lies in performance: The impact of frequent allocation of '<em>free memory</em>'
(aka <em>heap allocation</em>) is often underestimated by developers. Therefore, for local
string operations class \b %ASPreAlloc and its convenient type definitions #String16, #String32 ... #String1K, #String2K, #String4K.
should be considered as a fast alternative for class \b %ASAlloc.

### Exceeding the Buffer Capacity ###
Although the internal buffer size is fixed at compile time and hence can not be expanded, a user
of the class must not fear an assertion from '<em>buffer overflows</em>'. If the internal buffer capacity
is exceeded, a regular allocated buffer from the <em>free memory</em> (aka '\e heap') will be
allocated. The slight disadvantage then is, that the memory of the internal buffer is (of-course)
not freed.

In debug compilations of ALib, already parent class
\ref aworx::lib::strings::ASAlloc "ASAlloc" provides warning mechanism that enables the easy
detection of such probably unwanted replacements of external buffers
(in this case the '\e member-allocated' buffer).
Using macro \ref ALIB_WARN_ONCE_PER_INSTANCE_DECL an <em>ALib Warning</em> will be issued when a buffer
is replaced. There are two scenarios how a this mechanism might be used during development:
- If the buffer should never be replaced, the capacity of an %ASPreAlloc has to be increased
  step by step when the warning is issued, until the member-buffer is huge enough.
- If it is OK, if the buffer is replaced every once in a while (because there special
  situations with higher capacity needs occur, but are relatively seldom) then, the warning
  should be switched off for this specific object, as it is explained in
  \ref aworx::lib::strings::ASAlloc::ReplaceExternalBuffer "ASAlloc::ReplaceExternalBuffer".

\note Again, all warnings are effective only with debug compilations of ALib.

### Aliases For Frequently Used Sizes ###
For commonly used sizes, some convenient alias names are defined. See aliases
#String16, #String32, #String64 ... #String1K, #String2K, #String4K.

### Implicit construction ###
While class \b %ASAlloc, as
\ref alib_namespace_strings_class_overview_astring_construction "noted above", does not provide
implicit construction, this class re-implements
the common constructors of \b %ASAlloc and exposes them as <em>implicit</em>.
The rationale here is that although the data is copied (which might not be a very lightweight task),
still the performance impact is far less compared to constructing an \b %ASAlloc and
it is taken into account that an \b %ASPreAlloc is created without explicit exposure of this creation. <p>
The following method, as a sample, takes three different ALib string types as parameters:
\snippet "DOX_ALIB_STRINGS.cpp"     DOX_ALIB_STRINGS_AS_PARAMETERS_1
The following code will \e not compile:
\snippet "DOX_ALIB_STRINGS.cpp"     DOX_ALIB_STRINGS_AS_PARAMETERS_2
Class ASAlloc has to be explicitly created, the others don't:
\snippet "DOX_ALIB_STRINGS.cpp"     DOX_ALIB_STRINGS_AS_PARAMETERS_3

In addition, besides having implicit construction, the default assign operator is defined as well.
This allows to use objects of this type as class members that are initialized within the class
declaration as shown here:
\snippet "DOX_ALIB_STRINGS.cpp"     DOX_ALIB_STRINGS_ASPREALLOC_MEMBER
Such members are not allowed to be initialized in the declaration if their type is \b %ASAlloc.

### Move Constructor and Assignment ###
Class \b %ASPreAlloc provides a '<em>move constructor</em>' but no '<em>move assignment operator</em>'.
See the \ref aworx::lib::strings::ASPreAlloc "classes reference documentation" for more information.



## Class ASSubstring ##  {#alib_namespace_strings_class_overview_substring}
Class \ref aworx::lib::strings::ASSubstring "ASSubstring" is derived directly from class \b %AS.
Conceptually, the difference to its parent class is that it is not constant. It was discussed
earlier, that objects of type \b %AS, once constructed, will never change the pointer to the buffer
or its length. Objects of class \b %ASSubstring are entitled to do so. In general, the string they
represent is a portion of another string and if they change, this change normally means
either shrinking or they are just changing completely. They are especially useful to parsing string
data.
Some Parsing of strings (in its probably simplest form) making use of class \b %ASSubstring is provided
with class
\ref aworx::lib::strings::Tokenizer "Tokenizer", which is also defined in this namespace.

\note Speaking of \b %ASSubstring being '<em>non constant</em>' refers to their own members
\e buffer and \e length. This does not mean that the contents of the buffer is manipulatable.


## Class ASLiteral ##  {#alib_namespace_strings_class_overview_asliteral}
Other than this classes' name suggests, template class
\ref aworx::lib::strings::ASLiteral "ASLiteral" represent strings whose length is fixed and
known at compile time. Often, objects of this type are constructed from C++ string literals, like
in the following samples:
\snippet "DOX_ALIB_STRINGS.cpp"     DOX_ALIB_STRINGS_LITERAL_1

But it is also allowed to construct them from other character arrays, even writable ones, like here:
\snippet "DOX_ALIB_STRINGS.cpp"     DOX_ALIB_STRINGS_LITERAL_2

As the class specializes
\ref aworx::lib::strings::ASTerminatable "ASTerminatable", with the second sample, the user of
the class has to make sure that the string represented by objects of this type is zero terminated.

Using class \b %ASLiteral improves the performance of certain operations. For example appending
(applying) objects of this type to objects of class \b %ASAlloc will not result in a copy loop but
will simply inline the correct number of copy operations into the object code (at least for the
smaller sizes which are typically used).

\note
  With ALib strings, this performance improvement is also given when using C++ string literals
  directly. But, when C++ string literals get passed to methods, usually such passing will convert
  them to <em>const char*</em> type (unless template methods are in place). From this moment on, the
  information about the length is lost. Therefore, class \b %ASLiteral should be used whenever
  C++ literals are shared between different code segments to avoid converting them to
  <em>const char*</em> or \b %AS type.
  <p>
\note
  It is possible to enable 'external', user defined types to act as string literals as well.
  This is a rather unlikely scenario, but might happen the software that uses ALib defines string
  types with a constant length, other than <em>char[N]</em>. In this case, optionally and solely
  for a (potentially small) performance gain, these types can get adopted to ALib by implementing
  class \ref aworx::lib::strings::TMPLiteral "TMPLiteral". This process is not further documented
  or demonstrated by a sample. Interested audience should consult the source code of ALib for
  doing it. The mechanism used is similar to what is used with template functions
  \ref aworx::lib::strings::ToAS "ToAS" and
  \ref aworx::lib::strings::ApplyTo "ApplyTo".





# 'Non-Checking' Methods of ALib String Classes# {#alib_namespace_strings_nonchecking}
Many of the methods found in the different string classes of ALib are template methods with
a boolean template parameter named <em>TCheck</em>. This template parameter is defaulted with
the value \c true which is sort of 'hiding' it in normal code. Consider the following
piece of code:
\snippet "DOX_ALIB_STRINGS.cpp"     DOX_ALIB_STRINGS_NONCHECKING_1

The implementation of method
\ref aworx::lib::strings::ASSubstring::Consume  "Substring::Consume(int)" by default checks if
object \e line is big enough to cut the given number of characters from the front.
Obviously this check is redundant here, because \b Consume is invoked only if \b IndexOfAs had
found the string <em>"\<start\>"</em>. To avoid the redundant check, we invoke the non-checking version of
method \b Consume by providing template parameter \p TCheck with value \c false.
\snippet "DOX_ALIB_STRINGS.cpp"     DOX_ALIB_STRINGS_NONCHECKING_2

\note
  In this simple sample, especially as these methods are inlined, the compiler might detect
  already that the check is redundant and would remove it from the code. However, there
  are many occasions where the compiler is lacking the information and the possibility to detect
  such redundancy.

In the C# and Java versions of ALib, where such template methods are not available,
still some non-checking methods are provided, but less than in the C++ implementation. In these
languages, these methods exist twice with the same name, the non-checking one with
postfix <em>_NC</em> appended.

The following general rules apply for all non-checking methods:
- String parameters are not checked for being nullptr.
- Index, size, length, region start/end and other parameters are not checked to be correct
- If parameters are incorrect, the result of the methods is undefined
  and an exception/assertion may be raised.
- Append methods that in their original version would set a \e nulled \b %ASAlloc to non \e nulled
  state in the case that an empty string or string region is appended, are not confirming
  to this  principle in their non-checking version.<br>
  In other words, \e nulled strings keep being \e nulled if empty strings are appended.
- In the Java and C# versions of ALib, the hash value of an \b %ASAlloc object keeps
  being cached when invoking an <em>_NC</em> method. This may lead to wrong behavior, e.g. when
  an \b %AString object is used as a key of a hash table. To avoid errors, within a context that
  makes use of an \b %AStrings' hash value, before each hash code retrieval
  (C#: <em>GetHashCode()</em>, Java: <em>hashCode()</em>),
  it has to be certified that at least one of the methods manipulating the object has
  to be a non <em>_NC</em> method.

Apart from the previous points, the behavior and result of invoking a non-checking version
of a method is the same as of invoking the original version. The only difference is in a higher
execution performance.



# Compatibility with External Libraries# {#alib_namespace_strings_compat}
ALib provides compatibility extensions with different class libraries. Currently the following
extensions are provided:
## Standard C++ Library ##
- Trough header file <em>"alib/compatibility/std_string.hpp"</em>
    - Implements template method
      \ref aworx::lib::strings::ToAS "ToAS" to allow (implicit) conversion of objects of type
      \e std::string to type aworx::String.
    - Implements template method
      \ref aworx::lib::strings::ApplyTo "ApplyTo" to allow the concatenation of objects of type
      \e std::string to type aworx::AString.
    - Implements namespace function
      \ref aworx::lib::strings::ToStdString (with various overloads) to convert an object of
      type aworx::String to type \e std::string.

<p>
- Trough header file <em>"alib/compatibility/std_iostream.hpp"</em>
    - Provides \e applicable class
      \ref aworx::lib::strings::ReadLineFromIStream "ReadLineFromIStream" and corresponding
      implementation of
      \ref aworx::lib::strings::ApplyTo "ApplyTo" to allow reading lines of text from
      a \e std::istream into an object of type aworx::AString.

    - Provides namespace functions
      \ref operator>>(std::istream&, AString&) and
      \ref operator>>(std::istream*, AString&) which are using aforementioned applicable
      class \b ReadLineFromIStream with default parameters to read a line from
      a \e std::istream into an object of type aworx::AString.

    - Provides namespace functions
      \ref operator<<(std::ostream& os, const String& as) and
      \ref operator<<(std::ostream* os, const String& as) to write an object of type aworx::String
      into a \e std::ostream.

\note Support for other Libraries to come...

# Debugging ALib String Classes # {#alib_namespace_strings_debugging}
In some situations during the development using ALib string classes, some additional debug
checking is helpful. Among such situations are:
- development of types derived from ALib string types
- specializing template functions
  \ref aworx::lib::strings::ToAS "ToAS" or
  \ref aworx::lib::strings::ApplyTo "ApplyTo" to add support for user defined string types or
  formatting operations to class \b %AString.
- external manipulation of \b %AString string data
- provision of external data buffers to class \b %AString

In these and similar situations, it is advised to using the compiler symbol
\ref ALIB_DEBUG_STRINGS_ON. This enables internal consistency checks with almost any method ALib
string invoked. By default this is disabled, as it generates a quite huge drop of runtime
performance. When string debugging is enabled, macro ALIB_STRING_DBG_CHK can be used to check
the consistancy of ALib string classes. Furthermore, macro #ALIB_STRING_DBG_UNTERMINATE <em>has
to</em> be used when changing the length of a terminatable string without using method
\ref aworx::lib::strings::ASAlloc::SetLength "ASAlloc::SetLength<false>" (e.g. in custom, derived
classes).
***************************************************************************************************/
namespace                   strings {


}}} // namespace aworx::lib::strings


#endif // HPP_AWORX_LIB_STRINGS_NAMESPACE



