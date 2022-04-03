// A: 3 overloads with member init list

fraction()
: numerator(0)
, denominator(1)
{}

fraction(int numerator)
: numerator(numerator)
, denominator(1)
{}

fraction(int numerator, int denominator)
: numerator(numerator)
, denominator(make_valid_denominator(denominator))
{}

// B: 3 overloads, 2 overloads use delegation

fraction()
: fraction(0, 1)
{}

fraction(int numerator)
: fraction(numerator, 1)
{}

fraction(int numerator, int denominator)
: numerator(numerator)
, denominator(make_valid_denominator(denominator))
{}

// C: 1 overload using default parameters

fraction(int numerator = 0, int denominator = 1)
: numerator(numerator)
, denominator(make_valid_denominator(denominator))
{}
