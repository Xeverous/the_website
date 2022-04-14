int x = 1 + 2 + 3 + 4;
int y = ((1 + 2) + 3) + 4; // equivalent
int y = operator+(operator+(operator+(1, 2), 3), 4); // pseudo-code

std::cout << 1 << 2 << 3 << 4;
(((std::cout << 1) << 2) << 3) << 4; // equivalent
operator<<(operator<<(operator<<(operator<<(std::cout, 1), 2), 3), 4); // equivalent
