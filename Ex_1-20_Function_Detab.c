/* Exercise 1-20. Write a program "detab" that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. 
 * Should n be a variable or a symbolic parameter? */
// N should be a variable because it keeps functions generality for using in other programs. Also, programs that use the functions with variables are easier to modify. 

#include <stdio.h>
#define MAXCHAR 1000
#define TABSIZE 6

int xgetline(char line[], int);
void detab(char line[], char line2[], int size_of_tab);

int main(void) {

	char line[MAXCHAR];
	char line2[MAXCHAR*TABSIZE];
	int len;

	while ((len = xgetline(line, MAXCHAR)) > 0) {
		detab(line, line2, TABSIZE);
		printf("%s", line2);	
	}
	printf("\n");
	return 0;
}
int xgetline (char s[], int lim) {

	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* detab: replace tab with the proper amount of spaces */
void detab(char s[], char s2[], int tab_size) {
	
	int i, j, k;

	i = j = 0;
	while (s[i] != '\0') {
		if (s[i] != '\t')
			s2[j++] = s[i++];
		else {
			for (k = tab_size; k > 0; --k)
				s2[j++] = ' ';
			i++;
		}
	}
	s2[j] = '\0';

}
			





	
