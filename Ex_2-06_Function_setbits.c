/* Exercise 2-6. Write a function "setbits(x,p,n,y)" that returns 'x' with the 'n' bits that begin at position 'p' set to the rightmost 'n' bits of 'y', leaving the other bits unchanged */
/* Return 'x' with the 'n' bits, beginning at positiong 'p', set to the rightmost 'n' bits of 'y', leaving other bits unchanged */ 
#include <stdio.h>

int setbits(unsigned int x, int p, int n, unsigned int y);

int main(void) {

	unsigned int x, y;
	int p, n;
	x = 64;
	y = 8;
	p = 3;
	n = 4;
	int val1, val2, val3, val4, val5, val6;
	val1 = setbits(x, p, n, y);
	val2 = setbits(1, 11, 1, 1);
	val3 = setbits(0, 11, 1, 1);
	val4 = setbits(288, 2, 1, 1); 
	printf("x:%d\tx2:%d\tval3:%d\tval4:%d\n", val1, val2, val3, val4);
	return 0;

}

/* setbits: return 'x' with the 'n' bits, beginning at 'p', set at the rightmost 'n' of 'y' */
int setbits (unsigned int x, int p, int n, unsigned int y) {
	
	return (x & ~((~(~0 << n)) << p)) | (((~(~0 << n)) & y) << p - n);	
	
}




