







#if 1
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

int __bionic_cmpxchg(int32_t old_value, int32_t new_value, volatile int32_t* ptr) {
	int32_t prev;
	__asm__ __volatile__("lock; cmpxchgl %1, %2"
			: "=a" (prev)
			: "q" (new_value), "m" (*ptr), "0" (old_value)
			: "memory");
	return prev != old_value;
}

int32_t __bionic_atomic_dec(volatile int32_t* ptr) {
	int increment = -1;
	__asm__ __volatile__("lock; xaddl %0, %1"
			: "+r" (increment), "+m" (*ptr)
			: : "memory");
	return increment;
} 


void spin_lock(int *lock) { while (__bionic_cmpxchg(0, 1, lock)); }
void spin_unlock(int *lock) { __bionic_atomic_dec(lock); }

int lock = 0;

int loop_cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		spin_lock(&lock);
		// ------------------------
		++loop_cnt;	
		sleep(60);	// 오버헤드가 큰 작업이라고 가정
		// -----------------------
		spin_unlock(&lock);	
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
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

int __bionic_cmpxchg(int32_t old_value, int32_t new_value, volatile int32_t* ptr) {
	int32_t prev;
	__asm__ __volatile__("lock; cmpxchgl %1, %2"
			: "=a" (prev)
			: "q" (new_value), "m" (*ptr), "0" (old_value)
			: "memory");
	return prev != old_value;
}

int32_t __bionic_atomic_dec(volatile int32_t* ptr) {
	int increment = -1;
	__asm__ __volatile__("lock; xaddl %0, %1"
			: "+r" (increment), "+m" (*ptr)
			: : "memory");
	return increment;
} 


void spin_lock(int *lock) { while (__bionic_cmpxchg(0, 1, lock)); }
void spin_unlock(int *lock) { __bionic_atomic_dec(lock); }

int lock = 0;

int loop_cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		spin_lock(&lock);	// while (__bionic_cmpxchg(0, 1, &lock));
		// ------------------------
		++loop_cnt;	// 임계 영역(critical section)
		// -----------------------
		spin_unlock(&lock);	//__bionic_atomic_dec(&lock);	// lock = 0;
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
// 6sync.c
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

// old_value와 *ptr를 비교하여 같다면 *ptr을 new_value로 설정한다.
// 이와 같은 연산을 CAS(Compare And Set) 연산이라고 한다.
// 이 함수의 리턴 값은 설정에 성공했다면 0을, 실패했다면 1을 반환한다.
int __bionic_cmpxchg(int32_t old_value, int32_t new_value, volatile int32_t* ptr) {
	int32_t prev;
	__asm__ __volatile__("lock; cmpxchgl %1, %2"
			: "=a" (prev)
			: "q" (new_value), "m" (*ptr), "0" (old_value)
			: "memory");
	return prev != old_value;
}

int32_t __bionic_atomic_dec(volatile int32_t* ptr) {
	int increment = -1;
	__asm__ __volatile__("lock; xaddl %0, %1"
			: "+r" (increment), "+m" (*ptr)
			: : "memory");
	return increment;
} 


int lock = 0;

int loop_cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		while (__bionic_cmpxchg(0, 1, &lock));
		// ------------------------
		++loop_cnt;	// 임계 영역(critical section)
		// -----------------------
		__bionic_atomic_dec(&lock);	// lock = 0;
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
// 6sync.c
#include <stdio.h>
#include <pthread.h>

// old_value와 *ptr를 비교하여 같다면 *ptr을 new_value로 설정한다.
// 이와 같은 연산을 CAS(Compare And Set) 연산이라고 한다.
// 이 함수의 리턴 값은 설정에 성공했다면 0을, 실패했다면 1을 반환한다.
int __bionic_cmpxchg(int32_t old_value, int32_t new_value, volatile int32_t* ptr) {
	int32_t prev;
	__asm__ __volatile__("lock; cmpxchgl %1, %2"
			: "=a" (prev)
			: "q" (new_value), "m" (*ptr), "0" (old_value)
			: "memory");
	return prev != old_value;
}

int lock = 0;

int loop_cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 5000000; i++) {
		while (lock == 1);
		lock = 1;
		// ------------------------
		++loop_cnt;	// 임계 영역(critical section)
		// -----------------------
		lock = 0;
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
// 6sync.c
#include <stdio.h>
#include <pthread.h>

int loop_cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 1000000; i++) {
		++loop_cnt;
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
