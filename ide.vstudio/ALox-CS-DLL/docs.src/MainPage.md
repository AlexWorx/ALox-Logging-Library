\mainpage	ALox Main Page


\section mainpage_overview        Overview

ALox is a small and efficient software library that provides an ecosystem to support structured and organized 
log output.

The library attempts to make logging as easy and lightweight as possible. One of the goals
we want to achieve is that developers, once making use of the library, just stop to put any temporary debug output
statements into their code, but do it all with nice, readable, configurable, reusable logging statements
that can be switched off and that are furthermore automatically pruned out of release versions of
the application.

On the other end of the list, we want to enable release logging for productive applications to collect
mission critical metrics and data from *the field*.
Basic support for release logging is here today already. The introduction of new features and concepts
in the area of release logging will also support debug logging aspects of ALox. Therefore the natural path
of evolution for the ALox project is "debug features first, release features next".

This is Version 1.0.3, a really early release but considered stable. A lot of future improvements are to come. 
Stay tuned. If you do not want to wait, take the source and extend ALox yourself: We hope, the simple [Bauhaus Style](\ref alox_faq)
architecture and code style  of the library allows users to easily extend it with features they 
need today.

We would be happy to receive your feedback or feature requests.


\section mainpage_features        Features and Limitations

To get an overview about what ALox offers, read \ref man_features_and_limitations.


\section mainpage_documentation   Documentation

\subsection mainpage_docs_tut         Tutorials
  
  - \ref tutorial_cs provides first steps for using ALox logging in C# Language
  
\subsection mainpage_docs_man         A-Lox User Manual
  
  \ref manual describes ALox concepts and use in depth and covers all platforms
  and programming languages 
  
  
\subsection mainpage_docs_faq         FAQ
  
  - \ref alox_faq are answered here

  	
\subsection mainpage_docs_chglg       Change Log
  
  - \ref changelog : Information about the version history
	


