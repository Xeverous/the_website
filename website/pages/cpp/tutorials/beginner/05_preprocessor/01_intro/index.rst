.. title: 01 - intro
.. slug: index
.. description: introduction to the preprocessor
.. author: Xeverous

The preprocessor is a build process mechanism that is invoked before compilation takes place.

Preprocessor code consists of *directives*. A directive is a single command for the preprocessor. All directives start with ``#`` and span until end of line (not until ``;`` - it's not regular C or C++ code). ``\`` Can be used at the end of line to extend the directive 1 more line.

All preprocessor directives (more details in subsequent lessons):

- :cch:`#` - does nothing
- :cch:`#include` - pastes the content of mentioned file in place of the directive
- :cch:`#define` and :cch:`#undef` - define and undefine identifiers for further preprocessing or text replacement (often called *macros*)
- :cch:`#if`, :cch:`#ifdef`, :cch:`#ifndef`, :cch:`#elif`, (since C++23 :cch:`#elifdef`, :cch:`#elifndef`) - conditionally parse enclosed code (may contain nested preprocessor directives)
- :cch:`#error` - force an error during preprocessing
- :cch:`#pragma` - implementation defined preprocessor extensions
- :cch:`#line` - changes values of the :cch:`__LINE__` and :cch:`__FILE__` macros

A very common example of preprocessor usage is conditional compilation - providing different code depending on defined identifiers. Many are either implicitly defined by the compiler or passed as compiler options (``-D`` for GCC and Clang). In the example below you can observe macro definition detection used to conditionally include platform-specific headers and platform-specific text replacement macros that represent a constant of maximum file name length.

.. cch::
    :code_path: example.cpp
    :color_path: example.color

This way the program can implement the same behavior on different platforms where different code is needed. Note that :cch:`#ifdef` does not behave as :cch:`if` - the preprocessor is run before compilation so it's not a runtime decision, it's a build-time decision which code to even start compiling.

.. admonition:: note
  :class: note

  The preprocessor operates on text, not on C++ level - it doesn't understand C++ grammar and will not attempt to verify that generated code, even whether it's syntaxically valid. It's more or less just a text paste/find/replace mechanism, not very far away from whole-word-find-replace functionality in text editors.

.. admonition:: note
  :class: note

  You can place :cch:`#define`/:cch:`#undef` inside :cch:`#ifdef`/:cch:`#ifndef` ... :cch:`#endif` to conditionally (un)define macros based on other macros.

After the preprocessing is done, compiler sees generated code without any preprocessor directives. Thus, the preprocessor can effectively be used to compile different code based on build settings and target platform information.

Applications
############

Apart from conditional compilation, complex replacement macros can be used to automate code generation. Abuse of this mechanism is generally considered bad style but still today some things have no better alternative - this is especially true for any kind of boilerplate that is not supported by templates or other language features. Typical applications of such macros are:

- logging
- *assertions*
- unit tests
- serialization

.. TODO an example?
