/* Exercise 4-7. Write a routine "ungets (s)" that will push back an entire string onto the input. Should "ungets" know about "buf" and "bufp", or should it just use "ungetch"? */
// Answer: just use "ungetch"

#include <stdio.h>
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch (void);
void ungetch (int c);
void ungets (char s[]);

int main () {

	printf("size:%d\n", bufp);
	int i, g;
	char b[100];
	char s[] = "Not Cool Exercise!";
	ungets (s);

	printf("size:%d\n", bufp);

		


}

int getch (void) {

	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch (int c) {

	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void ungets (char s[]) {

	int i, c;

	for (i = c = 0; s[i] != '\0'; ++i) {
		c = (s[i] - '0');
		ungetch (c);
	}
	ungetch ('\0');
}

		


