
#if 1
// 이전의 코드는 생산자가 쓰레드가 데이터를 다 생산할 때 까지
// 소비자 쓰레드는 루프를 돌면서 대기하고 있습니다. -> busy waiting
// -> 조건 변수(conditiona variable)
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int is_full = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *download(void *arg) {	// 생산자 쓰레드
	pthread_mutex_lock(&mtx);
	//-----------------------------
	printf("downloading...\n");
	sleep(5);	//  버퍼링...
	is_full = 1;
	printf("download complete!\n");
	//-----------------------------
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

void *play(void *arg) {	  // 소비자 쓰레드
	pthread_mutex_lock(&mtx);
	pthread_cond_wait(&cond, &mtx);	// -> pthread_mutex_unlock();
	//-----------------------------
	if (is_full) {
		printf("playing...\n");
		sleep(3);	//  재생중
		is_full = 0;
		printf("it's done!\n");
	}
	//-----------------------------
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main() {
	pthread_t tid1, tid2;
	pthread_create(&tid2, 0, play, 0);
	getchar();

	pthread_create(&tid1, 0, download, 0);

	pthread_join(tid1, 0);
	pthread_join(tid2, 0);

	return 0;
}
#endif
#if 0
// 9cond.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int is_full = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
void *download(void *arg) {	// 생산자 쓰레드
	pthread_mutex_lock(&mtx);
	//-----------------------------
	printf("downloading...\n");
	sleep(5);	//  버퍼링...
	is_full = 1;
	printf("download complete!\n");
	//-----------------------------
	pthread_mutex_unlock(&mtx);
	return NULL;
}

void *play(void *arg) {	  // 소비자 쓰레드
	int done = 0;
	while (1) {
		pthread_mutex_lock(&mtx);
		//-----------------------------
		if (is_full) {
			printf("playing...\n");
			sleep(3);	//  재생중
			is_full = 0;
			printf("it's done!\n");

			done = 1;
		}
		//-----------------------------
		pthread_mutex_unlock(&mtx);

		if (done) break;
	}
	return NULL;
}

int main() {
	pthread_t tid1, tid2;
	pthread_create(&tid2, 0, play, 0);
	getchar();

	pthread_create(&tid1, 0, download, 0);

	pthread_join(tid1, 0);
	pthread_join(tid2, 0);

	return 0;
}
#endif
