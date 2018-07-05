
// Aopen.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// 심볼의 정의로 이동하는 방법: 심볼에 커서를 위치시킨 후, g + ]
// inode 

int main() {
	int fd = open("Aopen.c", O_RDONLY);
	printf("fd = %d\n", fd);
	close(fd);
	return 0;
}
