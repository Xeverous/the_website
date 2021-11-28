.. title: 03 - const
.. slug: 03_const
.. description: const member function qualifier
.. author: Xeverous

So far we have talked about member functions and how they can shield the class from undesirable use. This lesson extends the topic, covering few very common kinds of member functions.

Setters:

- primary purpose: change data members (they *set* things)
- secure class **invariants**.
- function names usually start with ``set``
- such functions almost always return :cch:`void` (if not, it's usually :cch:`bool` to indicate whether operation succeeded)

Getters:

- primary purpose: obtain information (they *get* things)
- function names usually start with ``get`` (return value of a private data member or compute something from them)
- almost always are read-only operations that do not change data members

Question-like functions (a subset of getters):

- very often return :cch:`bool`
- names usually start with ``is`` or ``has`` - for example: ``is_ready()``, ``is_full()``, ``is_open()``, ``has_completed()``,
- almost always are read-only operations that do not change data members

Action-like functions:

- primary purpose: modify the object to complete specific task
- names are formed like orders - for example: ``next_item()``, ``load_file()``, ``refresh()``
- typically return one of:

  - :cch:`void`
  - :cch:`bool` (to inform if the operation succeeded)
  - specific data type that holds operation result and/or detailed error information

Action-like functions are the most broad group and usually they will contain most important code for any given class.

.. admonition:: definition
    :class: definition

    Getters are commonly referred as **accessors**. Setters as **mutators**.

Getters and setters do not always come in pairs - getters may combine information from multiple members and setters (and action functions) may change multiple fields. This all depends on class invariants.

Exercise
########

Recall fraction class from previous lesson. Can you assign each of its member functions a specific category?

.. TODO spoiler

- ``set`` - setter
- ``simplify`` - action
- ``print`` - getter (although instead of returning it prints the values)

Member function qualifiers
##########################

In C++ member functions can have certain qualifiers:

- :cch:`const`
- :cch:`volatile` (explained in pointers chapter)
- :cch:`&` - the lvalue reference qualifier or :cch:`&&` - the rvalue reference qualifier

In this lesson you will learn about the simplest of them - the const qualifier.

When applied to a variable, :cch:`const` prevents its modification. When applied to a member function, it prevents that function from modifying fields - it's as if all fields were :cch:`const` for the code inside the function. You can still do everything else in such function, the only restriction is on modifying member variables.

The fraction class already has a function that could use it - you probably already know which one.

Const-qualified member functions have 2 important properties:

- they can be called on const-qualified objects
- they can not call non-const-qualified member functions

Let's have an example:

.. TOCOLOR

.. code::

    #include <iostream>

    // (greatest common divisor)
    // if you have C++17, you can remove this function and use std::gcd from <numeric>
    int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        else
            return gcd(b, a % b);
    }

    class fraction
    {
    private:
        int numerator = 0;
        int denominator = 1;

    public:
        void set(int count, int denom)
        {
            numerator = count;

            if (denom == 0)
                denominator = 1;
            else
                denominator = denom;
        }

        void simplify()
        {
            const int n = gcd(numerator, denominator);
            numerator /= n;
            denominator /= n;
        }

        // note where the const keyword is placed
        // "const double approx()" would affect return type, not the function
        double approx() const
        {
            return static_cast<double>(numerator) / denominator;
        }

        void print() const
        {
            std::cout << numerator << "/" << denominator;
        }
    };

    /*
     * Because fraction class is small and inexpensive to copy,
     * it should be passed by value instead of const reference.
     * Const reference is used here to demonstrate potential
     * errors of calling non-const methods on const objects.
     */
    void print_details(const fraction& fr)
    {
        fr.print();
        std::cout << ", approx. " << fr.approx() << "\n";

        // fr.simplify(); // error: can not call non-const member function on const-qualified object
    }

    void test(fraction fr)
    {
        print_details(fr);
        fr.simplify();
        std::cout << "after simplification:\n";
        print_details(fr);
    }

    int main()
    {
        fraction fr;

        fr.set(8, 12);
        test(fr);
        fr.set(8, -12);
        test(fr);
        fr.set(-8, -12);
        test(fr);
    }

It's important to note that const-qualifying a function changes its type. If you would like to form a reference (or a pointer) to such function (references and pointers to member functions are also possible) you need to take it into account. Analogical convertion rules apply - a reference/pointer to a less cv-qualified function can be converted to a reference/pointer to a more cv-qualified function but not vice versa.

.. TODO should the above info be moved elsewhere?

.. admonition:: tip
    :class: tip

    Getters should be const-qualified.

Don't get it wrong - do not const-qualify a function just becase it can be. Think what is the function's purpose and only then add :cch:`const` if it's a getter. Action-like functions should not be const-qualified even if they can (for whatever reason). If you make this mistake, there is a chance that the function implementation will change at some point in a way that prevents applying :cch:`const`. This can cause compilation issues in other code which was (incorrectly) using the class by relying on the action constness.

    Does const-qualifying a function helps in optimization?

Generally no. :cch:`const` does not help the compiler except in few corner cases. It's much more of a help for the programmer to catch bugs related to object misuse.

Overloading on qualification
############################

This style of a pair of getter and setter is very popular in C++ (and often the recommended one):

.. TOCOLOR

.. code::

    class button
    {
    private:
        std::string m_text;
        // [...] other fields

    public:
              std::string& text()       { return m_text; }
        const std::string& text() const { return m_text; }

        // [...] other methods
    };

    // example uses
    button1.text() = "Exit";

    if (button2.text() == button3.text())
        assert(button2.text().length() == button3.text().length());

There are few key things here:

- Member variables are named with some prefix (usually ``m_`` or ``_``):

  - This avoids name clashes with method names.
  - This improves code readability of method implementations (member variables can be easily distinguished from function-local variables).
  - This helps with tooling (e.g. IDE autocomplete feature)

- Both functions are named as nouns, just like fields.
- There are 2 overloads which differ in const qualification and analogically their return type.

Which overload is choosen when a method is called? It depends on the constness of the object on which it is done.

- For const objects, the const-qualified overload is choosen which acts only as a getter.
- For non-const objects, the non-const-qualified overload is choosen which can be used both as a getter and as a setter.

The tradeoffs of this style:

- Such pair of functions exposes an implementation detail - the type of the data member is visible in the function. If the class is later refactored to contain fields of different types, code which was using the class may also need to be changed.
- Since the setter does not take the value as a parameter but returns a reference to a field:

  - ...it no longer can control what is actually written to it. This makes the style undesirable if the class has invariants to enforce.
  - ...the calling code can access field's methods, which allows significant code reuse. Example above did it with string's assignment operator.
