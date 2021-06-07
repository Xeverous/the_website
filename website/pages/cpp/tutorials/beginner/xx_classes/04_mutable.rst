.. title: 04 - mutable
.. slug: 04_mutable
.. description: mutable class members
.. author: Xeverous

expensive getters
#################

Consider a situation where there is a class that performs lots of calculations and the result takes some time to compute.

.. TOCOLOR

.. code::

    class simulation
    {
    public:
        // setters for data...

        simulation_result compute_result() const; // very expensive

    private:
        int amount;
        double velocity;
        double time_ms;
        // [...] more data members...
    };

So far everything looks fine:

- all fields are private
- setters secure invariants
- computation function is const-qualified

But there is one problem - we know that data doesn't change often but we often need the computation result. If we call this function over and over, we are continuously repeating the same (expensive) calculations. We could implement some caching so that if data has not changed the class just returns the last result.

We add a result field to the class to store last result inside but now we have a problem - the const-qualified function to compute the result can not change it!

:cch:`mutable` members
######################

.. admonition:: note
    :class: note

    :cch:`mutable` fields can be modifed in const-qualified functions.

.. TOCOLOR

.. code::

    class simulation
    {
    public:
        // setters for data...

        simulation_result compute_result() const
        {
            if (!last_result)
                last_result = compute_result_impl();

            return last_result.value();
        }

    private:
        int amount;
        double velocity;
        double time_ms;
        // [...] more data members...

        mutable std::optional<simulation_result> last_result;

        simulation_result compute_result_impl() const;
    };

We have moved actual computation to a private function, which is now called when there is no result available. Implementation functions which perform the same task are usually similarly named, in C++ the convention is to append ``_impl`` to the name.

All setters will need to be modified to clear the result (make the optional empty). This will force any future call to get the result to perform computation again.

Note that storing computation result inside the class is not necessarily a good design:

- Some would argue that the class stores extra data it should not store. There should be an enclosing class that adds this caching feature.
- Some would say it's the class user responsibility to cache the result (in other words: read the documentation) and avoid calling costly function frequently when the result can be cached.

In practice you should avoid :cch:`mutable` keyword. It can be very easily overused. The only widely accepted uses in C++ are:

- When the data member is a concurrency object (e.g. a getter needs to lock a member mutex in order to access the field in a thread-safe way).
- When implementing one of well-known *design patterns*.

Other notes:

- :cch:`mutable` fields can not be :cch:`const`
- :cch:`mutable` fields can not be :cch:`static` (on static members later)
- :cch:`mutable` fields can not be references (on reference members later)
- :cch:`mutable`, unlike :cch:`const` does not affect entity's type - it only affects possible operations in member functions
