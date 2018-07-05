
#if 1
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void *thread_main(void *arg) {
	const char *str = (const char *)arg;
	for(int i = 0; i < 5; ++i) {
		sleep(1);
		printf("%s\n", str);
	}
	return "done";
}

// 리눅스에서 쓰레드는 LWP라고 합니다.
// LWP: Light Weight Process
int main() {
	pthread_t tid;
	pthread_create(&tid, NULL, thread_main, "\t\tdo something...");	// fork

	// 워크 쓰레드가 종료될 때 까지 대기하는 함수
	char *msg;
	pthread_join(tid, (void**)&msg);								// wait
	printf("%s\n", msg);

	return 0;
}
#endif

#if 0
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

// 멀티 쓰레드인 상황에서 메인 쓰레드가 종료되면 모든 쓰레드는 종료됩니다.
// 메인 쓰레드가 종료된다는 것은 결국 프로세스가 종료됨을 의미하기 때문입니다.
void *thread_main(void *arg) {
	const char *str = (const char *)arg;
	for(int i = 0; i < 5; ++i) {
		sleep(1);
		printf("%s\n", str);
	}
	return NULL;
}

int main() {
	pthread_t tid;
	pthread_create(&tid, NULL, thread_main, "\t\tdo something...");
	return 0;
}
#endif
#if 0
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

// 하나의 프로세스에 2개 이상의 쓰레드가 동작할 경우, 이를 멀티 쓰레드(multi-thread)라고
// 합니다.

// 빌드 시, -pthread 옵션을 사용해야 합니다.
void *thread_main(void *arg) {
	const char *str = (const char *)arg;
	for(int i = 0; i < 5; ++i) {
		sleep(1);
		printf("%s\n", str);
	}
	return NULL;
}

// 메인 함수를 호출한 쓰레드를 메인 쓰레드라고 합니다.
int main() {
	pthread_t tid;

	// 메인 쓰레드로부터 파생된 쓰레드를 워커 쓰레드라고 합니다.
	pthread_create(&tid, NULL, thread_main, "\t\tdo something...");
	
	while(1) {
		printf("main...\n");
		sleep(1);
	}
	return 0;
}
#endif

#if 0
#include <unistd.h>
#include <stdio.h>

void print(const char *str) {
	for(int i = 0; i < 5; ++i) {
		sleep(1);
		printf("%s\n", str);
	}
}

// main thread: main 함수를 호출하는 실행의 흐름(실타래)
// 프로세스에 쓰레드가  하나만 생성된 경우, 싱글 쓰레드(single thread)라고 합니다.
int main() {
	print("\t\tdo something...");
	
	while(1) {
		printf("main...\n");
		sleep(1);
	}
	return 0;
}
#endif
