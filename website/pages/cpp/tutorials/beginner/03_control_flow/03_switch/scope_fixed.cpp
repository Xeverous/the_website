switch (x)
{
	case 1:
	{
		int y = 0; // initialization
		std::cout << y << '\n';
		break;
	} // y dies here
	default: // braces not necessary here but use them for consistency
	{
		std::cout << "default\n";
		break;
	}
}
