#include <stdio.h>
#include <string.h>
#include <errno.h>

/* char *strerror(int errnum); 
/* void perror(const char *s);
* const char *sys_errlist[];
* int sys_nerr;
* int errno;
*/

int main(void)
{
	int i;

	for(i = 0; i < 131; i++){
		printf("%4d: %s\n", i, strerror(i));
	}
//	errno = EACCES;
	printf("perror: ");
	perror("hahahaha");
	return 0;
}
