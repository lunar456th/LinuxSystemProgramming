
#if 1
// 4error.c
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>	// extern int errno;

int main() {
	pthread_t tid;
	int ret = pthread_join(tid, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_join: %s\n", strerror(ret));
		return -1;
	}
	return 0;
}
#endif
#if 0
// 4error.c
#include <stdio.h>
#include <string.h>
#include <errno.h>	// extern int errno;

void print_error(const char *msg) {
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

int main() {
	// 표준 라이브러리 함수의 대부분은 함수 호출이 실패할 경우, 에러 코드(errno)를
	// 설정합니다
	FILE *fp = fopen("xyz", "r");
	if (fp == NULL) {
		perror("fopen");	// print_error("fopen");
		return -1;
	}

	char buf[1024];
	fgets(buf, sizeof buf, fp);

	printf("%s\n", buf);

	fclose(fp);
	return 0;
}
#endif
#if 0
// 4error.c
#include <stdio.h>
#include <string.h>
#include <errno.h>	// extern int errno;

int main() {
	// 표준 라이브러리 함수의 대부분은 함수 호출이 실패할 경우, 에러 코드(errno)를
	// 설정합니다
	FILE *fp = fopen("xyz", "r");
	if (fp == NULL) {
		// fprintf(stderr, "fopen: %d\n", errno);
		fprintf(stderr, "fopen: %s\n", strerror(errno));
		return -1;
	}

	char buf[1024];
	fgets(buf, sizeof buf, fp);

	printf("%s\n", buf);

	fclose(fp);
	return 0;
}
#endif
#if 0
// 4error.c
#include <stdio.h>

int main() {
	FILE *fp = fopen("xyz", "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen error\n");
		return -1;
	}

	char buf[1024];
	fgets(buf, sizeof buf, fp);

	printf("%s\n", buf);

	fclose(fp);
	return 0;
}
#endif
