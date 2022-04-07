.. title: 08 - static methods
.. slug: index
.. description: class static function members
.. author: Xeverous

Just like :cch:`static` fields, :cch:`static` methods are not tied to any particular instance of the class. They are essentially global (free) functions in the class namespace.

- :cch:`static` methods can not access non-static class fields.
- :cch:`static` methods can not have any qualifiers (:cch:`const`, :cch:`volatile`, :cch:`&`, :cch:`&&`). Since they do not work on any object, there is no point in declaring any object-specific behavior.

Named constructors
##################

One particularly good use of :cch:`static` methods is *named constructor* idiom. In some languages, constructors can have specific names. In C++ and many other languages that support OOP, constructors have no names - they just use the name of the class. This can sometimes lead to unclear code:

.. cch::
    :code_path: temperature.cpp
    :color_path: temperature.color

Clarity of such code can be improved by implementing *named constructors* (or actually faking it since C++ has no such feature):

- make the constructor :cch:`private`
- supply :cch:`public` :cch:`static` methods that return an object

Now any external code that uses the class is much clearer:

.. cch::
    :code_path: named_ctor.cpp
    :color_path: named_ctor.color

Singletons
##########

A common pattern that uses :cch:`static` methods and :cch:`private` constructor is `singleton <https://en.wikipedia.org/wiki/Singleton_pattern>`_, that is a class that is designed on purpose to only allow one object of its type.

This can sometimes be useful to limit interactions with the state that should exist only once such as program-wide configuration object, **but the pattern can very quickly become an antipattern if overused**. The more singletons a program has, the more interactions with global state (complicates reasoning about the program) and the more troublesome testing becomes. Code with lots of singletons is also much harder to refactor because one place of code can couple very arbitrary, different parts of the program, trigerring a cascade of required changes if the singleton is to be modified.

Canonical singleton in C++ looks as follows (this is sometimes called *Meyer's Singleton* as this form appeared in his book):

.. cch::
    :code_path: singleton.cpp
    :color_path: singleton.color

Empty classes with :cch:`static` methods
########################################

Sometimes you may encounter a code like this:

.. cch::
    :code_path: class_static_methods_only.cpp
    :color_path: class_static_methods_only.color

Such code is against C++ idioms. It's typically written by people who are too used to OOP and don't understand that in C++ there is no need to create a class. Some languages force OOP style and (probably the most disliked language by C++ programmers) Java is a primary example (hello world in Java requires to write a class).

The correct code for the example above is:

.. cch::
    :code_path: namespace_for_functions.cpp
    :color_path: namespace_for_functions.color

Notice that after refactoring, function calls would remain the same: :cch:`math::sin(angle)$$$namespace::func(var_local)` etc. If the class had any :cch:`private` methods as implementation detail, they can be moved to an anonymous namespace.

Corner cases
############

Pretty much no one writes code like this so it's more of a fun fact than any rule worth remembering.

.. admonition:: note
  :class: note

  Local classes (1) (classes defined inside functions) and unnamed classes (2), including member classes of unnamed classes (3), cannot have *static data members*.

  .. cch::
    :code_path: corner_cases.cpp
    :color_path: corner_cases.color

Why ban *static data members* in these cases? I don't really know, my guess is that it simplifies the job of compiler writers.

Why are such definitions even possible? Perhaps some consistency reason and maybe backwards compatibility, but I remember that once being able to define an :cch:`enum` inside a function was useful. Note that *lambda expressions* technically each create a new type and by design they are intended to be defined locally.
