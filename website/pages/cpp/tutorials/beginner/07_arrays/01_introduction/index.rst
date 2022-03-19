.. title: 01 - introduction
.. slug: index
.. description: introduction to arrays
.. author: Xeverous

You may have noticed that sometimes the code contains variables named like ``x1``, ``x2``, ``x3``. Multiple objects of the same type are used for the same purpose. You may write functions to reuse logic on multiple objects, but even calling functions with a group of same variables gets repetitive and we know that duplicate code is a really bad thing.

.. cch::
    :code_path: repetition.cpp
    :color_path: repetition.color

Object-variable relationship
############################

Recall the difference between an object and a variable:

- An object is data in memory.
- A variable is an abstraction, a name that refers to (potentially multiple) objects.

So far there were examples of n:1 variable-object relation (multiple references to the same object), now it's time for 1:n (one variable for multiple objects).

Arrays
######

.. admonition:: definition
    :class: definition

    An array object is an object that consists of multiple contiguously allocated objects.

.. cch::
    :code_path: sample_array.cpp
    :color_path: sample_array.color

The example looks differently and few things need to be explained.

Syntax
######

Intuitively, you might expect the syntax to be a bit different:

.. cch::
    :code_path: syntax.cpp
    :color_path: syntax.color

Recall one of the first lessons - **declarator syntax is not "type followed by name"** and unfortunately due to backwards compatibility, it can not be changed.

    So is there any lesson about declarator syntax?

No, at least not now. But the problem is old enough that you may find various resources on the internet that may help you, e.g. https://cdelc.org. Here, I will post examples when needed as I don't think spending time trying to understand this part of C grammar is worth it. In practice, there are C++ alternatives and actual "syntax abonimations" are pretty rare so people usually just remember them instead of understanding.

The good news for arrays is that we will not use this syntax for long, as C++11 added an alternative, which is much better and not only in syntax. But first, let's explain some aspects of arrays.

Indexing
########

**Arrays are zero-indexed.** This means that an array of size ``n`` has objects under indexes ``0 ... n-1``. In the example above both arrays are of size 3 and their valid indexes are 0, 1, 2.

If this is the first time you encounter 0-based indexing you might be a bit confused, but **the more you dwell into programming the more appropriately it will sound**. Once you gain enough knowledge, it will be obvious that zero-based indexing is the only proper way of dealing with arrays.

The primary reason for zero-based indexing is related to how arrays work underneath - variables that refer to contiguously allocated objects (next to each other) of the same type. A good comparison (which may be surprising, depending where do you live) is floor numbering - ground floor is floor 0, first floor is 1, second is 2 and so on. If you are not used to this type of indexing, I have to inform you that this is the European convention and elevators there do have a 0 floor button.

An array starts at a specific memory address and it's first element is placed right in the beginning:

.. cch::
    :code_path: addresses.cpp
    :color_path: addresses.color

.. code::

    0x7ffdc1562d04
    0x7ffdc1562d04
    0x7ffdc1562d08
    0x7ffdc1562d0c

Standard streams print memory addresses using base 16 (extra 6 digits are denoted with a-f) but you can clearly see that the address of the first array element is the same as the address of the array. Obviously if you run the same program the output may be different but **first 2 lines should always be identical**. This lack of difference is the reason for 0 based numbering - during *pointer arithmetics* (which are far from this lesson) the index is used to calculate memory address of specific object and if it wasn't 0-based indexing, the math would simply not work.

.. admonition:: error
    :class: error

    Accessing an element with invalid index in an array is undefined behavior.

The reason for the above is simple: if you use an index that is outside valid range, a machine instruction will be generated that tries to access memory outside what has been allocated for the array. Such bug will usually either immediately crash the program or corrupt memory of something else that will later lead to a crash and/or other faulty behavior.

Array size
##########

Array size must be a constant expression, that is, an expression that can be evaluated at compile time.

    So array size must be :cch:`constexpr`?

Generally, this is a good mental shortcut because everything :cch:`constexpr` can be used as an array size, but some other things too. These other things (`related cppreference page <https://en.cppreference.com/w/cpp/language/constant_expression>`_) are mostly special rules for various C++ constructs (especially :cch:`const`) that were possible much earlier, before C++11 introduced :cch:`constexpr`.

.. cch::
    :code_path: constant_expressions.cpp
    :color_path: constant_expressions.color

My recommendation is to use :cch:`constexpr` and then you don't need to remember all these special rules - they were made before :cch:`constexpr` became the norm. In C, text-replacing macros have to be used as there is no way to make a constant expression other than writing the literal (obviously C++ code which uses macro for constants is bad code).

.. admonition:: note
    :class: note

    Array size must be a constant expression but when indexing, the index can be computed at runtime.

.. admonition:: note
    :class: note

    Array size must be greater than 0.

.. admonition:: note
    :class: note

    Some compilers allow arrays of size 0 as the last member of a :cch:`struct`, but this is a non-standard extension known as *flexible array member*. See `GCC description of the feature <https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html>`_.

VLA
###

During some experiments, you might accidentally use a common extension known as **variable length arrays**. It permits code such as this:

.. cch::
    :code_path: vla.cpp
    :color_path: vla.color

**This is not standard C++.** The feature dates back to C89, but even in C99 it was changed from "official" to "optional" and later removed in C11. C++ never officially had VLA, some compilers simply continued to support it as a non-standard extension. Modern compilers (with standard options) should reject such code or at least output a warning.

    Why it was removed from C and never was a part of C++? It seems useful.

There are multiple reasons:

- VLA does runtime computation of stack allocation, which is very unsafe. There is no easy way to detect any failures with such operation and programs which invoke undefined behavior due to stack corruption are very prone to security exploits.
- The same functionality (arrays with runtime changeable size) is available through dynamic memory allocation (you will learn about :cch:`std::vector` later in this chapter) and to some extent with preallocated fixed-size arrays.
- The performance gain of VLA (compared to alternatives) is negligible.

Initialization
##############

Arrays can be initialized in multiple ways. You don't need to remember how every initialization is named (hardly anyone does), it's much more important to know their effect.

.. cch::
    :code_path: initialization.cpp
    :color_path: initialization.color

Array size
##########

Because of how arrays work and how they occupy space in memory, there is a simple trick to compute their size:

.. cch::
    :code_path: size1.cpp
    :color_path: size1.color

Since C++17 the same can be done using a standard function:

.. cch::
    :code_path: size2.cpp
    :color_path: size2.color

And before C++17, the function could be written in C++11 compatible code as such (this function doesn't use :cch:`sizeof` operator but the fact that template will deduce array size from its type):

.. cch::
    :code_path: size3.cpp
    :color_path: size3.color

Working with arrays
###################

Since arrays are variables that refer to multiple objects you will pretty much always use loops to work with them, especially the :cch:`for` loop. Now you should be able to see how well a :cch:`for` loop is tied to arrays:

.. cch::
    :code_path: loop.cpp
    :color_path: loop.color

Notice how exactly the loop is written:

- it starts with :cch:`0`
- the condition is :cch:`<`
- it uses preincrement (postfix would work too but we don't need an extra copy of old :cch:`i`)

A common mistake is writing loop condition with :cch:`<=`. For an array of size ``n``, valid indexes are ``0 ... n-1``, thus the loop should continue only when :cch:`i` is lower than the size. Rarely you might find :cch:`!=`, which is also valid but such code is usually written when working with *iterators* which will be covered later.

Whichever of :cch:`<` and :cch:`!=` operators is used, after last iteration the loop control variable (:cch:`i`) will be equal to array size and stop the loop. Iteration with :cch:`i` equal to array size will never happen.

Loop control vs array size type
###############################

The C++ standard library uses size type (:cch:`std::size_t`) for array sizes. For historical reasons, this type is an alias of some unsigned integer (usually :cch:`unsigned long long`) which as you should remember is not a good choice - unsigned types should only be used when dealing with bit-level operations or when overflow is desired.

This causes a quite common warning:

.. cch::
    :code_path: warning.cpp
    :color_path: warning.color

.. ansi::
    :ansi_path: warning.txt

Most beginners will find this warning hard to understand. What's the problem here? Can't the compiler generate code that converts one integer to the type of another and then compare them?

It can. The problem is, the resulting behavior can be very surprising. The prime example is the expression :cch:`-1 < 1u`. Obviously -1 is smaller than 1 but surprisingly the expression evaluates to :cch:`false`. Why?

The cause are convertion rules. Promotion is preferred so if you compare e.g. :cch:`int` with :cch:`long` there will be no problem as the first one will be promoted and the comparison will happen between 2 long integers. But in the case of :cch:`-1 < 1u`, there is no promotion because both integers are of the same size: :cch:`int` (AKA :cch:`signed`) and :cch:`unsigned`. One must be converted to another and in both cases there is a risk that final value will not fit:

- convert to signed: huge values will not fit
- convert to unsigned: negative values will not fit

For historical reasons, convertion to :cch:`unsigned` takes place. Because of how integer convertions work, value :cch:`-1` will be interpreted as the largest possible value representable in unsigned type (modulo 2 arithmetic), causing an operation like 4294967296 < 1. In other words: if you compare signed with unsigned and the signed value is negative, the comparison will evaluate to :cch:`false`. This is a common source of bugs in loops.

The solution is simple: make sure both comparison operands are of the same type. Usually it's as simple as changing the type of :cch:`i`, which is on the same line as the warning. Since C++20 there is also another small help: :cch:`std::ssize` member functions with the same name. These work just like :cch:`std::size` but their return type is a signed version of `std::size_t`, called :cch:`std::ptrdiff_t` (pointer difference type). Later you will also learn about other typical forms of loops (range-based, iterator-based) which do not have this problem.

Looping backwards
#################

Some algorithms need to work on the array in reverse order. A typical loop would look then like this:

.. cch::
    :code_path: loop_backwards1.cpp
    :color_path: loop_backwards1.color

This is fine, but breaks when :cch:`i` is of unsigned type as for unsigned types condition :cch:`i >= 0$$$var_local >= num` is always true as they can not represent negative numbers (:cch:`--i` on zero will overflow to the largest possible value).

It's possible to loop backward on an unsigned control variable, but one needs to do a little trick to change the order of operations:

.. cch::
    :code_path: loop_backwards2.cpp
    :color_path: loop_backwards2.color
