mkdir styles

doxygen -w html styles\default_header.html default_footer.html default_stylesheet.css   doxyfile
doxygen -l styles\default_doxlayout.xml    doxyfile

