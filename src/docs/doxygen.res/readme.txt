This folder contains:
* Doxyfiles:
  * "java.doxyfile" for JAVA sub documentation tree
  * "cs.doxyfile" for C# sub documentation tree
  * "cpp.doxyfile" for C++ sub documentation tree
  * "doxyfile" for main documentation tree

* batch scripts (.bat for Windows, .sh for unix/bash)
  * makedox.bat/.sh  to create doxygen documentation
  * makeDoxygenTemplates.bat/sh to create the subfolder "styles" and within that
    the defaults from doxygen for the page layout that after the creation can be
    edited manually.

Note on the template generation:
With new doxygen versions, new templates might be generated. Therefore, the generated
"default_X.Y" files need to be merged with the existing (old) version.
