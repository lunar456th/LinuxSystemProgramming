
// 1myls.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


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
	char perm[] = "----------";

	if      (S_ISDIR(sb.st_mode))  perm[0] = 'd';
	else if (S_ISCHR(sb.st_mode))  perm[0] = 'c';
	else if (S_ISBLK(sb.st_mode))  perm[0] = 'b';
	else if (S_ISFIFO(sb.st_mode)) perm[0] = 'p';
	else if (S_ISLNK(sb.st_mode))  perm[0] = 'l';
	else if (S_ISSOCK(sb.st_mode)) perm[0] = 's';

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

	printf("%s ", perm);
	printf("%lu ", sb.st_nlink); 

	struct passwd *pwd = getpwuid(sb.st_uid);	// /etc/passwd 파일로부터 참조
	printf("%s ", pwd->pw_name);
	struct group *grp = getgrgid(sb.st_gid);	// /etc/group 파일로부터 참조
	printf("%s ", grp->gr_name); 

	if ((*perm == 'c') || (*perm == 'b'))
		printf("%lu, %lu ", (sb.st_rdev >> 8) & 0xff, sb.st_rdev & 0xff);
	else
		printf("%lu ", sb.st_size); 

	// printf("%lu ", sb.st_mtime); 
	// printf("%s ", ctime(&sb.st_mtime));
	struct tm *tmp = localtime(&sb.st_mtime );
	printf("%2d월 %2d %02d:%02d ", tmp->tm_mon+1, tmp->tm_mday, tmp->tm_hour, tmp->tm_min );

	if (*perm == 'l') {
		char symlink[256];
		int ret = readlink(*argv, symlink, sizeof(symlink));
		symlink[ret] = 0;
		printf("%s -> %s\n", *argv, symlink);
	}
	else
		printf("%s\n", *argv); 

	return 0;
} 
