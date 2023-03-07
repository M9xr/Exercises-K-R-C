/* Exercise 2-8. Write a function "rightrot(x,n)" that returns the value of the integer 'x' rotated to the right by 'n' positions. */

#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main(void) {

	int v1, v2, v3;

	v1 = rightrot(2, 7);
	v2 = rightrot(1, 3);
	v3 = rightrot(16, 11);
	printf("v1:%d\tv2:%d\tv3:%d\n", v1, v2, v3);
	return 0;
}

/* rightrot: rightmost n bits go to the left side, x is adjusted to the right by n */
unsigned rightrot(unsigned x, int n) {

	unsigned i;
	int bits;
	i = 0;
	i = ~i;
	for (bits = 0; i > 0; i >>= 1) {
		++bits;
	}

	if (n > bits)
		n = bits;

	return (x << n) | (x >> (bits - n));
}


