/* Exercise 8-6. The standard library function "calloc(n, size)" returns a pointer to n objects of size "size", with the storage initialiazed to zero.
 * Write "calloc", by calling "malloc" or by modifying it. */
/* Exercise 8-7. "malloc" accepts a size request without checking its plausibility; "free" belives that the block it is asked to free contains a valid size field.
 * Improve these routines so they make more pain with error checking. */

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

/* calloc: return a pointer to n objects of size "size", with the storage initialized to zero. */
void *xcalloc(unsigned n, size_t size) {

	char *p_zero, *p;
	long unsigned i = 0, val1 = 0;
	if ((p = p_zero = (char *) xmalloc(n * size)) == NULL)
		return NULL;
	while (i++ < n * size) {
		*p_zero++ = '\0';
		++val1;
	}
	printf("Size:%ld\n", val1);
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
	bp = (Header *)ap - 1;	/* point to block header */
	if (bp->s.size <= 0) {
		printf("free: error, invalid value (%d) of the header size\n", bp->s.size);
		return;
	}
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

	
	int *ap1, *ap2, i = 0;
	ap1 = (int *) xcalloc(10, sizeof(int));
	printf("\n");
	for (i = 0; i < 10; ++i) {
		ap1[i] = i + i;
		printf("ap1[%d] = %d ", i, ap1[i]);
	}
	xfree(ap1);
	printf("\n");
	ap2 = (int *) xcalloc(10, sizeof(int));
	for (i = 0; i < 10; ++i) {
		ap2[i] += i;
		printf("ap2[%d] = %d ", i, ap2[i]);
	}
	printf("\n");
	xfree(ap2);



	 long double *a = xcalloc(1000, sizeof(long double));
    		for (int i = 0; i < 1000; i++) {
		        if (a[i] != 0) {
	            		printf("Error: mycalloc failed to initialize memory to zero a[%d] = %Lf\n", i, a[i]);
        		    	xfree(a);
            			return -1;
			}
		}
	char *b = xcalloc(1000, sizeof(char));	 
		for (int i = 0; i < 1000; i++) {
		        if (b[i] != 0) {
	            		printf("Error: mycalloc failed to initialize memory to zero a[%d] = %c\n", i, b[i]);
        		    	xfree(b);
            			return -1;
			}
		}


	float *c = xcalloc(1000, sizeof(float));
	for (int i = 0; i < 1000; i++) {
		        if (c[i] != 0) {
	            		printf("Error: mycalloc failed to initialize memory to zero a[%d] = %f\n", i, c[i]);
        		    	xfree(c);
            			return -1;
			}
		}
	xfree(a);
	xfree(b);
	xfree(c);
	int *tesv = xmalloc(-2.2+2);
	xfree(tesv);
	xfree(&base);

	double *d = xcalloc(1000, sizeof(double));
	for (int i = 0; i < 1000; i++) {
		        if (d[i] != 0) {
	            		printf("Error: mycalloc failed to initialize memory to zero a[%d] = %f\n", i, d[i]);
        		    	xfree(d);
            			return -1;
			}
		}
		

	long int *f = xcalloc(1000, sizeof(long int));
    		for (int i = 0; i < 1000; i++) {
		        if (f[i] != 0) {
	            		printf("Error: mycalloc failed to initialize memory to zero a[%d] = %ld\n", i, f[i]);
        		    	xfree(f);
            			return -1;
			}
		}

		
	signed int *e = xcalloc(1000, sizeof(signed int));
    		for (int i = 0; i < 1000; i++) {
		        if (e[i] != 0) {
	            		printf("Error: mycalloc failed to initialize memory to zero a[%d] = %d\n", i, e[i]);
        		    	xfree(e);
            			return -1;
			}
		}

	xfree(d);
	xfree(e);
	xfree(f);



	printf("\n");
	return 0;
}
	
