
// 사번과 이름을 적으시오.
// 사번:
// 이름:

#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define err_abort(code,text) do {       					\
	fprintf(stderr, "%s at \"%s\":%d: %s\n",  			\
			text, __FILE__, __LINE__, strerror(code));  \
	abort();    																		\
}while(0)

#define errno_abort(text) do {       								\
	fprintf(stderr, "%s at \"%s\":%d: %s\n",  				\
			text, __FILE__, __LINE__, strerror(errno));		\
	abort();    																			\
} while(0)

typedef struct alarm_tag {
	struct alarm_tag    *next;
	int                 seconds;
	time_t              time;   /* seconds from EPOCH */
	char                message[64];
} alarm_t;

pthread_mutex_t alarm_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t alarm_cond = PTHREAD_COND_INITIALIZER;
alarm_t *alarm_list = NULL;

// 전역 변수는 최대 2개까지 추가 가능합니다.


// 아래의 함수를 구현하세요.
void display_list() {

}

// 아래의 함수를 구현하세요.
void alarm_insert (alarm_t *alarm){

}

void *alarm_thread (void *arg) {
	int status = pthread_mutex_lock (&alarm_mutex);
	if (status != 0)
		err_abort (status, "Lock mutex");

	while (1) {
		// 나머지를 구현하세요.
	}
}

int main() {
	pthread_t thread;
	int status = pthread_create(&thread, NULL, alarm_thread, NULL);
	if (status != 0)
		err_abort (status, "Create alarm thread");

	while (1) {
		printf("Alarm> ");

		char line[128];
		if (fgets(line, sizeof (line), stdin) == NULL)
			exit (0);

		if (strlen(line) <= 1)
			continue;

		if (strncmp(line, "list", 4) == 0) {
			display_list();
			continue;
		}

		// 이곳에서 알람 생성 및 리스트 추가 그리고 시그널 전송 코드를
		// 구현합니다.
	}
}


