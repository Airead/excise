/**
 * @file tcpserver.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/06/06 20:50:10
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

int get_listenfd(short port)
{
	int fd;
	struct sockaddr_in sin;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket failed");
		exit(1);
	}

	// fcntl(fd, F_SETFL, O_NONBLOCK);
	fprintf(stdout, "server listen fd=%d\n", fd);

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);

	if (bind(fd, (const struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("bind error");
		exit(1);
	}

	return fd;
}

int main(int argc, char *argv[])
{
	short port;
	int lfd;		/* listen fd */

	if (argc < 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
	}

	// long int strtol(const char *nptr, char **endptr, int base);
	port = strtol(argv[1], NULL, 10);
	
	lfd = get_listenfd(port);
	if (lfd < 0) {
		fprintf(stderr, "get listenfd failed\n");
		exit(1);
	}

	listen(lfd, 10);

	while (1) {
		struct sockaddr_in sin;
		socklen_t len = sizeof(struct sockaddr);
		int fd;

		fd = accept(lfd, (struct sockaddr *)&sin, &len);
		if (fd < 0) {
			perror("accept failed");
			exit(1);
		}

		while (1) {
			int rn;
			char buf[2048];
			
			memset(buf, 0, 2048);
			rn = recv(fd, buf, sizeof(buf) - 1, 0);
			if (rn < 0) {
				perror("read error");
				close(fd);
				break;
			} else if (rn == 0) {
				fprintf(stdout, "closed gracefully");
				break;
			} else { /* rn > 0 */
				fprintf(stdout, "from [%d], recv: %s\n", fd, buf);
			}
		}
	}

	return 0;
}
