switch (x)
{
	case 1:
		int y = 0; // initialization
		std::cout << y << '\n';
		break;
	default:
		// compilation error: jump to default would
		// enter the scope of y without initializing it
		std::cout << "default\n";
		break;
}
