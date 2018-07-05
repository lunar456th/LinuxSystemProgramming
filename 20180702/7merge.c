
#include <stdio.h>
#include <string.h>

typedef struct {
	char fname[20];     // 파일의 이름 저장
	int  fsize;         // 파일의 크기 저장
} INFO;

int get_fsize( FILE *fp ) {
	int fsize, fpos;
	fpos = ftell( fp );
	fseek( fp, 0, SEEK_END );
	fsize = ftell( fp );
	fseek( fp, fpos, SEEK_SET );
	return fsize;
}

// ./merge    hello.txt world.txt out.merge
//   argv[0]  argv[1]   argv[2]   argv[3]
int main( int argc, char **argv ) {
	INFO info;
	FILE *src, *dst;
	int ret,i;
	char buff[4096];

	dst = fopen( argv[argc-1], "w" );

	for( i=0; i<argc-2; i++)	{
		src = fopen( argv[i+1], "r" ); 
		strcpy(info.fname, argv[i+1] );  // 파일의 이름 저장
		info.fsize = get_fsize( src );   // 파일의 크기 저장
		fwrite( &info, 1, sizeof info, dst ); // info 저장
		while( ret = fread( buff, 1, sizeof buff, src) )
			fwrite( buff, 1, ret, dst );    
		fclose(src);
	}
	fclose(dst);
}


