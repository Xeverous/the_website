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
