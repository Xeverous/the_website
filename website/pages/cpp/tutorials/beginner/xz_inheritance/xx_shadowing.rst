.. title: shadowing
.. slug: shadowing
.. description: shadowing in derived classes
.. author: Xeverous

Just like entities declared in nested scopes *shadow* other entities with the same name, analogical thing happens in derived classes.

Data member shadowing
#####################

.. code:: cpp

    struct base
    {
        int x = 0;
    };

    struct derived : base
    {
        int x = 1; // shadows base::x

        void print() const;
    };

    void derived::print() const
    {
        std::cout << "derived::x: " << x << "\n";
        std::cout << "base::x: " << base::x << "\n";
    }

    int main()
    {
        derived d;
        d.print();
        d.x *= 10;
        d.base::x *= 10;
        d.print();
    }

Obviously you should avoid such name conflicts, but sometimes you will have no control over external code. It's no so rare that the base class comes from a different project. Many libraries and frameworks expect their users to use inheritance to implement specific things.

Overload shadowing
##################

Shadowing also applies to function overloads. By default, functions with the same name will be hidden in derived type.

.. code:: cpp

    class image;

    class text_button
    {
    public:
        void set_content(std::string /* text */) { /* ... */ }

    // [...]
    };

    class image_text_button : public text_button
    {
    public:
        // expected: add another overload
        // actual: hides all base type overloads
        void set_content(const image& /* img */) { /* ... */ }
    };

    void func(const image& img)
    {
        image_text_button btn;
        btn.set_content(img);      // ok
        btn.set_content("cancel"); // error: argument type mismatch
    }

This surprising "feature" may have some niche uses but more often than not such behavior is unwanted. Imagine a situation where a base type overload accepts :cch:`int` and derived type overload accepts :cch:`long`. Because both are integers and promotion is an implicit convertion, a lot of code can match both overloads. Minor details like changing how you refer to the object (reference to base or derived type) will affect which overload is choosen, silently breaking existing code without any warning.

The actually desirable behavior (calling specific function implementation based on *dynamic type* of the object) are :cch:`virtual` functions which are explained later.

The problem can be solved by using using-declarations inside class definition.

Using-declarations inside classes
#################################

Classes aren't namespaces but using-declarations can be used to manipulate access level and overload resolution.

Function and data members
=========================

The declaration has 2 effects:

- it redefines access level to the entity
- for functions, it merges overloads that aren't exactly the same into one set

.. code:: cpp

    class base
    {
    public:
        void f(int);
        void g(int);

    protected:
        int m = 0;
    };

    class derived : public base
    {
    public:
        // derived::m is public
        // if base::m was private, this would be rejected
        // (derived can not redefine access if it itself has no access)
        using base::m;

        using base::f;
        void f(long); // does not hide base::f, now there are 2 overloads

        using base::g;
        void g(int); // hides base::g because this overload is identical
    };

    void func()
    {
        derived d;
        d.m = 2; // ok
        base& b = d;
        b.m = 1; // error: base::m is protected

        d.f(1);  // ok, calls base::f
        d.f(1l); // ok, calls derived::f

        d.g(1); // ok, calls derived::g
        d.base::g(1); // ok, calls base::g
        b.g(1); // ok, calls base::g
    }

Redefining access is against OOP principles and again, I haven't heard of this ability in other languages. I guess the only reasonable use would be to allow access to specific member functions from types derived in non-public way.

Merging overload sets into one is fine, this actually brings behavior to the expectation that derived types extend the base type, not overwrite it.

.. admonition:: tip
  :class: tip

  When adding function overloads in derived classes, write a using declaration so that overloads form one set instead of hiding base class overloads (in case of multiple levels of inheritance, this action has to be repated in every class along the hierarchy that adds new overloads).

Constructors
============

.. TODO explain "direct base"

Using-declarations can also be used for direct base constructors. In such case the current class works as if it had identical constructor overloads and just forwarded everything to the base type. This can save some boilerplate code when a new class doesn't have any additional initialization requirements.

.. code:: cpp

    class base
    {
    public:
        base(int x, int y, int z);
        base(double v);
    };

    class derived : public base
    {
    public:
        // works like
        // derived(int x, int y, int z) : base(x, y, z) {}
        // derived(double v) : base(v) {}
        using base::base;

    private:
        std::string str; // will use string's default constructor
        int n = 0;       // has explicitly specified initializer
    };

In this specific case of using-declarations, access specifiers are ignored. Accessibility level of each overload is copied from the base type.

There are more nuances and corner cases than described here, see https://en.cppreference.com/w/cpp/language/using_declaration#Inheriting_constructors for additional examples.
