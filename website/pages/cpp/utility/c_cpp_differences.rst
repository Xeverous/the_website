.. title: differences between C and C++
.. slug: c_cpp_differences
.. description: features that exist in both languages but have different meaning
.. author: Xeverous

Below is a (hopefully complete) list of differences between C and C++.

I do not list features that are only in one language, only stuff that exists in both but has different meaning.

keywords
########

- C++ has no :cch:`restrict` keyword. There were some attempts to bring it but it is already complicated in C - in C++ due to language complexity it could very easily become a source of bug-generating optimizations if used incorrectly. Every major compiler offers :cch:`__restrict` extension though.
- C++ has no meaning for :cch:`register`, the keyword remains reserved.
- C++ has changed meaning of :cch:`auto` from storage specifier to a type specifier.

character literals
##################

In C, character literals like :cch:`'a'` have type :cch:`int`. In C++ they have type :cch:`char`. Both languages support character literal prefixes and for prefixes allowed in both languages they have the same resulting type.

string literals
###############

C allows to assign string literals to non-const pointers:

.. cch::
    :code_path: c_cpp_differences/str_abc.cpp
    :color_path: c_cpp_differences/str_abc.color

Attempting to modify such string is undefined behaviour.

Both languages allow to initialize non-const character array with a string literal:

.. cch::
    :code_path: c_cpp_differences/arr_abc.cpp
    :color_path: c_cpp_differences/arr_abc.color

There is no undefined behaviour when modifying such array.

type definitions and usage
##########################

C requires to prefix every non-built-in type name with a keyword that describes what it is.

.. cch::
    :code_path: c_cpp_differences/types1.cpp
    :color_path: c_cpp_differences/types1.color

It's possible to create an alias to avoid this requirement. A strong convention is to use exactly the same name:

.. cch::
    :code_path: c_cpp_differences/types2.cpp
    :color_path: c_cpp_differences/types2.color

A lot of code combines the type definition and an alias into one statement:

.. cch::
    :code_path: c_cpp_differences/types3.cpp
    :color_path: c_cpp_differences/types3.color

All of the above is allowed in C++ (for backwards compatibility) but not required.

A corner case where it is required are name clashes:

.. cch::
    :code_path: c_cpp_differences/types_stat.cpp
    :color_path: c_cpp_differences/types_stat.color

Obviously using the same name for a type and a function is bad practice.

empty types
###########

C does not allow empty types.

.. cch::
    :code_path: c_cpp_differences/empty.cpp
    :color_path: c_cpp_differences/empty.color

Empty types in C++ are commonly used in tag dispatching and other tricks that leverage strong typing - usually found in templates. Empty types are also a subject for empty base optimization.

empty parameter lists
#####################

In C, a function declaration with no expression between parenthesis declares a function with unspecified amount of arguments (also known as function without prototype). Calling such function with arguments that mismatch function definition results in undefined behavior. In C++ there is no such problem.

.. cch::
    :code_path: c_cpp_differences/func_decl.cpp
    :color_path: c_cpp_differences/func_decl.color

missing return
##############

In both languages it is valid to have a function with non-void return that does not return on some control flow paths.

.. cch::
    :code_path: c_cpp_differences/func_missing_return.cpp
    :color_path: c_cpp_differences/func_missing_return.color

However:

- In C it is UB to read the value returned from such function if it reached non-return path.
- In C++ it is UB to just reach the non-return path when executing the function (the stricter requirement is an effect of return value optimation which C does not have).

Writing such functions is obviously discouraged in both languages, all major compilers generate a warning.

standard library function address
#################################

C explicitly allows to take adresses of standard library functions (with exceptions).

C++ explicitly disallows to take addresses of standard library functions (with exceptions). One of the reasons is that C++ allows or requires multiple overloads for many functions, many of which can be implemented through templates and can change with standard library updates. Workaround: make a wrapper around standard library function and use the address of the wrapper.

unions
######

C allows unions for type punning.

C++ has constructors and destructors which complicate the situation. Unions allows only to access last assigned member and any other access is undefined behaviour.

.. cch::
    :code_path: c_cpp_differences/union.cpp
    :color_path: c_cpp_differences/union.color

All major C++ compilers document that such behavior is not UB in their implementation and permit it for type punning (there are other, standard-compliant ways to do it though). C++ committee is aware of the problem that this part of the standard is a grey area; from what I know there is some work undergoing to permit such code if the union members are *trivial* types.

aliasing
########

- In both languages any (potentially cv-qualified) :cch:`void*` may alias.
- In C, (potentially cv-qualified) :cch:`signed`/:cch:`unsigned`/unspecified :cch:`char*` may alias.
- In C++, only (potentially cv-qualified) :cch:`unsigned`/unspecified :cch:`char*` may alias.

Want to know more? Read the article about strict aliasing TODO link.

linkage rules
#############

Names in the global scope that are :cch:`const` and not :cch:`extern` have external linkage in C but internal linkage in C++.

.. cch::
    :code_path: c_cpp_differences/linkage.cpp
    :color_path: c_cpp_differences/linkage.color
