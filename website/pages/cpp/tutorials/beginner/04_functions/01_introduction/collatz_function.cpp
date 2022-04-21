long long collatz_next_number(long long n)
{
	if (n % 2 == 0)
		return n / 2;
	else
		return 3 * n + 1;
}
