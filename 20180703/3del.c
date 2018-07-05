
// 3del.c

// rm -> unlink();

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
// # echo "hello" > hello.txt -> 아이노드의 nlink(연결 계수)가 1로 설정됨
int main() {
	int fd = open("hello.txt", O_RDONLY); // 아이노드의 count(참조 계수)가 1 증가
	if (fd == -1) {
		perror("open");
		return -1;
	}
	getchar();
	unlink("hello.txt"); // 연결 계수가 1 감소되어 0이 됨
	getchar();
	char buf[1024];
	int nread = read(fd, buf, sizeof(buf));
	write(1, buf, nread);
	getchar();
	close(fd); // 참조 계수가 0이 되고 연결 계수도 0이므로 아이노드는 삭제됨
	return 0;
}
