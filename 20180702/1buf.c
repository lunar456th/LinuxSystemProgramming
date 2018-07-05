

// 1buf.c
#include <stdio.h>

// 표준 입력에 대하여 flush를 하는 방법은 존재하지 않기 때문에
// 개발자들은 일반적으로 아래의 방식을 많이 사용합니다.
void flush_stdin() {
	int ch;
	do {
		ch = getchar();
	} while (ch != '\n');
}

int main() {
	int i;
	printf("input int: ");
	scanf("%d", &i);

	// 표준 입력에 대하여 flush를 하는 것은 비표준
	// fflush(stdin); // V$
	flush_stdin();

	char c;
	printf("input char: ");
	scanf("%c", &c);

	printf("char: %c, int: %d\n", c, i);
	return 0;
}


#if 0
#include <stdio.h>
#include <unistd.h>

// 프로그램 상에서 디버깅 메시지나 에러 메시지를 출력하고 싶다면
// 버퍼가 없는 stderr에 전송해야만 프로세스 비정상 종료시에도 메지시를
// 확인할 수 있습니다.
int main() {
	printf("hello, world");
	// return 0;	// exit(main()); == exit(0);
	_exit(0);		// in exit(0);
}
#endif

#if 0
#include <stdio.h>
#include <unistd.h>

int main() {
	fprintf(stdout, "hello, world\n");	// == printf("hello, world\n");
	fprintf(stderr, "hello, world");
	sleep(5);
	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <unistd.h>

int main() {
	// printf는 라인 버퍼를 사용하기 때문에 개행 문자가 없으면
	// 버퍼를 비우지 않습니다.
	// printf("hello, world");

	//printf("hello, world\n");
	
	printf("hello, world");
	// 강제적으로 버퍼를 비우고 싶다면 fflush 함수를 사용해야 합니다.
	fflush(stdout);	// stdin, stdout, stderr
	sleep(-1);	// 찾고자 하는 함수명에 커서를 위치시키고 3 + K
				// 메뉴얼 페이지에서 나오는 방법은 q(quit)를 입력

	return 0;
}
#endif
