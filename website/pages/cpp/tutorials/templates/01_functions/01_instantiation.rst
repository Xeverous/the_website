.. title: 01 - instantiation
.. slug: 01_instantiation
.. description: C++ function templates - instantiation
.. author: Xeverous

Using templates
###############

Template code is used just like any other code except that the compiler needs to know what to substitute in place of specified aliases (here ``T``). Function templates have special feature called **template argument deduction** which lets the compiler figure it out.

.. TODO compile example

.. cch::
    :code_path: 01_instantiation/min_used.cpp
    :color_path: 01_instantiation/min_used.color

You might already wonder what happens if the deduction results in ambiguity or if it can not be performed at all (which is the case for function templates with 0 parameters) - more on this in the next lesson.

Instantiation in detail
#######################

C++ templates are a fully compile-time mechanism. They are not "real compilable code" (you can't e.g. take an address of a function template) but a recipe for making compilable code. The compiler can only generate machine code when it knows all necessary information about the entity. The act of using a template and providing that information is called **template instantation**.

.. admonition:: note
    :class: note

    Each template instantiation can generate different machine code (or different compiler errors).

Whenever a template is instantiated, the compiler replaces aliases with explicitly specified or deduced types/values. **In order to do this operation, a definition of the templated entity must be available.** This follows ODR which you should already know - ODR-using an entity without a definition is an error.

Because of the requirement that a definition must be visible at the point of instantiation, if you want to use template in multiple files you need to put its definition in a header. This arises 3 questions:

- When is template code parsed? When first read or when instantiated?
- Do templates have declarations or only definitions?
- What happens with duplicate instantiations of the same template?

2-phase parsing
===============

.. TODO does it have a formal name?

The code for C++ templates is analyzed twice.

- First, when a definition is encountered. The compiler can not compile the code yet, but it checks the syntax and code that does not depend on template paramaters.
- Second, when a template is instantiated. Only then the code is compiled.

This has specific consequences:

- If you make an obvious mistake (e.g. a syntax error) it will be caught at the first step.
- If the code is invalid upon instantiation, the compiler error will specify for what template parameters instantiation has failed and where the instantiation has been triggered. It is possible that only for certain types/values the code makes sense. In the minimum function, the code only makes sense if the used type has defined :cch:`operator<`.

Template declaration
====================

As ODR states, every definition is also a declaration. Templates can be declared too:

.. cch::
    :code_path: 01_instantiation/min_fwd_decl.cpp
    :color_path: 01_instantiation/min_fwd_decl.color

Is there any need though? A full definition is required to use the template. Do template declarations have any use? The answer is yes, there are 2 major situations where template declarations are useful:

- Cross-dependency between templates. If you have 2 functions that can call each other, you need to declare at least 1 of them in order to write the definition of the second one. Exactly the same happens with function templates - it's nothing new.
- Unevaluated contexts. They are pretty rare but there are some template tricks which need only declaration. In fact, writing a definition in such cases could be very problematic.

In practice, both of these situations are rare so template declarations are rarely seen. Some projects which have a lot of templates use them to split code in a special way:

- template declarations (usually with lots of documentation comments) in a header file
- template definitions (usually lots of code) in a separate file (usually the same name but with an ``.inc``, ``.inl`` extension) that is :cch:`#include`\ d at the end of the header.

This practice allows to reduce noise in headers (especially if they are indended to be read by project users) while still technically delivering all required code in a header file.

Duplicate template instances
============================

You know that a duplicate definition is an error. If multiple non-inline definitions exist, it's an ODR violation. So what happens if different *translation units* instantiate a template the same way, resulting in multiple identical template-made functions? Nothing.

.. admonition:: note
    :class: note

    Templates are implicitly :cch:`inline`.

Thus, there is no problem at all.

Exercise
########

- Play with the minimum function presented earlier:
  - make a syntax error and observe compiler error triggered in first phase
  - make a semantic error and observe compiler error triggered in instantation phase
- Write an analogical maximum function.
- Write a class with overloaded comparison operator(s). Test that both functions work with the class.

If you encounter compiler errors you can not easily solve - move to the next lesson. There is still a lot to explain.
