#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

__thread int cnt = 0;	// 정적 TLS
int func(void) {
	return ++cnt;
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
int main() {
	pthread_t tid1, tid2;
	pthread_create( &tid1, 0, my_handler1, 0 );
	pthread_create( &tid2, 0, my_handler2, 0 );
	pthread_join( tid1, 0 );
	pthread_join( tid2, 0 );
	return 0;
} 
