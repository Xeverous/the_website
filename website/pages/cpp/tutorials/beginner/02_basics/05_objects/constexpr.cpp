constexpr long cppstd = __cplusplus; // this magic macro is a number in the form "YYYYMM"
constexpr long year = cppstd / 100;  // remove MM part
std::cout << "Year of the used C++ standard: " << year << "\n";
