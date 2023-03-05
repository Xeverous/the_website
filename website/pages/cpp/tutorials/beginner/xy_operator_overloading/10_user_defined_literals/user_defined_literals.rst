.. title: 10 - user defined literals
.. slug: index
.. description: user defined literals
.. author: Xeverous

C++ offers multiple suffixes for literals:

.. cch::
  :code_path: example.cpp
  :color_path: example.color

...and it's possilble to define new literal suffixes too.

    How about user-defined prefixes?

There is no such thing but character literals and string literals can have both prefixes and suffixes.

Syntax
######

User-defined literals are defined by overloading :cch:`operator""` (free function only), where the suffix immediately follows ``""``.

.. cch::
  :code_path: overloading_example.cpp
  :color_path: overloading_example.color

To avoid confusion and conflicts with the standard library suffixes, suffixes must begin with ``_``. Literal suffixes have significant parsing priority which:

- cause suffixes not to be replaced by macros
- allows suffixes to use names which would normally be keywords
- allows suffixes to use reserved names (so suffixes like ``_Hz`` and ``_Pa`` are allowed)

There should not be any space between :cch:`operator` keyword and the suffix:

.. cch::
  :code_path: overloading_spacing.cpp
  :color_path: overloading_spacing.color

Paramaters
##########

Because it's not possible to combine language built-in suffixes with user-defined ones in the same literal, it has been decided that overloads of :cch:`operator""` must take arguments of the largest possible type of that literal.

These are all allowed paramater sets:

.. cch::
  :code_path: parameter_sets.cpp
  :color_path: parameter_sets.color

Default arguments in :cch:`operator""` overloads are not allowed.

In standard library
###################

.. admonition:: note
    :class: note

    The feature is since C++11 but first standard library suffixes appeared in C++14.

Standard library literals have their own namespaces. They are not exposed in :cch:`std` namespace to avoid name conflicts (there are two ``s`` suffixes: one for  :cch:`std::chrono::seconds` and one for :cch:`std::string`). A specific namespace must be used in order to access them.

.. cch::
  :code_path: stdlib_examples.cpp

.. code::

    abs(1,1) = 1.41421
    one lesson is 45 minutes
    half a minute is 0.5 minutes
    s1: 3 "abc"
    s2: 8 "abc^@^@def"
    There have been 13 leap years since the beginning of UNIX time.

Corner cases
############

.. cch::
  :code_path: corner_cases.cpp
  :color_path: corner_cases.color

Recommendation
##############

User-defined suffixes are mostly useful for classes representing specific physical units. Such strongly-typed code can prevent lots of bugs related convertion and incorrect treatment of units.
