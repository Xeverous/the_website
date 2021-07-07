// long long is used because factorial results grow very fast
// 32-bit integer can hold max 12!
// 64-bit integer can hold max 20!
long long factorial_iterative(long long n)
{
	long long result = 1;
	while (n > 0)
		result *= n--;

	return result;
}

long long factorial_recursive(long long n)
{
	if (n == 0)
		return 1;
	else
		return n * factorial_recursive(n - 1);
}
