if (bargain_percent >= 100)
	price = 0; // set price to 0 when bargain exceeds 100%
else
	price = price - price * bargain_percent / 100;
