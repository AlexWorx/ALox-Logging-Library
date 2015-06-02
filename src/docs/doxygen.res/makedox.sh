echo "*** Creating C++ site ***"
doxygen cpp.doxyfile

echo "*** Creating C# site ***"
doxygen cs.doxyfile

echo "*** Creating JAVA site ***"
doxygen java.doxyfile

echo "*** Creating main site ***"
doxygen doxyfile
