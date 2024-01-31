/* Exercise 6-5. Write a function "undef" that will remove a name and definition from the table maintained by "lookup" and "install". */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {	/* table entry: */
	struct nlist *next;	/* next entry in chain */
	char *name;		/* defined name */
	char *defn;		/* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];	/* pointer table */

unsigned hash(char *);
struct nlist *lookup(char *);
char *xstrdup(char *);
struct nlist *install(char *, char *);
void undef(char *);
void print_hash(void);

/* Undef: Undefine an defined value */
int main(void) {

/* Make two lists one with hash value 25, next one with value 49 */

	/* Hash value 25 */
	install("Ania", "Flex");
	install("calciuf", "calcium");
	
	/* Hash value 49 */
	install("Bazylia", "Kleks");
	install("Trabaj", "Toryzle");
	install("sync", "x");
	install("wielkiegq", "x");
	
	print_hash();
	
	/* Undef first member of the hash 25 list, and middle member of hash 49 then check if the list are connected properly*/
	undef("calciuf");
	undef("Trabaj");

	printf("---- calciuf and Trabaj are removed by undef -----\n\n");

	print_hash();

	return 0;
}

/* print_hash: print hashed values */
void print_hash(void) {

	struct nlist *p;
	for (int i = 0; i < HASHSIZE; i++) {
		if ((p = hashtab[i]) != NULL) {
			printf("Hash value of the following words: %d\n", i);
			for (; p != NULL; p = p->next)
				printf("|Name: %s Defn: %s|  ", p->name, p->defn);
			printf("\n\n");
		}
	}
}

/* undef: undef name and definition from the table */
void undef(char *s) {

	struct nlist *np, *np2;
	unsigned index = hash(s);
	for (np = hashtab[index], np2 = NULL; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0) {
			free((void *) np->name);
			free((void *) np->defn);
			if (np2 == NULL) {		/* The word is at the beginnig of the linked list */
				if ((np->next) != NULL) /* Check whether the list has more than one member */
					hashtab[index] = np->next;	/* if so, make the next member fiest in the list */
				else
					hashtab[index] = NULL;		/* The word was at the beginning and had had no following members */
			}
			else  {
				np2->next = np->next; /* If the word is not at the beginnig of the list, connect the preceeding member to the following member */
				free((void *) np);		/* The word wasn't at the beggining so the memory can be freed */
			}
			
			return;
		}
		np2 = np;	/* np2 now points to the current member, the for loop will make np to point to the next member */
	}		
				
}

/* hash: form hash value for string s */
unsigned hash(char *s) {
	
	unsigned hashval;
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
	return NULL;			/* no found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {

	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	/* not found */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = xstrdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];	/* pointer to next gets the address of the "old" list */
		hashtab[hashval] = np;		/* beginning of the list gets the address of the new struct */
	} else	/* already there */
		free((void *) np->defn);  /* free previous defn */
	if ((np->defn = xstrdup(defn)) == NULL)
		return NULL;
	return np;
}

/* xstrduop: make a duplicate of char s */
char *xstrdup(char *s) {

	char *p;
	p = (char *) malloc(strlen(s)+1);	/* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}
