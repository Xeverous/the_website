class temperature
{
public:
	temperature(double value)
	: value(value) {}

	// other methods...

private:
	double value;
};

void some_func()
{
	// What unit is this?
	// Celsius? Fahrenheit? Kelvin?
	temperature t = 0.0;
}
