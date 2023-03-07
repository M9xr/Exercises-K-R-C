/* Exercise 5-13. Write the program "tail", which prints the last n lines of its input. 
 * By default, n is set to 10, let us say, but it can be change by an optiona argument so that "tail -n" prints the last n lines.
 * The program should behave rationally no matter how unresonable the input or the value of n. 
 * Write the program so it makes the best use of avaiable storage; lines should be stored as in the sorting program of Section 5.6, not in a two dimensional array of fixed size. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXSTORE 10 
#define MAXLINES 1000

int foptional (int argc, char *argv[]);
int alloclines (char *lineptr[], int maxlines, char buffer[], int maxstore, int prlines);
void writelines (char *lineptr[], int prlines, int nlines);

/* Tail: print the last -n (10 by default) lines of the input */
int main (int argc, char *argv[]) {

	char *lineptr[MAXLINES];
	char buffer[MAXSTORE];
	int prlines = 10;	/* default lines to print */
	if (argc > 1) {
		prlines = foptional (argc, argv);
		if (prlines < 1) {
			printf("Tail - print the last n lines. Usage: \" tail -n \", where n is an number.\n");
			return -1;
		}
		else if (prlines > MAXLINES - 1) {
			printf("Error, maximum value is %d\n", (MAXLINES - 1));
			return -1;
		}
		
	}
	printf("Will be printed last %d lines\n", prlines);
	int lines = 0;
	if ((lines = alloclines (lineptr, MAXLINES, buffer, MAXSTORE, prlines)) > 0) {
		writelines (lineptr, prlines, condition);
		return 0;
	} else {
		printf("error: input too big, exiting\n");
		return 1;
	}
}

#define MAXLEN 1000	/* max length of any input line */
int xgetline (char s[], int lim);
int space_allocator (int nspace, int *nlines, int prlines, char buffer[], int free);

/* readlines: read input lines */
int alloclines (char *lineptr[], int maxlines, char buffer[], int maxstore, int prlines) {

	int len, left, size, nlines, place, free, nplace;
	char line[MAXLEN], *p;
	nlines = place = 0;
	while ((len = xgetline (line, MAXLEN)) > 1)  {
		if ((place + len) > maxstore) {
			free = maxstore - len;
			if ((nplace = space_allocator (len, &nlines, prlines, buffer, free)) > 0)
				place = maxstore - nplace;
			else
				return -1;
		}
			line[len] = '\0';
			p = &buffer[place];
			strcpy (p, line);
			lineptr[nlines++] = p;
			place += len;
			
		}
	return nlines;
}	

/* space_allocator: make space in the buffer for the valid lines */
int space_allocator (int nspace, int *nlines, int prlines, char buffer[], int free) {
	printf("\n-------SPACEALLOCATOR------------\n");
	int unused_pointers, total_free, unused_free, i;
	if ((unused_pointers = *nlines - prlines) < 1)
		return -1;
	for (i = 1; i <= unused_pointers; ++i)
	       unused_free = strlen (buffer+i);
	if ((total_free = free + unused_free) < nspace)
		return -1;
	printf("\n-------SPACEALLOCATOR------------\n");
	for (i = 0; i <= prlines; ++i)
		buffer[i] = buffer[unused_free + i];
	return total_free;
}
			
/* writelines: write output lines */
void writelines (char *lineptr[], int prlines, int nlines) {
	
	if (nlines < prlines)
		prlines = nlines;

	while (prlines-- > 0)
		printf("%s\n", lineptr[--nlines]);
}

/* xgetline: get a line into s[], return length */
int xgetline (char s[], int lim) {

	int i, c;
	
	i = 0;
	while ((c = getchar()) != EOF && c != '\n' && i < lim - 1)
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* foptional: return value of the optional argument */
int foptional (int argc, char *argv[]) {

	int i, c, val;

	if (argc != 2) {
		printf("Too many optional arguments\n");
		return -1;
	}

	if ((c = (*++argv)[0]) == '-') {
		if (isdigit (c = (*++argv[0]))) {
				val = atoi (*argv);
				return val;
				}
		else {
			printf("Not a number afer \"-\"\n");
			return -1;
		}
	}
	else {
		printf("Argument for tail: \"-n\", where n is a number\n");
		return -1;
	}
	printf("Unknown error, exiting\n");
	return -1;
}



