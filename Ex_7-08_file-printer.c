/* Exercise 7-8. Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 57
#define MAXCHARS 234

int getstr(FILE *, char *, int);
int main(int argc, char *argv[]) {

	int page = 0, strl;
	long lineno;
	FILE *fp;
	char *prog = *argv;
	char line[MAXCHARS];
	if (argc == 1) {
		printf("No files specifed, exiting\n");
		exit(1);
	}
	while (--argc > 0) {
		if ((fp = fopen(*++argv, "r")) == NULL)
				fprintf(stderr," %s: can't open %s\n", prog, *argv);
		else {
			strl = (int)(strlen(*argv)/2);
			printf("%*s%*d", 119 + strl, *argv, 115 - strl, ++page);
			printf("\n\n");
			lineno = 2;
			while ((getstr(fp, line, MAXCHARS)) != -1) {
				printf("%s\n", line);
				if ((++lineno) % MAXLINES == 0) {
					printf("%234d\n\n", ++page);
					lineno = 2;
				}
			}
			for (; lineno < MAXLINES; ++lineno)
				printf("\n");
		}
	}
	if (page == 0 && lineno == 0)
		exit(1);
	exit(0);
}

int getstr(FILE *ifp, char *s, int lim) {

	while ((*s = getc(ifp)) != '\n' && *s != EOF && --lim > 0)
		++s;
	if (*s != EOF) {
		if (*s == '\n')
			*s = '\0';
		else
			*++s = '\0';
		return 0;
	}
	return -1;
}


			

				



