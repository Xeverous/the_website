int numerator() const
{
	return m_numerator;
}

void numerator(int value)
{
	m_numerator = value;
}

int denominator() const
{
	return m_denominator;
}

void denominator(int value)
{
	m_denominator = make_valid_denominator(value);
}
