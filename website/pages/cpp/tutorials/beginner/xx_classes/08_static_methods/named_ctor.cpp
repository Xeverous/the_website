constexpr double celsius_to_fahrenheit(double celsius)
{
	return 1.8 * celsius + 32;
}

constexpr double fahrenheit_to_celsius(double fahrenheit)
{
	return (fahrenheit - 32) / 1.8;
}

// https://en.wikipedia.org/wiki/Absolute_zero
constexpr double absolute_zero = -273.15;

constexpr double celsius_to_kelvin(double celsius)
{
	return celsius - absolute_zero;
}

constexpr double kelvin_to_celsius(double kelvin)
{
	return kelvin + absolute_zero;
}

class temperature
{
public:
	static temperature from_kelvin(double kelvin)
	{
		return temperature(kelvin);
	}

	static temperature from_celsius(double celsius)
	{
		return from_kelvin(celsius_to_kelvin(celsius));
	}

	static temperature from_fahrenheit(double fahrenheit)
	{
		return from_celsius(fahrenheit_to_celsius(fahrenheit));
	}

	// other methods...

private:
	temperature(double kelvin)
	: kelvin(kelvin) {}

	double kelvin;
};

void some_func()
{
	// now any object creation is very clear
	auto t1 = temperature::from_kelvin(0);
	auto t2 = temperature::from_celsius(100);
}
