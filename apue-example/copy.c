/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 24 15:20:06 CST			*
 ********************************************************
 *		after studying C 37 days		*
 *		after studying APUE 2 days		*
 ********************************************************/

/*
 * This program can copy a file to another file
 * with a same permission
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 2048

#if 0
struct stat {
	dev_t     st_dev;     /* ID of device containing file */
	ino_t     st_ino;     /* inode number */
	mode_t    st_mode;    /* protection */
	nlink_t   st_nlink;   /* number of hard links */
	uid_t     st_uid;     /* user ID of owner */
	gid_t     st_gid;     /* group ID of owner */
	dev_t     st_rdev;    /* device ID (if special file) */
	off_t     st_size;    /* total size, in bytes */
	blksize_t st_blksize; /* blocksize for file system I/O */
	blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
	time_t    st_atime;   /* time of last access */
	time_t    st_mtime;   /* time of last modification */
	time_t    st_ctime;   /* time of last status change */
};
#endif

int main(int argc, char *argv[])
{
	int fd;
	int newfd;
	struct stat stat;
	char buf[BUFSIZE];
	ssize_t readbytes;
	ssize_t writebytes;

	if(argc < 3){
		fprintf(stderr, "uasge: %s <soucrefile> <targetfile>\n", argv[0]);
		exit(1);
	}
	
	//step 1. open source file
	//int open(const char *pathname, int flags, mode_t mode);
	if((fd = open(argv[1], O_RDONLY)) < 0){
		perror("open source file error: ");
		exit(1);
	}
	
	//step 1.5 get source file mode
	//int fstat(int fd, struct stat *buf);
	if(fstat(fd, &stat) < 0){
mode		perror("fstat error: ");
		exit(1);
	}
	fprintf(stdout, "mode = %u\n", stat.st_mode);

	//step 2. open target file
	//int open(const char *pathname, int flags, mode_t mode);
	if((newfd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, stat.st_mode)) < 0){
		perror("create target file error: ");
		exit(1);
	}else{
		fprintf(stdout, "create target file success\n");
		
	}

	//step 3. read source write target
	// ssize_t read(int fd, void *buf, size_t count);
	while((readbytes = read(fd, buf, sizeof(buf))) != 0){
		/* read file */
		if(readbytes < 0){
			perror("read error: ");
			exit(1);
		}else{
			fprintf(stdout, "read %d bytes\n", (int)readbytes);
		}
		/* write file */
		//ssize_t write(int fd, const void *buf, size_t count);
		if((writebytes = write(newfd, buf, readbytes)) < readbytes){
			fprintf(stderr, "write less than read\n");
			exit(1);
		}else{
			fprintf(stdout, "write %d bytes\n", writebytes);
		}
	}

	//step 4. colse file
	close(fd);
	close(newfd);

	return 0;
}
