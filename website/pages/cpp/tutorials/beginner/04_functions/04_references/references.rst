.. title: 04 - references
.. slug: index
.. description: references and pass by reference
.. author: Xeverous

.. described topics (not in this order):
.. - references use regular syntax but offer reference semantics
.. - references must always be initialized and can not be rebound
.. - unlike pointers, references can not be null - they are always assumed to be bound to a valid object
.. - only const references can be bound to read-only values, non-const references require named mutable objects
.. - references collapse
.. not described topics:
.. - rvalue references and their usage
.. - references do not allow pointer arithmetics

Functions output results by their return value. You might have tried to do something like this:

.. cch::
    :code_path: pass_by_value.cpp
    :color_path: pass_by_value.color

Surprisingly, the program prints:

.. code::

    x before function call: 10
    x inside function: 20
    x after function call: 10

The reason for this behavior is that functions do not work directly on objects provided as arguments. They work on their copies. Each frame on the call stack is a new set of objects. Only the return value is transferred to the previous frame.

    Isn't this approach inefficient?

At the machine instruction level, everything that the processor does is based on copying data between memory cells and/or registers. These copies are one of the fastest operations.

Lifetime of local objects is related to the existence of current stack frame. If a function would like to modify an object that lives in a different frame, it needs to know where exactly that object is stored. In such case the object will not be copied into the frame but its memory address will be. **However the function works, something must be copied - either the data itself or memory address of the data.** For lightweight types (described more precisely later) it's more efficient to copy the data than to use any indirect mechanism.

References
##########

References are variables which refer to other objects. Reference types are denoted with ``&``.

.. cch::
    :code_path: references.cpp
    :color_path: references.color

Notice the difference between reference initialization (A) and later assignment (B). Both use ``=`` but their meaning is very different:

- A: reference initialization specifies to which object it should refer
- B: assignment (and any other operation after initialization) work on the specified object

.. admonition:: note
    :class: note

    References must be always intialized.

.. admonition:: note
    :class: note

    References can not be rebound. Once a reference has been initialized, it will always work on the initially specified object.

Refereces undergo *collapsing*. A reference to a reference is equivalent to a single reference:

.. cch::
    :code_path: reference_collapsing.cpp
    :color_path: reference_collapsing.color

There are actually 2 types of references:

- *lvalue references*, denoted with ``&``
- *rvalue references*, denoted with ``&&``

rvalue references have different binding (reference initialization) rules and will be covered much later. You can assume that the term *reference* (with no further context) means *lvalue reference* (rvalue references are rare - they are used for very specific operations). Apart from initialization, both types of references work the same.

References can be used to modify objects that are defined elsewhere. Creating a reference has a fixed cost (quite cheap) because references copy memory addresses of other objects, not objects themselves. The actual objects can be arbitrarily large but a *pointer* (memory address) at the machine code level is always a single integer of the architecture size (8 bytes on 64-bit).

Pass by reference
#################

Coming back to the first example, we can now modify the function to use a reference:

.. cch::
    :code_path: pass_by_reference.cpp
    :color_path: pass_by_reference.color

Now the function works on the same object:

.. code::

    x before function call: 10
    x inside function: 20
    x after function call: 20

Reference binding in detail
###########################

Creation of a reference does not create new objects. Instead, a reference is bound to an already existing object (which is done by copying its memory address, not contents). You can not bind non-const lvalue references to temporary objects (*rvalues*):

.. cch::
    :code_path: reference_binding.cpp
    :color_path: reference_binding.color

.. ansi::
    :ansi_path: reference_binding.txt

If a function takes an object by non-const reference it means it wants to modify it. If the function got a temporary object, the object would be destroyed just after the function returns which would defeat the purpose of storing a result in the parameter. For this reason, **binding temporaries to non-const lvalue references is forbidden**.

Bidning temporaries to :cch:`const` lvalue references is fine though. The lifetime of the temporary is extended to the lifetime of the reference:

.. cch::
    :code_path: const_reference_binding.cpp
    :color_path: const_reference_binding.color

Const references exist as a consequence of combining const-qualified types and references. There is a big difference in machine code between values and const references:

- passing by value copies the object
- passing by const reference copies the memory address of the object

Copying memory address (pointer) results in slightly more complex machine code but it's always cheap (memory address is a fixed-size integer). Copying values varies greatly, it can be computationally expensive for 2 reasons:

- The type itself is very large (:cch:`sizeof` greater than 1024).
- The type has complex definition and requires any sort of resource acquisition (especially dynamic memory) in order to copy its contents.

Typical C++ nomenclature will use names like "lightweight type", "heavy type" and "cheap type", "expensive type".

Changing between passing *by value* and *by const reference* has practically no difference in semantics but it can have significant difference in performance.

.. admonition:: tip
    :class: tip

    Types cheap to copy should be passed by value. Types expensive to copy should be passed by const reference.

What exactly makes a type expensive is somewhat platform-dependent but **generally, any type that dynamically allocates memory is expensive**. First expensive types you will learn are :cch:`std::string` (array of characters, optimized for storing text) and :cch:`std::vector` (array of objects of specific type, optimized for read and write operations).

.. TODO when should std::string be introduced?

On parameter passing
####################

Depending on how parameters are used we can differentiate 3 kinds:

- in parameters - data is read by the function; passed by value (:cch:`T`) or by const reference (:cch:`const T&`)
- out parameters - data is written by the function to the referenced object; the object is passed by non-const reference (:cch:`T&`) (both cheap and expensive types)
- in-out parameters - like out parameters but the value is additionally read before modification

In practice, out parameters (and in-out parameters) are rare. And they should be - **you should use function's return mechanism to return function results**. Non-const reference parameters are for specific purposes like in-out parameters (functions which read and update objects) where the object is complex enough that copying it and returning a copy of the new state would be inefficient.

.. admonition:: note
  :class: note

  By convention, if a function has an out parameter or in-out parameter it's the last parameter.

Dangling reference
##################

A *dangling* reference (or pointer) refers to an object that has been destroyed. Using such reference/pointer invokes undefined behavior.

Without using advanced features, the only case where a dangling reference can be created is returning a reference to function-local object:

.. cch::
    :code_path: dangling_reference.cpp
    :color_path: dangling_reference.color

.. TODO paste compiler warning

When the function returns, the :cch:`result$$$var_local` has already been destroyed. Returned reference (or pointer) will store memory address that is no longer valid.

    Shouldn't references then be banned completely from function return types? Why they are allowed?

There are numerous cases when a function can return a reference. Some examples of useful functions that don't return dangling references:

- An object has *static storage duration* (basically lifetime of the whole program) and the function gives an access to it by returning a reference (sometimes const reference).
- A function returns a reference to a subobject of a larger object that has been passed to the function by reference. Could be used for a function that accepts an array of objects and returns a reference to one based on some search criteria.
- A *member function* is inherently tied to an object, it can return references to subobjects of this object.

Recommendations
###############

.. admonition:: tip
    :class: tip

    A function should have at most 1 out or in-out parameter. Anything more has been proved to be extremely bug-prone apart from very specific usage patterns.

One particular usage can be introduced now - standard library has a function which swaps values between 2 objects of the same type. The function takes both parameters by non-const reference.

.. cch::
    :code_path: swap.cpp
    :color_path: swap.color

Core Guidelines have a cheatsheet for parameter passing in `F.15 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-conventional>`_, though it's more complicated than the recommendation in this lesson - it additionally covers *move operations* which are far from this lesson.

.. image:: https://isocpp.github.io/CppCoreGuidelines/param-passing-normal.png
    :alt: parameter passing
