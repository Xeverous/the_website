#define TO_FAHRENHEIT(celsius) 1.8 * celcius + 32

double temp = TO_FAHRENHEIT(20 + 80);

// what was meant
double temp = 1.8 * 100 + 32;
// what preprocessor generated
double temp = 1.8 * 20 + 80 + 32;
