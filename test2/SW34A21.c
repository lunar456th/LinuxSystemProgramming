
// 사번과 이름을 적으시오.
// 사번: SW34A21
// 이름: 김승주

#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define err_abort(code,text) do {					 \
	fprintf(stderr, "%s at \"%s\":%d: %s\n",			\
			text, __FILE__, __LINE__, strerror(code)); \
	abort();										\
}while(0)

#define errno_abort(text) do {					 \
	fprintf(stderr, "%s at \"%s\":%d: %s\n",			\
			text, __FILE__, __LINE__, strerror(errno)); \
	abort();										\
} while(0)

typedef struct alarm_tag {
	struct alarm_tag *next;
	int		 seconds;
	time_t	 time; /* seconds from EPOCH */
	char		message[64];
} alarm_t;

pthread_mutex_t alarm_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t alarm_cond = PTHREAD_COND_INITIALIZER;
alarm_t alarm_list = { .next = &alarm_list };

// 전역 변수는 최대 2개까지 추가 가능합니다.
pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;

// 아래의 함수를 구현하세요.
void display_list() {
	if(alarm_list.next == &alarm_list)
	{
		printf("[no alarm]");
	}
	for(alarm_t * temp = alarm_list.next; temp != &alarm_list; temp = temp->next)
	{
		printf("[(%d) %s]", temp->seconds, temp->message);
	}
	printf("\n");
}

// 아래의 함수를 구현하세요.
void alarm_insert (alarm_t * alarm){
	alarm_t * temp;
	alarm_t * prev = &alarm_list;
	if(alarm_list.next == &alarm_list)
	{
		alarm_list.next = alarm;
		alarm->next = &alarm_list;
		return;
	}
	for(temp = alarm_list.next; temp != &alarm_list; )
	{
		if(temp->seconds > alarm->seconds)
		{
			break;
		}
		prev = temp;
		temp = temp->next;
	}
	alarm->next = prev->next;
	prev->next = alarm;
}

void * alarm_thread (void * arg) {
	int status = pthread_mutex_lock (&alarm_mutex);
	if (status != 0)
		err_abort (status, "Lock mutex");

	while (1) {
		// 나머지를 구현하세요.
		struct timespec ts;
		ts.tv_sec = 5;
		ts.tv_nsec = 0;
		pthread_cond_timedwait(&alarm_cond, &alarm_mutex, &ts);
		if(alarm_list.next != &alarm_list)
		{
			alarm_t * temp = alarm_list.next;

			while(temp->seconds > 0)
			{
				sleep(1);
				for(alarm_t * temp2 = alarm_list.next; temp2 != &alarm_list; temp2 = temp2->next)
				{
					temp2->seconds--;
					temp = alarm_list.next;
				}
				if(temp->seconds == 0) break;
			}
			printf("%s\n", temp->message);
			alarm_list.next = temp->next;
			free(temp);
		}
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
		if (fgets(line, sizeof(line), stdin) == NULL)
			exit (0);

		if (strlen(line) <= 1)
			continue;

		if (strncmp(line, "list", 4) == 0) {
			display_list();
			continue;
		}

		// 이곳에서 알람 생성 및 리스트 추가 그리고 시그널 전송 코드를
		// 구현합니다.
		char * time_str = strtok(line, " ");
		int time_int = atoi(time_str);
		char * line_ptr = line;
		for(int i = 0; i < strlen(time_str); i++, line_ptr++);
		char * msg_str = strdup(line + strlen(time_str) + 1);
		if(msg_str[strlen(msg_str) - 1] == '\n') msg_str[strlen(msg_str) - 1] = '\0';
		alarm_t * new_alarm = (alarm_t *)calloc(1, sizeof(alarm_t));
		new_alarm->next = NULL;
		new_alarm->seconds = time_int;
		new_alarm->time = 0;
		strcpy(new_alarm->message, msg_str);
		alarm_insert(new_alarm);
		pthread_cond_signal(&alarm_cond);
		memset(line, 0, sizeof(line));
	}
}
