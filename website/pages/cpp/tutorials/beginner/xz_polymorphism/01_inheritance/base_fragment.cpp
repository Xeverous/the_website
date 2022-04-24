struct dimentions
{
	int width_cm;
	int length_cm;
	int height_cm;
};

class product
{
public:
	product(int price, int warranty_months, dimentions dims)
	: price(price), warranty_months(warranty_months), dimentions(dims)
	{
		// some checks (e.g. negative values not accepted)
	}

	// some methods...

private:
	int price;
	int warranty_months;
	dimentions dims;
};
