.. title: 07 - stream operators
.. slug: 07_stream
.. description: stream insertion and extraction
.. author: Xeverous

:cch:`operator<<` and :cch:`operator>>` are officially named *bitwise shift operators* but you might also encounter the name *stream insertion/extraction operators*. At this point you should be very accustomed to using :cch:`std::cout` and :cch:`std::cin` with these operators.

In other words, these operators have 2 common usage patterns:

- bit shift operations (multiplication/division by powers of 2)
- reading or writing data to a stream

In this lesson you will learn how to write operator overloads that work with standard library streams.

Operator chaining
#################

Streams allow *operator chaining* - you can use ``<<`` and ``>>`` multiple times in one statement. This feature is powered by the return type having the same overloaded operator. To illustrate:

.. TOCOLOR

.. code::

    int x = 1 + 2 + 3 + 4;
    int y = ((1 + 2) + 3) + 4; // equivalent
    int y = operator+(operator+(operator+(1, 2), 3), 4); // pseudo-code

    std::cout << 1 << 2 << 3 << 4;
    (((std::cout << 1) << 2) << 3) << 4; // equivalent
    operator<<(operator<<(operator<<(operator<<(std::cout, 1), 2), 3), 4); // equivalent

Simply put, the trick is to return a reference to the stream.

Canonical implementation
########################

.. admonition:: note
    :class: note

    - :cch:`std::cout` is a global object of type :cch:`std::ostream`
    - :cch:`std::cin` is a global object of type :cch:`std::istream`

    Standard library file streams (:cch:`std::ofstream`, :cch:`std::ifstream` and :cch:`std::fstream`) have types *derived* from types mentioned above, so operator overloads also work with them.

.. TOCOLOR

.. code::

    std::ostream& operator<<(std::ostream& os, fraction fr)
    {
        return os << fr.numerator() << "/" << fr.denominator();
    }

    std::istream& operator>>(std::istream& is, fraction& fr)
    {
        // read data from stream...

        if (/* reading failed */)
            is.setstate(std::ios::failbit);

        return is;
    }

Standard argument passing recommendations apply:

- In both operators stream is taken by non-const reference because any work on the stream changes it's state.
- Stream insertion only reads the data so should it should take the object (here: fraction) by value or const reference (here: value because fraction class is cheap to copy).
- Stream extraction stores the result in the object so the object must be passed by non-const reference.

    How about :cch:`operator<<=` and :cch:`operator>>=`?

These operators only make sense when :cch:`operator<<` and :cch:`operator>>` are implemented to perform mathematical operations. If you implementat stream insertion/extraction, these operators should be left unimplemented.

Exercise
########

What's wrong with the implementation below?

.. TOCOLOR

.. code::

    std::ostream& operator<<(std::ostream& os, fraction fr)
    {
        return std::cout << fr.numerator() << "/" << fr.denominator();
    }

.. TODO spoiler element

The function does not use the stream provided as an argument. Instead, it always inserts data to :cch:`std::cout`. This is a bug because someone might want to output a fraction to a file.
