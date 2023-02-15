.. title: 03 - exception specification
.. slug: index
.. description: dynamic exception specification and noexcept
.. author: Xeverous

Dynamic exception specification
###############################

.. admonition:: note
    :class: note

    This section describes a feature deprecated in C++11 that was later removed in C++17.

Until C++17, functions (including special member functions) could have *dynamic exception specification*.

.. cch::
    :code_path: dynamic_exception_specification.cpp
    :color_path: dynamic_exception_specification.color

This informed the compiler which types of exceptions (or types derived from) can be thrown (otherwise each function is assumed to potentially throw everything). From cppreference:

    If the function throws an exception of the type not listed in its exception specification, the function :cch:`std::unexpected` is called. The default function calls :cch:`std::terminate`, but it may be replaced by a user-provided function (via :cch:`std::set_unexpected`) which may call :cch:`std::terminate` or throw an exception. If the exception thrown from :cch:`std::unexpected` is accepted by the exception specification, stack unwinding continues as usual. If it isn't, but :cch:`std::bad_exception` is allowed by the exception specification, :cch:`std::bad_exception` is thrown. Otherwise, :cch:`std::terminate` is called.

Why the feature was removed? Well, it was wonky from the start. Java has identical feature and while not removed, it receives strong criticizm. The reasons for removing dynamic exception specification from C++ were:

- It did not enforce what it stated at compile time. In the case of Java, compilers can track possible exceptions and block code at compile time that violates it, but in case of C++ the feature was introduced too late to put such a high requirement on already existing code. Thus, :cch:`std::unexpected` was born.
- There was hope for potential performance gains from providing such information to compilers. No possible optimizations were found. **Even worse**, the feature has **actually prevented certain optimizations** because of additional violation checks that had to be performed.
- Because there were no compile time checks, writing dynamic-exception-specification-correct code was a huge burden on programmers (and still is in Java). The meta of ignorance in both languages reached a point where people simply specified standard library base exception class for every function, making it useless in Java and marginally-informative in C++ (which allows non-class exceptions which no one uses).
- The feature was not consistent with C++ type system. Unlike :cch:`const` and :cch:`volatile`, it could not fully propagate and was not syntaxically allowed in some subgrammars (e.g. :cch:`typedef`\ s of function pointers). Exception specification did not participate in function's type, *except when it did*.

For a longer description read `this article by Herb Sutter <http://www.gotw.ca/publications/mill22.htm>`_.

:cch:`noexcept` specification
#############################

Exception specification is not gone entirely, but it has been reduced to 2 simplest cases:

- a function can throw objects of any type (nothing is written)
- a function can not throw (:cch:`noexcept` is written) (if it actually throws - :cch:`std::terminate`)

And this time it fully works with the type system - analogically to :cch:`const` and :cch:`volatile` the qualification can be increased, but not removed. That is:

- You can assign addresses of :cch:`noexcept` functions to function pointers, but not vice versa (non-\ :cch:`noexcept` functions to :cch:`noexcept` function pointers).
- If a base class :cch:`virtual` function is :cch:`noexcept`, all overrides have to be too.
- Just like the return type of a function:

  - It is a part of the function type.
  - It is not a part of the function signature - it is not possible to overload functions only by exception specification.

:cch:`noexcept` allows some optimizations on stack unwinding that normally would break implementation of destructors. It also informs the programmer that a given function is safe to use in exception-unsafe contexts such as the body of a destructor or any other function that is also :cch:`noexcept`.

It's possible to call potentially throwing functions and have an exception inside a :cch:`noexcept` function. The exception should just not escape such function (must be caught inside). It if escapes - :cch:`std::terminate`.

.. admonition:: note
    :class: note

    The following are implicitly :cch:`noexcept`\ :

    - `atomic operations <https://en.cppreference.com/w/cpp/thread#Atomic_operations>`_
    - all C++ standard library functions that come from the C standard library
    - destructors (can be disabled by :cch:`noexcept(false)` but it's heavily discouraged - destructors should never throw exceptions)

:cch:`noexcept(bool)`
=====================

The keyword `noexcept` can accept a constant expression that is convertible to :cch:`bool`. Defaults to :cch:`true`, which means :cch:`noexcept` specifier is equivalent to :cch:`noexcept(true)`. This feature is typically used within function templates to conditionally apply :cch:`noexcept` depending on template parameters.

:cch:`noexcept` operator
########################

Apart from exception specification, the keyword can also be used as an operator. It returns a compile time constant of type :cch:`bool` which value is :cch:`true` if the expression can not throw exceptions. Just like :cch:`sizeof` and :cch:`alignof` operators, the expression is an *unevaluated context* - it is not executed, only checked for specific behavior. The returned value is :cch:`constexpr` but the expression itself does not have to be.

.. cch::
    :code_path: noexcept_operator.cpp

In rare cases both the :cch:`noexcept` specifier and :cch:`noexcept` operator can appear together: :cch:`T func() noexcept(noexcept(T()))$$$param_tmpl func() keyword(keyword(param_tmpl()))`. This tests the expression and immediately uses the result to specify whether the current function is :cch:`noexcept`.

    Couldn't it be simplified to just 1 use of the keyword?

While it looks like a simplification, it would actually result in a significantly more complicated definition of the keyword - it would have to dynamically adapt depending on a complex context information; some ambiguities might arise. The current definition is much simpler: :cch:`noexcept` works as an operator except in the immediate context of a function (template) declaration - then a specifier. Apparently the committee is fine with this approach, because C++20 introduces identical situation with double :cch:`requires` for concepts.

In practice
###########

Apply :cch:`noexcept` very carefully. Just because a function doesn't throw doesn't mean it will never do after any future edits. You can easily :cch:`std::terminate` your program by applying :cch:`noexcept` and realizing that many stack frames deeper some subfunction can throw. Don't use :cch:`noexcept` unless you can verify and guarantee that all calls within will never throw.

Only a small subset of functions is recommended to be marked as :cch:`noexcept`:

- special member functions: move constructor and move assignment (destructors are already implicitly :cch:`noexcept`)
- swap operations (a kind of functions written to implement *copy and swap* idiom which is used in some special member functions)
- memory and resource (de)allocation functions (pretty low-level code) - such functions are used within destructors
- functions intended to operate in an exception-unsafe context:

  - interacting with C: passing addresses of C++ functions to a C API - if C code calls a C++ function and it throws, undefined behavior occurs
  - badly written C++ - there is a lot of exception-unsafe C++ code, including whole libraries (e.g. Qt)

Special member functions do not have to be :cch:`noexcept`, but if they are the C++ standard library takes advantage of it in various places (mostly containers and algorithms - improved performance or better *exception guarantees*).
