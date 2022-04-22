void draw_rectangle(int width, int height = width); // ill-formed

void draw_rectangle(int width, int height);
void draw_rectangle(int width)
{
	draw_rectangle(width, width); // ok
}
