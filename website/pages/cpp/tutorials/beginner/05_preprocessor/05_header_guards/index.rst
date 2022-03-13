.. title: 05 - header guards
.. slug: index
.. description: header (include) guards
.. author: Xeverous

Let's recall the example multi-file program from the previous lesson. This time we will introduce multiple problems into the project in order to observe build errors and explain certain aspects of the C/C++ build process.

.. admonition:: warning
  :class: warning

  Multiple examples in this lesson intentionally violate ODR (One Definition Rule). Most of such violations are technically *undefined behavior* so a conforming implementation may not detect all such problems or produce very different errors.

Build process
#############

Before we begin, you need to understand most important steps in the process of building a C/C++ project.

Simplified list (very detailed list on `cppreference page <https://en.cppreference.com/w/cpp/language/translation_phases>`_):

- comments are removed
- preprocessor: code (treated as text) is altered and loses all preprocessor directives
- compilation: translation units are transformed to intermediate build object files (usually named ``*.o`` or ``*.obj``)
- linking: separate object files are merged by the linker to form an executable or a static/dynamic library file

If you define something non-:cch:`inline` multiple times in the same file, you will get a compilation error. But if such problem is across files, in most implementations such ODR violation will be caught on the linking step - in such case the problem happens between different translation units.

.. admonition:: note
  :class: note

  Many linking stage errors mention the term *reference*. This is different from C++ reference qualifiers (:cch:`&` and :cch:`&&`). By *reference*, the linker means "usage of specific *symbol*".

..

    What is a symbol?

A symbol is a single entity for the linker, usually some intermediate code attached to a *mangled name* of a specific C/C++ entity that needs compilation. So if the linker outputs an error "undefined reference to ..." it means that a definition of specific entity was not found.

    What is name mangling?

Name mangling is transformation of ordinary entity names into ones that can be understood and differentiated by the linker. Generally, linkers work on lower level than the programming language and since they don't understand various high-level features that can result in same or complex names, they need a mechanism to differentiate them. For more information, see `Wikipedia article about name mangling <https://en.wikipedia.org/wiki/Name_mangling>`_.

Undefined reference
###################

To trigger this linker error a single file is enough but to illustrate a more realistic problem, we will comment out function definition to simulate typical build misconfiguration (missing source files, not everything compiled).

.. cch::
    :code_path: undefined_reference.cpp
    :color_path: undefined_reference.color

.. code::

    /tmp/ccQJjzeS.o: In function `main':
    main.cpp:(.text+0x5): undefined reference to `write_hello()'
    collect2: error: ld returned 1 exit status

The error appears because some entity (a function in this case) was ODR-used (used in a way which requires definition) but the definition was not provided. The same error can appear if you try to use an external library and do not link to library's compiled code in the build process.

.. admonition:: note
  :class: note

  Compilers and linkers typically automatically link C++ standard library and require a specific option to disable it. For any other library, the situation is reverse (an option required to link it).

Multiple reference
##################

This error usually appears when:

- Some code refactoring has been done and 2 copies of the same entity were left present in different files.
- 2 different functions accidentally have been given the same name.
- The project contains multiple subprojects and at least 2 of them link to the same external library with incompatible settings.

To trigger the error, we will simulate a mistake in refactoring and attempt to compile 2 files with definition of the same function:

.. cch::
    :code_path: multiple_reference.cpp
    :color_path: multiple_reference.color

.. code::

    /tmp/ccb9JA6l.o: In function `write_hello()':
    hello.cpp:(.text+0x0): multiple definition of `write_hello()'
    /tmp/ccfsecFJ.o:main.cpp:(.text+0x0): first defined here
    collect2: error: ld returned 1 exit status

In such situation the programmer must figure out what's causing multiple definitions as it will affect the solution:

- refactoring - remove redundant code
- accidental same name - rename something
- duplicated dependencies - make changes in project build recipe (this is outside C++ code)

The most helpful information in such problem is usually contained within linker error: places (files) from which each definition is coming from.

Multiple inclusion
##################

As you should know now, some headers can be included transitively. But what happens when because of this a specific header gets included multiple times? Remember, headers are not just for declarations (which by ODR can be repeated) but also for anything that is not immediately compiled, which includes some definitions.

One particulary good example are type definitions. Defining a type does not immediately produce any compilable code. It is rather a specification how exactly code which manipulates objects of this type should behave. But defining a type multiple times is an ODR violation.

To illustrate, here is an example that defines a type and accidentally includes its definition multiple times:

.. cch::
    :code_path: multiple_inclusion.cpp
    :color_path: multiple_inclusion.color

.. ansi::
    :ansi_path: multiple_inclusion.txt

The main file included ``power_state.hpp`` and ``to_string.hpp`` which indirectly included ``power_state.hpp`` too. This resulted in having duplicate contents of ``power_state.hpp`` in ``main.cpp`` file.

You could probably think of a convention how to split/separate code so that such situations don't arise but it would be very annoying in practice to track code dependencies of each file.

Header guards
#############

We can create a mechanism that automatically prevents accidental duplicate inclusion through preprocessor identifiers. The solution is simple: wrap entire contents of each header file between :cch:`#ifndef`, :cch:`#define` and :cch:`#endif` directives:

.. cch::
    :code_path: header_guards.cpp
    :color_path: header_guards.color

How it works? Each time a file is included, the preprocessor is required to check if a specific identifier has been defined. At first inclusion, it's not. At any later inclusion, it has been defined so entire content of the file is skipped. Because each header was given a unique identifier and separate translation units have separate preprocessing, any header content is parsed exactly once.

.. admonition:: note
  :class: note

  This specific form of preprocessor directives is known as **header guards** and **include guards**.

The identifier must be unique for each header, so to guuarantee uniqueness it usually consists of the company name and/or project name, root-relative file path and sometimes a date/time when it was created.

    Why source files did not get these directives?

Because only header files are supposed to be included. Only header files are shared between *translation units*.

Alternative guards
##################

Since header guards are a such often used mechanism, many compilers implemented :cch:`#pragma once` to make it easier. Pragmas are special subset of preprocessor directives intended for implementation-defined extensions (see `cppreference page about pragmas <https://en.cppreference.com/w/cpp/preprocessor/impl>`_). An example header then looks like this:

.. cch::
    :code_path: pragma_once.cpp
    :color_path: pragma_once.color

The usage is much simpler - less code, no unique identifier required and no :cch:`#endif` at the end of the file. The only disadvantage is that pragmas are not strictly standard. On the other hand, personally I had never any problems with :cch:`#pragma once` while I have observed many people (including myself) get into errors after broken traditional header guards (usually due to missing :cch:`#endif` or non-unique identifier).

There were some attempts to standarize :cch:`#pragma once` as it's probably the most common preprocessor extension but ultimately they failed. Reasons were many but mostly because each implementation uses different way of veryfying that a file is unique and no universal solution could be agreed upon. Standarizing it as "implementation-defined solution" makes very little sense because all pragmas already work this way. Even though the feature remains an extension, many projects use this type of guard for it's simplicity and very widespread support.

Recommendation
##############

All headers should be guarded, even if they are included only once in the entire project.

As for which type of guard to use - the choice is yours depending on whether you prefer absolute standard conformance or simpler code and convenience. Use one and be consistent.
