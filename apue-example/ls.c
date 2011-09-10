/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 27 11:07:51 CST			*
 ********************************************************
 *		after studying C 40 days		*
 *		after studying APUE 5 days		*
 ********************************************************/

/*
 * This program implement `ls -l' functions of GNU/Linux
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
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_file_info(char *filepath);
void print_file_permission(struct stat *buf);
void print_file_owner(struct stat *buf);
void print_file_group(struct stat *buf);
void print_file_time(struct stat *buf);

int main(int argc, char *argv[])
{
	int line_max = sysconf(_SC_LINE_MAX);
	char path[line_max + 1];
	
	fprintf(stdout, "%d\n", sizeof(path));
	
	memset(path, 0, sizeof(path));
	//step 0. get destination path
	if(argc < 2){
		strcpy(path, "./");
	}else{
		strcpy(path, argv[1]);
		if(path[strlen(path) - 1] != '/'){
			strcat(path, "/");
		}
	}
	
	//step 1. open a directory
	DIR *dirp;

	//DIR *opendir(const char *name);
	if((dirp = opendir(path)) == NULL){
		fprintf(stderr, "open %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	
	//step 2. read and show contents of directory one by one
	/* struct dirent {
         *        ino_t          d_ino;       inode number
         *        off_t          d_off;       offset to the next dirent
         *        unsigned short d_reclen;    length of this record
         *        unsigned char  d_type;      type of file; not supported
         *                                       by all file system types
         *        char           d_name[256]; filename
         *    };
	 */
	struct dirent *de;
	char filepath[line_max + 1];

	errno = 0;
	//struct dirent *readdir(DIR *dirp);
	while((de = readdir(dirp)) != NULL){
		/* get fullpath of file */
		memset(filepath, 0, sizeof(filepath));
		strncpy(filepath, path, line_max);
		
		/* fullpath too long */
		if(line_max < strlen(filepath) + strlen(de->d_name)){
			fprintf(stderr, "fullpath `%s%s' is too long\n", path, de->d_name);
			exit(1);
		}else{
			strncat(filepath, de->d_name, line_max - strlen(filepath));
		}

		//void print_dirent_info(char *path, dirent *de);
		print_file_info(filepath);
	}
	if(errno != 0){
		fprintf(stderr, "readdir %s error: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	//step 3. close directory
	//int closedir(DIR *dirp);
	closedir(dirp);
}

/*
 * print file of directory information like `ls -l'
 *
 * -rw-r--r-- 1 airead airead  2280 2011-08-23 22:27 dupfd.c
 * drwxr-xr-x 2 airead airead  4096 2011-08-27 10:53 excise
 */
void print_file_info(char *filepath)
{
	/* struct stat {
         *        dev_t     st_dev;     ID of device containing file
         *        ino_t     st_ino;     inode number
         *        mode_t    st_mode;    protection
         *        nlink_t   st_nlink;   number of hard links
         *        uid_t     st_uid;     user ID of owner
         *        gid_t     st_gid;     group ID of owner
         *        dev_t     st_rdev;    device ID (if special file)
         *        off_t     st_size;    total size, in bytes
         *        blksize_t st_blksize; blocksize for file system I/O
         *        blkcnt_t  st_blocks;  number of 512B blocks allocated
         *        time_t    st_atime;   time of last access
         *        time_t    st_mtime;   time of last modification
         *        time_t    st_ctime;   time of last status change
         *    };
	 */
	struct stat s;

	//int stat(const char *path, struct stat *buf);
	if(stat(filepath, &s) < 0){
		fprintf(stderr, "get %s stat failed: %s\n", filepath, strerror(errno));
		exit(1);
	}

	/* print file permission */
	//void print_file_permission(struct stat *buf);
	print_file_permission(&s);
	
	/* print number of hard links */
	fprintf(stdout, "%3d ", s.st_nlink);
	
	/* print owner of file */
	//void print_file_user(struct stat *buf);
	print_file_owner(&s);

	/* print group of file */
	//void print_file_group(struct stat *buf);
	print_file_group(&s);

	/* print size of file */
	fprintf(stdout, "%9ld ", (long int)s.st_size);

	/* print file last access time */
	//void print_file_time(struct stat *buf);
	print_file_time(&s);

	/* print file name */
	//char *strrchr(const char *s, int c);
	fprintf(stdout, "%s\n", strrchr(filepath, '/') + 1);
}

/*
 * print file permission like
 * drwxr-xr-x 
 */
void print_file_permission(struct stat *buf)
{
	mode_t mode = buf->st_mode;
	char per[11] = "-rwxrwxrwx";
	
	/* file type */
	/* S_IFMT     0170000   bit mask for the file type bit fields
         * S_IFSOCK   0140000   socket
         * S_IFLNK    0120000   symbolic link
         * S_IFREG    0100000   regular file
         * S_IFBLK    0060000   block device
         * S_IFDIR    0040000   directory
         * S_IFCHR    0020000   character device
         * S_IFIFO    0010000   FIFO
	 */
	switch(S_IFMT & buf->st_mode){
	case S_IFSOCK:
		per[0] = 's';
		break;
	case S_IFLNK:
		per[0] = 'l';
		break; 
	case S_IFREG:
		per[0] = '-';
		break; 
	case S_IFBLK:
		per[0] = 'b';
		break; 
	case S_IFDIR:
		per[0] = 'd';
		break; 
	case S_IFCHR:
		per[0] = 'c';
		break; 
	case S_IFIFO:
		per[0] = 'f';
		break; 
	default:
		per[0] = '?';	/* UNKONWN */
	}	
	
	/* set rwxrwxrwx ... */
        /* S_IRWXU    00700     mask for file owner permissions
         * S_IRUSR    00400     owner has read permission
         * S_IWUSR    00200     owner has write permission
         * S_IXUSR    00100     owner has execute permission
         * S_IRWXG    00070     mask for group permissions
         * S_IRGRP    00040     group has read permission
         * S_IWGRP    00020     group has write permission
         * S_IXGRP    00010     group has execute permission
         * S_IRWXO    00007     mask for permissions for others (not in group)
         * S_IROTH    00004     others have read permission
         * S_IWOTH    00002     others have write permission
         * S_IXOTH    00001     others have execute permission
	 */
	int i;
	int flag;

	for(i = 1; i <= 9; i++){
		flag = (buf->st_mode >> (9 - i)) & 0x01;
		if(!flag){
			per[i] = '-';
		}
	}

	/* set uid, gid, and sticky */
	/* S_ISUID    0004000   set UID bit
         * S_ISGID    0002000   set-group-ID bit (see below)
         * S_ISVTX    0001000   sticky bit (see below)
	 */
	if(buf->st_mode & S_ISUID){
		if(per[3] = '-'){
			per[3] = 'S';
		}else{
			per[3] = 's';
		}
	}
	if(buf->st_mode & S_ISGID){
		if(per[6] = '-'){
			per[6] = 'S';
		}else{
			per[6] = 's';
		}
	}
	if(buf->st_mode & S_ISVTX){
		if(per[9] = '-'){
			per[9] = 'T';
		}else{
			per[9] = 't';
		}
	}
	
	fprintf(stdout, "%s ", per);
}

/*
 * print owner of file
 */
void print_file_owner(struct stat *buf)
{
	/* struct passwd {
         *        char   *pw_name;       username
         *        char   *pw_passwd;     user password
         *        uid_t   pw_uid;        user ID
         *        gid_t   pw_gid;        group ID
         *        char   *pw_gecos;      real name
         *        char   *pw_dir;        home directory
         *        char   *pw_shell;      shell program
         *    }; */
	struct passwd *pd;

	errno = 0;
	//struct passwd *getpwuid(uid_t uid);
	if((pd = getpwuid(buf->st_uid)) == NULL){
		if(errno != 0){
			perror("getpwuid");
			exit(1);
		}else{
			fprintf(stdout, "%8d", (unsigned int)buf->st_uid);
		}
	}else{
		fprintf(stdout, "%8s ", pd->pw_name); 
	}
}

//void print_file_group(struct stat *buf);
void print_file_group(struct stat *buf)
{
	/* struct group {
         *        char   *gr_name;       group name
         *        char   *gr_passwd;     group password
         *        gid_t   gr_gid;        group ID
         *        char  **gr_mem;        group members
         *    }; */
	struct group *gr;
	
	errno = 0;
	//struct group *getgrgid(gid_t gid);
	if((gr = getgrgid(buf->st_gid)) == NULL){
		if(errno != 0){
			perror("getpwgid");
			exit(1);
		}else{
			fprintf(stdout, "%8d", (unsigned int)buf->st_gid);
		}
	}else{
		fprintf(stdout, "%8s ", gr->gr_name); 
	}
}

/*
 * print time of file
 * 2011-08-26 22:57
 */
void print_file_time(struct stat *buf)
{
	char format[] = "%Y-%2m-%2d %R ";
	char s[20] = "";

	/* struct tm {
         *        int tm_sec;         seconds
         *        int tm_min;         minutes
         *        int tm_hour;        hours
         *        int tm_mday;        day of the month
         *        int tm_mon;         month
         *        int tm_year;        year
         *        int tm_wday;        day of the week
         *        int tm_yday;        day in the year
         *        int tm_isdst;       daylight saving time
         *    }; */
	struct tm *t;
	//struct tm *localtime(const time_t *timep);
	if((t = localtime(&buf->st_atime)) == NULL){
		perror("localtime");
		exit(1);
	}

	//size_t strftime(char *s, size_t max, const char *format,
	//                const struct tm *tm);
	strftime(s, sizeof(s) - 1, format, t);

	fprintf(stdout, "%s ", s);
}
