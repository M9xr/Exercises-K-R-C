/* Exercise 5-7. Rewrite "readlines" to store lines in an array suppplied by "main", rahter than calling "alloc" to maintain storage. How much faster is the program? */ 
/* Exercise 5-14. Modify the sort program to handle a "-r" flag, which indicates sorting in reverse (decreasing) order. Be sure that "-r" works with "-n". */ 

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXSTORE 50000
char *lineptr[MAXLINES];

int readlines (char *lineptr[], int nlines, char buffer[], int bufsize);
void writelines (char *lineptr[], int nlines);
void xqsort (void *lineptr[], int left, int right,
		int (*comp) (void *, void *), int optional);
int numcmp (char *, char *);

/* sort input lines */
int main (int argc, char *argv[]) {

	int nlines;		/* number of input lines read */
	int numeric = 0;	/* 1 if numeric sort */
	int reverse = 0;	/* 1 if reverse sort */
	char buffer[MAXSTORE];	/* array to store input */
	
	int c;
	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
			case 'n':
				numeric = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			default:
				printf("No such option - sort settings set to default\n");
				numeric = reverse = 0;
				argc = 0;
				break;
			}

	if ((nlines = readlines (lineptr, MAXLINES, buffer, MAXSTORE)) >= 0) {
		xqsort ((void **) lineptr, 0, nlines - 1,
			(int (*) (void *, void *)) (numeric ? (void *) numcmp : (void *) strcmp), reverse);
		writelines (lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000	/* max length of any input line */

int xgetline (char *, int);

/* readlines: read input lines */
int readlines (char *lineptr[], int maxlines, char buffer[], int maxstore) {

	int len, nlines, place;
	char *p, line[MAXLEN];

	nlines = place = 0;
	while ((len = xgetline (line, MAXLEN)) > 1) {
		if (nlines >= maxlines || (maxstore -= len) <= 0)
			return -1;
		else {
			line[len-1] = '\0';	/* delete newline */
			p = &buffer[place];
			strcpy (p, line);
			lineptr [nlines++] = p;
			place += len;
		}
	}
	return nlines;
}

/* writelines: write output lines */
void writelines (char *lineptr[], int nlines) {

	while (nlines-- > 0)
		printf("%s\n", *lineptr++);

}

/* qsort: sort v[left]...v[right] into increasing order */
void xqsort (void *v[], int left, int right,
		int (*comp) (void *, void *), int reverse) {

	int i, last;
	void swap (void *v[], int i, int j);

	if (left >= right)	/* do nothing if array contains */
		return;
	swap (v, left, (left + right)/2);
	last = left;

	for (i = left+1; i <= right; i++)
		if (((*comp) (v[i], v[left]) < 0) != reverse)
			swap (v, ++last, i);
	swap (v, left, last);
	xqsort (v, left, last-1, comp, reverse);
	xqsort (v, last+1, right, comp, reverse);
}

/* swap: interchange v[i] and v[j] */
void swap (void *v[], int i, int j) {

	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* getline: specialized version */
int xgetline (char s[], int lim) {

	int c, i;
	
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

#include <stdlib.h>

/* numcmp: compare s1 and s2 numerically */
int numcmp (char *s1, char *s2) {

	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

