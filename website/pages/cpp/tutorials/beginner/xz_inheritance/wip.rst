.. title: inheritance wip
.. slug: inheritance_wip
.. description: WIP
.. author: Xeverous

.. admonition:: note
  :class: note

  - The default inheritance for :cch:`struct` is :cch:`public`.
  - The default inheritance for :cch:`class` is :cch:`private` (rarely useful).

Acess when deriving
###################

Just like members can have specific access level (one of :cch:`private`, :cch:`protected` and :cch:`public`), inheritance can too.

.. list-table::
    :header-rows: 1

    * - access in base
      - derived as public
      - derived as protected
      - derived as private
    * - public
      - public
      - protected
      - private
    * - protected
      - protected
      - protected
      - private
    * - private
      - (no access)
      - (no access)
      - (no access)

It's worth mentioning that non-public inheritance is a C++-specific feature (at least I haven't seen another language that supported it). Other languages do not have the concept of changing access level in derived types, they do not have a syntax that supports access specifier in inheritance and always work as if the type was derived as :cch:`public`. Non-public inheritance is not typical OOP practice, it's a niche within C++ for some implementation tricks (many which are used in standard library implementations).

Classes which are derived in non-public way disallow convertions to their non-public bases for code outside the class. This effectively prevents any outside code in treating the type as if it was a base, making inheritance acts an implementation detail, usually only for the purpose of code reuse. In such cases any external code should treat the class as if it has no such parent.

Static vs dynamic type
######################

- A **static type** is a type of the object that is visible during compilation of the program.
- A **dynamic type** is the real type of the object during runtime, which might be identical to the *static type* or be a type derived from it.

As you move further into inheritance and polymorphism, specific language features will be described using one of these terms.
