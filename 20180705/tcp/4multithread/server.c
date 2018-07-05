
// 멀티 프로세스 기반의 서버는 안정적이다. 하지만 메모리 사용량이
// 많고 프로세스 간 데이터 공유도 어렵다. 이를 해결하기 위해 멀티 쓰레드를
// 도입합니다.
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> // for struct sockaddr_in
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void __error_quit(const char *msg, int line) {
	char buf[1024];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(-1);
}
#define error_quit(msg) __error_quit(msg, __LINE__)

void *thread_main(void *arg) {
	int csock = (int)arg;
	char buf[4096];
	int ret = read(csock, buf, sizeof(buf));
	if (ret < 0)
		error_quit("read");
	buf[ret] = 0;
	write(csock, buf, ret);
	close(csock);
	return NULL;
}
int main() {
	int ssock = socket(AF_INET, SOCK_STREAM, 0);
	if (ssock < 0)
		error_quit("socket");

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
		struct sockaddr_in caddr = { 0, };
		int addr_len = sizeof(caddr);
		int csock = accept(ssock, (struct sockaddr*)&caddr, &addr_len);
		if (csock < 0)
			error_quit("accept");
		printf("[server] %s is connected\n", inet_ntoa(caddr.sin_addr));
		pthread_t tid;
		if (pthread_create(&tid, NULL, thread_main, (void*)csock))
			error_quit("pthread_create");
		if (pthread_detach(tid))
			error_quit("pthread_detach");
	}
	close(ssock);
	return 0;
} 
