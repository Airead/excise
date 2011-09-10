/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 10 16:52:09 CST			*
 ********************************************************
 *		after studying C 54 days		*
 *		after studying APUE 19 days		*
 ********************************************************/

#include <stdio.h>
#include <string.h>

#if 0
一月份＝JAN.      Jan.=January
二月份＝FEB.      Feb.=February
三月份＝MAR.      Mar.=March 
四月份＝APR.      Apr.=April 
五月份＝MAY       May=May
六月份＝JUN.      Jun.=June
七月份＝JUL.      Jul.=July
八月份＝AUG.      Aug.=August 
九月份＝SEP.      Sept.=September
十月份＝OCT.      Oct.=October
十一月份＝NOV.    Nov.=November
十二月份＝DEC.    Dec.=December   
#endif
	int main(int argc, char *argv[])
{
	char *strs[] = { "Jan.=January",
			 "Feb.=February",
			 "Mar.=March",
			 "cut",
			 "Apr.=April",
			 "May=May",	   
			 "Jun.=June",	  
			 "cut",
			 "Jul.=July",	  
			 "Aug.=August", 	  
			 "Sept.=September", 
			 "cut",
			 "Oct.=October",	  
			 "Nov.=November",	  
			 "Dec.=December",
			 NULL};


	fprintf(stdout, "-------------------------show string-------------------------\n");
	char **p;

	p = strs;
	while(*p != NULL && p != NULL){
		fprintf(stdout, "%s\n", *p);
		p++;
	}

	fprintf(stdout, "-------------------------attempt to split-------------------------\n");
	p = strs;
	while(*p != NULL && p != NULL){
		if(strcmp(*p, "cut") == 0){
			fprintf(stdout, "(null)\n");
		}else{
			fprintf(stdout, "%s\n", *p);
		}
		p++;
	}

#if 0
	fprintf(stdout, "-------------------------split and store witd subnum-------------------------\n");
	char *cuted[100][100];
	int i;
	int j;
	int count;

	i = 0; p = strs; count = 0;
	while(*p != NULL && p != NULL){
		j = 0;
		while(*p != NULL && strcmp(*p, "cut") != 0){
			cuted[i][j++] = *p;
			p++;
		}
		i++;
		count ++;
		if(*p != NULL){
			*p++ = NULL;
		}
	}
	cuted[i][0] = NULL;
	fprintf(stdout, "count = %d\n", count);

	for(i = 0; i < count; i++){
		j = 0;
		while(cuted[i][j] != NULL)
			fprintf(stdout, "[%d]%s\n", i, cuted[i][j++]);
	}
#endif
	fprintf(stdout, "-------------------------split and store with pointer-------------------------\n");
	char *cuted[100][100];
	int i;
	char *((*q)[100]);
	char **s;

	i = 0; p = strs;  
	q = cuted;
	while(*p != NULL && p != NULL){
		s = *q;
		while(*p != NULL && strcmp(*p, "cut") != 0){
			*s++ = *p;
			p++;
		}
		q++;
		if(*p != NULL){
			*p++ = NULL;
		}
	}
	*q[0] = NULL;

	q = cuted; i = 0;
	while(*q[0] != NULL){
		s = *q;
		
		while(*s != NULL){
			fprintf(stdout, "[%d]%s\n", i, *s);
			s++;
		}
		i++;
		q++;
	}

	return 0;
}
