// example calling code, somewhere else
std::optional<int> result = safe_divide(x, y);
if (result) // optional is convertible to bool, there is also .has_value()
	// result.value() - returns reference to T if present, otherwise throws an exception (safer)
	// *result        - returns reference to T if present, otherwise undefined behavior (faster)
	use_result(*result);
else
	// some error...
