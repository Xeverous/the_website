.. title: 03 - error reporting
.. slug: index
.. description: how to deliver error information elsewhere
.. author: Xeverous

Introduction
############

One of the most common kinds of errors are ones which are easily fixable but require taking a different control flow path from some function up the stack.

Example:

- The user attempts to save an image.

  - A "save as" dialog box appears and the user chooses a path.

    - User selects destination and the program attempts to save a file.

      - User or standard library code eventually calls system function for I/O.
      - The function returns an error code ENOSPC (no space left on device).

    - Failed save operation is reported to the UI part of the program.

  - UI displays the information that the file could not be saved.

- The user chooses a different path (different physical device).

  - Operation succeeds.

The indent on this list matches function call stack. As you can see, the error happened deep in the stack and the solution requried to traverse the stack upwards (basically return from previously called functions) because an appropriate action could only be taken from high-level perspective.

This is a very typical scenario:

- Error information is gathered in currently executed function and returned to the caller.
- Error information is passed upwards if the parent function can not handle it too.
- Eventually the error reaches a point where it can be handled.

This results in 3 layers:

- a function that notices the error and builds error information (representations vary)
- zero or more functions that only pass received error informaion upwards
- a function that performs a specific action based on received error information

..

    What if the error can not be dealth with?

Then just report this inability to the source which triggered the operation (e.g. user: show an error dialog; networking: send a reply message with content according to the used protocol).

It's important to understand the separation of reporting, passing and handling errors. A file-saving function is not capable of doing human interface like GUI (nor it should be) so it has to return error information to the calling function. A function should do just 1 task and if it can not be done, just report the inability. The reason for this is that functions deep down the stack do not have enough context and access to necessary information to perform an appropriate decision.

How it's done
#############

There are many ways in which error information can be delivered. Most typical ones:

- through functions:

  - return mechanism (just returning if operation succeeded)
  - out parameter (if the return type is already occupied by the result)
  - special return type capable of both representing the result and error information

- other:

  - externally accessible state such as :cch:`errno`
  - *exceptions*

Exceptions are a quite sophisticated feature offered by many programming languages (including C++) that come with very unique tradeoffs. They will be briefly showcased later in this chapter. A full explanation of exceptions is much later because of how much other topics need to be taught first (mostly classes, inherirance and polymorphism).

Comparison of approaches
########################

As with many things in engineering (including software engineering) no solution is best for every situation - there are just different tradeoffs. For the purpose of comparison, I will showcase a very trivial safe division function and how differently errors can be reported.

There are 2 cases where a division can not be performed:

- Integer division by 0 has undefined behavior (for floatint-point types it produces +/- infinity).
- Division of smallest possible integer by -1 falls just out of range of positive values - recall that two's complement representation has 1 more possible magnitude on negative numbers. For example, on an 8-bit integer (which has range [-128, 127]) operation -128 / -1 has result 128, which is not representable. Overflow on signed types is also undefined behavior.

errno
#####

This approach to error reporting is very often seen in the C standard library and some system interfaces.

- :cch:`errno` `is a macro <https://en.cppreference.com/w/cpp/error/errno>`_ that expands to a :cch:`thread_local` non-const global object of type :cch:`int`. :cch:`thread_local` objects exist per thread of execution so in a multithreaded program each thread will have its own :cch:`errno` variable.
- The value 0 indicates no error. Non-zero values represent specific errors, which for portability (at early C times) were defined as macro constants. The `list of error constants <https://en.cppreference.com/w/cpp/error/errno_macros>`_ has majority of them defined as a part of C++11 standard, previously they were only a part of system interfaces, mainly `POSIX <https://en.wikipedia.org/wiki/POSIX>_` standards (that is, you needed to include system-specific headers to use them).
- No library function ever writes :cch:`0` to :cch:`errno` on success, only non-zero values are written on failures.

.. cch::
    :code_path: errno.cpp
    :color_path: errno.color

Example usage:

.. cch::
    :code_path: errno_usage.cpp
    :color_path: errno_usage.color

:cch:`errno` is a very old mechanism and although very simple it has multiple disadvantages:

- one must be aware that a function reports errors this way (it's not easily visible in the interface (function declaration) and one needs to read an informatory comment if such exists)
- it's quite easy to forget to check :cch:`errno` after function call - in many cases the return value always seems valid so an error might be unnoticed
- it's quite easy to forget to set :cch:`errno` to zero before function call - otherwise one can read non-zero value left after some operation in the past
- the error information is poor (a single integer indicating one of predefined list of possible problems)
- passing state through global thread-local object has negative performance consequences

..

    Why is :cch:`errno` a macro?

I don't know precisely but as with all such things: history, backwards compatibilty and portability. Many such things were outside standards (or - there were no standards at all) in the past and due to possible differences in implementation, macros were most portable way of allowing compilers to implement things as they prefer. Today the macro typically expands to a function call that returns a non-const reference.

Performance
===========

Some functions which implement this error reporting mechanism return error number directly instead of writing to :cch:`errno`. This approach avoids mentioned performance problem but limits return type of the function to :cch:`int`. In rare cases, if only positive or only negative results are valid it's possible to fit both error number and the result into a single :cch:`int` - the calling code has to check the sign to interpret returned value properly.

Many mathematical functions from the standard library (e.g. :cch:`std::pow`, :cch:`std::log`) report errors by setting :cch:`errno`. Some projects (especially ones which heavily rely on such functions) which do not need strict compliance but need performance are compiled with ``-fno-math-errno`` (or ``-ffast-math`` which is a superset), effectively changing approach from :cch:`errno` to "garbage in, garbage out".

For more information see:

- https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
- `SO: What does GCC's -ffast-math actually do? <https://stackoverflow.com/questions/7420665>`_
- `SO: Why doesn't GCC optimize a*a*a*a*a*a to (a*a*a) * (a*a*a)? <https://stackoverflow.com/questions/6430448>`_

POSIX vs ISO
============

To clear out some confusion, as it often happens in this area, multiple things are in play here:

- ISO C standard
- ISO C++ standard
- POSIX standards
- practice and implementation, where a lot of Unix-like systems are not strictly POSIX-compliant

The C++ standard doesn't define the language entirely, for parts imported from C it refers to the C standard (newer C++ standards refer to newer C standards).

POSIX specifies portable operating system interface. This touches many aspects of an operating system, some are about system-provided C libraries and their interfaces. Some functions specified in POSIX are the same as in the C standard, so the implementation of the C standard library can be as simple as directly calling system functions. Because functions specified by POSIX heavily overlap with ISO C, they are often in one library that is shipped with the system.

A lot of work in this area has been done by the GNU project. Sometimes GNU makes decisions that are ISO and POSIX incompatible for practical reasons - this is mostly seen with system-level functions where GNU often implements slightly different interfaces. For more information, see `SO: What does _GNU_SOURCE imply? <https://stackoverflow.com/questions/5582211>`_.

What you should remember is that not everything you find in your system's C library is a part of C or C++. Some stuff is provided by the system and it's possible that some of the standard library headers expose system-specific or POSIX-specific headers for implementation reasons. So if you want to write "portable C or C++ program that does not require POSIX" check from where a given type of function comes from before using it. I'm writing this because I have seen and received (to review) many programs claimed to be multiplatform C or C++ that were actually relying on POSIX headers. POSIX is quite portable, but unlike ISO it is not on every operating system. Most GNU/Linux distributions are only partially POSIX-compliant.

Extra stuff
===========

:cch:`errno` to text functions:

- https://en.cppreference.com/w/cpp/string/byte/strerror
- https://en.cppreference.com/w/cpp/io/c/perror

While :cch:`errno` is thread-local, functions which return textual representation aren't thread safe. `An article elsewhere <http://www.club.cc.cmu.edu/~cmccabe/blog_strerror.html>`_ describes the problem in detail.

Care should be taken when mixing errno-based error reporting with :cch:`bool` return types:

- in case of :cch:`errno`, 0 means success
- in case of `bool`, :cch:`true` means success

Many function calls are put into :cch:`if` statements. :cch:`errno` (which has type :cch:`int`) with value :cch:`0` is converted to :cch:`false`. But the success for other kind of functions is represented by :cch:`true`. This creates a program with very surprising and confusing code: sometimes :cch:`if (!func())$$$keyword (!func())` is correct to check against errors and sometimes :cch:`if (func())$$$keyword (func())`.

summary
=======

Errno is a global variable (1 per thread) that holds an integer representing error number. The list of predefined error numbers is specified (with varying precision) by both ISO and POSIX standards.

Generally, you should avoid using this mechanism. It delivers poor information, it is inefficient and ironically, it is quite error-prone.

If you face a standard library or 3rd party function which reports errors this way you have 2 options:

- stick to it for consistency (though I discourage "consistently bad approaches")
- translate it to a different mechanism (:cch:`std::error_code` is meant as a direct replacement)

Out parameters
##############

This approach is called *out* parameter because unlike usually, a function parameter is used to deliver data outside the function, not to inside.

.. cch::
    :code_path: out_parameter.cpp
    :color_path: out_parameter.color

Usage:

.. cch::
    :code_path: out_parameter_usage.cpp
    :color_path: out_parameter_usage.color

Advantages:

- The function can deliver precise error message, e.g. by using an enum or any other custom type for holding error information.
- Non-const parameter forces function users to create a value that will be passed as an out parameter (non-const lvalue reference does not accept temporaries - it must be a writeable object with some lifetime).

Disadvantages:

- Function parameters aren't well-suited for outputting information. This mechanism creates code that may be considered unclear and/or ugly. More than 1 out parameter leads to very complex and error-prone code.
- There is still a risk of accidentally using returned value when operation failed.
- Just like with :cch:`errno`, this mechanism is very problematic where a special value (in case of error) can not be returned. Objects of some types (classes specifically) may be very hard to create without valid data.

Many C libraries use a convention where places are swapped: out parameter is used to deliver the result and function return type (typically :cch:`int`) to deliver error code (often :cch:`errno`). The reason for this is that unlike C++, C does not have *return value optimization* which makes any return value larger (in bytes) than architecture size (typically 32 or 64 bit) inefficient. If such C function does not need to report errors but needs to output a large object, it will still return :cch:`void` and use out parameter. In C++ there are optimizations for returning values (RVO, NRVO) so obviously you should prefer returning values normally.

Monadic interfaces
##################

C++17 added 2 `monadic <https://en.wikipedia.org/wiki/Monad_(functional_programming)>`_ types to the standard library:

- :cch:`std::optional`
- :cch:`std::variant`

If you don't have C++17, both of these are available in boost.

Optional type
=============

Optional is essentially a struct with an object of specified type and a :cch:`bool` indicating whether it actually exists. The actual implementation is much more complex (to avoid problems caused by types which always require initialization) but can be thought as such. It either contains or does not contain an object.

.. cch::
    :code_path: optional.cpp
    :color_path: optional.color

Non-empty optional can be initialized and assigned with objects of the matching type or types that are implicitly convertible to the destination type. Empty optional can be created with ``{}`` and :cch:`std::nullopt`.

.. cch::
    :code_path: optional_usage.cpp
    :color_path: optional_usage.color

More examples and information on `cppreference page about <https://en.cppreference.com/w/cpp/utility/optional>`_ :cch:`std::optional`. You shouldn't have significant problems using it in your own code. Most of the operations are very intuitive and can be easily remembered by their name. If you do have problems, write down your questions and revisit them later once you reach classes and further chapters.

Compared to output parameters, there are multiple advantages:

- The code is much cleaner.
- It's impossible to read anything when empty.
- The function implementation does not have to return a special value in case of error, it simply creates an empty optional. No trouble with objects of types that have no special state.

The core disadvantage of the optional type is that it doesn't support holding any error information, only whether the value is present or not. For this reason it's discouraged to use optional in places where a rich state is needed in case of an error. In case of the example above it's fine because an empty result indicates that value could not be computed and very likely we will not care about the exact cause - we just know that many mathematical operations can not produce meaningful results.

Functional programming
======================

As the name suggests, functional programming is all about functions. A common pattern is to encapsulate state and use higher-order functions (functions which accept other functions as arguments). With the help of monads, it's possible to write very consise code:

.. cch::
    :code_path: fp_example1.cpp
    :color_path: fp_example1.color

As of writing this, :cch:`boost::optional` has significantly richer interface than :cch:`std::optional`, so if you would like to play with functional style of programming, I recommend to read `boost's documentation <http://boost.org/libs/optional>`_ (it's quite thorough) and use their implementation (this boost library is header-only).

Here is a more advanced example:

.. cch::
    :code_path: fp_example2.cpp
    :color_path: fp_example2.color

This code hides a lot of if-else instructions inside. Various monadic functions apply different transformations:

- :cch:`map$$$func`:

  - changes :cch:`optional<T>$$$type<tparam>` into :cch:`optional<U>$$$type<tparam>`, requires a function of the form :cch:`U f(T)$$$tparam func(tparam)` or :cch:`optional<U> f(T)$$$type<tparam> func(tparam)`
  - if there is a value, applies supplied function and returns its result as :cch:`optional<U>$$$type<tparam>`
  - if there is no value, returns an empty optional of the destination type :cch:`optional<U>$$$type<tparam>`

- :cch:`flatmap$$$func`:

  - like map, but the function has to have the form :cch:`U f(optional<T>)$$$tparam func(type<tparam>)` or `optional<U> f(optional<T>)$$$type<tparam> func(type<tparam>)`

- :cch:`value_or$$$func`:

  - if there is a value, returns stored value
  - if there is no value, returns supplied argument

- :cch:`value_or_eval$$$func`:

  - if there is a value, returns stored value
  - if there is no value, returns value returned by supplied function (the function is only called if there is no value)

:cch:`boost::optional` allows to hold a reference type, :cch:`std::optional` does not. In this case I agree with the standard library approach: if you want an optional reference, just use a pointer. Additionally, optional references create some confusion when it comes to the assignment operator (boost documentation has examples on this problem).

An optimized version of an optional monad is available on https://github.com/akrzemi1/markable. This one does not hold a :cch:`bool` but instead reserves one value to have the special meaning, specified as a template parameter. This value can not be used normally - assigning it will make the object appear as empty.

Variant type
============

A variant type holds a value of one of specified types - e.g. :cch:`std::variant<int, float>$$$namespace::type<keyword, keyword>` holds either an :cch:`int` or a :cch:`float`. There can be more than 2 types. :cch:`std::variant` allows even duplicates in types, though then using it becomes cumbersome as the primary value extraction mechanism (:cch:`std::get<T>`) becomes ambiguous and one must use index-based extraction instead (:cch:`std::get<I>`).

We could say that an optional is a specific case of a 2-type variant where the second type is :cch:`void`.

.. cch::
    :code_path: variant.cpp
    :color_path: variant.color

If you understand optional, you should have no problems understanding variant. There is no support for pattern matching or other syntax sugar for variants in C++ (at least at the time of writing this), so code that uses variants can become verbose:

.. cch::
    :code_path: variant_usage.cpp
    :color_path: variant_usage.color

Boost implementation here also has a richer interface but it requires much more knowledge to take full advantage of it so I don't present expert-level examples.

    Why can not I use :cch:`std::variant` as an array?

Because it is not an array. :cch:`std::variant` has internal storage only for one element (size and alignment enough to hold one object of specified types). Adding array interface to :cch:`std::variant` is not even possible because for different indexes it would need to return objects of different types. Both :cch:`std::get<T>` (which takes a type as a template parameter) and :cch:`std::get<I>` (which takes an index as template parameter) are function templates and their return types change depending on provided template parameters.

Other
#####

There are many more approaches to error reporting - some as simple as creating a dedicated type for the result of the function. I have only listed the easiest and most popular ones. What you need to learn is how to use specific approaches correctly and develop the ability to notice advantages and disadvantages of each approach.

Later, you will learn about one very special feature made specifically for error reporting and handling: *exceptions* (:cch:`try`, :cch:`throw` and :cch:`catch`).

There is also an article (outside the tutorial) about `standard library for system errors <link://filename/pages/cpp/stdlib/system_error/system_error.rst>`_ which describes how to encapsulate :cch:`errno` and create own numbered error categories. The mechanism relies on classes though, which are yet to be explained.

.. TODO write exceptions chapter and revisit here to decide whether or not to make a short introduction to exceptions
