.. title: 04 - exception guarantees
.. slug: index
.. description: different levels of exception safety
.. author: Xeverous

Functions can be marked as :cch:`noexcept` to inform they will never throw. However, functions which potentially throw can still offer some guarantees. There is no syntax for it - it's simply documentation about function postconditions. Exception safety of standard library functions is documented on cppreference on a per-function basis.

4 levels of safety exist, each higher one being a superset of previous guarantees.

Nothrow exception guarantee
###########################

The highest level of all - the function simply never throws. Such functions are typically marked :cch:`noexcept` but there are some exceptions (pun intended):

- Destructors are implicitly :cch:`noexcept`, there is no need to mark them as such
- C++ standard library functions imported from the C standard library (C has no exceptions).

Note that it's still possible to break some C functions - some of them take function pointers as arguments. Make sure that callbacks given to C interfaces do not throw.

Strong exception guarantee
##########################

A function can throw, but if it throws the state of the program is rolled back to the state just before the function call. This approach is very common in the whole IT and of particular importance in networking and databases - each operation either succeeds or fails with rollback behavior. There is no partial success. A slightly outdated database is better than the one with inconsistent or corrupted information.

Many operations which do not inherently give strong guarantees can be made as such by performing a temporary copy. Edits on the copy can fail, but the state of the program remains unaffected. If edits succeed, the copy is swapped with the original object (swaps are :cch:`noexcept`) and the now-copy-of-old-state object is destroyed. Standard library containers take advantage of :cch:`noexcept` member functions when implementing their copy and move operations. If stored objects do not have :cch:`noexcept` copy and move operations, containers switch implementation to perform additional copies (reduced performance) in order to guard against possible failures.

Because providing strong exception guarantee is sometimes a safety/performance tradeoff, it has to be decided on a case-by-case basis.

Basic exception guarantee
#########################

A function can throw and if it throws the program remains in a valid but unspecified state (same guarantee as for *moved-from objects*). Data loss may occur but no resource leaks or memory corruption.

.. TODO IIRC there is a container which drops all data in case of some operation failure (strong guarantee not possible to implement) - find it and give example

No exception guarantee
######################

Basically undefined behavior when an exception occurs. Don't use exceptions in such places or if you have to - guard exception-unsafe code by cathing or terminating the program (termination is better than undefined behavior).

Example: once I was implementing a callback for data download performed by the `curl library <https://curl.se/>`_., specifically for `WRITEFUNCTION option from the easy interface <https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html>`_. The code looked as follows:

.. cch::
    :code_path: curl_write_callback.cpp
    :line_start: 9

The library is written in C but the callback function can be written in C++. libcurl will simply call it when needed. I have given the address of this function earlier, when setting up the transfer options. Obviously libcurl isn't prepared for the case where its C code calls a C++ function that in turn throws an exception. The exception would have to go through unprepared C code, likely resulting in undefined behavior because C code isn't compiled with support for exceptions.

To prevent this, I simply wrap the risky operation in the :cch:`try` block and immediately handle any possible exception. I can not exit this callback by exception, so I have written it to simply :cch:`return 0;` which informs libcurl I couldn't accept even 1 byte (this will cancel the download).

Recommendations
###############

Aim for the highest level of exception guarantees when writing your own code. This means that you will usually end up with basic and strong guarantee.
