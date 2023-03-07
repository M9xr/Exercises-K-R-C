#include <stdio.h>
#define swap(t,x,y) { t temp; temp = x, x = y, y = temp; }

int main (void) {

	double a = 52.1, b = 823.22, c = 1230;
	int g = 23, o = 134, i = 21311;
	printf("a1=%g b1=%g c1=%g\n", a, b, c);
	swap(double, a, c);
	printf("a2=%g b2=%g c2=%g\n", a,b,c);
	printf("g=%d o=%d i=%d\n", g, o, i);
	swap(int, o, i);
	printf("g=%d o=%d i=%d\n", g, o, i);
	int aa1 = 666;
	int bb1 = 13;
	printf("\naa1=%d\tbb1=%d\n", aa1, bb1);	
	swap (int, aa1, bb1);
	printf("\naa1=%d\tbb1=%d\n", aa1, bb1);	

}
