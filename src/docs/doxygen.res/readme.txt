This folder contains:
* Doxyfiles:
  * "Doxyfile.forJAVA" for JAVA sub documentation tree
  * "Doxyfile.forCS" for C# sub documentation tree
  * "Doxyfile" for main documentation tree
  
* batch scripts (.bat for Windows, .sh for unix/bash)
  * makedox.bat/.sh  to create doxygen documentation
  * makeDoxygenTemplates.bat/sh to create the subfolder "styles" and within that 
    the stubs for the page layout that after the creation can be edited manually.
    
Note on the template generation:
With new doxygen versions, new templates might be generated. This will overwrite the
existing ones. Therefore, the following approach might be taken: 
* backup the current styles by renaming the existing styles folder
* run the script (makeDoxygenTemplates)
* merge the changes within the old version into the new version.      
    