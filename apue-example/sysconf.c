#include <unistd.h>
#include <stdio.h>


/* POSIX allows an application to test at compile or run time whether certain
 * options are supported, or what the value is of certain configurable constants or
 * limits.  
 * At compile time this is done by including <unistd.h> and/or <limits.h>
 * and testing the value of certain macros. 
 */

int main(void)
{
/* long sysconf(int name); */
	printf("ARG_MAX = %d\n", _SC_ARG_MAX);
/* CHILD_MAX - _SC_CHILD_MAX
 * The max number of simultaneous processes per user ID.  Must  not
 * be less than _POSIX_CHILD_MAX (25).
 */	printf("CHILD_MAX = %d\n", _SC_CHILD_MAX);
/* OPEN_MAX - _SC_OPEN_MAX
 * The  maximum number of files that a process can have open at any
 * time.  Must not be less than _POSIX_OPEN_MAX (20).
 */
	printf("OPEN_MAX = %d\n", _SC_OPEN_MAX);
/* _POSIX_VERSION - _SC_VERSION
 * indicates the year and month the POSIX.1 standard  was  approved
 * in  the  format  YYYYMML;  the value 199009L indicates the Sept.
 * 1990 revision.
 */
	printf("_POSIX_VERSION = %d\n", _SC_VERSION);
        
	return 0;
}
