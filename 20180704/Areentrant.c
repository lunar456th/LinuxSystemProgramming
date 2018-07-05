#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void *my_handler1(void *data) {
	char hp[] = "010-1234-5678";
	char *saveptr;
	char *p = strtok_r( hp, "-", &saveptr);
	while(p) {
		printf("[%s]\n", p );
		p = strtok_r( 0, "-", &saveptr);
		sleep(1);
	}
}
void *my_handler2(void *data) {
	char ip[] = "192.168.1.100";
	char *saveptr;
	char *p = strtok_r( ip, ".", &saveptr);
	while(p) {
		printf("[%s]\n", p );
		p = strtok_r( 0, ".", &saveptr);
		sleep(1);
	}
}
int main() {
	pthread_t tid1, tid2;
	pthread_create( &tid1, 0, my_handler1, 0 );
	pthread_create( &tid2, 0, my_handler2, 0 );
	pthread_join( tid1, 0 );
	pthread_join( tid2, 0 );
	return 0;
} 
#if 0
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *my_handler1(void *data) {
	char hp[] = "010-1234-5678";
	pthread_mutex_lock(&mutex);
	//-------------------------------
	char *p = strtok( hp, "-");
	while(p) {
		printf("[%s]\n", p );
		p = strtok( 0, "-");
		sleep(1);
	}
	//-------------------------------
	pthread_mutex_unlock(&mutex);
}
void *my_handler2(void *data) {
	char ip[] = "192.168.1.100";
	pthread_mutex_lock(&mutex);
	//-------------------------------
	char *p = strtok( ip, ".");
	while(p) {
		printf("[%s]\n", p );
		p = strtok( 0, ".");
		sleep(1);
	}
	//-------------------------------
	pthread_mutex_unlock(&mutex);
}
int main()
{
	pthread_t tid1, tid2;
	pthread_create( &tid1, 0, my_handler1, 0 );
	pthread_create( &tid2, 0, my_handler2, 0 );
	pthread_join( tid1, 0 );
	pthread_join( tid2, 0 );
	return 0;
} 
#endif

#if 0
// strtok 함수는 내부적으로 정적 지역 변수를 사용하므로 멀티 쓰레드에 안전하지
// 않습니다. 이를 위해 동기화 메커니즘을 도입합니다.
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void *my_handler1(void *data) {
	char hp[] = "010-1234-5678";
	char *p = strtok( hp, "-");
	while(p) {
		printf("[%s]\n", p );
		p = strtok( 0, "-");
		sleep(1);
	}
}
void *my_handler2(void *data) {
	char ip[] = "192.168.1.100";
	char *p = strtok( ip, ".");
	while(p) {
		printf("[%s]\n", p );
		p = strtok( 0, ".");
		sleep(1);
	}
}
int main() {
	pthread_t tid1, tid2;
	pthread_create( &tid1, 0, my_handler1, 0 );
	pthread_create( &tid2, 0, my_handler2, 0 );
	pthread_join( tid1, 0 );
	pthread_join( tid2, 0 );
	return 0;
} 
#endif
#if 0
#include <stdio.h>
#include <string.h>

int main() {
	char hp[] = "010-1234-5678";
	char *p;
	p = strtok( hp, "-");
	while(p) { 
		printf("[%s]\n", p );
		p = strtok(0, "-");
	}
	return 0;
} 
#endif


#if 0
#include <stdio.h>
#include <pthread.h>

// 아래의 함수와 같이 서로 다른 쓰레드가 같은 함수를 사용한다 하더라도 언제가
// 같은 실해 결과를 보장하는 함수를 재진입(reentrant) 함수라고 하며 이 함수는
// 병행과 병렬 모두 안전하게 동작합니다.

// 표준 라이브러리에서는 어떤 함수가 재진입성을 갖는다면 다른 함수와 구분을 하기 위해
// 접미사로 r(reentrant)를 사용합니다.
void func_r(int *cnt) {
	++(*cnt);
}

// 재진입 함수의 조건
// 정적 (전역) 변수를 사용하면 안 된다.
// 정적 (전역) 변수의 주소를 반환하면 안 된다.
// 호출자가 호출 시 제공한 매개변수만으로 동작해야 한다.
// 다른 비-재진입 함수를 호출하면 안 된다. 

void *thread_main1(void *arg) {
	int cnt = 0;
	func_r(&cnt);
	func_r(&cnt);
	func_r(&cnt);
	printf("cnt = %d\n", cnt);
	return 0;
}

void *thread_main2(void *arg) {
	int cnt = 0;
	func_r(&cnt);
	func_r(&cnt);
	func_r(&cnt);
	printf("cnt = %d\n", cnt);
	return 0;
}

int main() {
	pthread_t t1, t2;
	pthread_create(&t1, 0, thread_main1, 0);
	pthread_create(&t2, 0, thread_main2, 0);

	pthread_join(t1, 0);
	pthread_join(t2, 0);
	return 0;
}

#endif
#if 0
#include <stdio.h>
#include <pthread.h>

// 정적 지역 변수나 전역 변수는 멀티 쓰레드에 안전하지 않습니다.
int func() {
	static int cnt = 0;
	return ++cnt;
}

void *thread_main1(void *arg) {
	func();
	func();
	int cnt = func();
	printf("cnt = %d\n", cnt);
	return 0;
}

void *thread_main2(void *arg) {
	func();
	func();
	int cnt = func();
	printf("cnt = %d\n", cnt);
	return 0;
}

int main() {
	pthread_t t1, t2;
	pthread_create(&t1, 0, thread_main1, 0);
	pthread_create(&t2, 0, thread_main2, 0);

	pthread_join(t1, 0);
	pthread_join(t2, 0);
	return 0;
}

#endif
#if 0
// 함수가 몇 번 호출되었는지를 확인하고 싶다면 어떻게 해야 할까?
#include <stdio.h>

// int cnt = 0;	// global is evil!
int func() {
	static int cnt = 0;
	return ++cnt;
}

int main() {
	func();
	func();
	int cnt = func();
	printf("cnt = %d\n", cnt);
	return 0;
}

#endif
