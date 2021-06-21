if (bargain_percent >= 100)
	price = 0; // prevent price reduction below 0
else
	price = price - price * bargain_percent / 100;
