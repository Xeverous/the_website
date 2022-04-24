// definitions outside classes should not use any of virtual, override and final
void more_derived::f(double arg)
{
	// code wants to use implementation from some parent class
	base::f(arg); // this function call is non-virtual
}
