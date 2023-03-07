/* Exercise 3-5. Write the function itob (n,s,b) that converts the integer n into a base b character representation in the string s. In particular, itob (n,s,16) formats s as a hexadecimal integer in s. */
#include <stdio.h>

#define MAXCHAR 100
void itob (int n, char s[], int b);

int main (void) {

	int num, base;
	char str[MAXCHAR];
	num = 9190;
	base = 19;
	printf("TEST1");
	itob (num, str, base);
	return 0;
}

void itob (int num, char s[MAXCHAR], int base) {

	int power, i, c, xbase;
	xbase = base -1;
	power = 0;
	for (i = 0; i < MAXCHAR; ++i) {
		s[i] = 0; }
	while (num != 0) {
		while ((num /xbase) >= 1) {
			xbase = xbase * base;
			++power; 
			printf("[pwer %d xbase %d", power, xbase);}
		++i;
		s[power-1] = base;
		num = num - (xbase / base);
		xbase = power = 0;
		if (num < base) {
			s[0] = num;
			num = 0; }
	}
	s[i] = '\0';
	printf("%s\n", s);

}
	


