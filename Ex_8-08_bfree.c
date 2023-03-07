/* Exercise 8-6. The standard library function "calloc(n, size)" returns a pointer to n objects of size "size", with the storage initialiazed to zero.
 * Write "calloc", by calling "malloc" or by modifying it. */
/* Exercise 8-7. "malloc" accepts a size request without checking its plausibility; "free" belives that the block it is asked to free contains a valid size field.
 * Improve these routines so they make more pain with error checking. */
/* Exercise 8-8. Write a routine "bfree(p,n)" that will free any arbitrary block "p" of "n" characters into the free list maintained by "malloc" and "free".
 * By using "bfree", a user can add a static or external array to the free list at any time. */

#include <stdio.h>

typedef long Align;	/* for alignment to long boundary */

union header {		/* block header */
	struct {	
		union header *ptr;	/* next block if on free list */
		unsigned size;		/* size of this block */
	} s;
	Align x;  /* force alignment of blocks */
};

#define NALLOC	1024	/* minimum #units to request */

typedef union header Header;
static Header base;	/* empty list to get started */
static Header *freep = NULL;	/* start of free list */

void *xmalloc(unsigned);
void xfree(void *);
static Header *morecore(unsigned);
void *xcalloc(unsigned n, size_t size);
void bfree(void *, unsigned);

/* bfree: free block "p" of "n" characters */
void bfree(void *p, unsigned n) {
	
	printf("\n\n");
	Header *bp = (Header *)(p) - 1;
	Header *bp2 = (Header *)(p) -1;
	printf("\taddress of the block = %p\n", bp);
	unsigned long nunits;
	nunits = ((n + sizeof(Header) - 1) / sizeof(Header));
	printf("block_size in:\t bytes:%ld | nunits:%d |\n\t\b\bto free:\t bytes:%d  | nunits:%ld\n\t  bytes to adjust:%ld | bytes after adjustment:%ld\n", bp->s.size * sizeof(Header), bp->s.size, n, nunits, nunits * sizeof(Header) - n, nunits * sizeof(Header));
	if (p == NULL || bp->s.size < nunits || nunits <= 0) {
		if (p == NULL)
			printf("bfree: error, can't free block pointing to NULL\n");
		if (bp->s.size < nunits) 
			printf("bfree: error, size of the block is smaller(%d) than requested bytes[in nunits](%ld) to free within it.\n", bp->s.size, nunits);
	        if (nunits == 0)
			printf("bfree: error, invalid number of bytes[in nunits](%ld)\n", nunits);
		return;
	}
	bp->s.size -= nunits;
	bp += bp->s.size;
	bp->s.size = nunits;
	xfree(bp+1);
}

/* calloc: return a pointer to n objects of size "size", with the storage initialized to zero. */
void *xcalloc(unsigned n, size_t size) {

	char *p_zero, *p;
	long unsigned i = 0;
	if ((p = p_zero = (char *) xmalloc(n * size)) == NULL)
		return NULL;
	while (i++ < n * size) 
		*p_zero++ = '\0';
	return p;
}


/* xmalloc: general-purpose storage allocator */
void *xmalloc(unsigned nbytes) {

	Header *p, *prevp;
	unsigned nunits;
	if (nbytes > (sizeof(long double) * NALLOC) || nbytes == 0) {
		printf("malloc: error, invalid value (%d) to allocate\n", nbytes);
		return NULL;
	}
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

/* morecore: ask system for more memory */
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
	
	if (ap == NULL) {
		printf("free: error, invalid value (NULL) for freeing\n");
		return;
	}
	bp = ((Header *)ap) - 1;	/* point to block header */
	if (bp->s.size <= 0) {
		printf("free: error, invalid value (%d) of the header size\n", bp->s.size);
		return;
	}
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)		/* condition checks where is the address of bp relatively to freep, it break if bp is between freep and freep->s.ptr */
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))			/* if condition checked the whole loop; the bp address is outside */
			break;	/* block to place at the beggining or end of arena */

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


	Header *dp;
	dp = (Header *) xmalloc(320);
	printf("address of the block given by malloc:\n\t(address after the header) %p\n\t(address of the header)    %p", dp, dp-1);
	bfree(dp, 16);
	bfree(dp, 16);
	bfree(dp, 14);
	bfree(dp, 111);


	printf("\n");
	return 0;
}
	
