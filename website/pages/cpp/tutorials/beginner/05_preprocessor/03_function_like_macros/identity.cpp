#define IDENTITY(x) x
IDENTITY(,) // error: 2 arguments (both empty) but macro takes 1
IDENTITY(() // some syntax error
IDENTITY()) // this can work, it's just macro call followed by )
// error: 2 arguments but macro expects 1
// argument 1: std::pair<int
// argument 2: int>
IDENTITY(std::pair<int, int>)
IDENTITY((std::pair<int, int>)) // ok: 1 argument
