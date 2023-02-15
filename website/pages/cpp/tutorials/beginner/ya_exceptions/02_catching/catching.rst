.. title: 02 - catching
.. slug: index
.. description: multiple catch blocks
.. author: Xeverous

Multiple catch blocks
#####################

:cch:`try` and :cch:`catch` blocks always have to be together, but the :cch:`catch` block can appear multiple times.

.. admonition:: definition
    :class: definition

    Choosing the handler **does not** work like function overloading. Instead, handlers are tested in order of their appearance. The first matching handler is choosen, even if it requires implicit convertions. Code from other handlers is not executed.

If no match is found, exception continues to propagate and unwind the stack untill another try-catch block is found upwards the call stack.

If a match is found, control flow enters the scope of a specific handler. Because exception objects are polymorphic and they are rarely modified, they are typically caught by const reference - this prevents *object slicing* and ensures const-correctness.

.. cch::
    :code_path: catch_order.cpp

Suppose :cch:`func()` throws :cch:`b_exception$$$type`, then:

- first catch block is ignored because :cch:`b_exception$$$type` is not (a child of) :cch:`d_exception$$$type`
- second catch block is ignored because :cch:`b_exception$$$type` is not (a child of) :cch:`c_exception$$$type`
- third catch block is matched (types are identical); it is executed
- program continues past last catch block

Effectively, the program prints:

.. code::

    program start
    before func()
    caught b exception
    program end

If the order of handlers was different, exceptions objects could be caught with unnecessary loss of type information.

:cch:`catch (...)`
##################

:cch:`catch (...)` will catch every exception regardless of it's type (it might not be even a class, just whatever that was thrown)*.

The good is that it catches everything. The bad is that you don't know the type of caught exception and have no way to use it.

Obviously catch-all block should be always the last. No handler after this one could ever be matched.

**\*:** Microsoft compiler offers a language extension where some UB (such as null pointer dereference) is turned into exceptions. Such exceptions are beyond official C++ and require implementation-specific :cch:`__try` and :cch:`__except` keywords.

Catching multiple exceptions
############################

Some languages offer a feature to catch exceptions of multiple, different *dynamic types* in one handler block. C++ does not - you just can't have multi-argument :cch:`catch` clause.

There are 2 solutions for it:

- catching each separately and invoking same code as the handler

.. cch::
    :code_path: catch_many_lambda.cpp
    :line_start: 7

- catching a generic type and performing dynamic casts to check dynamic type

.. cch::
    :code_path: catch_many_cast.cpp
    :line_start: 7

Comparing by machine code, they will be very similar. Both :cch:`dynamic_cast` and built-in :cch:`catch` mechanism relies on RTTI so both implementations perform roughly the same operations. For the latter version, if the exception is not matched it can simply be thrown again. Because of this and additional conditional instructions I presume most programmers would think of the first approach as cleaner.

Rethrowing
##########

Caught exceptions can be thrown again, simply by writing :cch:`throw;`. The statement doesn't have to be directly within a :cch:`catch` block, it can be executed indirectly, e.g. from a function which is called inside the handler. No new objects are created, the current exception simply continues to propagate up the stack; any handlers immediately after the one which rethrows are not checked. One can also write regular :cch:`throw` statement (with an argument) to throw a new exception object.

If :cch:`throw;` is executed while there is no exception object, :cch:`std::terminate` is called.

Rethrowing and throwing again (an exception of a different type) is useful in some minor cases such as:

- Capturing a narrow set of errors and rethrowing them as something different (better understood by higher-level code).
- Logging intermediate state (that would be potentially lost if caught as a base class).
- Performing partial cleanup (e.g. closing the connection), then continuing to propagate failure about network operation.

.. admonition:: warning
    :class: warning

    A common mistake when rethrowing: slicing the object.

    .. cch::
        :code_path: rethrow_slice.cpp
        :color_path: rethrow_slice.color

Remember that the caught object might be of a more derived type than actually visible. :cch:`throw;` simply continues propagation of the current exception, whatever is is. It may also result in better diagnostics from some tools: correct rethrowing ensures continuity of the stack unwinding process, throwing another object may reset/discard exception call stack information.

Additional utilities
####################

The standard library header :cch:`<exception>` offers some additional (magic) utility functions.

.. cch::
    :code_path: exception_utils.hpp

They are useful primarily in concurrent programs for:

- capturing a running exception, passing :cch:`std::exception_ptr` to a different thread and repropagating it there
- creating :cch:`std::future` objects holding exceptions to signal a failure in satisfying :cch:`std::promise` (a mechanism of asynchronous communication)

Summary
#######

- write handlers in order of decreasing specificity
- catch by const reference
- when rethrowing the same exception object, write just :cch:`throw;`
