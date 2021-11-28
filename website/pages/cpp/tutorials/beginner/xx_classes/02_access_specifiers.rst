.. title: 02 - access specifiers
.. slug: 02_access_specifiers
.. description: introduction to encapsulation
.. author: Xeverous

When browsing settings on an online account or government documents, you can sometimes find that some data is marked as **public** (everyone can see it) or as **private** (only you can see it). We limit access to certain data in order to prevent unauthorized people from accessing data they shouldn't need. An analogical mechanism exists in object-oriented programming: we limit access to class members in order to prevent unwanted code to accidentally interact (in a bad way) with class invariants.

There are 3 keywords which affect class member access:

- :cch:`public`
- :cch:`protected`
- :cch:`private`

:cch:`public` is something you already know. It places no restrictions and is the default access when a class is defined using the :cch:`struct` keyword.

The remaining 2 place certain restrictions:

- :cch:`private` - only class member functions can use affected member
- :cch:`protected` - only class and *derived class* member functions can use affected member (slightly less restrictive than :cch:`private`)

Derived classes will be explained in a later chapter. Now, we will only focus on public vs private access.

Order of sections
#################

.. TODO recommended order of members? public/protected/private? This is pretty controversial

There is no required order of sections within a class. You can also repeat access specifier keywords - this is sometimes required if definitions of certain members need at least declarations of other members.

.. TODO some simple example?

Encapsulation
#############

We have modified the class in 2 ways:

- member variables are now private
- added a public function to set the values
- added reasonable default values (simplest form of a fraction representing 0)

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

    class fraction
    {
    private:
        int numerator = 0;
        int denominator = 1;

    public:
        void set(int count, int denom)
        {
            numerator = count;

            if (denom == 0)
                denominator = 1;
            else
                denominator = denom;
        }

        void simplify()
        {
            const int n = gcd(numerator, denominator);
            numerator /= n;
            denominator /= n;
        }

        void print()
        {
            std::cout << numerator << "/" << denominator << "\n";
        }
    };

    int main()
    {
        // no longer possible
        // fraction fr1{2, 6};
        // fraction fr2{5, 10};

        fraction fr1;
        fr1.set(2, 6);
        fraction fr2;
        fr2.set(5, 10);

        // fr1.denominator = 0; // error: can not access private member

        fr1.print();
        fr2.print();
        fr1.simplify();
        fr2.simplify();
        fr1.print();
        fr2.print();
    }

The change has important consequences:

- Because direct access to member variables is no longer possible and must be done through a public function, the function can verify that passed data is correct. This shields objects from breaking invariants.
- Because the type contains non-public data members, it has stopped being an *aggregate*. This means that aggregate initialization (which uses ``{}``) is no longer possible. This is only a temporary problem - in few lessons you will see multiple ways how to initialize class objects.

At this point we can say we have created a type that has:

- an interface (public members) - a way to interact with the object from the outside
- an implementation (private members) - details how stuff is done, only to be accessed (indirectly) through the interface

...and this is the key to write code that cooperates with other projects. If you use someone else's code (e.g. from a library project) methods can be changed (e.g. library update) and code that uses them will also change its behaviour. In this regard methods save us from rewriting the program - all of your code automatically gets indirect update when a library's method implementation is changed. You have already wrote code that relies on it - the C++ standard library also gets updates on its specification and compiler vendors continuously work on improving the code inside.

.. admonition:: note
    :class: note

    Library project interfaces are commonly referred to as **API** (application programming interface). We can say that the website `cppreference <https://en.cppreference.com/>`_ documents C++ standard library API.

.. admonition:: tip
    :class: tip

    Generally, for a class that has invariants:

    - All member variables should be private.
    - Functions which are a part of the class interface should be public.
    - Functions which are a part of the implementation (often helper functions to be used inside public functions) should be protected or private.

In the case of a class representing a fraction, there was no need for private functions but once your classes get bigger, you might need to split/extract some code from public functions to simplify or deduplicate their code. Protected/private functions in such case should be used - they are a detail how interface is realized so they should not be a part of the (public) interface.

    What if there are invariants but only between certain fields? What if other fields have no invariants? Should first group of fields be private and the second group be public?

Such situation indicates that the class has been badly designed. Very likely, fields with invariants should form a class on their own, and the remaining fields should be added in another class definition through *composition* or *inheritance*.

When in doubt, a good default is to make more smaller classes. Such code is more reusable, modular and testable.

More analogy
############

Kitchen (and other household) devices are pretty good examples - they are relatively simple to use but hide complicated mechanisms inside.

.. list-table::
   :header-rows: 1

   * - device
     - invariant
     - private data
     - private functions
     - public functions
   * - microwave
     - no microwaves emitted when opened
     - current power, rotating speed
     - rotate plate, switch light, emit microwaves
     - switch on/off, set time, set power, open, close
   * - fridge
     - light is off when closed
     - compressor state
     - switch light, compressor controls
     - open, close, input item, take item
   * - dishwasher
     - no water when opened
     - available water, current program stage
     - enable water pump, rotate nozzles
     - switch on/off, set program, open, close

Many devices of the same purpose will share the same interface but may be constructed differently. Another great example of an interface is a power socket. Different devices can access the power from the same interface.

Of course you might have a device that does not match the table above - sometimes it can be quite hard to determine what should be a part of (public) interface and what should be controlled internally.

Making **and justifying** decisions is one of programming skills that come with time. Many of OOP design decisions are not always trivial. Some problems take a lot of attempts and experiments to achieve satisfying solution. Remember that **the best way to learn programming is by writing code**. The more problems you encounter and solve, the better.
