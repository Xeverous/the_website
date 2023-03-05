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
