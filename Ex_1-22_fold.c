/* Exercise 1-22. Write a progam to "fold" long input lines into two or more shorter lines after the last non-blank character occurs before the n-th column of input.
 * Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column. */

#include <stdio.h>
#define MAXCHAR 1000
#define MAXBUFFER 50000
#define NEW_LINE_SIZE 57

int xgetline(char line[], int lim);
void fold(char line[], int lenght);
void cat_strings(char to[], char from[]);

int main(void) {

	char line[MAXCHAR];
	char buffer[MAXBUFFER];
	int len;

	while ((len = xgetline(line, MAXCHAR)) > 0)
		cat_strings(buffer, line);

	printf("\n");
	fold(buffer, NEW_LINE_SIZE);
	if (line[len-1] != '\n')
		printf("\n");
	return 0;
}

#define IN   1	/* inside word */
#define OUT  0	/* outside word */

/* fold: fold long lines into smaller of length "size" */
void fold(char s[], int new_size) {

	int number_of_words = 0;	/* number of words in the line */
	int start_word_index = 0;	/* index of the beginning of the last word */
	int cond = OUT;			/* if current position is inside a word */
	int len = 0;			/* length of the current line */
	int i = 0;			/* index for line processing */

	while (s[i] != '\0') {

		/* part that deal with chars that are at the position closer than "new_size" */
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
			if (cond == IN) 
				for (; start_word_index < i; ++start_word_index)
					putchar(s[start_word_index]);
			if (s[i] == '\n') 
				s[i] = ' ';
			putchar(s[i]);
			cond = OUT;
		}
		else {
			if (cond == OUT) {
				start_word_index = i;
				++number_of_words;
			}
			cond = IN;
		}
		++i;
		++len;
		
		/* Part that deal with exceeded size */
		if (len >= new_size) {		
			len = 0;
			if (cond == OUT)
				printf("\n");
			else if (number_of_words > 1) {
				i = start_word_index;
				printf("\n");
			}
			else if (number_of_words == 1) {
				for (; start_word_index < i; ++start_word_index)
					putchar(s[start_word_index]);
				if (s[i] != '\n' && s[i] != '\t' && s[i] != ' ') {
					printf("-\n-");
					++len;
				}
			}
			number_of_words = 0;
			cond = OUT;
		}
	}
	if (len == start_word_index && len > 0)
		printf("%s", s+i-len+1);
}

/* xgeltine: get a line into string s, return length of the line */
int xgetline(char s[], int lim) {

	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* cat_strings: concatenate t to end of s; s must be big enough */
void cat_strings(char s[], char t[]) {

	int i, j;

	i = j = 0;
	while (s[i] != '\0')	/* find end of s */
		i++;
	while ((s[i++] = t[j++]) != '\0') /* copy t */
		;
}
