.. title: 06 - default arguments
.. slug: index
.. description: function default arguments
.. author: Xeverous

Sometimes you may encounter a situation where multiple overloads are written to supply predefined values:

.. cch::
    :code_path: motivation.cpp
    :color_path: motivation.color

You can use *default arguments* to simplify this code:

.. cch::
    :code_path: default_arguments.cpp
    :color_path: default_arguments.color

In vast majority of cases, default arguments are temporary objects, often literals. But you can also do stuff like :cch:`void f(int n = g());$$$keyword func(keyword param = func());`.

How it works exactly? Very simple: when a function is called with reduced amount of arguments, the call behaves as if default arguments were written in place of ommited arguments. This means that each time :cch:`f` is called without the argument, :cch:`g` will be called to supply it, as if the code was :cch:`f(g())$$$func(func())`. Formally speaking, default argumnets are evaluated every time the function is called.

There is no support for calling functions like :cch:`func(x,,z)$$$func(var_local,,var_local)`. Only rightmost arguments can be ommited and only rightmost parameters can have default arguments specified:

.. cch::
    :code_path: rightmost.cpp
    :color_path: rightmost.color

Default arguments act as additional overloads so it's possible to create overload sets which can have ambiguities:

.. cch::
    :code_path: ambiguity.cpp
    :color_path: ambiguity.color

Declarations
############

If a function has separate declaration and definition, default arguments should be present only in the declaration.

In practice
###########

Arguments for *default arguments* (pun intended):

- Less code compared to overloading.
- Refactoring and extensibility: it's possible to add parameters to a function and as long as new parameters have default values specified, no changes are needed for existing code (obviously the default argument should preserve behavior that was before the change).

Arguments against *default arguments*:

- They create code that is hard or impossible to reuse (particulary problematic if *inheritance* or function *pointers* are involved). There is no way to "extract" default arguments to use them elsewhere.
- They do not allow certain usage patterns, particulary default arguments can not refer to other arguments:

  .. cch::
      :code_path: argument_from_other_argument.cpp
      :color_path: argument_from_other_argument.color

`This post <https://quuxplusone.github.io/blog/2020/04/18/default-function-arguments-are-the-devil/>`_ (not mine) lists much more arguments against default arguments, some examples use features which haven't been covered yet so I'm only leaving the link.
