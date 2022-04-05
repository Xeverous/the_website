.. title: 06 - mutable
.. slug: index
.. description: mutable class members
.. author: Xeverous

Expensive getters
#################

Consider a situation where there is a class that performs lots of calculations and the result takes some time to compute.

.. cch::
    :code_path: simulation.cpp
    :color_path: simulation.color

So far everything looks fine:

- all fields are private
- setters secure invariants
- computation function is const-qualified

But there is one problem - we know that data doesn't change often but we often need the computation result. If we call this function over and over, we are continuously repeating the same (expensive) calculations. We could implement some caching so that if data has not changed the class just returns the last result.

We can add a result field to the class to store last result inside but now we have a problem - the const-qualified function to compute the result can not change it!

:cch:`mutable` members
######################

.. admonition:: note
    :class: note

    :cch:`mutable` fields can be always modifed.

.. cch::
    :code_path: simulation_mutable.cpp
    :color_path: simulation_mutable.color

We have moved actual computation to a private function, which is now called when there is no result available. Setters have been modified to reset the result if specified parameter values are different. Now the code outside the class can call :cch:`get_result$$$func` as many times as needed and it will only be computed if something changed.

.. TODO is this a complete memo design pattern? if yes, mention it here

In practice
###########

In practice :cch:`mutable` is used very sparingly. It's purpose is to specify that the member does not affect the externally visible state of the class. It should be used when there is a strong desire to const-qualify a member function but specific class implementation (such as result caching in the presented example) requires changes in some members in such function.

The most common use of :cch:`mutable` is for members that implement synchronization mechanisms such as :cch:`std::mutex`. For a thread-safe class, a mutex needs to be locked and unlocked in every member function so the only way to preserve const-correctness on the outside is to use :cch:`mutable std::mutex$$$keyword namespace::type` member.

.. details::
    :summary: Extra technical details

    - :cch:`mutable` fields can not be :cch:`const` on the top level
    - :cch:`mutable` fields can not be :cch:`static`
    - :cch:`mutable` fields can not be references

    .. cch::
        :code_path: mutable_details.cpp
        :color_path: mutable_details.color
