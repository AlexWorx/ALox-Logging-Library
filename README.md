##ALox Homepage ##
Please find all about the **ALox Logging Library**, including

* **Tutorials**
* **Tutorials**
* **User manual**
* **Reference documentation**
* **FAQ** and the
* **Change log**

at the [ALox Homepage](http://alexworx.github.io/ALox-Logging-Library).


##Overview ##

ALox is a small and efficient software library that provides an ecosystem to support structured and organized log output.

ALox is available as [ALox for C++ 11](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/cppmainpage.html), [ALox for C#](http://alexworx.github.io/ALox-Logging-Library/cs_ref/csmainpage.html) and [ALox for Java](http://alexworx.github.io/ALox-Logging-Library/java_ref/javamainpage.html).

To reach this goal, ALox is featured by **ALib** (see ALib for [C++](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/namespaceaworx_1_1lib.html),[C#](http://alexworx.github.io/ALox-Logging-Library/cs_ref/namespacecs_1_1aworx_1_1lib.html),[Java](http://alexworx.github.io/ALox-Logging-Library/java_ref/namespacecom_1_1aworx_1_1lib.html)), which is a basic utility library that among other goals
provides *'source-compatible'* types for the three languages.

ALox attempts to make logging as easy and lightweight as possible. We want you to **stop adding temporary debug output lines** into your code. Instead, write (with less effort!) short, nice and readable *ALox statements* that live in your code as if they were comment lines. Let ALox do the rest: Add meta information to the output, format the output, filter output based on verbosity level and based on your current topic of interest. Finally, get it all *pruned* out of your release executable, same as your source comments.

On the other end of the list, ALox  enables **release logging** for productive applications to collect mission critical **metrics from the field**.

##Features##

* **Open source**, MIT License.
* Jump-start **tutorials** for [ALox for C++](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/cpptutorial.html),[ALox for C#](http://alexworx.github.io/ALox-Logging-Library/cs_ref/cstutorial.html) and [ALox for Java](http://alexworx.github.io/ALox-Logging-Library/java_ref/javatutorial.html)) and **Sample Projects**.

* **Auto-configuration** (if not configured by your code) based on OS (GNU/Linux, Windows) and **detecting IDE** (VStudio, Eclipse, QTCreator, etc.). Minimal intrusiveness in respect to *cluttering* your code and what you need to make it really work.

* Formatted, **colorful, configurable log output** with support for ANSI compatible consoles and Windows OS consoles.

* Log lines **'clickable' in IDE** to jump to the corresponding source code line (depending on IDE).

* Automatic collection of **meta information** like time stamp, time-difference to previous log, executing thread, caller information (source file, line number, class, method, etc.), domain (the 'topic' of the log output)

* **Hierarchical 'Log-Domains'**, (like for example "MYAPP/UI", "MYAPP/DATABASE" that allow the classification of different log statements into user defined topics. Such domains can be controlled (recursively) at runtime to allow the programmer to concentrate on the area of current interest.

* Defaulting 'Log-Domains' for **source scope**, like *file*, *class*, *method*, which allows to omit the log-domain parameter from the log statements (again: leads to short, clean and readable log statements).

* Support for **CMake**, **Eclipse**, **Visual Studio**, **QT Creator**, **Mono Develop** in combination with **GNU/Linux**, **Windows**, **Windows Phone** and **Android**. (Windows Phone in current versions not tested any more). Porting to other platforms should be easy.

* Very **fast** to minimize runtime overhead of logging (We just broke our former record and did 1 million log lines in a second, including meta information. This was of-course the C++ version doing release logging on release executable).

 * Automatic removal, aka **'pruning'**,  of *debug-log* statements from release code mostly without the need of preprocessor if/endif code  cluttering. Optionally also automatic pruning of *release-log* statements. (In Java: implemented using [Proguard](http://proguard.sourceforge.net), with provision of ready to use configuration files.

* Multiple **parallel log streams** with different *filters* and verbosity levels, e.g. for logging to the console and in parallel into a file.

* **Extensible** with own loggers, which enables dedicated "data drains" (e.g. databases or Internet services) and custom output formatting. ALox provides a simple programming interface and internal architecture that is easy to learn, not overloaded by 'factories' and 'factory factories' ;-)

* **Code markers** for debug logging (get pruned) to allow back tracing of conditions that happened
  previous to a log statement. (This is useful for example within exception handlers.)

* **Conditional logging** (similar to assertions).

* Automatic (OK, half-automatic :-) mapping of thread IDs to **readable thread names**

* **LogTools** (in C# and Java) for

     * Recursive **logging of complex types** with one line of code using *class inspection/reflection*. Variable recursion depth and detection of cyclic references.
    * Logging **Exceptions** (recursively with inner exceptions)
    * Logging **XML trees**

* C++ version accepts arbitrary **3rd party string types**. No need to convert, e.g. a *QString* before logging it although ALox is not built on QT! This goal was reached by underlying A-Worx utility library *ALib* (open source, MIT License) which greatly [solved that problem](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/namespaceaworx_1_1lib_1_1strings.html) using some *template meta programming* to relieve us from the (disastrous) string mix in the C++ world.
  On the same token, conversion of **user defined types** to loggable (string) objects is supported. After implementing the conversion once, you can just throw your custom types into ALox log statements, even as a part of a concatenated log message.

* and finally: ALox is under **continuous development**. You're invited to contribute!




