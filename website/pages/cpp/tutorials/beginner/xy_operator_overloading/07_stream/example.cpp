std::stringstream ss("1/2 3/4"); // requires <sstream>
fraction fr1;
fraction fr2;
ss >> fr1 >> fr2;
std::cout << fr1 << " " << fr2;
