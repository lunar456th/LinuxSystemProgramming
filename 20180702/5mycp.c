
// 5mycp.c
#include <stdio.h>

int main(int argc, char **argv) {
	FILE *src, *dst;
	int ret;
	char buff[4096];

	src = fopen( argv[1], "r" );
	dst = fopen( argv[2], "w" );  

	while( ret = fread( buff, 1, sizeof buff, src) )
		fwrite( buff, 1, ret, dst );

	fclose(src);
	fclose(dst);

	return 0;
}
