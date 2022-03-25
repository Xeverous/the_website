// C++17 - defining multiple levels with one keyword and one {}
namespace na { namespace nb { namespace nc { /* ... */ }}}
namespace na::nb::nc { /* ... */ } // no prior appearance of na and na::nb is required

// C++20 - additionally supports inline
namespace nd::ne { inline namespace nf { /* ... */ } }
namespace nd::ne::inline nf { /* ... */ }

namespace ng { inline namespace nh { namespace ni { /* ... */ }}}
namespace ng::inline nh::ni { /* ... */ }
