
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> // for struct sockaddr_in
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h>
void __error_quit(const char *msg, int line) {
	char buf[1024];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(-1);
}
#define error_quit(msg) __error_quit(msg, __LINE__)
struct epoll_event event_pool[32];
int main() {
	int efd = epoll_create(1);
	if (efd < 0)
		error_quit("epoll_create");
	int ssock = socket(AF_INET, SOCK_STREAM, 0);
	if (ssock < 0)
		error_quit("socket");
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = ssock;
	int ret = epoll_ctl(efd, EPOLL_CTL_ADD, ssock, &event);
	if (ret < 0)
		error_quit("epoll_ctl");
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
		int event_cnt = epoll_wait(efd, event_pool, 32, -1);
		if (event_cnt < 0)
			error_quit("epoll_wait");
		for (int i = 0; i < event_cnt; i++) {
			if (event_pool[i].data.fd == ssock) {
				struct sockaddr_in caddr = { 0, };
				int addr_len = sizeof(caddr);
				int csock = accept(ssock, (struct sockaddr*)&caddr, &addr_len);
				if (csock < 0)
					error_quit("accept");
				printf("[server] %s is connected\n", inet_ntoa(caddr.sin_addr));
				event.events = EPOLLIN;
				event.data.fd = csock;
				int ret = epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event);
				if (ret < 0)
					error_quit("epoll_ctl");
				continue;
			}
			char buf[4096];
			ret = read(event_pool[i].data.fd, buf, sizeof(buf));
			if (ret < 0)
				error_quit("read");
			buf[ret] = 0; 
			write(event_pool[i].data.fd, buf, ret);
			ret = epoll_ctl(efd, EPOLL_CTL_DEL, event_pool[i].data.fd, NULL);
			close(event_pool[i].data.fd);
			if (ret < 0)
				error_quit("epoll_ctl");
		}
	}
	close(ssock);
	return 0;
} 
