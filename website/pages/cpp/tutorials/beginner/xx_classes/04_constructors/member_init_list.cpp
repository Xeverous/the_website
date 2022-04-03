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
	// the syntax is :member1(init1), member2(init2), member3(init3)
	// many like to format it this way to align : and ,
	fraction(int numerator, int denominator)
	: numerator(numerator)
	, denominator(make_valid_denominator(denominator))
	{}

	// [...]
};
