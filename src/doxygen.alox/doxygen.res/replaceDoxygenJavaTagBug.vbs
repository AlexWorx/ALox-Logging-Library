Const ForReading = 1    
Const ForWriting = 2

strFileName=    "..\..\..\html\java_ref\java_ref.tag"
strOldText=     "compound kind=" & chr(34) & "enum"  & chr(34) 
strNewText=     "compound kind=" & chr(34) & "class" & chr(34) 

Set objFSO = CreateObject("Scripting.FileSystemObject")

Set objFile = objFSO.OpenTextFile(strFileName, ForReading)
strText = objFile.ReadAll
objFile.Close

strNewText = Replace(strText, strOldText, strNewText)
Set objFile = objFSO.OpenTextFile(strFileName, ForWriting)
objFile.Write strNewText  'WriteLine adds extra CR/LF
objFile.Close
