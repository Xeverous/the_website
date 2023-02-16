.. title: 05 - function-try-blocks
.. slug: index
.. description: whole-function-body exception handlers
.. author: Xeverous

.. admonition:: note
  :class: note

  This lesson is optional.

A hardly-ever used feature (as of writing this, I have never seen it in production code) are *function-try-blocks*. The feature lets embed entire function body in exception-handling code:

.. cch::
  :code_path: function_try_block.cpp

The feature is mostly just syntax sugar, however it is worth to mention that:

- Function parameters live in both :cch:`try` and :cch:`catch` blocks. Parameters are constructed and destroyed before and after function call.
- Exceptions thrown by constructors (and destructors) of function parameters are not being caught. They are thrown at the call site, before (or after) the function is called.
- For the main function and thread top-level functions, function-try-blocks do not catch exceptions thrown by constructors (and destructors) of :cch:`static` and :cch:`thread_local` global objects.

In each :cch:`catch` block you should do one of two things:

- place a return statement (if the function returns non-void)
- rethrow (:cch:`throw;`) or throw a different exception

Otherwise control reaches end of the function and since there is no return value neither an exception, :cch:`return;` is assumed which is undefined behaviour for functions returning non-void.

Special member functions
########################

A special use-case of this feature are constructors and destructors. The block begings before member initializer list which means derived classes can catch exceptions caused by base class constructors and member object constructors.

.. cch::
  :code_path: ctor_try_block.cpp

Constructor failures cause the object to be thought as not constructed, therefore respective destructors are not being run.

Like in previous case, arguments have scope that cover both :cch:`try` and :cch:`catch` blocks, however non-static members (including members of parent classes) are destroyed upon entering any :cch:`catch` block and thus are no longer safe to access (compiler might allow such code but it's undefined behaviour).

For constructors, return statements are not allowed in :cch:`catch` blocks. Every :cch:`catch` must terminate by throwing an exception. If no exception is thrown, rethrow (:cch:`throw;`) is implicitly assumed.

For destructors, rethrow is also implicitly assumed but :cch:`return;` statements are allowed.

    How about delegating constructors?

From cppreference: *If the function-try-block is on a delegating constructor, which called a non-delegating constructor that completed successfully, but then the body of the delegating constructor throws, the destructor of this object will be completed before any catch clauses of the function-try-block are entered.*

Applications
############

The main purposes of function-try-blocks are:

- (for constructors) responding to an exception thrown from the member initializer list by logging and rethrowing
- modifying the exception object and rethrowing
- throwing a different exception instead
- terminating the program

Recommendation
##############

This feature is hardly-ever used. The most typical usage would be to catch member/base class initialization failures in the deried class and (one of):

- modifying the exception object (e.g. adding more context information) and rethrowing
- throwing a different exception instead

In the most unpleasant scenario, the feature could be used to safely deal with throwing destructors of parent/member objects.
