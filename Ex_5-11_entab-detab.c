/* Exercise 5-11. Modify the program "entab" and "detab" (written as exercises in Chapter 1) to accept a list of tab stop as arguments.
 * Use the default tab settings if there are no arguments. */

#include <stdio.h>

#define XTAB 5
#define MAXCHAR 1000

int main (int argc, char *argv[]) {

	char string1[MAXCHAR];
	int nchar = 0, i, c, linechar = 0;

	while ((c = getchar()) != EOF && nchar < MAXCHAR - 1) {
	       if (c == '\t') {
		       for (i = 0; i < XTAB; ++i) {
			       string1[nchar++] = ' ';
			       ++linechar;
		       }
	       }
	       else if (c == '\n'){
		       if (linechar > 0) {
		       		string1[nchar++] = c;
		      	 	linechar = 0;
		       }
		       else {
			       string1[nchar++] = c;
			       c = EOF;
			       break;
		       }
	       }
	       else {
		       string1[nchar++] = c;
		       ++linechar;
	       }
	}
	string1[nchar] = '\0';
	printf("%s\n", string1);

	return 0;
}




