/* Exercise 2-1. Write a program to determine the ranges of "char", "short", "int", and "long" variables, both "signed", and "unsigned", by printing apropriate values from standard headers and by direct computation. 
 * Harder if you compute them: determine the ranges of the various floating-point types. */

#include <stdio.h>
#include <limits.h>
#include <float.h>


int main(void) {

	signed char schar = -2;
	signed short sshort = -2;
	signed int sint = -2;
	signed long slong = -2;
	
	signed long i2 = -2;
	unsigned long i1 = 2;

printf("----------------------COMPUTED----------------------\n");
	while (schar == i2) {
		i2 *= 2;
		schar *= 2;
	}
	printf("\tmin signed char = %ld\n", i2/2);
	printf("\tmax signed char = %ld\n", (-i2/2) - 1);
	printf("\tmax unsigned char = %ld\n\n", -i2);

	i2 = -2;
	while (sshort == i2) {
		i2 *= 2;
		sshort *= 2;
	}
	printf("\tmin signed short = %ld\n", i2/2);
	printf("\tmax signed short = %ld\n", (-i2/2) -1);
	printf("\tmax unsigned short = %ld\n\n", -i2-1);


	i2 = -2;
	while (sint == i2) {
		i2 *= 2;
		sint *= 2;
	}
	printf("\tmin signed int = %ld\n", i2/2);
	printf("\tmax signed int = %ld\n", (-i2/2) -1);
	printf("\tmax unsigned int = %lu\n\n", -i2-1);

	i2 = -4;
	while (slong == (i2 / 2)) {
		i2 *= 2;
		slong *= 2;
	}
	printf("\tmin signed long = %ld\n", slong);
	printf("\tmax signed long = %ld\n", -slong -1);
	slong = -slong;
	long unsigned ulong = slong;
	--ulong; 
	printf("\tmax unsigned long = %lu",2*ulong + 1);

printf("\n----------------------COMPUTED----------------------\n\n");
	
printf("\n----------------------REAL----------------------\n");


	printf("\tschar_min = %d\n\tschar_max = %d\n"
	       "\tuchar_max = %d\n\n"
	       "\tsshor_min = %d\n\tsshort_max = %d\n"
	       "\tushort_max = %d\n\n"
	       "\tsint_min = %d\n\tsint_max = %d\n"
	       "\tuint_max = %u\n\n"
	       "\tslong_min = %ld\n\tslong:max = %ld\n"
	       "\tulong_max = %lu", SCHAR_MIN, SCHAR_MAX, UCHAR_MAX, SHRT_MIN, SHRT_MAX, USHRT_MAX, INT_MIN, INT_MAX,
	       UINT_MAX, LONG_MIN, LONG_MAX, ULONG_MAX);


printf("\n----------------------REAL----------------------\n\n");


printf("\n-----------------------FLOATS------------------------\n");

	float float1 = 1;
	float float2 = 2;
	float float3 = 0.1;
	double double1 = 1;
	double double2 = 2;
	double double3 = 0.1;
	long double longdouble1 = 1;
	long double longdouble2 = 2;
	long double longdouble3 = 0.1;
	
	while (float1 * 2 == float2 && float2 / 2 != float2) {
		float1 *= 2;
		float2 *= 2;
	}
	printf("\tmax_float cecha = %g\n", float1);
	float1 = 1;
	while (float3 * 0.1 < float3) {
		float1 *= 0.1;
		float3 *= 0.1;
	}
	printf("\tmin_float mantysta = %g\n\n", float1);
	
	while (double1 * 2 == double2 && double2 / 2 != double2) {
		double1 *= 2;
		double2 *= 2;
	}
	printf("\tmax_double cecha = %g\n", double1);

	double1 = 1;
	while (double3 * 0.1 < double3) {
		double1 *= 0.1;
		double3 *= 0.1;
	}
	printf("\tmin_double mantysta = %g\n\n", double1);


	while (longdouble1 * 2 == longdouble2 && longdouble2 / 2 != longdouble2) {
		longdouble1 *= 2;
		longdouble2 *= 2;
	}
	printf("\tmax_long_double cecha = %Lg\n", longdouble1);

	longdouble1 = 1;
	while (longdouble3 * 0.1 < longdouble3) {
		longdouble1 *= 0.1;
		longdouble3 *= 0.1;
	}
	printf("\tmin_long_double mantysta = %Lg", longdouble1);



printf("\n-----------------------FLOATS------------------------\n\n");
printf("\n-----------------------REAL FLOATS------------------------\n");

	printf("\tmin_float = %e\n\tmax_float = %g\n\n\t"
	       "min_double = %g\n\tmax_double = %g"
	       , FLT_MIN, FLT_MAX, DBL_MIN, DBL_MAX);

printf("\n-----------------------REAL FLOATS------------------------\n");
	return 0;
}


