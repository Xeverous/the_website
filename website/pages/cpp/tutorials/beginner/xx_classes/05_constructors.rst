.. title: 05 - constructors
.. slug: 05_constructors
.. description: constructors
.. author: Xeverous

Remember recent problem of being unable to create objects with custom initial values? This lesson will solve it.

.. TOCOLOR

.. code::

    // fails to compile, various possible errors
    // (in short, no way to initialize the object)
    fraction fr1{2, 6};

Constructors are one of **special member functions**. They are automatically called whenever an object of their type is created.

Constructors have 2 main purposes:

- initialize all fields
- establish class invariants

.. TOCOLOR

.. code::

    #include <iostream>

    // (greatest common divisor)
    // if you have C++17, you can remove this function and use std::gcd from <numeric>
    int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        else
            return gcd(b, a % b);
    }

    int make_valid_denominator(int value)
    {
        if (value == 0)
            return 1;
        else
            return value;
    }

    class fraction
    {
    private:
        int counter = 0;
        int denominator = 1;

    public:
        // constructor
        fraction(int counter, int denominator)
        {
            set(counter, denominator);
        }

        void set(int count, int denom)
        {
            counter = count;
            denominator = make_valid_denominator(denom);
        }

        void simplify()
        {
            const int n = gcd(counter, denominator);
            counter /= n;
            denominator /= n;
        }

        double approx() const
        {
            return static_cast<double>(counter) / denominator;
        }

        void print() const
        {
            std::cout << counter << "/" << denominator;
        }
    };

    int main()
    {
        // this is how you use a constructor to create an object
        fraction fr(1, 2);
    }

.. TODO fr(1, 2) vs fr{1, 2} ?

Pay attention to the syntax:

- Constructors always use the name of the class.
- Constructors do not have a return type - not even :cch:`void`.

Besides these, constructors behave just like member functions:

- Constructors are affected by access specifiers.
- It's possible to overload constructors (including :cch:`= delete`). If no overload can be selected - compilation error.
- It's possible to place a :cch:`return` statement in their body, just like in a function returning :cch:`void`.

The only exception is that constructors can not have any member function qualifiers - they would not make any sense anyway since at the point of the call no object exists yet.

initialization > assignment
###########################

As you already know, when creating objects, initialization should always be preferred over assignment. Creating uninitialized objects only asks for trouble (and if the initial value cannot be given it means the object has too large lifetime and is not needed that early).

Constructors have a special feature for it - **member initializer list**:

.. TOCOLOR

.. code::

    // BAD: fields are assigned
    // If field definitions have no default initializers,
    // they might be left uninitialized until assigned!
    fraction(int counter, int denominator)
    {
        set(counter, denominator);
    }

    // GOOD: fields are initialized
    fraction(int counter, int denominator)
    : counter(counter)
    , denominator(make_valid_denominator(denominator))
    {}

Member intializer list is placed before the body, it starts with ``:`` and member initializers are separated by ``,``. The punctuation layout presented above helps in aligning members.

You might have also noticed a surprising thing - parameter names are identical to member names. This is a special feature of member intializer list - it lets you reuse the same names without name clashes.

The list does not have to contain all class members - if any of them already have an initializer defined in the class body, they can be skipped. If a member is present in the list, its initialization code simply overrides the default initializer.

Delegating constructors
#######################

Apart from overloading, a constructor can also delegate to another overload:

.. TOCOLOR

.. code::

    // A: 1 overload using default parameter

    fraction(int counter, int denominator = 1)
    : counter(counter)
    , denominator(make_valid_denominator(denominator))
    {}

    // B: 2 overloads

    fraction(int counter, int denominator)
    : counter(counter)
    , denominator(make_valid_denominator(denominator))
    {}

    fraction(int counter)
    : counter(counter)
    , denominator(1)
    {}

    // C: 2 overloads, 1 overload uses delegation

    fraction(int counter, int denominator)
    : counter(counter)
    , denominator(make_valid_denominator(denominator))
    {}

    fraction(int counter)
    : fraction(counter, 1)
    {}

Your preference should be in this order:

- default arguments (less overloads to write)
- delegation (more code reuse, can provide default values for non-last arguments)
- separate overloads

The goal is simple: avoid duplicated code.

Default constructor
###################

There is an implicit rule that if a class does not have any constructors defined, it automatically gets one (it's public, takes 0 arguments and has empty body). This means all classes so far actually had a constructor, it just wasn't doing anything if fields had no default initializers.

If you have defined custom constructors and still want to have the default one, you can do this:

.. TOCOLOR

.. code::

    fraction() = default;
    fraction(int counter, int denominator = 1);

Default constructor is not *a constructor that takes 0 arguments*, it's *a constructor that can be called with 0 arguments*:

.. TOCOLOR

.. code::

    // can be called with 0, 1 and 2 arguments
    fraction(int counter = 0, int denominator = 1);

With the constructor above, the class is still *default constructible*.

Vexing parse
############

Due to historical reasons, C++ contains a small trap in regards to calling 0-argument constructors:

.. TOCOLOR

.. code::

    fraction fr(0, 1); // 2-argument constructor
    fraction fr(0);    // 1-argument constructor
    fraction fr();     // function declaration!
    fraction fr;       // 0-argument constructor

If you want to default-construct an object, remember to not write ``()``.

.. TODO mentiong that {} has no problem?

Initialization order
####################

.. TOCOLOR

.. code::

    class point
    {
    private:
        int x;
        int y;
        int z;

    public:
        point(int x, int y, int z)
        : x(x), y(y), z(z) {}

        point(int value)
        // compilers can print warnings about this
        // x is initialized first, using uninitialized z
        // y is initialized second, using uninitialized z
        // z is initialized third, using parameter value
        : z(value), x(z), y(z) {}
    };

Order of fields in member initializer list has no influence on the initialization order - it's defined by the order of fields in the class definition. This leads to a simple conclusion: **to avoid confusion, member initializer list should always use the same order as the class members are defined**. Otherwise it creates an illusion that the order can be changed, incentivizing mistakes like the one just presented.

    Previously it has been mentioned that constructors are affected by access specifiers. Is there any point of other specifier than :cch:`public` for a constructor? Wouldn't other access prevent from creating an object?

It would - and that's desirable in few small patterns which offer to create an object through some indirect mechanism (e.g. derived class or static member function) - you will learn about them in further lessons.

.. TODO some exerices? class def + guess the result? answers in the spoiler?
