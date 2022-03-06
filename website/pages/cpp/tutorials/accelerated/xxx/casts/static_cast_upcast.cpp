struct base {};
struct derived : base {};
struct extra_derived : derived, base {};
struct privately_derived : private base {};

extra_derived ed;
static_cast<derived&>(ed);  // well-defined
static_cast<derived*>(&ed); // well-defined

static_cast<base&>(ed);  // error: base is ambiguous
static_cast<base*>(&ed); // error: base is ambiguous

privately_derived pd;
static_cast<base&>(pd);  // error: base is inaccessible
static_cast<base*>(&pd); // error: base is inaccessible
