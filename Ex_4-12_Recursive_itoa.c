/* Exercise 4-12. Adapt the ideas of printd to write a recursive version of "itoa"; that is, convert an integer into a string by calling a recursive routine */

#include <stdio.h>
#include <string.h>

void itoa (int n, char s[]);
int main (void) {

	int c, i;
	char s[100];
	
	c = -38419;
	itoa (c, s);
	printf("%s\n", s);

	return 0;
}

/* itoa: convert n to characters in s */
void itoa (int n, char s[]) {
	
	static int i = 0, num = 0;
	num++;

	if (n < 0) {
		s[i++] = '-';
		n = -n;
	}
		
	if (n / 10) 
		itoa (n / 10, s);
	s[i++] = n % 10 + '0';
	if (num == 0) {
		s[i] = '\0';
		i = 0;
	}
}

