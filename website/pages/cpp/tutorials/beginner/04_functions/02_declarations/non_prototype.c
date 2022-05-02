// before C89 this was all that was possible
// formal name: non-prototype function declaration

// return type: void
// name: f
// parameters: UNSPECIFIED
void f();
// return type: void
// name: g
// parameters: UNSPECIFIED
void g();

// new syntax added in C89

// return type: void
// name: f
// parameters (1): int
void f(int x);
// return type: void
// name: g
// parameters (0)
void g(void);

// before C89: both function calls are well-defined
// but will cause undefined behavior at runtime
// C89: both function calls are ill-formed
// compile time error (argument type/amount mismatch)
f(3.14);
g(3.14);
