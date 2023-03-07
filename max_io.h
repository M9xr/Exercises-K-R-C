#ifndef MAX_IO
#define MAX_IO

#define NULL	     	0
#define EOF		(-1)
#define BUFSIZ 		8192
#define OPEN_MAX 	20	/* max #files open at once */

typedef struct _iobuf {
	int cnt;	/* characters left */
	char *ptr;	/* next character position */
	char *base;	/* location of the buffer */
	struct {
		unsigned int _READ  : 1;	/* file open for reading */
		unsigned int _WRITE : 1;	/* file open for writing */
		unsigned int _UNBUF : 1;	/* file is unbuffered */
		unsigned int _EOF   : 1;	/* EOF has occured on this file */
		unsigned int _ERR   : 1;	/* error occurred on this file */
	} flag;		/* mode of file access */
	int fd;		/* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];	// extern can be declared without array size specified. It is defined later, but just below it is used in #define, so declaration here is mandatory.

#define stdin (&_iob[0])	// &_iob - means adress of iob. 
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE *fopen(char *name, char * mode);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *fp);
int fclose (FILE *fp);

#define feof(p)		((p)->flag._EOF != 0)
#define ferror(p)	((p)->flag._ERR != 0)
#define fileno(p)	((p)->fd)

#define getc(p)    (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)  (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)	


/* definition and initialization of input/output buffer ~mx*/
FILE _iob[OPEN_MAX] = {		/* stdin, stdout, stderr */
	{ 0, (char *) 0, (char *) 0, 1, 0, 0, 0, 0, 0},
	{ 0, (char *) 0, (char *) 0, 0, 1, 0, 0, 0, 1},
	{ 0, (char *) 0, (char *) 0, 0, 1, 1, 0, 0, 2}
  /*      ^	      ^		  ^  ^  ^  ^  ^  ^  ^
   *      |	      | 	  |  |  |  |  |  |  |
   *      |	      |		  |  |	|  |  |  |  |
  char left           |		  |  |  |  |  |  |  |
next character position		  |  |  |  |  |  |  |
	     location of the buffer  |  |  |  |  |  |
	         file open for reading  |  |  |  |  |
		    file open for writing  |  |  |  |
		    	  file is unbuffered  |  |  |
	          EOF has occurred on this file  |  |
		       error occurred on this file  |
		       		      file descriptor
  */

};



/* ----------------------------------------------------------------*/


/* ----------------- FOPEN ---------------------------------------------------- */
#include <fcntl.h>
#include <unistd.h>
#define PERMS 0666	/* RW for ownwer, group, others */

FILE *fopen(char *name, char *mode) {

	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag._READ | fp->flag._WRITE) == 0)
			break;	/* found free slot */
	if (fp >= _iob + OPEN_MAX)	/* no free slots */
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	}
	else 
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)	/* couldn't access name */
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	if (*mode == 'r')
		fp->flag._READ = 1;
	else
		fp->flag._WRITE = 1;
	return fp;
}


/* ------------ _FILLBUF --------------------------------------- */
#include <stdlib.h>
/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp) {

	int bufsize;

	if (fp->flag._READ != 1 | fp->flag._EOF | fp->flag._ERR)
		return EOF;
	bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL)	/* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;	/* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {  /* --cnt because function will return *fp->ptr++, taking one place form the buffer, */
		if (fp->cnt == -1)
			fp->flag._EOF = 1;
		else
			fp->flag._ERR = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* ----------- _FLUSHBUF --------------------------------------- */
/* flushbuf: On output stream write all unwritten data;
 * set the ptr to the beginning of the buffer; write the char to the beginning of the buffer*/
int _flushbuf(int x, FILE *fp) {
	
	int bufsize = 1;
	int num;

	int cond; 
	if (fp->flag._WRITE == 0 | fp->flag._EOF == 1 | fp->flag._ERR == 1)
		return EOF;
	//bufsize = (fp->flag._UNBUF) ?  1 : BUFSIZ;
	if (fp->base == NULL) {
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	}
	else {
		num = fp->ptr - fp->base;
		if ((write(fp->fd, fp->base, num)) != num) {
			fp->flag._ERR = 1;
			return EOF;
		}
	}
	fp->ptr = fp->base;
	fp->cnt = bufsize - 1;
	*fp->ptr = (char) x;
	return *fp->ptr++;

}


/* ------------- FFLUSH --------------------------------------- */
/* fflush: On output stream cause any buffered but unwritten data to be written;
 * on an input stream the effect is undefined. It returns "EOF" for a write error, and zero otherwise.
 * fflush(NULL) flushes all output streams */
int fflush(FILE *fp) {
	
	if (fp != NULL && fp->flag._WRITE != 1)
		return 0;
	
	if (fp == NULL) {
		for (fp = _iob; fp < _iob + OPEN_MAX; fp++) 
			if (fp->flag._WRITE == 1 && fp->cnt > 0) 
				if ((write(fp->fd, fp->ptr, fp->cnt)) != fp->cnt) {
					fp->flag._ERR = 1;
					return EOF;
				}
	}
	else if (fp->cnt > 0)
		if (fp->cnt != write(fp->fd, fp->ptr, fp->cnt)) {
			fp->flag._ERR = 1;
			return EOF;
		}
	fp->ptr = fp->base;
	fp->cnt = 0;
	return 0;

}


/* ----------- FCLOSE -------------------------------------- */
/* fclose: flushes any unwritten data for stream, discards any unread buffered input, frees any automatically allocated buffer, then closes the stream.
 * It returns "EOF" if any errors occured, and zero otherwise. */
int fclose (FILE *fp) {  

	int cond;
	if (fp->flag._WRITE == 1) {
		if (fflush(fp) != 0)
			return EOF;
	}
	else {
		fp->cnt = 0;
		fp->ptr = fp-> base;
	}
	free(fp->base);
	fp->flag._WRITE = fp->flag._READ = fp->flag._EOF = 0;
	fp->flag._ERR = fp->flag._UNBUF = fp->fd = 0;
	close(fp->fd);
	return 0;
}




#endif

				
