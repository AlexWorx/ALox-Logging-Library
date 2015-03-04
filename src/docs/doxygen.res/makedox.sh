echo "*** Creating C# site ***"
doxygen Doxyfile.forCS

echo "*** Creating JAVA site ***"
doxygen Doxyfile.forJAVA

echo "*** Creating main site ***"
doxygen Doxyfile
