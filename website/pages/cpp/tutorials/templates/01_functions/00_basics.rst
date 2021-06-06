.. title: 00 - basics
.. slug: 00_basics
.. description: C++ function templates - basics
.. author: Xeverous

The need for abstraction
########################

Suppose you have a min function:

.. cch::
    :code_path: 00_basics/min1.cpp
    :color_path: 00_basics/min1.color

Now suppose you want to have the same function, but for doubles and strings:

.. cch::
    :code_path: 00_basics/min2.cpp
    :color_path: 00_basics/min2.color

You can easily overload it, but you notice that the code is almost identical, only **types** have changed. Everything else is duplicated and we know that code duplication is one of the worst mistakes in programming. It would be very nice to have an abstraction that allows to use the same code with arbitrary types. Templates exist for this purpose.

Creating templates
##################

.. admonition:: definition
    :class: definition

    There are 4 kinds of templates in C++:

    - function templates
    - class templates
    - alias templates
    - variable templates

    All of them allow to abstract types and values.

To make an entity a template, there are 2 simple steps:

- Prepend the entity with a :cch:`template` signature with some aliases (here we will use a :cch:`typename` alias because we want to abstract a type).
- Replace desired type/value occurences with specified aliases.

.. cch::
    :code_path: 00_basics/min_template.cpp
    :color_path: 00_basics/min_template.color

This is very close code to the simplest overload of :cch:`std::min` function template.

The template signature works just like a function signature with minor differences:

- it is written using ``<>`` instead of ``()``
- it gives names to template parameters instead of function parameters

Just like with function parameters, there can be multiple template parameters and they may have defaults. More on these later.

:cch:`class` vs :cch:`typename`
===============================

Sometimes you might see :cch:`class` used in place of :cch:`typename`. Historically, :cch:`class` was originally used as in C++ it's preferred to give extra meaning for existing keywords instead of making new ones to avoid breaking existing code. Some time later :cch:`typename` was added to avoid the confusion. There was 1 corner case: :cch:`typename` was not allowed in templates of templates but that was basically a typo in the standard which got fixed in C++17 - compilers already knew of this mistake and accepted the keyword.

My recommendation is to use the intended keyword :cch:`typename`. It avoids confusing some people that only classes can be used inside templates.

.. admonition:: Types in templates
    :class: note

    The type with which the template is used does not have to be a class. It can be absolutely any type (potentially even an *incomplete type*) as long as the definition is valid when the alias is replaced with an actual type.

Naming convention
=================

The name of the alias doesn't really matter, but it is a very strong convention to use T and consecutive letters (U, V, W, ...) for arbitrary type aliases. It probably originated from word "type" or "template".

Template type aliases are PascalCase, not UPPERCASE. We just have a 1-letter name here. Later, in more advanced scenarios, longer, more descriptive alias names will be used such as ``UnaryPredicate`` or ``RandomAccessIterator`` to indicate the template is supposed to be used with type that satisfies certain concepts.

Because in the minimum function code relies on support for :cch:`operator<`, ``T`` could be named ``LessThanComparable``.

Passing arguments
#################

In function templates, you generally want to pass objects by const reference because:

- If the type is not copyable, there is no choice.
- If the type is expensive to copy, const reference is much more optimal than a copy.
- If the type is cheap to copy, const reference will get optimized to copy (or more precisely, the whole function will get inlined).

The only time you would want to pass objects by value in function templates is when you are sure that all possible types the template could be used with are cheap to copy.

Template limits
###############

In C++ there are no limits what template code can do. Example possibilities:

.. TODO should there be any examples?

.. code::

    template <typename T>
    bool is_default_constructed(const T& value)
    {
        return value == T();
    }

    template <typename Numeric>
    bool is_zero(Numeric num)
    {
        return num == static_cast<Numeric>(0);
    }

    template <typename T>
    void reset(T& t)
    {
        t.x = 0;
        t.y = 0;
    }

    template <typename T>
    std::size_t allocator_size(const T& /* obj */)
    {
        return sizeof(typename T::allocator_type);
    }
