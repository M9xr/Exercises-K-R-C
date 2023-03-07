#include <stdio.h>
void test(int);

int main () {
	
	char g;
	int c, i, value, set, end_value, j;
	unsigned long multi = 1;
	char number[20];
	i = set = 0;
	unsigned long decimal = 0;
	while ((c = getchar()) != EOF && set != 1) {
		if (c >= '0' && c <= '9') {
			g = c - '0';
			number[i] = g;
	       		++i; }
		else if (c >= 'A' && c <= 'F') {
			c = c - 'A' + 10;
			number[i] = c;
			++i; }
		else if (c >= 'a' && c <= 'f') {
			c = c - 'a' + 10;
			number[i] = c;
			++i; }
		else {
			set = 1;
	       		//test(2);
			--i;}
			 
	}	
		multi = 1;	
		for (j = i; j >= 0; j--) {
			//test(1);
	       		decimal = decimal + number [j] * multi; printf("\tvalue:%ld\tmulti:%ld\tnumber[j]:%d\n", decimal, multi, number[j]);
			multi = (multi * 16); }
	
		printf("The number is: %ld\n", decimal);
		return 0;
}
void test(int nomb) {
	printf("\n\t\tTest%d\n", nomb); 
}	

					
