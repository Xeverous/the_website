errno = 0;
int result = safe_divide(x, y);
if (errno == 0)
{
	// use result
}
else
{
	// report error
	// if this function also uses errno, it can just return
}
