.. title: 02 - member functions
.. slug: index
.. description: class member functions
.. author: Xeverous

Classes, just like member variables (**fields**) can also contain member functions (**methods**).

.. cch::
    :code_path: member_function_calls_demo.cpp
    :color_path: member_function_calls_demo.color

Output:

.. code::

    2/6
    5/10
    1/3
    1/2

Notice few things:

- Member functions, just like member variables are defined inside the class.
- Member functions have innate ability to access member variables - as if all member variables were always passed as arguments.
- Because member functions are tied to a specific class, they can not be called like global functions. They need to be called **on a specific object**, and this is done using ``.`` operator.

If you would like to split the code above into files:

.. TOCOLOR

.. cch::
    :code_path: split_code.cpp
    :color_path: split_code.color

.. admonition:: note
    :class: note

    Member functions defined inside class are implicitly :cch:`inline`. It's recommended to write short member functions in the class definition to help the compiler optimize their calls (through inlining when LTO is not available) and avoid boilerplate (by specifying function arguments again in the source file).

For simplicity, since majority of examples in the tutorial are single-file they will contain function definitions inside the class definition.

Invariants
##########

Thanks to member functions, the code is now more object-oriented but it still contains some flaws. What happens if we do something like this?

.. cch::
    :code_path: broken_invariant.cpp
    :color_path: broken_invariant.color

.. details::
    :summary: Answer

    - For (1), the fraction will be simplified to 1/0 because :cch:`gcd(2, 0) == 1$$$func(num, num) == num`.
    - For (2), the code will invoke undefined behavior because :cch:`gcd(0, 0) == 0$$$func(num, num) == num` and integer division by 0 is undefined.

In both cases, the intial problem is that fraction *invariant* was broken - the denominator can not be zero. No matter how well member functions treat the data, we can always use the ``.`` operator to access and modify class members, potentially breaking some conditions on which the methods operate.

.. admonition:: definition
    :class: definition

    An invariant is something that is always true. A condition that must always be satisfied.

Can we protect the code from breaking invariants? Yes. For this, we will need to restrict the access to some class members.
