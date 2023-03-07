/* Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and for each word, a list of the line number on which it occurs.
 * Remove noisy words like "the", "and", and so on. */


// TO DO!
// TO DO!
// TO DO!
// TO DO!
// TO DO!
// TO DO!
// TO DO!
//
struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct hznode {
	char *word2;
	int count2;
	struct hznode *less;
	struct hznode *more;
};

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "max_functions.h"
#include <stdlib.h>

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);
int getword(char *, int);
struct hznode *addhz(struct hznode *, char *, int);
void hztreeprint(struct hznode *);
void build_addhz(struct tnode *);


int number_of_lines = 1;
int num_of_words = 0;
int words_out = 0;
struct hznode *root2;

/* hertz-counting-tree */
int main (void) {
	
	struct tnode *root;
	char word[MAXWORD];
	int num_of_line = 0;
	root = NULL;
	root2 = NULL;
	while ((num_of_line = getword(word, MAXWORD)) != -1) {
			++num_of_words;
			if (strlen(word) > 2) 
				root = addtree(root, word);
	}
	build_addhz(root);
	hztreeprint(root2);
	printf("Number of words on input: %d\n", num_of_words);
	printf("Number of words on output: %d\n", words_out);

	return 0;
}

void build_addhz(struct tnode *p) {
	
	
	if (p != NULL) {
		build_addhz(p->left);
		root2 = addhz(root2, p->word, p->count);
		build_addhz(p->right);
	}

}

struct tnode *talloc(void);
char *strdupl(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = strdupl(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else {
		cond = strcmp(p->word, w);
		if (cond == 0)
			p->count++;
		else if (cond > 0)
			p->left = addtree(p->left, w);
		else
			p->right = addtree(p->right, w);
	}
	return p;
}

struct hznode *hzalloc(void);
struct hznode *addhz(struct hznode *p, char *s, int hz) {
	
	if (p == NULL) {
		p = hzalloc();
		p->word2 = s;
		p->count2 = hz;
		p->less = p->more = NULL;
	}
	else {
		if ((hz) < (p->count2)) {
			p->more = addhz(p->more, s, hz);
		}
		else {
			p->less = addhz(p->less, s, hz);
		}
	}
	return p;

}

/* hzalloc: make a hznode */
struct hznode *hzalloc(void) {
	return (struct hznode *) malloc(sizeof(struct hznode));
}	
	

/* talloc: make a tnode */
struct tnode *talloc(void) {

	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strudp: make a duplicate of s */
char *strdupl(char *s) {

	char *p;

	p = (char *) malloc(strlen(s)+1);	/* +1 for '\0' */
	if (p != NULL)
		strcpy(p,s);
	return p;
}
/* treeprint: in-order print of tree p */
void hztreeprint (struct hznode *p) {
	
	if (p != NULL) {
		++words_out;
		hztreeprint(p->less);
		printf("%d %s\n", p->count2, p->word2);
		hztreeprint(p->more);
	}

}



/* getword: get next word or character from input */
int getword (char *word, int lim) {

	int c;
	char *w = word;
	
	while ((c = getch()) != EOF) {
		if (isalpha(c)) {
			if (c >= 'A' && c <= 'Z')
				c+= ('a' - 'A');
			*w++ = c;
		}
		else if (c == '\'')
			*w++ = c;
		else if (isspace(c)) {
			if (c == '\n') {
				*w = '\0';
				return number_of_lines++;
			}
			else {
				*w = '\0';
				return number_of_lines++;
			}
		}
		else {
			*w = '\0';
			return number_of_lines;
		}
	}
	if (!isalpha(*w))
		return -1;
	else {
		*w = '\0';
		return number_of_lines;
	}
	
}

