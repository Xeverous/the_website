int max = MAX(++x, f(y));
// after preprocessing
int max = ++x < f(y) ? f(y) : ++x;
