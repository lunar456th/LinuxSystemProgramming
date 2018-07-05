
// 1daemon.c


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <syslog.h>

int daemon_init(void) {
	if(fork() > 0)
		exit(0); 
	setsid();               /* become session leader */
	chdir("/");             /* change working directory */
	umask(0);               /* clear our file mode creation mask */

	for(int i = 0;i < 64; i++)
		close(i);
	
	signal(SIGCLD,SIG_IGN);
	return(0);
}

int main(void) {
	daemon_init();
	// printf("hello, world\n");

	// /var/log/syslog
	syslog(1, "%s\n", "hello, world\n");

	sleep(100);
}


