mkdir styles

doxygen -w html styles\main_header.html styles\main_footer.html styles\main_stylesheet.css   Doxyfile
doxygen -w html styles\cs_header.html   styles\cs_footer.html   styles\cs_stylesheet.css     Doxyfile.forCS
doxygen -w html styles\java_header.html styles\java_footer.html styles\java_stylesheet.css   Doxyfile.forJAVA


doxygen -l styles\main_DoxygenLayout.xml    Doxyfile
doxygen -l styles\cs_DoxygenLayout.xml      Doxyfile.forCS
doxygen -l styles\java_DoxygenLayout.xml    Doxyfile.forJAVA

