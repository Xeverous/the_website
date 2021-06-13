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

The :cch:`explicit` convertion feature has been added after it turned out that user-defined implicit convertions are hardly ever useful and can cause lots of bugs:

.. TOCOLOR

.. code::

    // even if a and b are of different types but have implicit convertion to bool,
    // the compiler will use built-in operator==(bool, bool)
    if (a == b)
        // ...

To solve this (in era before C++11), there was a `safe bool <https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Safe_bool>`_ idiom. A class did not overload convertion to :cch:`bool`, but to a member function pointer or a member data pointer, which themselves are convertible to :cch:`bool`. Then it added some template overloads of :cch:`operator==` and :cch:`operator!=` which call empty member function to cause compilation errors on specific (unwanted) comparisons. In short, it was a pretty complex idiom to implement correctly, only to prevent certain unwanted implicit convertions to :cch:`bool`.

After C++11 introduced :cch:`explicit` for user-defined convertions, the safe bool idiom is now obsolete.

Recommendation
##############

Make user-defined convertions :cch:`explicit`, especially convertions to :cch:`bool`.
