/* Exercise 2-7. Write a function invert (x,p,n) that returns x with the n bits that begin at postion p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. */


#include <stdio.h>

int invert (unsigned int x, int p, int n);

int main(void) {
	
	unsigned int x, xx1;
	int p, n, x2, xx2;
	x = 147, p = 3, n = 2;
	
	x2 = invert (x, p, n);
	printf("\n x --> 1 0 0 1 0 0 1 1\nx2 --> 1 0 0 1 0 1 0 1\n");
	printf("x1: %d\t\tx2: %d\n", x, x2);
	
	xx1 = 1224;
	p = 8;
	n = 3;
	xx2 = invert(xx1, p, n);
	printf("x1: %d\tx2: %d\n", xx1, xx2);

	return 0;
}

/* invert: invert n bits in x, beginning from the position p */
int invert (unsigned int x, int p, int n) {

	if (n > p)
		return -1;
	return (x ^ (~(~0 << n) << (p-n)));



}
	





