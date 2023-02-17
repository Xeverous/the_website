.. title: 05 - explicit and std::initializer_list
.. slug: index
.. description: converting constructors, explicit and std::initializer_list
.. author: Xeverous

Now you should understand that constructors offer the ability to control object initialization. There are 2 further minor features.

Convering constructors
######################

.. admonition:: definition
  :class: definition

  A constructor that is declared without the function specifier :cch:`explicit` is called a converting constructor.

Since the keyword :cch:`explicit` wasn't used in any prior example, all constructors written so far were *converting constructors*.

What does it mean? It means that the call to the object constructor is allowed to perform *implicit convertions* if necesary. A good example is :cch:`std::string` which has a non-\ :cch:`explicit` constructor overload accepting pointers to character arrays. This allows to do such things:

.. cch::
  :code_path: std_string_converting_ctor.cpp

The function accepts an object of type :cch:`std::string`, however the argument is an array of characters (:cch:`const char[7]$$$keyword keyword[num]` to be specific - 5 characters, 1 escaped character and null terminator). Because :cch:`std::string` has a non-\ :cch:`explicit` constructor overload that accepts :cch:`const char*`, there is no "function parameter/argument type mismatch" error. The compiler notices that the provided argument is not of type :cch:`std::string` but it also notices that it can be constructed from the provided argument.

Reminder: function arguments passed by value always undergo a set of implicit convertions (*decay*) where most notably top-level :cch:`const` is stripped and raw arrays (:cch:`T[N]`) lose size information and become raw pointers (:cch:`T*`).

Adding :cch:`explicit` to constructors simply disallows implicit convertions (other than decay) and some forms of initialization:

.. cch::
  :code_path: explicit.cpp

This leads to the question - **when should a constructor be marked** :cch:`explicit`?

.. admonition:: tip
  :class: tip

  `CG C.46 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-explicit>`_: By default, declare single-argument constructors :cch:`explicit`.

This is because implicit convertions are generally undesirable. For few cases where the convertion is desired (such as :cch:`fraction fr = 1;$$$type var_local = num;`) some people write :cch:`/* implicit */$$$0com_multi` before the constructor to signify it's intentionally not marked :cch:`explicit`.

:cch:`std::initializer_list`
############################

Not to be confused with member initialization syntax, this simple class is intended to hold arbitrary amount of arguments of specific type for the purpose of initialization. The class is implemented as lightweight proxy object. Copying :cch:`std::initializer_list` does not copy underlying objects and objects from the list are read-only.

Because :cch:`std::initializer_list` is intended for construction of other objects, it has special rules for its own construction:

- It is automatically constructed when constructors accept it as a parameter and the syntax used to initialize is ``{}`` or ``=``.
- It is automatically constructed from braced init lists that are bound to :cch:`auto`.

.. cch::
  :code_path: std_initializer_list.cpp

This can be particulary surprising when a type has multiple overloads, some of which use this special class:

.. cch::
  :code_path: init_list_ctor.cpp
  :color_path: init_list_ctor.color

In such case my recommendation is to write :cch:`v2 = {5, 2}$$$var_local = {num, num}` which is much clearer about intent.

    How about combining :cch:`explicit` with :cch:`std::initializer_list`?

Don't. The whole point of :cch:`std::initializer_list` is to offer syntax sugar for construction, without having to explicitly write the class name.
