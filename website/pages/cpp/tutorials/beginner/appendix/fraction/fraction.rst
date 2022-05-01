.. title: fraction
.. slug: index
.. description: complete fraction class
.. author: Xeverous

Below is the complete fraction class (written in most idiomatic way), with everything that was used in any lesson (with all possible improvements).

.. TODO add all 4 roudning functions (round, ceil, floor, truncate)

.. cch::
    :code_path: fraction.cpp
    :color_path: fraction.color

..

    Couldn't the :cch:`gcd$$$func` function be :cch:`constexpr`?

Actually, everything except :cch:`print$$$func` function can be :cch:`constexpr`. Adding it is very trivial so I choose not to - it would only increase verbosity.
