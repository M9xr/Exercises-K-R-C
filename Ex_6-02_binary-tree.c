/* Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each group of variable names that are identical in the fist 6 characters, but different somewhere thereafter.
 * Don't count words within strings and comments. Make 6 a parameter that can be set from the command line. */


struct tnode {		/* the tree node: */
      char *word;		/* points to the text */
      int count;		/* numer of occurrences */
      struct tnode *left;	/* left child */
      struct tnode *right;	/* right child */
      struct tnode *sim_left;	/* sim left child */
      struct tnode *sim_right;	/* sim right child */
	    
};

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "max_functions.h"
#include <stdlib.h>

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *, int);
int getword(char *, int);
int spec_strcmp(char *, char *, int); 
int num_word_ex = 0;

#define DEFAULT_CHARS 6		/* default similar chars for a word to be printed in group */

/* word frequency count */
int main(int argc, char *argv[]) {
	
	int to_print = DEFAULT_CHARS;
	if (argc > 1) {
		if (argc == 2 && *(++argv)[0] == '-') {
			if (isdigit(*++argv[0]))
				to_print = atof(*argv);
			else
				printf("Invalid value \"%c\" for the parameter, seting default 6\n", **argv);
		}
		else {
			printf("Syntax error: \"%s\" is no a parameter, exiting\n", *argv);
			return -1;
		}
	}
//	printf("Chars to print in group:%d\n", to_print);


	struct tnode *root;
	char word[MAXWORD];
	int num_word = 0;
	root = NULL;
	while (getword(word, MAXWORD) != EOF) 
		if (isalpha (word[0])) {
			root = addtree(root, word, to_print);
			++num_word;
		}
	treeprint(root, 0);
	printf("\nNumber of words: %d", num_word);
	printf("\nNumber or the different words: %d", num_word_ex);
	printf("\n");
	return 0;
}

struct tnode *talloc(void);
char *strdupl(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree (struct tnode *p, char *w, int to_print) {

	int cond, val;
	if (p == NULL) {		/* a new word has arrived */
//		printf("I.Add word: %s\n", w);
		p = talloc();		/* make a new node */
		p->word = strdupl(w);
		p->count = 1;
		p->left = p->right = p->sim_left = p->sim_right = NULL;
	}
	else {
		cond = spec_strcmp(p->word, w, to_print);
		if (cond == 0){
//			printf("(same), ");
			p->count++;			/* reapeated word */
		}
		else if (cond > 0 && cond < 665 ) {	/* less than the node goes into left subtree */
//			printf("(left), ");
			p->left = addtree(p->left, w, to_print);
		}
		else if (cond < 0 && cond > -665) { /* greater than node goes into right subtree */
//			printf("(right), ");
			p->right = addtree(p->right, w, to_print);
		}
		else if (cond == 666) { /* n chars is similar to node and lexicographically word is less than it */
//			printf("(sim-left), ");
			p->sim_right = addtree(p->sim_right, w, to_print);
		}
		else  { /* n chars is similar to node and lexicographically word is more than it */
//			printf("(sim-right), ");
			p->sim_left = addtree(p->sim_left, w, to_print);
		}
	}
	return p;
}

/* spec_strcmp: compare two strings, special version */
int spec_strcmp(char *s, char *t, int lim) {

	for ( ;*s == *t; s++, t++, --lim)
		if (*s == '\0' && *t == '\0' && *s == *t)
			return 0;	
	if (lim <= 0) {
		if ((*s - *t) > 0)
			return -666;
		else
			return 666;
	}
	else
		return *s - *t;
}

/* talloc: make a tnode */
struct tnode *talloc(void) {

	return (struct tnode *) malloc (sizeof(struct tnode));
}

/* strdup: make a duplicate of s */
char *strdupl(char *s) {

	char *p;

	p = (char *) malloc (strlen(s)+1);	/* +1 for '\0' */
	if (p != NULL)
		strcpy(p,s);
	return p;
}
/* treeprint: in-order print of tree p */
/* types of node:	1-simleft;	2-left;		3-right;	 4-simright;	0-root */
void treeprint (struct tnode *p, int type) {

	if (p != NULL) {
		++num_word_ex;
		if (type == 4)
			printf("[%d] %s  ", p->count, p->word);
		treeprint(p->left, 2);
		treeprint(p->sim_left, 1);
		if (type == 1 || type == 2 || type == 3 || type == 0)
			printf("[%d] %s  ",p->count, p->word);
		treeprint(p->sim_right, 4);
		if (type == 2 || type == 3 || type == 0)
			printf("\n");
		treeprint(p->right, 3);
	}
}
		
/* getword: get next word or character from input */
int getword(char *word, int lim) {

	int c;
	char *w = word;

	while (isspace(c = getch()))
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
			while ((c = getch()) != EOF)
				if (c == '*') {
					if ((c = getch()) == '/' && c != EOF)
						break;
				}
		}
		else
			ungetch(c);
	}
	else if (c == '"')
		while ((c = getch()) != '"' && c != EOF)
			;
	if (!isalpha(c) && c != '*') {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++) {
		*w = getch();
		if (!isalnum(*w) && *w != '_' && *w != '*') {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}
