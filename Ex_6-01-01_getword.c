/* Exercise 6-1. Our version of "getword" does not properly handle underscores, string constants, comments, or preprocesor control lines. Write a better version. */

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"constant", 0,
	"continue", 0,
	"default", 0,
	"do", 0,
	"double", 0,
	"else", 0,
	"enum", 0,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"register", 0,
	"return", 0,
	"short", 0,
	"signed", 0,
	"sizeof", 0,
	"static", 0,
	"struct", 0,
	"switch", 0,
	"typedef", 0,
	"union", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "max_functions.h"

#define NKEYS (sizeof keytab / sizeof (keytab[0]))
#define MAXWORD 100

int getword (char *, int);
struct key *binsearch (char *, struct key *, int);

/* count C keywords; pointer version */
int main (void) {
	
	char word[MAXWORD];
	struct key *p;

	while (getword (word, MAXWORD) != EOF)
		if (isalpha (word[0]))
			if ((p = binsearch (word, keytab, NKEYS)) != NULL)
				p->count++;
	for (p = keytab; p < keytab + NKEYS; p++)
		if (p->count > 0)
			printf("%4d %s\n", p->count, p->word);
	return 0;
}

/* binsearch: find word in tab[0]..tab[n-1]; version returning pointer to struct*/
struct key *binsearch (char *word, struct key *tab, int n) {

	int cond;
	struct key *low = &tab[0];
	struct key *high = &tab[n];	// This exceed the boundries just one above, so you cannot dereference it, but you can use it in expression
	struct key *mid;

	while (low <= high) {
		mid = low + (high - low) /2; 	// Addition is illegal. Substraction is legal, however, so "high - low" is the number of elements.
		if ((cond = strcmp (word, mid->word)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else 
			return mid;
	}
	return NULL;
}

/* getword: get next word or character from input */
int getword (char *word, int lim) {

	int c;
	int exit = 0;

	char *w = word;

	while (isspace (c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (c == '/') {
		c = getch();
		if (c == '/') {
			while ((c = getch()) != '\n' && c != EOF)
				;
		}
		else if (c == '*') {
			while ((c = getch()) != EOF) {
				if (c == '*') {
					if ((c = getch()) == '/' && c != EOF)
						break;
				}
			}
		}
		else
			ungetch(c);
	}
	else if (c == '#' || c == '_')
		while (!isspace (c = getch()))
				;
	else if (c == '"')
		while ((c = getch()) != '"' && c != EOF)
			;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!islower (*w = getch()) && *w != '_' ) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

	
