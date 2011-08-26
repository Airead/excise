/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 25 21:51:57 CST			*
 ********************************************************
 *		after studying C 38 days		*
 *		after studying APUE 3 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * how to show type(s) of file
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

void dump(struct stat *s);


/* struct stat {
 * 	dev_t     st_dev;     ID of device containing file
 * 	ino_t     st_ino;     inode number
 * 	mode_t    st_mode;    protection
 * 	nlink_t   st_nlink;   number of hard links
 * 	uid_t     st_uid;     user ID of owner
 * 	gid_t     st_gid;     group ID of owner
 * 	dev_t     st_rdev;    device ID (if special file)
 * 	off_t     st_size;    total size, in bytes
 * 	blksize_t st_blksize; blocksize for file system I/O
 * 	blkcnt_t  st_blocks;  number of 512B blocks allocated
 * 	time_t    st_atime;   time of last access
 * 	time_t    st_mtime;   time of last modification
 * 	time_t    st_ctime;   time of last status change
 * };
 */


int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	//step 1. get one file status
	struct stat s;
	
	int lstat(const char *path, struct stat *buf);
	if(lstat(argv[1], &s) < 0){
		fprintf(stderr, "get %s status failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	
	//step 2. print file types
	//void dump(struce stat *s)
	dump(&s);

	return 0;
}

/*
 * print mode to human read
 */
void dump(struct stat *s)
{
	/* | Macro         | Type of file           | Example                   |
	 * |---------------+------------------------+---------------------------|
	 * | S_ISREG()     | regular file           | hello.c                   |
	 * | S_ISDIR()     | directoryfile          | /                         |
	 * | S_ISCHR()     | character special file | stdin/stdout              |
	 * | S_ISBLK()     | block special file     | disk drives               |
	 * | S_ISFIFO()    | pipe or FIFO           | named pipe                |
	 * | S_ISLNK()     | symbolic link          | create by "$ ln -s"       |
	 * | S_ISSOCK()    | socket                 | for network communication |
	 * | S_TYPEISMQ()  | message queue          |                           |
	 * | S_TYPEISSEM() | semaphore              |                           |
	 * | S_TYPEISSHM() | shared memory object   |                           |
	 */
	
	if(S_ISREG(s->st_mode)){
		fprintf(stdout, "regular file\n");
	}    
	if(S_ISDIR(s->st_mode)){
		fprintf(stdout, "directory file\n");
	}    
	if(S_ISCHR(s->st_mode)){
		fprintf(stdout, "character file\n");
	}    
	if(S_ISBLK(s->st_mode)){
		fprintf(stdout, "block special file\n");
	}    
	if(S_ISFIFO(s->st_mode)){
		fprintf(stdout, "fifo\n");
	}   
	if(S_ISLNK(s->st_mode)){
		fprintf(stdout, "symbolic link\n");
	}    
	if(S_ISSOCK(s->st_mode)){
		fprintf(stdout, "socket\n");
	}     

	if(S_TYPEISMQ(s)){
		fprintf(stdout, "message queue\n");
	} 
	if(S_TYPEISSEM(s)){
		fprintf(stdout, "semaphore\n");
	}
	if(S_TYPEISSHM(s)){
		fprintf(stdout, "shared memory object\n");
	} 

}
