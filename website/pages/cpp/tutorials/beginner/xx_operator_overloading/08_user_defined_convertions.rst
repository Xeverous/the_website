.. title: 08 - user defined convertions
.. slug: 08_user_defined_convertions
.. description: user defined convertion operators
.. author: Xeverous

It's possible to define custom convertions by overloading *cast operator*.

The operator must be a member function. The syntax is keyword :cch:`operator` followed by the return type name (it has no restrictions - it can be a class too).

Optionally, :cch:`explicit` can be used to disallow implicit convertions.

.. TOCOLOR

.. code::

    // inside fraction class
    explicit operator double() const
    {
        return static_cast<double>(numerator()) / denominator();
    }

    explicit operator bool() const
    {
        return numerator() != 0;
    }

    // since C++11 this overload is no longer required
    // built-in operator! will perform contextual convertion to bool
    // overloading explicit operator bool is enough
    bool operator!() const
    {
        return !operator bool();
    }

Example usage:

.. TOCOLOR

.. code::

    void fd(double);
    void fb(bool);
    fraction fr(1, 2);

    double d1 = fr; // error if "explicit" is used
    double d2 = static_cast<double>(fr); // ok
    fd(f1); // error if "explicit" is used
    fd(static_cast<double>(fr)); // ok

    bool is_non_zero1 = fr; // error if "explicit" is used
    bool is_non_zero2 = static_cast<bool>(fr); // ok
    fb(f1); // error if "explicit" is used
    fb(static_cast<bool>(fr)); // ok

    if (fr) // fine, "if" acts as an explicit convention to bool
        // ...

    if (!fr) // also fine; since C++11 bool convertion is enough
        // ...

Trivia
######

The :cch:`explicit` feature has been added after it turned out that user-defined implicit convertions are hardly ever useful. Unwanted implicit convertions cause lots of bugs so **it's recommended to make user-defined convertions explicit**.
