// bad
namespace lib {}
inline namespace lib {} // error: inline namespace must be specified at initial definition

// good
inline namespace lib {}
inline namespace lib {}

// also good
inline namespace lib {}
namespace lib {}
