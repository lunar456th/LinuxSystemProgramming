

#if 1
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

#include <unistd.h>
#include <sys/syscall.h>

// futex
#define FUTEX_WAIT 0
#define FUTEX_WAKE 1
void sleep_lock(int *lock) { syscall(202, lock, FUTEX_WAIT, 1, 0); }
void sleep_unlock(int *lock) { syscall(202, lock, FUTEX_WAKE, 1); }

int lock = 0;
int loop_cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		sleep_lock(&lock);	// spin_lock(&lock);
		// ------------------------
		++loop_cnt;	
		sleep(60);	// 오버헤드가 큰 작업이라고 가정
		// -----------------------
		sleep_unlock(&lock);	// spin_unlock(&lock);	
	}
	return NULL;
}

int main() {
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, thread_main, NULL);
	pthread_create(&tid2, NULL, thread_main, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("loop_cnt = %d\n", loop_cnt);
	return 0;
}
#endif
#if 0
// 7futex.c
// futex	// 2 + K
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#define FUTEX_WAIT 0
#define FUTEX_WAKE 1
void sleep_lock(int *lock) { syscall(202, lock, FUTEX_WAIT, 1, 0); }
void sleep_unlock(int *lock) { syscall(202, lock, FUTEX_WAKE, 1); }

int lock = 1; // locked
void* thread_func(void* arg) {
	printf("[worker] sleep\n");
	sleep_lock(&lock);
	printf("[worker] wake\n");
	return NULL;
}
int main() {
	pthread_t tid;
	pthread_create(&tid, 0, thread_func, 0);
	getchar();
	sleep_unlock(&lock);
	pthread_join(tid, 0);
	return 0;
} 
#endif
#if 0
// 7futex.c
// futex	// 2 + K
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#define FUTEX_WAIT 0
#define FUTEX_WAKE 1

int lock = 1; // locked
void* thread_func(void* arg) {
	printf("[worker] sleep\n");
	syscall(202, &lock, FUTEX_WAIT, 1, 0); // __futex_wait();
	printf("[worker] wake\n");
	return NULL;
}
int main() {
	pthread_t tid;
	pthread_create(&tid, 0, thread_func, 0);
	getchar();
	syscall(202, &lock, FUTEX_WAKE, 1); // __futex_wake();
	pthread_join(tid, 0);
	return 0;
} 
#endif

