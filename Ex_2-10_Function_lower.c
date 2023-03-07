/* Exercise 2-10. Rewrite the function lower, which converts upper case letters to lwoer case, with a conditional expression instead of if-else. */
#include <stdio.h>

char lower (char c);
int main (void) {
char swinx;
	char c;
	while ((c = getchar()) != EOF) {
		swinx = lower (c);
		printf("%c", swinx); }
	printf("\n\n");
}

char lower (char c) {
	 
	 char a;

	 a = (c >= 'A' && c <= 'Z') ?   ('a' + c - 'A') : c ; 
	 return a;
}

/* THE OLD LOWER */
/* lower: convert c to lower case; ASCII only */
/* int lower (int c) {

	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	else
		return c; 
} */
