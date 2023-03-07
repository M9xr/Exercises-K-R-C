/* Exercise 5-7. Rewrite "readlines" to store lines in an array suppplied by "main", rahter than calling "alloc" to maintain storage. How much faster is the program? */ 
/* Exercise 5-14. Modify the sort program to handle a "-r" flag, which indicates sorting in reverse (decreasing) order. Be sure that "-r" works with "-n". */ 
/* Exercise 5-15. Add the option "-f" to fold upper and lower case together, so that case distinctions are not made during sorting; for example "a" and "A" compare equal */
/* Exercise 5-16. Add the "-d" ("directory order") option, which makes comparisons only on letters, numbers and blanks. Make sure it works in conjunction with "-f". */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXSTORE 50000
char *lineptr[MAXLINES];

int readlines (char *lineptr[], int nlines, char buffer[], int bufsize);
void writelines (char *lineptr[], int nlines);
void xqsort (void *lineptr[], int left, int right,
		int (*comp) (void *, void *), int reverse);
int numcmp (char *, char *);
int function_fold (char *s, char *t);

static int numeric = 0;		/* 1 if numeric sort */
static int reverse = 0;		/* 1 if reverse sort */
static int fold = 0;		/* 1 if fold upper and lower case together */
static int directory = 0;	/* 1 if only letters, numbers, and blanks */	

/* sort input lines */
int main (int argc, char *argv[]) {

	int nlines;		/* number of input lines read */
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
			case 'f':
			       	fold = 1;
				break;
			case 'd':
				directory = 1;
				break;
			default:
				printf("No such option - sort settings set to default\n");
				numeric = reverse = fold = directory = 0;
				argc = 0;
				break;
			}

	if ((nlines = readlines (lineptr, MAXLINES, buffer, MAXSTORE)) >= 0) {
		xqsort ((void **) lineptr, 0, nlines - 1,
			(int (*) (void *, void *)) (numeric ? (void *) numcmp : ((fold > 0  || directory > 0) ? (void *) function_fold : (void *) strcmp)), reverse);
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

	for (i = left+1; i <= right; i++) {
		if (((*comp) (v[i], v[left]) < 0) != reverse)
			swap (v, ++last, i);
	}
	swap (v, left, last);
	xqsort (v, left, last-1, comp, reverse);
	xqsort (v, last+1, right, comp, reverse);
}

#define less_value(A, B) ((A) > (B) ? (A-B) : (B-A))
#define max(A, B) ((A) > (B) ? (A) : (B))
#define min(A, B) ((A) > (B) ? (B) : (A))
#define is_within(A, B, C) (((A) >= (B) && (A) <= (C)) ? 1 : 0)

/* function_fold: check if upper case equals lower case */
int function_fold (char *s, char *t) {

	int val, within, valt, vals, sett, sets, set;
	set = sett = sets = 0;
	within = less_value ('a', 'A');
	
	while (*s != '\0' && *t != '\0') {
		valt = *t;
		vals = *s;
		if (*s != *t) {
			if (fold == 1) {
				if (is_within (valt, 'A', 'Z')) 
					valt += within;
				if (is_within (vals, 'A', 'Z')) 
					vals += within;
			}
			if (directory == 1) {
				if (!(is_within (valt, 'A', 'z') || isdigit(valt - '0') || isspace(valt))) {
					sett = set = 1;
					++t;
				}
				if (!(is_within (vals, 'A', 'z') || isdigit(vals - '0') || isspace(vals))) {
					sets = set = 1;
					++s;
				}
			}
					
			if (vals != valt && set != 1) {
				if (vals < valt)
					return -1;
				else
					return 1;
			}
		}
		if (set != 1) {
			++s;
			++t;
		}
		set = 0;

	}
	if (*s == '\0' && *t != '\0')
		return -1;
	if (*t == '\0' && *s != '\0')
		return 1;
	return 0;
	
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

