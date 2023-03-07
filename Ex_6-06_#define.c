/* Exercise 6-6. Implement a simple version of the "#define" processor (i.e., no arguments) suitable for use with C programs, based on the routines of this section.
 * You may find "getch" and "ungetch" helpful. */

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include "max_functions.h"
#include "string.h"

int getword(char *, int);
struct nlist *install(char *name, char *defn);
unsigned hash(char *s);
struct nlist *lookup(char *);
int getch(void);
void ungetch(int);

#define HASHSIZE 101
#define MAXWORD 100
#define MAXCHARS 10000

#define dbgint(expr) printf(#expr " = %d\n", expr)
#define dbgstr(expr1, expr2) printf(#expr1"%d = %s\n", expr2, expr1)
static struct nlist *hashtab[HASHSIZE];
static char buffer[MAXCHARS];
enum {NORMAL, COMMENT = 2, NEW_LINE = -2, START_LONG_COMMENT = 3, END_LONG_COMMENT = 3, START_STRING = 4, END_STRING = 4, DEFINITION, UPPER_WORD, FALSE, TRUE, SPACE,
	START_BRACKET = 0, END_BRACKET = 0};

int main(void) {

	int value;
	int spec_value = FALSE;
	int demand = FALSE;
	int setd = FALSE;
	struct nlist *p;
	char word[MAXWORD], word1[MAXWORD], *w = word;

	while ((value = getword(word, MAXWORD)) != EOF) {
		if (value == SPACE)
			;
		else if (demand == FALSE) {
			if (spec_value == FALSE) {
//				printf(" Spec_false--%s-value%d-\n", word, value);
				if (value == NORMAL || value == NEW_LINE || value == SPACE || value == START_BRACKET) {
//					printf("NORMAL NEW SPACE(%d) %s", value,  word);
				}
				else if (value == DEFINITION) {
//					printf("DEFINITION ARRIVED---\n");
					demand = TRUE;
				}
				else if (value == UPPER_WORD) {
					if ((p = lookup(word)) != NULL) {
						strcpy(word, p->defn);
//						printf(" lookup1:%s",word);
					}
					else {
						//printf("Error, \"%s\" undefined!\n", word);
					}
							
				}
				else 
					spec_value = value;
//				printf("OTHER TYPE----%s--\n", word);
			}
			else {
				if (value == spec_value || value + spec_value == 0) {
					spec_value = FALSE;
//				printf("   SPECIAL:%s  ", word);
				}
			}
		}
		else if (demand == TRUE) {
			if (value == UPPER_WORD && setd == FALSE) {
				strcpy(word1, word);
				setd = TRUE;
//				printf("  ||-DEMAND UPPER  word1:%s word:%s ||", word1, word);
			}
			else {
				install(word1, word);
				demand = setd = FALSE;
//				printf(" EXIT_DEMAND! word%s defn:%s\n", word1, word);
			}
		}
		strcat(buffer, word);


	}

	printf("\n\n%s", buffer);
	return 0;
}

int getword(char *word, int lim) {

	int c;
	char *w = word;
	while ((c = getch()) != EOF && lim-- > 0) {
		*w++ = c;
		if (c == '\n') {
			*w = '\0';
			return NEW_LINE;
		}
		else if (c == ' ') {
			*w = '\0';
			return SPACE;
		}
		else if (c == '[' || c == ']') {
			*w = '\0';
			return START_BRACKET;
		}
		else if (c == '/') {
			c = getch();
			*w++ = c;
			if (c == '/') {
				*w = '\0';
				return COMMENT;
			}
			else if (c == '*') {
				*w = '\0';
				return START_LONG_COMMENT;
			}
			else  {
				*(--w) = '\0';
				ungetch(c);
			}
		}
		else if (c == '*') {
			if ((c = getch()) == '/') {
				*w++ = '/';
				*w = '\0';
				return END_LONG_COMMENT;
			}
			else
				*w++ = c;
		}
		else if (c == '"') {
			*w = '\0';
			return START_STRING;
		}
		else if (c == '#') {
			while (!isspace (c = getch()))
				*w++ = c;
			ungetch(c);
			*w = '\0';
			if (strcmp(word, "#define") == 0)
				return DEFINITION;
			else
				return NORMAL;
		}
		else if (isupper(c)) {
			while (isupper(c = getch()))
				*w++ = c;
			ungetch(c);
			*w = '\0';
			return UPPER_WORD;
		}
		else if (c != EOF) {
			while (!isspace(c = getch()) && c != EOF && c != '[' && c != ']')
				*w++ = c;
			ungetch(c);
			*w = '\0';
			return NORMAL;
		}

			
	}
	*w = '\0';
	return EOF;
}

unsigned hash(char *s) {

	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 19 * hashval;
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {

	struct nlist *np;
	for(np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

struct nlist *install(char *name, char *defn) {

	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else
		free((void *) np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
	
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {

	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else {
		if (c != EOF)
			buf[bufp++] = c;
		else
			buf[bufp++] = '\0';
	}
}
