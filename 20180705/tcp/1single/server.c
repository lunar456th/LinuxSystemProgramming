
// server.c
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> // for struct sockaddr_in
#include <stdio.h>
#include <stdlib.h>

void __err_quit(const char *msg, int line) {
	char buf[1024];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(-1);
}
#define err_quit(msg)	__err_quit(msg, __LINE__)

// network programming -> socket programming
int main() {
	// 1. 소켓 생성
	int ssock = socket(AF_INET, SOCK_STREAM, 0); 
	if (ssock == -1)
		err_quit("socket");

	// 2. 주소 정보 설정
	struct sockaddr_in saddr = { 0, };
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);	// host to network short(16bit);
	saddr.sin_addr.s_addr = INADDR_ANY; 

	// 소켓에 할당된 주소를 즉시 재사용하기 위한 옵션
	int val = 1;
	int ret = setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&val, sizeof(val));
	if (ret < 0)
		perror("setsockopt"); 

	// 3. 소켓과 주소를 바인딩
	ret = bind(ssock, (struct sockaddr*)&saddr, sizeof(saddr));
	if (ret != 0) 
		err_quit("bind");

	// 4. 소켓으로부터 접속을 대기
	ret = listen(ssock, 5);
	if (ret != 0)
		err_quit("listen");

	printf("[server] running...\n");

	while (1) {
		struct sockaddr_in caddr = { 0, };
		int addr_len  = sizeof(caddr);

		int csock = accept(ssock, (struct sockaddr*)&caddr, &addr_len);
		if (csock == -1)
			err_quit("accept");
		printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));

		char buf[4096];
		ret = read(csock, buf, sizeof(buf));
		if (ret < 0)
			err_quit("read");
		// buf[ret] = 0;
		write(csock, buf, ret);
		close(csock);
	}
	close(ssock);
	return 0;
}
