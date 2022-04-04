.. title: 04 - constructors
.. slug: index
.. description: constructors
.. author: Xeverous

.. TODO explain explicit

Remember recent problem of being unable to create objects with custom initial values? This lesson will solve it.

Constructors are one of **special member functions**. They are automatically called whenever an object of their type is created. They have 2 main purposes:

- initialize all fields
- establish class invariants

.. cch::
    :code_path: syntax.cpp
    :color_path: syntax.color

Pay attention to the syntax:

- Constructors always use the name of the class.
- Constructors do not have a return type - not even :cch:`void`.

Besides these, constructors behave just like member functions:

- Constructors are affected by access specifiers.
- It's possible to overload constructors (including :cch:`= delete`). If no overload can be selected - compilation error.
- It's possible to place a :cch:`return;` statement in their body, just like in a function returning :cch:`void`.

Initialization vs assignment
############################

As you already know, when creating objects, initialization should always be preferred over assignment. Creating uninitialized objects only asks for trouble (and if the initial value cannot be given it means the object has too large lifetime and is not needed that early).

Constructors use special syntax for initialization - **member initializer list**:

.. cch::
    :code_path: member_init_list.cpp
    :color_path: member_init_list.color

*Member intializer list* is placed before the body, it starts with ``:`` and member initializers are separated by ``,``. The example presents a common style of formatting.

You might have also noticed a surprising thing - **parameter names are identical to member names.** This is a special feature of *member intializer list* - names after ``:`` and ``,`` are parsed as member names, everything else is treated as function (constructor) parameters.

The list does not have to contain all class members - if any of them already have an initializer defined in the class body, they can be skipped. If a member is present in the list, its initialization code simply overrides the default initializer.

Initialization order
####################

.. admonition:: warning
  :class: warning

  *Member initializer list* can have different order than definitions of class members but the order of initialization always matches order of class members. This can lead to compiler warnings about misleading order and undefined behavior.

.. cch::
    :code_path: member_init_order.cpp
    :color_path: member_init_order.color

.. ansi::
    :ansi_path: member_init_order.txt

Order of fields in member initializer list has no influence on the initialization order - **it's defined by the order of fields in the class definition**. This leads to a simple conclusion:

.. admonition:: tip
  :class: tip

  Always write members in *member initializer list* in the same order as they are defined in the class definition.

Delegating constructors
#######################

The :cch:`fraction$$$type` class can offer 3 reasonable possibilities of initialization:

- 0 arguments: the object should represent zero (0/1)
- 1 argument: the object should represent a whole number (x/1)
- 2 arguments: the object will have both values specified explicitly (x/y)

The are multiple ways to achieve it. There is nothing special in overloading constructors, but there is an additional feature: **constructor delegation**. A constructor can replace *member initializer list* with a call to a different overload.

Below I showcase various ways to achieve support for 0, 1 and 2 arguments:

.. cch::
    :code_path: delegation.cpp
    :color_path: delegation.color

All of A, B and C are valid. The goal is to write least amount of code and avoid code duplication. In the case of :cch:`fraction$$$type` class, C wins because only 1 function has to be written.

Your preference should be in this order:

- default arguments (each default argument acts as another overload)
- delegation
- separate overloads

Constructor delegation helps avoiding writing *member initializer list* multiple times.

Calling constructors
####################

Calling constructors works the same way as *function overloading* but there is a small syntax trap when you want to call an overload with 0 parameters:

.. cch::
    :code_path: calling_ctors.cpp
    :color_path: calling_ctors.color

.. admonition:: tip
  :class: tip

  If you want to call a constructor with 0 arguments, remember to not write ``()``.

This syntax problem is not present when you do :cch:`auto fr = fraction();$$$keyword var_local = type();`.

Other options
=============

There are 2 other ways to call constructors:

.. cch::
    :code_path: calling_ctors_other.cpp
    :color_path: calling_ctors_other.color

``{}`` places additional requirement: no *narrowing convertions*. So giving a :cch:`long` would not work because convertion from :cch:`long` to :cch:`int` is considered *narrowing*.

``=`` is very convenient when you want to call a constructor with exactly 1 argument. For the :cch:`fraction$$$type` class this allows very intuitive statements like :cch:`fraction fr = 5;$$$type var_local = num;` (here creating a fraction 5/1).

Default constructor
###################

If a class does not have any constructors specified, it automatically gets a **default constructor**. It has the following properties:

- it's :cch:`public`
- it takes 0 arguments
- it uses initializers defined inside class body (if present)
- it has empty body

If you have defined custom constructors and still want to have the default one, you can write :cch:`class_name() = default;$$$func() = keyword;` to force its existence. You can also write :cch:`class_name() = delete;$$$func() = keyword;` to explicitly disable its existence.

When an object of specific class can be constructed with 0 arguments, the class is *default constructible*. Note that this can be achieved even if the constructor takes multiple parameters - just provide default arguments (see variant C in delegation example).

Questions
#########

    How does *function overloading* interact with *access specifiers*?

Access specifiers do not affect *overload resolution* - functions are selected without checking their access. If a function is selected and it can not be called in the current context (e.g. a :cch:`private` function call outside the class) it's simply a compiler error.

    Constructors are affected by access specifiers. Is there any point of other specifier than :cch:`public` for a constructor? Wouldn't other access prevent from creating an object?

It would, but only outside the class code. There are some situations where having non-public constructor is beneficial. For example, a class can have 1 :cch:`private` constructor overload and many :cch:`public` overloads, all which delegate to the :cch:`private` one. More examples of non-public constructors will be presented in later lessons.

    What happens if there is a loop within constructor delegations?

Same thing as with mutually recursive functions - the program will be stuck in an endless call cycle (or something worse because technically endless recursion is undefined behavior).
