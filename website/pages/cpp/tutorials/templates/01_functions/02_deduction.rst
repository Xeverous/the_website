.. title: 02 - deduction
.. slug: 02_deduction
.. description: C++ function templates - deduction
.. author: Xeverous

The need for information
########################

When a template is about to be instantiated, the compiler must know what to substitute template parameters with. There are 3 ways to provide this information:

- explicitly specifying template parameters
- template argument deduction
- defaults for template parameters (covered later)

All of these can be combined. In case of overlap, the priority is the same as listed above.

.. admonition:: note
    :class: note

    Deduction is a feature only for function templates. Other kinds of templates do not deduce.

How deduction works
###################

Template parameters are deduced using the same rules as the :cch:`auto` keyword. For each function argument, the template parameter is deduced separately. If an ambiguity arises for some template parameters or if deduction can not find matching type, deduction fails.

.. TOCOLOR
.. TODO find a more real example for deductions

.. code::

    template <typename T, typename U>
    void f(T t1, T t2, U u) { /* ??? */ }

    template <typename T>
    void print_vector(const std::vector<T>& v)
    {
        for (const T& value : v)
            std::cout << value << ", ";

        std::cout << "\n";
    }

    int main()
    {
        f(1, 2, 3); // ok: T deduced as int, U deduced as int
        f(1, 2, 3.0); // ok: T deduces as int, U deduced as double
        f(1, 2.0, 3); // error: argument 1 deduced T as int, argument 2 deduced T as double
        f<double>(1, 2.0, 3); ok: T explicitly specified to double, U deduced as int
        f<double, double>(1, 2.0, 3); ok: T explicitly specified to double, U explicitly specified as double

        print_vector(1.5); // error: parameter 1 can not deduce matching T
    }

..

  Can I specify second template parameter without specifying the first?

No. But note that template parameters do not need to have the same order as the function arguments:

.. TODO need a realistic example

???
###

If you have played enough with minimum function, you might have found this problem:

.. TOCOLOR

.. code::

    #include <iostream>

    template <typename T>
    const T& min(const T& x, const T& y)
    {
        if (y < x)
            return y;
        else
            return x;
    }

    int main()
    {
        // error: argument 1 deduced T as char[7], argument 2 deduced T as char[5]
        std::cout << min("foobar", "abcd");
    }

If const reference is removed (so parameters are passed by value) compilation succeeds because pass-by-value applies decay (in this case converting arrays into pointers). But the program then can print ``foobar``! It can print ``abcd`` too! **Actually, it can do anything since such program contains undefined behavior!**

The problem is that in pass-by-value scenario, :cch:`T` is deduced to :cch:`const char*` so the function actually compares pointers. Comparison other than equality of pointers that do not belong to the same array is undefined. The program can print both answers, depending where both strings are in memory. It can also crash because UB is UB, so there is a chance that the compiler's optimization mechanisms somehow break machine code due to assumptions of things that should never happen.

The root of the problem is that we tried to use comparison operators with character arrays (or character pointers). We don't want that - we want lexicographical comparison for strings. The solution is simple - explicitly specify template parameters:

.. TOCOLOR

.. code::

    std::cout << min<std::string>("foobar", "abcd");
    std::cout << min<std::string_view>("foobar", "abcd"); // C++17

Parameterless function templates
################################

Since they have no parameters, deduction is not possible. But you can still use explicit specification:

.. TOCOLOR

.. code::

    #include <iostream>

    template <typename T>
    void print_sizeof_alignof()
    {
        std::cout << "size: " << sizeof(T) << ", alignment: " << alignof(T) << "\n";
    }

    int main()
    {
        print_sizeof_alignof<int>();
        print_sizeof_alignof<double>();
        print_sizeof_alignof<decltype(std::cout)>();
    }
