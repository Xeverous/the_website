.. title: 02 - inline
.. slug: index
.. description: inline keyword meaning
.. author: Xeverous

Sometimes you may write or encounter very short but nonetheless useful functions:

.. cch::
    :code_path: deg_to_rad.cpp
    :color_path: deg_to_rad.color

Historically, :cch:`inline` was recommneded for such functions. It informed the compiler that the function is very small and should not be called, but put *inline* where the function call is. Essentially this:

.. cch::
    :code_path: inlined_call.cpp
    :color_path: inlined_call.color

In other words, the function body should be copied into where it is called. The motivation was to reduce overhead caused by function calls - for each call there is some work to do (put arguments to registers and/or push them onto the stack, save return address, perform jump from current code to function code) and if the function is very small, this overhead can be significant when compared to what is actually computed.

Such functions would be then put into header files and since the keyword meant "don't compile it, just paste its body when it's used" there were no ODR violations as the function was never compiled as a standalone entity. Basically as if the function was a macro.

Over time, it turned out that humans are pretty bad at deciding what is worth inlining and what is not. Sometimes very small amount of high-level code compiles to hundreds machine instructions and sometimes a lot of high-level code is optimized well and compiles into just few instructions. For this reasons, compilers started to:

- inline some functions which were not explicitly marked :cch:`inline`
- not inline some functions which were explicitly marked :cch:`inline`

The keyword :cch:`inline` has lost it's former meaning but gained a different one - **it allows the definition to repeat across TUs**. :cch:`inline` entities can be put into headers, be included multiple times in different TUs and will not cause "multiple reference" linker errors. :cch:`inline` doesn't break ODR, it only opens a possibility of multiple definitions - but all must be identical.

    How do linkers deal with such functions?

Linkers are much more complex when compared to C++ point of view. Each symbol (usually from compiled function) can have a lot of metadata attached and/or encoded within it's mangled name.

So ... should the keyword be used today? Well, yes and no - depends on the case.

Optimization
############

Compilers are much better at deciding what should be inlined and what not. But there is a catch - they often can not do it across TUs. The reason is that when compiling one TU, they only see definitions of what has been defined in this TU. But what if a hypothetically-worth-inlining function is defined in another TU? Since they don't see the definition, there is no way to perform inlining.

To avoid this problem, some compilers offer LTO - **link-time optimization**. Basically, the compiler generates extra metadata for each compiled TU and the decision about inlining is performed at the linking step when metadata from multiple TUs is available. LTO offers better program performance but comes with the cost of significantly larger linking times.

Inlining is one of the most powerful optimizations, especially if there is a lot of high-level code that does low amount of actual computations but a lot of abstraction logic. If you want to benefit from this optimization without having to use LTO, put definitions of functions that you think are worth inlining into header files and mark them :cch:`inline`.

Note that inlining optimizations are done per call, not per function. The same function can be inlined in one place but not in the other. Compilers can have complex `heuristic <https://en.wikipedia.org/wiki/Heuristic>`_ logic that decides whether it's worth or not - too much inlining can hurt cache a lot. See https://en.wikipedia.org/wiki/Inline_expansion for more details.

For GCC and Clang, LTO requires ``-flto`` option for both the compiler and the linker. To enable it through a CMake build recipe, use ``set_target_properties(target_name PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)``.

Header-only libraries
#####################

If the function is short or is the only entity that would constitute the source file, putting its definition in a header marked with :cch:`inline` removes the need for the source file and also reduces some boilerplate (no need to copy the line which specifies function parameters, no need to write another copyright notice and whatever else given project does on a file basis).

If we apply this approach to all entities (since C++17 :cch:`inline` can also be applied to global objects, in C++11 there are some workarounds) we will end up with header-only code. Header-only libraries may negatively impact compilation times of projects that use them (as for each TU that includes them the compiler compiles definitions again) but have the benefit that no actual library build is needed. Many libraries go for header-only code, especially the ones aimed at less experienced C++ users as for such programmers the barrier to use these libraries is significantly lowered.

.. admonition:: note
  :class: note

  :cch:`template` and :cch:`constexpr` imply :cch:`inline`.

If the library project consists of mostly templates and :cch:`constexpr` code, it's already header-heavy and going header-only will make using the library easier at a very low cost.
