/* Exercise 5-3. Write a pointer version of the function "strcat" that we showed in Chapter 2: "strcat (s,t)" copies the string "t" to the end of "s". */

#include <stdio.h>
#define MAXCHAR 250

void xstrcat (char *, char *s);

int main (void) {

	char s1[MAXCHAR] = "A good asian is...\n";
	char s2[MAXCHAR] = "a dead asian\n";

	xstrcat (s1,s2);
	printf("%s", s1);	
	return 0;
}

/* xstrcat: concatenate t to end of s; s must be big enought */
void xstrcat (char *s, char *t) {

	while (*++s != '\0')
		;
	while (*s++ = *t++)
		;
}
