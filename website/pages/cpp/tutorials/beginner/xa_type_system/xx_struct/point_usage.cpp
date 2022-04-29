point p1; // right here x and y are still uninitialized
// members are accessed through "."
p1.x = 2;
p1.y = 3;

// aggregate initialization
point p2{-3, 5};

// copy initialization
point p3 = p2;

// assignment operator (by default applies assignment to each data member)
p1 = p2;
