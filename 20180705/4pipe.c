
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSGSIZE 20

int main() {
	int fd[2];
	int pid;
	char msgout[MSGSIZE] = "Hello, world\n";
	char msgin[MSGSIZE];

	if(pipe(fd)==-1) {
		perror("pipe()");
		exit(1);
	}
	if ((pid = fork()) > 0) {
		close(fd[0]);
		write(fd[1], msgout, MSGSIZE);
	}
	else if (pid == 0) {
		close(fd[1]);
		read(fd[0],msgin,MSGSIZE);
		puts(msgin);
	}
	else {
		perror("fork()");
		exit(2);
	}
}
#if 0
// 4pipe.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MSGSIZE 16

char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";
char *msg3 = "hello, world #3";

int main() {
	char inbuf[1024];
	int p[2], j;
	int ret;

	if (pipe(p) < 0) {
		perror("pipe call");
		exit(1);
	}
	/* write down pipe */
	write(p[1], msg1, MSGSIZE);
	write(p[1], msg2, MSGSIZE);
	write(p[1], msg3, MSGSIZE);

	while(1) {
		ret = read(p[0], inbuf, sizeof(inbuf));
		write( 1, inbuf, ret );
		getchar();
	}
	return 0;
}
#endif
