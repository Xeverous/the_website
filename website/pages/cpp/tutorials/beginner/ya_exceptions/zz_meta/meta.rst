.. title: zz - meta
.. slug: index
.. description: meta discussion of exceptions
.. author: Xeverous

The usability of exceptions in C++ is disputed. The downside for the power of exceptions is that they are by far the most costly mechanism of all, and by *far* I mean `really really far <https://www.boost.org/doc/libs/1_79_0/libs/outcome/doc/html/faq.html#high-end-cpu-intel-skylake-x64>`_. In the linked FAQ from Boost.Outcome (which is another approach to error handling) you can observe that exceptions are roughly **2 orders of magnitude more expensive than any other error handling method**. For this reason exceptions get mixed opinions in the C++ community - while the mechanism offers great power (much greater than out parameters or composite return types) it comes with a great performance cost, a cost which many projects simply can not accept. Apart from slower execution, exceptions also consume a lot of executable space and increase performance unpredictability.

An additional argument against the use of exceptions is having to work with exception-unsafe code. While it's a good reason to resign from exceptions in such case in stricly pragmatic view, it's not a real argument against exceptions. If the program is a tangled forest of pointers with unclear ownership (and possibily other causes that lead to convoluted resource management), working with such code in general is a pain - it's not a fault of exceptions. It's worthwhile to write exception-safe RAII code even if you don't plan on using exceptions.

Exceptions are mostly disabled for these reasons:

- They take a lot of time to process with no predictability or any guuarantees.
- They take a lot of space in binary code - additional data has to be embedded in the executable to enable their support (problematic in embedded systems).
- They are weakly supported on rarer architectures.
- They prevent some optimizations (without them, everything is :cch:`noexcept`).
- They are one C++ feature which is against its own philosophy of "you don't pay for what you don't use" - even if no exceptions are used, there is still a cost associated with enabling their support.

*In the Itanium ABI, throwing an exception requires a heap allocation. In the Microsoft ABI, re-throwing an exception will consume surprisingly large amounts of stack space (2100 bytes for a re-throw in 32-bit environments, 9700 bytes in a 64-bit environment). Program storage space, heap space, and stack space are typically scarce resources in embedded development.* - taken from `The Freestanding Proposal <http://wg21.link/p0829>`_.

Implications
############

About half of C++ projects partially or fully ban use of exceptions\ [CppDevSurvey]_. Many projects are compiled with ``-fno-exceptions`` or equivalent compiler option.

While there is nothing wrong in *not using* some language feature, disabling exceptions at the compiler level has few important consequences:

- It makes use of keywords :cch:`try`, :cch:`throw` and :cch:`catch` illegal (or something worse like undefined behavior). This limits interoperatibility with other code, which uses these keywords.
- It modifies the behavior of the standard library, which is required to throw in certain places. I have checked libstdc++ (the implementation used by GCC) and it uses macros that cover the 3 keywords. In general, if exceptions are disabled, :cch:`try` becomes :cch:`if (true)`, :cch:`catch` becomes :cch:`if (false)` (effectively causing removal of dead code) and :cch:`throw` expressions are turned into aborts or something specific (allocation failures do not abort but return null pointers instead).
- It incentivizes to write exception-unsafe code.

Removing language feature completely makes the code non-standard C++ because the standard library has somewhat changed behaviour.

    How about not using exceptions but also not disabling them through compiler options?

Impractical. The standard library still has exceptions (unless you avoid relevant parts of it too) and not disabling them at the compiler level means that a lot of potential performance gains will not be achieved.

It's a well-known problem in the C++ community (Core Guidelines state the debate is 40 years old) but it's also a kind of a problem where no single solution can satisfy everyone. The committee is aware of this - they are often the same people who work in no-exception projects. The status quo is that compilers offer multiple options to choose from (some non-standard but motivated by practicality) to let everyone have their project running however they like. This helps different projects achieve what they want but also fractures the ecosystem into multiple, incompatible dialects.

Implementation
##############

Exceptions require compiler support. Generally, they can not be implemented in regular C++ code but if some functionality is sacrificed a similar mechanism can be achieved, typically offering less for a significantly smaller performance cost. Such implementations I know are (already mentioned) `Boost.Outcome <https://boost.org/libs/outcome>`_ and `Boost.Leaf <https://boost.org/libs/leaf>`_. They might be a good tradeoff for some projects.

If you want to know what kind of mechanisms compilers use to implement exceptions, checkout `the long jump function <https://en.cppreference.com/w/cpp/utility/program/longjmp>`_.

TODO describe SJLJ, SEH, and DW2 exception implementations

.. also mention that currently used exception implementation mechanisms do not incur overhead unless an exception is actually thrown

Recommendations
###############

I still encourage you to use exceptions because:

- Exceptions are the best error handling mechanism (from feature capability point of view) for non-local errors or problematic situations like constructor being unable to establish a class invariant.
- It's better to write in ISO standard C++, especially when learning. Using exceptions forces you to write exception-safe code.
- The programs you write during learning aren't constrained by platform-specific performance requirements (unless you do play with compiling for embedded devices).
- You are learning C++ and thus should understand the feature, even if you won't use it in production code. No project uses all possible C++ features but as a programmer you should know what tools you have at your disposal and why certain ones are or are not being used in the given situation.

This of course doesn't mean that exceptions should be the only error handling mechanism - using them for function-local error handling or inside tight loops (loops that work on raw memory and can reap huge benefits from optimization) is simply unnecessary overhead for no or very little functional gain.

The future
##########

There is a possibily of a more efficient exceptions implementation but compilers and the committee would have to agree on a specific design - implementation techniques of such machine-instruction-level features tend to impose various language-level decisions to be made.

I know of 2 hot papers regarding exceptions:

- `Zero-overhead deterministic exceptions <https://wg21.link/p0709>`_ - a paper that discusses current issues in detail and proposes a completely different implementation of exceptions with different tradeoffs.
- `Zero overhead deterministic failure - A unifed mechanism for C and C++ <http://wg14.link/n2289>`_ - a paper that proposes mechanism that could be used across languages, including partial support of exception-like features in C and better interoperatibility of C code with throwing C++ code.

Additional summary: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rnr-no-exceptions

Additional resources
####################

Boost.Outcome has `a list of presentations <https://www.boost.org/doc/libs/1_80_0/libs/outcome/doc/html/videos.html>`_ that describe various intricasies of exceptions and error handling. My favouite (and likely also most valueable for you) is Deterministic Disappointment by Niall Douglas.

.. [CppDevSurvey] https://isocpp.org/files/papers/CppDevSurvey-2018-02-summary.pdf
