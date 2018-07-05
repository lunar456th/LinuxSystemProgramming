
// 멀티 쓰레드의 경우, 안정성이 떨어지게 되고 동기화로 인한 성능 상이 이슈가 존재합니다.
// 이를 해결하기 위해 select(io multiplexing)를 도입합니다.
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> // for struct sockaddr_in
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
void __error_quit(const char *msg, int line) {
	char buf[1024];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(-1);
}
#define error_quit(msg) __error_quit(msg, __LINE__)

int fd_table[1024] = { 0, };
int fd_cnt = 0;
fd_set read_fds;

int get_max_fd() {
	int max = -1;
	for (int i = 0; i < fd_cnt; i++) {
		if (fd_table[i] > max)
			max = fd_table[i];
	}
	return max;
}
int main() {
	int ssock = socket(AF_INET, SOCK_STREAM, 0);
	if (ssock < 0)
		error_quit("socket");
	fd_table[fd_cnt++] = ssock;

	struct sockaddr_in saddr = { 0, }; 
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int val = 1;
	int ret = setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR,
			(char*)&val, sizeof(val));
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
		FD_ZERO(&read_fds);
		for (int i = 0; i < fd_cnt; i++)
			FD_SET(fd_table[i], &read_fds);
		int max_fd = get_max_fd();
		int ret = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
		if (ret < 0)
			error_quit("select");
		if (FD_ISSET(ssock, &read_fds)) {
			struct sockaddr_in caddr = { 0, };
			int addr_len = sizeof(caddr);
			int csock = accept(ssock, (struct sockaddr*)&caddr, &addr_len);
			if (csock < 0)
				error_quit("accept");
			fd_table[fd_cnt++] = csock;
			printf("[server] %s is connected\n", inet_ntoa(caddr.sin_addr));
			continue;
		}
		char buf[4096];
		for (int i = 0; i < fd_cnt; i++) {
			if (FD_ISSET(fd_table[i], &read_fds)) {
				ret = read(fd_table[i], buf, sizeof(buf));
				if (ret < 0) 
					error_quit("read");
				buf[ret] = 0;
				write(fd_table[i], buf, ret);
				close(fd_table[i]);
				fd_table[i] = fd_table[--fd_cnt];
			}
		}
	}
	close(ssock);
	return 0;
}
