#include <iostream>

void run()
{
	static int x = 0;
	std::cout << "x is now " << ++x << "\n";
}

int main()
{
	for (int i = 0; i < 5; ++i)
		run();
}
