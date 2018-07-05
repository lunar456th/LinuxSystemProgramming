
// TLS(Thread Local Storage)
// 전역 변수를 쓰레드 별로 저장하는 메커니즘

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_key_t key;
int func(void) {
	int *ptr;
	ptr = pthread_getspecific(key);	// int *ptr = TLS[key];
	if( ptr == 0 ) {
		ptr = calloc(1, sizeof(int));
		printf("ptr=%p\n", ptr );
		pthread_setspecific(key, ptr);	// TLS[key] = ptr;
	}
	return ++*ptr;
}
void *my_handler1(void *data) {
	func();
	func();
	int cnt = func();
	printf("cnt = %d\n", cnt);
}
void *my_handler2(void *data) {
	func();
	func();
	int cnt = func();
	printf("cnt = %d\n", cnt);
} 
void destructor(void* p) {
	printf("destructor(%p)\n", p ); 
	free(p);
}
int main() {
	pthread_t tid1, tid2;
	pthread_key_create( &key, destructor);
	pthread_create( &tid1, 0, my_handler1, 0 );
	pthread_create( &tid2, 0, my_handler1, 0 );
	pthread_join( tid1, 0 );
	pthread_join( tid2, 0 );
	return 0;
} 

