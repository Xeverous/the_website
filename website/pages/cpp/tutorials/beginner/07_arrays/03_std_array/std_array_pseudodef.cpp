namespace std {

template <typename T, size_t N>
struct array
{
	T arr[N];

	constexpr const T& operator[](size_t n) const { return arr[n]; }
	constexpr       T& operator[](size_t n)       { return arr[n]; }

	constexpr size_t size() const noexcept { return N; }

	// [...] other functions and support for operators such as =, ==, !=
};

}
