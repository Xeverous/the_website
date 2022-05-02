// since C++11
template <typename T>
struct underlying_type
{
	using type = /* compiler magic */;
};

// since C++14 (short alias)
template <typename T>
using underlying_type_t = typename underlying_type<T>::type;

// since C++23 available as std::to_underlying in <utility>
// here a C++11-compatible implementation
// with this function you can write to_underlying(some_enum_value)
// which is much shorter than static_cast with a type trait
template <typename Enum>
constexpr typename underlying_type<Enum>::type to_underlying(Enum e) noexcept
{
	return static_cast<typename underlying_type<Enum>::type>(e);
}
