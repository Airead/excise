/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 28 09:41:34 CST			*
 ********************************************************
 *		after studying C 41 days		*
 *		after studying APUE 6 days		*
 ********************************************************/

/*
 * This program implement `mv' simple function of GNU/Linux
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int arg_max;

int rename_dif_filesystem(const char *oldpath, const char *newpath);
int rename_into_dir(const char *oldpath, const char *newpath);

int main(int argc, char *argv[])
{
	arg_max = sysconf(_SC_ARG_MAX);

	if(argc < 3){
		fprintf(stderr, "usage: %s <oldpath> <newpath>\n", argv[0]);
		exit(1);
	}
	
	//int rename(const char *oldpath, const char *newpath);
	if(rename(argv[1], argv[2]) < 0){
		//EXDEV:oldpath and newpath are not on the same mounted file system.
		if(errno == EXDEV){
			//int rename_dif_filesystem(const char *oldpath, const char *newpath);
			rename_dif_filesystem(argv[1], argv[2]);
		}else if(errno == EISDIR){ 
			//int rename_into_dir(const char *oldpath, const char *newpath);
			rename_into_dir(argv[1], argv[2]);
		}else{
			fprintf(stderr, "%s:%d: move file failed: %s\n",
				__FILE__, __LINE__, strerror(errno));
			exit(1);
		}
	}

	fprintf(stdout, "move %s to %s success\n", argv[1], argv[2]);

	return 0;
}

/*
 * make rename can across diffent file system
 * On success, zero is returned. On error, -1 is returned.
 */

int rename_dif_filesystem(const char *oldpath, const char *newpath)
{
	printf("rename_ex run\n");
}

int rename_into_dir(const char *oldpath, const char *newpath)
{
	char newpath_buf[arg_max + 1];
	char filename[arg_max + 1];
	char *p;		/* point file name str */

	/* get pointer of filename */
	memset(filename, 0, sizeof(filename));
	//char *strrchr(const char *s, int c);
	if((p = strrchr(oldpath, '/')) == NULL){
		strncpy(filename, oldpath, sizeof(filename) - 1);
	}else{
		strncpy(filename, p, sizeof(filename) - 1);
	}

	memset(newpath_buf, 0, sizeof(newpath_buf));
	//int snprintf(char *str, size_t size, const char *format, ...);
	snprintf(newpath_buf, arg_max, "%s/%s", newpath, filename);

	//int rename(const char *oldpath, const char *newpath);
	if(rename(oldpath, newpath_buf) < 0){
		fprintf(stderr, "%s:%d: move file failed: %s\n",
			__FILE__, __LINE__, strerror(errno));
		return errno;
	}
	
}
