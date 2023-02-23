// good: T is deduced and U can be specified first
template <typename U, typename T>
U convert_to1(T value)
{
	return static_cast<U>(value);
}

// also good, just different (swapped) names of template parameters
template <typename T, typename U>
T convert_to2(U value)
{
	return static_cast<T>(value);
}

// bad: T will be deduced but U has to be specified second
// any call will have to specify both to reach U
//
// error: U not specified and can not be deduced
// convert_to3<int>(1)
//
// will work, but verbose and duplicate work
// (int is both deduced and specified explicitly)
// convert_to3<int, double>(1)
template <typename T, typename U>
U convert_to3(T value)
{
	return static_cast<U>(value);
}
