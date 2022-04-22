void func1(int a,     int b,     int c = 10); // ok
void func2(int a,     int b = 5, int c = 10); // ok
void func3(int a = 0, int b = 5, int c = 10); // ok
void func4(int a = 0, int b,     int c);      // ill-formed
void func5(int a = 0, int b = 5, int c);      // ill-formed
void func6(int a = 0, int b,     int c = 10); // ill-formed
