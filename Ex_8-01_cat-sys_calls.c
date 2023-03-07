/* Exercise 8-1. Rewrite the program "cat" from Chapter 7 using "read", "write", "open" and "close" instead of their standard library equivalents.
 *  Perform experiments to determine the relative speed of the two versions. */

#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void error(char *fmt, ...);

#define BUFSIZE 8192

int main(int argc, char *argv[]) {

	int fd, n;
	char *prog = argv[0];	/* program name for errors */
	char buf[BUFSIZE];

	if (argc == 1) {
		while ((n = read(0, buf, BUFSIZE)) > 0) 
			if (write(1, buf, n) != n)
				error("cat: error during writing to stdout");
	}
	else {
		while (--argc > 0) {
			printf("Test1\n");
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				printf("Test3\n");
				error("cat: cannot open file %s", *argv);
			}
			while ((n = read(fd, buf, 1)) > 0) {
				printf("Test2\n");
				if (write(1, buf, n) != n)
					error("cat: cannot write stdout");
			}
			printf("Test4 fd = %d\tn:%d\n", fd, n);
			close(fd);
		}
	}

			      	       

	return 0;
}


/* error: print an error message and die */
void error(char *fmt, ...) {

	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}
