/* Exercise 1-19. Write a function reverse(s) that reverses the character string s. Use it to write a program that reverses its input a line at a time. */

#include <stdio.h>

#define MAXCHAR 238
void reverse (char s[]);

int main (void) {
	
	char s[MAXCHAR];
	int i, c;
	for (i = 0; (c = getchar()) != EOF; ++i) {
		s[i] = c;
		if (c == '\n') {
			s[++i] = '\0';
			reverse(s);
			printf("%s", s);
			i = 0;
		}
	}
	if (s[i - 1] != '\n')
		s[i++] == '\n';
	s[i] = '\0';	
	reverse(s);
	printf("%s", s);
	return 0;
}

void reverse (char s[MAXCHAR]) {
	
	int i, j;
	char temp;

	for (i = 0; s[i] != '\0' && s[i] != '\n'; ++i)
		;
	--i;
	for (j = 0; j < i; --i, ++j) {
		temp = s[j];
		s[j] = s[i];
		s[i] = temp;
	}
}



	
