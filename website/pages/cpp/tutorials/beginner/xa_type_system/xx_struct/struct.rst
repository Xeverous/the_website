.. title: ?? - struct
.. slug: index
.. description: structure types
.. author: Xeverous

.. TOCOLOR all examples in this article
.. TODO explain why not to use typedef struct approach from C
.. TODO explain unnamed structs: struct {} object;
.. TODO explain how a struct can solve f(true, false, true, true) problem

It's quite common to have a few closely related variables. The :cch:`struct` keyword allows you to define a new type that consists of multiple objects.

.. code:: cpp

    struct point // the name of the type
    {
        // members
        int x;
        int y;
    }; // don't forget ; when defining types

Entities defined inside are called *members*. Here the :cch:`point$$$type` type has 2 *data members*. Later you will learn about *member functions* and *member types*. Members are accessed through ``.``.

This code alone doesn't create any objects. :cch:`point.x$$$type.var_member` is not a valid expression. First you need to create an object of this type:

.. code:: cpp

    point p1; // right here x and y are still uninitialized
    p1.x = 2;
    p1.y = 3;

    // aggregate initialization
    point p2{-3, 5};

    // copy initialization
    point p3 = p2;

    // assignment operator (by default applies assignment to each data member)
    p1 = p2;

You can specify default values for members. If the object is not explicitly initialized, it will use initializers specified in the type definition.

.. code:: cpp

    #include <iostream>

    struct point
    {
        int x = 0;
        int y = 0;
    };

    int main()
    {
        point p1;
        point p2{2, 2};

        std::cout << "p1 = (" << p1.x << ", " << p1.y << ")\n"
            << "p2 = (" << p2.x << ", " << p2.y << ")\n";
    }

If the initializers were not specified in the type definition, reading their values before assignment would be undefined behavior. Thus, **it's recommended to always initialze members**.

The example above contains small code duplication. We can fix it by writing a function:

.. code:: cpp

    void print(const char* name, point p)
    {
        std::cout << name << " = (" << p.x << ", " << p.y << ")\n";
    }

.. put the function into a spoiler and also spoiler full example?

Nested structures
#################

It's possible to nest structures. This is known as **composition** and is one of the primary ways of reusing code to build larger programs.

.. code:: cpp

    #include <iostream>

    struct triangle
    {
        point p1;
        point p2;
        point p3;
    };

    struct circle
    {
        // initializers already specified inside
        point origin;
        // built-in types need initializers
        int radius = 0;
    };

    void print(const char* name, point p)
    {
        std::cout << name << " = (" << p.x << ", " << p.y << ")\n";
    }

    void print(const char* name, triangle t)
    {
        std::cout << name << " = {\n";
        print("p1", t.p1);
        print("p2", t.p2);
        print("p3", t.p3);
        std::cout << "}\n";
    }

    int main()
    {
        triangle t1;
        t1.p1.x = 1;
        t1.p1.y = 2;
        t1.p2.x = -2;
        t1.p2.y = -1;
        t1.p3.x = 3;
        t1.p3.y = 3;

        // equivalent
        triangle t2{{1, 2}, {-2, -1}, {3, 3}};

        print("t1", t1);
        print("t2", t2);
    }

..

    I don't like the fact that in the second overload of :cch:`print$$$func` the code mixes function calls with :cch:`std::cout`. Is it possible to make :cch:`std::cout << p$$$namespace::var_global << var_local` work?

Yes. The specific feature that supports it is known as *operator overloading*. You can overload operators (they work just like functions with few restrictions) for *user-defined types* (built-in types already have behavior specified). I'm not going to delve into details as the topic is described in it's own chapter but for the sake of example:

.. code:: cpp

    // std::cout is a global object of type std::ostream
    std::ostream& operator<<(std::ostream& stream, point p)
    {
        return stream << "(" << p.x << ", " << p.y << ")\n";
    }

More syntax
###########

Unary operators when combined with member access are written like this: :cch:`++t1.p3.y$$$++var_local.var_member.var_member`.
