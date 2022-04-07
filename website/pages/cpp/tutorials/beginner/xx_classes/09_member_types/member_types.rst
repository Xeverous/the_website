.. title: 09 - member types
.. slug: index
.. description: class member types
.. author: Xeverous

A class apart from data and function members, can also contain member types.

Non-class member types
######################

This just follows same conventions as :cch:`static` members - they act as free entities but are defined within class namespace.

I haven't seen a lot of member enumerations, but member type aliases can be very useful to reduce code duplication, increase flexibility and shorten the code:

.. cch::
    :code_path: member_using.cpp
    :color_path: member_using.color

Any code outside the class can use :cch:`config::container_type$$$type::type`. Apart from being shorter, if the class implementation changes (different data structure) any code outside is automatically adjusted. Since most containers share similar functionality (C++ has strong conventions for names and types in member functions of containers), there is a high chance no edits will be required where data is extracted/inserted/iterated on.

Nested classes
##############

It's possible to define a class (:cch:`class` or :cch:`struct`) or :cch:`union` within another class. Such types do not have any additional requirements, objects of both outer and inner can exist independently. Intuitively, they follow analogical namespace rules for declarations and definitions:

.. cch::
    :code_path: member_class.cpp
    :color_path: member_class.color

Access specifiers
#################

Member types are affected by *access specifiers* but have an additional permission: because they are members, just like any member they also have the access to all other members of the enclosing class:

.. cch::
    :code_path: access_specifiers.cpp
    :color_path: access_specifiers.color

Because types and functions can have different access, it's also possible to create situations like this:

.. cch::
    :code_path: return_private.cpp
    :color_path: return_private.color

Obviously don't write such code.

.. admonition:: tip
  :class: tip

  If a :cch:`public` function returns an object of a member type (just like in the first example), make that type :cch:`public` too.
