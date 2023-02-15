.. title: 05 - smart pointers
.. slug: index
.. description: introduction to smart pointers and how to use them for polymorphic objects; virtual destructors
.. author: Xeverous

Storing polymorphic objects
###########################

At this point you know all core features that allow polymorphism. A "cherry on top" would be something that allows storing multiple objects of different types so that you can call virtual functions on them without caring about the dynamic type.

The problem is, something like :cch:`std::vector<animal>$$$namespace::type<type>` will not work for multiple reasons:

- The type is abstract, so the vector class with this type will not compile.
- Even if it did compile, it would only allocate enough storage for objects of type :cch:`animal$$$type`.
- Even if there was enough additional storage for larger, derived types the vector class would need to keep some metadata about (varying) object sizes so that :cch:`operator[]` implementation can access memory at correct offsets in the storage.

If you try to do this (by making the :cch:`animal$$$type` non-abstract), the code will compile but the vector class will slice every object to this type.

Since dynamic types only make sense with pointers and references we should create a vector of pointers or references. Vector can not be used with reference types (their limited binding/assignment functionality disallows memory-managing code inside vector implementation) so the only left thing are pointers. But this also means that the vector can not store objects themselves, only pointers to them (and consequently, it will allocate storage only for pointers).

We could use such vector of pointers, but having to create objects elsewhere and pass pointers to them to the vector would be very annoying and limiting: at best we would need 1 vector for objects of each type and the final vector that accumulated pointers to all objects. And then all the problems with pointer/iterator invalidation...

There is a solution to all these problems though: *smart pointers*.

.. admonition:: definition
  :class: definition

  A smart pointer is a pointer that automatically manages memory. Different smart pointers implement different managing strategies. They can also be used to manage non-memory resources.

Memory management
#################

Memory allocation and resource management are topics for a separate tutorial (it's a topic as big as object-oriented programming) but because idiomatic polymorphism sort of requires this knowledge, this lesson will explain what is needed.

We won't delve into actual allocation and management (even :cch:`new` and :cch:`delete` are a high-level way of managing allocations), the whole point of smart pointers is that they do it instead. What is important is their semantics and generally how they can and should be used.

Smart pointers
##############

The C++ standard library contains 3 smart pointer class templates:

- :cch:`std::unique_ptr`, which implements *single ownership* model
- :cch:`std::shared_ptr`, which implements *shared ownership* model
- :cch:`std::weak_ptr`, which is an *observer pointer* for shared pointers
- (you can use raw pointers as observers for unique pointers)

The first 2, once constructed, will automatically manage memory of an object of specified type.

Both can be created in multiple ways:

- By calling default constructor (it will be empty won't manage any object):

  - :cch:`std::unique_ptr<T> uptr;$$$namespace::type<param_tmpl> var_local;`
  - :cch:`std::shared_ptr<T> sptr;$$$namespace::type<param_tmpl> var_local;`

- By providing a pointer to dynamically allocated object to the constructor:

  - :cch:`std::unique_ptr<T> uptr(new T(/* ctor args... */));$$$namespace::type<param_tmpl> var_local(keyword param_tmpl(18com_multi));`
  - :cch:`std::shared_ptr<T> sptr(new T(/* ctor args... */));$$$namespace::type<param_tmpl> var_local(keyword param_tmpl(18com_multi));`

- By using a factory function:

  - :cch:`auto uptr = std::make_unique<T>(/* ctor args... */);$$$keyword var_local = namespace::func<param_tmpl>(18com_multi);`
  - :cch:`auto sptr = std::make_shared<T>(/* ctor args... */);$$$keyword var_local = namespace::func<param_tmpl>(18com_multi);`

You should prefer factory functions because:

- In case of :cch:`std::shared_ptr` it's more optimal - the class also needs to allocate a control block and the factory function merges 2 allocations into 1 larger.
- They allow *no naked new* idiom - everything related to allocation is encapsulated within smart pointers and containers.
- There are some corner cases where the first approach can leak memory when a subexpression throws an exception.

The factory functions implement *perfect forwarding* idiom. Arguments passed to them are *perfectly* forwarded to the constructors of specified types.

Unlike other stuff that came with C++11, :cch:`std::make_unique` was added in C++14. If you don't have C++14 you can use equivalent implementation of the function:

.. details::
  :summary: C++11-compatible implementation

    TOINCLUDE make_unique stdex impl

Thanks to overloaded operators, once you have a smart pointer, you can:

- test whether it's not empty (AKA not null): :cch:`if (ptr)$$$keyword (var_local)`
- get a reference to the managed object: :cch:`T& ref = *ptr;$$$param_tmpl& var_local = 1oo`var_local;` (pointer must not be empty)
- access smart pointer members: :cch:`ptr.$$$var_local.`
- access managed object members: :cch:`ptr->$$$var_local2oo` (pointer must not be empty)

How it works
############

Smart pointers implement all *special member functions*, most importantly their *destructors* release (:cch:`delete`) managed memory. There are 2 *ownership models*, each with different semantics. *Ownership* specifies responsibility for managing memory.

Single ownership
================

:cch:`std::unique_ptr` models single ownership. The managed object always has 1 owner.

- The pointer can not be copied (formally, its *copy constructor* is :cch:`= delete`\ d) (this also disallows copy constructors of containers of this smart pointer).
- The pointer can be *moved*: :cch:`uptr2 = std::move(uptr1);$$$var_local 1oo namespace::func(var_local);`.

:cch:`std::move` is a simple 1-line function that returns :cch:`T&&` (*rvalue reference*) - the function is just a cast. When such reference is passed to constructors or assignment operators, it triggers *move operations*.

After the *move*, :cch:`uptr2$$$var_local` is the owner and :cch:`uptr1$$$var_local` is empty. If :cch:`uptr2$$$var_local` was already managing an object (not empty) that object is destroyed and its memory released.

In other words, :cch:`std::unique_ptr` acts as a mechanism that encapsulates calls to :cch:`new` and :cch:`delete`. You can obtain a non-managing raw pointer (*observer*) through :cch:`.get()$$$.func()` though you must ensure that such raw pointer is used only when the unique pointer exists and is non-empty. Otherwise it will be dangling, pointing to memory that has been released.

Shared ownership
================

:cch:`std::shared_ptr` models shared ownership, that is, there can be multiple owners of the memory. It additionally allocates a control block which stores small amount of metadata about managed object.

This poiner can be both moved and copied.

- First shared pointer initializes the control block and sets *use count* to 1.
- Every time a copy is made, the pointer increments *use count* within the control block.
- Every time a shared pointer is destroyed, it decrements *use count* within the control block.
- When the last shared pointer is destroyed, the *use count* becomes 0 and both control block and managed object are destoyed and their memory released.

:cch:`std::shared_ptr` is very useful for sitations when it's unclear for how long the object will be needed and/or what's the lifetime of all pointers. A sample situation is a multi-threaded program - it's unknown which thread will finish last but because the control block uses *atomic objects* threads can independently modify use count without data races and the last thread (whichever it is) will correctly release allocated memory.

:cch:`std::weak_ptr` can be constructed from :cch:`std::shared_ptr`. It will be able to access the control block but will not affect the use count (they use separate *weak count*). Weak pointers do not grant access to the managed object - :cch:`.lock()$$$.func()` has to be used on weak pointers to get a shared pointer - if the object has already been released the returned shared pointer will be empty. Thus, :cch:`std::weak_ptr` acts as an observer - it can be used to access managed object through :cch:`.lock()$$$.func()` but otherwise it does not take part in the ownership. Existence of weak pointers does not prevent the last shared pointer from releasing the object - they only prevent release of the control block.

Using smart pointers
####################

By default, you should use unique pointers. In most situations you can clearly identify what the lifetime of managed object should be - just put unique pointer in this scope. Then inside this scope you can create as many references and raw pointers as needed - they all will be destroyed before the managed object is destroyed so nothing will be dangling.

Generally, you shouldn't pass smart pointers to functions for the following reasons:

- For :cch:`std::unique_ptr`, it won't work in majority of cases as the pointer can not be copied.
- It's just limiting compared to plain references - a function should not care how an object's lifetime is managed.
- There is nothing unsafe with it: unless the function saves the address of the object for later, the smart pointer can not be destroyed while the function is executing.

Smart pointers to derived types are implicitly convertible to smart pointers to base types (they overload convertion, without :cch:`explicit`).

Destruction
###########

Each class on the inheritance hierarchy can store some members. Some of these members may manage memory (e.g. :cch:`std::string`). If we use smart pointers to manage object lifetime, they need to know how to properly destroy the object - if they only call destructors of the base class, resource-managing members in derived classes will leak.

The solution to this problem is very simple: *virtual destructors*. Destructors can be virtual just like any other function, but unlike other functions (but like constructors) virtual destructors execute **all** implementations, not just the one from most derived overrider.

You can also force a type to be abstract by making the destructor pure virtual, though in such case you must define it's body anyway. The body can still use default implementation, like this: :cch:`class_name::~class_name() = default;$$$type::11func() = keyword;`.

Summing up all that was said in this lesson, we get the following very idiomatic implementation of the animal-cat-dog example:

.. TOINCLUDE in design patterns: runtime polymorphism

.. cch::
    :code_path: animal_cat_dog.cpp
    :color_path: animal_cat_dog.color

Once a destructor is declared :cch:`virtual`, destructors in derived classes are implicitly :cch:`virtual` too (unless explicitly defined without the keyword). Because you can't expect when a specific class is used and how in other code, you should stick to the following guideline:

.. admonition:: tip
  :class: tip

  `CG C.35: <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-dtor-virtual>`_ classes intended for inheritance should have their destructors either:

  - :cch:`public` and :cch:`virtual`
  - :cch:`protected` and non-virtual
