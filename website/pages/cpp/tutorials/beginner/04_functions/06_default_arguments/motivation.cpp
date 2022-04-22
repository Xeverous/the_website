void start_timer(long precision, long delay) // A
{
	// [...]
}

void start_timer(long precision) // B
{
	start_timer(precision, 0); // calls overload A
}

void start_timer() // C
{
	start_timer(1000); // calls overload B
}
