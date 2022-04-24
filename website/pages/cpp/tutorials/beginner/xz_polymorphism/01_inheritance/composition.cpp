class tyre
{
public:
	tyre(product prod, int diameter)
	: prod(prod), diameter(diameter) {}

	      product& get_product()       { return prod; }
	const product& get_product() const { return prod; }

private:
	product prod;
	int diameter;
	// some other tyre-specific data...
};
