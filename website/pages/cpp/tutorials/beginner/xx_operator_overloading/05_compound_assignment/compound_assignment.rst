.. title: 05 - compound assignment
.. slug: index
.. description: compound assignment operators
.. author: Xeverous

Compound assignment operators can be defined both as free functions and as member functions. Member functions are preferred because their implementation is simpler and since the operation has no symmetry (:cch:`a += b$$$var_local += var_local` is not the same as :cch:`b += a$$$var_local += var_local` for non-numeric abstractions, e.g. strings) there are no problems with inconsistent implicit convertion.

Both free and member function implementations can return a reference to allow chained operations like :cch:`a = b = c = d$$$var_local = var_local = var_local = var_local` (most commonly done with operators ``<<`` and ``>>``) (member function uses :cch:`return *this;` statement, free function returns first parameter which for the cause of modification is taken by non-const reference).

To avoid code duplication, there are 2 choices:

- compound assignments reuse other operators
- other operators reuse compound assignments

The second one is preferred. Reason: just simpler and less code to write.

Updated code:

.. cch::
    :code_path: compound_assignment.cpp
    :color_path: compound_assignment.color
