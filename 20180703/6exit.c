
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	if (fork() == 0) {
		// ...
		// exit(2);	// 종료 코드 설정
		while(1);
	}

	int exit_code;
	wait(&exit_code);

	if( WIFEXITED(exit_code) )
		printf("정상종료 : exit(%d)\n", WEXITSTATUS(exit_code) );
	else if( WIFSIGNALED(exit_code) )
	{
		printf("비정상종료 : signo(%d) %s\n", WTERMSIG(exit_code),
				(WCOREDUMP(exit_code))?"(core dumped)":"" );
	}
	return 0;
}

#if 0
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	if (fork() == 0) {
		// ...
		// exit(2);	// 종료 코드 설정
		while(1);
	}

	int exit_code;
	wait(&exit_code);

	// if ((exit_code & 0xFF) == 0)	
	printf("%d\n", (exit_code >> 8) & 0xFF);
	else
		printf("signo: %d %s\n", exit_code & 0xFF,
				(exit_code & 0x80)	? "(core dumped)" : "");
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	if (fork() == 0) {
		// ...
		// exit(2);	// 종료 코드 설정
		while(1);
	}

	int exit_code;
	wait(&exit_code);

	if ((exit_code & 0xFF) == 0)	// 정상 종료(exit)
		printf("%d\n", (exit_code >> 8) & 0xFF);
	else	// 비정상 종료(시그널)
		printf("signo: %d\n", exit_code & 0xFF);
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	if (fork() == 0) {
		// ...
		exit(2);	// 종료 코드 설정
	}

	int exit_code;
	wait(&exit_code);

	if ((exit_code & 0xFF) == 0)	// 정상 종료(exit)
		printf("%d\n", (exit_code >> 8) & 0xFF);
	return 0;
}
#endif
