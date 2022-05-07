.. title: 05 - const
.. slug: index
.. description: const member function qualifier
.. author: Xeverous

So far we have talked about member functions and how they can shield the class from undesirable use. This lesson extends the topic, covering few very common kinds of member functions.

.. The only exception is that constructors can not have any member function qualifiers - they would not make any sense anyway since at the point of the call no object exists yet.

Setters:

- primary purpose: change data members (they *set* things)
- secure class **invariants**.
- function names often start with ``set``
- such functions almost always return :cch:`void` (if not, it's usually :cch:`bool` to indicate whether operation succeeded)

Getters:

- primary purpose: obtain information (they *get* things)
- function names often start with ``get`` (return value of a private data member or compute something from them)
- almost always are read-only operations that do not change data members

Question-like functions (a subset of getters):

- very often return :cch:`bool`
- names usually start with ``is`` or ``has`` - for example: ``is_ready``, ``is_full``, ``is_open``, ``has_completed``,
- almost always are read-only operations that do not change data members

Action-like functions:

- primary purpose: modify the object to complete specific task
- names are formed like orders - for example: ``next_item``, ``load_file``, ``refresh``
- typically return one of:

  - :cch:`void`
  - :cch:`bool` (to inform if the operation succeeded)
  - specific data type that holds operation result and/or detailed error information

Action-like functions are the most broad group and usually they will contain most important code for any given class.

.. admonition:: definition
    :class: definition

    Getters are commonly referred as **accessors**. Setters as **mutators**.

Getters and setters do not always come in pairs - getters may combine information from multiple members and setters (and action functions) may change multiple fields. This all depends on class invariants.

Exercise
########

Recall :cch:`fraction$$$type` class from previous lessons. Can you assign each of its member functions a specific category?

.. details::
    :summary: Answer

    - ``set`` - setter
    - ``simplify`` - action
    - ``print`` - getter (although instead of returning it prints the values)

Member function qualifiers
##########################

In C++ member functions can have certain qualifiers:

- :cch:`const`
- :cch:`volatile`
- :cch:`&` - the lvalue reference qualifier or :cch:`&&` - the rvalue reference qualifier

In this lesson you will learn about the simplest of them - the const qualifier.

When applied to a variable, :cch:`const` prevents its modification. When applied to a member function, it prevents that function from modifying fields - it's as if all fields were :cch:`const` for the code inside the function. You can still do everything else in such function, the only restriction is on modifying member variables.

The fraction class already has a function that could use it - you probably already know which one.

Const-qualified member functions follow const-correctness:

- they can be called on const-qualified objects
- they can not call non-const-qualified member functions

Let's have an example (with improved :cch:`print$$$func` function - now it also supports other streams):

.. cch::
    :code_path: example.cpp
    :color_path: example.color

.. admonition:: tip
    :class: tip

    Getters should be const-qualified.

Don't get it wrong - do not const-qualify a function just becase it can be. Think what is the function's purpose and only then add :cch:`const` if it's a getter. Action-like functions should not be const-qualified even if they can (for whatever reason). If you make this mistake, there is a chance that the function implementation will change at some point in a way that prevents applying :cch:`const`. This can cause compilation issues in other code which was (incorrectly) using the class by relying on the action constness.

    Does const-qualifying a function help in optimization?

Generally no. :cch:`const` does not help the compiler except in few corner cases. It's much more of a help for the programmer to catch bugs related to object misuse.

Overloading on qualification
############################

Const-qualifying a function changes its type. This in turn allows overloading based on constness of the object. The following style of getters and setters is very popular in C++ (and often the recommended one):

.. cch::
    :code_path: overloading.cpp
    :color_path: overloading.color

This example presents multiple conventions, common in C++ code:

- Member variables are named with some prefix (usually ``m_`` or ``_``):

  - This avoids name clashes with method names.
  - This improves code readability of method implementations (member variables can be easily distinguished from function-local variables).
  - This helps with tooling (e.g. IDE autocomplete feature)

- Functions should generally be named as verbs but here they are named as nouns - they only return references to fields.
- There are 2 overloads which differ in const qualification and analogically their return type.

Which overload is choosen when a method is called? It depends on the constness of the object on which it is done.

- For const objects, the const-qualified overload is choosen which acts only as a getter.
- For non-const objects, the non-const-qualified overload is choosen which can be used both as a getter and as a setter.

The tradeoffs of this style:

- Such functions expose an implementation detail - the return type must match member type. If the class is later refactored to contain fields of different types, code which was using the class may also need to be changed.
- Since the setter does not take the value as a parameter but returns a reference to a field:

  - ...it no longer can control what is actually written to it. This makes the style undesirable if the class has invariants to enforce. For the :cch:`fraction$$$type` class, this style should not be used because the denominator has to be checked against zero.
  - ...the calling code can access field's methods, which allows significant code reuse. Example above accesses :cch:`std::string::operator=$$$namespace::type::keyword1func`.

In other words, the approach of returning a reference to the field offers code reuse (access to methods of the field) at the cost of coupling external code to the implementation (the type of the field).

Selecting desired overload
##########################

If an object is const-qualified, only const-qualified methods can be called. But in the opposite situation, both const and non-const overloads can be called. For a non-const object, **the compiler doesn't check how the function is used and what is done with it's return type (if non-void)** - it simply picks non-const overload for consistency.

In some situations, calling const-qualified overload on a non-const object is beneficial. This often happens for types which use COW (copy-on-write) implementation as an optimization.

For a type that implements COW, specific data is shared across multiple objects. Each object holds some form of access to a shared state (e.g. a pointer) and only such pointer is copied. This allows read operations for actual data from multiple places (potentially multiple threads) while not wasting memory by duplicating the data for each thread. If at any point in time, there is a need for modification, the object will create a new copy of the data and refer to this new copy. Many file systems use this optimization - copied files are not actually copied but only their metadata, a real copy is made only when one of users attempts to edit the file. Thus "copy-on-write" name. This approach of sharing identical copies is also known as *shallow copying* and is a part of *flyweight* design pattern.

In C++ COW can be used whenever there is a resource which is expensive to obtain (simplest example is dynamically allocated memory, such as buffers for strings). String types in many libraries (but not :cch:`std::string` in C++11 and later) are implemented with COW. Below is a hypothetical excerpt from such class:

.. cch::
    :code_path: cow_type.cpp
    :color_path: cow_type.color

In such situation, there is a big difference between calling const-qualified overload and non-const-qualified overload. For this reason, C++17 added a helper function:

.. cch::
    :code_path: as_const_use.cpp
    :color_path: as_const_use.color

:cch:`std::as_const` is a very simple function, it just returns a const reference to the passed object. If you don't have C++17 you can implement this function in C++11 compatible code:

.. cch::
    :code_path: as_const_impl.cpp
    :color_path: as_const_impl.color

Later you will also learn about :cch:`std::shared_ptr` which can be used to implement types with COW behavior.

.. TODO short question about pre-C++11 std::string and SSO? Currently SSO is mentioned in arrays chapter which might be too early.

Setters for classes with invariants
###################################

The style of const + non-const overloads is quite popular but it's not appropriate when a class has some invariants - returning a non-const reference makes external code totally unconstrained. For something like the :cch:`fraction$$$type` class, the following implementation can be used:

- the const-qualified overload returns const reference
- the non-const-qualified overload, instead of retuning a non-const reference, takes the value to set as a parameter

.. cch::
    :code_path: fraction_setters.cpp
    :color_path: fraction_setters.color

Data member names were changed to avoid name conflicts with function names.
