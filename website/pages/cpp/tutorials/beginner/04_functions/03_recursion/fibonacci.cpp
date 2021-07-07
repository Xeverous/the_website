int fibonacci_iterative(int n)
{
	int a = 0;
	int b = 1;

	for (int i = 0; i < n; ++i)
	{
		int temp = b;
		b = a + b;
		a = temp;
	}

	return a;
}

int fibonacci_recursive(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return fibonacci_recursive(n - 2) + fibonacci_recursive(n - 1);
}
