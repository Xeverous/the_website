int f1(int x, int y = 0); // ok

// error: parameter not allowed as default argument
// int f2(int x, int y = x);

template <typename T, typename U = int> // ok
U g1(T x, T y);

template <typename T, typename U = T> // also ok!
U g2(T x, T y);
