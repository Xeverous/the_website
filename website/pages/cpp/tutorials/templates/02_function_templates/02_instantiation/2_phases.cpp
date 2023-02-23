template <typename T>
void f(T t)
{
	static_assert(sizeof(T) == 0);
	nonexistent_function(t); // also dependent on T
}
