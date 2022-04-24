class tyre: public product // public inheritance
{
public:
	tyre(int price, int warranty_months, dimentions dims, int diameter)
	: product(price, warranty_months, dims), diameter(diameter) {}
	// ^^^^^^ calling constructor of the base type
	// if it was skipped, product() would be assumed (default 0-argument constructor)

	tyre(product prod, int diameter)
	: product(prod), diameter(diameter) {}

private:
	int diameter;
	// some other tyre-specific data...
};
