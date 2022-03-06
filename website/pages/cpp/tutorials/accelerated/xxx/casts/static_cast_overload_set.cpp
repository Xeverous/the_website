template <typename F, typename... Args>
auto invoke(F f, Args&&... args);

void f(int, int);
void f(double, double);

invoke(f, 1, 2); // error: can not deduce F
invoke(static_cast<void(&)(int, int)>(f), 1, 2); // ok
