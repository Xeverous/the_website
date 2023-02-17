.. title: 06 - destructors
.. slug: index
.. description: destructors
.. author: Xeverous

Destructors are very analogic to constructors. The difference is that they are run when objects are being destroyed.

.. cch::
  :code_path: destructors.cpp

.. code::

    bar constructor
    baz constructor
    foo constructor
    foo destructor
    baz destructor
    bar destructor

Destructors are written like constructors, but the class name is prepended with ``~``. Destructors are called automatically - they are run when objects ends their lifetime.

Objects that are not managed dynamically (a topic which is far from this lesson) have their lifetime tied to the enclosing scope (formally they are called objects with *automatic storage duration*). For such objects:

- destruction happens at the enclosing ``}``
- **destruction always happens in exactly opposite order of construction**

.. admonition:: note
  :class: note

  The word "constructor" is sometimes abbreviated as "ctor" and similarly, "destructor" - "dtor".

Sometimes you might encounter the name "deconstructor" but no such name is formally recognized.

In detail
#########

Most rules for destructors are the same as for constructors:

- Like constructors, destructors use the name of the class (just with ``~``).
- Like constructors, destructors do not have a return type - not even :cch:`void`.
- Like constructors, destructors can have an early :cch:`return;` statement like in a function returning :cch:`void`.
- Like constructors, if you don't write any destructor a default one is implicitly added to the class (it's :cch:`public`, has 0 parameters and has an empty body).
- Like constructors, destructors are affected by access specifiers.
- Like constructors, destructors can be made :cch:`= default` and :cch:`= delete`.

But there are few differences:

- Unlike constructors, destructors can not be overloaded and always take 0 arguments.

The reason for this is simple - they are called automatically when objects die. There is no way to pass any arguments or specify which overload to choose. Thus, each class always has exactly 1 destructor - explicitly written or default one.

- Unlike constructors, destructors can be :cch:`virtual`.

This will be covered later, in polymorphism chapter.

- Unlike constructors, destructors are :cch:`noexcept` by default.

This will be covered later, in exceptions chapter.

Purpose
#######

The core purpose of destructors is performing necessary cleanup when objects die. A lot of classes acquire resources in their constructors (e.g. opening a file, opening a network socket, allocating memory) that need to be freed when they are no longer in use. Otherwise the resources would be never given back to the underlying system which would create a situation known as a *leak* - reduction in available resouces even though they aren't actively used.

Destructors are one of key C++ design elements that differentiate it from most of other programming languages. Most languages rely on *garbage collection* mechanism - a side "process" that is running simultaneously with the application. Roughly speaking, it scans the memory of the application and frees resources (most predominantly memory) which are no longer in use (not referened in any object) or are unreachable (referenced in some object(s) but these objects are no longer referenced).

Garbage collection simplifies resource management but comes with its costs:

- The code is significantly simpler but underlying implementation has to be much more complex. The program has to run together with the garbage collector.
- Garbage collection has negative performance impact. The impact has been reduced during decades of GC algorithms evolution but it will never be zero.
- Garbage collection may not immediately free all unused resources. Some GC implementations do periodic scanning for performance resons, trading latency for throughput.
- Garbage collection is hard to predict which may negatively impact performance profiling and bug reproduction.
- Some resources are too complex to be garbage collected (e.g. file handles). This results in situation where resources have to be manually freed but there is no or limited support in the given programming language for resource management.

One of key C++ design principles is "you don't pay for what you don't use". Thus the language doesn't provide more-or-less satisfactory garbage collector (the standard formally allows GC implementations though) but instead offers a set of features that help in abstracting resource management.

Because dynamic memory allocation is far from the current lesson, you won't write any "real" destructors for now. Only the sample ones like in this lesson to print and notice when they are actually run. But destructors will be of huge importance one you start writing resource-managing classes and delve into RAII - a backbone idiom of resource management in C++.

Note that many examples have already relied on destructors. :cch:`std::string` is a class that dynamically allocates memory for its character buffer. It doesn't know how large the string will be so it allocates and frees up memory as needed. Same for :cch:`std::vector`. If you create a class that has :cch:`std::string` member(s), even without explicitly writing a destructor, the string destructor will be called whenever an enclosing object is being destroyed (unlike constructors, there is no delegation or member "deinit" list - all destructors of members on each composition level are always run).
