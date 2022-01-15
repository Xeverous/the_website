.. title: 04 - references
.. slug: 04_references
.. description: references and pass by reference
.. author: Xeverous

.. TODO in-out parameters - seems like unnecessary confusion in this article, move it to later lessons?

Functions output results by their return value. You might have tried to do something like this:

.. cch::
    :code_path: 04_references/pass_by_value.cpp
    :color_path: 04_references/pass_by_value.color

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
    :code_path: 04_references/references.cpp
    :color_path: 04_references/references.color

Notice the difference between reference initialization (A) and later assignment (B). Both use ``=`` but their meaning is very different:

- A: reference initialization specifies to which object it should refer
- B: assignment (and any other operation after initialization) work on the specified object

.. admonition:: note
    :class: note

    References must always be intialized.

.. admonition:: note
    :class: note

    References can not be rebound. Once a reference has been initialized, it will always work on the initially specified object.

Refereces undergo collapsing. A reference to a reference is equivalent to a single reference:

.. cch::
    :code_path: 04_references/reference_collapsing.cpp
    :color_path: 04_references/reference_collapsing.color

There are actually 2 types of references:

- *lvalue references*, denoted with ``&``
- *rvalue references*, denoted with ``&&``

rvalue references have different binding (reference initialization) rules and will be covered much later. You can assume that the term *reference* (with no further context) means *lvalue reference*.

References can be used to modify objects that are defined elsewhere. Creating a reference is always very cheap because references copy memory addresses of other objects, not objects themselves. The actual objects can be arbitrarily large but a *pointer* (memory address) at the machine code level is always a single integer of the architecture size (8 bytes on 64-bit).

Pass by reference
#################

Coming back to the first example, we can now modify the function to use a reference:

.. cch::
    :code_path: 04_references/pass_by_reference.cpp
    :color_path: 04_references/pass_by_reference.color

Now the function works on the same object:

.. code::

    x before function call: 10
    x inside function: 20
    x after function call: 20

Parameters that are read by functions (input data) are called *in parameters*. In the example above the function is both reading and writing to the parameter so it can be called an *in-out parameter*.

Binding rules
#############

Creation of a reference does not create new objects. Instead, a reference is bound to an already existing object (which is done by copying its memory address, not contents). You can not bind non-const lvalue references to temporary objects (*rvalues*):

.. cch::
    :code_path: 04_references/reference_binding.cpp
    :color_path: 04_references/reference_binding.color

.. ansi::
    :ansi_path: 04_references/reference_binding.txt

If a function has an *out parameter* or an *in-out parameter*, it means it wants to save some result in it. If the function got a temporary object, the object would be destroyed just after the function returns which defeats the purpose of storing a result in such parameter. For this reason, binding temporaries to non-const lvalue references is forbidden.

Bidning temporaries to const lvalue references is fine though. The lifetime of the temporary is extended to the lifetime of the reference:

.. cch::
    :code_path: 04_references/const_reference_binding.cpp
    :color_path: 04_references/const_reference_binding.color

Const references exist as a consequence of combining const-qualified types and references. The difference in how they work compared to values plays a big role in machine code when it comes to passing data to functions:

- values copy the object
- references copy the memory address of the object

Copying memory address results in slightly more complex machine code but it's always cheap (memory address is a fixed-size integer). Copying values varies greatly, it can be expensive for 2 reasons:

- The type itself is very large (:cch:`sizeof` greater than 1024).
- The type has complex definition and requires any sort of resource acquisition (especially dynamic memory) in order to copy its contents.

Majority of function parameters are *in parameters*. The difference between passing them by value and passing them by const reference has impact only on program performance.

.. admonition:: tip
    :class: tip

    For in paramaters:

    - types cheap to copy should be passed by value
    - types expensive to copy should be passed by const lvalue reference

.. TODO when should std::string be introduced? then add description below

.. Most expensive types are to be learned later, starting with std::string and std::vector

Recommendations
###############

In practice, out parameters (and in-out parameters) are rare. And they should be - you should use function's return mechanism to return any function results. Non-const reference parameters are for specific purposes like in-out parameters (functions which read and update objects).

.. admonition:: tip
    :class: tip

    A function should have at most 1 out or in-out parameter. Anything more has been proved to be extremely bug-prone apart from very specific usage patterns.

One particular usage can be introduced now - standard library has a function which swaps values between 2 objects of the same type. The function takes both parameters by non-const reference.

.. cch::
    :code_path: 04_references/swap.cpp
    :color_path: 04_references/swap.color
