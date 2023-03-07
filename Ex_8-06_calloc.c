/* Exercise 8-6. The standard library function "calloc(n, size)" returns a pointer to n objects of size "size", with the storage initialiazed to zero.
 * Write "calloc", by calling "malloc" or by modifying it. */

#include <stdio.h>

typedef long Align;	/* for alignment to long boundary */

union header {		/* block header */
	struct {	
		union header *ptr;	/* next block if on free list */
		unsigned size;		/* size of this block */
	} s;
	Align x;  /* force alignment of blocks */
};

typedef union header Header;
static Header base;	/* empty list to get started */
static Header *freep = NULL;	/* start of free list */

void *xmalloc(unsigned);
void xfree(void *);
static Header *morecore(unsigned);
void *xcalloc(unsigned n, size_t size);

/* calloc: return a pointer to n objects of size "size", with the storage initialized to zero. */
void *xcalloc(unsigned n, size_t size) {

	char *p_zerro, *p;
	p = p_zerro = (char *) xmalloc(n * size);
	while (*p_zerro)
		*p_zerro++ &= 0;
	return p;
}


/* xmalloc: general-purpose storage allocator */
void *xmalloc(unsigned nbytes) {

	Header *p, *prevp;
	unsigned nunits;

	nunits = ((nbytes + sizeof(Header) - 1) / sizeof(Header)) + 1;
	if ((prevp = freep) == NULL) {	/* no free list yet */	/* assign address of freep to prevp */
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {  /* big enough */
			if (p->s.size == nunits)  /* exactly */
				prevp->s.ptr = p->s.ptr;
			else {	/* allocate tail end */
				p->s.size -= nunits;		/* substract allocated units from the block */
				p += p->s.size;			/* make a new header in the place where newly allocated units reside */
				p->s.size = nunits;		/* set up size for the new header; the size is equal to the allocated units */
			}
			freep = prevp;			/* freep points to the last found block */ 
			return (void *) (p+1);		/* return free space to user; (p+1) preserves the header */
		}
		if (p == freep)	/* wrapped around free list */  /* searching made a lap around all blocks; no proper one was found */
			if ((p = morecore(nunits)) == NULL)
				return NULL;	/* none left */
	}
}

#define NALLOC	1024	/* minimum #units to request */
static Header *morecore(unsigned nu) {

	char *cp, *sbrk(int);		/* cp - char pointer (probably), sbrk - space break (probably) */
	Header *up;			/* up - unit pointer (probably) */

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)	/* no space at all */
		return NULL;
	up = (Header *) cp;	/* cast space units to Header */
	up->s.size = nu;	/* unit pointer->struct.size = number units */
	xfree((void *)(up+1));	/* puts all units, except the header, to the free list */
	return freep;
}

/* free: put block ap in free list */
void xfree(void *ap) {			/* ap - allocate pointer (pr...) */

	Header *bp, *p;

	bp = (Header *)ap - 1;	/* point to block header */
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)		/* condition checks where is the address of bp relatively to freep, it break if bp is between freep and freep->s.ptr */
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))			/* if condition checked the whole loop; the bp address is outside */
			break;	/* freed bloack at start or end of arena */

	if (bp + bp->s.size == p->s.ptr) {	/* join to upper nbr */		/* bp has header included in its size, therfore bp + bp->s.size points one unit beyond its free space boundary, maybe at another header*/
		bp->s.size += p->s.ptr->s.size;					/* if it has the same address as a header, add the header's size to bp's size to combine them */ 
		bp->s.ptr = p->s.ptr->s.ptr;					/* bp->s.ptr pointing to the same header as the header with which bp was combined */
	}
	else
		bp->s.ptr = p->s.ptr;						/* bp->s.ptr points where free->s.ptr do */
	if (p + p->s.size == bp) {	/* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;						/* The address of bp was higher than freep and it starts just after freep boundary, therfore bp is appended to freep. */
	}
	else
		p->s.ptr = bp;							/* free->s.ptr points where bp->s.ptr do */
	freep = p;
}

int main(void) {

	int array1[] = {61, 124, 63, 21, 52}, i = 0, *ar1;
	for (; array1[i] != '\0'; ++i) {
		printf("%d ", array1[i]);
	}
	printf("\n");
	ar1 = (int *) xmalloc(10 * sizeof(array1[0]));

	ar1[0] = 14;
	ar1[1] = 12;
	ar1[6] = array1[2];
	ar1[8] = 88;
	for (i = 0; i <= 10; ++i) {
		ar1[i] += i;
		printf("%d:", i);
		printf("%d  ", ar1[i]);
	}
	printf("\n");

	char *ptr1;
	ptr1 = xcalloc(50, sizeof(char));
	ptr1[0] = 'X';
	ptr1[14] = 'A';
	for (i = 0; i < 50; ++i) {
		ptr1[i] += 30 + i;
		printf("%c", ptr1[i]);
	}
	//printf("%c %c\n", ptr1[0], ptr1[14]);

	printf("\n");
	return 0;
}
	
