#if 1
// 3model.c

// 

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

//           fork -> do_fork
// pthread_create -> do_fork

// 리눅스 운영체제의 입장에서 프로세스와 쓰레드는 같은 개념으로
// 취급합니다. 다만 다른 점이 있다면 프로세스는 메모리를 공유하지 않지만
// 쓰레드는 메모리를 공유합니다.


// 프로세스와 달리 쓰레드는 모든 메모리를 공유합니다.
int global = 0;
void *thread_main(void *arg) {
	++global;
	printf("[worker] global = %d\n", global);
	return NULL;
}
int main() {
	pthread_t tid;
	pthread_create(&tid, NULL, thread_main, NULL);
	pthread_join(tid, NULL);

	printf("[main] global = %d\n", global);
	return 0;
}
#endif

#if 0
// 3model.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// 프로세스가 생성되면 기계어 코드는 공유하지만 메모리 영역은
// 분리하여 사용합니다.	메모리가 복제되는 시점은 COW!!!
int global = 0;
int main() {
	if (fork() == 0) {
		++global;
		printf("[child] global = %d\n", global);
		exit(0);
	}

	wait(0);
	printf("[parent] global = %d\n", global);
	return 0;
}
#endif
