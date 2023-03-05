.. title: glossary
.. slug: glossary
.. description: a list of terms common in the C and C++ community
.. author: Xeverous

.. TODO - article with symbol character names

- **ABC** - *abstract base class*. ABCs have at least 1 unimplemented virtual function and can not be instantiated. Some languages offer :cch:`abstract` keyword to force a class being abstract without the need to declare any unimplemented function. In C++ you can do this by declaring at least 1 pure virtual function, possibly pure virtual destructor (:cch:`virtual ~T() = 0;$$$keyword 2func() = num;`). The destructor still needs to be implemented (outside the class).
- |Boost|_ - a collection of over 80 high-quality C++ libraries for a very wide set of purposes, some being state-of-the-art C++. Many have been incorporated into the C++ standard library, with also many proposed for inclusion in future standards. Boost is sometimes referred to as "the second standard library". Majority of Boost libraries are header-only.
- **build** (as a noun) - a ready to use (compiled and linked) program made from source code with certain configuration.
- **CMake** - meta build system and build system generator. Used by various C and C++ projects to generate project files and build scripts. Some IDEs use CMake to build projects or to discover dependencies and their properties (e.g. include paths).
- **ctor** - constructor.
- **compiler** - a program which turns source code (text file) in the given programming language into machine code (executable file, static or dynamic library). Major C++ compilers are GCC, Clang and MSVC.
- **CRTP** - *curiously recurring template pattern*. A C++-specific unique form of static polymorphism where a derived class inherits from base class template instantiated with derived type as the template parameter. Explained in TOWRITE.
- **Cygwin** - a Unix-like environment and command-line interface for Microsoft Windows which provides POSIX functionality on top of the Win32 API. If you want to create native Windows binaries (not requiring MSVC or Cygwin) use MinGW-w64 or Clang.
- |Doxygen|_ - documentation generation tool supporting multiple programming languages. Generates static web pages from comments in the source code. Quite common in C++ projects. Doxygen's comment syntax is based on JavaDoc.
- **dtor** - destructor.
- **errno** - a macro that expands to a thread-local, global variable holding last POSIX error number. Set by many POSIX functions and some functions in the C and C++ standard library. Note that `only 3 constants are mandated by C <https://en.cppreference.com/w/c/error/errno_macros>`_ (EDOM, ELISEQ and ERANGE), `C++ offers many more <https://en.cppreference.com/w/cpp/header/cerrno>`_. See also `a list of error numbers in Linux <http://www.virtsync.com/c-error-codes-include-errno>`_.
- **GC** - `garbage collector <https://en.wikipedia.org/wiki/Garbage_collection_(computer_science)>`_. An automatic cleanup mechanism used in many higher-level languages which do not use RAII. GC simplifies resource management but imposes a performance penalty. Note that GC typically handles only memory while the RAII idiom used in C++ and Rust can handle any resource (e.g. file handles, network sockets).
- **GCC** - originally *GNU C Compiler*, now *GNU Compiler Collecion*. The de facto standard compiler toolchain for C and C++ on most GNU/Linux distributions.
- **final** - a keyword in many programming languages that blocks a method from being overriden or a class from being derived from. In Java, it has additional functionality of preventing assignments (similar to :cch:`const` in other languages).

.. _`FOSS`:

- **FOSS** - *free and open-source software*. The word *free* here `means freedom, not price <https://www.gnu.org/philosophy/free-sw.html)>`_.
- **framework** - a prepared set of tools and code base for certain purpose. Differs from library that it requires a certain application structure and can not be customized beyond creator's intent. Frameworks are more popular in higher level languages while libraries in lower level ones, although both are widely used in various languages.
- **IDE** - *integrated development environment*. Usually an advanced code editor with autocomplete and rich refactor features integrated with build system, compiler and debugger.
- **idempotent** - an operation that when applied multiple times has the same effect as applied only once. Can be used to describe both functional programming (a function where output depends only on the input) and high-level concepts (transactions in online shops should be idempotent to prevent cases where accidentally sent multiple identical requests would commit multiple purchases).
- **immutable** - Something unchangeable, usually some data. In OOP means that a type by design has unchangeable state once constructed. This approach is very common for data shared across threads and strings - they are often implemented with `copy-on-write technique <https://en.wikipedia.org/wiki/Copy-on-write)>`_. Since C++11 the specification for :cch:`std::basic_string` API (on which :cch:`std::string` is based on) implicitly bans COW (non-const overloads of :cch:`operator[]` must be O(1)) in favor of an implementation based on *small buffer optimization*.
- **interface**:

  - (in strict sense) a type that has no data members and containst only (pure) virtual functions. There is no special notion of interfaces in C++ (there is no :cch:`interface` keyword) - the language allows basically unconstrained multiple inheritance and an interface is simply a :cch:`class` that has no non-static data members.
  - (more general) an abstraction specifying communication between 2 distinct elements (code-code or code-human). For example: graphic user interface (layout of buttons on the screen etc.), command line interface (a terminal where the user inputs textual commands) and POSIX interface (system-specific C headers offerred by POSIX-compliant systems).

- **LEWG**, **LWG** - *library (evolution) working groups*. Parts of `the C++ Committee <https://isocpp.org/std/the-committee>`_.
- **ld** - the GNU linker. Part of GCC toolchain.
- **linker** - a program used to link compiled source code files into an executable or a static/dynamic library. Linkers can merge code from different programming languages and embed additional metadata.
- |LLVM|_ - *low level virtual machine*. An open-source library for building compilers and related tools. Backend of the Clang compiler. https://stackoverflow.com/questions/2354725/what-exactly-is-llvm
- **Makefile** - a file with directives for performing incremental builds. Used by *make* command line program. Various IDEs and other tools create makefiles and then call *make* which calls compiler and linker with appropriate arguments. Makefiles can also be used for other incremental command build tasks, for example LaTeX document generation.
- **memoization** - caching (possibly intermediate) function results. Useful for operations where multiple subtasks may be identical, as is in some recursive functions - e.g. the Fibonacci function can result in identical recursive calls multiple times.
- **MinGW** - *minimalist GNU for Windows*. A port of GCC toolchain for Windows (the most popular are `MinGW-w64 distributions <https://www.mingw-w64.org>`_). Builds native Windows 32- and 64-bit executables without MSVC-specific code required such as :cch:`WinMain` entry function.
- **MI** - multiple inheritance, usually referring to a situation when a class inherits multiple non-interface classes - a feature supported only by some programming languages.
- **MSVC** - Microsoft Visual C/C++ compiler.
- |MSYS2|_ - *minimal system 2*. Software Distribution and Building Platform for Windows.
- **NTBS** - *null-terminated byte string*, also called C-string.
- **null** - the lack of object, an invalid memory address. On practically every (if not every) hardware represented by memory address zero. Using (dereferencing) a null pointer is undefined behaviour in C and C++ and typically an exception in other languages. In C represented by the macro :cch:`NULL`, in C++ by the keyword :cch:`nullptr`.
- **OSS** - *open source software*. See also `FOSS`_.
- **PGO** - *profile guided optimization*. Optimizations performed on the base of data generated by performance profiling. Information such as which code paths are more frequent (aka hot/cold code), how many times a given function is called or how much time does it take to run can help compilers optimize the program.
- **pimpl** - *pointer to implementation*, a design pattern in C++, used mostly for reducing coupling and guaranteeing ABI stability. Explained in TOWRITE.
- **pointer** - an object that does not store ordinary data, but holds the memory address of another object (possibly another pointer). In C and C++ pointer types are denoted with ``*``.
- |POSIX|_ - *portable operating system interface*. A standarized interface to create and maintain ABI, API, CLI and other compabilities between operating systems. Windows is the most well-known system that is not POSIX compliant. Cygwin and WSL can be used to create POSIX-compliant layer on Windows.
- **RAII** - *resource aquisition is initialization*, an idiom where resources are managed by classes that implement user-defined constructor and special member functions (copy/move constructor and copy/move assignment operator), which are subject to special optimization rules in C++ - such classes are typically *containers* and *smart pointers*. RAII is the backbone of :s:`memory` resource management in C++ and Rust. Also sometimes referred to as SBRM (*scope based resource management*) or CADR (*constructor acquires, destructor releases*).
- **reference** - an alias to another object. In C++ references are a simpler and safer version of pointers, they do not offer pointer arithmetics. In C++, references must always be initialized and always point to a valid object. In higher level languages references can be null but still do not offer pointer arithmetics.
- **RVO**, **NRVO** - *(named) return value optimization*. An optimization in C++ where the return operation in a function returning expensive local object by value is optimized from copying the object to *moving* it or a zero-cost abstraction. This optimization does not exist in C.
- **segfault** - |segmentation fault|_. A userspace error caused by violating virtual memory access, typically by trying to access memory referenced by a *dangling pointer* or a *null pointer*. Very common way to crash by programs with undefined behavior.
- **SFINAE** - *substitution failure is not an error*. An exploit on the C++ template instantiation mechanism used to disable certain function template overloads and template specializations. A saner version of the feature are *concepts* added in C++20.
- **SIGSEGV** - `a signal <https://en.wikipedia.org/wiki/Signal_(IPC)>`_ raised by the operating system to the program after encountering segmentation fault or similar error.
- **singleton** - a design pattern where a type that is supposed to be instantiated only once as a global object. Often regarded as an anti-pattern. Explained in TOWRITE.
- **smart pointer** - a pointer that automatically manages underlying resource (not necessarily memory). C++ standard library offers smart pointer class templates that model unique ownership (:cch:`std::unique_ptr`) and shared ownership (:cch:`std::shared_ptr`, :cch:`std::weak_ptr`). Additional smart pointers are offered by Boost. https://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one.
- **std** - the namespace name used by the C++ standard library. Every entity except macros is inside this namespace.
- **STL**:

  - (the library) *standard template library*. A major part of the C++ standard library, which itself is sometimes referred to as STL due to its historical significance. STL is still a very important part of C++, somewhat analogic to LINQ in C#, though both differ in their design goals.
  - (the person) Stephan T. Lavavej, a member of the C++ committee that also works on Microsoft's implementation of the STL. See `this reddit post <https://old.reddit.com/r/cpp/comments/c90sxa/whats_the_difference_between_stl_and_c_standard/>`_ for more information.

- **strict aliasing** - an assumption that pointers to *unfamiliar types* (mostly classes which do not share a common base) can never point to the same object (that is, they can not *alias* each other). Strict aliasing allows multiple optimizations based on `type-based alias analysis <https://en.wikipedia.org/wiki/Alias_analysis#Type-based_alias_analysis>`_. Mandated by both C and C++, although there is a lot of code that violates this requirement and thus invokes undefined behavior unless a compiler-specific option like ``-fno-strict-aliasing`` is used. See TOWRITE for more information.
- **this** - in C++, a pointer to the object itself, available in any non-static member function. :cch:`this` is never null.
- **toolchain** - a set of tools used to develop a software project. A typical toolchain includes a text editor, a compiler, a linker and a debugger. Additionally: documentation tools, static analyzers, continuous integration/delivery and more.
- **UDL** - *user-defined literal*. A C++11 feature that allows to define custom suffixes for literals which create objects of possibly user-defined types. Explained in `operator overloading / user-defined literals <link://filename/pages/cpp/tutorials/beginner/xy_operator_overloading/10_user_defined_literals/user_defined_literals.rst>`_.
- **Qt** (read *cute*) - one of the biggest C++ GUI frameworks and set of GUI-related libraries. Loved by many for its backwards compatibility, mature and large libraries, advanced tooling and rich platform support. Hated by many for its non-idiomatic/non-conventional use of C++, complicated build system involving code generation and reliance on macros.
- **Qt Creator** - an IDE from the Qt project. Has integrated support for Qt libraries and can also be used for non-Qt C++ projects.
- **vtable** - |virtual method table|_. In a typical implementation of runtime function dispatch, each polymorphic object holds a pointer to vtable specifying method implementations for its class.

.. _Boost: https://www.boost.org
.. |Boost| replace:: **Boost**
.. _Doxygen: https://doxygen.nl
.. |Doxygen| replace:: **Doxygen**
.. _LLVM: https://en.wikipedia.org/wiki/LLVM
.. |LLVM| replace:: **LLVM**
.. _MSYS2: https://www.msys2.org
.. |MSYS2| replace:: **MSYS2**
.. _POSIX: https://en.wikipedia.org/wiki/POSIX
.. |POSIX| replace:: **POSIX**
.. _segmentation fault: https://en.wikipedia.org/wiki/Segmentation_fault
.. |segmentation fault| replace:: *segmentation fault*
.. _virtual method table: https://en.wikipedia.org/wiki/Virtual_method_table
.. |virtual method table| replace:: *virtual method table*
