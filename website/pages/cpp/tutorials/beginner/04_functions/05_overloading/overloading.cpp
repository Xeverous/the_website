// ok: all overloads have different amount of arguments
int func1(int);
int func1(int, int);
int func1(int, int, int);

// ok: all overloads have different argument types
int func2(int);
int func2(float);
int func2(double);

// also ok
int func3(int, float);
int func3(int);
int func3(double);
int func3(char);

// error: can not overload only by different return type
int func4();
void func4();

// ok: different amount of arguments
int func5();
void func5(int);

// top-level const/volatile are ignored
// ok but these all declare the same overload 3 times
void func6(int);
void func6(const int);
void func6(volatile int);

// ok: different argument types
// (references do not have top-level cv-qualifiers)
void func7(int*);
void func7(int&);
void func7(int&&);
void func7(const int&);
void func7(const int&&);

// error: can not overload only by different exception specification
// (exceptions explained later)
void func8();
void func8() noexcept;
