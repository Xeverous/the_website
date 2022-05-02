// ok
enum class e1 : char { a, b, c, d };
// error: value -1 outside range of unsigned char
enum class e2 : unsigned char { a, b, c, x = -1 };
// error: float is not an integral type
enum class e3 : float { a, b, c, d };
