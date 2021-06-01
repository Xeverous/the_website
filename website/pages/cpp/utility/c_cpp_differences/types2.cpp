struct foo { int x; };
typedef struct foo foo;
void func1(foo* f);

enum some_enum { e1, e2 };
typedef enum some_enum some_enum;
void func2(some_enum e);
