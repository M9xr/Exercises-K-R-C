/* Exercise 3-5. Write the function "itob (n,s,b)" that converts the integer "n" into a base "b" character representation in the string "s". In particular, "itob (n,s,16)" formats 
"s" as a hexadecimal integer in "s". */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 1000
#define BASE_MIN 2
#define BASE_MAX 36

void itob (int n, char s[], int b);
void reverse (char s[]);

int main (void) {

	int n, base;
	int g = 213124;
	char s[MAXCHAR];
	for (base = 2; base <= 36; ++base) {
		itob (g, s, base);
		printf("For base:%d, the value of %d is %s\n", base, g, s);
	}
	printf("\n");
	return 0;
}

void itob (int n, char s[], int b) {

	int i, j, c;

	if (b < BASE_MIN || b > BASE_MAX) {
		printf("Valid base ranges from %d to %d.\n", BASE_MIN, BASE_MAX);
		exit (1);
	}
	j = 0;
	if (n == 0)
		s[j++] = '0';
	for (i = n; i > 0; i /= b) {
		if ((c = i % b) <= 9 )
			s[j++] = c + '0';
		else
			s[j++] = c - 10 + 'A';
	}
	s[j++] = '\0';
	reverse (s);

}

void reverse (char s[]) {

	int c, i, j;
	for (i = 0, j = strlen (s) - 1; i < j; i++,  j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
