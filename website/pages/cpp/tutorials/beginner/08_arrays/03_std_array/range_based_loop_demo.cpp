double c_arr[5] = {0.1, 0.2, 0.3, 0.4, 0.5};

for (double& d : c_arr)
	d *= 2;
// expanded
{
	auto&& __range = c_arr; // auto = double(&)[5] (reference to C-array)
	auto __begin = c_arr;   // auto = double* (decays array to pointer)
	auto __end = c_arr + 5; // auto = double* (also decays and shifts the pointer to point further in memory)
	for (; __begin != __end; ++__begin) {
		double& d = *__begin;
		d *= 2;
	}
}

std::array<double, 5> std_arr = {0.1, 0.2, 0.3, 0.4, 0.5};

for (double& d : std_arr)
	d *= 2;
// expanded
{
	auto&& __range = std_arr;       // auto = std::array<double, 5>&
	auto __begin = std_arr.begin(); // auto = std::array<double, 5>::iterator
	auto __end = std_arr.end()      // auto = std::array<double, 5>::iterator
	for (; __begin != __end; ++__begin) {
		double& d = *__begin;
		d *= 2;
	}
}
