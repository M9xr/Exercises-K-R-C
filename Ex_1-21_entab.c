/* Exercise 1-21. Write a program "entab" that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for "detab".
 * When either a tab or a single blank would suffice to reach a tab stop, which should be givien preference */ 
/* - A singe blank. */

#include <stdio.h>
#define MAXCHAR 1000
#define TABSIZE 8

int xgetline(char line[], int);
void entab(char line[], int size_of_tab);

int main(void) {

	char line[MAXCHAR];
	int len;

	while ((len = xgetline(line, MAXCHAR)) > 0) {
		entab(line, TABSIZE);
		printf("%s", line);	
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

/* entab: replace blanks with the proper amount of tabs */
void entab(char s[], int tab_size) {
	
	int i, nblanks, ntabs, j;
	i = nblanks = j = ntabs = 0;
	while (s[i] != '\0') {
		if (s[i] != ' ') {
			s[j] = s[i];
			++i;
			++j;
		}
		else  {
			while (s[i] == ' ') {
				++nblanks;
				++i;
			}
			if ((ntabs = (nblanks / tab_size)) >= 1) {
			       nblanks = nblanks % tab_size;
			       while (ntabs > 0) {
				       s[j] = '\t';
				       ++j;
				       --ntabs;
			       }
			}
			while (nblanks > 0) {
				s[j] = ' ';
				++j;
				--nblanks;
			}
		}
	}
	s[j] = '\0';      			    
}
			





	
