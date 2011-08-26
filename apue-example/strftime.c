/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 21:07:22 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * size_t strftime(char *s, size_t max, const char *format,
 *                 const struct tm *tm);
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char s[1024];
	char fstr[] = "aAbBcCdDeEFGghHIjklmMnOpPrRsStTuUVwWxXyYzZ+%";
	int i;
	struct tm t;
	char buf[10];
	
	t.tm_year = 2012 - 1900;
	t.tm_mon = 12 - 1;
	t.tm_mday = 21;
	t.tm_hour = 23;
	t.tm_min = 59;
	t.tm_sec = 59;
	t.tm_isdst = -1;

	//time_t mktime(struct tm *tm);
	if(mktime(&t) < 0){
		fprintf(stderr, "mktime error\n");
	}

	fprintf(stdout, "time: 2012/12/21 23:59:59\n");
	
	for(i = 0; i < strlen(fstr); i++){
		//void *memset(void *s, int c, size_t n);
		memset(buf, 0, sizeof(buf));

		//int snprintf(char *str, size_t size, const char *format, ...);
		snprintf(buf, sizeof(buf) - 1, "%%%c", fstr[i]);
 
		//size_t strftime(char *s, size_t max, const char *format,
		//                const struct tm *tm);
		if(strftime(s, 1024 - 1, buf, &t) == 0){
			fprintf(stderr, "strftime error\n");
			exit(1);
		}
		fprintf(stdout, "%3s: %s\n", buf, s);
	}
	return 0;
}
