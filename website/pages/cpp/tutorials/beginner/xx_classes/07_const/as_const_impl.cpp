#include <type_traits>

template <typename T> constexpr
typename std::add_const<T>::type& as_const(T& t) noexcept
{
	return t;
}

template <typename T>
void as_const(const T&&) = delete; // disallows temporary objects
