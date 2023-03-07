/* Exercies 2-9.i In a two's complement number system, "x &= (x-1)" deletes the rightmost 1-bit in x. Explain why. Use the observation to write a faster version of "bitcount". */
/* Explain why. Use the observation to write a faster version of bitcount. */
// Compared to "x", "x - 1" flips all its bits starting at the rightmost 1-bit , therefore if 'x' has the rightmost 1-bit at 6th place (counting from RHS), "x-1" will flip last 6 bits, e.i. 0->1 and 1->0. 
// "&" compare all bits, and preserves 1 only if both operands has 1 at the particular place.

#include <stdio.h>
int main (void) {

	unsigned x = 131072, x2;	
	x2 = x;
	int bits;
	for (x2 = x; x2 > 0; x2 /= 7) {
	/*	
		for (bits = 0, x = x2; x != 0; x >>= 1)
			if (x & 01)
				++bits;
	*/
		
		for  (bits = 0, x = x2; x != 0; x &= (x-1))
				++bits;
	
		printf("There are %d bits set to '1' in %d\n", bits, x2);
	}
}
	
