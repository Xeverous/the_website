.. title: std::function
.. slug: index
.. description: function object class
.. author: Xeverous

:cch:`std::function` is an implementation of a generic function object - an object that can be used like a function while supporting passing itself by value and assigning different *callables*. It is the equivalent of :cch:`delegate$$$keyword` in C#. Because of :cch:`std::function`'s primary ability, it's mainly used for callbacks - places where the user can specify what should happen when a certain action is triggered (e.g. GUI). It's essentially a replaceable virtual function that supports holding some state (usually lambda captures).

.. cch::
    :code_path: example.cpp
    :color_path: example.color

The primary features of this class template are:

- instances are copyable
- it can be assigned different *targets* (free functions, lambdas and many other *callables*)
- it overloads :cch:`operator()` so it can be called just like a function

Internally, it allocates (statically or dynamically) a storage that holds all necessary state in order to be capable of performing the call. For free functions this simply means storing a pointer to them, for lambdas this means storing their captured state, for member functions this means storing a pointer to the object and so on...

The exact implementation uses very advanced technique - *type erasure*. Explaining it goes far beyond this article, especially since it requires significant knowledge in all of: templates, pointers, polymorphism implementation (how vtable works and such) and C++ language rules (concept *callable*, operator overloading and lifetime semantics). Additionally, efficient implementations use *small buffer optimization* which even further complicates the code. The greatness of the :cch:`std::function` is that while it's one of the hardest things to implement, it's usage is extremely simple and thus the article is focused on less skilled readers - for now I will simply call the implementation *magic*.

The core interface looks as follows:

.. cch::
    :code_path: interface.cpp
    :color_path: interface.color

By default, the function object is empty (no *target* set). Calling :cch:`operator()` when there is no target causes :cch:`std::function` to throw :cch:`std::bad_function_call`.

    Why does it throw in such case? Couldn't it just do nothing?

At first this sounds like a reasonable behavior alternative, but what when :cch:`R$$$param_tmpl` is not :cch:`void` (the result is potentially passed somewhere)? Theoretically if the type was *default-constructibe* :cch:`std::function` could return a new instance of it but - what if it doesn't make sense in the given application or the type has no default constructor? I think it's much better to have a single throw-on-no-target behavior than an entire set of rules that governs what :cch:`operator()` does when there is no target.

The only other reasonable option would be to make it UB.

Performance
###########

Call cost
=========

From performance point of view, if the cost of a function call is ``F`` and the cost of a virtual function call is ``V + F``, the cost of a :cch:`std::function` call is not higher than ``2V + F`` (at least that's what I observed from my own experiments - just slightly more expensive than standard virtual call). It's a pretty efficient mechanism for something that offers a polymorphic call with the possibility of copying and replacing the *target* - classical virtual functions inside classes do not allow reassignment.

Allocation
==========

:cch:`std::function` may allocate its storage dynamically to hold necessary data to perform the call. In case of pointer or :cch:`std::reference_wrapper` targets, small buffer optimization is guuaranteed (no dynamic allocation, the class will use its own static buffer capable of holding a pointer).

Binds
#####

:cch:`std::bind` makes very little sense even though it was added in C++11. Everything it does can be done by lambda expressions, sometimes even with better performance due to the fact that language features generally have higher potential of optimization than library code. A lot of helper binders and wrappers were already deprecated in C++11/17 and removed in C++17/20.

.. cch::
    :code_path: binds.cpp
    :color_path: binds.color

I have never found a reason to use :cch:`std::bind` over lambdas, so my recommendation is to use the latter.

Lifetime
########

Const reference
===============

Const reference extends the lifetime of a temporary. But this is not the case when it happens through :cch:`std::function` call - there are multiple layers of abstraction inside (potentially multiple function calls) and thus the temporary object dies before reaching final reference.

.. cch::
    :code_path: lifetime_const_reference.cpp
    :color_path: lifetime_const_reference.color

Ownership
=========

:cch:`std::function` doesn't manage lifetime of objects used inside the target. It only cares about its storage that holds required information to perform the call. This means that if :cch:`std::function` is assigned a lambda expression with state captured by reference, the referenced state must live to the point of function object call.

.. cch::
    :code_path: lifetime_lambda_capture.cpp
    :color_path: lifetime_lambda_capture.color

Similarly, if you assign a :cch:`struct` with overloaded :cch:`operator()`, the :cch:`struct` will be held in :cch:`std::function`'s storage, but anything referenced by the :cch:`struct` can die before invokation takes place.

Copying issues
##############

:cch:`std::function` requires the target to be copyable. If you don't have C++23 and need to store a move-only callable, you can wrap it using the class template below. It won't make it copyable (will throw exception on any attempt) but will at least make it compile so that you can use the callable as long as the function object copy is not attempted.

    Why such limitation exists? :cch:`std::vector<T>` doesn't require :cch:`T` to be copyable as long as vector's copy constructor is not used. Couldn't :cch:`std::function` go this way?

My initial thought was the answer "no, because *type erasure* used within its implementation requires copyable types" but after experimenting with it, I realized that :cch:`std::function` indeed doesn't copy the callable when the function object is not copied (at least with libstdc++ implementation, used by GCC). So sadly, I can not answer the question now. I don't even know why for C++23 it was decided to add :cch:`std::move_only_function` than to change specification to make :cch:`std::function` only require copyable types when copy constructor is called.

TODO implementation of fake_copyable

Move-only function object
#########################

Since C++23 there is :cch:`std::move_only_function` that allows move-only callables. The interface is identical to that of :cch:`std::function`, except few things:

- :cch:`const` qualifier, ref-qualifiers and :cch:`noexcept` are a part of class template specializations and they are "forwarded" to the :cch:`operator()` so this class is more const-correct, ref-correct and noexcept-correct than :cch:`std::function`.
- Calling :cch:`operator()` when there is no target is UB instead of throwing an exception.
- No :cch:`target$$$func` and `target_type$$$func` member functions.

For reasoning, see `https://wg21.link/P0288R9 <P0288R9>`_

Additional resources
####################

note: all talks are on somewhat advanced level

- `CppCon 2018: Tom Poole "Why and How to Roll Your Own std::function Implementation" <https://www.youtube.com/watch?v=VY83afAJUIg>`_
- `CppCon 2017: Sven Over "folly::Function: A Non-copyable Alternative to std::function" <https://www.youtube.com/watch?v=SToaMS3jNH0>`_
- `CppCon 2019: Arthur O'Dwyer "Back to Basics: Type Erasure" <https://www.youtube.com/watch?v=tbUCHifyT24>`_
