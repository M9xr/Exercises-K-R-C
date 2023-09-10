/* Exercise 5-08. There is no error checking in "day_of_year" or "month_day". Remedy this defect. */
/* Exercise 5-09. Rewrite the routines "day_of_year" and "month_day" with pointers instead of indexing. */

#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {

	int leap, i;
	char *p2;
        
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if ((month < 1 || month > 12) || (day < 1 || day > 31) || (day > 30 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)) || \
                        (leap && month == 2 && day > 29) || (!leap && month == 2 && day > 28))
                return -1;
	       
       	p2 = &daytab[leap][1];

	for (i = 0; ++i < month; ++p2) 
		day += *p2;
	return day;
}

/* month_day: set month and day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {

	int i, leap;
	char *p2;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if (yearday < 1 || (leap && yearday > 366) || (!leap && yearday > 365))
        	return;

	p2 = &daytab[leap][1];

	for (i = 1; yearday > *p2; ++i) 
		yearday -= *p2++;
	*pmonth = i;
	*pday = yearday;
}

int main(void) {

	int yearday1, month1, year1, yearday2, month2, year2, day1, day2;
	

	yearday1 = day_of_year(2000, 3, 6);
	yearday2 = day_of_year(2001, 3, 6);
       	month_day(2023, 60, &month1, &day1);
       	month_day(2024, 60, &month2, &day2);
	if (yearday1 < 0 || yearday2 < 0) {
		printf("Error, wrong values\n");
		return -1;
	}
	printf("year day of 03/06/2000 is:%d\nyear day of 03/06/2001 is:%d\n\n", yearday1, yearday2);
	printf("for 60th day of 2023 the month is:%d the day is:%d\nfor 60th day of 2024 the month is:%d the day is:%d\n", month1, day1, month2, day2);

	return 0;
}	

	
