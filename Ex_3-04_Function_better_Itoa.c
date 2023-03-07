/* Exercise 3-4. In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of n equal to -(2*wordsize-1*). Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs. */
/* It is because char cannot handle numbers as big as int can and int cannot handle the biggest numbers for which long int is capable. */
#include <stdio.h>
#include <string.h>

void reverse (unsigned char s[]);
void itoa (long int n, unsigned char s[]);

int main (void) {

	long int c, i;
	char s[100];
	
	c = -91999999999;
	printf("%ld\n", c);
	itoa (c, s);
	printf("%s\n", s);	
	return 0;
}

/* itoa: convert n to characters in s */
void itoa (long int n, unsigned char s[100]) {

	int i, sign;

	if ((sign = n) < 0)	/* record sign */
		n = -n;		/* make n positive */
	i = 0;
	do {	/* generate digits in reverse order */
		s[i++] = n % 10 + '0';	/* get next digit */
		printf("%ld\t ", n);
	} while ((n /= 10) > 0);	/* delte it */
	printf("\n");
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse (s);
}

void reverse (unsigned char s[]) {
	
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
