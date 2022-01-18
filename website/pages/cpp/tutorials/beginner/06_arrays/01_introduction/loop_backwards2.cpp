// start with sz (which is out of bounds)
// but decrement i after each comparison, not after each iteration
// this loop will also work on signed types
for (std::size_t i = sz; i-- > 0;)
