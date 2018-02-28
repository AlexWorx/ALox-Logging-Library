// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"



using namespace std;


#if ALIB_MODULE_BOXING && ALIB_MODULE_STRINGS && ALIB_FEAT_BOXING_FTYPES
#   if !defined (HPP_ALIB_LANG_ENUM_ENUM)
#       include "alib/lang/enum.hpp"
#   endif
#endif

using namespace aworx::lib::lang;


namespace aworx { namespace lib {

// The singleton of the library class located in namespace aworx::lib.
lang::Lang LANG;

// #################################################################################################
// Replacement method for ALib Essential Reports
// #################################################################################################
#if ALIB_MODULE_ALL &&  ALIB_DEBUG
namespace debug {
    /**
     * This method is installed with
     * \ref aworx::lib::debug::DbgSimpleALibMsg_Plugin in method
     * \ref aworx::lib::lang::Lang::init "Lang::init".
     *
     * The message strings are simply passed to the default
     * \ref aworx::lib::lang::Report "Report".
     * This way, the essential assert, error and message macros are using the \b %ALib report system
     * in the moment that the complete %ALib library is in place (instead of only one of the
     * libraries' modules.
     *
     * @param file    Information about the scope of invocation.
     * @param line    Information about the scope of invocation.
     * @param method  Information about the scope of invocation.
     * @param type    The type of message. See \ref aworx::lib::lang::Report::Message "Report::Message".
     * @param qtyMsgs The number of messages in \p msgs.
     * @param msgs    A list of strings (this is all that the essential versions of \b %ALib reporting
     *                macros provide).
     */
    void ALib_Dbg_Report_Plugin(const char* file, int line, const char* method, int type, int qtyMsgs, const char** msgs);
    void ALib_Dbg_Report_Plugin(const char* file, int line, const char* method, int type, int qtyMsgs, const char** msgs)
    {
        lang::Report::Message message( file,line,method, type, msgs[0] );
        for (int i= 1; i< qtyMsgs; ++i )
            message.Add( msgs[i] );
        lang::Report::GetDefault().DoReport( message );
    }
} // namespace aworx::lib[::debug]
#endif

namespace lang {


// #################################################################################################
// init/terminationCleanup
// #################################################################################################

void Lang::init( Phases phase )
{
    if( phase == Phases::resourceset )
    {
        #if ALIB_MODULE_ALL &&  ALIB_DEBUG
            debug::DbgSimpleALibMsg_Plugin= debug::ALib_Dbg_Report_Plugin;
        #endif

        Res->AddBulk( ResourceCategory.ToCString(),

        // aworx::lib::lang::Exceptions
        "ExceptionsPrefix" , "lang::" ,
        "ExceptionsPostfix", ""         ,
        "Exceptions",
            "1"  ","    "ErrorWritingReport"  ","  "EX1" ,

         "EX1", "Error writing ALib report.",

        // enums
//! [DOX_ALIB_LANG_ENUMS_PARSABLE_MULTIPLE]
"Bool",         "0,False,1,"
                "1,True,1,"
                "0,0,1,"
                "1,1,1,"
                "0,No,1,"
                "1,Yes,1,"
                "0,On,2,"
                "1,Off,2,"
                "0,-,1,"
                "1,Ok,2",
//! [DOX_ALIB_LANG_ENUMS_PARSABLE_MULTIPLE]

//! [DOX_ALIB_LANG_ENUMS_PARSABLE_3]
"Case",         "0,Sensitive,1,"
                "1,Ignore,1",
//! [DOX_ALIB_LANG_ENUMS_PARSABLE_3]

//! [DOX_ALIB_LANG_ENUMS_PARSABLE_4]
"ContainerOp",  "0,Insert,1,"
                "1,Remove,1,"
                "3,GetCreate,4,"
                "2,Get,1,"
                "4,Create,1",
//! [DOX_ALIB_LANG_ENUMS_PARSABLE_4]

//        catMap.emplace( "Switch0",          "0"  ","  "Off"                ","  "2" );
//        catMap.emplace( "Switch1",          "1"  ","  "On"                 ","  "2" );



        "Switch",           "0"  ","  "Off"                ","  "2" ","
                            "1"  ","  "On"                 ","  "2"     ,

        "Alignment",        "0"  ","  "Left"               ","  "1" ","
                            "1"  ","  "Right"              ","  "1" ","
                            "2"  ","  "Center"             ","  "1"     ,

        "SortOrder",        "0"  ","  "Ascending"          ","  "1" ","
                            "1"  ","  "Descending"         ","  "1"     ,

        "Inclusion",        "0"  ","  "Include"            ","  "1" ","
                            "1"  ","  "Exclude"            ","  "1"     ,

        "Reach",            "0"  ","  "Global"             ","  "1" ","
                            "1"  ","  "Local"              ","  "1"     ,

        "CurrentData",      "0"  ","  "Keep"               ","  "1" ","
                            "1"  ","  "Clear"              ","  "1"     ,

        "SourceData",       "0"  ","  "Copy"               ","  "1" ","
                            "1"  ","  "Move"               ","  "1"     ,

        "Safeness",         "0"  ","  "Safe"               ","  "1" ","
                            "1"  ","  "Unsafe"             ","  "1"     ,

        "Responsibility",   "0"  ","  "KeepWithSender"     ","  "1" ","
                            "1"  ","  "Transfer"           ","  "1"     ,

        "Timezone",         "0"  ","  "Local"              ","  "1" ","
                            "1"  ","  "UTC"                ","  "1"     ,

        "LockMode",         "0"  ","  "Recursive"          ","  "1" ","
                            "1"  ","  "SingleLocks"        ","  "1"     ,

        "Whitespaces",      "0"  ","  "Trim"               ","  "1" ","
                            "1"  ","  "Keep"               ","  "1"     ,

        "Create",           "0"  ","  "Never"              ","  "1" ","
                            "1"  ","  "IfNotExistent"      ","  "1"     ,

        "Propagation",      "0"  ","  "Omit"               ","  "1" ","
                            "1"  ","  "ToDescendants"      ","  "1"     ,

        "Phase",            "0"  ","  "Begin "             ","  "1" ","
                            "1"  ","  "End"                ","  "1"     ,

        // end of AddBulk()
        nullptr );


        #if ALIB_MODULE_BOXING && ALIB_MODULE_STRINGS && ALIB_FEAT_BOXING_FTYPES

            ALIB_DBG( ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE( std::type_info*        );    )
                      ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE(aworx::lib::lang::Enum* );

        #endif
    }

}

void Lang::terminationCleanUp()
{
    #if ALIB_MODULE_ALL
       Report::TerminationCleanUp();
    #endif
}


}}}// namespace [aworx::lib::lang]





