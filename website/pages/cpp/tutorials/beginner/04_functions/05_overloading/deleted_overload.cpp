void f1(long);
f1(1); // ok, int promoted to long

void f2(int) = delete;
void f2(long);
f2(2); // chooses first overload, triggers compilation error
