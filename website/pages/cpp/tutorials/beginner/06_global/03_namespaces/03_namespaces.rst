.. title: 03 - namespaces
.. slug: index
.. description: namespaces and usings, including: aliases, inline and anonymous
.. author: Xeverous

.. some notes about order of sections in this lesson:
.. - anonymous namespaces are after using-directive because they work similarly (as if the namespace had unique name and followed by using namespace)
.. - inline namespace are are after using-directive because they have special interaction with them (finely-grained usings)

Namespaces are C++ equivalent of filesystem directories. They group entities under same name prefix, but ``::`` is used instead of ``/``.

The primary purpose of namespaces is grouping related entities and preventing name conflicts. C++ standard library uses :cch:`namespace std` but there are some inner namespaces too, e.g. :cch:`std::chrono`.

Syntax
######

.. cch::
    :code_path: syntax.cpp
    :color_path: syntax.color

:cch:`using`
############

The keyword has 4 possible meanings, depending on the context:

- type aliases
- using-declaration, inside classes (changes overloading rules in *derived* types)
- using-declaration, outside classes (shortens names)
- using-directive (shortens names)

This article explains last 2.

Using-declaration
#################

Introduces names from other namespaces to current namespace or block scope (if used inside a function).

.. cch::
    :code_path: using_declaration.cpp
    :color_path: using_declaration.color

The declaration introduces all entities with specified name. In particular, the name can refer to a template or to a set of function overloads. The declaration applies only to entities that have already been declared:

.. cch::
    :code_path: using_declaration_order.cpp
    :color_path: using_declaration_order.color

:cch:`using namespace` does not have this behavior - for it the order of declarations is irrelevant (all names will be affected, not only ones defined before).

.. TODO some recommendation? This looks really bad

If using-declaration introduces names from different scopes, ambiguity errors appear only under specific usages. If using-declaration attempts to introduce something that is already in the current scope, it's an error.

.. cch::
    :code_path: using_declaration_ambiguity.cpp
    :color_path: using_declaration_ambiguity.color

Using-directive
###############

Similar to *using-declaration*, but introduces all names from specified namespace to the current scope.

.. cch::
    :code_path: using_directive.cpp
    :color_path: using_directive.color

:cch:`using namespace std;`
===========================

Shortly speaking, one of the most overused statements in C++. There is so much to say about it that **I wrote a separate article about it**. TOLINK

:cch:`using enum`
#################

Since C++20 it's also possile to bring enumerator names into enclosing scope.

.. cch::
    :code_path: using_enum.cpp
    :color_path: using_enum.color

Anonymous namespaces
####################

Formally *unnamed-namespace-definition* but the "anonymous" term is very popular in the community. Works as if the namespace has some unique name and is immediately followed by :cch:`using namespace`. Can also be mentally understood as "not actually enclosing entities in any namespace".

**Everything defined inside anonymous namespaces has internal linkage.** This includes named namespaces inside. The purpose of this feature is to further reduce name conflicts, but specifically across TUs. You should put there all things that are not being used outside of current source file and do not need to be visible to other TUs.

.. cch::
    :code_path: anonymous_namespace.cpp
    :color_path: anonymous_namespace.color


You might notice that the same functionality was already presented with :cch:`static` - anonymous namespaces should be preferred. Why? See these:

- https://stackoverflow.com/questions/154469/unnamed-anonymous-namespaces-vs-static-functions
- https://stackoverflow.com/questions/4977252/why-an-unnamed-namespace-is-a-superior-alternative-to-static

.. admonition:: tip
   :class: tip

   Do not use anonymous namespaces or :cch:`static` entities - basically any way of specifyng *internal linkage* in header files. They are specifically for code that is intended to not be shared and headers are specifically to do the opposite.

Inline namespaces
#################

Inline namespaces work similarly to anonymous namespaces - names are available in enclosing namespace, as if there was a :cch:`using namespace` directive after it's definition. There are no changes in linkage though.

.. cch::
    :code_path: inline_namespace_example.cpp
    :color_path: inline_namespace_example.color

.. admonition:: note
  :class: note

  :cch:`inline namespace` must be specified at the first definition. Any later definition can skip the keyword :cch:`inline`.

  .. cch::
      :code_path: inline_namespace_definition.cpp
      :color_path: inline_namespace_definition.color

  Because order of includes can change (and potentially break code which skips the keyword), my recommendation is to never skip :cch:`inline`. This will also make the code more consistent and less surprising for any readers.

This feature has 2 purposes.

Finely-grained usings
=====================

Names are available in enclosing scopes, without having to specify their inline namespace name. But using directives can be more selective. Below is an example with standard library *user-defined literals*.

.. cch::
    :code_path: inline_namespace_std_udl.cpp
    :color_path: inline_namespace_std_udl.color

Versioning support
==================

Users of a library can refer to specific names or use a default one if automatic behavior updates are desired.

.. cch::
    :code_path: inline_namespace_versioning.cpp
    :color_path: inline_namespace_versioning.color

.. it's a huge failure that in 2022 reST is not capable of nesting inline markup
.. I have to use 2 replacements to make a bold link
.. https://stackoverflow.com/a/4836544/4818802

Apart from being able to select a specific version or use a default, there is one additional important functionality: **inline namespaces affect** |name mangling|_. What are benefits of this? Suppose a such situation:

- the programmer compiles library version 1
- the programmer writes some code that uses the library and compiles it
- the programmer updates the library and compiles version 2
- library-using-code is not recompiled and only the compiled library object (e.g. ``.so`` or ``.dll`` file) is replaced

This can result in undefined behavior due to ODR violations. The library-using-code was compiled with version 1 definitions, but actually linked with version 2. The executable can crash because there can be mismatches between expected and actual size/alignment of structures and many other machine-instruction-level details:

.. cch::
    :code_path: abi_breakage.cpp
    :color_path: abi_breakage.color

Such situation is known as **ABI mismatch** or **ABI breakage**. ABI stands for *application binary interface*. It's different from **API** (*application programming interface*) - API pertains to compatibility at the source code level, ABI pertains to compatibility at binary (compiled code) level.

.. admonition:: note
  :class: note

  It's possible to make an API-breaking change that does not break the ABI and also to make an ABI-breaking change that does not break the API. The latter is dangerous because the build can succeed and contain undefined behavior due to ODR violations.

.. admonition:: note
  :class: note

  Sometimes no code changes are needed to break the ABI. Some compiler options can affect it too!

.. admonition:: note
  :class: note

  C++ does not specify ABI at all so it's completely *implementation-defined* what affects it and what changes are ABI-breaking. Many implementations (especially for non-Windows platforms) adhere to `Itanium C++ ABI <https://itanium-cxx-abi.github.io/cxx-abi/>`_.

.. admonition:: note
  :class: note

  Some libraries commit to maintaining stable ABI. This means that you do not have to recompile library-using-code if the library is updated and rebuilt as no machine-instruction-level incompatibilities are introduced. The benefit of this approach is that you don't have to constantly recompile your code upon library update (this is especially useful for system package updates on GNU/Linux distributions); the drawback is that such practice limits possible changes in code and/or requires indirection techniques like *PIMPL* to support it.

If inline namespaces are used (and changed every time an ABI-breaking change is introduced) such problem can be detected at linking step because compiled entities will have different symbol names - inline namespaces will be present in *mangled names*.

Using inline namespaces in such case is superior to preprocessor-based solutions because inline namespaces allow providing different definitions for different versions in the same build. If there are disjoint parts of code that use different versions, there are no problems - since these parts don't interact they have no conflicts. As if they used different entities.

As of C++20, the standard library officially does not use inline namespaces for this functionality, but some implementations use it internally - Clang's libc++ uses :cch:`inline namespace __1$$$keyword keyword namespace`. This will help detect ODR violations if compiled code is mixed across versions with different implementations.

Syntax sugar
############

.. cch::
    :code_path: syntax_sugar.cpp
    :color_path: syntax_sugar.color

Recommendation
##############

- Size of a namespace: no consensus in the community. Some libraries put almost everything in a first-level namespace (like 1000+ names) (:cch:`std` is a very good example), others do many layers with <100 names per namespace. Core Guidelines: as of writing this, namespace size is under to-do section.
- Avoid name conflicts. You won't need to memorize what happens when ambiguities appear. And I haven't even listed all possible cases.
- Prefer function-local usings to namespace-level usings.
- Prefer usings for specific names like :cch:`using std::cout;` instead of whole-namespace usings like :cch:`using namespace std;`.
- If a conflict would arise, create name or namespace aliases instead to shorten names only (no scope changes) - e.g. :cch:`namespace bc = boost::container;$$$keyword namespace = namespace::namespace;` allows short :cch:`bc::vector$$$namespace::type` which does not conflict with :cch:`std::vector`.
- Avoid :cch:`using namespace` in headers. It can hijack code that (potentially transitively) accidentally includes a header with this directive.

Similar recommendations are present in Core Guidelines. Like many other mechanisms in the language, it can be very useful but if abused, it can lead to non-trivial errors and complex situations (especially name shadowing).

.. _name mangling: https://en.wikipedia.org/wiki/Name_mangling
.. |name mangling| replace:: **name mangling**
