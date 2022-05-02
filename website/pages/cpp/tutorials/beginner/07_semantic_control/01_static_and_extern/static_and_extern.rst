.. title: 01 - static and extern
.. slug: index
.. description: storage duration and linkage
.. author: Xeverous

:cch:`static` is a pretty overloaded keyword in C++. It's meaning depends on the context:

- when applied to a function-local objects, modifies their *storage duration*
- when applied to a global object or a function definitions, modifies their *linkage*
- when applied to data or function member of a class, modifies its semantics and both *storage duration* and *linkage*

This lesson will explain first 2 contexts.

Function-local :cch:`static` objects
####################################

Objects are being destroyed when their scope ends - basically enclosing ``}``. But this is not the case in the following program:

.. cch::
    :code_path: function_local_static.cpp
    :color_path: function_local_static.color

.. code::

    x is now 1
    x is now 2
    x is now 3
    x is now 4
    x is now 5


The variable acts as if it lived beyond the function body - and in fact, this is what happens for objects with **static storage duration**. This brings us to the topic of this lesson.

Storage duration
################

C++ specifies 4 kinds of object lifetime.

- **automatic storage duration** - basically everything you have used so far. Objects are limited by enclosing braces and die when they go out of scope. This is the default storage duration for everything.
- **static storage duration** - object is created when the program starts or on first use and destroyed when the program ends. This applies to:

  - global objects
  - objects declared with :cch:`static`
  - objects declared with :cch:`extern` (all external objects are global)

- **thread storage duration** - similarly to static, but with the difference that the object is created when the thread launches and destroyed when the thread finishes. Each thread will have its own (independent) instance of the object. Aplies to objects declared with :cch:`thread_local`.
- **dynamic storage duration** - object is (allocated and/or created) and (deallocated and/or destroyed) explicitly. Related with resource management. Opens many powerful features but often comes with a cost. Done through :cch:`new`, :cch:`delete`, *placement-new* and *pseudo-destructor calls*.

.. admonition:: note
  :class: note

  Only one *storage class specifier* may appear in a declaration except that :cch:`thread_local` may be combined with :cch:`static` or with :cch:`extern`.

.. admonition:: note
  :class: note

  :cch:`thread_local` overrides :cch:`static` / :cch:`extern` when both are used in one declaration.

.. admonition:: note
  :class: note

  When given no initializer, global :cch:`static` objects are zero-initialized.

  .. cch::
    :code_path: static_zero_init.cpp
    :color_path: static_zero_init.color

Function-local :cch:`static` objects behave differently from global :cch:`static` objects and functions. Let's move to another example.

:cch:`static` functions
#######################

.. admonition:: note
  :class: note

  This example showcases a static free function. :cch:`static` has a different meaning for *member functions* and it will be covered in the classes chapter.

.. cch::
    :code_path: static_function.cpp
    :color_path: static_function.color

When trying to build the program, we get a surprising output. First, a warning is emmited. Then the build fails but at the linking stage, not compilation:

.. ansi::
    :ansi_path: static_function.txt

So what has actually gone wrong? :cch:`static`, when applied to free (AKA *non-member*) functions changes their **linkage**. First, the compiler warns that a :cch:`static` function has been declared but not defined. This isn't usually a problem - definitions of many things can be placed in another *translation unit*. But in this case, it is a problem. The keyword has informed the compiler that the function should have *internal linkage* instead of default *external linkage* for functions, which led to the linker error.

Linkage
#######

cppreference:

    A name that denotes object, reference, function, type, template, namespace, or value, may have linkage. If a name has linkage, it refers to the same entity as the same name introduced by a declaration in another scope. If a variable, function, or another entity with the same name is declared in several scopes, but does not have sufficient linkage, then several instances of the entity are generated.

Said differently, linkage affects how an entity is seen by other code. Entities with insufficient linkage will not be visible to other entities. The simplest example are variables defined locally in different functions - they just don't see each other and thus can have the same name while being separate objects.

There are 3 kinds of linkage:

- **no linkage** - name can be referred only from the scope it is declared. Applies to:

  - all objects declared without :cch:`extern`
  - everything else declared locally (inside a function)

- **internal linkage** - name can be referred from all scopes in **current translation unit**. Applies to:

  - objects and functions declared :cch:`static`
  - members of *anonymous unions*
  - members of *anonymous namespaces*

- **external linkage** - name can be referred from all scopes in **any translation unit**. Applies to:

  - objects declared :cch:`extern`
  - basically everything else which is not :cch:`static`

Combing to the example,

- The compiler emmited a warning that the function is used but not defined because it knew that due to :cch:`static` the function could not be defined in a different TU.
- The linker could not find the definition for the function because the compiled function had *internal linkage*. It was not accessible outside its own TU.

The example showcased a function but a global :cch:`static` object would have a similar problem. But instead of ending in a linker error, it would create a different object with the same name for each TU. This is because :cch:`static` objects (unlike functions) can not be just declared, the statement already forms a definition. The exact same problem would reproduce if the header used :cch:`extern` and source :cch:`static`.

:cch:`extern`
#############

Functions by default have *external linkage*. :cch:`extern` can be added to them, but is not necessary.

But the same is not true for global objects. If you write something like :cch:`int x;$$$keyword var_global;` in a header file, it will create a different object for each TU that includes such statement. This is because for objects (unlike for functions), there is no immediate way to differentiate a declaration from a definition. Function declarations are easily tell apart from definitions due to the lack of body. But for objects, you need to write :cch:`extern int x;$$$keyword keyword var_global;` in order to change the meaning from definition to just a declaration. Such declaration can then be included as many times as needed and exactly one TU should define it. That's basically how you create a global object that is shared across TUs.

.. cch::
    :code_path: extern_object.cpp
    :color_path: extern_object.color

:cch:`extern "C"`
#################

Specific entities (function types, functions and global objects) with *external linkage* also have *language linkage*. This feature allows to link code defined in different programming languages and is the standard way of C/C++ interoperatibility at the binary (compiled code) level.

The standard mandates support of only :cch:`extern "C"` and :cch:`extern "C++"` but an implementation is allowed to support more.

For a detailed explanation how to use *language linkage*, read TODO link.

You may also be interested in:

- `SO: What does it mean for a name or a type to have a certain language linkage? <https://stackoverflow.com/questions/5763919>`_
- `SO: C++'s extern "C" functionality for languages other than C <https://stackoverflow.com/questions/21484500>`_

Static initialization order fiasco
##################################

Initialization of global objects across TUs has *undefined* order. **If one's object initialization depends on another object that is defined in a different TU, the behavior is undefined.**

Workaround: since these objects are already related, put them in a :cch:`struct`. Now you can write a function (*constructor* or a free function) that will have *well-defined* order.

https://isocpp.org/wiki/faq/ctors#static-init-order

In practice
###########

At this point you might be wondering - what's the point of :cch:`static` functions and objects?

They serve multiple purposes:

- Less entities with large linkage means less work for the linker. This speeds up the build process.
- Code clarity: when seeing a declaration or a definition of a :cch:`static` function or a :cch:`static` global object, you are sure it's not being used in other TUs.
- The same function name can be reused for multiple functions in different TUs as the :cch:`static` effectively reduces their visibility to a single TU.
- If the project is built as a library (*static* or *dynamic*), the resulting binary object size is smaller as entities without *external linkage* do not have to be reported there.

The reality is a bit more complicated than what C++ specification covers, although the same concept applies. It's just more detailed because modern systems support both *static linking* (merging compiled code into an executable) and *dynamic linking* (loading compiled code from separate files - usually named ``*.so`` (*shared object*) on POSIX systems and ``*.dll`` (*dynamic link library*) on Windows).

GCC, when speaking of linkage on implementation-level calls it **visibility**. `This article on GCC wiki <https://gcc.gnu.org/wiki/Visibility>`_ explains benefits of using detailed support for symbol visibility. Macros like the ones presented in the article have become the conventional way of writing libraries. In C++20 the situation has been further improved by introducing **modules**, a C++ standard way of specifying which code is public (for others to use) and which code is private (implementation detail).

.. details::
  :summary: Article clarifications

  - DSO means the same thing as dynamic library
  - C++ doesn't specify beyond *translation unit*. In reality we can also speak about *library units*. ``-fvisibility=hidden`` and :cch:`__attribute__ ((visibility("hidden")))$$$keyword ((ext(str)))` allow to mark code with *external linkage* for working across TUs but not across *library units*.

Summary
#######

*Storage duration* (lifetime) and *linkage* (visibility) are 2 independent properties of each object.

Cheatsheet:

- objects with *automatic* and *dynamic* *storage duration* always have *no linkage*
- objects with *static storage duration*:

  - *no linkage* - function-local :cch:`static`
  - *internal linkage* - global :cch:`static`
  - *external linkage* - global :cch:`extern`

- objects with *thread storage duration*:

  - *no linkage* - :cch:`thread_local`
  - *internal linkage* - :cch:`static thread_local`
  - *external linkage* - :cch:`extern thread_local`

Can you guess *storage duration* of :cch:`std::cout`?

.. details::
  :summary: answer

  *static*

Can you guess *linkage* of :cch:`std::cout`?

.. details::
  :summary: answer

  *external*

Recommendation
##############

- Avoid function-local :cch:`static` objects. They are essentially global variables, just with reduced accessibility.
- Never write declarations or definitions of :cch:`static` functions and :cch:`static` global objects in a header file. Since such entities have *internal linkage*, there are no reasons for other TUs to see them.

.. admonition:: note
  :class: note

  It's unlikely that you will remember everything from this lesson. You don't have to. Just understand that *storage duration* and *linkage* are independent properties and come here later when you have a problem.
