.. title: 05 - objects
.. slug: index
.. description: making objects in C++
.. author: Xeverous

You already know basic types in C++. Time to create some *objects*.

What is an object?
##################

It's hard to give a simple and consise definition of an object that doesn't just go by listing every C++ language rule attached to it, so to put it simply: **objects are data in memory**.

Every object has:

- *lifetime* (when associated memory can be used)
- type (how the bit pattern should be interpreted)
- value (actual bit pattern in memory)
- (optionally) a name (identifier)
- some memory-related properties (address, size, alignment, storage duration) that won't be interesting for now

Note that most of these are purely an abstraction on which the programming language is built. Hardware only performs computations, read and write operations and doesn't know about types - it only sees data as different memory cells, each being one byte.

The name is optional because:

- In some cases temporary (unnamed) objects may be created as a part of evaluation of expressions - e.g. in :cch:`2 * 3 + 4$$$num * num + num` an unnamed integer object with value :cch:`6` may temporarily appear in memory.
- In some cases objects can be referred using indirect mechanisms such as *pointers* and *references*. This is especially true for any data that has variable size (e.g. an array).

Don't think that an *object* (some data in memory with certain properties) means the same as a *variable* (named modifiable entity in code):

- When using indirect mechanisms such as references and pointers, it's possible to have 2 variables (e.g. 2 references) that refer to the same object in memory.
- When using variable-size objects such as arrays, it's possible to have multiple objects that are accessed through the same variable.

Of couse we are still pretty far from indirect mechanisms, for now all of the code will have 1:1 variable-object relation.

If you are curious for the formal difference:

.. admonition:: definition
    :class: definition

    A *variable* is an *object* or a *reference* that is not a *non-static data member*, that is introduced by a *declaration*.

Creating objects
################

Before using an object, you must first specify what type it will be.

.. cch::
    :code_path: variable_definitions.cpp
    :color_path: variable_definitions.color

At this point, the compiler will determine any other properties (especially memory-related ones) automatically. Such statements are called variable *definitions*, though many mistakenly named them *declarations*.

It's possible to define multiple objects at once:

.. cch::
    :code_path: multiple_definitions.cpp
    :color_path: multiple_definitions.color

...but **such practice is very discouraged**. For historical reasons (mostly backwards compatibility), C++ adopted C grammar which while generally brilliant, has some peculiarities and most of them lie in *decl-specifier-seq* subgrammar, which is used for declarations. Thinking of object declaration syntax as "type followed by name" is fundamentally wrong with how C/C++ grammar works and for this reason:

.. admonition:: tip
    :class: tip

    Declare only 1 entity per statement.

This is a very common C++ teaching mistake - please point it out by giving link to this article TODO. While I understand the need for mental shortcuts, "type followed by name" is only trapping beginners in incorrect thinking. We wish it worked this way, but it doesn't.

To further prove the argument, take a look at this:

.. cch::
    :code_path: declarator_syntax.cpp
    :color_path: declarator_syntax.color

In this specific example, only :cch:`int` is "picked up" for every object and any other type modifiers seem to be in random places. People don't want to deal with such unintuitive rules - they are only maintained for backwards compatibilty.

.. admonition:: tip
    :class: tip

    Always declare each variable in a separate statement. Never declare mutliple variables in one.

..

    Can't these syntax rules be changed?

C++ is a very history-rich language (40+ years) and it also takes backwards compatibility very seriously. C++ inherited a lot from C, including some of its grammar design flaws. Still, it wouldn't be in a place it is today if the language did not appear as an alternative to then very fast growing C. Many of past problems did get "fixed" in C++11 **without breaking backwards compatibility** by adding more alternative subgrammars. This of course spawned a lot of corner cases so if you want some laugh, watch the 7min talk `CppCon 2018: Timur Doumler "Can I has grammar?" <https://www.youtube.com/watch?v=tsG95Y-C14k>`_.

Don't be intimitated by the C declaration grammar. Majority of C++ code uses types which are very easy to read. The ones that aren't easily readable have multiple ways to workaround it such as type name aliases. Vast majority of code will look as if "type followed by name" was true.

Assignment
##########

After an object has been created, we can start using it. One of the simplest operations you can perform is assignment:

.. cch::
    :code_path: assignment.cpp
    :color_path: assignment.color

You can observe that statements are executed from top to bottom and :cch:`x`'s value is changed.

Initialization
##############

If an object definition is combined with giving it a value, it's called **initialization**.

.. cch::
    :code_path: initialization.cpp
    :color_path: initialization.color

It looks just like a shortcut version of previous code (AKA *syntax sugar*) but **initialization is fundamentally different from assignment**:

- an object can be assigned any time after its creation
- initialization can happen only once: when the object is created

Right now there is no visible difference but it will be very important later. Even though both assignment and initialization use ``=``, they are technically very different operations.

.. admonition:: tip
    :class: tip

    Always initialize variables upon their creation.

There is nothing wrong in assignment, however the first ever value than an object will hold should be given through initialization. Reasoning is pretty simple:

.. Sometimes only initialization will be possible - such is the case of :cch:`const` objects. They can be initialized, but never assigned.

- Initialization offers more than the assignment:

  - Sometimes initialization will be more optimal than creation + assignment.
  - Sometimes initialization will be required.

- If you create an object, but can't give any value to initialize it with, you very likely don't need the object. In such case, the object creation should be postponed (done later in the code) to the moment it's actually needed.

..

    If initialization is so important, why objects aren't intialized automatically by the compiler?

In some programming languages (usually ones which operate on higher abstraction level) they actually are, but C++ (and its ancestor - C) have always fundamentally followed the rule that you don't pay for what you don't use and if something is not absolutely necessary, it shouldn't be done - at least automatically. The performance penalty of "dead writes" (e.g. initializing an object with some value but never reading it before future assignment) is getting lower, but it's still not zero and C++ doesn't like forcing things that are not required. A lot of people advocate for a reversed default though, where initialization would be opt-out, not opt-in as in vast majority of cases the programer wants to be warned about missed initialization and the need for optimizing to the point of removing single write instructions is very rare.

Other reasons include backwards compatibility and the inability to provide good defaults. For any numeric type, zero is a very good choice. For :cch:`bool` it's :cch:`false` because it is represented by bit 0. But for a lot of types there is no good default and their bit representation made full of 0s may have no valid interpretation.

Syntax
======

Initialization can be performed in multiple ways:

.. cch::
    :code_path: initialization_syntax_examples.cpp
    :color_path: initialization_syntax_examples.color

Each of these works somewhat differently. There are even more than in the example, but they can not be used for built-in types like :cch:`int`.

For now, we will stick to copy initialization as ``=`` is definitely the easiest and most intuitive syntax to remember. We will come back to different ways of initialization once you gain more knowledge about the type system in C++.

:cch:`const`
############

:cch:`const` can be aplied to any type, which adds some restrictions:

.. cch::
    :code_path: const.cpp
    :color_path: const.color

The keyword is simple yet very useful but at this stage you likely wouldn't believe how much programming errors it prevents and how much it improves code readability for others.

For simple types, 2 positions of the keyword are accepted:

.. cch::
    :code_path: const_direction.cpp
    :color_path: const_direction.color

Technically, **const applies to what is on its left, unless there is nothing - then it applies to what is on its right**. There are lots of people advocating for both, mainly because:

- East :cch:`const` is more in-line with underlying grammar rules - this is the more noticeable the more complex type is. But since majority of types are simple (1-3 tokens), they can rely on the "unless there is nothing - then it applies to what is on its right" rule.
- West :cch:`const` is more in-line with English grammar and general expecation of the public. It's also how the keyword works in other programming languages.

In other words, for strictly technical reasons, east :cch:`const` should be used. But because it's known that declaration part of the C/C++ grammar is unintuitive, many recommend west :cch:`const` - it feels more natural and in majority of cases it's possible to do so.

The west vs east :cch:`const` debate is C++'s equivalent of the "on which side the toiler paper should be" debate. Community likes to make fun of it, it's most prominently visible on CppCon materials.

`Core Guidelines NL.26 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rl-const>`_ recommend west version although the recommendation itself isn't very strong.

I have tried both conventions in different projects and personally I prefer the west version, even if the code I write is quite complex and even if I'm often forced to use the east version for technical (grammatical) reasons.

:cch:`constexpr`
################

:cch:`constexpr` is a leveraged version of :cch:`const`. The additional requirement is that the value must be computable at compile time.

.. cch::
    :code_path: constexpr.cpp
    :color_path: constexpr.color

If possible, it's recommended to use :cch:`constexpr` over :cch:`const` as it opens few more language features; features which require compile-time data. The features are specified to require *constant expressions*.

It's possible to write :cch:`constexpr const ...$$$keyword keyword 0spec` but it's redundant: for object definitions, :cch:`constexpr` already implies :cch:`const`.

.. admonition:: note
  :class: note

  :cch:`constexpr` was introduced in C++11 but *constant expressions* are almost as old as the entire language - they are required in many fundamental features.

  To support manipulation of constant expressions, C++ extended rules governing :cch:`const`. :cch:`const` objects in C can never be used as constant expressions (they must be literals) but in C++ they can - details are complicated but roughly speaking they are classified as constant expressions if their value is computable at compile time.

  Details aren't really worth learning for now, just use :cch:`constexpr` but don't be surprised if you see pre-C++11 code that uses :cch:`const` as if it was :cch:`constexpr`.

Recommendations
###############

- define 1 variable per statement
- use :cch:`const` for objects that once initialized, should not be changed
- use :cch:`constexpr` for objects which values are computable at compile-time

Exercise
########

Is the following code valid?

.. cch::
    :code_path: exercise1.cpp
    :color_path: exercise1.color

.. details::
    :summary: Answer

    Yes. Assignments work by evaluating expression on the right before the result is stored in an object. There are no problems if the expression refers to the same object.

Is the following code valid?

.. cch::
    :code_path: exercise2.cpp
    :color_path: exercise2.color

.. details::
    :summary: Answer

    Technically yes (this will compile) but contains *undefined behavior*. :cch:`x` here is used (on the right side) before it's initialized. It's not possible to correctly initialize an object with a value that depends on it.
