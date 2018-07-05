
// Bftype.c

// lstat 함수를 사용하면 파일의 정보를 얻어올 수 있습니다.
#include <sys/stat.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <FILE_NAME>\n", *argv);
		return -1;
	}
	++argc;
	++argv;

	struct stat sb;	// g + ], 이동 후 복귀하는 방법: CTRL + T
	if (lstat(*argv, &sb) == -1)
		return -1;

	// 파일의 타입을 출력
	// printf("sb.st_mode: %X\n", sb.st_mode);

#if 0
	switch (sb.st_mode & S_IFMT) {
		case S_IFBLK: printf("block device\n"); break;
		case S_IFCHR: printf("character device\n"); break;
		case S_IFDIR: printf("directory\n"); break;
		case S_IFIFO: printf("FIFO/pipe\n"); break;
		case S_IFLNK: printf("symlink\n"); break;
		case S_IFREG: printf("regular file\n"); break;
		case S_IFSOCK: printf("socket\n"); break;
		default: printf("unknown\n"); break;
	} 
#endif 
	if      (S_ISREG(buf.st_mode))	ptr = "regular";
	else if (S_ISDIR(buf.st_mode))	ptr = "directory";
	else if (S_ISCHR(buf.st_mode))	ptr = "character special";
	else if (S_ISBLK(buf.st_mode))	ptr = "block special";
	else if (S_ISFIFO(buf.st_mode))	ptr = "fifo";
	else if (S_ISLNK(buf.st_mode))	ptr = "symbolic link";
	else if (S_ISSOCK(buf.st_mode))	ptr = "socket";
	else				ptr = "** unknown mode **";

	return 0;
} 

