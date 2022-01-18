template <typename T, std::size_t N>
constexpr std::size_t size(const T (&)[N]) noexcept
{
	return N;
}
