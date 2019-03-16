## ALox Homepage ##
Please find all about the **ALox Logging Library**, including

* **Tutorials**
* **User manual**
* **Reference documentation**
* **FAQ** and the
* **Change log**

at the [ALox Homepage](http://alexworx.github.io/ALox-Logging-Library).



## Overview ##

ALox is a software library providing an ecosystem for structured and organized log output.

ALox is available as [ALox for C++ 11](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/cppmainpage.html), [ALox for C#](http://alexworx.github.io/ALox-Logging-Library/cs_ref/csmainpage.html) and [ALox for Java](http://alexworx.github.io/ALox-Logging-Library/java_ref/javamainpage.html).

To reach this goal, ALox is featured by **ALib** (see ALib for [C++](https://alexworx.github.io/ALib-Class-Library/index.html),[C#](http://alexworx.github.io/ALox-Logging-Library/cs_ref/alox_cs_mainpage.html),[Java](http://alexworx.github.io/ALox-Logging-Library/java_ref/alox_cs_mainpage.html)), which is a basic utility library that among other goals
provides *'source-compatible'* types for the three languages.

ALox attempts to make logging as easy and intuitive as possible. We want you to **stop adding temporary debug output lines** into your code. Instead, write (with less effort!) short, nice and readable *ALox statements* that live in your code as if they were comment lines. Let ALox do the rest: Add meta information to the output, format the output, filter output based on verbosity level and based on your current topic of interest. Finally, get it all *pruned* out of your release executable, same as your source comments.

On the other end of the list, ALox  enables **release logging** for productive applications to collect mission critical **metrics from the field**.

This is **Version 1903 Revision 0**.

## C++ Version ##
As of library version 1805, the C++ codebase was extracted from this repository.
**ALox for C++** became a "module" of general purpose class library **"ALib"**.
Consequently, the C++ sources of ALox are to be retrieved at
[ALib for C++ Github Repository](https://github.com/AlexWorx/ALib-Class-Library). 

**ALib for C++** also disposes about a dedicated [homepage](http://alexworx.github.io/ALib-Class-Library).


## Features ##

* Available for **C++ 11** (GNU/Linux, Windows OS, macOS),  **C#** (.Net, Windows, Linux, Microsoft, Mono) and **Java**
  (with Android support and extensions).

* **Free software**, published under Boost Software License.

* Jump-start **tutorials** for [ALox for C++](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/cpptutorial.html),[ALox for C#](http://alexworx.github.io/ALox-Logging-Library/cs_ref/cstutorial.html) and [ALox for Java](http://alexworx.github.io/ALox-Logging-Library/java_ref/javatutorial.html), **Sample Projects** and pre-configured project files for **different IDEs** and **CMake**.

* **Formatted**, **colorful** and **configurable** log output** with support for ANSI compatible consoles and Windows OS consoles.

* Log lines **'clickable' in IDE** to jump to the corresponding source code line (depending on IDE).

* Automatic collection of **meta information** like time stamp, time-difference to previous log, executing thread or executing source scope information (platform/language dependent).

* Automatic removal, aka **'pruning'**,  of *debug-log* statements from release code mostly without the need of pre-processor if/endif code cluttering. Optionally also automatic pruning of *release-log* statements. (In Java: implemented using [Proguard](http://proguard.sourceforge.net), with provision of ready to use configuration files.

- Minimal intrusiveness in respect to *cluttering* your code and what you need to make it really work.

* Use of external configuration (INI-files, command line parameters, environment variables, etc.) which allows developer specific local settings and greatly supports working in teams.

* **Hierarchical 'Log-Domains'**, (like for example "MYAPP/UI", "MYAPP/DATABASE" that allow the classification of different log statements into user defined topics. Verbosity is controlled per domain to allow the programmer to concentrate on the area of current interest.

* Defaulting 'Log-Domains' for **source scopes**, like *file*, *class* or *method*, which allows to omit the log-domain parameter from the log statements (again: leads to short, clean and readable log statements).

* Defaulting 'Log-Domains' for **thread scopes**, which allows to control the verbosity of the log output on a per thread basis.

* Support for **CMake**, **Eclipse**, **Visual Studio**, **QT Creator**, **Mono Develop** in combination with **GNU/Linux**, **Windows**, **Windows Phone** and **Android**. (Windows Phone in current versions not tested any more). Porting to other platforms should be easy.

* Very **fast** to minimize runtime overhead of logging (We just broke our former record and did **one million log lines in a second**, including meta information. This was of-course the C++ version doing release logging on release executable).

* Multiple **parallel log streams** with different *filters* and verbosity levels, e.g. for logging to the console and in parallel into a file.

* **Extensible** with own loggers, which enables dedicated "data drains" (e.g. databases or Internet services) and custom output formatting. ALox provides a simple programming interface and internal architecture that is easy to learn, not overloaded by 'factories' and 'factory factories' ;-)

* Logging of <b>arbitrary objects</b> which means the whole ALox architecture is designed for logging 'objects' instead of just string messages. Only the logger instances which are attached at runtime, decide how logged data might be converted to human readable strings.

* Scope dependent **Log Data** to add debug variables that automatically get pruned like the debug-logging statments are.

* **Conditional logging** (similar to assertions).

* **Log Once** to restrict a log message or a set of log messages to appear only once (or up to n-times).

* Support for **Recursive logging**, which is the correct execution of log statements during the evaluation of parameters of another log statement.

* Automatic (OK, half-automatic :-) mapping of thread IDs to **readable thread names**

* **LogTools** (in C# and Java) for

    * Recursive **logging of complex types** with one line of code using *class inspection/reflection*. Variable recursion depth and detection of cyclic references.
    * Logging **Exceptions** (recursively with inner exceptions)
    * Logging **XML trees**

* C++ version:
  * Compiled and tested on **GNU/Linux**, **Windows OS** and Apple **macOS**.
  * Accepts **arbitrary objects** to be logged. This goal is reached by using underlying library [ALib Boxing](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/namespaceaworx_1_1lib_1_1boxing.html) which allows to pass 'anything' as a parameter to C++ functions and methods.
  * Accepts **3rd party string types**. This goal is reached by using underlying library [ALib Strings](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/namespaceaworx_1_1lib_1_1strings.html).

* and finally: ALox is under **continuous development**. You're invited to contribute!

#Alternatives
The following alternatives to **ALox** may be worth mentioning:

**For C++:**
- [boost.Log](http://www.boost.org/doc/libs/1_55_0/libs/log/doc/html/index.html)
- [Google glog](https://github.com/google/glog)
- [Pantheios](http://www.pantheios.org/)
- [log4cplus](https://sourceforge.net/p/log4cplus/wiki/Home/)
- [log4cpp](http://log4cpp.sourceforge.net/)

**For C#:**
- [Apache Log4net](https://logging.apache.org/log4net/)
- [nlog](http://nlog-project.org/)
- CSharp-Source.Net provides an [extensive list](http://csharp-source.net/open-source/logging) of further alternatives.


**For Java:**
- [built-in java.util.logging](https://docs.oracle.com/javase/7/docs/api/java/util/logging/package-summary.html)
- [Apache Log4j](https://logging.apache.org/log4)
- Java-Source.Net provides an [extensive list](http://java-source.net/open-source/logging) of further alternatives.






