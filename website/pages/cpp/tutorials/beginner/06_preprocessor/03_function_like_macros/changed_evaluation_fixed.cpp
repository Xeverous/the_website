// fully guarded against other operators
#define TO_FAHRENHEIT(celsius) (1.8 * (celsius) + 32)
// now, after preprocessing
double temp = (1.8 * (20 + 80) + 32);
