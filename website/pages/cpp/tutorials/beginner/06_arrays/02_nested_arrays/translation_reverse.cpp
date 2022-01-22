// 2D
x = index % size_x;
y = index / size_x;

// 3D
x = index % size_x;
y = index % (size_x * size_y) / size_x;
z = index / (size_x * size_y);
