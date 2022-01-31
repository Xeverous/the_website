namespace std {

template <typename T, std::size_t N>
struct array
{
	T arr[N];

	constexpr const T& operator[](std::size_t n) const { return arr[n]; }
	constexpr       T& operator[](std::size_t n)       { return arr[n]; }

	// lots of other code,
	// mostly functions and support for other operators such as =, ==, !=
	// [...]
};

}
