
#if 1
#include <unistd.h>
#include <stdio.h>

int main() {
	const char *p1 = "hello";
	const char *p2 = "hello";

	pid_t pid = fork();
	// 부모 프로세스에는 자식의 프로세스가, 자식 프로세스에게는 0이 반환됩니다.
	// 복제된 이후에 부모 자식 중 어떠한 프로세스가 실행될 지는 아무도 알 수 없습니다.
	if (pid > 0) {
		printf("[parent] hello, world\n");
	}
	else if (pid == 0) {
		printf("[child] hello, world\n");
	}
	else {
		// error...
	}

	return 0;	// exit(main());	
}
#endif

// 4fork.c
#if 0 
#include <unistd.h>
#include <stdio.h>

// 리눅스의 경우, 프로세스의 생성 방법은 기존의 프로세스를 복제하여 생성합니다.
// 윈도우즈의 경우, 기존 프로세스를 사용하지 않고 새로운 프로세스를 생성합니다.
int main() {
	fork();	// CreateProcess(,,,,,,,);
	printf("hello, world\n");
	return 0;
}

#endif
