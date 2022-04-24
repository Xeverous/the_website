.. title: 07 - covariant return types
.. slug: index
.. description: an extra feature of virtual functions
.. author: Xeverous

Due to various *design patterns*, polymorphic types rarely need to be copied. But sometimes there is a need to do so. However, polymorphic types can not be copied easily. Copies done using ``=`` are potentially sliced because it's unknown what the dynamic type of the object is (the operator only considers the static type).

An idiomatic workaround would be to write a virtual function for the copy. The problem is, memory-related properties (size, alignment etc.) of different types can be different so the potential return type or the type of a potential in-out parameter must be something clever that supports multiple, different dynamic types.

This naturally brings us to pointers and references. A virtual function can be specified to return a pointer or reference to the base type. Any override of this function can actually produce an object which type is derived from specified and cast it upwards.

Because references and pointers to function-local objects are dangling, the only way to avoid the problem is to use *dynamic memory allocation*. This leads us to a following implementation:

.. cch::
    :code_path: clone.cpp
    :color_path: clone.color

Dynamic memory allocation is a topic for a separate tutorial, so I'm not going to delve into it now. The only thing worth mentioning is that in modern C++ (2011 standard and later) *naked new* is a really bad thing. All dynamically allocated objects should be managed by *smart pointers* or *containers*. The example above should be rewritten as:

.. cch::
    :code_path: clone_modern.cpp
    :color_path: clone_modern.color

However, for the purpose of explaining *covariant return types* we will stick to the first example. Why? Read further.

Because casts upwards do not need any machine instructions (it's purely an abstraction cast), virtual functions offer a special feature which allows the return type to differ slightly.

A virtual function in derived class can return a type that is *covariant* to the type specified in the base class. A type is covariant if:

- it's also a reference or also a first-level pointer (pointers to pointers not allowed)
- the referenced type is derived from the referenced type in function's return type in the base class
- the type is equally or less cv-qualified to the function's return type in the base class
- the type is complete (forward declarations not allowed)

One of the best examples where covariant return types are useful is copying:

.. cch::
    :code_path: clone_covariant.cpp
    :color_path: clone.color

In this specific example the return type covariance uses the same class hierarchy - it's not necessary but given the occasional need for copying polymorphic objects, it's probably the most common use of covariant return types.

In a typical scenario of calling virtual functions through a pointer/reference to the base class, the feature has no impact. But if for some reason the code has a pointer/reference to a derived type, it's rewarded with richer return type information. **Sadly, as of C++20 it's not possible to use covariant return types over smart pointers.** Smart pointers to derived types are implicitly convertible to smart pointers to base types, but they do not derive from them. The feature would need to be respecified to be based on object representation or something related, but that's a really hard problem given numerous mechanics that come into play here.

Because the need for covariant return types is pretty rare, I recommend to use (non-covariant) smart pointers by default. In vast majority of cases, better resource management abstraction will be worth more than this minor polymorphism feature.
