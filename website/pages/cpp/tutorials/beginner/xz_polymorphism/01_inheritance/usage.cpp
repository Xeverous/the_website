int calculate_bargain_percent(const product& p);

void f(const tyre& t)
{
	// composition - obtain a member
	int bargain_percent = calculate_bargain_percent(t.get_product());

	// inheritance - tyre is implicitly convertible to product
	// this specific convertion is referred to as "upcast"
	int bargain_percent = calculate_bargain_percent(t);
}
