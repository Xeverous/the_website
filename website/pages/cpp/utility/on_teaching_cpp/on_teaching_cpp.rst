.. title: on teaching C++
.. slug: index
.. description: common mistakes in teaching C++
.. author: Xeverous

C++ is a hard language. As a C++ programmer, I really get it. But many teachers make it much harder than it actually is. This article aims to list very common mistakes in teaching C++.

- If you are a student, this article should help you with argumentation towards (potentially incompetent) teachers. You should have much easier time explaining why your teacher is bad or where does the feeling of low quality learning material comes from.
- If you are a teacher, well, I have bad news for you... On the other hand, if you do get criticized, the good news is that you can improve a lot.

teaching C first
################

We start at the absolutely biggest offender. It usually starts in a situation where:

- Some or all students already know C.
- The teacher already knows C and is just learning C++ while also teaching it.
- Some or all students and/or the teacher fall into the misconception that C++ is a superset of C (it is not) and think C needs to be taught first.
- The learning material has already been prepared over time as things were added and no one ever questioned why chronological order is used.

All of these incentivize the very bad thing: the feeling that C needs to be taught first. Why is it bad:

- Hipocrisy. Inconsistency. Teachers do not require students to learn data structures and C before learning Python, which is based upon them. Teachers do not require students to learn garbage collection algorithms before they learn any GC-based language. Why do such approach towards C++?
- The whole idea of "you must first understand how it was built to use it" is a huge error. The whole human world is made so that you do not need to know all the details in order to use something - just see how few year old kids learn to use every possible household device, without understanding even basic physics. I can easily bet that a huge number of adults don't understand how a fridge works, yet they have no problems using one every day. If you respond to this like "but these things are designed to be used without care for details" - you are right. The exactly same principle is present in C++ - stuff like :cch:`std::string` is designed to be used without complete knowledge of how it is implemented.
- The whole idea of "you should learn it in the order it was made" is another huge error.

  - When you start to learn a game, do you read its instruction for the first edition and then all the changes that have been made? No. You read the introductory chapter and slowly move towards more complex game mechanics. If something was changed during game history (balancing, design, optimizations, extensions, etc.) it should never directly affect teaching order. New things shouldn't be appended to the learning material - they should be integrated where their difficulty and related mechanics are appropriate.
  - Fortran came before C. Do C teachers teach Fortran first? How about assembly?
  - C++ actually builds on 2 languages: C and Smalltalk. Do teachers teach Smalltalk before C++? Do teachers even know what C++ picked up from Smalltalk? Apparently the C parts (especially grammar) were much easier to notice.
  - JavaScript was created as an alternative to (now defunct) Java Applets. Should we learn Java (including Applets technology) before learning JavaScript?

As a result of teaching C first:

- The material is longer.
- The material starts with very steep learning curve by introducing all the complex stuff at the same time (syntax, pointers, build process, math concepts, backwards compatibility problems).
- **The material starts with C-related content that will be needed to be later "untaught" when students meet modern C++**, which has replaced and/or redefined a lot of C habits.
- Students stick to C conventions in C++, which results in a ton of frustration once compiler does what C++ allows it to do.
- Students do not see the true benefits of C++.
- Students are taught finely-grained C stuff, which is performant but trust me - performance is irrelevant for beginners. They want simplicity and slowly increasing difficulty. They won't feel bad if you showcase them the easy way and tell "this is not performant in all cases, for more complex situations you will need to use more complex features" - they actually expect such stuff at the beginning.

problems caused by teaching C first
===================================

- Students stick to C habits and it's a hard time for them when C++ redefines them.
- Students experience all of the C backwards compatibility cruft (grammar anomalies, unsafe type system, language history (which at this point is very boring)).
- Students constantly think and fear of pointers, compiler errors and any kind of bug caused by undefined behavior.
- Once noticed C++ power mechanisms (such as :cch:`std::string` and templates), they immediately abandon previously showcased material (such as :cch:`char*` and macros) because they find C++-specific stuff to be easier to use and learn. Students wonder why they could not use these at the start.
- Students miss a ton of simple and powerful stuff that makes ++ in C++. Stuff that is easily showcased and easily remembered. Stuff with which you can start making simple programs instead of dying in depression caused by reading :cch:`printf` documentation after a compiler error.

stuff to avoid at the beginning
===============================

- :cch:`printf` and :cch:`scanf`
- any kind of pointer usage (including C-style arrays and :cch:`char*` strings)
- :cch:`new` and :cch:`delete`

.. admonition:: Note
    :class: note

    I'm not advocating that these things are bad. I'm not trying to state that all C++ equivalents have better performance or that they are always better. I'm not stating that these should never be taught. I'm stating that these things should not be at the beginning of the learning material. You (as a teacher) should not need to draw tons of diagrams and explain how pointers work just to explain hello world code.

printf / scanf
--------------

Why is it bad for very first lessons?

- :cch:`scanf` requires to explain pointer arguments.
- Both functions are not type-safe.
- Both functions require to explain buffers and C-style arrays.
- Both functions require to explain null-terminated strings.
- Both functions require to explain ellipsis (``...``).
- Use of both functions produce code that is hard to read for beginners (a lot of punctuation) and requires a lot to memorize (format specifiers).

Just think of a sample program that asks the user for a name and prints it back. **How many mistakes can you make if you write it the C way?** How many mistakes can the student make, once you understand they occasionally forget ``;`` and are still a bit unsure about function call with pass-by-pointer syntax? What will happen if you show the students a big table of format specifiers and tell them that if they don't memorize it correctly, their programs will likely crash?

Now - what if it is written the C++ way? Do you really need to explain how ``+`` and ``=`` work with strings? No. Students will just get it. This showcases C++ strengths in action (type system, operator overloading) without needing to explain them.

C-style arrays / pointers
-------------------------

Why is it bad for beginners?

- It requires to explain pointers, **which are the hardest of all non-template C++ topics**.
- It requires to explain decay.
- It allows a huge array (pun intended) of mistakes:

  - incorrect bounds checking
  - manually written loops
  - off-by-one errors
  - buffer overflow
  - syntax confusion and compiler error horrors (``[]``, ``*``, ``&``, ``.``, ``->``)

- It will usually end up also having to explain ``str-`` and ``mem-`` functions. That's another pile of things to memorize.

Now, what if you start with :cch:`std::vector`? Everything is again simple. ``+``, ``=`` and ``==`` all just work. You don't need to explain ``= { 1, 2, 3 }``. You don't need to explain the difference between a vector of one type and another - students will immediately get that what is put inside ``<>`` is the type of thing that vector holds. From this point, you can also easily move to usage other parts of C++ - the standard library and high-level features such as range-based loops.

Just don't introduce iterators yet. If you showcase stuff from :cch:`<algorithm>`, just explain that for start we will only use begin and end to use the algorithm on the entire vector. Nothing more is needed. Students will get that standard library algorithms have higher potential than presented that will be possible to use once they learn more.

Advantages
==========

If you start teaching C++ using recommendations mentioned earlier:

- You will avoid a lot of confusion caused by pointers and related topics.
- Students will be able to write simple programs, with motivation to learn further.
- Students will think in terms of objects and values (not pointers), which is essential in a value semantics language such as C++.

You probably aren't aware how far it is possible to go without using pointers:

- The book "The C programming language" written by Kernighan & Ritchie introduces pointers at around half of the book. And remember - this is just C. For half of the learning material, students need not to fiddle with asterisks and ampersands.
- You can even showcase polymorphism without using pointers. How? See `CppCon 2015: Kate Gregory “Stop Teaching C" <https://www.youtube.com/watch?v=YnWhqhNdYyk>`_ (at 27min) which was also a major source for this article.

Other recommendations
=====================

- When to introduce :cch:`const`? The sooner the better, but certainly it must be taught when references are.
- Use tools (such as debugger) from the beginning. Enable compiler warnings.
- When you introduce scopes and the stack theory, do not focus on memory. Focus on other resources that have cleanup much easier to explain (such as closing a file). Focus on deterministic destruction, not on memory release.
- When explaining heap, you can mention :cch:`new` and :cch:`delete` but:

  - Don't spend much time on it. Just explain they are used to explicitly create and destroy stuff (in contrast  to stack lifetime) and tell that classes such as strings and vectors use this mechanism inside their implementation.
  - You may make a comparison to GC-based languages (e.g. Java, C#) where :cch:`new` is required for every object creation.
  - Introduce smart pointers to showcase how easy it is now to make a heap-allocated RAII object.

- Raw pointers can be introduced after references and smart pointers as a more complex mechanism to manipulate objects. But do not present raw owning pointers! Use pointers as a non-owning mechanism only - e.g. to showcase :cch:`nullptr` and ability to rebind them.
- Use C++ standard library as soon as possible. Whenever you showcase some code that has equivalent implemented in the standard library, show students the 1-line way of doing the same task.
- Do not showcase complex stuff by explaining each case (example: different lambda captures, polymorphism). Instead, showcase some code, tell there is a feature to simplify it and then showcase simplified code. This approach causes students to understand that features are not arbitrary - they have reasons why they were introduced.

common C++ mistakes in teaching
###############################

Below sections are meant to list common mistakes in explaining specific stuff. This not about order how things are taught but about how they are explained - we all like mental shortcuts but C++ mental shortcuts are often wrong or incorrectly formed.

C++ as a superset of C
======================

C++ was forked from ANSI C, the C language before any standarization. Today we can at most say that ISO C and ISO C++ have a common ancestor.

For a list of features that C has but C++ does not (or their alternatives) see TOWRITE.

C++ standard library as a superset of C standard library
========================================================

Also false. Some parts are only available in C (usually because C++ has equivalent but different features).

function type / prototype / signature
=====================================

These are all distinct terms.

function type
-------------

Primary uses:

- function pointers and function references

Consists of:

- return type
- paramater types (after *decay* applied)
- :cch:`noexcept` (since C++17)
- (if member function) member function qualifiers
- linkage type

function prototype
------------------

Function prototype are the types of the parameters (after *decay* applied).

This is a C-only term, because only C allows to declare a function without specifying paramater types. In C++ it is impossible to declare a function without defining its prototype.

Primary uses:

- compiler warnings about missing prototype

function signature
------------------

The primary uses:

- function overloading
- `name mangling <https://en.wikipedia.org/wiki/Name_mangling>`_

Consists of:

- enclosing namespaces
- enclosing classes
- (if member function) member function qualifiers
- function name
- parameter types
- *requires-clause* (if any)

The most notable thing is that function signature does not include return type, which disallows overloading functions only by their return type.

function parameter vs function argument
=======================================

Function parameters are what function definition expects to be passed in. Function arguments are expressions that are given for specific function call. If there is a mismatch we can say that a function F has been passed incompatible argument X for parameter Y.

"User-defined type is a very formal name for a class"
=====================================================

User-defined type is any new type (not an alias of an existing type) that has been defined in code. Standard library classes are also user-defined types. Apart from classes, C++ has other mechanisms for creating new types - enumerations and unions.

"Header files are for declarations. Source file are for definitions."
=====================================================================

This very short mental shortcut is just wrong:

- Definitions of user-defined types are put in headers.
- Both declaration and definition can be source-only if there is no need to use the entity in a different source file.

The header/source split is not about declaration/definition mechanism but about what can be compiled and what not. Type definitions are only an abstraction - they do not form any code by themselves. What matters for compilation is executable code - mostly function definitions and global objects.

"the type of :cch:`"abc"` is :cch:`const char*`" OR "an array is a pointer to its first element"
================================================================================================

Both of these are wrong:

- String literals are arrays, not pointers.
- Arrays are not pointers, they can at most *decay* to pointers.

The myth comes from very often forgotten implicit convertion caused by *decay*:

.. cch::
    :code_path: str_abc.cpp
    :color_path: str_abc.color

.. admonition:: Note
    :class: note

    Decay happens whenever arguments are passed by value to a function (only *perfect forwarding* will prevent decay). This means that functions having array types as paramaters, such as :cch:`const int[N]` and :cch:`const int[]` are equivalent to :cch:`const int*`. If you want type-safe array function parameters (that do not lose type information), you will need to use abstractions like :cch:`std::array` and :cch:`std::span`.

":cch:`typedef` declaration syntax is :cch:`typedef type identifier$$$keyword spec spec`"
=========================================================================================

.. cch::
    :code_path: typedef.cpp
    :color_path: typedef.color

Such mental shortcut **exhibits the fact that the teacher does not understand language grammar**. This isn't even true for "simple cases", whatever you might think of such term. The whole idea that :cch:`typedef` declaration grammar expects 1 type expression and 1 identifer expression is just wrong.

So ... how is it done then? The answer lies in C++ standard, 9.2 (dcl.spec) (bolded are syntactic elements significant for :cch:`typedef` declarations):

.. parsed-literal::

    *decl-specifier*:
        *storage-class-specifier*
        **defining-type-specifier**
        *function-specifier*
        friend
        **typedef**
        constexpr
        consteval
        constinit
        inline

    *decl-specifier-seq*:
        *decl-specifier* *attribute-specifier-seq*\ (optional)
        *decl-specifier* *decl-specifier-seq*

    *typedef-name*:
        **identifier**
        *simple-template-id*

    *type-specifier*:
        **simple-type-specifier**
        *elaborated-type-specifier*
        *typename-specifier*
        *cv-qualifier*

    *type-specifier-seq*:
        *type-specifier* *attribute-specifier-seq*\ (optional)
        **type-specifier** **type-specifier-seq**

    *defining-type-specifier*:
        **type-specifier**
        *class-specifier*
        *enum-specifier*

    *defining-type-specifier-seq*:
        *defining-type-specifier* *attribute-specifier-seq*\ (optional)
        **defining-type-specifier** **defining-type-specifier-seq**

    *simple-type-specifier*:
        *nested-name-specifier*\ (optional) **type-name**
        *nested-name-specifier* template *simple-template-id*
        *decltype-specifier*
        *placeholder-type-specifier*
        *nested-name-specifier*\ (optional) *template-name*
        char
        char8_t
        char16_t
        char32_t
        wchar_t
        bool
        short
        int
        long
        signed
        unsigned
        float
        double
        void

    *type-name*:
        *class-name*
        *enum-name*
        **typedef-name**

In simpler words:

- :cch:`typedef` declaration expects only 1 subexpression which is also a part of a larger grammar used for declarations.
- :cch:`typedef` declaration recursively reuses other grammars and treats a specific subpart as the newly declared type.
- It is not :cch:`typedef A B$$$keyword spec spec` (where :cch:`A$$$spec` and :cch:`B$$$spec` are disjoint grammars) but :cch:`typedef X$$$keyword spec` where :cch:`X$$$spec` is a recursive grammar, part of which will be treated as the newly introduced type alias identifier.

I know it would be really hard (and pretty much pointless) to explain grammar for beginners (especially this heavily-recursive case) but **do not explain** :cch:`typedef` **syntax using mental shortcut mentioned above**. It leads people to a very false thinking. It's much better explained as ":cch:`typedef` reuses declaration grammar but the identifier instead of being a new object is treated as a newly introduced type alias".
