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
int rename_into_dir(const char *oldpath, char *newpath);
char *get_file_name(const char *path, char *filename);
char *get_newpath(const char *oldpath, char *newpath);

int main(int argc, char *argv[])
{
	arg_max = sysconf(_SC_ARG_MAX);

	if(argc < 3){
		fprintf(stderr, "usage: %s <oldpath> <newpath>\n", argv[0]);
		exit(1);
	}

	char oldpath[arg_max + 1];
	char newpath[arg_max + 1];

	memset(oldpath, 0, arg_max + 1);
	memset(newpath, 0, arg_max + 1);
	
	//char *strncpy(char *dest, const char *src, size_t n);
	strncpy(oldpath, argv[1], arg_max);
	strncpy(newpath, argv[2], arg_max);
	
	//int rename(const char *oldpath, const char *newpath);
	if(rename(oldpath, newpath) < 0){
		if(errno == EACCES){
			perror("move file failed");
			exit(1);
		}else if(errno == EXDEV){
			//int rename_dif_filesystem(const char *oldpath, const char *newpath);
			if(rename_dif_filesystem(oldpath, newpath) == 0){
				goto success;
			}
		}

		errno = 0;
		
		//char *get_newpath(const char *oldpath, char *newpath);
		get_newpath(oldpath, newpath);

		if(rename(oldpath, newpath) < 0){
			//EXDEV:oldpath and newpath are not on the same mounted file system.
			if(errno == EXDEV){
				//int rename_dif_filesystem(const char *oldpath, const char *newpath);
				rename_dif_filesystem(oldpath, newpath);
			}else{
				perror("move file failed");
				exit(1);
			}
		}
	}

success:
	fprintf(stdout, "move %s to %s success\n", oldpath, newpath);

	return 0;
}

/*
 * make rename can across diffent file system
 * On success, zero is returned. On error, -1 is returned.
 */

int rename_dif_filesystem(const char *oldpath, const char *newpath)
{
	printf("rename_ex run\n");

	return 0;
}

/*
 * get filename of path
 */
char *get_file_name(const char *path, char *filename)
{
	char *p;		/* point file name str */

	/* get pointer of filename */
	memset(filename, 0, arg_max + 1);
	//char *strrchr(const char *s, int c);
	if((p = strrchr(path, '/')) == NULL){
		strncpy(filename, path, arg_max);
	}else{
		strncpy(filename, p + 1, arg_max + 1);
	}

	return filename;
}

/*
 * get new path
 */
char *get_newpath(const char *oldpath, char *newpath)
{
	char filename[arg_max + 1];
	char newpath_buf[arg_max + 1];

	//char *get_file_name(const char *path, char *filename);
	get_file_name(oldpath, filename);

	memset(newpath_buf, 0, arg_max + 1);
	
	if(newpath[strlen(newpath) - 1] == '/'){
		//int snprintf(char *str, size_t size, const char *format, ...);
		snprintf(newpath_buf, arg_max, "%s%s", newpath, filename);
	}else{
		//int snprintf(char *str, size_t size, const char *format, ...);
		snprintf(newpath_buf, arg_max, "%s/%s", newpath, filename);
	}
	
	//char *strncpy(char *dest, const char *src, size_t n);
	strncpy(newpath, newpath_buf, arg_max);

	return newpath;
}
