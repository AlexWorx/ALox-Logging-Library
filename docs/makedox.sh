#!/bin/bash

echo "Note: To successfully create the documentation, the unit tests have to be run upfront to generate input files."

### Cleaning before build When uncomment, also uncomment the echo message below ###
# echo "!!! Cleaning before build. This is for testing.  !!!"
# makeclean.sh

echo "*** Creating C++ site ***"
doxygen doxygen/doxyfile.cpp.ini

echo "*** Creating C# site ***"
doxygen doxygen/doxyfile.cs.ini

echo "*** Creating JAVA site ***"
doxygen doxygen/doxyfile.java.ini

echo "*** Creating main site ***"
doxygen doxygen/doxyfile.ini

#echo "*** Copying other additional resources ***"
 cp resources/* ../html
 cp resources/* ../html/cpp_ref
 cp resources/* ../html/cs_ref
 cp resources/* ../html/java_ref
