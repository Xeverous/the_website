#include <iostream>
#include <limits>

int main()
{
	double sum = 0;
	int number_count = 0;

	while (true)
	{
		double d;
		if (std::cin >> d)
		{
			// if code gets here it means I/O operation succeeded
			sum += d;
			++number_count;
		}

		if (std::cin.bad())
		{
			std::cout << "unrecoverable error\n";
			break;
		}

		// it's quite common to have both eof and fail bits set together
		// in such case it's better to handle eof first and just stop I/O
		if (std::cin.eof())
		{
			std::cout << "end of input, proceeding with calculations\n";
			break;
		}

		if (std::cin.fail())
		{
			std::cout << "input failed, try again\n";
			std::cin.clear();
			// ignore all characters in the stream or until line break is encountered
			// without this line, the same invalid input would be tried endlessly
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	std::cout << "numbers entered: " << number_count << "\n";
	if (number_count != 0)
		std::cout << "average of entered numbers: " << sum / number_count << "\n";
}
