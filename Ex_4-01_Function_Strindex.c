/* Exercise 4-1. Write the function "strindex (s,t)" which return the position of the righmost occurence of t in s, or -1 if there is none. */

#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int xgetline (char line[], int max);
int strindex (char source[], char searchfor[]);

char pattern[] = "ould";	/* pattern to search for */

/* find all lines matching pattern */
int main () {

	char line[MAXLINE];
	int found = 0;

	while (xgetline (line, MAXLINE) > 0){
		 found = strindex (line, pattern);
		  if (found > 0) {
			printf("%s", line);
			printf("found:%d\n", found);
		}
	}
	return found;
}

/* xgetline: get line into s, return length */
int xgetline (char s[], int lim) {

	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* strindex: return index of t in s, -1 if none */
int strindex (char s[], char t[]) {

	int i, j, k;
	for (i = 0; s[i] != '\0'; i++) {
		for (k = 0; t[k] != '\0' && s[i] == t[k]; i++, k++) {
			//printf("Found!:%c\tk=%d\ti=%d\n", s[i], k, i);
			if (t[k] == '\0') {
			       --i; }
		}	
	}
	if (k > 0 && t[k] == '\0')
		return i-k;
	else
		return -1;
}
	

