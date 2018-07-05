

// Cperm.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>	// for toupper();

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <FILE_NAME>\n", *argv);
		return -1;
	}
	++argc;
	++argv;
	struct stat sb;
	if (lstat(*argv, &sb) == -1) {
		perror("lstat");
		return -1;
	}
	char perm[] = " ---------";
	char rwx[] = "rwx";
	for (int i = 0; i < 9; i++) {
		if ((sb.st_mode >> (8 - i)) & 0x1)
			perm[1 + i] = rwx[i % 3];
	}

	char sst[] = "sst";
	for (int i = 0; i < 3; i++) {
		if ((sb.st_mode >> (11 - i)) & 0x1) {
			if (perm[(i + 1) * 3] == '-')
				perm[(i + 1) * 3] = toupper(sst[i]);
			else
				perm[(i + 1) * 3] = sst[i];
		}
	} 



	printf("%s\n", perm);
	return 0;
} 
