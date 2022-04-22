.. title: 05 - overloading
.. slug: index
.. description: function overloading
.. author: Xeverous

Sometimes you may encounter a problem where you need multiple functions doing similar task or the same task but on different types. You probably would name them similarly - in fact, names can be the same thanks to overloading.

Function overloading is a feature that allows to have multiple functions with the same name as long as their *signatures* are different.

.. cch::
    :code_path: example.cpp
    :color_path: example.color

.. code::

    quotient: 2
    remainder: 2

    can not divide by 0

    quotient: 2.28571

    quotient: inf

The first 2 calls are using the first *overload* and the second 2 calls are using the second one.

How it works
############

Which overload to call is decided upon provided arguments. In order to overload, functions must have different *signature*.

.. admonition:: definition
  :class: definition

  Function signature consists of:

  - amount of parameters
  - types of parameters, except that top-level *cv-qualifiers* are ignored
  - function qualifiers (:cch:`const`, :cch:`volatile`, :cch:`&`, :cch:`&&`) - these are only applicable to *member functions*

  Function signature does not consist of:

  - return type
  - *exception specification*

Examples:

.. cch::
    :code_path: overloading.cpp
    :color_path: overloading.color

When a call to overloaded function is encountered, a mechanism called *overload resolution* takes place:

- If no function can be matched to provided arguments and their types, the program is *ill-formed* (compiler error)
- If multiple overloads match, they are selected in this order:

  - an overload which does not require any convertions (perfect match)
  - an overload which requires *promotion* (lossless convertion) or *user-defined convertion*
  - an overload which requires *narrowing convertion* (potentially losing convertion)

- If multiple overloads require same-rank convertion then the one that requires least convertions is selected.
- If there are still multiple overloads to choose from the program is *ill-formed* due to ambiguity.

The `detailed rules <https://en.cppreference.com/w/cpp/language/overload_resolution>`_ are much more complicated but the points above should serve well as a general explanation.

Examples:

.. cch::
    :code_path: overload_resolution.cpp
    :color_path: overload_resolution.color

Deleted overloads
#################

The keyword :cch:`delete` is primarily for memory deallocation, but since C++11 it gained an additional functionality. It can be used to explicitly :cch:`delete` function overloads. Deleted overloads take part in overload resolution as any other overload, but if a deleted overload is choosen then compilation fails.

.. cch::
    :code_path: deleted_overload.cpp
    :color_path: deleted_overload.color

.. admonition:: note
  :class: note

  Overloads written with :cch:`= delete` are treated as function definitions, not just declarations.

In practice
###########

Don't worry if you can not memorize everything - intuitively the most fitting overload is choosen.

Operators, like functions can be overloaded too (operators actually *are* functions, just with special syntax). The best example is ``<<`` which is extensively overloaded for standard library stream types (:cch:`std::cout` is one of such streams). As of C++17, there are 29 overloads, 14 of which are templates.

    How do templates play with overload resolution?

Function templates, before entering overload resolution are subject to *template type deduction*, that is, their template parameters are sort of guessed based on provided *arguments* and *template arguments*. It's a pretty complex mechanism but after finishing it (or failing it, in the case of *SFINAE*, which is even more complicated) a signature is formed (or not, if SFINAE happened) that takes part in overload resolution like any other overload. If there is a match of the same priority from a template and non-template overload, the non-template one is selected.

.. admonition:: note
  :class: note

  Function overloading and default arguments are features that are not present in C.
