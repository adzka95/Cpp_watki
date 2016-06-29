#include <stdio.h>
#include <windows.h>
int main(int argc, char **argv){
	
	printf("Zglasza sie nowy proces o priorytecie: %s", argv[1]);
	int licznik = 0;
	while( 1 ) {
		licznik++;
		if(licznik%10000000==0)
			printf( "." );
	}
	
	return 0;
}