// C
void qsort(
	void* ptr,
	size_t count,
	size_t size,
	int (*comp)(const void*, const void*));

// C++
template <typename RandomAccessIterator, typename BinaryPredicate>
constexpr void std::sort(
	RandomAccessIterator first,
	RandomAccessIterator last,
	BinaryPredicate func);
