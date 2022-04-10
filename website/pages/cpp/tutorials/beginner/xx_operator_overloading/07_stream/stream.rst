.. title: 07 - stream operators
.. slug: index
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

.. cch::
    :code_path: operator_chaining.cpp
    :color_path: operator_chaining.color

Simply put, the trick is to return a reference to the stream. Then, the same operation can be repeated.

Canonical implementation
########################

.. admonition:: note
    :class: note

    - :cch:`std::cout` is a global object of type :cch:`std::ostream`
    - :cch:`std::cin` is a global object of type :cch:`std::istream`

    Standard library file streams (:cch:`std::ofstream`, :cch:`std::ifstream` and :cch:`std::fstream`) and string stream (:cch:`std::stringstream`) have types *derived* from types mentioned above, so operator overloads also work with them.

.. cch::
    :code_path: stream_overloads.cpp
    :color_path: stream_overloads.color

Standard argument passing recommendations apply:

- In both operators stream is taken by non-const reference because any work on the stream changes its state.
- Stream insertion only reads the data so should it should take the object (here: fraction) by value or const reference (here: value because fraction class is cheap to copy).
- Stream extraction stores the result in the object so the object must be passed by non-const reference.

Example with string stream:

.. cch::
    :code_path: example.cpp
    :color_path: example.color

..

    How about :cch:`operator<<=` and :cch:`operator>>=`?

Their implementation should follow the same guidelines as other compound assignment operators but these operators only make sense when :cch:`operator<<` and :cch:`operator>>` are implemented to perform mathematical operations. If you implement stream insertion/extraction, these operators should be left unimplemented.

Exercise
########

What's wrong with the implementation below?

.. cch::
    :code_path: exercise.cpp
    :color_path: exercise.color

.. details::
    :summary: Answer

    The function does not use the stream provided as an argument. Instead, it always inserts data to :cch:`std::cout`. This is a bug because someone might want to output a fraction to a different stream. Even worse that this function will also return a reference to the wrong stream object.
