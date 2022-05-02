.. title: 00 - introduction
.. slug: 00_introduction
.. description: C++ templates introduction
.. author: Xeverous

A brief history
###############

*Redacted, from Wikipedia:* STL (Standard Template Library) did not originated right in C++. In 1979 Alexander Stepanov began working out his initial ideas of generic programming and exploring their potential for revolutionizing software development. At the time there was no real support in any programming language for generic programming. By 1987 Stepanov and David Musser had developed and published an Ada library for list processing that embodied the results of much of their research on generic programming. However, Ada had not achieved much acceptance outside the defense industry and C++ seemed more likely to become widely used and provide good support for generic programming even though the language was relatively immature. Another reason for turning to C++, which Stepanov recognized early on, was the C/C++ model of computation that allows very flexible access to storage via pointers, which is crucial to achieving generality without losing efficiency. Andrew Koenig at Bell Labs become aware of the work and asked Stepanov to present the main ideas at a November 1993 meeting of the ANSI/ISO committee for C++ standardization. The response was overwhelmingly favorable. Over time, STL proposed by the SGI company began to grow and C++ got more and more generic programming features.

Today templates are one of the most significant things C++ is known for. They are also a huge part of the C++ standard library - so big that sometimes it is treated as a synonym for STL.

Generic code offers high portability, extensibility and a large code reuse. Corner cases can be handled by template specializations and other forms of static polymorphism.

You can also read https://stackoverflow.com/questions/1039853/why-is-the-c-stl-is-so-heavily-based-on-templates-and-not-on-interfaces regarding STL history and why templates were chosen over object-oriented design for C++ standard library.

The core difference
###################

The core difference between C++ templates and similar mechanisms in other languages (e.g. Java generics) is that C++ templates are a fully compile time mechanism.

.. admonition:: 2 phases of templates
    :class: note

    C++ template code goes through 2 phases:

    - initial parsing which checks for syntax and semantic errors only for non-template-dependent code
    - template instantiation (when they are used) - only then the code is actually compiled

C++ templates are a functional language inside C++. Because they are Turing-complete, they form a standalone metaprogram which result can not be easily predicted (if it was possible the `halting problem <https://en.wikipedia.org/wiki/Halting_problem>`_ would have been solved). In other words, the compiler can not predict when metaprogram will finish. The only way to know it is to execute it. **It's possible to write a C++ template code that has infinitely long compile time** (in practice compilers will give up after too many instantations).

Don't worry if you don't get this point right now - you will get it once you read the examples. Some of them have been specifically designed to showcase mechanisms that do not exist in other languages.

.. admonition:: Learning difficulty
    :class: success

    C++ templates are not that hard to learn. This guide is made to allow incremental step-by-step learning - there should be no steep curve. Anyone with understanding of C++ should be able to go through. Templates mostly seem hard due to a lack of knowledge - beginners very often are not aware of instantation rules and template specialization.
