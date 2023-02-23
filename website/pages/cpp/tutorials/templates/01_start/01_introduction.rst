.. title: 01 - introduction
.. slug: 01_introduction
.. description: introduction to C++ templates
.. author: Xeverous

Templates are one of the most characteristic C++ features, yet they remain mostly unknown. Only a few seem to grasp their power in significant amount and any template-heavy library looks like some arcane magic.

While templates feel more or less like just a better-than-preprocessor replacement mechanism, when paired with specific language features they can offer surprisingly rich functionalities such as:

- using member types/values of subsituted types
- defining classes that inherit from types specified in template parameters
- defining functions which return objects of new, unique types that are formed based on template parameters

By the size of this tutorial you probably already know that templates are much more than just replacing :cch:`T` with custom types. It's only a tip of the iceberg.

A brief history
###############

*Redacted, from Wikipedia:* STL (Standard Template Library) did not originated right in C++. In 1979 Alexander Stepanov began working out his initial ideas of generic programming and exploring their potential for revolutionizing software development. At the time there was no real support in any programming language for generic programming. By 1987 Stepanov and David Musser had developed and published an Ada library for list processing that embodied the results of much of their research on generic programming. However, Ada had not achieved much acceptance outside the defense industry and C++ seemed more likely to become widely used and provide good support for generic programming even though the language was relatively immature. Another reason for turning to C++, which Stepanov recognized early on, was the C/C++ model of computation that allows very flexible access to storage via pointers, which is crucial to achieving generality without losing efficiency. Andrew Koenig at Bell Labs become aware of the work and asked Stepanov to present the main ideas at a November 1993 meeting of the ANSI/ISO committee for C++ standardization. The response was overwhelmingly favorable. Over time, STL proposed by the SGI company began to grow and C++ got more and more generic programming features.

Today templates are one of the few core features C++ is known for. They are also a huge part of the C++ standard library - so big that sometimes (technically incorrectly) STL is referred to as the standard library even though it's only a part of it, albeit very significant.


You can also read https://stackoverflow.com/questions/1039853/why-is-the-c-stl-is-so-heavily-based-on-templates-and-not-on-interfaces regarding STL history and why templates were chosen over object-oriented design for C++ standard library.

The benefits
############

The main benefits of having templates in the language are:

- High portability and code reuse.
- Higher performance compared to alternative approaches (templates are optimized compile-time for specific types/values, they do not use virtual functions or any similar runtime mechanism).
- Increased type safety and compile time information compared to other approaches (each *template instantiation* is a separate entity with full information, not a base class with an interface).
- Templates significantly reduce the need for other forms of metaprogramming, such as writing programs that generate source code.
- They are a part of the language which means they offer a standarized solution (more efficient and convenient to use than external tools such as code generation scripts).

The core difference
###################

The core difference between C++ templates and similar mechanisms in other languages (e.g. Java generics) is that C++ templates are a fully compile time mechanism. They are a functional language inside C++. Because they are Turing-complete, they form a standalone metaprogram which result can not be easily predicted (if it was possible the `halting problem <https://en.wikipedia.org/wiki/Halting_problem>`_ would have been solved). In other words, the compiler can not predict when metaprogram will finish. The only way to know it is to execute it. Just like with ordinary programs, it's possible to write template code that produces nothing meaningful or gets stuck in a loop during evaluation of specializations, resulting in infinite compile time (obviously compilers will point it out if they notice too deep instantiations).

Templates are not implemented using virtual tables nor anything that relies on runtime mechanisms. Types within templates do not even have to be classes. Templates work as if occurences of abstracted types/values were replaced with template parameters in the source code each time the template was used (producing a new set of source code).

Overview
########

Templates consist of multiple subfeatures. There are 4 kinds of templates:

- function templates
- class templates
- alias templates (since C++11)
- variable templates (since C++14)

It's worth noting that:

- templates can be nested (e.g. a member function template inside class template)
- function templates are not limited to just substitution of parameter and return types
- class templates are not limited to just members of substituted types - they can also inherit from :cch:`T` and do many other shenanigans

Most kinds of templates can be combined with most of additional features creating sophisticated abstraction mechanisms:

- non-type template parameters (NTTP) - subsituting values
- (partial) template specialization - overriding template implementation for specific template parameters
- (since C++11) variadic templates - templates with an arbitrary amount of template parameters
- SFINAE - disabling certain function template overloads or template specializations for template parameters that satisfy certain criteria
- templates of other templates

In addition to these, newer C++ stadards introduced additional convenience features:

- (since C++17) fold expressions - syntax sugar for binary operators
- (since C++17) class template argument deduction (CTAD) + deduction guides
- (since C++20) concepts (constrained templates with much better diagnostics), a replacement for SFINAE
