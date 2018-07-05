
#if 1
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sig_handler(int signo) {
	int exit_code;
	while(waitpid(-1, &exit_code, WNOHANG) > 0) // while(wait(&exit_code) > 0)
		printf("%d\n", (exit_code >> 8) & 0xFF);
}

int main() {	// int main(int argc, char **argv, char *envp):q
	signal(SIGCHLD, sig_handler);

	for (int i = 0; i < 1000; i++) {
		if (fork() == 0) {
			printf("\t\t[child] %d create...\n", i+1);
			sleep(i+1);
			exit(i+1);
		}
	}

	while (1) {
		printf("[parent] do something...\n");
		sleep(1);
	}
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sig_handler(int signo) {
	int exit_code;
	while(wait(&exit_code) > 0)
		printf("%d\n", (exit_code >> 8) & 0xFF);
}

int main() {
	signal(SIGCHLD, sig_handler);

	for (int i = 0; i < 1000; i++) {
		if (fork() == 0) {
			printf("\t\t[child] %d create...\n", i+1);
			sleep(5);
			exit(i+1);
		}
	}

	while (1) {
		printf("[parent] do something...\n");
		sleep(1);
	}
	return 0;
}
#endif
// 5exit.c
#if 0
// 현재 코드는 부모와 자식이 병행적으로 수행되지 않습니다. 이를 해결하기
// 위해 시그널을 도입합니다. 시그널이란 서로 다른 프로세스 사이의 통신을 하기 위한
// 메커니즘으로 kill -l로 리눅스에서 사용되는 시그널의 정보를 확인할 수 있습니다.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sig_handler(int signo) {
	int exit_code;
	wait(&exit_code);
	printf("%d\n", (exit_code >> 8) & 0xFF);
}

int main() {
	// 운영체제에게 SIGCHLD에 대하여 통지를 받을 수 있도록 콜백 함수를 등록합니다.
	signal(SIGCHLD, sig_handler);

	if (fork() == 0) {
		for (int i = 0; i < 5; i++) {
			printf("\t\t[child] do something...\n");
			sleep(1);
		}
		// 자식이 종료가 되면 부모 프로세스에게 SIGCHLD라는 시그널을
		// 보냅니다.
		exit(7);
	}

	while (1) {
		printf("[parent] do something...\n");
		sleep(1);
	}
	return 0;
}
#endif

#if 0
// 현재 프로세스는 부모가 자식의 종료 코드를 읽어 오지 않아 좀비 프로세스가
// 생성되었습니다. 좀비 프로세스가 생성되지 않도록 종료 코드를 읽어오는
// 코드를 추가합니다.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	if (fork() == 0) {
		for (int i = 0; i < 5; i++) {
			printf("\t\t[child] do something...\n");
			sleep(1);
		}
		exit(7);	// return 0;
	}

	// 자식이 종료될 때까지 대기하고 있다가 자식이 종료 코드를 
	// 설정하면 그 값을 읽어오는 역할을 합니다.
	int exit_code;
	wait(&exit_code);
	printf("%d\n", (exit_code >> 8) & 0xFF);

	while (1) {
		printf("[parent] do something...\n");
		sleep(1);
	}
	return 0;
}
#endif
#if 0
// 부모와 자식이 어떠한 일을 동시에 한다고 가정합니다.
#include <stdio.h>
#include <unistd.h>

int main() {
	if (fork() == 0) {
		// 자식 프로세스
		for (int i = 0; i < 5; i++) {
			printf("\t\t[child] do something...\n");
			sleep(1);
		}
		return 0;
	}

	// 부모 프로세스
	while (1) {
		printf("[parent] do something...\n");
		sleep(1);
	}
	return 0;
}
#endif
