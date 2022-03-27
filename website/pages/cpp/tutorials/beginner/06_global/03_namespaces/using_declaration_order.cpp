namespace abc
{
	void f(int);
}
using abc::f; // ::f is now a synonym for abc::f(int)

namespace abc
{
	void f(char); // does not change what ::f means
}

void foo()
{
	f('a'); // calls f(int), even though f(char) exists.
}

void bar()
{
	using abc::f; // introduces both overloads
	f('a');       // calls f(char)
}
