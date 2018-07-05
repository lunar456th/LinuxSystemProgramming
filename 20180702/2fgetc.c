
// 2fget.c
#include <stdio.h>

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

	int fsize = 0;
	int ch = fgetc(fp); // char ch = fgetc(fp);
	while (ch != EOF) {
		++fsize;
		ch = fgetc(fp);
	}

	printf("size: %d\n", fsize);
	fclose(fp);
	return 0;
}
