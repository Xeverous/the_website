for (int i = 0; i < n; ++i)
{
	// C: well-defined (name shadowing)
	// C++: ill-formed (redefinition of i)
	long i = 1;
}
