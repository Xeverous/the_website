<!--
.. title: glossary
.. slug: glossary
.. description: a list of terms common in the C and C++ community
.. author: Xeverous
-->

TODO - article with symbol character names.

`ABC` - abstract base class. ABCs have at least 1 unimplemented virtual function and can not be instantiated. Some languages offer `abstract` keyword to force a class being abstract without the need to declare any unimplemented function. In C++ you can do this by declaring a virtual destructor. You still need to implement it though. More in TODO tutorial link.

[`Boost`](https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries)) - a collection of over 80 high-quality C++ libraries for various purposes. Many have been incorporated into the C++ standard, with also many proposed for inclusion in future standards. Boost is sometimes referred to as "the second standard library". Most Boost libraries are header-only.

`build` (as a noun) - a ready to use (compiled and linked) program made from source code with certain configuration.

`CMake` - meta build system or build system generator. Used by various C and C++ projects to generate project files and build scripts. Some IDEs use CMake to build projects or to discover dependencies and their properties (eg include paths).

`ctor` - constructor.

`compiler` - a program which turns source code (text file) in the given programming language into machine code (executable file that can be run). Major C++ compilers are GCC, Clang and MSVC.

`CRTP` - curiously recurring template pattern. Allows a unique form of static polymorphism. TODO tutorial link.

`Cygwin` - a virtual environment layer allowing to run POSIX compliant programs on Microsoft Windows. Able to run programs using UNIX interfaces.

`Doxygen` - documentation generation tool supporting multiple programming languages. Generates static web pages from comments in the source code. Quite common in C++ projects.

`dtor` - destructor.

`errno` - thread-local, global variable holding last C error number. Very rarely used in C++. [Error numbers list](http://www.virtsync.com/c-error-codes-include-errno). Note: only 3 values are defined by the C standard, rest is implementation defined but consistent across all POSIX compliant systems.

`GC` - garbage collector. A side process cleanup mechanism used in many higher-level languages which do not use RAII. GC simplifies resource management but imposes a performance loss and some restrictions upon the programming language.

`GCC` - originally "GNU C Compiler", now "GNU Compilers Collecion". The de facto standard compiler toolchain for most GNU/Linux distributions.

`final` - A keyword which has practically the same functionality in many languages. In C++ it is not technically a "keyword" but that is a minor detail. Depending on the context it is either preventing a class to be inherited from or preventing a virtual function to be overriden in descendant classes. In Java, it has additional functionality of preventing assignments (similar to `const` in other languages).

`FOSS` - free and open-source software. "free" here can have 2 meanings: zero price but more importantly freedom - the fact that FOSS is done for users and should not contain any aritifcial limitations (e.g. constantly requiring internet connection to send usage statistics).

`framework` - a prepared set of tools and code base for certain purpose. Differs from library that it requires a certain application structure and can not be customized beyond creator's intent. Frameworks are more popular in higher level languages while libraries in lower level ones, although both are widely used in various languages.

`IDE` - integrated development environment. Usually an advanced code editor with autocomplete and rich refactor features integrated with build system, compiler and debugger.

`interface` - 1. A type (class) that has no member objects and contains only pure (unimplemented) virtual functions. There is no special notion of interfaces in C++ because there are no restrictions on members and inheritance. See TODO turorial link. 2. (more general) A set of rules defining communication between some systems or humans. For example graphic user interface (layout of buttons on the screen etc), command line interface (a terminal where the user inputs textual commands) and POSIX interface (system-specific C headers offerred by POSIX-compliant systems).

`LEWG`, `LWG` - library (evolution) working groups. Parts of the [C++ Committee](https://isocpp.org/std/the-committee).

`ld` - the GNU linker. Part of GCC toolchain.

`linker` - a program used to link compiled source code files into an executable or a shared/static library. Linkers can merge code from different programming languages and embed additional info.

[`LLVM`](https://en.wikipedia.org/wiki/LLVM) - low level virtual machine. An open-source library for building compilers and related tools. Backend of the Clang compiler. https://stackoverflow.com/questions/2354725/what-exactly-is-llvm

`makefile` - a file with incremental build directives used by GNU make command line program. Various IDEs and other tools create makefiles and then call make which calls compiler and linker with appropriate arguments. Makefiles can also be used for other incremental command build tasks, for example LaTeX document generation.

`MinGW` - Minimalist GNU for Windows. `MinGW-w64` is the most commonly used GCC toolchain port for Windows. Builds native Windows 32 and 64 bit executables without MSVC-specific code required such as `WinMain` entry function.

`MI` - multiple inheritance.

`MSVC` - Microsoft Visual C/C++ compiler.

`MSYS2` (minimal system) - package manager for GNU toolchains for Windows. [Used by Qt](https://wiki.qt.io/MSYS2).

`nullptr`, `NULL`, (in other languages `null` or `nil`) - the lack of object, a null (empty, invalid) memory address. On practically every (if not every) hardware represented by address `0x00000000`. Using (dereferencing) a null pointer is undefined behaviour in some languages (C, C++) and an exception in higher level ones.

`OSS` - open source software.

`PGO` - profile guided optimization. Optimizations performed on the base of data generated by performance profiling. Information such as which code paths are more frequent (aka hot/cold code), how many times a given function is called or how much time does it take to run can help compilers optimize the program.

`pimpl` - pointer to implementation (sort of design pattern), used mostly for ABI stability. TODO tutorial link.

`pointer` - a variable that does not store ordinary data, but holds the address of another variable. Pointers can be nested (that is, it is possible to create a pointer to a pointer). In C and C++ pointer types are denoted with `*`.

`POSIX` - portable operating system interface. A standarized interface to create and maintain ABI, API, CLI and other compabilities between operating systems. The only largerly used OS which is not POSIX compliant is Windows. Cygwin can be used to create POSIX-compliant layer on Windows.

`RAII` - resource aquisition is initialization (a C++ idiom). Objects allocating resources are responsible for their cleanup (done by implementing custom destructors). Idiom requires types to implement precise resource ownership models allowing move semantics and compile-time cleanup decisions. RAII is the backbone of C++ and Rust resource management. Term sometimes referred as SBRM (scope based resource management) or CADR (constructor acquires, destructor releases).

`reference` - an alias to a variable or constant. Does not offer all possibilities of pointers, but it safer and easier to optimize. In C++, references must always be initialized and always point to valid object (you can not reference references). In higher level languages references can be null but still do not offer pointer arithmetics.

`RVO` (or `NRVO`) - (named) return value optimization. In C++ function returning local temporaries by value are optimized out or to at least move operations. This allows to return any big object from the function without any unnecessary copies. Note: this optimization does not exist in C.

`segfault` - [Segmentation Fault]((https://en.wikipedia.org/wiki/Segmentation_fault)). Error caused by dereferencing an invalid poitner (not necessarily a null pointer) or violating virtual memory access. Very common way to crash for programs with undefined behavior.

`SFINAE` - substitution failure is not an error. Exploit on the C++ template instantiation mechanism used to disable certain implementations based on the type or value properties. Concepts can leverage SFINAE and offer syntax sugar for various template tricks but are mostly aimed towards generic type-safe programming.

`SIGSEGV` - [Signal](https://en.wikipedia.org/wiki/Signal_(IPC)) thown to the program after encountering segentation fault or similar error.

[`singleton`](https://en.wikipedia.org/wiki/Singleton_pattern) - A type that is supposed to be only instantiated once. Often regarded as an anti-pattern.

`smart pointer` - a pointer that <del>is smart</del> automatically manages underlying resource (not necessarily memory). C++ standard library offers classes for unique ownership model (`std::unique_ptr`) and shared ownership model (`std::shared_ptr`, `std::weak_ptr`). Additional and legacy smart pointers are offered by Boost. [SO question](https://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one).

`std` - the C++ standard library namespace. Every identifier except macros is inside this namespace. More namespaces are possible in the future.

`STL` - 1. Standard template library. A major part of the C++ standard library. Often the C++ standard library itself is (technically incorrectly) referred to as "the STL" - this is due to historical reasons. 2. Stephan T. Lavavej, a member of the C++ committee. https://old.reddit.com/r/cpp/comments/c90sxa/whats_the_difference_between_stl_and_c_standard/

`strict aliasing` - an assumption that pointers to *unfamiliar types* (eg not sharing same inheritance tree) can never point to the same object. All variants of `char` and `void` pointers are excluded from this rule (because they are used for unknown type reads/writes). Strict aliasing allows multiple optimizations because compiler can assume certain data is not overriden between various instructions. Strict aliasing is very highly encouraged by the C++ standard. Enabled by default in all major compilers and requires certain flag to compile code which violates this rule. TODO SA article link

`this` - In C++, a pointer to the object itself, available in any non-static member function. `this` is never null.

`toolchain` - a set of tools (programs, scripts, files) used to build a project. The typical minimal toolchain would invole a text editor, compiler and debugger. Bigger projects additionally use documentation tools, static analyzers, continuous integration tools and more.

`Qt` (cute) - One of the biggest C++ GUI frameworks and set of GUI-related libraries. Loved by many for its backwards compatibility, large libraries, advanced tooling and rich platform support. Hated by many for its non-idiomatic/non-conventional use of C++, complicated build system which often involves code generation and unportable language extensions.

`Qt Creator` - IDE from the Qt project. Has integrated support for Qt libraries but can also be used for ordinary C++ projects.

`vtable` - [virtual method table](https://en.wikipedia.org/wiki/Virtual_method_table). In typical runtime dispatch implementation, each object of a class that implements virtual function(s) has embedded vtable pointer(s) inside its memory representation.
