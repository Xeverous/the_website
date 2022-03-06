// max value depends on range of type int
enum class fixed : int { one = 1, two, three, last = 30 };
// max value = 31 (30 requires bit-field of 5 bits, which has range [0, 31])
enum class not_fixed { one = 1, two, three, last = 30 };

auto e1 = static_cast<fixed>(31);     // well-defined
auto e2 = static_cast<fixed>(50);     // well-defined
auto e3 = static_cast<not_fixed>(31); // well-defined
auto e4 = static_cast<not_fixed>(50); // undefined behavior
