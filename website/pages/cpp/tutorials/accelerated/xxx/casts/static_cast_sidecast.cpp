struct base {};
struct left : base {};
struct right : base {};
struct derived : left, right {};

derived d;
left& l = d;
static_cast<right&>(l); // error: invalid cast

// Valid, but actually performs reinterpret_cast.
// Would perform static_cast if such was valid
// (another reason not to use old casts, changes
// in inheritance can cause undefined behavior).
(right&) l;
