.. title: 09 - virtual inheritance
.. slug: index
.. description: the diamond problem and virtual inheritance
.. author: Xeverous

.. admonition:: note
  :class: note

  This lesson is optional. It discusses most complex inheritance scenarios, all of which never or hardly ever appear in production code.

A class can have multiple parent classes. Sometimes this can lead to inheriting from the same parent type multiple times.

The diamond problem
###################

The diamond problem occurs when the same parent class appears multiple times in the hierarchy.

.. cch::
    :code_path: diamond_problem.cpp
    :color_path: diamond_problem.color

The problem is named *diamond* because the hierarchy graph looks like a diamond:

.. code::

      animal
      /    \
     /      \
  mammal   flying
     \      /
      \    /
       bat

.. admonition:: note
  :class: note

  For simplicity and consistency with majorty of other examples on the internet that describe the diamond problem, the rest of the article will use class names :cch:`A$$$type` (base of all), :cch:`B$$$type`, :cch:`C$$$type` and :cch:`D$$$type` (the most derived).

  Additionally, :cch:`class` has been replaced with :cch:`struct` (which is against the convention) to shorten code in examples.

Logically (considering graph theory behind inheritance) there is no problem for such relation but for programming, the essence lies in problems that arise when deciding how such code should work.

Problem 1: multiple overrides at the same level
===============================================

If :cch:`A$$$type` has a virtual function that is overriden in :cch:`B$$$type` and :cch:`C$$$type`, and :cch:`D$$$type` does not override it - which implementation should be used? So far "down-most overrider" won, but now there are 2 overriders at the same level in the hierarchy.

Problem 2: duplication of base type state
=========================================

If :cch:`B$$$type` contains state (data members) inherited from :cch:`A$$$type` and :cch:`C$$$type` also contains state inherited from :cch:`A$$$type`, should the :cch:`D$$$type` class contain 2 copies of :cch:`A$$$type` state?

Having 2 copies of :cch:`A$$$type` state seems a natural consequence of the fact that inheritance accumulates (sums up) the state from all classes involved. But in practice, we don't want :cch:`D$$$type`\ s to have duplicates of their base-level information (:cch:`bat$$$type` with 2 :cch:`animal$$$type` states makes no sense).

If there should be only one copy of :cch:`A$$$type` state within :cch:`D$$$type`, how and where it should be stored? So far inheritance simply extended object representation in memory by appending any additional data. But if data of :cch:`A$$$type` needs to appear only once, object representation of :cch:`D$$$type` can not be made of :cch:`B$$$type` and :cch:`C$$$type` sticked together.

----

**Problem 1** is solved in many languages by a simple requirement that if multiple overriders are present at the same level, the current class must override the function.

**Problem 2** is "solved" in many languages by simply forbidding multiple *implementation inheritance*. In such case, besides *vptr*, all data members come from 1 line of inheritance which means no problems with object representation in memory - any derived class just appends its data.

Now, in C++; C++ obviously being *C++*, would not go for a simple solution like forbidding a feature just because it can be misused or because its implementation is complex. Many C++ features already can be misused/abused in a variety of ways (it's nothing new) and the language already deals with complex memory-level stuff like padding, size and alignment. So it's not strictly about complexity - it's more about pragmatism. Would the feature even have any practical value?

The answer is: yes, it would. And interestingly, **there are actually 2 solutions**.

Multiple inheritance
####################

By default, inheritance uses a simple "accumulation mechanism" which means that each derived class is simply a sum of all of its members and members of its parent classes.

Surprisingly, there are no overriding requirements on :cch:`D$$$type`:

- If :cch:`D$$$type` overrides a function from :cch:`A$$$type`, the situation is clear as :cch:`D$$$type` is clearly the down-most overrider.
- If :cch:`D$$$type` does not override the function and leaves 2 overrides from :cch:`B$$$type` and :cch:`C$$$type` on equal hierarchy level:

  - The function **can not** be called on the object through a reference/pointer to :cch:`D$$$type` (ambiguous call).
  - The function **can** be called on the object through a reference/pointer to a different type in the hierarchy.

Weird, isn't it? The function can not be called in the context of :cch:`D$$$type` but can be when some parent type is used?

- Aren't these rules just inconsistent? Why bases but not derived?
- Isn't the restriction easily bypassed by casting a pointer/reference upwards?
- What actually happens when the function is called through some base type? There are still 2 overriders at the same level.

Seems like nonsense, right? Here is the thing: **there will be 2 subobjects of type** :cch:`A$$$type` **within** :cch:`D$$$type`. This means that the graph which looks this way:

.. code::

    A
   / \
  B   C
   \ /
    D

actually works like this:

.. code::

  A   A
  |   |
  B   C
   \ /
    D

**Multiple, different references/pointers to** :cch:`A$$$type` **are possible**. Yes, you can obtain 2 different :cch:`A$$$type` objects from an object of type  :cch:`D$$$type`.

There are 2 different "inheritance lines". This explains why it's possible to call the function through some base type reference - it will either be:

- a reference to :cch:`A$$$type` that is a subobject of :cch:`B$$$type`
- a reference to :cch:`A$$$type` that is a subobject of :cch:`C$$$type`

Because there are 2 objects of type :cch:`A$$$type` within :cch:`D$$$type`, it's formally named as *ambiguous base class*. Casts to ambiguous types (have different semantics / work differently / ???).

.. cch::
    :code_path: diamond_problem_mi.cpp
    :color_path: diamond_problem_mi.color

.. code::

  B::f
  C::f

Analogical rules follow every other member (not just functions): if there is an ambiguity which one should be used (there are 2 subobjects of type :cch:`A$$$type` within :cch:`D$$$type`), references (or pointers) must be cast upwards through a parent type which is not ambiguous.

Virtual inheritance
###################

Adding :cch:`virtual` keyword when inheriting causes the compiler to deduplicate any (ambiguous) bases that have :cch:`virtual` specified. The final object representation contains exactly 1 instance of :cch:`virtual` base.

Classes which have conflicting same-level final overriders from :cch:`virtual` bases are required to override them again. Casts to :cch:`virtual` bases classes are not ambiguous since there is only 1 object of the virtualized type.

.. cch::
    :code_path: diamond_problem_vi.cpp
    :color_path: diamond_problem_vi.color

Virtual inheritance fixes the problem of duplicate information (which usually is undesired) but it comes with its costs.

Because the base is :cch:`virtual`, it can not be a subobject of both :cch:`B$$$type` and :cch:`C$$$type`. There can be only 1 :cch:`A$$$type` within :cch:`D$$$type`. Since 2 classes must share the same subobject, they need to know where it is inside the final object (:cch:`D$$$type` or something derived from it). For this reason, **each inheritance hierarchy that inherits virtually adds another vptr to the final class**.

To illustrate, here are the layouts of the types based on the information obtained with ``clang++ -cc1 -emit-llvm -fdump-record-layouts`` (the output contained much more information but this is not the place of the tutorial to discuss padding and alignment, only order of the data):

.. code::

  A:
  - vtable pointer for A
  - non-static data members of A

  B:
  - vtable pointer for B
  - non-static data members of B
  - A:
    - vtable pointer for A
    - non-static data members of A

  C:
  - vtable pointer for C
  - non-static data members of C
  - A:
    - vtable pointer for A
    - non-static data members of A

  D:
  - B:
    - vtable pointer for B
    - non-static data members of B
  - C:
    - vtable pointer for C
    - non-static data members of C
  - non-static data members of D
  - A:
    - vtable pointer for A
    - non-static data members of A

..

    No vtable pointer for :cch:`D$$$type`?

I think vtable pointer for :cch:`B$$$type` will actually function for both :cch:`B$$$type` and :cch:`D$$$type`. After all, :cch:`D$$$type` overrides :cch:`B$$$type`\ 's functions and so far every class had its vtable pointer at the start. Multiple vptrs are present only to support casting so that pointers/references to base types can also expect vptr at the beginning of what memory they refer.

The shared state of :cch:`A$$$type` is placed at the end of any type that inherits virtually from it. The offsets can be different for different dynamic types:

- In :cch:`B$$$type`, the state of :cch:`A$$$type` immediately follows the state of :cch:`B$$$type`.
- In :cch:`D$$$type`, there is the state of :cch:`C$$$type` and :cch:`D$$$type` before the state of :cch:`A$$$type`.

Layouts are no longer subsets or supersets, each class can have its own specific order of vtable pointers and state of other classes (though some pattern can be observed). This also means that casts require additional overhead of checking the offsets (they are stored in vtables). For example, converting a pointer/reference from :cch:`B$$$type` to :cch:`A$$$type` requires different adjustment when the actual (*dynamic type*) of the object is :cch:`B$$$type` and when it is :cch:`D$$$type`. The distance between data of :cch:`A$$$type` and data of :cch:`B$$$type` is not the same for all types.

- :cch:`dynamic_cast` will fail (null pointer/exception) when the destination type is ambiguous (checked at runtime)
- :cch:`static_cast` downcast: cast is *ill-formed* if input type is ambiguous or is a virtual base of or base of virtual base of destination type (there is no way to perform the cast only with compile-time information)

Apart from complex object layout and casts with runtime overhead there is one more thing: *constructors*. How should the constructor of :cch:`A$$$type` be called when :cch:`B$$$type` and :cch:`C$$$type` specify different initialization for :cch:`A$$$type`?

.. cch::
    :code_path: vi_ctor.cpp
    :color_path: vi_ctor.color

There are 2 different initializations specified for :cch:`A$$$type` but there is only 1 :cch:`A$$$type` subobject within objects of type :cch:`D$$$type`.

The solution is that **initialization (constructor calls) of virtual bases behave similarly to virtual functions and have to be overriden**:

.. cch::
    :code_path: vi_ctor_solved.cpp
    :color_path: vi_ctor_solved.color

Note that normally this is not possible: a class, in its *member init list*, can only call constructors of its direct parent classes. In the case of :cch:`virtual` inheritance, calling constructors of indirect virtual parents is not only allowed but actually required.

.. admonition:: note
  :class: note

  C++ standard library streams are implemented using virtual inheritance. Inheritance diagram on https://en.cppreference.com/w/cpp/io.

  - :cch:`std::basic_ostream` inherits virtually from :cch:`std::basic_ios`
  - :cch:`std::basic_istream` inherits virtually from :cch:`std::basic_ios`

  Thus, :cch:`std::basic_iostream` (and its derived types) have only one subobject of type :cch:`std::basic_ios`.

.. admonition:: note
  :class: note

  Further examples are very extreme, I doubt such code has any practical value (it's supported mainly for technical correctness and consistency). Nonetheless I present them for the curious and just for fun.

Extra example - extended diamond
================================

In this hierarchy :cch:`B$$$type` inherits virtually from :cch:`A$$$type`.

.. code::

    A
   / \
  B   B
  |   |
  C   D
   \ /
    E

The most interesting thing is that :cch:`E$$$type` contains 2 :cch:`B$$$type` subobjects that share 1 :cch:`A$$$type` subobject. Casts from :cch:`A$$$type` to :cch:`B$$$type` are ambiguous and their ambiguity can not be detected at compile-time (:cch:`dynamic_cast` will fail, :cch:`static_cast` will be *ill-formed* as it does not allow converting from :cch:`virtual` bases). Pointers/references to :cch:`A$$$type` would have to be converted to refer to :cch:`C$$$type` or :cch:`D$$$type` first before being converted to :cch:`B$$$type`.

This is the layout:

.. code::

  A:
  - vtable pointer for A
  - non-static data members of A

  B:
  - vtable pointer for B
  - non-static data members of B
  - A:
    - vtable pointer for A
    - non-static data members of A

  C:
  - B:
    - vtable pointer for B
    - non-static data members of B
  - non-static data members of C
  - A:
    - vtable pointer for A
    - non-static data members of A

  D:
  - B:
    - vtable pointer for B
    - non-static data members of B
  - non-static data members of D
  - A:
    - vtable pointer for A
    - non-static data members of A

  E:
  - C:
    - B:
      - vtable pointer for B
      - non-static data members of B
    - non-static data members of C
  - D:
    - B:
      - vtable pointer for B
      - non-static data members of B
    - non-static data members of D
  - non-static data members of E
  - A:
    - vtable pointer for A
    - non-static data members of A

Extra example - mixed inheritance
=================================

- :cch:`A$$$type` is virtually inherited by :cch:`B$$$type` and :cch:`C$$$type`
- :cch:`A$$$type` is inherited by :cch:`D$$$type`
- :cch:`C$$$type` is virtually inherited by :cch:`E$$$type` and :cch:`F$$$type`

If the same base is inherited virtually and non-virtually, the final object contains 1 base of this type (from :cch:`virtual` inheritance) + 1 non-virtual base for each non-virtual inheritance. That is, only :cch:`virtual` bases are deduplicated.

.. code::

    A     A
   / \    |
  B   C   D
   \ / \ /
    E   F
     \ /
      G

.. code::

  A:
  - vtable pointer for A
  - non-static data members of A

  B:
  - vtable pointer for B
  - non-static data members of B
  - A:
    - vtable pointer for A
    - non-static data members of A

  C:
  - vtable pointer for C
  - non-static data members of C
  - A:
    - vtable pointer for A
    - non-static data members of A

  D:
  - A:
    - vtable pointer for A
    - non-static data members of A
  - non-static data members of D

  E:
  - B:
    - vtable pointer for B
    - non-static data members of B
  - non-static data members of E
  - A:
    - vtable pointer for A
    - non-static data members of A
  - C:
    - vtable pointer for C
    - non-static data members of C

  F:
  - D:
    - A:
      - vtable pointer for A
      - non-static data members of A
    - non-static data members of D
  - non-static data members of F
  - A:
    - vtable pointer for A
    - non-static data members of A
  - C:
    - vtable pointer for C
    - non-static data members of C

  G:
  - E:
    - B:
      - vtable pointer for B
      - non-static data members of B
    - non-static data members of E
  - F:
    - D:
      - A:
        - vtable pointer for A
        - non-static data members of A
      - non-static data members of D
    - non-static data members of F
  - non-static data members of G
  - A:
    - vtable pointer for A
    - non-static data members of A
  - C:
    - vtable pointer for C
    - non-static data members of C

----

Additional resources:

- https://en.wikipedia.org/wiki/Multiple_inheritance
- https://en.wikipedia.org/wiki/Virtual_inheritance
