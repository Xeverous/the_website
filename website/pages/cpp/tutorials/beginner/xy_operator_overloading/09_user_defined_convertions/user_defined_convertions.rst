.. title: 09 - user defined convertions
.. slug: index
.. description: overloading user defined convertion and operator!
.. author: Xeverous

It's possible to define custom convertions by overloading :cch:`operator T`. The operator must be a member function that takes 0 arguments.

By default, the convertion is implicit. Since C++11 :cch:`explicit` can be used to disallow implicit convertions - using it is strongly recommended.

.. cch::
    :code_path: fraction.cpp
    :color_path: fraction.color

:cch:`operator!` must be a member function that takes 0 arguments. It has no restrictions on the return type although there is very little point in a type different than :cch:`bool`. Since C++11 ``!`` performs *contextual convertion* to :cch:`bool` so overloading :cch:`operator bool` is enough - expressions like :cch:`if (!obj)$$$keyword (1oo`var_local)` where ``!`` is not overloaded will be treated as :cch:`if (!static_cast<bool>(obj))$$$keyword (!keyword<keyword>(var_local))`.

Example usage:

.. cch::
    :code_path: example_usage.cpp
    :color_path: example_usage.color

Trivia
######

The :cch:`explicit` convertion feature has been added after it has been realized that user-defined implicit convertions are hardly ever useful. Expressions like :cch:`if (a == b)$$$keyword (var_local == var_local)` where :cch:`a$$$var_local` and :cch:`b$$$var_local` are objects of different types would compile - the compiler would implicitly convert both objects to :cch:`bool` and then compare them.

To solve this (in era before C++11), there was a `safe bool <https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Safe_bool>`_ idiom. A class did not overload convertion to :cch:`bool`, but to a member function pointer or a member data pointer, which themselves are convertible to :cch:`bool`. Then it added some template overloads of :cch:`operator==` and :cch:`operator!=` which call empty member function to cause compilation errors on specific (unwanted) comparisons. In short, it was a pretty complex idiom to implement correctly, only to prevent certain unwanted implicit convertions to :cch:`bool`.

After C++11 introduced :cch:`explicit` for user-defined convertions, the safe bool idiom is now obsolete.

Recommendation
##############

Make user-defined convertions :cch:`explicit`, especially convertions to :cch:`bool`.
