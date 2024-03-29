.. title: 04 - include
.. slug: index
.. description: include directive and header files
.. author: Xeverous

So far all presented programs were written in a single file. Most examples will still be (for practical reasons) but it's pretty obvious that any larger, actual program (again, for practical reasons) can not be written in a single file.

So how is it done exactly?

Surprisingly, both C and C++ specifications do not define how code can/should/must be split and/or how it cooperates between different files. The only real thing that governs compilation process is **ODR** (One Definition Rule). As long as ODR is satisfied, any form of separation of code into different files is valid.

History
#######

At first, at times of C being developed (before any standard was made) computers were not sufficiently powerful to compile large (at that time) programs. The solution was to not write too many function definitions in a single file. Each file was compiled separately and then compiled files (containing some intermediate representation) were merged to an executable program with actual machine code.

The compiler was performing many operations blindly - if a function call was encountered and the function was not defined in the current file, it was simply assumed that such function existed somewhere else. If there was any kind of mismatch that wasn't detected during compilation and machine code generation (e.g. different number of arguments given to the function than it expects) it was simply undefined behavior.

Such situation could not last long. It was simply too error-prone. Later function declarations became popular, but just the name and return type, e.g. :cch:`int func();$$$keyword func();` (in C empty parentheses mean *unspecified* parameters). Then *function prototypes* - function declarations that specify parameters, e.g. :cch:`int func(int, int);$$$keyword func(keyword, keyword);`). Compilers started to verify that function calls match their expectations. I have no knowledge where (on the timeline of C's development) C++ started exactly (early as an extension to C) but in C++ fully-informational function declarations existed and were mandatory since the beginning.

To simplify the work and avoid code duplication, people started writing files which contained just function declarations and used the preprocessor :cch:`#include` directive to paste their contents into other files (intended for compilation) that needed these declarations. That's how **header files** were born.

*Whole paragraph:* citation needed.

The C/C++ build process
#######################

You already know that you need to include certain files in order to use certain parts of the C++ standard library. The same thing applies for your code.

There are 2 types of files for C and C++ code:

- header files, which main purpose is to provide necessary information for other files (source files or other headers)
- source files, which main purpose is to implement various compilable entities (mostly functions) that have been declared in header files

The build process instructs the compiler only to compile source files. Each source file :cch:`#include`\ s headers to satisfy ODR (basically provide necessary information) and implements entities which are transformed to machine code.

In other words, headers are files for code shared between source files.

..

    Does it mean that headers are for declarations and sources for definitions?

No. This is an incorrect mental shortcut.

- Some things should be defined in headers. The best example are user-defined types. Almost all code which uses new types defined in code needs to see their definition, otherwise the compiler will not be able to generate machine code to handle them. Types themselves do not form compilable code, but their use in functions does.
- Some things can be declared in sources (or not declared at all), mostly because they are used only within a single file.

Instead, I propose to think of headers and sources in more generic terms such as specification and implementation. The mechanism is quite flexible - **C++ does not impose any strict rules what needs to be in which file. The language doesn't even define what a header or a source file is** - this is just a very strong convention that was formed through practice to make the best use of the preprocessor. **All that really matters is that when code is compiled, ODR is satisfied.**

    So which entities are put where? Is there any convention for it?

There is some convention but nothing is strict. Generally:

- header files:

  - type *definitions*
  - global object *declarations*
  - function *declarations*
  - templates - both *declarations* and *definitions*

- source files:

  - function *definitions*
  - global object *definitions*

This is only a rough guideline, details for specific entities are explained in respective lessons. There is also a detailed cheatsheet. TOWRITE

File naming
###########

The C language uses ``h`` extension for header files and ``c`` for source files.

In C++:

- Source files typically use ``cpp`` extension. Rarely ``cc``, ``cxx`` or others.
- Header files typically use ``h`` or ``hpp`` extension. My recommendation is ``hpp`` because ``h`` is confused by some tools as a C header file, not C++. ``hpp`` is the most common extension that clearly states it's a C++ file. In this specific case my recommendation is in conflict with `CG SF.1 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rs-file-suffix>`_ but `there is an issue where it was discussed <https://github.com/isocpp/CppCoreGuidelines/issues/686>`_ which (at least to me) clearly states there is no consensus in the community.
- C++ standard library headers are an exception, they intentionally have no extension so you can easily differentiate standard library from any other.

.. admonition:: note
    :class: note

    Some standard library headers exist in 2 forms: one with ``h`` extension and one with ``c`` prepended - e.g. ``<stdio.h>`` vs ``<cstdio>``, ``<stdlib.h>`` vs ``<cstdlib>`` (`full list on cppreference <https://en.cppreference.com/w/cpp/header>`_). The former are for compatibility only and additionally have everything placed in global scope (not in :cch:`namespace std$$$keyword namespace`). The latter are a "C++-ified" version of the headers that were already present in C. Newer C++ additions happen only in the latter.

    The status of these headers is discussed in `P2340 <https://wg21.link/P2340>`_.

The main purpose of ``.h`` standard library headers in C++ is the ability to import C code into C++ projects with minimal edits. When writing new projects that are not starting from C code, you should use C++-exclusive headers (the ones without ``.h``). They are cleaner (entities are inside standard namespace) and only these are being updated.

    How about using ``.h`` headers to write polyglot code that compiles in both languages?

This practice has much better alternatives. The main problem with polyglot code is that it is neither full C nor C++. Apart from having reduced set of features, there are syntax constructs that have different meaning in both languages (most notably character literals: they have type :cch:`int` in C but `char` in C++).

If one intends to write a project that is compatible for both C and C++, the predominant approach is to write it in C and only make headers polyglot. This uses the :cch:`extern "C"` feature in C++ that was designed to import code compiled in other languages.

Include directive
#################

The directive behaves as if the contents of specified file were copy-pasted in place of the directive. It's not strictly working as such (compilers can implement preprocessor to be entirely in-memory, without any file operations) but it's a very good mental shortcut of how it works because it's specified to work as if that happened.

The main purpose of the directive is to avoid manual work of copying and pasting code that provides required information. Instead, a header file is written (such as :cch:`<iostream>`) and you can have as many source files as you want, each able to access entire information about I/O stream library with just a single preprocessor statement.

    What if the I/O stream library needs some information too?

Then it includes other headers for itself. Includes work transitively, so if file A includes B which includes C, C content will be visible in any *translation unit* that included A.

You should not rely on transitive includes though. Example: some code uses :cch:`<iostream>` and it also needs to access some mathematical functions from :cch:`<cmath>` but does not :cch:`#include` it. On at least one compiler, I have observed that including :cch:`<iostream>` also provides something (or everything) from :cch:`<cmath>`. But it's only because on this particular compiler implementers of the I/O stream library also needed mathematical functions. If you try to build such project using a different compiler, it may fail due to missing :cch:`#include`.

.. admonition:: tip
  :class: tip

  Do not rely on transitive includes. Include headers for everything that the current file explicitly uses.

Translation Unit
################

A translation unit is basically what the compiler sees after preprocessing. That is, the contents of the specified file + any file it has included (potentially transitively). We could say that only source files need compilation although strictly technically what is being compiled are entire *translation units*.

.. cch::
    :code_path: translation_unit.cpp
    :color_path: translation_unit.color

The example above has 2 translation units:

- one which contains contents of ``hello.hpp``, ``iostream`` and ``main.cpp`` (in this order)
- one which contains contents of ``iostream`` and ``hello.cpp`` (in this order)

..

    Does order of includes matter?

It should not. Some projects may accidentally make themselves suspectible to it if they rely on transitive includes or other misused preprocessor directives. You will learn about such problems later in this chapter.

This mini project should compile and build fine, but it can be improved - ``hello.cpp`` should include ``hello.hpp``. Why? There are few reasons:

- For some code, this is simply required. This will be very prominent once you learn about classes.
- Even if not required, included files can be used to check validity of the source file. Change return type of the function in ``hello.hpp`` to :cch:`int` and try to build the project. The compiler should output an error that function's definition does not match declaration.

.. admonition:: tip
  :class: tip

  If a source file has respective header for its contents, the header should always be included in this source file even if it's not strictly necessary. This allows the compiler to detect many problems.

There are no requirements for specific order of header inclusion (we just list dependencies and if they have their own dependencies *header guards* make redundant includes empty) but there are some benefits for inside-out order - mostly hitting any build errors sooner than later and preventing code from accidentally relying on dependencies of dependencies.

Therefore, I recommend the following order:

- (if the current file is a source file) associated header file
- any header closely related to the code (usually headers from your own project)
- any external library headers if needed in this file
- any standard library headers if needed in this file

This way your project headers will be always parsed first, making sure they are self-contained. If they need some library that you did not include in themselves, build will appropriately fail.

    What if there is a loop within includes (e.g. A includes B which includes A)?

Technically this is possible but in practice, it's as useful as a program which is stuck on an infinite loop. Whatever happens (out of memory error or actual detection of this problem by the compiler) the build surely has no way to succeed. If there is a situation of dependencies within code leading to this, the code must either be reordered or employ *forward declarations* to break some dependencies.

``<>`` vs ``""``
################

There are subtle differences between how preprocessor treats paths given in ``<>`` versus ``""``. Strictly by the standard, both are *implementation-defined* so it's up to the compiler vendor to decide how exactly they work.

By convention:

- ``<>`` should be used for C++ standard library and any other library that has been specified in compiler options
- ``""`` should be used for files local to the project. The search usually starts from the same directory trying a relative path first

Some library projects use ``<>`` for all of their files.

Source layout
#############

There are 2 conventions how a C++ project files should be laid out:

Separate
========

2 same directory trees, one containing headers and one sources.

.. code::

    <root>/
        include/
            cat/
                sounds/
                    meow.hpp
                    purr.hpp
        src/
            cat/
                sounds/
                    meow.cpp
                    purr.cpp

Merged
======

1 directory tree, containing headers and sources next to each other.

.. code::

    <root>/
        src/
            cat/
                sounds/
                    meow.cpp
                    meow.hpp
                    purr.cpp
                    purr.hpp

There are no particulary strong advantages/disadvantages in any of these but it's worth to mention that:

- In separate layout, usually only ``include`` path needs to be given to compiler include search option.
- In separate layout, some headers might be put into ``src`` tree to signify they are not a part of project's public interface (AKA private headers). That is, users (not developers) of the project should only use headers from ``include`` directory.
- In merged layout, the pair of header+source can be extended to contain even more similarly named files, such as ``meow.test.cpp``.
- IDEs and other tools work well with both.
- For many years, there was no significant convention how a C or C++ project should be laid out. You can find many projects which do not stick to any convention. `The Pitchfork proposal <https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs>`_ aims to establish/standarize typical C/C++ project structure.

..

    Do header and source files always come in pairs?

No. This is what usually happens but:

- Some source files do not need headers as nothing uses their code elsewhere. This happens most commonly for ``main.cpp`` and files with tests.
- Some headers do not need sources because they don't contain code requiring compilation. Such headers usually contain only constants, :cch:`inline` definitions or templates (which are implicitly :cch:`inline`).
- Some headers may have multiple source files associated but only one specific source file is compiled depending on the selected platform (one of possible approaches for multiplatform code).
- In most extreme case, some library projects are designed to be header-only. Such libraries don't require compilation and to use them it's enough to just provide path to the include directory in compiler's options. Boost (and many other template-heavy library projects) use this approach as templates by practical reasons have to be in headers and the lack of source files simplifies build management.

:cch:`#include` guidelines
##########################

Suppose that a project presented above has one more file: ``cat/actions/pat.cpp`` and this file needs to access information in ``cat/sounds/purr.hpp``. There are many ways this could be done:

.. cch::
    :code_path: include_guidelines.cpp
    :color_path: include_guidelines.color

- A: very impractical. All of major compilers accept mostly directory paths and ideally there should be only 1 path required per project for its include directory tree. Such approach would also complicate build recipes.
- B: generally it will work, but is annoying and fragile in practice. Paths with ``..`` break when one of the files is moved. Strictly technically, there is nothing about support of ``..`` in paths in the standard.
- C: the preferred and recommended approach. Requires 1 simple compiler option and is very clear where the file is. Many projects which use this approach only use ``<>`` includes.

.. admonition:: tip
  :class: tip

  When writing include directives, prefer root-relative paths to avoid using ``..``. The only widely accepted alternative is sole file name if it's present in the same directory.

Exercise
########

Which files should be included?

.. details::
  :summary: answer

  Only header files.

Which files should be compiled?

.. details::
  :summary: answer

  Only source files (with their includes, forming translation units).

Which files can include other files?

.. details::
  :summary: answer

  Both header and source files.

What is a translation unit?

.. details::
  :summary: answer

  A virtual file that is actually compiled by the compiler. It consists of one source file and all (potentially transitively) included header files.
