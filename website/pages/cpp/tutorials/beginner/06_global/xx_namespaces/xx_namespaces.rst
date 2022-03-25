.. title: namespaces
.. slug: index
.. description: namespaces, including inline, anonymous and aliases
.. author: Xeverous

Namespaces are C++ equivalent of filesystem directories. They group entities under same name prefix, but ``::`` is used instead of ``/``.

The primary purpose of namespaces is preventing name conflicts. C++ standard library uses :cch:`namespace std` but there are some inner namespaces too, e.g. :cch:`std::chrono`.

Syntax
######

.. code:: cpp
    namespace foo { void f1(); }

    // namespaces can be opened multiple times, potentially in different files
    namespace foo { void f2(); }

    // namespaces can be nested and entities can appear at any level
    namespace bar {
        void f3();

        namespace foo { // bar::foo is not the same as foo
            void f4();

            namespace baz {
                void f5();
            }

            void f6();
        }
    }

    // definitions of entities can appear in another namespace definition...
    namespace foo { void f1() {} }
    // ...or use qualified name
    void foo::f2() {}

    // inside a namespace, enclosing namespace names can be skipped
    namespace bar {
        void f3() {}
        void foo::f4() {}      // no need to write bar::foo::f4
        void foo::baz::f5() {} // no need to write bar::foo::baz::f5
    }

    // out-of-namespace definitions and redeclarations can not appear
    // in a namespace that does not enclose original declaration
    namespace xyz {
        // error: xyz::bar::foo::f6 does not exist
        // this syntax (qualified-id) can not be used to declare new entities
        // void bar::foo::f6() {}
    }

    // :: can be used before the name to refer to shadowed entity
    void f();
    namespace abc {
        void f()
        {
            ::f(); // ok: calls ::f (not a recursion)
        }
    }

    // it's possible to create namespace aliases
    namespace abc {
        namespace bfb = ::bar::foo::baz;
    }

    void f7()
    {
        abc::bfb::f5();
    }

:cch:`using`
############

The keyword has 4 possible meanings, depending on the context:

- type aliases
- using-declaration, inside classes
- using-declaration, outside classes
- using-directive

This article explains last 2.

Using-declaration
#################

Introduces names from other namespaces to current namespace or block scope (if used inside a function).

.. code:: cpp

    void f();

    namespace abc
    {
        void g1();
        void g2();
    }

    namespace xyz
    {
        using ::f;
        using abc::g1;

        using ::f, abc::g1; // C++17 shorter version
    }

    void h()
    {
        xyz::f();  // calls ::f
        xyz::g1(); // calls abc::g1

        using abc::g2;
        g2(); // calls abc::g2
    }

The declaration introduces all entities with specified name. In particular, the name can refer to a template or to a set of function overloads. The declaration applies only to entities that have already been declared:

.. code:: cpp
    namespace abc
    {
        void f(int);
    }
    using abc::f; // ::f is now a synonym for abc::f(int)

    namespace abc
    {
        void f(char); // does not change what ::f means
    }

    void foo()
    {
        f('a'); // calls f(int), even though f(char) exists.
    }

    void bar()
    {
        using abc::f; // introduces both overloads
        f('a');       // calls f(char)
    }

.. TODO some recommendation? This looks really bad

If using-declaration introduces names from different scopes, ambiguity errors appear only under specific usages. If using-declaration attempts to introduce something that is already in the current scope, it's an error.

.. code:: cpp

    namespace abc
    {
        void f(int);
        void f(double);

        void g(int);
    }

    namespace xyz
    {
        void f(int);
        void f(double);
        void f(char);
    }

    void g();
    // using abc::g; // error: g already in this scope

    // no error even though some overloads are identical
    using abc::f;
    using xyz::f;

    // void f(int); // error: conflicts with abc::f(int) and xyz::f(int)

    void h()
    {
        f('h'); // calls xyz::f(char)
        f(1.0); // error: ambiguity between abc::f(double) and xyz::f(double)
    }

Anonymous namespaces
####################

Formally *unnamed-namespace-definition*.

Syntax sugar
############

.. cch::
    :code_path: syntax_sugar.cpp
    :color_path: syntax_sugar.color

Recommendation
##############

- Avoid name conflicts. You don't need to memorize all ambiguity cases. And I haven't even listed them all.
- Prefer function-local usings to namespace-level usings.
- Prefer usings for specific names like :cch:`using std::cout;` instead of whole-namespace usings like :cch:`using namespace std;`.
- If a conflict would arise, create name/namespace aliases instead to shorten names only (no scope changes) - e.g. :cch:`namespace bc = boost::container;$$$keyword namespace = namespace::namespace;` allows short :cch:`bc::vector$$$namespace::type` which does not conflict with :cch:`std::vector`.
- Avoid :cch:`using namespace` in headers.

Similar recommendations are present in Core Guidelines. Like many other mechanisms in the language, it can be very useful but if abused, it can lead to non-trivial errors and complex situations (especially name shadowing).
