catch (const std::exception& e) {
	// [...]

	// BAD: does not rethrow, instead makes a slice and throws only
	// the std::exception subobject of the current exception
	throw e;
}
