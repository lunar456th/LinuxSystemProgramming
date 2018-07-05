
#if 1
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sig_handler(int signo) {
	if (signo == SIGALRM) {
		printf("알람 왔음\n");
		alarm(1);
	}
}

int main() {
	signal(SIGALRM, sig_handler);
	alarm(3);
	alarm(0);
	while(1);
	return 0;
}
#endif
#if 0
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sig_handler(int signo) {
	if (signo == SIGALRM) {
		printf("알람 왔음\n");
		alarm(1);
	}
}

int main() {
	signal(SIGALRM, sig_handler);
	alarm(10);
	sleep(3);
	int ret = alarm(3);
	printf("%d\n", ret);
	while(1);
	return 0;
}
#endif
#if 0
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sig_handler(int signo) {
	if (signo == SIGALRM) {
		printf("알람 왔음\n");
		alarm(1);
	}
}

int main() {
	signal(SIGALRM, sig_handler);
	alarm(1);
	while(1);
	return 0;
}
#endif

#if 0
#include <signal.h>
int main() {
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGKILL, SIG_IGN);

	while(1);
	return 0;
}
#endif
// kill
// 3000
// kill(3000, SIG_INT); == kill -2 3000

#if 0
#include <signal.h>
#include <stdio.h>
int main() {
	signal(SIGINT, SIG_IGN);
	getchar();

	signal(SIGINT, SIG_DFL);	// 기본값으로 복원합니다.

	while(1);
	return 0;
}
#endif
#if 0
#include <signal.h>
int main() {
	signal(SIGINT, SIG_IGN);

	while(1);
	return 0;
}
#endif
