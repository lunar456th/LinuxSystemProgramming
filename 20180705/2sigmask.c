#include  <stdio.h>
#include  <stdlib.h>
#include  <signal.h>

void show_mask() {
	sigset_t sigset;

	if (sigprocmask(0, NULL, &sigset) < 0)
		printf("sigprocmask error");

	if (sigismember(&sigset, SIGINT))       printf("SIGINT ");
	if (sigismember(&sigset, SIGQUIT))      printf("SIGQUIT ");
	if (sigismember(&sigset, SIGUSR1))      printf("SIGUSR1 ");
	if (sigismember(&sigset, SIGALRM))      printf("SIGALRM ");
	printf("\n");
}

int main(void) {
	sigset_t newmask, oldmask;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	/* add SIGQUIT signal to blocked signal list */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		printf("sigprocmask error");

	show_mask();

	/* restore previous signal mask */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("sigprocmask error");

	exit (0);
}

#if 0
#include <signal.h>
#include <unistd.h>

int main()
{
	sigset_t set;	// 시그널 블록 집합
	sigset_t oldset;

	sigemptyset(&set);	// 시그널 블록 집합의 모든 비트가 0으로 설정

	// SIGINT에 대하여 시그널을 받지 않고 싶다!
	sigaddset(&set, SIGINT);
	sigprocmask( SIG_BLOCK, &set, &oldset);
	sleep(3);
	sigprocmask( SIG_SETMASK, &oldset, 0);
	while(1);
	return 0;
}
#endif
