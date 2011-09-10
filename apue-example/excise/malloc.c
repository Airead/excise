/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 05 20:05:55 CST			*
 ********************************************************
 *		after studying C 49 days		*
 *		after studying APUE 14 days		*
 ********************************************************/

/*
 * This program demonstrates functions
 * void *calloc(size_t nmemb, size_t size);
 * void *malloc(size_t size);
 * void free(void *ptr);
 * void *realloc(void *ptr, size_t size);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 10

int main(int argc, char *argv[])
{
	char *pmalloc;
	char *pcalloc;
	char *prealloc;
	int i;

	//void *malloc(size_t size);
	pmalloc = (char *)malloc(SIZE * sizeof(char));
	if(pmalloc == NULL){
		perror("malloc");
		exit(1);
	}
	fprintf(stdout, "pmalloc addr: %#08x\n", (int)pmalloc);
	for(i = 0; i < SIZE; i++){
		fprintf(stdout, "%4u", pmalloc[i]);
	}
	fprintf(stdout, "\n");

	//void *calloc(size_t nmemb, size_t size);
	pcalloc = (char *)calloc(SIZE, sizeof(char));
	if(pcalloc == NULL){
		perror("calloc");
		exit(1);
	}
	fprintf(stdout, "pcalloc addr: %#08x\n", (int)pcalloc);
	for(i = 0; i < SIZE; i++){
		fprintf(stdout, "%4u", pcalloc[i]);
	}
	fprintf(stdout, "\n");

	//void *realloc(void *ptr, size_t size);
	prealloc = realloc(pcalloc, 2 * SIZE * sizeof(char));
	if(prealloc == NULL){
		perror("realloc");
		exit(1);
	}else{
		pcalloc = NULL;
	}
	fprintf(stdout, "prealloc addr: %#08x\n", (int)prealloc);
	for(i = 0; i < 2 * SIZE; i++){
		fprintf(stdout, "%4u", prealloc[i]);
	}
	fprintf(stdout, "\n");

	//void free(void *ptr);
	free(prealloc);
	free(pmalloc);

	return 0;
}
