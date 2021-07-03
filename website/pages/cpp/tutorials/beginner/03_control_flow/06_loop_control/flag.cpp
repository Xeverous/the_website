bool exit = false;
for (int y = 0; y < size_y; ++y)
{
	if (exit)
		break;

	for (int x = 0; x < size_x; ++x)
	{
		if (/* ... */)
		{
			exit = true;
			break;
		}
	}
}
