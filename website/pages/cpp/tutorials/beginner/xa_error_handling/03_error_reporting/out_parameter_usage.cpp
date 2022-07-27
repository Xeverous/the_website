bool success = false;
// because the last parameter is taken by non-const reference,
// something like safe_divide(x, y, true) will not compile
int result = safe_divide(x, y, success);
if (success)
{
	// use result
}
else
{
	// report error
}
