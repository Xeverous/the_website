#define CONCAT_IMPL(x, y) x ## y // spaces here are not a problem
#define CONCAT(x, y) CONCAT_IMPL(x, y)

int y = CONCAT(x, x); // ok: int y = xx;
