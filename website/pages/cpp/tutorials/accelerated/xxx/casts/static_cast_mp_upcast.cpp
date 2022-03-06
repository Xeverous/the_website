struct base {};
struct derived : base { int m = 42; };

derived d;
int derived::* d_pm = &derived::m;
auto b_pm = static_cast<int base::*>(d_pm); // well-defined
d.*b_pm; // well-defined

base b;
b.*b_pm; // undefined behavior (the runtime object has no such member)
