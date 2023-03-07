/* Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and for each word, a list of the line numbers on which it occurs.
 * Remove noise words like "the", "and", and so on. */

struct tnode {		/* the tree node: */
      char *word;		/* points to the text */
      int count;		/* numer of occurrences */
      int line;			/* line number */
      struct tnode *left;	/* left child */
      struct tnode *right;	/* right child */
      struct tnode *next;	/* same word, different line */
};

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "max_functions.h"
#include <stdlib.h>

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);

int line_number = 1;

/* word frequency count */
int main(void) {
	
	struct tnode *root;
	char word[MAXWORD];
	int num_word = 0;
	root = NULL;
	while (getword(word, MAXWORD) != EOF) 
		if (isalpha (word[0])) {
			root = addtree(root, word, line_number);
			++num_word;
		}

	treeprint(root);
	printf("\nNumber of words: %d\n", num_word);
	return 0;
}

struct tnode *talloc(void);
char *strdupl(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree (struct tnode *p, char *w, int line_num) {

	int cond, val;
	if (p == NULL) {		/* a new word has arrived */
		p = talloc();		/* make a new node */
		p->word = strdupl(w);
		p->count = 1;
		p->line = line_num;
		p->left = p->right = p->next = NULL;
	}
	else {
		cond = strcmp(p->word, w);
		if (cond == 0) {
			p->count++;			/* reapeated word */
			while (p->next != NULL)
				p = p->next;
			if (p->line != line_num)
				addtree(p->next, w, line_num);
		}
		else if (cond > 0) {	/* less than the node goes into left subtree */
			p->left = addtree(p->left, w, line_num);
		}
		else { 			/* greater than node goes into right subtree */
			p->right = addtree(p->right, w, line_num);
		}
	}
	return p;
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
void treeprint (struct tnode *p) {

	if (p != NULL) {
		treeprint(p->left);
		treeprint(p->next);
		printf("%4d %d %s\n", p->count, p->line, p->word);
		treeprint(p->right);
	}
}
		
/* getword: get next word or character from input */
int getword(char *word, int lim) {

	int c, gethc(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	
	if (c == '\n');
		++line_number;
	if (c != EOF && c != '\n')
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}

	*w = '\0';
	return word[0];

}
