void func()
{
	class foo { /* can not have static data members */ }; // (1)
}

class
{
	/* can not have static data members */ // (2)

	class bar { /* can not have static data members */ }; // (3)
} object;
