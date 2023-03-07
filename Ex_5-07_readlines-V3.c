/* Exercise 5-7. Rewrite "readlines" to store lines in an array suppplied by "main", rahter than calling "alloc" to maintain storage. How much faster is the program? */ 
 

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXSTORE 50000

char *lineptr[MAXLINES];

int readlines (char *lineptr[], int nlines, char buffer[], int bufsize);
void writelines (char *lineptr[], int nlines);
void qsort (char *lineptr[], int left, int right);

/* sort input lines */
int main (void) {

	int nlines;	/* number of input lines read */
	char buffer[MAXSTORE];

	if ((nlines = readlines (lineptr, MAXLINES, buffer, MAXSTORE)) >= 0) {
		qsort (lineptr, 0, nlines - 1);
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
void qsort (char *v[], int left, int right) {

	int i, last;
	void swap (char *v[], int i, int j);

	if (left >= right)	/* do nothing if array contains */
		return;
	swap (v, left, (left + right)/2);
	last = left;

	for (i = left+1; i <= right; i++)
		if (strcmp (v[i], v[left]) < 0)
			swap (v, ++last, i);
	swap (v, left, last);
	qsort (v, left, last-1);
	qsort (v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap (char *v[], int i, int j) {

	char *temp;

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



