
// 기존의 select는 사용자가 입출력 정보를 관리해야 하고 모든 비트를 순회하면서
// 이벤트 처리를 해야하기 때문에 성능 상의 오버헤드가 존재합니다. 이를 해결하기 위해
// poll을 도입합니다.
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> // for struct sockaddr_in
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
void __error_quit(const char *msg, int line) {
	char buf[1024];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(-1);
}
#define error_quit(msg) __error_quit(msg, __LINE__)

struct pollfd poll_fds[1024];
int fd_cnt = 0;
int main() {
	int ssock = socket(AF_INET, SOCK_STREAM, 0);
	if (ssock < 0)
		error_quit("socket");

	poll_fds[fd_cnt].fd = ssock;
	poll_fds[fd_cnt].events = POLLIN;
	++fd_cnt;
	
	struct sockaddr_in saddr = { 0, };
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int val = 1;
	int ret = setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&val,
			sizeof(val)); 
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
		int ret = poll(poll_fds, fd_cnt, -1);
		if (ret < 0)
			error_quit("poll");
		if (poll_fds[0].revents & POLLIN) {
			struct sockaddr_in caddr = { 0, };
			int addr_len = sizeof(caddr);
			int csock = accept(ssock, (struct sockaddr*)&caddr, &addr_len);
			if (csock < 0)
				error_quit("accept");
			printf("[server] %s is connected\n", inet_ntoa(caddr.sin_addr));
			poll_fds[fd_cnt].fd = csock;
			poll_fds[fd_cnt].events = POLLIN;
			++fd_cnt;
			continue;
		}
		char buf[4096];
		for (int i = 1; i < fd_cnt; i++) {
			if (poll_fds[i].revents & POLLIN) {
				ret = read(poll_fds[i].fd, buf, sizeof(buf));
				if (ret < 0)
					error_quit("read");
				buf[ret] = 0;
				write(poll_fds[i].fd, buf, ret);
				close(poll_fds[i].fd);
				poll_fds[i] = poll_fds[--fd_cnt];
			}
		} 
	}
	close(ssock);
	return 0;
}
