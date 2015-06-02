@echo *** Creating C++ site ***
doxygen.exe cpp.doxyfile

@echo *** Creating C# site ***
doxygen.exe cs.doxyfile

@echo *** Creating JAVA site ***
doxygen.exe java.doxyfile

@echo *** Creating main site ***
doxygen.exe doxyfile
