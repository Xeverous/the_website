.. title: 09 - user defined literals
.. slug: 09_user_defined_literals
.. description: user defined literals
.. author: Xeverous

C++ offers multiple suffixes for literals:

.. TOCOLOR

.. code::

    3.14f // float
    1ul   // unsigned long

    // prefix, not suffix
    U'貓' // char32_t

...and it's possilble to define new literal suffixes too.

    How about user-defined prefixes?

There is no such thing but character literals and string literals can have both prefixes and suffixes.

Syntax
######

User-defined literals are defined by overloading :cch:`operator""` (free function only), where the suffix immediately follows ``""``.

.. TOCOLOR

.. code::

    class celcius { /* ... */ };

    constexpr celcius operator""_C(long double x)
    {
        return celcius(x);
    }

    // example use
    constexpr auto human_body_temperature = 36.6_C; // auto deduced to celcius

To avoid confusion and conflicts with the standard library suffixes, suffixes must begin with ``_``. Literal suffixes have significant parsing priority which:

- cause suffixes not to be replaced by macros
- allows suffixes to use names which would normally be keywords
- allows suffixes to use reserved names (so suffixes like ``_Hz`` and ``_Pa`` are allowed)

There should not be any space between :cch:`operator` keyword and the suffix:

.. TOCOLOR

.. code::

    kelvin operator""_K(long double x);  // ok: literal suffix _K
    kelvin operator"" _K(long double x); // undefined behavior: use of reserved identifier

Paramaters
##########

Because it's not possible to combine language built-in suffixes with user-defined ones in the same literal, it has been decided that overloads of :cch:`operator""` must take arguments of the largest possible type of that literal.

These are all allowed paramater sets:

.. TOCOLOR

.. code::

    (unsigned long long) // integer literals
    (long double) // floating point literals
    // fallbacks if the number does not fit into overloads above
    // source code characters are passed instead
    (const char*) // ...as a pointer to character array
    template <char...>
    /* ... */ () // ...as non-type template arguments

    // character literals
    (char)
    (wchar_t)
    (char8_t) // C++20
    (char16_t)
    (char32_t)

    // string literals
    (const char*, std::size_t)
    (const wchar_t*, std::size_t)
    (const char8_t*, std::size_t) // C++20
    (const char16_t*, std::size_t)
    (const char32_t*, std::size_t)
    // C++20 alternative (string literal must be well-formed template argument for ClassType)
    template <ClassType>
    /* ... */ ()

Default arguments in :cch:`operator""` overloads are not allowed.

In standard library
###################

.. admonition:: note
    :class: note

    The feature is since C++11 but first standard library suffixes appeared in C++14.

Standard library literals have their own namespaces. They are not exposed in :cch:`std` namespace to avoid name conflicts (there are two ``s`` suffixes: one for  :cch:`std::chrono::seconds` and one for :cch:`std::string`). A specific namespace must be used in order to access them.

.. TOCOLOR

.. code::

    #include <iostream>
    #include <complex>
    #include <chrono>
    #include <string_view>

    int main()
    {
        { // C++14
            using namespace std::complex_literals;
            auto c = 1.0f + 1.0if; // float(1.0) + std::complex<float>(0.0, 1.0)
            std::cout << "abs" << c << " = " << std::abs(c) << '\n';
        }

        { // C++14
            using namespace std::chrono_literals;
            auto lesson = 45min;   // std::chrono::minutes, uses integers
            auto halfmin = 0.5min; // std::chrono::minutes, uses floating-point
            std::cout << "one lesson is " << lesson.count() << " minutes\n"
                      << "half a minute is " << halfmin.count() << " minutes\n";
        }

        { // C++17
            using namespace std::string_view_literals;
            std::string_view s1 = "abc\0\0def"; // ctor that takes (const char*) - terminates on first null character
            std::string_view s2 = "abc\0\0def"sv; // literal that takes (const char*, std::size_t)
            std::cout << "s1: " << s1.size() << " \"" << s1 << "\"\n";
            std::cout << "s2: " << s2.size() << " \"" << s2 << "\"\n";
        }

        { // C++20
            using namespace std::chrono_literals;
            auto date = 1970y/1/1; // overloaded operator/ for year type and integers
            const auto now = std::chrono::system_clock::now();
            const auto today = std::chrono::year_month_day(std::chrono::sys_days(now));
            int leap_years = 0;
            while (date.year() <= today.year())
            {
                if (date.year().is_leap())
                    ++leap_years;
                date += std::chrono::years(1);
            }
            std::cout << "There have been " << leap_years << " leap years since the beginning of UNIX time.\n";
        }
    }

.. code::

    abs(1,1) = 1.41421
    one lesson is 45 minutes
    half a minute is 0.5 minutes
    s1: 3 "abc"
    s2: 8 "abc^@^@def"
    There have been 13 leap years since the beginning of UNIX time.

Corner cases
############

.. TOCOLOR

.. code::

    // string literal concatenation + prefixes + suffixes
    L"A" "B" "C"_x;  // OK: same as L"ABC"_x
    "P"_x "Q" "R"_y; // error: two different suffixes _x and _y
    "P"_y "Q" "R"_y; // OK: same as "PQR"_y

    // maximal munch: use longest sequence of characters that could constitute a
    // preprocessing token, even if that would cause subsequent analysis to fail
    auto x = 1.0_E+2.0;   // error: invalid literal 1.0_E+2.0
    auto y = 1.0_a+2.0;   // OK (a does not form exponential notations)
    auto z = 1.0_E +2.0;  // OK
    auto q = (1.0_E)+2.0; // OK
    auto w = 1_p+2;       // error: invalid literal 1_p+2
    auto u = 1_p +2;      // OK

    auto a = 4_km.as_miles(); // error: no suffix _km.as_miles
    auto b = 4_km .as_miles(); // ok
    auto c = (4_km).as_miles(); // ok

Recommendation
##############

User-defined suffixes are mostly useful for classes representing specific physical units. Such strongly-typed code can prevent lots of bugs related convertion and incorrect treatment of units.
