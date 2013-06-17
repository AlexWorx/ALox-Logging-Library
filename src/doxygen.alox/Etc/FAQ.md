\page alox_faq  FAQ - Frequently asked Questions for ALox


\section alox_faq_the_name_alex       Why the name "ALox" and how is it pronounced?

The English term "log" is known. Now "logs" is the plural. As English pronunciation is always
a little unspecific and volatile, you could write the word "logs" as "lox" easily without
changing the pronunciation.  Now, as we were looking for some artificial new word for the project,
we loved to turn "logs" into "lox". 

But then we wanted to add the "A". This tells you: **This is *class a* logging!**
Got it? So, please pronounce it in two words, with a separately spoken "a" like in "a car" or "a cat".

*Note: This explanation also proves that the name has nothing to do with this guy called "Alex", because 
his name pronounced in one word!)*




\section alox_faq_bauhaus             What is "Bauhaus Code Style", please? 

Well, if you are not familiar with it, checkout [Bauhaus](http://http://en.wikipedia.org/wiki/Bauhaus)
on Wikipedia (and yes, we are a German team). 
Bauhaus in Software for us means: *Simplicity*, *platform independence*, *efficiency* and *speed*. While we are
embracing all modern concepts of software development (the same as we love modern art, romantic,
surrealistic, pop art, punk and rock!) we consider Bauhaus the right approach for *core libraries* - what ALox definitely is.

While applications and tailored software might have other goals in respect to life cycle, budget, portability
and such, we think the design of a *core library* which is embedded in many projects and used by different teams should 
follow certain rules. For example, we are avoiding memory allocations as much as possible. In fact, after
ALox performed some few log statements, the next statements will probably allocate/dispose just ZERO new 
objects! (Ok, some unavoidable platform depended things, like a *DateTime*  object in C# to receive the current system
time, which makes the *DateTime* class in C# in turn a great sample for non-efficient, non-Bauhaus code style that should
never have gone into a core library called *System*!). 

As a consequence, you will sometimes see code pieces where you might think: "Hmmm, they missed to use
this great language feature XYZ here". Well, send us a note, but the answer will probably be: "This is not
available in that other platform and we want to keep similar simple code bases.", or "Well, this would look
nice in code, but would increase down execution time."

Mean people (e.g. that bright fellow from Berlin) might say: You just do Bauhaus, because you can't do Pop Art. Maybe they are right.
At least we love Bauhaus and we love to do efficient libraries and that's why we do!

PS: If you can tell us a way how to get the current system time in C# without the allocation
of a *DateTime*  object (what *DateTime.Now* does), then please send us an Email!











