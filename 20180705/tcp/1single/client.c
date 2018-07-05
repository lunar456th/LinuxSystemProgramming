#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void __error_quit(const char *msg, int line) {
	char buf[1024];
	sprintf(buf, "%s(%d)", msg, line); 
	perror(buf);
	exit(-1);
}
#define error_quit(msg) __error_quit(msg, __LINE__)

int main() {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		error_quit("socket");
	struct sockaddr_in saddr = { 0, };
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = inet_addr("192.168.56.100");
	int ret = connect(sock, (struct sockaddr*)&saddr, sizeof(saddr));
	if (ret < 0)
		error_quit("connect");
	char buf[1024];
	ret = read(0, buf, sizeof(buf));
	buf[ret - 1] = 0; // delete '\n'
	write(sock, buf, ret);
	ret = read(sock, buf, strlen(buf));
	buf[ret] = 0;
	printf("%s\n", buf);
	close(sock);
	return 0;
} 
