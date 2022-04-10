// all inside class body

fraction& operator++() // prefix increment
{
	m_numerator += m_denominator;
	return *this;
}

fraction& operator--() // prefix decrement
{
	m_numerator -= m_denominator;
	return *this;
}

fraction operator++(int) // postfix increment
{
	fraction old = *this; // copy old value
	operator++(); // reuse prefix; you can also write ++(*this);
	return old;
}

fraction operator--(int) // postfix decrement
{
	fraction old = *this;
	operator--();
	return old;
}
