.. title: 03 - virtual functions
.. slug: index
.. description: how virtual functions work; object slicing
.. author: Xeverous

All examples so far used relatively simple code that uses inheritance as a class extension mechanism. In this lesson I will showcase the main feature of object-oriented programming: *virtual functions*.

This very unique feature allows to *implement* or *override* base class code, not *extend* it. The absolutely most classical example is the animal-cat-dog hierarchy, which examples will start in this lesson and be incrementally improved as more features are explained.

Example
#######

.. cch::
    :code_path: example.cpp
    :color_path: example.color

output:

.. code::

    meow
    whoof

Unlike examples in the lesson about shadowing, **virtual functions are always resolved based on the dynamic type**. Even though :cch:`print_sound$$$func` takes a reference to the base :cch:`animal$$$type` class, it calls :cch:`sound$$$func` function based on the actual type of the object, which is unknown to the :cch:`print_sound$$$func` function.

Virtual functions open up a world of dynamic behavior, where a code written against an *interface* (here: the base :cch:`animal$$$type` class) can exhibit different behavior depending on the dynamic type of the object. Multiple types can satisfy one *interface*, promoting code reuse, allowing complex interactions and at the same time avoiding strong coupling - the only area where code "must match" is the base class. Each derived class can contain its own implementation, which modifications do not require changes in external code like the :cch:`print_sound$$$func` function.

Standard library streams are another example - all share the interface of reading and writing data but how and where exactly the data is written depends on the actual stream (standard I/O, file I/O, network and so on...). You can even create your own stream class that inherits one (or more) from the standard library and use it just like any other. Because it will be a derived type, everything that works on the base will also work with it - this includes stuff like overloads of :cch:`operator<<`.

How it works
############

Virtual functions can be implemented in multiple ways, but majorty of programming languages (including C++) use roughly the same mechanism.

When a class contains at least 1 :cch:`virtual` function, the compiler inserts an additional, hidden field into the class (which is then inherited by all derived classes). This magic field is typically referred to as **virtual table pointer** (**vptr** for short). The pointer is set in the constructor to refer to specific **virtual method table** (**vtable** for short). Vtable holds an array of pointers to actual function implementations. Objects of the same dynamic type will have the same value of vptr - they will refer to the same table of actual functions.

Calling a virtual function works this way:

- read vptr in the object (this is always possible because vptr is already present in the base type)
- go to vtable referenced by vptr (different dynamic types will refer to different tables)
- call a function present in the vtable on the current object

Virtual tables are formed during compilation and embedded in the binary object, typically in some read-only section.

.. TODO some vtable infographic?

The mechanism itself is known as **dynamic dispatch**, in contrast to **static dispatch** where the address of the function is resolved at compile time. Other analogical terms are **late binding** and **early binding**.

Sometimes *binding* terms may also appear when the topic is about loading shared (dynamic) libraries (such files typically have ``*.so`` and ``*.dll`` names). The difference with loading libraries is that addresses are resolved once, upon library load while with virtual functions addresses are resolved every time a function is called. So virtual functions bind later than dynamically loaded machine code which binds later than statically linked machine code.

.. admonition:: note
  :class: note

  :cch:`static` functions can not be :cch:`virtual`.

The reason should be obvious: static functions are not tied to any object while virtual functions require an access to vtable which is done through vptr in the object.

Performance
###########

Virtual function calls impose an overhead - the address of the function is not immediately known - it has to be fetched from the vtable and vtable's address must be fetched from the object. This process isn't very computationally expensive (just 2 jumps in machine code) but the virtuality itself blocks multiple optimizations that happen across function boundaries. Generally it's not possible to inline virtual function calls because at the point of compilation it's unknown what the dynamic type of the object is (in cases where the compiler can determine the dynamic type it will *devirtualize* the call by using appropriate function address directly).

Depending on the function size, the overhead might or might not be significant. The more a function does, the smaller is the proportion of the overhead (the cost is constant) to the whole.

Terminology
###########

**Polymorphism** is the act of using multiple different types through one interface that is shared between them.

In C++ we can differentiate 2 kinds of polymorphism:

- **Static polymorphism**, where the operation uses compile time information. A good example is a set of multiple function overloads. The same function (by name) can work differently depending on the type of the object. The interface here is the function (the name shared across overloads).
- **Dynamic polymorphism** (more often referred to as **runtime polymorphism**) where the operation uses runtime information. The interface here is the base class with its virtual functions, which is shared across derived classes.

A class that has at least 1 virtual function is a **polymorphic type**.

Object slicing
##############

Previously it has been mentioned that dynamic types only make sense when the object is accessed through a pointer or a reference.

Modify the example to have :cch:`void print_sound(animal a)$$$keyword func(type param)` and observe the result.

.. details::
    :summary: result

    .. code::

      ???
      ???

Suddenly virtual functions stopped working, all calls are performed as if :cch:`virtual` was not used. You can try something like :cch:`animal& ref = a;$$$type& var_local = var_local;` inside the function but it won't revert the behavior.

The problem is that now the function doesn't work on the object directly **but on the copy of the actual object**. Even worse, **this is a sliced copy**. The function call only copied the subpart of the object that the function expects, effectively creating a partial copy (sliced copies will have vptr modified to vtable of their class).

Types that are cheap to copy can be passed by value, but this guideline no longer applies when you want to call :cch:`virtual` functions. You simply should not copy *polymorphic* objects into functions. Because each derived type is different there is no way to properly copy them in a generic way (except writing a separate overload for each but this defeats the purpose of virtual functions).

.. admonition:: tip
  :class: tip

  Avoid object slicing. Do not pass polymorphic objects by value.

Existence of slicing also means that something like :cch:`std::vector<animal>$$$namespace::type<type>` will not be able to store objects of types :cch:`cat$$$type` and :cch:`dog$$$type`. Workarounds will be presented in later lessons.

:cch:`override`
###############

Technically, :cch:`override` and :cch:`final` are not keywords but *identifiers with special meaning*. They were added in C++11 and because a lot of existing code already used these words, they are not specified as keywords to not break such code. They have their keyword-like behavior only in specific contexts. Obviously if you write any new code you should treat them like keywords and not use them for anything else to avoid unnecessary confusion.

:cch:`override` is not necessary, but it has been added to C++ (at the time where many other languages already had it) to inform the compiler that it should verify that the function is in fact an implementation of a :cch:`virtual` function from some base class. If a function has :cch:`override` specified but does not match any :cch:`virtual` function in any base classes, the program is *ill-formed*.

Prior to C++11, some programmers used the convention to write :cch:`virtual` in front of every virtual function to signify that the function is virtual (this is allowed but not necessary - writing :cch:`virtual` in the base class alone is enough). This can create another problem: if there is a mistake within the function (which will cause it to not match base class function), it will start another virtual function from the current class:

.. cch::
    :code_path: accidental_virtual.cpp
    :color_path: accidental_virtual.color

.. code::

    base::f
    base::f
    more_derived::f

In the example above there are actually 2 virtual function chains:

- :cch:`void f(double)$$$keyword func(keyword)` that starts in :cch:`base$$$type`
- :cch:`void f(float)$$$keyword func(keyword)` that starts in :cch:`derived$$$type`

Overriding virtual functions is not necessary - if it's not overriden the vtable for the current class will have the address of such function copied from it's parent class. You can even do things like this:

.. cch::
    :code_path: virtual_function_using_base.cpp
    :color_path: virtual_function_using_base.color

There might be also an additional code in such function definition. When done at every inheritance level, it can be an implementation of the *decorator pattern* where instead of replacing base class function it's being augmented with additional code.

:cch:`final`
############

:cch:`final` is written in the same place where :cch:`override` is and informs the compiler that no further overrides are possible. If a derived class attempts to override a function marked :cch:`final`, the program is *ill-formed*.

:cch:`final` can also be applied to classes: :cch:`class more_derived final: public derived$$$keyword type keyword: keyword type` specifies that no class can inherit from :cch:`more_derived$$$type`. If such thing is attempted, the program is *ill-formed*.

In both cases, you should be very cautious about using :cch:`final`. It artificially limits the code for further extension - you must have a very good reason to forbid overriding or further inheritance. In practice, :cch:`final` is only used when implementing specific *design patterns* which are known to never have a need for further extension (:cch:`final` sometimes lets the compiler perform some optimizations).

.. admonition:: tip
  :class: tip

  Because :cch:`override` implies :cch:`virtual` and :cch:`final` implies :cch:`override` in any case you should use exactly 1 of these (`CG C.128 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override>`_).

Exercise
########

What's the output of the following program?

.. cch::
    :code_path: exercise_slicing.cpp
    :color_path: exercise_slicing.color

.. details::
    :summary: hint

    :cch:`b_ref = d2$$$var_local = var_local`

.. details::
    :summary: answer

    .. code::

      d1.b: x
      d1.d: b

.. details::
    :summary: explanation

    Assignment through a reference to base causes object slicing: only the base subobject of the :cch:`d2$$$var_local` object is assigned to :cch:`d1$$$var_local`. This results in a partially assigned object with mixed state from :cch:`d1$$$var_local` and :cch:`d2$$$var_local`.

    How to properly copy polymorphic objects is described in a later lesson in this chapter.
