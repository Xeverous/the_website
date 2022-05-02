.. title: 01 - struct
.. slug: index
.. description: structure types
.. author: Xeverous

It's quite common to have a few closely related variables. The :cch:`struct` keyword allows you to define a new type that consists of multiple objects.

.. cch::
    :code_path: struct_point.cpp
    :color_path: struct_point.color

Entities defined inside are called *members*. Here the :cch:`point$$$type` type has 2 *data members*. Later you will learn about *member functions* and *member types*.

This code alone doesn't create any objects - it defines a type. :cch:`point.x$$$type.var_member` is not a valid expression. First you need to create an object of this type:

.. cch::
    :code_path: point_usage.cpp
    :color_path: point_usage.color

You can specify default values for members. If the object is not explicitly initialized, it will use initializers specified in the type definition.

.. cch::
    :code_path: point_member_initializers.cpp
    :color_path: point_member_initializers.color

If the initializers were not specified in the type definition, reading their values before assignment would be undefined behavior. Thus, **it's recommended to always initialze members**.

The example above contains small code duplication. We can fix it by writing a function:

.. cch::
    :code_path: print_point.cpp
    :color_path: print_point.color

Nested structures
#################

It's possible to nest structures. This is known as **composition** and is one of primary ways of reusing code to build larger programs.

.. cch::
    :code_path: composition.cpp
    :color_path: composition.color

.. admonition:: warning
    :class: warning

    Definition of *aggregates* (and thus *aggregate initialization*) have been evolving across C++11/14/17/20. See https://en.cppreference.com/w/cpp/language/aggregate_initialization for exact details.

The code above requires C++14, becase *default member initializers* introduced in C++11 initially were outside the definition of an *aggregate*. If you want to make the code above C++11-compatible, you have to remove default member initializers.

..

    I don't like the fact that in the second overload of :cch:`print$$$func` the code mixes function calls with :cch:`std::cout`. Is it possible to make :cch:`std::cout << p$$$namespace::var_global << var_local` work?

Yes. The specific feature that supports it is known as *operator overloading*. You can overload operators (they work just like functions with few restrictions) for *user-defined types* (built-in types already have behavior specified). I'm not going to delve into details as the topic is described in it's own chapter but for the sake of example:

.. cch::
    :code_path: stream_overload.cpp
    :color_path: stream_overload.color

More syntax
###########

- Unary operators when combined with member access are written like this: :cch:`++t1.p3.y$$$++var_local.var_member.var_member` (``.`` has higher priority).
- Type definitions can be combined with object definitions like this:

  .. cch::
      :code_path: unnamed_struct.cpp
      :color_path: unnamed_struct.color

  though such code is generally considered to be less readable (and potentially troublesome). Such practice is typically only done for types defined as nested types within other types.

Named parameters
################

In sitations where a function has multiple parameters of the same type (especially :cch:`bool`), a structure can be introduced to avoid hardly readable code:

.. cch::
  :code_path: named_parameters_before.cpp
  :color_path: named_parameters_before.color

.. cch::
  :code_path: named_parameters_after.cpp
  :color_path: named_parameters_after.color

An additional benefit is that a :cch:`struct` can be extended in more ways than function's default arguments.

Tag names in C
##############

C requires keywords :cch:`struct`, :cch:`enum` and :cch:`union` to be repeated every time respective type names are used.

.. cch::
    :code_path: tag_names.cpp
    :color_path: tag_names.color

C++ offers :cch:`namespace`\ s to group related names and avoid name conflicts in large programs - showcased code already contained some names from :cch:`namespace std`.

In C, there are no namespaces. Instead, there are "tag spaces" for names attached to different kinds of definitions. When a name from specific "tag space" is used, it must be preceeded by the tag keyword. Tag names can be introduced into global "name space" through aliases:

.. TODO typedef/using when?

.. cch::
    :code_path: typedef_struct.c
    :color_path: typedef_struct.color

Some C projects use such aliases for all of their types, others explicitly prohibit this practice (most notably the Linux kernel).

Writing :cch:`typedef struct` is considered ugly in C++ because there is no need to do so. Even if the definition comes from C code, there is no need to prepend :cch:`struct`, :cch:`enum` and :cch:`union`.

More information:

- https://stackoverflow.com/questions/612328/difference-between-struct-and-typedef-struct-in-c
- https://stackoverflow.com/questions/252780/why-should-we-typedef-a-struct-so-often-in-c
