/* Exercise 2-10. Rewrite the funcion "lower", which converts upper case letters to lower case, with a conditional expression istead of "if-else". */

#include <stdio.h>

int lower(int);

int main(void) {

	char str1[] = "Redakcje twierdzenNIe i LINi sa podobone";
	printf("%s\n", str1);
	int i;
	for (i = 0; str1[i] != '\0'; ++i)
		str1[i] = lower(str1[i]);
	printf("%s\n", str1);
	return 0;
}

/* lower: convert c to lower case; ASCII only */
int lower(int c) {

	return (c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c);
}


