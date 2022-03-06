struct base {};
struct derived : base {};
struct virtually_derived : virtual base {};

derived d;
base& br = d;
static_cast<derived&>(br);  // well-defined
static_cast<derived*>(&br); // well-defined

base b;
static_cast<derived&>(b);  // undefined behavior
static_cast<derived*>(&b); // undefined behavior

static_cast<virtually_derived&>(br);  // error: virtual inheritance is present
static_cast<virtually_derived*>(&br); // error: virtual inheritance is present
