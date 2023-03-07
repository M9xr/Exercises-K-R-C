/* Exercise 1-11. How would you test the word count progarm? What kinds of input are most likely to uncover bugs if there are any? */
// I would check wheter conditions inside while's body are evaluated properly. The inputs to check are: space, tab, newline. All inputs to check should be put between some words.

#include <stdio.h>

#define IN   1		/* inside a word */
#define OUT  0		/* outside a word */

/* count lines, words, and characters in input */
int main(void) {

	int c, nl, nw, nc, state;

	state = OUT;
	nl = nw = nc = 0;
	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {	// it is the same as: else "\n" if (state =...) but it doesn't take two lines.
			state = IN;		             
			++nw;				
		}
	}
	printf("%d %d %d\n", nl, nw, nc);
}


