.. title: typeof
.. slug: index
.. description: C++ typeof keywords - typeid and decltype
.. author: Xeverous

This article is intentionally named "typeof" even though formally there is no such keyword in C++. There is simply no better title given the existence of such keyword and its usage in other languages. After all, you want to know what C++ offers in place of it and why.

Why
###

The reason why C++ has no :cch:`typeof` keyword is mostly historical.

Many compilers did/do have such non-standard extension. Standarizing it would be very troublesome given the differences in existing implementations. The idea is pretty old, before ``__name`` was commonly used for extensions so many implementations added a formally-looking keyword, something that today would be very discouraged. The standard would like to avoid breaking existing code or changing the meaning of something that already exists, even if it was already violating the standard.

:cch:`typeid`
#############

This is what you usually want. The keyword works like a function and similarly to :cch:`sizeof` and :cch:`alignof` it accepts both type expressions (:cch:`typeid(T)`) and value expressions (:cch:`typeid(obj)`).

The behavior of the keyword is dependent on exact usage.

- For :cch:`typeid(T)`, if the type :cch:`T` is a reference type, the behavior is identical as if it had no reference. Thus, references are considered to have the same type ID as types they refer to, but pointers have different type IDs. Top-level cv-qualifiers are ignored, thus:

  - :cch:`typeid(T&) == typeid(T)$$$keyword(tparam&) == keyword(tparam)`
  - :cch:`typeid(const T) == typeid(T)$$$keyword(keyword tparam) == keyword(tparam)`
  - :cch:`typeid(volatile T) == typeid(T)$$$keyword(keyword tparam) == keyword(tparam)`
  - :cch:`typeid(T*) != typeid(T)$$$keyword(tparam*) != keyword(tparam)`

- For :cch:`typeid(obj)`:

  - If the object is polymorphic (a class that declares or inherits at least 1 virtual function):

    - A runtime cost is incurred to evaluate the exact type of the object (typical implementation will use object's vtable pointer to access global metadata).
    - If the expression is :cch:`typeid(*ptr)$$$keyword(*var_local)` and the pointer is null, additional guuarantee exists: instead of undefined behavior an exception is thrown of type :cch:`std::bad_typeid` or a type derived from it.

  - If the object is not polymorphic, the expression is not evaluated and is resolved at compile time (though it's not considered :cch:`constexpr`). *Decay* does not happen. In this case the resulting type ID may not represent actual (most derived) type of the object.

Similarly to virtual functions in constructors and destructors, using :cch:`typeid` during them will yield IDs about the class currently being constructed/destroyed, not the most-derived one.

In all cases, the resulting expression returns :cch:`const std::type_info&`. The type info object has infinite lifetime (*static storage duration* strictly technically) and because it's a reference, the actual referenced object can be derived from :cch:`std::type_info` if the implementation needs it.

In all cases, you have to :cch:`#include <typeinfo>$$$8pp_header 0pp_direct` in order to use the keyword. Otherwise the program is *ill-formed*.

The interface looks as follows:

.. cch::
    :code_path: interface.cpp
    :color_path: interface.color

Hash code
=========

The hash code is the same for all :cch:`std::type_info` referring to the same type. No other guuarantees are given, this means that:

- multiple types may have the same hash (although discouraged by the standard)
- hash code for the same type can change between invocations of the program

Before
======

cppreference: *returns true if the type of this :cch:`std::type_info` precedes the type of :cch:`rhs` in the implementation's collation order. No guarantees are given; in particular, the collation order can change between the invocations of the same program.*

Personally I have never seen this used in practice. :cch:`std::type_index` sounds much better.

Name
====

You would probably expect the real name of the type, as written in code, with all qualifiers. But this is not the case. The standard places no requirements on it, not even the lifetime of the returned string.

This is an example place where the specification is very tolerant. It's much better to not guuarantee something than to label practically-valuable implementations non-conforming.

So what's the reality then? `https://en.cppreference.com/w/cpp/types/type_info/name <cppreference>`_ says:

- Some implementations (such as MSVC, IBM, Oracle) produce a human-readable type name.
- GCC and Clang, return the `mangled name <https://en.wikipedia.org/wiki/Name_mangling>`_, which is specified by the `Itanium C++ ABI <https://itanium-cxx-abi.github.io/cxx-abi/abi.html#typeid>`_
- The lifetime of the string is tied to the lifetime of RTTI data, which typically lives as long as its originating file (for executables - as long as the program is running, for shared library objects - to the point of unload).

The mangled name can be demangled by:

- GCC's :cch:`abi::__cxa_demangle$$$namespace::func` - see https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html
- :cch:`boost::core::demangle$$$namespace::namespace::func` - see http://www.boost.org/doc/libs/release/libs/core/doc/html/core/demangle.html
- command-line utility: ``c++filt -t mangled_name``, available as a part of GCC and Clang toolchains

RTTI
====

C++ is a language where you don't pay for what you don't use and the existence of the keyword already puts some requirements on implementation - it must provide some metadata in the executable. This metadata is known as RTTI (runtime type information) and compilers offer a ``-fno-rtti`` option. For GCC, the option disallows :cch:`typeid` and RTTI-requiring uses of :cch:`dynamic_cast` (typically downcasts). Exceptions are unaffected (any data to support them is generated as needed). Additionally, GCC documents that *mixing code compiled with ``-frtti`` with that compiled with ``-fno-rtti`` may not work. For example, programs may fail to link if a class compiled with ``-fno-rtti`` is used as a base for a class compiled with ``-frtti``*.

Note that ``-fno-rtti`` apart from reducing binary file size, like many options which limit amount of produced metadata will also reduce the possibility of reverse engineering.

Alternatives
============

RTTI is a costly OOP feature (as far as typical C++ philosophy is concerned). Some frameworks (most notably Qt) generate their own metadata using their own ways.

If you want to use standard-like :cch:`typeid` with a richer API and guuarantees, check `Boost.TypeIndex library <https://www.boost.org/doc/libs/release/doc/html/boost_typeindex.html>`_

:cch:`decltype`
###############

This is the second keyword, it bevahes much differently. Instead of returning an object, it behaves like a type name:

.. cch::
    :code_path: decltype_example_simple.cpp
    :color_path: decltype_example_simple.color

The keyword has 2 usages:

- :cch:`decltype(entity)$$$keyword(spec)`, that is: :cch:`decltype(ref.member)$$$keyword(var_local.var_member)`, :cch:`decltype(ptr->member)$$$keyword(var_local->var_member)` and :cch:`decltype(T::member)$$$keyword(tparam::var_member)` - yields the type of the (member) *entity*, with top-level cv-qualifiers removed
- :cch:`decltype(expression)$$$keyword(spec)` - yields a type depending on value category of the expression:

  - for prvalue, yields :cch:`T`
  - for lvalue, yields :cch:`T&`
  - for xvalue, yields :cch:`T&&`

Because the first point applies only to limited set of expressions, :cch:`decltype(expression)` and :cch:`decltype((expression))` can yield distinct types (first the type of the entity, second the type of the expression).

.. cch::
    :code_path: decltype_example_parenthesis.cpp
    :color_path: decltype_example_parenthesis.color

Like other operator keywords, it has *unevaluated context* (the code is not run) and doesn't impose requirements beyond necessary to process the expression (some types in the expression may be incomplete, abstract or have no destructor).

:cch:`decltype` is used almost exclusively in templates, usually to denote function return type or an alias that would otherwise be impossible or complex to express. In non-template code, the need is usually accompanied by an initialization, thus such code typically uses :cch:`auto`.

Since C++14 both keywords can be combined as a single constituent for type declaration: :cch:`decltype(auto)` for initialization or function return type. In such case instead of template type deduction, the resulting type is :cch:`decltype(expression)` where *expression* is the initializer.

.. cch::
    :code_path: decltype_example_large.cpp
    :color_path: decltype_example_large.color
