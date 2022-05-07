.. title: 06 - increment and decrement
.. slug: index
.. description: increment and decrement operators
.. author: Xeverous

As you should remember, increment and decrement have 2 variations:

- prefix should apply the change and return modified value
- postfix should apply the change and return old value

As with compound assignments, to avoid code duplication one operator implementation should reuse the other one. Postfix operators should reuse prefix operators - this way code is simpler.

Increment and decrement need to be defined as member functions. But how to differentiate prefix from postfix operator overload? Intuitively, one might think :cch:`operator++` vs :cch:`++operator$$$2oo`keyword` but that's not how syntax works. Due to syntax limitations, it has been decided that the ambiguity problem will be fixed by adding a dummy :cch:`int` parameter to postfix operators. The value of this parameter is always :cch:`0` and it should be always ignored.

As with most other operators, this one is going to showcase :cch:`fraction$$$type` class too. There are 2 potential designs:

- increment changes 2/4 to 3/4 (adds 1 to numerator)
- increment changes 2/4 to 6/4 (adds 1/1 to the fraction)

The first design is wrong. Example: 2/4 is equal to 3/6. So after incrementing both, we have 3/4 and 4/6 which aren't equal. The second design works correctly: 6/4 is equal to 9/6. The second one is also consistent with general expectation that the operation modifies value by 1 (which holds for all numeric types, including floating-point).

.. cch::
    :code_path: increment_decrement.cpp
    :color_path: increment_decrement.color

Pay attention to the return types:

- Postfix operators return by value because there is no other way - an old value must be a separate object.
- Prefix operators return by reference because after the operation we want to continue using modifed object, possibly in the same statement.

Notable exception
=================

Operator overloads for :cch:`std::atomic` always return by value because the whole point of atomic types is to ensure atomic loads and stores in machine code - returning references would allow to circumvent this mechanism, breaking code intended to run concurrently.
