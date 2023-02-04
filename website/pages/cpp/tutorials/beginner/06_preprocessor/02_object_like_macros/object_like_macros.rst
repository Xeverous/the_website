.. title: 02 - object-like macros
.. slug: index
.. description: object-like macros
.. author: Xeverous

The :cch:`#define` directive offers text replacement and is commonly used as a building block for more complex preprocessor code.

Syntax
######

.. cch::
    :code_path: syntax.cpp
    :color_path: syntax.color

The :cch:`replacement-list$$$0spec` is always optional (a macro may have "empty" definition and just exist). The identifier can be anything except:

- keywords
- *identifiers with special meaning* (list on https://en.cppreference.com/w/cpp/keyword)
- standard attribute tokens (list on https://en.cppreference.com/w/cpp/language/attributes#Standard_attributes)

In practice, implementations allow such macros (preprocessor doesn't understand C++ grammar and keywords after all) but output a warning - the standard doesn't want programmers to hijack core parts of the language by the preprocessor text replacement mechanism.

.. admonition:: note
  :class: note

  By convention, all preprocessor identifiers (especially *macros*) should be written in UPPERCASE_ONLY. This is to avoid clashes with ordinary code - *macros* must be clearly visible.

.. admonition:: note
  :class: note

  A macro can use other macros inside it's own *replacement-list*.

In the example below you can see both object-like and function-like macros in action. The preprocessor is capable of basic math operations - these are typically used to check the level of available features.

.. cch::
    :code_path: example.cpp
    :color_path: example.color

:cch:`#undef`
#############

Generally, there is no need to undefine previously defined macros - each *translation unit* that is a part of compilation process (source file + all files it includes) will run through separate preprocessor. Still, in some cases undefining may be desirable to affect other directives.

Unlike the C++ compiler (when it comes to duplicate definitions), the preprocessor reacts differently to conflicting directives:

- :cch:`#define`: if the identifier is already defined as any type of macro, the program is *ill-formed* unless the definitions are identical.
- :cch:`#undef`: if the identifier does not have associated macro, the directive is ignored.

Still, major compilers in both cases (duplicate definition, undefining non-existing macro) will issue warnings as such code while technically valid, typically indicates some mistake within preprocessor code.

When macro presence can not be easily predicted (which is the case on many platforms where supported features vary) one can prepend operations with checks to avoid warnings:

.. cch::
    :code_path: undef.cpp
    :color_path: undef.color

Predefined macros
#################

Several macros are defined by the C++ standard. You don't need to include any files to get them.

Macro constants
===============

Most notable ones:

- :cch:`__cplusplus` - version of the C++ standard being used as a number in the form ``YYYYMM``

  - C++98: :cch:`199711L$$$6num1suf`
  - C++11: :cch:`201103L$$$6num1suf`
  - C++14: :cch:`201402L$$$6num1suf`
  - C++17: :cch:`201703L$$$6num1suf`
  - C++20: :cch:`202002L$$$6num1suf`

- :cch:`__STDC_HOSTED__$$$macro` - :cch:`1` if the implementation runs on an OS, :cch:`0` if freestanding (the code is the operating system)
- :cch:`__STDCPP_THREADS__$$$macro` - if present and if has value :cch:`1` indicates that the implementation supports multiple threads of execution

More listed on https://en.cppreference.com/w/cpp/preprocessor/replace

.. admonition:: warning
  :class: warning

  Up untill Visual Studio 2017 version 15.7 Preview 3, the Microsoft's compiler implementation was erroneously stuck at :cch:`__cplusplus` being :cch:`199711L$$$6num1suf`. Library implementers had to rely on :cch:`_MSC_VER$$$macro` or other MSVC-specific macros to check what is supported. See `a post on Microsoft's blog <https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/>`_ for more information.

Feature-testing macros
======================

These macros indicate support for certain language features or certain standard library parts. Even though :cch:`__has_include` and :cch:`__has_cpp_attribute` are officially since C++17 and C++20 respectively, GCC and Clang supported them much earlier - if I'm right it was probably compiler implementers idea that later turned out to be so useful it has been standarized. With the help of these macros you can enable a better implementation of something at compile time and still have working code if the feature is not supported.

Full list on https://en.cppreference.com/w/cpp/feature_test

Magic macros
============

There are also few "magic" macros which have very unique behavior:

- :cch:`__FILE__` - expands to an *implementation-defined* string literal indicating currently processed file. IMO GCC made a very good decision to simply output the same string as the file path provided to the compiler - so whether it's relative or absolute the form will be preserved.
- :cch:`__LINE__` - expands to an integer constant indicating current line number.
- :cch:`__DATE__` - expands to a string literal indicating date of preprocessing the file. Has the ugly ``Mmm dd yyyy`` format - ugly because month is not a number and there is no order consistency like year/month/day in ISO 8601 format.
- :cch:`__TIME__` - expands to a string literal indicating time of preprocessing the file in the format ``hh:mm:ss``.

These are commonly used for testing, debugging (especially assertions) and logging. Note that :cch:`__DATE__` and :cch:`__TIME__` expand during preprocessing, not during runtime. Once a file with these is compiled it will contain the same value until a file containing the macro is recompiled again.

:cch:`__func__`
===============

In the scope of every function body, there is a special function-local predefined variable named :cch:`__func__`, defined as a static character array holding the name of the function in implementation-defined format. It's not a preprocessor directive because the preprocessor does not understand C and C++ code - it sees everything as text and doesn't understand what a function is. For this reason :cch:`__func__` has been specified as magic function-local variable. This also means that directives like :cch:`#ifdef __func__$$$1pp_hash5pp_directive var_global` will not work.

The value is implementation defined, but on all major implementations it's simply the name of the function. If you want a richer variant (enclosing scopes + arguments + cv-qualifiers etc.), :cch:`<boost/current_function.hpp>$$$0pp_header` offers :cch:`BOOST_PRETTY_FUNCTION$$$macro` macro which tries to detect the compiler and use an alternative if the implementation supports it. GCC and Clang offer :cch:`__PRETTY_FUNCTION__$$$ext` (magic variable) and MSVC offers :cch:`__FUNCSIG__$$$macro` (macro - no idea why/how).

For extra information, see `SO: What's the difference between __PRETTY_FUNCTION__, __FUNCTION__, __func__? <https://stackoverflow.com/q/4384765/4818802>`_.

Implementation macros
#####################

Compilers provide a lot of information about the implementation in their own macros (not defined by the standard). Many are very useful for writing multiplatform code or code that takes advantage of certain features available only under special conditions. They typically provide information such as compiler name and version, target architecture and operating system, min/max/size/alignment of built-in types, endianess and other details.

For GCC and Clang, you can dump all of the predefined macros using a command like ``echo | g++ -x c++ -std=c++17 -dM -E - | sort`` (should work on Windows and many GNU/Linux distributions). See https://stackoverflow.com/q/2224334/4818802 for more info.

:cch:`NDEBUG$$$macro`
=====================

One particular macro that is very often used is :cch:`NDEBUG$$$macro`. It's presence signifies a release build and based on it, a lot of other macros may be defined differently to enable/disable/alter certain functionality that should be present only in debug or release builds. This typically includes *assertions* (explained later) and logging.

The macro name is reversed ("not debug", present only in release builds) for historical reasons.

Constants
#########

In both C and C++ various data must be a constant expression, e.g. an array size. C++ has extended :cch:`const` functionality so that some const-qualified objects could also be used for such purposes (this was before C++11 introduced :cch:`constexpr`) (the rules are somewhat complex so in C++11 and later code I strongly recommend :cch:`constexpr`).

In C however, :cch:`const` is not as powerful. This creates a necessity in C to use macros, otherwise the constants can not be used when a constant expression is needed:

.. cch::
    :code_path: constants.cpp
    :color_path: constants.color

In C using such macros is simply a necessity, otherwise there is no way to deal with code duplication. The language simply has no feature that solves this problem so the preprocessor text replacement is the only choice. In C++ the situation is much different so the following things are considered bad habits in C++:

- The use of macros when they are not needed. C++ has more powerful keywords and when macros can be avoided, they should be avoided.
- Naming constants using UPPERCASE when they are not macros. This may cause confusion and make regular code vulnerable to a macro of the same name. This is also mentioned in `ES.9 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-not-CAPS>`_, `NL.9 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rl-all-caps>`_ and `Enum.5 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Renum-caps>`_ points in Core Guidelines.

Exercise
########

Write a program that outputs ``Hello from C++XX`` where ``XX`` are last 2 digits of the year of the standard used.

.. details::
  :summary: solution

  A solution with :cch:`#if` for each value works too but here is the most clever one:

  .. cch::
    :code_path: exercise.cpp
    :color_path: exercise.color
