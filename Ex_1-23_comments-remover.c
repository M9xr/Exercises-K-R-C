/* Exercise 1-23. Write a program to remove all comments from a C program. Don't forget to handle quoted strings and character constants properly. C comments don't nest. */

#include <stdio.h>

#define MAXCHARS 30000
#define MAXCHAR 1000

void rmcomments(char s[]);
int xgetline(char s[], int lim);
void cat_strings(char s[], char t[]);

int main(void) {

	char buffer[MAXCHARS];
	char line[MAXCHAR];
	int len;

	while ((len = xgetline(line, MAXCHAR)) > 0)
		cat_strings(buffer, line);
	printf("\n");
	rmcomments(buffer);
	printf("%s", buffer);
	return 0;
}

/* rmcomments: remove all comments form a C program */
void rmcomments(char s[]) {

	int i, j, cond;
	i = j = cond = 0;
	
	while (s[i] != '\0') {
		if (s[i] == '/') {
			++i;
			if (s[i] == '/')
				while (s[i] != '\n')
					++i;
			else if (s[i] == '*') {
				cond = 1;
				while (cond != 0) {
					++i;
					if (s[i] == '*') {
						++i;
						if (s[i] == '/') {
							++i;
							cond = 0;
						}
					}
				}
			}
			else {
				s[j] = s[i-1];
				++j;
			}
		}
		else {
			if (j != i)
				s[j] = s[i];
			++i;
			++j;
		}
	}
	s[j] = '\0';
}


/* xgeltine: get a line into string s, return length of the line */
int xgetline(char s[], int lim) {

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

/* cat_strings: concatenate t to end of s; s must be big enough */
void cat_strings(char s[], char t[]) {

        int i, j;

        i = j = 0;
        while (s[i] != '\0')    /* find end of s */
                i++;
        while ((s[i++] = t[j++]) != '\0') /* copy t */
                ;
}

