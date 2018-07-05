
#if 1
// 3io.c
#include <stdio.h>
#include <unistd.h>

// 이전 프로그램의 경우, 행 단위로 입출력을 수행합니다. 이는 행의 크기가
// 버퍼의 크기보다 작은 경우, 복사의 오버헤드 및 메모리의 낭비가 발생합니다.
// 이를 해결하기 위해 버퍼를 다 사용하여 입출력을 수행합니다.
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <FILE_NAME>\n", *argv);
		return -1;
	}

	++argc;
	++argv;

	FILE *fp = fopen(*argv, "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen");
		return -1;
	}

	int nread;
	char buf[1024];	// 2의 승수 단위로 버퍼의 크기를 설정하는 것이 좋습니다.
	while(nread = fread(buf, sizeof(char), sizeof(buf), fp)) {
		usleep(100000);
		fwrite(buf, sizeof(char), sizeof(char)*nread, stdout);
		fflush(stdout);
	}

	fclose(fp);
	return 0;
}
#endif
#if 0
// 3io.c
#include <stdio.h>
#include <unistd.h>

// 이전 프로그램의 경우, 바이트 단위로 입출력이 이루어지기 때문에 성능 상의
// 이슈가 있습니다. 이를 해결하기 위해 라인 단위로 입출력을 합니다.
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <FILE_NAME>\n", *argv);
		return -1;
	}

	++argc;
	++argv;

	FILE *fp = fopen(*argv, "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen");
		return -1;
	}

	char buf[1024];	// 2의 승수 단위로 버퍼의 크기를 설정하는 것이 좋습니다.
	while(fgets(buf, sizeof(buf), fp)) {
		usleep(100000);
		fputs(buf, stdout);
		fflush(stdout);
	}

	fclose(fp);
	return 0;
}
#endif
#if 0
// 3io.c
#include <stdio.h>
#include <unistd.h>

// 파일을 표준 출력으로 전송하는 프로그램입니다.
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <FILE_NAME>\n", *argv);
		return -1;
	}

	++argc;
	++argv;

	FILE *fp = fopen(*argv, "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen");
		return -1;
	}

	int ch = fgetc(fp);
	while (ch != EOF) {
		fputc(ch, stdout);
		fflush(stdout);

		usleep(100000);
		ch = fgetc(fp);
	}

	fclose(fp);
	return 0;
}
#endif
#if 0
// 3io.c
#include <stdio.h>

// 파일을 표준 출력으로 전송하는 프로그램입니다.
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <FILE_NAME>\n", *argv);
		return -1;
	}

	++argc;
	++argv;

	FILE *fp = fopen(*argv, "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen");
		return -1;
	}

	int ch = fgetc(fp);
	fputc(ch, stdout);
	fflush(stdout);

	fclose(fp);
	return 0;
}
#endif
