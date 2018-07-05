
#include <pthread.h>
#include <stdio.h>

//#define GPIOA	*(const volatile int*)0x12FF60

// 쓰레드 내부에서 외부의 변수를 사용 시, 최적화로 인한 캐싱을 방지하려면
// volatile 키워드를 사용하는 것이 좋습니다.
void *thread_main(void *arg) {
	volatile int *flag = (volatile int*)arg;	
	printf("start thread...\n");

	while (*flag)
		;

	printf("exit thread...\n");
	return NULL;
}

int main() {
	int flag = 1;

	pthread_t tid;
	pthread_create(&tid, NULL, thread_main, (void*)&flag);

	getchar();
	flag = 0;

	pthread_join(tid, NULL);
	printf("exit main\n");

	return 0;
}
