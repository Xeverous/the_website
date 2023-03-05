const char c =
	  x == 1 ? 'a'
	: x == 2 ? 'b'
	: x == 3 ? 'c'
	: x == 4 ? 'd'
	: x == 5 ? 'e'
	: 'f';

// equivalent else-if code
char c; // can't use const here
     if (x == 1) c = 'a';
else if (x == 2) c = 'b';
else if (x == 3) c = 'c';
else if (x == 4) c = 'd';
else if (x == 5) c = 'e';
else             c = 'f';
