##ALox Homepage ##
Please find all about the ALox Logging library, including tutorials, manual, reference documentation,
FAQ and the change log at the [ALox Homepage](http://alexworx.github.io/ALox-Logging-Library) 
hosted on GitHub.


##Quick Overview ##

ALox is a small and efficient software library that provides an ecosystem to support structured and organized 
log output.

ALox was implemented in C++, C# and Java

The library attempts to make logging as easy and lightweight as possible. One of the goals
we want to achieve is that developers, once making use of the library, just stop to put any temporary debug output
statements into their code, but do it all with nice, readable, configurable, reusable logging statements
that can be switched off and that are furthermore automatically pruned out of release versions of
the application. 

On the other end of the list, we want to enable release logging for productive applications to collect
mission critical metrics and data from *the field*.

Of-course, ALox is designed to have all debug logging statements pruned (automatically) out of your release code, 
while release logging stays in!
