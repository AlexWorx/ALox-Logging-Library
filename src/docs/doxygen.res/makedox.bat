@echo *** Creating C# site ***
doxygen.exe Doxyfile.forCS

@echo *** Creating JAVA site ***
doxygen.exe Doxyfile.forJAVA

@echo *** Patching JAVA tag file ***
cscript replaceDoxygenJavaTagBug.vbs

@echo *** Creating main site ***
doxygen.exe Doxyfile
