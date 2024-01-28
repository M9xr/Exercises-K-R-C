/* Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and for each word, a list of the lines numbers on which it occurs. Remove noise words like "the," "and," and so on. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct tnode {		/* the tree node: */
	char *word;		/* points to the text */
	int count;		/* number of occurrences */
	int line_no;		/* which line the word occurs */
	struct lines *next;	/* next line the word occurs */
	struct tnode *left;	/* left child */
	struct tnode *right;	/* right child */
};

struct lines {
	int line_no;
	struct lines *next;	/* pointer to the next line */
};


#define MAXWORD 100
#define MIN_LEN 2	/* min length of the word */
struct tnode *addtree(struct tnode *, char*);
struct tnode *talloc(void);
char *xstrdup(char*);
void treeprint(struct tnode *);
int getword(char *, int);

struct lines *addline(struct lines *, int) ;
struct lines *lalloc(void);
void lineprint(struct lines *);

int line_number = 1;
int number_of_words = 0;
int ratio = 2;			/* default ratio for words to be printed, 1 = 1:100, 2 = 1:50, etc.. */
/* word frequency count */
int main(void) {

	struct tnode *root;
	char word[MAXWORD];
	int word_length;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((word_length = strlen(word) >= MIN_LEN)) {
				++number_of_words;
				root = addtree(root, word);
			}
	if (number_of_words > 100)
		ratio = 1;
	else if (number_of_words > 250)
		ratio = 0.9;
	else if (number_of_words > 1000)
		ratio = 0.8;
	else if (number_of_words > 5000)
		ratio = 0.6;
	else if (number_of_words > 10000)
		ratio = 0.3;
	else 
		ratio = 100;

	treeprint(root);

	printf("Number of words:%d   Number of lines: %d\n", number_of_words, line_number);
	return 0;
}

/* addtree: add a node with w, at or below p */ 
struct tnode *addtree(struct tnode *p, char *w) {

	int cond;
	if (p == NULL) {	/* a new word has arrived */
		p = talloc();
		p->word = xstrdup(w);
		p->count = 1;
		p->left = p->right = NULL;
		p->next = NULL;
		p->line_no = line_number;
	}
	else if ((cond = strcmp(w, p->word))  == 0) {	/* repeated word */
		p->count++;
		if ((p->line_no != line_number)) {
			p->next = addline(p->next, line_number);
		}
	}
	else if (cond < 0)	/* less than into left subtree */
		p->left = addtree(p->left, w);
	else	/* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* xstrdup: make a duplicate of char s */
char *xstrdup(char *s) {

	char *p;
	p = (char *) malloc(strlen(s)+1);	/* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* addline: add a line number to node */
struct lines *addline(struct lines *p, int number) {

	if (p == NULL) {
		p = lalloc();
		p->line_no = number;
		p->next = NULL;
	}
	else if (p->line_no != line_number)
		p->next = addline(p->next, number);
	return p;
}
	
/* lalloc: make a number_line node */
struct lines *lalloc(void) {
	return (struct lines *) malloc(sizeof(struct lines));
}

double val;
/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {

	if (p != NULL) {
		treeprint(p->left);
		/* If a particular word appears more frequently it won't be printed */
		if ((val = ((double)(p->count / (double)number_of_words) * 100)) < ratio) {
			printf("%4d %s", p->count, p->word);
			printf(" \t\t|%d", p->line_no);
			lineprint(p->next);
			printf("|\n");
		}
		treeprint(p->right);
	}
}

void lineprint(struct lines *p) {
	
	if (p != NULL) {
		printf(", %d", p->line_no);
		lineprint(p->next);
	}
}	
/* getword: get next word or character from input */
int getword(char *word, int lim) {

	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch())) 
		if (c == '\n')
			++line_number;
	if (c != EOF)
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

#define BUFSIZE 100
char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buffer */

/* get a (possibly pushed-back) character */
int getch (void) {

	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch (int c) {

	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else {
		if (c != EOF)
			buf[bufp++] =c;
		else
			buf[bufp++] = '\0';
	}
}
	
