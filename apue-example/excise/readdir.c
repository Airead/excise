/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 27 09:40:58 CST			*
 ********************************************************
 *		after studying C 40 days		*
 *		after studying APUE 5 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * read contents of directory
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <path>\n", argv[0]);
		exit(1);
	}
	
	DIR *dirp;

	//DIR *opendir(const char *name);
	if((dirp = opendir(argv[1])) < 0){
		fprintf(stderr, "opendir %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "opendir %s success\n", argv[1]);
	}
	
	fprintf(stdout, "NAME_MAX = %d\n", NAME_MAX);

	/* struct dirent {
	 * 	ino_t          d_ino;       inode number
	 * 	off_t          d_off;       offset to the next dirent
	 * 	unsigned short d_reclen;    length of this record
	 * 	unsigned char  d_type;      type of file; not supported
	 * 				    by all file system types
	 * 	char           d_name[256]; filename
	 * };
	 */
	struct dirent *de;

	errno = 0;
	//struct dirent *readdir(DIR *dirp);
	while((de = readdir(dirp)) != NULL){
		fprintf(stdout, "%s\n", de->d_name);
	}
	if(errno != 0){
		fprintf(stderr, "readdir %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	
	//int closedir(DIR *dirp);
	closedir(dirp);

	return 0;
}
