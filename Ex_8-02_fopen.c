/* Exercise 8-2. Rewrite "fopen" and "_fillbuf" with fields instead of explicit bit operations.
 * Compare code size and execution speed. */

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20	/* max #files open at once */

typedef struct _ibuf {
	int cnt;	/* characters lef */
	char *ptr;	/* next character position */
	char *base;	/* location of the buffer */
	struct {
		unsigned int _READ  : 1;
		unsigned int _WRITE : 1;
		unsigned int _UNBUF : 1;
		unsigned int _EOF   : 1;
		unsigned int _ERR   : 1;
	} flag;		/* mode of files access */
	int fd;		/* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];	// extern _iob can be declared without array size specified. It is defined later, but just below it is used in #define, so declaration here is mandatory.

#define stdin (&_iob[0])	// &_iob - means adress of iob. 
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)		(((p)->flag & _EOF) != 0)
#define ferror(p)	(((p)->flag & _ERR) != 0)
#define fileno(p)	((p)->fd)

#define getc(p)    (--(p)->cnt >= 0 \
		? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)  (--(p)->cnt >= 0 \
		? *(p)->ptr++ = (x) : _flushbuf((x),p))

/* ------------------END OF IO LIBRARY -------------------*/


/* ----------------- FOPEN ----------------- */
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

/* ------------ END FOPEN ------------- */


/* ------------ _FILLBUF -------------- */

#include <stdlib.h>

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp) {

	int bufsize;

	if (fp->flag._READ != 1)
		return EOF;
	bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL)	/* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;	/* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag._EOF = 1;
		else
			fp->flag._ERR = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

FILE _iob[OPEN_MAX] = {		/* stdin, stdout, stderr */
	{ 0, (char *) 0, (char *) 0, 1, 0, 0, 0, 0, 0},
	{ 0, (char *) 0, (char *) 0, 0, 1, 0, 0, 0, 1},
	{ 0, (char *) 0, (char *) 0, 0, 0, 0, 1, 1, 2}
};


int main(int argc, char *argv[]) {

	FILE *fp;
	char buf[1];
	int cond;

	while (--argc > 0) {
		if ((fp = fopen(*++argv, "w")) == NULL) {
			cond = write(1, "Couldn't create file\n", 22);
			return -1;
		}
		else
			while ((buf[0] = getc(&_iob[0])) != EOF)
				if ((cond = write(fp->fd, buf, 1)) == -1)
					return -1;
	}
	return 0;
}



				
