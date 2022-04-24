.. title: 04 - abstract classes
.. slug: index
.. description: pure virtual functions and abstract classes
.. author: Xeverous

The animal-cat-dog example in the previous lesson demonstrated how :cch:`virtual` functions work and their primary purpose - implementing different behavior that can be invoked through the same interface.

Constructing objects of the base type alone (:cch:`animal$$$type`) doesn't make much sense. We can make the :cch:`animal$$$type` constructor :cch:`protected` so that derived classes can call it but not any code outside the class (this is actually done sometimes). This would still allow inheriting but effectively block creation of objects of the base :cch:`animal$$$type` type.

But there is another problem. What to do with the implementation of the virtual function in the base type? Functions at the top level of inheritance hierarchy often can not have any meaningful body. But the code must compile.

In the case of :cch:`animal$$$type` the function simply returned a dummy string to satisfy the compiler. But what if in a hypothetical base class the return type of a :cch:`virtual` function had no default constructor? What if there was no way to return sensible special value?

The problem could be dealt with in a generic way by using *exceptions* or functions that perform some halt/exit but there is a much better solution through a dedicated language feature.

Pure virtual functions
######################

A **pure virtual function** is a virtual function that has no body.

A class with at least 1 *pure virtual function* is an **abstract class**. **Objects of abstract types can not be created** (pointers and references to abstract types are still allowed).

.. cch::
    :code_path: animal_cat_dog.cpp
    :color_path: animal_cat_dog.color

You can attempt to modify this example just like the the one in the previous lesson (change :cch:`print_sound$$$func` function to take argument by value) but this time, instead of causing undesirable object slicing the program will not compile. Since objects of abstract types can not exist, passing them by value (which requires creation, copy or slicing) is also impossible.

It's worth noting that in C++ you can still define bodies of pure virtual functions (the body has to be outside the class - there is no syntax support for both :cch:`= 0$$$= num` and :cch:`{}$$${}` in one place). The class will remain abstract, but the function can be called through usual means - usually inside bodies of the same virtual function in derived classes.

There is no requirement for implementing all pure virtual functions in derived classes. A derived class can implement only some of them, making itself also an abstract type. Even more, any further derived class can "repurify" a non-abstract class by specifying non-pure virtual functions as pure virtual functions (though IIRC this feature is not present in many languages and I don't know any example where the feature is useful).

Virtual functions vs other features
###################################

Polymorphism can be a lot of fun, but due to its dynamic nature some specific language features should not be combined with virtual functions or be combined in special ways to avoid creating unwanted surprises.

Default arguments
=================

Function default arguments are evaluated at the point of each call. This means that for something like :cch:`void f(int n = g())$$$keyword func(keyword param = func())` everytime the function is called with no explicit parameters, :cch:`g$$$func` will be called to supply the parameter (as if the call was :cch:`f(g())$$$func(func())`). Default arguments almost always are literals or other simple expressions that produce temporary objects but the problem still remains: **default arguments are not inherited**, which means they need to be respecified at each level of inheritance.

Respecifying default arguments at every level of inheritance is nothing more than code duplication. And we know that it's one of the worst things in programming. Even worse is the fact that if there is a mistake in the derived class, a different evaluation will happen depending whether the function is called in the context of base or some derived class.

The problem can be solved in a very clean way: just use overloading! Specifically, write **additional non-virtual overloads only in the base class** that supply default arguments. Below a beautiful example that just came to my mind:

.. cch::
    :code_path: virtual_functions_default_arguments.cpp
    :color_path: virtual_functions_default_arguments.color

Overloading is actually more powerful than default arguments, in this specific example you can observe that the default value of precision comes from another :cch:`virtual` function! Another benefit is that any derived class needs only to write one overload (and :cch:`using timer::start;$$$keyword type::func;` to avoid hiding base class overloads if they are called directly in the context of some derived type).

Overloading
===========

The same function can have multiple :cch:`virtual` overloads but this is generally a bad design because effectively it forms multiple chains of virtual functions that just happen to use the same name. Having to :cch:`override` multiple functions that differ very little signifies that the interface (base class) wasn't designed properly. And bad interfaces attract (and sometimes even force) suboptimal implementations.

In cases where there is a need for multiple, different inputs it would be much better to stick to the same approach as with default arguments: design only 1 virtual function and multiple non-virtual overloads that convert input data to match the one expected by the virtual overload.

Supporting only 1 input type may seem limiting, but it's much better to have an unchangeable set of input-converting non-virtual functions than expecting derived classes to additionally implement their own convertion (a great place for subtle bugs caused by differences in behavior).

Operator overloading
====================

Operators which are defined as member functions can be :cch:`virtual`, they work just like any other function - the only difference is that they have special name and offer special syntax.

What do to when an operator should or must be implemented as non-member? Just call a virtual function inside it (sometimes this might require creating a virtual function just for the purpose of implementing the operator):

.. cch::
    :code_path: virtual_operator_overload.cpp
    :color_path: virtual_operator_overload.color

Stream insertion/extraction is very different from other binary operators though - it's not commutative. For something like :cch:`a + b` (where there are 2 objects from the same type hierarchy):

- implementing it as :cch:`a.func(b)$$$var_local.func(var_local)` will call implementation based on the dynamic type of :cch:`a$$$var_local`
- implementing it as :cch:`b.func(a)$$$var_local.func(var_local)` will call implementation based on the dynamic type of :cch:`b$$$var_local`

If such thing happens, using operator overloading was probably a bad decision (polymorphic classes rarely overload operators). If the implementation of the operation requires knowledge of dynamic types of both operands, *visitor design pattern* should be used instead.

Constructors
============

Virtual functions can be called in constructors (and *destructors* - these are covered in other tutorial, in the chapter about RAII), but there is a limitation. Because during construction the object may only be partially initialized (the *dynamic type* might be a type derived from the type of which currently a constructor is running) virtual calls in constructors are resolved only down to the level of the current class (analogical but reverse thing happens in destructors - object is partially destroyed). To illustrate:

.. cch::
    :code_path: virtual_functions_in_ctor.cpp
    :color_path: virtual_functions_in_ctor.color

.. code::

    B::f

Inside the body of :cch:`B::B$$$type::func`, it's unknown whether the constructor is run to initialize an object of type :cch:`B$$$type` or as a part of initialization of an object which type inherits from :cch:`B$$$type`. Since the constructor can not assume what is the actual (*dynamic*) type of the constructed object (and even if it could, that part is still uninitialized), virtual call considers overriders only to the level of class :cch:`B$$$type`.

What if there are no overriders at the level of currently running constructor (that is, function remains pure virtual)? Well, nothing good:

.. admonition:: note
  :class: note

  A direct or indirect call to an unimplemented pure virtual function from a constructor or destructor has undefined behavior.

Reminder: UB also includes situations such as "doesn't compile" and "doesn't link". Some pure virtual calls might be caught by the linker (missing symbol definition). Some might crash in a very friendly way - I have seen GCC providing implementations for pure virtual functions so that if they happen to be called through UB, the body of the function prints an explanatory message and kills the program (this is much better than manually searching the cause of an unknown crash).

`CG C.82 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-ctor-virtual>`_ recommends to avoid virtual function calls in constructors and destructors. If initialization of the object requires such things (which is not always a bad design), use the *named constructor* approach, as described in `classes / static methods <link://filename/pages/cpp/tutorials/beginner/xx_classes/08_static_methods/static_methods.rst>`_ - write a :cch:`static` function that creates the object, calls necessary virtual functions and then returns it.

.. TODO it would be good to have some exercises to showcase example output of specific cases
