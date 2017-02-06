'''#################################################################################################
  gdb pretty printer python scripts for classes of ALib and ALox

  (c) 2015-2016 A-Worx GmbH, Germany
  Published under 'Boost Software License' (a free software license, see LICENSE.txt)

  This Python script implements "pretty printers" for the GNU Debugger 'gdb' as  suggested here:
    https://sourceware.org/gdb/onlinedocs/gdb/Writing-a-Pretty_002dPrinter.html

  Note:
    For users of QT Creator, a dedicated script is available at

            ALOX_LIB_PATH/tools/ideplugins/QTCreator/DebugHelpers/

    For more information, read that scripts header.


  Installation:
    Add the following lines to your "~/.gdbinit" file:

        python sys.path.insert(0, "ALOX_LIB_PATH/tools/ideplugins/gdb" )
        python import alibpp

    (where ALOX_LIB_PATH has to be replaced by the right directory path!)

  Attention:
    The author of this file had a lot of troubles in creating this script. The solution so
    far might be improvable.
    It seems that many IDEs, e.g. Eclipse CDT or CLion do not support the use of 'children' very well
    (as of August 2016 versions). As soon as child values are returned, the 'main' pretty
    printing result is not shown.  It is not very probable that this is a fault of this script,
    because this is also true for official pretty printer scripts of standard c++ container classes
    when used with these IDEs: The objects main value is just not shown with these IDEs.

    Therefore, this script is configurable. Configuration is made by adding global symbols
    to (the debug version) of the inferior (the library or executable to debug). This script
    checks if these symbols exists. The symbols are:
    - ALIB_PRETTY_PRINTERS_SUPPRESS_CHILDREN
      If this symbol is defined, the pretty printers of this script never return any children.
      Instead, the children's names and values are just appended to the pretty-print result
      of the variable itself.

    - ALIB_PRETTY_PRINTERS_FIND_POINTER_TYPES
      If this symbol is defined, then pointer types are treated just as normal types.
      This is dangerous. For example, with current CLion V. 2016.2.1, this symbol must only
      be set if ALIB_PRETTY_PRINTERS_SUPPRESS_CHILDREN is set as well. If not, the whole debug system might
      crash and debugging is not possible anymore.

    To set the symbols, just add a global int value, in one of your C++ files (conditionally, only in
    debug mode). E.g.

        #if defined( ALIB_DEBUG )

        int ALIB_PRETTY_PRINTERS_SUPPRESS_CHILDREN;
        int ALIB_PRETTY_PRINTERS_FIND_POINTER_TYPES

        #endif

        int main( int argc, char **argv )
        {
            ...
            ...

    Alternatively, for CMake users, the provided ALib/ALox CMake scripts create corresponding CMAke
    cache variables that allow to switch this feature.

    The symbols control the global script variables
    - cfg_suppress_children  and
    - cfg_find_pointers which
    are defined below. Instead of compiling the symbols into your software, you can also modify
    the initial value directly in this script. Their default is "-1" which makes the script
    search for the symbols on the first use.

    Currently, in file alib.cpp these variables are set for different IDEs.

    This is all quite ugly, but currently we do not find a different solution.


  Types supported so far:
    - String, TString, AString, StringLiteral, Tokenizer
    - Directory
    - Ticks
    - Thread, ThreadLock, ThreadLockNR,
    - Logger, Domain

#################################################################################################'''
import string
try:
    import gdb
    import gdb.printing
    import gdb.types
    import gdb.events
except:
    pass

import os
import os.path
import sys
import struct
import types


# For explanation see notes above!
cfg_suppress_children= -1

# For explanation see notes above!
cfg_find_pointers= -1



#
# ############################ Working with the inferior #############################
#
class InferiorByteArray(object):
    def __init__(self, base, size):
        self.data = gdb.selected_inferior().read_memory(base, size)

    def get(self, offset = 0):
        return struct.unpack_from("b", self.data, offset)[0]

#
# ############################ ALIB String Tools #############################
#

#----- Compare two ALib strings  ------
def areEqualStrings(strObject1, strObject2):

    # compare length
    length1=     strObject1["length"]
    length2=     strObject2["length"]

    if length1 != length2:
        return 0
    length= int(length1)

    # compare addresses
    straddress1= strObject1["buffer"]
    straddress2= strObject2["buffer"]

    if straddress1 == straddress2:
        return 1
    if straddress1 == 0 or straddress2 == 0:
        return 0

    # compare contents
    byteArray1 = InferiorByteArray( straddress1, length )
    byteArray2 = InferiorByteArray( straddress2, length )
    for i in range(0, length ):
        b1=  byteArray1.get(i)
        b2=  byteArray2.get(i)
        if b1 != b2:
            return 0

    # equal
    return 1


#----- Get the string value of an ALib string  ------
def getASString(strObject):
    straddress= strObject["buffer"]
    length=     strObject["length"]

    if length < 0:
        return "<negative length>"

    if straddress == 0:
        return "<nulled>"

    if length == 0:
        return "<empty>"

    if length > 200:
        cut=    True
        length= 200
    else:
        cut=    False

    byteArray = InferiorByteArray( straddress, length )
    asBuffer= ""
    zeroFound= 0
    for i in range(0, length ):
        b=  byteArray.get(i)
        c= int(b)
        if (c < 0):
            c=  c + 256
        if c == 0 and zeroFound == 0:
            asBuffer= "('\\0' at %i!) "  % i  + asBuffer
            zeroFound= 1

        if (c == 92):
            asBuffer+= r"\\"
            asBuffer+= c

        if (c == 34):
            asBuffer+= r'\\"'

        elif (c >= 32) and (c <= 127):
            asBuffer+= chr(c)

        elif (c < 32 ):
            asBuffer+= r'\\0'
            asBuffer+=  str(int(c/8))
            asBuffer+=  str(    c%8 )

        else:
            asBuffer+= r'\\x'
            nibble= int(c/16)
            if ( nibble < 10 ):
                asBuffer+= chr( 48 + nibble )
            else:
                asBuffer+= chr( 55 + nibble )
            nibble= int(c%16)
            if ( nibble < 10 ):
                asBuffer+= chr( 48 + nibble )
            else:
                asBuffer+= chr( 55 + nibble )

    if cut:
        asBuffer+= "..."
    return  asBuffer

#
# ############################ ALox Tools #############################
#

def getVerbosityString( value ):
    if value == 0:
        return "Verbose"
    if value == 1:
        return  "Info"
    if value == 2:
        return  "Warning"
    if value == 3:
        return  "Error"
    if value == 4:
        return  "Off"

    return  "<unknown value (" + str(value) + ")>"

def getLoggerDescription(value):
    name=       value["Name"]
    typeName=   value["TypeName"]
    result= getASString( name )

    if not areEqualStrings( name, typeName ):
        result+= " (" + getASString( typeName ) + ")"
    result+= " [" + str(value["CntLogs"] ) + "]"

    return result


#
# ############################## The Pretty Printer class ##############################
#
class ALibPrinter(object):
    ''' Generic printer taking the readily made variables result and children '''

    def __init__( self, result, children ):
        self.result=     result
        self.children=   children

    def to_string(self):
        return self.result


    def children(self):
        return self.childrenDict

glbALibPrinterWithOutChildrenBlocker= False
class ALibPrinterWithOutChildren(object):
    ''' Printer that does not define the 'children' method, to avoid problems with
    some IDEs '''

    def __init__( self, result, children ):
        self.result=    result
        self.childrenDict=  children

    def to_string(self):
        result= self.result
        global glbALibPrinterWithOutChildrenBlocker
        if glbALibPrinterWithOutChildrenBlocker is False:
            if self.childrenDict is not None:
                glbALibPrinterWithOutChildrenBlocker= True
                for t in self.childrenDict:
                    result+= ", " + t[0] +'=' + str(t[1])
                glbALibPrinterWithOutChildrenBlocker= False
        return result

    #def display_hint (self):
    #    return 'string'

#
# ############################## ALIB Printer ##############################
#
def lookup_pp_alib_and_alox( value  ):
    "Looks and implements ALib printers"

    type=  str(value.type.strip_typedefs() )

    # not aworx?
    if not type.startswith( "aworx::"):
        return None
    type= type[7:]

    #print( "ALib: Lookup for type >%s< " % type )


    # pointer / reference
    global cfg_find_pointers
    if cfg_find_pointers is -1:
        print ( 'ALib: Detecting global symbol "ALIB_PRETTY_PRINTERS_FIND_POINTER_TYPES"...')
        if  gdb.lookup_global_symbol( "ALIB_PRETTY_PRINTERS_FIND_POINTER_TYPES" ) is None:
            print ( 'ALib: ... not found')
            cfg_find_pointers=  0
        else:
            print ( 'ALib: ... found')
            cfg_find_pointers=  1


    if cfg_find_pointers == 1 and type.endswith(" *"):
        type= type[0:-2]


    if type.endswith(" &"):
        type= type[0:-2]


    # declare result and children for our pretty printer
    result=     None
    children=   None


    try:
        ################################## ALib ##################################
        if type.startswith( 'lib::' ):
            type= type[5:]


            #--------------------------------- strings ---------------------------------
            if type.startswith( 'strings::' ):
                type= type[9::]

                if type == "String":
                    asBuffer= getASString( value )
                    result= "[" + str(value["length"]) + '] "'  + asBuffer + '"'

                    children= [ ("buffer"   , value["buffer"]   ),
                                ("length"   , value["length"]   )   ];

                if type == "TString":
                    result= "[" + str(value["length"]) + '] "'  + getASString( value ) + '"'

                elif type == "Substring":
                    result= "[" + str(value["length"]) + '] "'  + getASString( value ) + '"'

                elif type[:13] == "StringLiteral":
                    result= "SLiteral<" + str(value["length"]) + '> "'  + getASString( value ) + '"'


                elif type == "AString":
                    result= "[" + str(value["length"]) +"/"
                    capacity= value["capacity"]
                    if capacity < 0:
                        result+=  str(-capacity) + "(Ext)"
                    else:
                        result+= str(capacity)
                    result+= '] "'  + getASString( value ) + '"'

                    children= [  ( "aworx::lib::strings::TString", value.cast(gdb.lookup_type("aworx::lib::strings::TString") ) )
                                ,( "capacity" , value["capacity"] )
                              ];
                    try:
                        children.append( ("OTW_ReplaceExternalBuffer" , value["ALIB_OTW_ReplaceExternalBuffer"] ) )
                    except:
                        pass

                elif type[:18] == "PreallocatedString":
                    result= "[" + str(value["length"]) +"/"
                    capacity= value["capacity"]
                    if capacity < 0:
                        result+=  str(-capacity) +"(PA)"
                    else:
                        result+= str(capacity)  +"(Replaced!)"
                    result+= '] "'  + getASString( value ) + '"'

                    children= [  ( "aworx::lib::strings::AString", value.cast(gdb.lookup_type("aworx::lib::strings::AString") ) )
                                ,( "capacity" , value["capacity"] )
                                 ];

                elif type == "Tokenizer":
                    result= 'Actual="' + getASString( value["Actual"] ) + \
                             '" Rest="' + getASString( value["Rest"] ) + '"' + \
                             " Delim='" + chr(value["delim"]) + "'"



            #--------------------------------- System ---------------------------------
            elif type.startswith( 'system::' ):
                type= type[8::]

                if type == "Directory":
                    result= getASString( value["Path"] )

            #--------------------------------- Time ---------------------------------
            elif type.startswith( 'time::' ):
                type= type[6::]

                if type == "Ticks":
                    result=  "<error>"
                    ticks= value["ticks"]
                    seconds=     1000000000
                    minutes=     1000000000 * 60
                    hours=       minutes*60
                    milliseconds= 1000000
                    microseconds=1000
                    if ticks == 0:
                        result= "<Uninitialized (0)>"
                    else:
                        origTicks= ticks
                        result= ""

                        if origTicks >= hours:

                            result+=  str(ticks/hours) + "h "
                            ticks-= int(ticks/hours) * hours

                        if origTicks >= seconds:

                            result+=  "%02d:" %  (ticks/minutes)
                            ticks-= int(ticks/minutes) * minutes

                            result+=   "%02d" %  (ticks/seconds)
                            ticks-= int(ticks/seconds)*seconds

                        if origTicks <  hours:
                            if origTicks >= seconds:
                                result+= "  +"

                            ms= int(ticks/milliseconds)
                            if ms > 0:
                                result+=  "%03dms " % ms
                                ticks-= ms * milliseconds

                        if origTicks <  minutes:

                            us= int(ticks/microseconds)
                            if us > 0:
                                result+=  "%03dus " % us
                                ticks-= us * microseconds

                            result+=  "%03dns " % ticks
                            ticks-= ticks/microseconds


            #--------------------------------- Threads ---------------------------------
            elif type.startswith( 'threads::' ):
                type= type[9::]
                if type == "ThreadLockNR":
                    tnrIsAcquired= value["dbgIsAcquired"]
                    result= "Unlocked" if (tnrIsAcquired == 0) else "Locked"
                    if value["mutex"] == 0:
                        result+= " (Unsafe mode!)"

                    children= [ ("acquirementSourcefile"   , value["acquirementSourcefile"]   ),
                                ("acquirementLineNumber"   , value["acquirementLineNumber"]   ),
                                ("acquirementMethodName"   , value["acquirementMethodName"]   )   ];

                elif type == "ThreadLock":
                    tnrCntLock= value["cntAcquirements"]
                    if tnrCntLock == 0:
                        result= "Unlocked"

                    elif tnrCntLock == 1:
                        result= "Locked"

                    elif tnrCntLock < 0:
                        result= "Illegal State. cntAcquirements=" + str(tnrCntLock)

                    else:
                        result= "Locked (" + str(tnrCntLock) +")"

                    if value["lockMode"] != 0:
                        result+= " (Non-Recursive)"

                    if value["mutex"] == 0:
                        result+= " (Unsafe mode!)"
                    else:
                        if tnrCntLock >= 1:
                            result+=  ", Owner: " + "#" + str(value["owner"]["id"]) + ' "' \
                                      + getASString( value["owner"]["name"] ) + '"'


                    children= [ ("lockMode"                , value["lockMode"]                ),
                                ("cntAcquirements"         , value["cntAcquirements"]         ),
                                ("owner"                   , value["owner"]                   ),
                                ("mutex"                   , value["mutex"]                   ),
                                ("acquirementSourcefile"   , value["acquirementSourcefile"]   ),
                                ("acquirementLineNumber"   , value["acquirementLineNumber"]   ),
                                ("acquirementMethodName"   , value["acquirementMethodName"]   )   ];

                elif type == "Thread":
                    result =  "#" + str(value["id"]) + ' "' + getASString( value["name"] )
                    result+=  '" (Alive/' if (value["isAliveFlag"]   != 0) else '" (Not alive/'
                    result+=  "User)"    if (value["id"]             >  0) else "System)"


        ################################## ALox ##################################
        elif type.startswith( 'lox::' ):
            type= type[5:]


            #---------------------------- Verbosity ------------------------------
            if type == "Verbosity":
                result= getVerbosityString( value )

            #---------------------------- Loggers ------------------------------
            elif type == "core::Logger"                 or \
                 type == "core::textlogger::TextLogger" or \
                 type == "loggers::ConsoleLogger"       or \
                 type == "loggers::MemoryLogger"        or \
                 type == "loggers::AnsiLogger"          or \
                 type == "loggers::AnsiConsoleLogger":

                result= getLoggerDescription( value )

            #---------------------------- Domain ------------------------------
            elif type == "core::Domain":

                result= ""

                # get absolute domain path
                domain= value
                omitFirstSlash= domain["Parent"] != 0
                while True:
                    if omitFirstSlash == False:
                        result=   "/" + result
                    omitFirstSlash= False

                    if domain["Name"]["length"] != 0:
                        result= getASString( domain["Name"] ) + result
                    domain= domain["Parent"]
                    if domain == 0:
                        break

                result+= "  [" + str(value["CntLogCalls"]) + "]"

                children= [    #("Name"              , value["Name"]              ) ,
                               ("Parent"            , value["Parent"]            ) ,
                               ("SubDomains"        , value["SubDomains"]        ) ,
                               ("Data"              , value["Data"]              ) ,
                               ("FullPath"          , value["FullPath"]          ) ,
                               ("CntLogCalls"       , value["CntLogCalls"]       ) ,
                               ("ConfigurationRead" , value["ConfigurationRead"] )   ]


            #---------------------------- Domain::LoggerData ------------------------------
            elif type == "core::Domain::LoggerData":
                result = "<"            + getVerbosityString(   value["LoggerVerbosity"]   )
                result+= ", "           + getLoggerDescription( value["Logger"]            )
                result+= ", priority="  + str(                  value["Priority"]          )
                result+= ">["           + str(                  value["LogCallsPerDomain"] ) + "]"

                #children= [ ("Name"              , value["Name"]              ) ,
                #            ("Parent"            , value["Parent"]            ) ,
                #            ("SubDomains"        , value["SubDomains"]        ) ,
                #            ("Data"              , value["Data"]              ) ,
                #            ("FullPath"          , value["FullPath"]          ) ,
                #            ("CntLogCalls"       , value["CntLogCalls"]       ) ,
                #            ("ConfigurationRead" , value["ConfigurationRead"] )   ];


    except Exception as e:
        print ("\nALib: !!! Exception occured: %s" % str(e))
        if result != None and len(result) > 0:
            result= "<Pretty Printer Error. Unfinished result='%s'>" % result
        else:
            result= "<Pretty Printer Error>"
        pass


    # now return a printer
    if result is None:
        return None

    if children is None:
        return ALibPrinterWithOutChildren( result, children )

    global cfg_suppress_children
    if cfg_suppress_children is -1:
        print ( 'ALib: Detecting global symbol "ALIB_PRETTY_PRINTERS_SUPPRESS_CHILDREN"...')
        if  gdb.lookup_global_symbol( "ALIB_PRETTY_PRINTERS_SUPPRESS_CHILDREN" ) is None:
            print ( 'ALib: ... not found')
            cfg_suppress_children=  0
        else:
            print ( 'ALib: ... found')
            cfg_suppress_children=  1

    if cfg_suppress_children is 0:
        return ALibPrinter( result, children )
    else:
        return ALibPrinterWithOutChildren( result, children )



    return None

def add_printers(obj):
    "Register ALib/ALox pretty printer lookup methods with."

    print( 'ALib: Registering Pretty Printers for ALib and ALox', True  )
    gdb.printing.register_pretty_printer(obj, lookup_pp_alib_and_alox, replace=True)


####################################################################################################
### main entry point
####################################################################################################

# invoked from .gdbinit ?
if gdb.current_objfile() is None:

    # import adpp main module
    try:
        import alibpp
    except Exception as e:
        gdb.write("Exception occurred: %s" % str(e) )
        raise Exception("Seems like this script is included in file '.gdbinit', but the propper import path is not set. ")


else:
    # import adpp main module
    try:
        import alibpp
    except:
        # TODO: in  /usr/lib/gcc/x86_64-pc-linux-gnu/5.4.0/libstdc++.so.6.0.21-gdb.py
        # is code included that inserts the module path to find the library from the object file name
        # not supported today....
        print ( __file__)

        raise Exception( "Can't find module 'addp.py'. Exiting" )


alibpp.add_printers(gdb.current_objfile())

##### For debugging: starts our test program.
##### (We just get more info when running this in a stand-alone GDB session)
#gdb.execute ( "file Debug/ALib_ALox_UT" )
#gdb.execute ( "break lox.cpp:1656" )
#gdb.execute ( "run" )
