.. title: 10 - friends
.. slug: index
.. description: friend declaration
.. author: Xeverous

.. admonition:: note
  :class: note

  This lesson presents a feature which is useful only in certain niches, particularly some operator overloads. You can skip this lesson and come back here when you actually need to use it.

:cch:`friend`\ s allow to ignore *access specifiers*.

*Friend declarations* are not themselves affected by *access specifiers*  so it doesn't matter where they are put.

Friend functions
################

A class can :cch:`friend` a non-member function. This function will have access to :cch:`private` and :cch:`protected` members.

.. cch::
    :code_path: friend_function.cpp
    :color_path: friend_function.color

:cch:`friend` function definition can also be placed directly within the class. In such case it's implicitly :cch:`inline`.

.. cch::
    :code_path: friend_function_inline.cpp
    :color_path: friend_function_inline.color

.. admonition:: note
  :class: note

  :cch:`friend` function definitions inside class are only allowed if the class is defined non-locally - it won't work for class defined locally in a function.

Friend classes
##############

A class can :cch:`friend` another class. Friended class (and it's functions) will have access to :cch:`private` and :cch:`protected` members. This works only in 1 direction.

There are 3 syntax possibilities here:

- :cch:`friend simple-type-specifier;$$$keyword 21spec;`
- :cch:`friend typename-specifier;$$$keyword 18spec;`
- :cch:`friend elaborated-class-specifier;$$$keyword 26spec;`

The reasoning for limited syntax is simple: :cch:`friend` declarations care only about the type name alone, code like :cch:`friend const foo&;$$$keyword keyword type&;` makes no additional sense by introduction of qualifiers. Thus, only a subset of syntax have been allowed instead of something like :cch:`decl-specifier-seq$$$0spec`.

Enough technicalities, now what's the real impact of it? As far as average C++ programmer would be concerned, there are 2 different usages:

- :cch:`friend identifier;$$$keyword spec;` (from first 2)

  - :cch:`identifier$$$spec` must already exist.
  - if :cch:`identifier$$$spec` does not name a :cch:`class`, :cch:`struct` or :cch:`union`, it's not an error but the statement is ignored instead

- :cch:`friend class identifier;$$$keyword keyword spec;` (from :cch:`elaborated-class-specifier$$$0spec`) (the :cch:`class` can also be :cch:`struct` and :cch:`union`)

  - if there is no type named :cch:`identifier$$$spec`, it additionally acts as a forward declaration

.. cch::
    :code_path: friend_classes.cpp
    :color_path: friend_classes.color

..
    I get that :cch:`elaborated-class-specifier$$$0spec` allows to combine friend declaration with type forward declaration. But why in the first case when the :cch:`identifier$$$spec` names something different the statement is ignored instead of raising an error?

I don't know the exact reason, but I guess it's similar why ``.`` is allowed for :cch:`static` members: it allows some templates to work out-of-the-box. Otherwise they would have the burdern of checking if the type is (not) a class and then providing different definitions to support both cases.

Friend members
##############

A class can also :cch:`friend` specific members of other classes, provided they themselves are accessible.

.. cch::
    :code_path: friend_members.cpp
    :color_path: friend_members.color

Other rules
###########

- Friendship is a one-way relation: if :cch:`foo$$$type` friends :cch:`bar$$$type`, :cch:`bar$$$type` can access all members of :cch:`foo$$$type` but not vice versa.
- Friendship is not transitive: a friend of your friend is not your friend.
- Friendship is not inherited (child classes (*derived types*) explained in inheritance chapter):

  - your friend's children are not your friends
  - your's children do not friend your friends

In short, friendship is a one-way relation that does not propagate.

Recommendation
##############

Friends defeat the purpose of encapsulation and can be used to break class invariants. Be very cautious with their usage.

- If two classes friend each other, they probably should be rewritten as one class or their public/non-public code is badly designed.
- If one class friends a lot of other code, it probably has insufficient public interface.

**Do not friend anything from the standard library!** Each implementation can be different and contain multiple layers of internal code - since friendship is not transitive and does not propagate there are no guuatantees whether the implementation of particular standard library entity will be able to use non-public members.

.. admonition:: note
  :class: note

  The only widely accepted place of using friends is *operator overloading*.
