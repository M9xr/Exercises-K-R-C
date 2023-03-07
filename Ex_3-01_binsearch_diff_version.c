/* Our binary search makes two test inside the loop, when one would suffice (at the price of more tests outside.) Write a version with only one test inside the loop and measure the difference in the run-time. */
#include <stdio.h>
#define MAXMAX 1250
int binsearch (int x, int v[], int n);
int main (void) {

	
	int result, x, n, i;
	x = 79;
	n = 322;
	int v[MAXMAX];
       for (i = 0; i < MAXMAX; ++i) {
       		v[i] = i; } 
	result = binsearch(x, v, n);
	printf("\nThe result is %d\n", result);
}

int binsearch (int x, int v[], int n) {

	int low, high, mid;
	low = 0;
	high = n - 1;
	mid = ((high+low)/2);
	while (low < (high) && mid != x) {
		if (x < v[mid]) {
			high = mid;
			mid = ((low+high)/2); 
			printf(" Value of high:%d Value of mid: %d\n", high, mid);}
		else {
			low = mid;
			mid = ((low+high)/2);
		       	printf(" Value of low: %d Value of mid: %d\n", low, mid);} 

		}
	printf("End Value of:\n\t      low: %d  high: %d  mid: %d\n", low, high, mid);
	if (mid == x) 
		return mid; 
	else 
		return -1;
}
