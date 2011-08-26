/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 14:13:17 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int chown(const char *path, uid_t owner, gid_t group);
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc < 4){
		fprintf(stderr, "usage: %s <filename> <uid> <gid>\n", argv[0]);
		exit(1);
	}

	uid_t uid;
	gid_t gid;
	//unsigned long int strtoul(const char *nptr, char **endptr, int base);
	uid = (uid_t)strtoul(argv[2], NULL, 10);
	gid = (gid_t)strtoul(argv[3], NULL, 10);

	//int chown(const char *path, uid_t owner, gid_t group);
	if(chown(argv[1], uid, gid) < 0){
		fprintf(stderr, "change %s own failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "change %s own success\n", argv[1]);
	}

	return 0;
}
