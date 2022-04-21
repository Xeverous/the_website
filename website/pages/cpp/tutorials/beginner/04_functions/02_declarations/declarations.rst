.. title: 02 - declarations
.. slug: index
.. description: function declarations and ODR
.. author: Xeverous

Before any entity is used (formally, *ODR-used*) it must be defined. This was already noticeable with variables (their definition specifies a type) and a similar mechanism exists with functions. So far all functions in example programs were defined before main function, because main function used them.

However, a function *definition* is not required at the point of calling it. A *declaration* is enough. It is possible to declare a function and define it's body later:

.. cch::
    :code_path: syntax.cpp
    :color_path: syntax.color

Despite the fact that function parameter names can be skipped in the declaration, it's still recommended to write them. Function declaration is the place most readers will check for documentation comments and parameters with descriptive names are valuable information. Parameter names in the declaration do not have to be the same as in definition (only names in definition affect function body) but in pretty much every case they are written as identical for consistency.

As long as the declaration appears before the function is called, the function definition can be placed later in the code. In fact, it can also be in a separate file!

    Is this the reason why :cch:`#include`\ s are needed to access standard library functions?

Yes. These files (called headers) contain all the declarations (and definitions) necessary to use the standard library, which can be implemented elsewhere. Note that header/source files are not strictly declaration/definition separation - the mechanism is a bit different (more like "interface/implementation") and explained in the preprocessor chapter.

ODR
###

Function declarations and function definitions are one of primary examples of ODR in practice.

.. admonition:: definition
    :class: definition

    One Definition Rule:

    - Every C++ entity must be declared at least once. Each declaration must be equivalent.
    - Every C++ entity can be defined at most once.
    - Every C++ entity must be defined before it's *ODR-used*.
    - Every definition is also a declaration.

ODR is extremely important so to make sure you understand, let's go over each point.

*Every C++ entity must be declared at least once. Every definition is also a declaration.*

This should be self-explanatory. A single definition is enough to act as both. These points were already used in examples in previous lessons where other functions were defined before main function.

*Each declaration must be equivalent.*

Because declarations may repeat (in practice they almost never do), there is a risk for code duplication. To prevent bugs, the compiler verifies that duplicate declarations are equivalent.

*Every C++ entity can be defined at most once.*

The rule specifies *at most once*, not *exactly once* because some entities can be declared and left undefined. As long as they are not *ODR-used*, a declaration is enough.

*Every C++ entity must be defined before it's ODR-used.*

An *ODR-use* is a use of the entity which requires its definition. What requires definition and what only a declaration is very case-specific. Calling functions only requires declaration. Obviously the final program must have the function defined - if you only declare it and try to build the program it will fail.

ODR is extremely important when separating code into multiple files. C and C++ build process (including the concept of *translation units*) requires ODR to be satisfied. More on multi-file projects later in the preprocessor chapter.

.. admonition:: error
    :class: error

    ODR violations can result in undefined behavior.

In practice, vast majority of ODR violations are caught by the compiler or the linker. Undefined behavior (which means anything can happen) also includes the possibility of build errors.

Advantages of declarations
##########################

Most of the code can only rely on declarations and definitions can be compiled separately. The main benefits of this are:

- ability to organize code much more freely (e.g. putting function definition in a separate file)
- ability to have cross dependencies within the code

The second point is very important. As the program gets more complex sooner or later you might find cycles: function A can call B which can call C which can call A. In some problems cycles of dependencies indicate flawed design but in some they are a necessity. A prime example of the second are mathematical and programming expressions - each can nest more subexpressions inside.

Below is an example of 2 cross-dependent functions which can not be defined without declaring something first. However you would try to reorder the program, at least 1 function needs to be declared first.

.. cch::
    :code_path: forward_declaration.cpp
    :color_path: forward_declaration.color

Necessary declarations are often called *forward declarations*.

    What would happen if one of these functions was called with a negative number?

Then both functions would end up calling each other endlessly. Potential outcomes are:

- Value reaches end of signed integer range which is undefined behavior (only unsigned numbers have well-defined overflow).
- Function call stack exhausts stack memory space which causes stack overflow which is also undefined behavior.

:cch:`(void)` declarations
##########################

History time. Initially, in C, there was no mechanism of function declarations. Code which called a function was implicitly declaring it, assuming such function exists and has :cch:`int` return type. If a function with such name was not found in compiled code (possibly originating from different file), it was a linker error. If a function with such name did exist, the linker would connect machine code of its call and definition, without checking whether provided arguments match function definition. At runtime, the function could start evaluating its parameters and if they did not match, it would perform improper read/write operations resulting in memory corruption.

It was a big problem that a mistake as simple as mismatched amount and/or types of arguments could result something as bad as undefined behavior. Function declarations have been added but they weren't initially as detailed as today - they only stated function name and return type.

.. cch::
    :code_path: non_prototype.c
    :color_path: non_prototype.color

The :cch:`(void)` thing does not specify an argument of type :cch:`void` (you can not have objects of this type). It's a special syntax to differentiate it from old *non-prototype function declaration* syntax. Without this rule, both new and old syntax would look the same for functions taking 0 parameters - this would break existing code by changing its meaning.

In other words, since C89 functions can be properly declared (with parameter types) but due to backwards compatibility and the fact that ``()`` already had a meaning, :cch:`(void)` is needed for functions taking 0 parameters.

**In C++, there is no such problem.** C++ has no *non-prototype function declarations*, ``()`` works as expected. :cch:`(void)` is supported only for compatibility with C code imported to C++.

.. cch::
    :code_path: void_param.cpp
    :color_path: void_param.color

Summing it up, writing :cch:`(void)` in C++ is a mistake. It comes from misunderstanding how function declaration syntax evolved in C and how it works in C++.

Exercise
########

Take the example of cross-dependent functions and swap their order so that a different function has to be declared first.
