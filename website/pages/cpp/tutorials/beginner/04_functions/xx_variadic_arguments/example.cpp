#include <cstdio>

int main()
{
	int x = 0xdeadbeef;
	long l = 6 * 142857;
	float f = 1.f / 7;
	std::printf("x = %x\nl = %ld\nf = %f\n", x, l, f);
}
