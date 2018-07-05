#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


void my_ls(char *d_name) {
	chdir(d_name); // 해당 디렉터리로 이동
	printf("%s\n", d_name);
	// 디렉터리의 내용만 출력
	DIR *dp = opendir(".");
	struct dirent *p = readdir(dp);
	while (p != NULL) {
		printf("%s ", p->d_name);
		p = readdir(dp);
	}
	printf("\n");
	// 파일의 옵셋을 처음으로 이동
	rewinddir(dp);
	// 하위 디렉터리에 대하여 재귀 호출
	p = readdir(dp);
	while (p != NULL) {
		struct stat buf;
		lstat(p->d_name, &buf);
		if (S_ISDIR(buf.st_mode)) {
			if (strcmp(p->d_name, ".") && strcmp(p->d_name, ".."))
				my_ls(p->d_name);
		}
		p = readdir(dp);
	}
	closedir(dp);
	chdir(".."); // 부모 디렉터리로 이동
}
int main() {
	my_ls(".");
	return 0;
} 

#if 0
// 2dir.c
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

// 기존의 코드는 .과 ..에 대해서 재귀를 수행하므로 이는 스택 오버플로를 
// 발생시키게 됩니다. 이를 해결하려면 .과 ..에 대해서는 재귀를 수행하지 않습니다.
void my_ls(char *d_name) {
	// 해당 디렉터리로 이동
	chdir(d_name);
	//-------------------------------------
	DIR *dp = opendir(".");
	struct dirent *p = readdir(dp);
	while (p != NULL) {
		printf("%s\n", p->d_name);
		//my_ls(p->d_name);	// 재귀 호출

		struct stat buf;
		lstat(p->d_name, &buf);
		if (S_ISDIR(buf.st_mode)) {
			if (strcmp(p->d_name, ".") && strcmp(p->d_name, ".."))
				my_ls(p->d_name);
		}

		p = readdir(dp);
	}
	closedir(dp);
	//-------------------------------------
	chdir("..");	// 상위(부모) 디렉터리로 이동
}

int main() {
	my_ls(".");
	return 0;
}
#endif
#if 0
// 2dir.c
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

void my_ls(char *d_name) {
	// 해당 디렉터리로 이동
	chdir(d_name);
	//-------------------------------------
	DIR *dp = opendir(".");
	struct dirent *p = readdir(dp);
	while (p != NULL) {
		printf("%s\n", p->d_name);
		my_ls(p->d_name);	// 재귀 호출
		p = readdir(dp);
	}
	closedir(dp);
	//-------------------------------------
	chdir("..");	// 상위(부모) 디렉터리로 이동
}

int main() {
	my_ls(".");
	return 0;
}
#endif

#if 0
// 2dir.c
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main() {
	DIR *dp = opendir(".");

	struct dirent *p = readdir(dp);
	while (p != NULL) {
		printf("%s\n", p->d_name);
		p = readdir(dp);
	}

	closedir(dp);

	return 0;
}
#endif
#if 0
// 2dir.c
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main() {
	DIR *dp = opendir(".");

	struct dirent *p = readdir(dp);
	printf("%s\n", p->d_name);

	closedir(dp);

	return 0;
}
#endif
