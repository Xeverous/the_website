void fd(double);
void fb(bool);
fraction fr(1, 2);

double d1 = fr; // error if "explicit" is used
double d2 = static_cast<double>(fr); // ok
fd(fr); // error if "explicit" is used
fd(static_cast<double>(fr)); // ok

bool is_non_zero1 = fr; // error if "explicit" is used
bool is_non_zero2 = static_cast<bool>(fr); // ok
fb(fr); // error if "explicit" is used
fb(static_cast<bool>(fr)); // ok

// always ok, "if" acts as an explicit convertion to bool
if (fr) {}

// C++ <= 98: ok even if only operator bool is overloaded (convertion is implicit)
// C++ >= 11: ok even if only explicit operator bool is overloaded (! applies contextual convertion)
if (!fr) {}
