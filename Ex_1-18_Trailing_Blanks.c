/* Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines */
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAXCHAR 1000
int main (void) {

	int c, i, blank, charx;
	char s[MAXCHAR];
	
	for (i = 0; i < MAXCHAR; ++i)
		s[i] = 0;

	blank = charx = FALSE;
	for (i = 0; i < MAXCHAR && (c = getchar()) != EOF; i++) {
		//printf(" %d ", i);
		if ((c == ' ' || c == '\t') && blank == FALSE) {
			s[i] = c;
			blank = TRUE; }
		else if ((c == ' ' || c == '\t') && blank == TRUE) {
			i--; }
		else if ((c == '\n') && charx == TRUE) {
		       s[i] = c;
		       blank = charx = FALSE; }
		else if ((c == '\n') && charx == FALSE) {
			i--; }
		else {
			s[i] = c;
			blank = FALSE;
	       		charx = TRUE;} 
		}
		s[i] = '\0';

	printf("%s\n", s);
	return 0;
}	       

