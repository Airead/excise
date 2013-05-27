/**
 * @file tcpclient.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/05/17 15:34:50
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#if 0
struct timeval timeout;      
timeout.tv_sec = 10;
timeout.tv_usec = 0;

if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
			sizeof(timeout)) < 0)
        error("setsockopt failed\n");

if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
			sizeof(timeout)) < 0)
        error("setsockopt failed\n");
#endif

int main(int argc, char *argv[])
{
	char *ip;
	short port;
	int sock, sec;
	struct sockaddr_in peer_addr;
	socklen_t len;
	struct timeval timeout;

	if (argc < 4) {
		fprintf(stderr, "usage: %s <ip_addr> <port> <timeout>\n", argv[0]);
		exit(1);
	}

	ip = argv[1];
	port = strtol(argv[2], NULL, 10);
	sec =  strtol(argv[3], NULL, 10);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("create socket failed");
		exit(1);
	}
	
	memset(&peer_addr, 0, sizeof(peer_addr));
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_port = htons(port);

	if (inet_pton(AF_INET, ip, &peer_addr.sin_addr) < 0) {
		perror("inet_pton:");
		exit(1);
	}

	timeout.tv_sec = sec;
	timeout.tv_usec = 0;

	if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
		perror("setsockopt failed\n");
	}

	len = sizeof(peer_addr);
	if (connect(sock, (const struct sockaddr *)&peer_addr, len) < 0) {
		perror("connect failed:");
		exit(1);
	}

	printf("exit normal\n");
	close(sock);
	
	return 0;
}
