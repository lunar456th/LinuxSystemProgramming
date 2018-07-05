
// 이전 서버의 경우, 싱글 쓰레드로 구동되기 때문에 다수의 접속에는
// 처리할 수 없다는 단점이 있습니다. 이를 해결하기 위해 넌블럭 기반으로 구현합니다.
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> // for struct sockaddr_in
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
void __error_quit(const char *msg, int line) {
	char buf[1024];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(-1);
}
#define error_quit(msg) __error_quit(msg, __LINE__)
int fd_table[1024] = { 0, };
int cnt = 0;
int main() {
	int ssock = socket(AF_INET, SOCK_STREAM, 0);
	if (ssock < 0)
		error_quit("socket");

	int ret = fcntl(ssock, F_SETFL, O_NONBLOCK);
	if (ret < 0)
		error_quit("fcntl");

	struct sockaddr_in saddr = { 0, };
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int val = 1;
	ret = setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&val, sizeof(val));
	if (ret < 0)
		perror("setsockopt"); 

	ret = bind(ssock, (struct sockaddr*)&saddr, sizeof(saddr));
	if (ret < 0)
		error_quit("bind");

	ret = listen(ssock, 10);
	if (ret < 0)
		error_quit("listen");

	printf("[server] running...\n");
	while (1) {
		struct sockaddr_in caddr = { 0, };
		int addr_len = sizeof(caddr);
		int csock = accept(ssock, (struct sockaddr*)&caddr, &addr_len);
		if (csock < 0) {
			if (errno != EAGAIN)
				error_quit("accept");
		}
		if (csock >= 0) {
			printf("[server] %s is connected\n", inet_ntoa(caddr.sin_addr));
			ret = fcntl(csock, F_SETFL, O_NONBLOCK);
			if (ret < 0)
				error_quit("fcntl");
			fd_table[cnt++] = csock;
		}
		char buf[4096];
		for (int i = 0; i < cnt; i++) {
			ret = read(fd_table[i], buf, sizeof(buf));
			if (ret < 0) {
				if (errno == EAGAIN) {
					continue;
				}
				error_quit("read");
			}
			buf[ret] = 0;
			write(fd_table[i], buf, ret);
			close(fd_table[i]);
			fd_table[i] = fd_table[--cnt];
		}
	}
	close(ssock);
	return 0; 
}
