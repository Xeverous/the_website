// () are necessary because ?: has normally lower priority than <<
std::cout << "x is " << (x % 2 == 0 ? "even" : "odd") << "\n";
