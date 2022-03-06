// comment virtual dtor in base - compile error: types are not polymorphic
// comment virtual inheritance - compile error: ambiguous base
struct base { virtual ~base() = default; };
struct left : virtual base {};
struct right : virtual base {};
struct derived : left, right {};

derived d;

// downcasts
base& br = d;
derived& dr = dynamic_cast<derived&>(br);
derived* dp = dynamic_cast<derived*>(&br);

// sidecasts
left& lr = d;
right& rr = dynamic_cast<right&>(lr);
right* rp = dynamic_cast<right*>(&lr);

// cast to void* (results in a pointer to most derived object)
auto vp = dynamic_cast<void*>(&br);
