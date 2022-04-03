.. title: ?? - destructors
.. slug: destructors
.. description: destructors
.. author: Xeverous

Let's be honest - the thing presented in this lesson is so simple that you already intuitively know what it is for based on the page title. So let's go straight to an example:

.. TOCOLOR

.. code::

    #include <iostream>

    class bar
    {
    public:
        bar() { std::cout << "bar constructor\n"; }
        ~bar() { std::cout << "bar destructor\n"; }
    };

    class baz
    {
    public:
        baz() { std::cout << "baz constructor\n"; }
        ~baz() { std::cout << "baz destructor\n"; }
    };

    class foo
    {
    private:
        bar br;
        baz bz;

    public:
        foo() { std::cout << "foo constructor\n"; }
        ~foo() { std::cout << "foo destructor\n"; }
    };

    int main()
    {
        foo f;
    }

.. code::

    bar constructor
    baz constructor
    foo constructor
    foo destructor
    baz destructor
    bar destructor

Destructors are written like constructors, but the class name is prepended with ``~``. Note that destructors are called automatically - they are run when object dies, which usually occurs at the enclosing ``}``. Enclosing objects are constructed after their parts and destroyed after their parts. **Destruction happens always in exactly opposite order of construction.**

In detail
#########

Most rules for destructors are the same as for constructors:

- Like constructors, destructors use the name of the class.
- Like constructors, destructors do not have a return type - not even :cch:`void`.
- Like constructors, destructors can have an early :cch:`return` statement like in a function returning :cch:`void`.
- Like constructors, if you don't write any destructor a default one is implicitly added to the class (it's public, takes 0 arguments and has empty body).
- Like constructors, destructors are affected by access specifiers.
- Like constructors, destructors can be made :cch:`= default` and :cch:`= delete`.

But there are few differences:

- Unlike constructors, destructors can not be overloaded and always take 0 arguments.

The reason for this is simple - they are called automatically when objects die. There is no way to pass any arguments or specify which overload to choose. Thus, each class always has exactly 1 destructor - explicitly written or default one.

- Unlike constructors, destructors can be :cch:`virtual`.

This will be covered later, in polymorphism chapter.

.. TODO unlike ctors, dtors are noexcept?

.. admonition:: note
    :class: note

    The word "constructor" is sometimes abbreviated as "ctor" and similarly, "destructor" - "dtor".

Purpose
#######

At this point the purpose of constructors should be obvious. But what about destructors? Are they really needed? The answer is yes for any class that manages a resource. You have already used some of them: :cch:`std::string` and :cch:`std::vector`. They perform memory allocations as needed to hold contained data (which size can vary significantly) and the main purpose of the destructor is to release this memory - otherwise the program would continuously drain system's memory (RAM).

Because constructors and destructors are run for any (sub)object, if your class stores members such as :cch:`std::string`, before your class is destroyed string will have a chance to perform its own cleanup.
