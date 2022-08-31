namespace std {

// A special smart pointer type capable of referencing an exception object.
// Can not be used as or converted to a raw pointer, but special
// standard library functions accept exception_ptr as an argument.
class exception_ptr {
public:
	// creates empty exception_ptr
	exception_ptr() noexcept;
	// the class is copyable, copies work like std::shared_ptr
	exception_ptr(const exception_ptr& other) noexcept;

	// check if non-empty
	explicit operator bool() const noexcept;

private:
	/* compiler magic */
};

bool operator==(const exception_ptr& lhs, const exception_ptr& rhs) noexcept;
bool operator!=(const exception_ptr& lhs, const exception_ptr& rhs) noexcept;

// Return a smart pointer to the current exception
// - if no exception is propagating, returns empty exception_ptr
// - otherwise stops propagation and returns non-empty exception_ptr
// - in case of problems (e.g. no memory) may return non-empty
//   exception_ptr to std::bad_alloc or std::bad_exception
exception_ptr current_exception() noexcept;

// Throw a given object and make exception_ptr for it.
// The parameter is passed by value and thus may be sliced
// (make sure you have the local object, not a reference to its base).
template <typename E>
exception_ptr make_exception_ptr(E e) noexcept
{
	// This isn't the actual implementation, but it works as such.
	try {
		throw e;
	} catch (...) {
		return current_exception();
	}
}

// p must not be empty, otherwise undefined behavior.
// The exception object may be copied for implementation reasons.
[[noreturn]] void rethrow_exception(exception_ptr p);

// ... even more obscure functionality, listed on
// https://en.cppreference.com/w/cpp/header/exception
}
