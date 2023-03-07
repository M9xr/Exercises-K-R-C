/* Exercise 1-6. Verify that the expression "getchar() != EOF" is 0 or 1 */

#include <stdio.h>

/* copy input to output; 2nd version */
int main() {

	int c;
	
	printf("In *while* loop:\n");
	while (c = getchar() != EOF) 
		printf("%d", c);
	printf("\nAfter *while* loop value of (c = getchar() != EOF) is: %d\n", c);
}



