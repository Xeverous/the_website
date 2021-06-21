 'a'          // char, ASCII encoding (compatible with UTF-8)
u'貓'         // char16_t, UTF-16, supports only BMP part of Unicode
U'🍌'         // char32_t, UTF-32, supports any Unicode character
U'\U0001f34c' // same as line above, value written as hex
L'β'          // wchar_t, encoding and value implementation-defined

// introduced in C++17, char
// breaking change in C++20: now it has type char8_t
u8'a'         // UTF-8, single byte characters from ISO 10646

// these forms are not really used
// compilers often give a warning about such code because
// multiple characters within '' are usually a typo
 'abc' // int, value implementation-defined
L'abc' // wchar_t, value implementation-defined
