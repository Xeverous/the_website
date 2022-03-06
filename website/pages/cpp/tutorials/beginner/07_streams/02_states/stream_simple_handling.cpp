#include <iostream>

int main()
{
	double sum = 0;
	int number_count = 0;

	double d;
	while (std::cin >> d) // uses convertion to bool
	{
		// if code gets here it means last I/O operation succeeded
		sum += d;
		++number_count;
	}

	std::cout << "numbers entered: " << number_count << "\n";
	// division by 0 is only undefined behavior on integers
	// but in this case floating-point division by 0 makes no sense
	if (number_count != 0)
		std::cout << "average of entered numbers: " << sum / number_count << "\n";
}
