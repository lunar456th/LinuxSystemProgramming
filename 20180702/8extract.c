
#include <stdio.h>
#include <string.h>

typedef struct
{
	char fname[20];
	int  fsize;
} INFO;
// extract   target
int main( int argc, char **argv )
{
	INFO info;
	FILE *src, *dst;
	int ret,i, len;
	char buff[4096];

	src = fopen( argv[1], "r" ); 

	while( ret = fread( &info, 1, sizeof info, src) )
	{
		dst = fopen( info.fname, "w" );
		while( info.fsize > 0 )  // 파일의 크기가 소진 됐는가?
		{
			len = (sizeof buff < info.fsize ) ? sizeof buff : info.fsize;
			// 파일의 크기와 buffer의 크기중 작은것 선택
			ret = fread( buff, 1, len, src); 
			fwrite( buff, 1, ret, dst );    
			info.fsize -= ret; // 읽은 만큼 감산
		}
		fclose(dst);
	}
	fclose(src);
}




