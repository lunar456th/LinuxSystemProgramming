
#if 1
#include <stdio.h>

// 현재 프로그램은 파일의 크기를 구하기 위해 파일 위치를 이동시킨 후,
// 복원하지 않아 프로그램이 제대로 동작하지 않습니다. 이를 해결하기 위해
// 파일의 위치를 복원하는 코드를 추가합니다.
long get_size(FILE *fp) {
	// 1. 현재 파일의 위치를 백업
	long fpos = ftell(fp);

	// 2. 파일의 위치를 끝으로 이동
	fseek(fp, 0 , SEEK_END);
	long fsize = ftell(fp);

	// 3. 파일의 위치를 복원
	fseek(fp, fpos, SEEK_SET);
	return fsize;
}

int main(int argc, char **argv) {
	++argc;
	++argv;

	FILE *fp = fopen(*argv, "r");	// fp = 0x12FF60;
	long fsize = get_size(fp);		// get_size(0x12FF60);
	printf("size: %ld\n", fsize);

	int nread;
	char buf[4096];

	while (nread = fread(buf, sizeof(char), sizeof(buf), fp)) {
		fwrite(buf, sizeof(char), nread, stdout);
		fflush(stdout);
	}

	fclose(fp);
	return 0;
}
#endif
#if 0
#include <stdio.h>

long get_size(FILE *fp) {
	fseek(fp, 0 , SEEK_END);
	return ftell(fp);
}

// 현재 프로그램은 파일의 크기를 출력한 다음 파일을 내용을 출력한다고
// 가정하겠습니다.
int main(int argc, char **argv) {
	++argc;
	++argv;

	FILE *fp = fopen(*argv, "r");
	long fsize = get_size(fp);
	printf("size: %ld\n", fsize);

	int nread;
	char buf[4096];

	while (nread = fread(buf, sizeof(char), sizeof(buf), fp)) {
		fwrite(buf, sizeof(char), nread, stdout);
		fflush(stdout);
	}

	fclose(fp);
	return 0;
}
#endif

#if 0

// 6fsize.c
#include <stdio.h>

// a.out file_name
int main(int argc, char **argv) {
	++argc;
	++argv;

	FILE *fp = fopen(*argv, "r");

	fseek(fp, 0 , SEEK_END);	// 파일 위치는 끝으로 이동
	long fsize = ftell(fp);		// 파일의 위치를 읽음

	printf("size: %ld\n", fsize);
	return 0;
}
#endif
