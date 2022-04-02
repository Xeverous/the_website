// header
class fraction
{
public:
	int numerator;
	int denominator;

	void simplify();
	void print();
};

// source
// notice that member function definitions use class_name::
// this informs the compiler about access to members
void fraction::simplify()
{
	const int n = gcd(numerator, denominator);
	numerator /= n;
	denominator /= n;
}

void fraction::print()
{
	std::cout << numerator << "/" << denominator << "\n";
}
