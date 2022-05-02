void copy(const int* input, int* output, int size)
{
	for (int i = 0; i < size; ++i)
		output[i] = input[i];
}

void reverse(int* arr, int size)
{
	const int n = size / 2;
	for (int i = 0; i < n; ++i)
	{
		int temp = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = temp;

		// the loop body could also be this
		// std::swap(arr[i], arr[size - i - 1]);
	}
}

bool compare(const int* lhs_arr, int lhs_size, const int* rhs_arr, int rhs_size)
{
	// if sizes are different, there is no point in going further
	if (lhs_size != rhs_size)
		return false;

	// now we can use just 1 variable for counting as both sizes must be the same
	for (int i = 0; i < lhs_size; ++i)
		if (lhs_arr[i] != rhs_arr[i])
			return false;

	return true;
}
