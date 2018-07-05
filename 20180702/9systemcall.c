
#if 1
// 9systemcall.c
#include <unistd.h>
#include <stdio.h>

#define STDIN	(0)
#define STDOUT	(1)
#define STDERR	(2)

// 이처럼 운영체제가 제공하는 함수를 사용하여 프로그래밍을 하는 것을
// 시스템 프로그래밍이라고 합니다.
int main() {
	char buff[4096];
	while (1) {
		// read는 리눅스가 제공하는 함수(System Call)
		int nread = read(STDIN, buff, sizeof(buff));	// 2 + K
		if (nread <= 0)
			return -1;
		write(STDOUT, buff, nread);
	}
	return 0;
}
#endif
#if 0
// 9systemcall.c
#include <stdio.h>

// 종료를 하려면 현재 프로그램에 EOF를 전송하면 됩니다.
// 전송 방법: CTRL + D	(# stty -a)
int main() {
	char buff[4096];
	while (1) {
		if (fgets(buff, sizeof buff, stdin) == NULL)
			return -1;
		fputs(buff, stdout);
	}
	return 0;
}
#endif
