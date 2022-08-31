.. title: 01 - introduction
.. slug: index
.. description: introduction to exceptions
.. author: Xeverous

Exceptions are the most sophisticated error handling mechanism that fundamentally works the same way in any programming language that offers it. The feature can be used for control flow too, but soon you will learn that **the only appropriate use of exceptions is error handling**.

What makes exceptions unique:

- The mechanism relies on a vast set of OOP features, including virtual functions and RTTI.
- It's impossible to ignore them - errors have to be dealt with. Even if one wants to ignore an exception, it has to be written explicitly in code every time.
- Exception errors propagate extremely easily through any abstraction, up to and beyond main function.
- Exceptions do not require any changes in return type or parameters of affected functions.
- Exceptions totally decouple error reporting code from error handling code.
- Exceptions are capable of transmitting data of an arbitrary type.
- Exception types can form a hierarchy which lets you deal with errors in a very polymorphic way.
- Exceptions can be thrown from constructors.

The downside for a such powerful mechanism are various (negative) performance consequences - they are discussed in the last lesson of this chapter.

How it works
############

Exceptions consist of 3 parts, each denoted with a specific keyword:

- :cch:`throw` - throws an exception object, immediately exiting current scope
- :cch:`try` - signifies a block of code from which exceptions can be caught
- :cch:`catch` - catches an exception object according to specification

Example:

.. cch::
    :code_path: example.cpp

Output:

.. code::

    program start
    beginning execution
    run starts
    foo starts
    foo1
    caught exception with message: foo2() failed
    program end

This is a quite verbose example, but it should demonstrate clearly what happens with control flow when an exception is thrown. A significant portion of the program was not executed. As soon as an exception was thrown, it immediately exited its scope untill (at a more shallow place of the function call stack) a handler (matching :cch:`catch` block) was found. Note that the handler wasn't a perfect match - the exception object type (:cch:`std::runtime_error`) is derived from :cch:`std::exception`. More details on catching in later lessons.

.. code::

    main()
        try                                  /|\
            run()                             |
                foo()                         |  stack unwinding
                    foo1()                    |
                    foo2() <-- exception here |
                bar()
                    bar1()
                    bar2()
        catch

If you are unsure about the process, play with the example above by moving the :cch:`throw` statement into different functions and observe program output. Compare results with the output of the program with the :cch:`throw` statement commented out.

Stack unwinding
###############

Exceptions allow to handle the error differently in each case. The same function can be called in multiple, different places and each time the enclosing function call stack can be different. When an exception is thrown, control flow jumps away from the current function and continues to jump up the stack untill a matching handler is found. This process is known as **stack unwinding** and the only code that is executed during it are *destructors* of any local objects that go out of scope as a result of moving up the stack. All other code is skipped.

The execution continues in the handler so:

- Objects which scope encloses the :cch:`try` and :cch:`catch` block remain alive as usual - they have larger lifetime.
- Objects which scope is enclosed by the :cch:`try` block (and inside any function calls there) are destroyed - execution continues in the :cch:`catch` block.

In other words, the :cch:`try` block acts as an information to the compiler: if an exception is thrown in this scope, destroy everything in it and jump to the :cch:`catch` block. For this reason, unlike :cch:`if` and :cch:`for`, the :cch:`try` and :cch:`catch` keywords always require ``{}`` - they always create 2 adjacent scopes. See https://stackoverflow.com/questions/3008937/why-do-try-catch-blocks-require-braces for further discussion.

.. admonition:: definition
    :class: definition

    The :cch:`try` and :cch:`catch` blocks must always be next to each other. You can not use just 1 of them.

..

    Can :cch:`throw` be thought as a multi-level :cch:`return`?

No. I think it's a bad mental shortcut because:

- It doesn't have to be multi-level. You can throw and catch in the same function (though it has very little practical value).
- Throw statements do not have any limitations imposed by the return type of the function. Both can use totally different types. TODO What in case of coroutines?
- It doesn't work like :cch:`return` - even if the function has a non-void return type, no data is actually produced. Since any code that expects something to be returned is not executed, there is no problem caused by the lack of object.

..

    I don't understand the last point. What if I do something like :cch:`x = may_throw();$$$var_local = func();` and the function throws? What will be the value of :cch:`x`?

- If :cch:`x` is defined inside the :cch:`try` block, it will be destroyed before stack unwinding reaches the handler. The execution continues in the :cch:`catch` block, so anything in the :cch:`try` block will be already dead and inaccessible.
- If :cch:`x` has larger lifetime and inside the :cch:`try` block it's only an assignment, the object will not be destroyed but also no assignment will take place. As if the statement was commented out.

..

    What if :cch:`x` is defined outside the :cch:`try` block, it is of some class type and I call a member function on it that throws? Will the object be left in the same state as before the call or will it be left as-is (potentially modified) at the moment of throw?

It will be left potentially modified. Any code executed before the :cch:`throw` statement can leave modifications. This question touches an important topic of **exception safety** - it's up to the class writer to ensure that when an exception is thrown from a member function, the object is left in a reasonable state. The C++ standard library defines multiple levels of *exception guuarantees*, which you can aim for when writing your code. They are explained in a later lesson.

    What happens when an exception is thrown and during stack unwinding, a destructor of some local object throws another exception?

Surprisingly, the behavior is not undefined: :cch:`std::terminate` is called. You simply can not have 2 exceptions running at the same time, so when an exceptional failure happens during handling of other exceptional failure, the program is simply killed. For this reason:

.. admonition:: error
    :class: error

    Never let an exception out of a destructor. Destructors must never fail and thus should never throw. You can have exceptions thrown and caught inside a destructor, but no exception should be allowed to escape a destructor.

..

    What happens when an exception gets out of main function?

:cch:`std::terminate` is called. Same thing happens if an exception gets out of a top-level function that was used to initiate a thread - exceptions can not propagate across threads. In general, you can assume that problems with exceptions themselves end up in termination or (rarely) undefined behavior.

    How about static global objects?

:cch:`std::terminate` too. This applies to both constructors and destructors of such objects - both are executed outside (before/after) main function. Same thing happens for :cch:`thread_local` objects - they are global objects too, just 1 per thread.

..

    What's the lifetime of an exception object?

Short answer: In general, to the point of last :cch:`catch` clause. But there are ways to lengthen the lifetime of the exception object: *rethrowing* and specific standard library functions.

Long answer: https://en.cppreference.com/w/cpp/language/throw#The_exception_object

Exception types
###############

Unlike other languages, C++ doesn't limit what types objects of can be thrown. Typically a language requires to use or inherit from designated standard library exception type but C++ gives no constraints - you can :cch:`throw` objects of any complete type, even if it doesn't make any sense. Just another case of C++ :s:`letting the programmer shoot themselves in the foot` giving more freedom in decision making for greater responsibility.

Why use designated classes for exception objects?

- Exception classes be written to support holding all desired error information.
- Inheriting from a common parent embraces polymorphic nature of catching exceptions and gives the ability to catch with varying specificity.
- Non-class types have limited functionality and they can be caught only by exact type match.

.. admonition:: tip
    :class: tip

    Use purpose-designed classes for exceptions. `CG E.14 <http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e14-use-purpose-designed-user-defined-types-as-exceptions-not-built-in-types>`_.

Exception classes
#################

Exception classes are nothing more than types specifically designed for the purpose of being an error information. There is nothing magical about such classes - there is only a pattern that such classes are used solely for exception objects and nothing else.

A good exception class contains all relevant information what has gone wrong and why. It also implements an interface offered by its parent class. This allows far away code to detect and handle the error even if it doesn't know exactly what can go wrong. In other words, it's possible to catch exceptions by their base types if caring about their exact type is not needed or not practical.

.. admonition:: tip
    :class: tip

    Use designated classes for exception objects. When writing such class, inherit from :cch:`std::exception` or `one of its child classes <https://en.cppreference.com/w/cpp/error/exception>`_.

The interface of 2 main standard library exception types is as follows:

.. cch::
    :code_path: std_exception.hpp
    :line_start: 3

The base exception class offers just a function to override. Since there is no control over the message at this level, typical usage is to throw at least :cch:`std::runtime_error` or create an own exception class and throw an object of this type.

A library project may create a special base exception class that inherits from :cch:`std::runtime_error` but never throw objects of exactly this type. The type is only used as a base for actual (further inherited) library error types. This allows external code to create a catch-all handler that only cares that the error comes from this specific library - for some applications this information alone is enough.

    Why exception classes have a copy constructor?

I haven't heard of any example or practical application of copying exception objects, even something for testing purposes. However, the language specification says *15.1.5 When the thrown object is a class object, the copy/move constructor and the destructor shall be accessible, even if the copy/move operation is elided (12.8).*. The reason for this is that exception implementations vary (especially in terms of memory allocation) and some of them require the ability to copy exception objects on the stack (MSVC in particular). See https://stackoverflow.com/questions/58955178/why-are-c-exceptions-potentially-copied for more information.

As a consequence of the copyability requirement and the fact that these classes are used for exception objects, their copy constructors and assignment operator are not allowed to throw exceptions - they are defined as :cch:`noexcept`, which is explained further down in this lesson. The message string copies (which could throw on memory allocation failure) are avoided typically by storing them in a separate, reference-counted buffer that is allocated only in the constructor. For this reason there are no constructor overloads that accept :cch:`std::string&&` - the message is always copied into this buffer upon construction.

    What if an exception has to be thrown but the constructor of such exception object throws when allocating the string?

Then the allocation exception (:cch:`std::bad_alloc`) is being thrown. It's not possible to throw multiple exceptions at once, the first successful throw (here: the one within exception object constructor) will immediately start propagating. Instead of constructing desired exception object and then throwing it, the constructor already throws which causes the initially planned throw to not be executed (even if it's combined with construction in the same statement). In other words, the initially planned throw will not be executed because the exception failed to construct due to another exception.

    What if an exception is thrown from a constructor that builds a member object of another (parent) object?

If an exception is thrown from the constuctor, the destructor is not called. Any (sub)objects constructed so far will be destroyed. In other words, destructors are called only when respective constructors finished successfully. As always, constructors are paired with destructors 1:1 and order of destruction is exactly reverse to order of construction. Becasue constructors that failed via exception are not considered to be successful, they must perform all necessary cleanup before the exception.

When to use exceptions
######################

Because of their cost, exceptions are intended for *exceptional* problems - problems which can not be easily dealt with or which can not be dealt with at all. There is a lot of subjectivity here, but in general the more common a potential error is and the more low-level code gets, the less motivation is to report it through exceptions.

Example places where **not to** use exceptions:

- Predictable occurences of invalid data (e.g. user entered invalid date, path etc.).
- Operations which can simply return failure and the cause is irrelevant or obvious (e.g. mathematical errors like division by 0).
- Code that heavily relies on compiler optimizations - typically tight non-allocating loops performing computations. Exceptions, like any other conditional code significantly complicate generation of machine code.

Example places where use of exceptions is acceptable:

- Unpredictable problems such as failure to allocate memory. The operator :cch:`new`, standard library string types and all standard library containers throw on allocation failures. It's worth noting though that allocation failures are very domain-specific and there can be many subjectively-good approaches in specific scenarios.
- Inability to return anything meaningful that satisfies function's postconditions.
- Inability to call a subfunction with satisfied preconditions.
- Failure to (re)establish a class invariant - especially for constructors. Constructors have no other way of reporting errors.
- Overloaded operators - majority of them have significant limitations on the number and types of arguments which makes exceptions the preferred choice.

Some functions in the standard library contain 2 versions. Containers with array access typically offer:

- :cch:`T& operator[](size_t idx) noexcept$$$param_tmpl& keyword[](type param) keyword` which is a fast implementation but invokes undefined behavior when the index is invalid.
- :cch:`T& at(size_t idx)$$$param_tmpl& func(type param)` which is a safe implementation (throws :cch:`std::out_of_range` on invalid index) but is not as efficient, especially if called inside a loop (additional checks and possible jumps within a loop prevent machine code vectorization).

Similar approach can be found in the standard filesystem library and other (non-standard) libraries.
