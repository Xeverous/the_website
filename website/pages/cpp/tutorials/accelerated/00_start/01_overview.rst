.. title: 01 - overwiev
.. slug: 01_overview
.. description: what makes C++ C++
.. author: Xeverous

First, let's see what are the core specifics of C++ as a programming language. Basically, what makes C++ C++. These should be fairly obvious.

type system
###########

Unlike dynamically typed languages such as Python or Java Script, C++ is statically typed. Absolutely every object has a type determined at compile time. It may not be exactly the same type as the type of the object at runtime (which is the case of inheritance and derived classes) but it always clearly defines all possible actions with the object at compile time.

build system and runtime
########################

C++ requires compilation, in other words, it needs to be translated from source code to machine code. This is the process at which compiler errors appear and optimizations happen. Later you will learn about all implications of this process.

Few important bits:

- C++ compiles to pure native code for the given platform. Unlike Java or C#, it does not require any virtual machine. It can run on the sole kernel layer that the target operating system supplies and directly invoke its functions.
- The target platform does not need to be any specific operating system - C++ can be compiled to run on the hardware itself. This is known as a *freestanding implementation* and is most often used in embedded software projects where the entire code that runs on the device is a single, statically-linked executable. In such case C++ has no differences in its behavior but the standard library is severly limited as many required things are simply not present on the bare metal.
- C++ has many dedicated features to write portable code that works on many or all supported platforms. Very few things actually require separate implementation and are easily abstracted.
- C++ can run practically anywhere. You may have heard the same statement about many other languages, but sorry, it was probably a lie. Taking many virtually-hosted languages as an example - they do not run on any platform, they run only on a single platform - their virtual machine. By "C++ can run practically anywhere" I mean:

  - hardware which does not have floating-point support
  - hardware which does not have dynamic memory, that is, everything must be stack allocated and anything that depends on dynamic allocation (:cch:`malloc()` and related stuff) is not possible
  - IBM-specific hardware that uses `EBCDIC <https://en.wikipedia.org/wiki/EBCDIC>`_

low-level access
################

Strictly formally, even C is a high-level language because it allows to write multiplatform code and many of its constructs do not map 1:1 to the machine code and may be arbitrarily transformed by the compiler as a part of program optimization. But because so many programmers are working on a much higher level today, the common meaning of "low-level programming" is often changed from "1:1 assembly abstraction" to "explicit use of pointers".

Of course just because C++ allows such things it does not mean they should be used all the time. The lower level code, the more it is prone to errors. C++ standard library already takes care of many such tasks. The tutorial will first explain how to use such functionality from the standard library and only then it will move to explaining how to implement it. It is very important that you do not dive deeply into hard topics at the start as they are the main cause of bad teaching and overall frustration with C++.

  Wait, are you saying that we will not learn pointers before using strings, arrays, etc.?

Yes. There is a common misconception that you need to learn C before C++. **Doing so is not only unnecessary, but also may be a disadvantage** if a person sticks too hard to idioms learned in C. 99% of C code is valid C++, but in 99% of times it is bad C++ (possibly resulting in compiler warnings). People are learning Python without learning CPython implementation, people are learning Java Script without understanding how browser works, people are using refrigerators without understanding how compressor works, people are driving cars... I think you get the point. The only needed thing is *abstraction* and in your case you should be already familiar with the term.

Also, be aware that C++ is not a strict superset of C. While most of the code is indeed compatible, sometimes it has slightly different meaning and resulting behavior. In C++ the primary use of C-like code is to implement higher-level abstractions for error-prone tasks that can be later reused without even understanding what is inside. You have already done such reuse with the string class in a different language, so you should have no problems with using :cch:`std::string` in C++ without detailed knowledge about underlying implementation.

resource management
###################

Read the section title again. It is resource management, not memory management. It is a broader topic.

Virtually hosted languages deal with memory management by garbage collection and/or reference counting. The topic gets interesting when the resource is not memory (e.g. file handle): some languages do not have any dedicated feature for such case and simply require to manually manage the resource (just like in C!); some languages offer a scope-based handling mechanism (e.g. :cch:`using` in C# or :cch:`with` in Python).

If you are already familar with scope-based resource management - good, because **C++ does it everywhere by default**. Constructing an object in C++ is inseparable from its destruction unless you go to a lower level by using explicit object creation/destruction and/or resource management features.

language philosophy
###################

Several languages have a certain philosophy behind them in order to encourage specific usage patterns.

For example, Python has the aim to provide exactly one way to do any certain task and it should be fairly obvious.

C++ philosophy and goals have been described in `Direction ISO C++ <https://wg21.link/p2000>`_ and they mostly are:

- support for low-level hardware and platform features
- support for multiple programming paradigms
- zero-overhead abstractions
- static type safety and resource safety
- long-term stability
- fairness between the standard library and the programmer

The last point might be a bit unclear so let's have a look at a very offending example: ``+`` in Java. Java does not have operator overloading, yet string objects can be concatenated using this operator. This is exactly what C++ always tries to avoid - making the standard library superior in power just because it is made by those who make the language. When C++11 added range-based loops (AKA for-each loops) it did not add them just for the standard library. It added an implicit interface than can be satisfied by any code and the standard library also makes use of this interface. Thanks to such design, you can implement 99% of C++ standard library from scratch and need only few intrinsic features (which usually are compiler extensions) to implement the remaining 1%. Very few programming languages can have their standard libraries implementated in them, most are simply implemented in C or C++ for this reason.
