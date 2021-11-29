.. title: 01 - member functions
.. slug: 01_member_functions
.. description: class member functions
.. author: Xeverous

Classes, just like member variables (**fields**) can also contain member functions (**methods**).

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
    public:
        int numerator;
        int denominator;

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
        fraction fr1{2, 6};
        fraction fr2{5, 10};

        fr1.print();
        fr2.print();
        fr1.simplify();
        fr2.simplify();
        fr1.print();
        fr2.print();
    }

Output:

.. code::

    2/6
    5/10
    1/3
    1/2

Notice few things:

- Member functions, just like member variables are defined inside the class.
- Member functions have innate ability to access member variables - as if all class fields were always passed as arguments.
- Because member functions are tied to a specific class, they can not be called like global functions. They need to be called **on a specific object**, and this is done using ``.`` operator.

If you would like to split the code above into files:

.. TOCOLOR

.. code::

    // header
    class fraction
    {
    public:
        int numerator;
        int denominator;

        void simplify();
        void print();
    };

    // source
    // notice that member function definitions use class_name::
    // this informs the compiler about access to members
    void fraction::simplify()
    {
        const int n = gcd(numerator, denominator);
        numerator /= n;
        denominator /= n;
    }

    void fraction::print()
    {
        std::cout << numerator << "/" << denominator << "\n";
    }

Thanks to member functions, the code is now more object-oriented but it still contains some flaws. What happens if we replace the code with this?

.. TOCOLOR

.. code::

    fraction fr1{2, 0}; // (1)
    fraction fr2{0, 0}; // (2)

.. details::
    :summary: Answer

    - For (1), the fraction will be simplified to 1/0 because ``gcd(2, 0) == 1``.
    - For (2), the code will invoke undefined behavior because ``gcd(0, 0) == 0`` and integer division by 0 is undefined.

In both cases, the intial problem is that fraction *invariant* was broken - the denominator can not be zero. No matter how well member functions treat the data, we can always use the ``.`` operator to access and modify class members, potentially breaking some conditions on which the methods operate.

.. admonition:: definition
    :class: definition

    An invariant is something that is always true. A condition that must always be satisfied.

Can we protect the code from breaking invariants? Yes. For this, we will need to restrict the access to some class members.
