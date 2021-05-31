.. title: C++ myths
.. slug: cpp_myths
.. description: myths about C++
.. author: Xeverous

A collection of common misconceptions about C++.

"C++ requires manual memory management"
#######################################

This is simply false. Proper C++ code sticks to the `RAII <https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization>`_ idiom where:

- constructor acquires the resource
- destructor releases the resource
- (optional) move constructor/assignment operator *move* the resource between objects (a *move* can never fail)
- (optional) copy constructor/assignment operator initializes a new object with the same state and a separate resource

Once a resource has been encapsulated inside a RAII class (in other words, the class implements *rule of 5*), there is no more need for any work - a containing class does not need to care about stored object special member function (*rule of 0*). Objects can be safely manipulated and the resource will never leak.

Extra notes:

- C++ compilers have special rule that allows them to optimize redundant object copies **even if their special member functions have side effects** - what is guuatanteed is that every constructed object sooner or later will be destroyed.
- Resource does not have to be memory. It can be anything that requires acquisition and cleanup.
- Even though C++11 added language support for move operations, the RAII idiom was possible to be used much earlier.

"C is faster than C++"
######################

It is not. Both languages should compile to equally fast (and often the same) machine code.

The myth appears to be true due to a wrong assumption that going lower level brings better performance because you have more power.

This often can be reverse - correctly done high-level abstractions are better for performance because compilers have more information about the code. Take for example sort algorithm APIs:

.. cch::
    :code_path: cpp_myths/sort.cpp
    :color_path: cpp_myths/sort.color

The C version takes a pointer to the data, count of elements and size (in bytes) of each element. The algorithm swaps elements depending on the result of the provided comparison function.

The C++ version takes 2 iterators (pointers are the simplest iterators) and accepts any function object that implements :cch:`operator()` which compares 2 elements provided by dereferencing iterators.

It turns out that the C++ version is much better optimized. Why?

- C version uses function pointer. It is unknown what will be put here so it's an optimization barrier. Compiler must insert function call. It can not be inlined.
- Comparisons are usually very short and C++ template takes advantage of this and inlines practically every closure coming from lambda expressions or other comparators. This avoids large overhead of calling a function for a very simple operation.
- C version loses type information. By treating everything as :cch:`void*`, it limits any type to trivially copyable block of bytes. C++ sort implementation supports any sequence which offers random access to elements.

It can be said that is example is cherry-picked bad design from C standard library but ... you just can't write a performant sort abstraction in C. It simply does not have enough features to cope with the sorted object requirements and provide enough information for the compiler to optimize the code.

A lot of C++ code can easily get equivalent C code. But the C++ code will contain RAII classes while the C code will contain manual resource management every time there is a need for it. The first one will provide much more information to the compiler about the expected behavior, while the second will contain a lot of places to make a leak and/or a crash.

Not every C++ thing is faster than the equivalent thing from C and not every thing from C should be abandoned in C++. What is often overlooked in discussions - performance is never a necessity in every part of the program and so in the places where top performance is not required projects prefer more convenient abstractions which are slower but much easier to maintain.

Badly written C tends to crash. Badly written C++ tends to run slowly. This might also cause a bias towards C because C++ performance bugs are harder to identify than C crash bugs.

":cch:`const char*` is faster than :cch:`std::string`"
######################################################

The entire comparison is flawed:

- The first one is used for compile-time strings which contents never change.
- The second one is used for dynamically allocated strings which contents are run-time dependent.

For honest comparison, one should do:

- :cch:`const char*` vs :cch:`std::string_view`
- :cch:`char*` + :cch:`malloc()` + :cch:`free()` vs :cch:`std::string`

And in both of these comparisons both approaches are pretty much even, although there are slight differences in required operations due to what information is stored - most notably, the C abstraction does not store string length.

- merging 2 :cch:`const char*` strings requires 1 call to the allocator and 2 calls to :cch:`strlen` (which has O(n) complexity)
- merging 2 :cch:`std::string_view` strings requires 1 call to the allocator and 2 calls to :cch:`std::string_view::size` (which has O(1) complexity)

As a result, C++ implementations occupy slightly more memory but their cached string length helps to reduce string length computations.

Also, C++ string class implementations use SSO (short string optimization) (a specific case of SBO - small buffer optimization) which helps string class avoid unnecessary allocations when the internal in-class buffer (made of member variables) is big enough. It certainly is possible in C too but I doubt it is very often used in C due to a lack of support for good abstraction.

More on SSO:

- https://stackoverflow.com/questions/10315041/meaning-of-acronym-sso-in-the-context-of-stdstring
- https://stackoverflow.com/questions/21694302/what-are-the-mechanics-of-short-string-optimization-in-libc

"C++ compilers transform C++ code to C and then compile it"
###########################################################

This was true like ... 30 years ago. It is no doubt that all of major compilers reuse their implementation for both C and C++ but by no means C++ is translated to C and then compiled. Newer standards of C++ provide so much useful information to the compiler that translating C++ to C would be a huge waste of various optimization opportunities. The real situation is that modern compilers transform both C and C++ code to an internal intermediate form that is then used to generate optimal machine code for the target hardware. The intermediate form is more or less a simple abstraction of reads, writes and computations.
