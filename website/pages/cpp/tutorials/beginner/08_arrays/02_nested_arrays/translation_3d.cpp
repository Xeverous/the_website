int index_3d_to_1d(int z, int y, int x, int size_y, int size_x)
{
	return size_y * size_x * z + size_x * y + x;
}
