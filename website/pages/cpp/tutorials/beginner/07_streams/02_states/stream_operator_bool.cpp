while (std::cin >> value)
{
	// use value...
}

// equivalent code
while (true)
{
	std::cin >> value;

	if (std::cin)
	{
		// use value...
	}
	else
	{
		break;
	}
}
