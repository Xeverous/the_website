.. title: 06 - increment and decrement
.. slug: 06_increment
.. description: increment and decrement operators
.. author: Xeverous

As you should remember, increment and decrement have 2 variations:

- prefix should apply the change and return modified value
- postfix should apply the change and return old value

As with compound assignments, to avoid code duplication one operator implementation should reuse the other one. Postfix operators should reuse prefix operators - this way code is simpler.

Increment and decrement need to be defined as member functions. But how to differentiate prefix from postfix operator overload? Due to syntax limitations, it has been decided that the ambiguity problem will be fixed by adding a dummy :cch:`int` parameter to postfix operators. The value of this parameter is always :cch:`0` and it should be always ignored.

As with many other operators, this one is going to reuse fraction class. Some readers might come up with 2 potential designs:

- increment changes 2/4 to 3/4 (adds 1 to numerator)
- increment changes 2/4 to 6/4 (1 + 2/4)

The first design is wrong. Example: 2/4 is equal to 3/6. So after incrementing both, we have 3/4 and 4/6 which aren't equal. The second design works correctly: 6/4 is equal to 9/6.

.. TOCOLOR

.. code::

    // all inside class body

    fraction& operator++() // prefix increment
    {
        m_numerator += m_denominator;
        return *this;
    }

    fraction& operator--() // prefix decrement
    {
        m_numerator -= m_denominator;
        return *this;
    }

    fraction operator++(int) // postfix increment
    {
        fraction old = *this; // copy old value
        operator++(); // reuse prefix; you can also write ++(*this);
        return old;
    }

    fraction operator--(int) // postfix decrement
    {
        fraction old = *this;
        operator--();
        return old;
    }

Pay attention to the return types:

- postfix operators return by value because there is no other way - an old value must be a separate object
- prefix operators return by reference because after the operation we want to continue using modifed object

Notable exception
=================

Operator overloads for :cch:`std::atomic` always return by value but they have a good reason to violate the convention - the whole point of atomic types is to ensure atomic loads and stores in machine code - returning references would allow to accidentally circumvent the mechanism, breaking code intended to run concurrently.
