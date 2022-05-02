int x = 2;
int xx = x * x;

#define MACRO() x
int y = MACRO()x; // treated as "int y = x x;" - syntax error
