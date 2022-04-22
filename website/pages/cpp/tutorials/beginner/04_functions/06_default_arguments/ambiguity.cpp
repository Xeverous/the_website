int f(int);
int f(int, int = 1); // valid, but impossible to call with 1 argument

f(1); // error: ambiguous call
