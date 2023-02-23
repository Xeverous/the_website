.. title: 02 - instantiation
.. slug: index
.. description: template instantiation and 2-phase translation
.. author: Xeverous

Anywhere a type or value appears it can be substituted with a template parameter. The types may be even *incomplete* if operations they are used with allow it. The only restriction is that the code formed by template subsitution mechanism is itself valid.

.. cch::
  :code_path: invalid_substitution.cpp

As you can see, the :cch:`f2$$$func` has return type :cch:`T` and no return statement. If the template parameter is :cch:`void` the function is valid. :cch:`f3$$$func` looks like it could work on any pointer, yet because forming references to void is not allowed, compilation of this function template combined with :cch:`void` template parameter will fail.

The example leads to an interesting conclusion:

.. admonition:: note
  :class: note

  When writing templates, errors may appear only when they are used with specific template parameters.

The act of using a template with specific template parameters is called **template instantiation**.

.. admonition:: note
  :class: note

  Each template instantiation can generate different machine code (or different compiler errors).

2-phase translation
###################

Because of instantiation, the code of each template is analyzed twice:

- First, when a definition is encountered. The compiler can not compile the code yet, but it checks the syntax and code that does not depend on template paramaters.
- Second, when a template is instantiated. Template-parameter-dependent code is now turned into non-template code and compiled.

The first step happens once for every template entity in the given translation unit. The second step (instantiation) can happen multiple times. Each instantiation can result in different compiler errors.

The 2-phase nature is best demonstrated with another example. The following program will fail with every possible instantiation (no type has size zero and :cch:`sizeof(void)` is *ill-formed*) but the 1st phase will succeed:

.. cch::
  :code_path: 2_phases.cpp

A program will compile successfully if this function template is never used. No instantiation - no errors.

  Why is the non-existent function not causing any errors? How is the template parameter relevant to it? Searching for a function declaration/definition doesn't depend on the type of the argument, right?

It does. But not on the template argument itself, but on the namespace of the argument. ADL (*argument dependent lookup*) means that functions are searched in the global namespace but also in namespaces of the arguments. This rarely-thought-of mechanism is the reason why overloaded operators work - they are functions that are often defined in namespaces of the types they support.

  What if the compiler is smart enough to figure it out that it's impossible to instantiate this function template successfully?

It can not be. The language specification dictates that statements dependent on template parameters (in any semantic way possible) are analyzed only at the second (instantiation) phase. It would also be computationally expensive to implement to handle more complex situations.

You can make this example fail in the first phase by modifying it to have :cch:`static_assert(false)`. Such statement is not dependent on template parameters and will be caught in the first phase, before any instantiations.

When working with templates, you will typically encounter compiler errors coming from the second (instantiation) phase. GCC and Clang will include "in instantiation of" string with template parameters in the diagnostic message if the error comes from this phase.

When receiving instantiation errors, you need to think which might be incorrect:

- the template definition
- the template parameter (this specific instantiation)

In typical situation, it's a mistake how the template is being used (usually a wrong type parameter). Rarely you may write a template that accidentally limits possible uses and it's the template definition that requires changes. Subtle changes in the definition (e.g. :cch:`T()` vs :cch:`T{}`) may alter meaning for some types and have no effect for others.

Declarations
############

Just like any non-template entity, templates can be forward declared too:

.. cch::
  :code_path: min_fwd_decl.cpp

In the case of templates it's done rarely because **the template definition (and all specializations) must be present before the first instantiation**.

The reason is simple: **templates are ODR-used upon instantiation**. The compiler can not enter second phase if it knows only the declaration of the entity. The primary use of declarations is resolving dependencies between templates themselves - a good example would be a set of function templates that can call each other recursively. For this reason declarations of template entities are generally rare.

Because of the requirement that a definition must be visible at the point of instantiation and the fact that templates are implicitly :cch:`inline`, they are typically put into header files.

.. TODO move the paragraph below to a separate article and develop it further?

Some library projects list all template declarations first and then write or include their definitions at the bottom of the file. This separates interface/implementation similarly to ordinary non-template code (2 separate files) while still technically delivering all necessary information to the compiler within a single header. It's a lot more code to write but it improves readability if the headers are a primary source of documentation and users of the library are expected to read comments within the source code. Having definitions separately reduces the noise while reading documentation comments.

.. TODO section about constexpr?
