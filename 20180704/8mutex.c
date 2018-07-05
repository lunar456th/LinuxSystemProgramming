
// 8mutex.c
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

// 정적 초기화
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;	// int lock = 0;

int loop_cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		pthread_mutex_lock(&mtx);
		// ------------------------
		++loop_cnt;	sleep(60);
		// -----------------------
		pthread_mutex_unlock(&mtx);
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
