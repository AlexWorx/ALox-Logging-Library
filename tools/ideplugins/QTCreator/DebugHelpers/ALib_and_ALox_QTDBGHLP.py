####################################################################################################
#  QTCreator Debug Helper python scripts for classes of ALib and ALox
#
#  (c) 2015-2016 A-Worx GmbH, Germany
#  Published under MIT License (Open Source License, see LICENSE.txt)
#
#  For further information, see http://doc.qt.io/qtcreator/creator-debugging-helpers.html
####################################################################################################

############################ imports #############################
import string

############################ general helpers #############################
def dbgOut( msg ):
    fh = open("~/output.txt", 'a')
    fh.write(msg)
    fh.write("\n")
    fh.close()
    return

def removeNamespaceHelper(s, startIdx, namespace):
    namespace+= "::"
    if s.startswith( namespace, startIdx ):
        startIdx+= len(namespace)

    return startIdx

def removeNamespace(identifier):
    identifier= str(identifier)
    actIdx= 7
    actIdx= removeNamespaceHelper( identifier, actIdx, "aworx" )
    actIdx= removeNamespaceHelper( identifier, actIdx,      "lib" )
    actIdx= removeNamespaceHelper( identifier, actIdx,          "strings" )
    actIdx= removeNamespaceHelper( identifier, actIdx,          "system" )
    actIdx= removeNamespaceHelper( identifier, actIdx,          "threads" )
    actIdx= removeNamespaceHelper( identifier, actIdx,          "time" )
    actIdx= removeNamespaceHelper( identifier, actIdx,          "config" )
    actIdx= removeNamespaceHelper( identifier, actIdx,      "lox" )
    actIdx= removeNamespaceHelper( identifier, actIdx,          "core" )
    actIdx= removeNamespaceHelper( identifier, actIdx,          "loggers" )
    actIdx= removeNamespaceHelper( identifier, actIdx,          "Log" )  #For Enums in class Log

    return identifier[actIdx:]

############################ ALIB Strings #############################

#----- Compare two ALib strings  ------
def areEqualStrings(d1, strObject1, d2, strObject2):

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
    blob1 = d1.extractBlob(straddress1, length)
    blob2 = d2.extractBlob(straddress2, length)
    for i in range(0, length ):
        b1=  blob1.extractByte(i)
        b2=  blob2.extractByte(i)
        if b1 != b2:
            return 0

    # equal
    return 1

#----- Get the string value of an ALib string  ------
def getASString(d, strObject):
    straddress= strObject["buffer"]
    length=     strObject["length"]

    if length < 0:
        return "<negative length>"

    if straddress == 0:
        return "<nulled>"

    if length == 0:
        return "<empty>"

    if length > 200:
        length= 200

    blob = d.extractBlob(straddress, length)
    asBuffer= ""
    zeroFound= 0
    for i in range(0, blob.size ):
        b=  blob.extractByte(i)
        c= int(b)
        if (c < 0):
            c=  c + 256
        if c == 0 and zeroFound == 0:
            asBuffer= "('\\0' at %i!) "  % i  + asBuffer
            zeroFound= 1

        if (c == 92):
            asBuffer+= r"\\"
        elif (c == 34):
            asBuffer+= r'\"'
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

    return  asBuffer

#----- String  ------
def qdump__aworx__lib__strings__AS(d, value):
    try:
        asBuffer= getASString( d, value )
        d.putValue( "[" + str(value["length"]) + r"] \"" + asBuffer + r"\"" )
    except:
        d.putValue("<String (AS) DBGHelper Exception>")
        return

    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)
    return

#----- Substring  ------
def qdump__aworx__lib__strings__ASSubstring(d, value):
    return qdump__aworx__lib__strings__AS(d, value)

#----- TString  ------
def qdump__aworx__lib__strings__ASTerminatable(d, value):
    try:
        asBuffer= getASString( d, value )
        d.putValue( "T[" + str(value["length"]) + r"] \"" + asBuffer + r"\""   )

    except:
        d.putValue("<TString DBGHelper Exception>")
        return

    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)

    return

#----- AString  ------
def qdump__aworx__lib__strings__ASAlloc(d, value):
    try:
        asBuffer= getASString( d, value )
        d.putValue( "[" + str(value["length"]) +"/" + str(value["capacity"]) + r"] \"" + asBuffer + r"\"" )

    except:
        d.putValue("<AString DBGHelper Exception>")
        return

    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)

    return


#----- ASPreAlloc  ------
def qdump__aworx__lib__strings__ASPreAlloc(d, value):
    return qdump__aworx__lib__strings__ASAlloc(d, value)


#----- StringLiteral  ------
def qdump__aworx__lib__strings__ASLiteral(d, value):
    try:
        d.putValue( "Lit<" + str(value["length"]) + r">: \"" + getASString( d, value ) + r"\"" )

    except:
        d.putValue("<ASPreAlloc DBGHelper Exception>")
        return

    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)

    return

#----- Tokenizer  ------
def qdump__aworx__lib__strings__Tokenizer(d, value):

    try:
        d.putValue( r"Actual: \"" + getASString( d, value["Actual"] ) + r"\" Rest: \"" + getASString( d, value["Rest"] ) + r"\"" )

    except:
        d.putValue("<Tokenizer DBGHelper Exception>")
        return

    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)

    return

############################ ALIB System #############################

#----- Directory  ------
def qdump__aworx__lib__system__Directory(d, value):
    # get member path
    asPathBuffer= getASString( d, value["Path"] )

    # write result
    d.putValue( asPathBuffer )

    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)
    return


############################ ALIB Thread #############################

#----- Thread  ------
def getThreadIDAndName(d, value):
    return "(" + str(value["id"]) + ") " + getASString( d, value["name"] )


def qdump__aworx__lib__threads__Thread(d, value):

    dhResult =  getThreadIDAndName( d, value )
    dhResult+=  " (Alive/" if (value["isAliveFlag"]    != 0) else " (Not alive/"
    dhResult+=  "User)"    if (value["id"] > 0) else "System)"
    d.putValue( dhResult )

    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)

    return

#----- ThreadLockNR  ------
def qdump__aworx__lib__threads__ThreadLockNR(d, value):

    tnrIsAcquired= value["dbgIsAcquired"]
    dhResult= "Unlocked" if (tnrIsAcquired == 0) else "Locked"

    if value["mutex"] == 0:
        dhResult+= " (Unsafe mode!)"

    d.putValue( dhResult )

    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)

    return

#----- ThreadLock  ------
def qdump__aworx__lib__threads__ThreadLock(d, value):

    tnrCntLock= value["cntAcquirements"]
    if tnrCntLock == 0:
        dhResult= "Unlocked"

    elif tnrCntLock == 1:
        dhResult= "Locked"

    elif tnrCntLock < 0:
        dhResult= "Illegal State. cntAcquirements=" + str(tnrCntLock)

    else:
        dhResult= "Locked (" + str(tnrCntLock) +")"

    if value["lockMode"] != 0:
        dhResult+= " (Non-Recursive)"

    if value["mutex"] == 0:
        dhResult+= " (Unsafe mode!)"
    else:
        if tnrCntLock >= 1:
            dhResult+=  ", Owner: " + getThreadIDAndName( d, value["owner"] )

    d.putValue( dhResult )

    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)

    return


############################ ALox  #############################

#----- Logger Types  ------

def getLoggerDescription(d, value):
    result= "(disabled) " if (value["IsDisabled"] != 0) else ""

    result+= getASString( d, value["Name"] )

    if not areEqualStrings(d, value["Name"], d, value["TypeName"] ):
        result+= " (" + getASString( d, value["TypeName"] ) + ")"
    result+= " [" + str(value["CntLogs"] ) + "]"

    return result

def stdLoggerHelper(d, value):
    d.putValue( getLoggerDescription( d, value ) )
    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)

#----- do the same for all Logger types  ------
def qdump__aworx__lox__core__Logger(d, value):
    stdLoggerHelper(d, value)

def qdump__aworx__lox__core__textlogger__TextLogger(d, value):
    stdLoggerHelper(d, value)

def qdump__aworx__lox__loggers__AnsiLogger(d, value):
    stdLoggerHelper(d, value)

def qdump__aworx__lox__loggers__AnsiConsoleLogger(d, value):
    stdLoggerHelper(d, value)

def qdump__aworx__lox__loggers__ConsoleLogger(d, value):
    stdLoggerHelper(d, value)

def qdump__aworx__lox__loggers__MemoryLogger(d, value):
    stdLoggerHelper(d, value)

#----- LogDomain ------
def getLogDomainFullName(d, domain, actString):

    # root domain?
    if domain["Name"]["buffer"] == 0:
        return "/" + actString

    # add current
    if actString != "":
        actString= "/" + actString
    actString=  getASString( d, domain["Name"] ) + actString

    # recursion
    return  getLogDomainFullName(d, domain["Parent"], actString)

def getLogDomainInheritedLevel(value):

    dhLevel=  value["level"]
    dhParent= value["Parent"]

    if ( dhParent == 0 or dhLevel <= 4 ):
        return removeNamespace( dhLevel )

    return getLogDomainInheritedLevel( dhParent )

def qdump__aworx__lox__core__LogDomain(d, value):
    dhResult=  getLogDomainFullName(d, value, "") +" "
    dhLevel= value["level"]
    if dhLevel != 5:
        dhResult+= "<" + removeNamespace( dhLevel ) + ">"
    else:
        dhResult+= "<" + getLogDomainInheritedLevel( value ) + "> (inherited)"

    d.putValue( dhResult )

    #----- expands normal object ----
    d.putNumChild(1)
    if d.isExpanded():
        d.putPlainChildren(value)




