/* Exercise 6-5. Write a function "undef" that will remove a name and definition from the table maintained by "lookup" and "install". */

struct nlist {		/* table entry: */
	struct nlist *next;	/* next entry in chain */
	char *name;		/* defined name */
	char *defn;		/* replacement text */
};

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "max_functions.h"

int getword(char *, int);
void hashprint(void);
struct nlist *install(char *name, char *defn);
void undef(char *name);

#define HASHSIZE 101
#define MAXWORD 100
static struct nlist *hashtab[HASHSIZE];	/* pointer table */

int main(void) {

	char word1[MAXWORD], word2[MAXWORD], word[MAXWORD];
	int set = 0, set2 = 0, val;
	while ((val = getword(word, MAXWORD)) > 1 || val == -2) {
		if (val == -2)
			set2 = 1;
		else {
			if (set != 1) {
				if (set2 == 1) {
				      	undef(word);
					set2 = 0;
				}	
				else {
					strcpy(word1, word);
					set = 1;
				}	
			}
			else {
				strcpy(word2, word);
				install(word1, word2);
				set = 0;
			}
		}
	}
	hashprint();
	return 0;

}

/* hasprint: print all hashes from the table */
void hashprint(void) {
	
	struct nlist *p;
	for (int i = 0; i < HASHSIZE; i++) {
		if ((p = hashtab[i]) != NULL) {
			printf("For value:%d, following strings are hashed\n", i);
			for (; p != NULL; p = p->next) 
				printf("-%s ", p->defn);
			printf("\n\n");
		}
	}
}

/* hash: form hash value for storing s */
unsigned hash(char *s) {

	signed long hashval;
	
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {

	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;	/* found */
	return NULL;			/* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {

	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {		/* not found */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];	/* Blocks are added at the begining of blocks. Here np->next copies the address to all added blocks so far. */
		hashtab[hashval] = np;		/* Here our newly created block's address is placed at the beginning of the array (hashtab[hashval] copies the address np), so n is now at the beggining and n->next points to the rest */
	} else	/* already there */
		free((void *) np->defn); /* free previous defn */
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;

}

/* getword: get next word or character from input */
int getword(char *word, int lim) {

        int c, amount = 1;
        char *w = word;

        while ((c = getch()) != EOF && amount < lim) {
		if (isalpha(c)) {
			*w++ = c;
                	while (isalnum(c = getch()) || c == '\'' && amount < lim) {
                        	*w++ = c;
				amount++;
			}

                }
                *w = '\0';
		if ((strcmp(word, "undef")) == 0)
			return -2;
                return amount;
     }
}

/* undef: remove a name and definition from the table */
void undef(char *s) {

	struct nlist *np, *np2;
	int val = hash(s);
	for (np = hashtab[val], np2 = NULL; np != NULL; np2 = np, np = np->next) {
		if (strcmp(s, np->name) == 0) {
			free((void *) np->name);
			free((void *) np->defn);
			if (np2 == NULL)	/* The word to remove is at the beginning */
				hashtab[val] = np->next;
			else			/* The word further in the linked list */
				np2->next = np->next;
			free(np);
			return;
		}
	}	
	printf("%s was not defined\n", s);	
}

