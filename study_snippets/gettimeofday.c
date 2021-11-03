#include <sys/time.h>
#include <stdio.h>

// struct timeval {
// 	time_t		tv_sec;		/* seconds */
// 	suseconds_t	tv_usec;	/* microseconds */
// };

// struct timezone {
// 	int tz_minuteswest;		/* minutes west of Greenwich */
// 	int tz_dsttime;			/* type of DST correction */
// };

// gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);

int	main(void)
{
	struct timeval tv;
	struct timezone tz;


	gettimeofday(&tv, &tz);

	printf("seconds = [%ld]\n", tv.tv_sec);
	printf("microseconds = [%ld]\n", tv.tv_usec);
	// printf("minutes west of Greenwich = [%d]\n", tz->tz_minuteswest);
	// printf("dst correction = [%d]\n", tz->tz_dsttime);
	long int yearsize = 31556926;
	long int monthsize = 2629743;
	long int daysize = 86400;
	long int hoursize = 3600;


	long int years = tv.tv_sec / yearsize + 1970;
	printf("years = [%ld]\n", years);

	// long int seconds = tv.tv_sec - ((years - 1970) * yearsize);
	long int seconds = tv.tv_sec % yearsize;
	long int month = seconds / monthsize + 1;
	printf("month = [%ld]\n", month);

	// seconds = seconds - ((month - 1) * monthsize);
	seconds = tv.tv_sec % monthsize; 
	long int day = seconds / daysize + 1;
	printf("day = [%ld]\n", day);

	// seconds = seconds - ((day - 1) * daysize);
	seconds = tv.tv_sec % daysize; 
	long int hour = seconds / hoursize;
	printf("hour = [%ld]\n", hour);

	// seconds = seconds - (hour * hoursize);	
	seconds = tv.tv_sec % hoursize;
	long int min = seconds / 60;
	printf("min = [%ld]\n", min);

	// seconds = seconds % 60;
	seconds = tv.tv_sec % 60;
	printf("seconds = [%ld]\n", seconds);

}