/* Exercise 7-6. Write a program to compare two files, printing the first line where they differ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getstr(FILE *, char *, int);

#define MAXCHARS 300

int main(int argc, char *argv[]) {

	FILE *fp, *fp2;
	char string1[MAXCHARS], string2[MAXCHARS];
	char *prog = *argv;

	if (argc != 3) {
		fprintf(stderr, "%s: name of two files needed, terminating\n", prog);
		exit(1);
	}
	else {
		if ((fp = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "%s: can't open \"%s\"\n", prog+10, *argv);
		}
		if ((fp2 = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "%s: can't open \"%s\"\n", prog+10, *argv);
		}
		if (fp == NULL || fp2 == NULL)
			exit(1);
	}
	int cond1 = 0, cond2 = 0, cond3 = 0, line = 0;
	while (cond1 != -1 || cond2 != -1) {
		cond1 = getstr(fp, string1, MAXCHARS);
		cond2 = getstr(fp2, string2, MAXCHARS);
		++line;
		if ((strcmp(string1, string2)) != 0) {
			cond3 = 1;
			printf("FILE 1 LINE %d:\n%s\nFILE 2 LINE %d:\n%s\n", line, string1, line, string2);
			break;
		}
	}
	if (cond3 == 0)
		printf("%s: No difference between files.\n", prog+10);
	fclose(fp);
	fclose(fp2);

	exit(0);
}

int getstr(FILE *ifp, char *s, int lim) {

	while ((*s = getc(ifp)) != '\n' && *s != EOF && --lim > 0)
		++s;
	if (*s != EOF){
		*++s = '\0';
		return 0;
	}
	return -1;
}

		


