@echo Note: To successfully create the documentation, the unit tests have to be run upfront to generate input files.
@echo *** Creating C++ site ***
doxygen.exe doxygen/doxyfile.cpp.ini

@echo *** Creating C# site ***
doxygen.exe doxygen/doxyfile.cs.ini

@echo *** Creating JAVA site ***
doxygen.exe doxygen/doxyfile.java.ini

@echo *** Creating main site ***
doxygen.exe doxygen/doxyfile.ini

