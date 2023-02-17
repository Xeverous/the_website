class fraction
{
public:
	// [...]

	// BAD: fields are assigned
	// If field definitions have no default initializers,
	// they are uninitialized until assigned!
	fraction(int num, int denom)
	{
		// both statements are assignments, not initialization
		numerator = num;
		denominator = make_valid_denominator(denom);
	}

	// GOOD: fields are initialized
	// the syntax is : followed by comma-separated list of members
	// members can be initialized using () and {}
	// the formatting below aligns : and ,
	fraction(int numerator, int denominator)
	: numerator(numerator)
	, denominator(make_valid_denominator(denominator))
	{}

	// [...]
};
