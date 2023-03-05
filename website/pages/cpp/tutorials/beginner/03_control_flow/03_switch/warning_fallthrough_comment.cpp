case 3:
	std::cout << "you entered 3 or a higher number\n";
	// fallthrough
case 2:
	std::cout << "you entered 2 or a higher number\n";
	// fallthrough
case 1:
	std::cout << "you entered 1 or a higher number\n";
	// fallthrough
case 0:
	std::cout << "you entered 0 or a higher number\n";
	break;
default:
	std::cout << "you entered a different number\n";
	break;
