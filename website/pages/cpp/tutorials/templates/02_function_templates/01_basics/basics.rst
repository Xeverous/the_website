.. title: 01 - basics
.. slug: index
.. description: basics of function templates
.. author: Xeverous

The need for abstraction
########################

Suppose you have a min function:

.. cch::
  :code_path: min1.cpp

..

  Why this specific order? Why :cch:`y < x$$$var_local < var_local` and not :cch:`x < y`?

Because for the minimum function, we want to always return the first argument if values compare equal (this has no difference for integers but objects like case-insensitive strings may compare equal while not being identical). The reasons for this touch the topic of iteration, ranges and algorithms that are out of scope of this tutorial.

Now suppose you want to have the same function, but for doubles and strings:

.. cch::
    :code_path: min2.cpp

You can easily overload it, but you notice that the code is almost identical, only **types** have changed. Everything else is duplicated and we know that code duplication is one of the worst sins in programming. It would be very nice to have an abstraction that allows to use the same code with arbitrary types. Templates exist for this purpose.

Creating templates
##################

Templates aren't immediately-compileable-code but stencils for compileable code. To make entity a template, it has to have at least one template parameter.

The predominant way to add template parameters to an entity is to prepend the entity with a :cch:`template` signature with specified template parameters. Then replace occurences of desired types/values within the entity definition with template parameters.

.. cch::
    :code_path: min_template.cpp

This code is very close to the simplest overload of :cch:`std::min` function template.

The template signature works just like a function signature with minor differences:

- it is written using ``<>`` instead of ``()``
- it gives names to template parameters instead of function parameters

Just like with function parameters, there can be multiple template parameters and they may have defaults. More on these later.

There are also other features that can be used inside the :cch:`template` signature but they will be explained much later in the tutorial.

:cch:`class` vs :cch:`typename`
===============================

The example above used :cch:`typename` keyword to parametrize a function on the type. Sometimes you might see :cch:`class` used instead. Initially, there was no :cch:`typename` keyword and :cch:`class` was used to introduce template type parameters. C++ is reluctant in adding keywords because every new keyword is a breaking change for code that uses identical identifier to name its own entities.

Because :cch:`class` created some confusion (template parameters do not have to be classes - they can be any type), :cch:`typename` was added later. Ironically:

- :cch:`typename` has got a second meaning too (in other context)
- :cch:`typename` was not formally allowed in templates of templates due to a simple mistake in the standard - compilers already knew of this mistake and accepted the keyword in all contexts, even before it was corrected in C++17

My recommendation is to use the intended keyword :cch:`typename`. It avoids the confusion that only classes can be used within templates.

Naming convention
=================

The name of the alias doesn't really matter, but it's a very strong convention to use T and consecutive letters (U, V, W, ...) for arbitrary type aliases. It probably originated from the word "type" or "template".

Longer (more descriptive) template names traditionally have been written using ``PascalCase`` style. They were names of *concepts* which specified syntaxical and semantic requirements for the given type. Initially, it was only an idea to increase code readability but soon the work started to formalize these expectations and provide a compile time mechanism for verifying them.

Concepts were a long-awaited feature that was initially planned to arrive in C++11 but due to many obstacles they were merged into the language in C++20. During (and before) this period, while concepts weren't yet a part of the language, the specification was already being formed which let programmers use very descriptive names. Some examples:

- ``UnaryPredicate`` - a type capable of being called (e.g. a class with overloaded :cch:`operator()`) with 1 argument that returns an object of type :cch:`bool`
- ``RandomAccessIterator``- a type capable of iteration in both directions supporting arbitrary-length jumps (valid to use with dereference, increment, decrement, addition and subtraction)

When C++20 came with concepts defined in the standard library, they came with the standard ``snake_case`` name style.

My recommendation is thus:

- use T and consecutive letters for template type parameters with no constraints
- use ``PascalCase`` name style for informal concept names or for code without C++20 concepts
- use ``snake_case`` for naming concepts as this is the style they are defined with in the standard library

Actual usage of concepts will be presented later. You still have to learn a lot of fundamentals about templates.

    Is there a concept name that would match the example minimum function?

Yes: ``LessThanComparable``.

Passing arguments
#################

This is tricky as both by value and by reference have their tradeoffs (not just performance) and exactly one approach must be choosen. The topic deserves a lesson of its own so for now the examples will simply follow standard library design without delving too deep into details.

Returning in function templates
###############################

Again, a topic worthy of its own lesson. But to touch what is important: you should never return a reference to a local variable. This holds true for function templates too.

In the example above, because the parameters are passed by const reference we can return them back - their lifetime is larger than the function body. **Except when it's not**:

.. cch::
  :code_path: dangling_reference.cpp

Unfortunately there is no easy way to deal with it. If the function returns by value, it can incur unnecessary copy when both arguments are already existing objects. More overloads could be written with different argument qualifiers but they have their own problems too (too complex to present for now).

The implementation will be left as is (:cch:`std::min` and :cch:`std::max` have the same problem). The problem occurs only if argument is a temporary object and the result is captured by reference. We will place the blame on language design and those who don't read documentation when using the function.

Both topics (passing arguments and returning) will be covered in their own lessons.
