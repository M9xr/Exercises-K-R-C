/* Exercise 5-8. There is no error checking in "day_of_year" or "month_day". Remedy this defect. */
/* Exercise 5-9. Rewrite the routines "day_of_year" and "month_day" with pointers instead of indexing. */

#include <stdio.h>

static int daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year (int, int, int);
void month_day (int, int, int *, int *);

int main (void) {

	int dyear, dyear2, pmon, pmon2, pda, pda2;
	
	dyear = day_of_year(1992, 3, 17);
	dyear2 = day_of_year (2024, 6, 6);
	month_day(2015, 150, &pmon, &pda);
	month_day(2016, 120, &pmon2, &pda2);
	printf("day_of_year (1992.3.17PL) = %d\nday_of_year2 (2024.06.06PL) = %d\n2015(150):%d.%d 2016(120):%d.%d\n", dyear, dyear2, pda, pmon, pda2, pmon2);
	
	return 0;
}
/* day_of_year: set day of year from month & day */
int day_of_year (int year, int month, int day) {


	int i, leap, *p1;
	leap = year % 4 == 0  && year % 100 != 0 || year % 400 == 0;
	
	if ((month < 1 || month > 12) || (day < 1 || day > 31) || (day > 30 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)) || \
			(leap && month == 2 && day > 29) || (!leap && month == 2 && day > 28))
		return -1;

	p1 = (leap == 0) ? &daytab[0][1] : &daytab[1][1];
	for (i = 1; i < month; i++)
		day += *p1;
	return day;
}

/* month_day: set month, day from day of year */
void month_day (int year, int yearday, int *pmonth, int *pday) {

	int i, leap, *p1;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	if (yearday < 1 || (leap && yearday > 366) || (!leap && yearday > 365))
			return;

	p1 = (leap == 0) ? &daytab[0][1] : &daytab[1][1];

	for (i = 1; yearday > *(p1+i); i++)
		yearday -= *(p1+i);
	*pmonth = i;
	*pday = yearday;
}
