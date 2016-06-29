#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <climits>
//---------------------------------------------------------------------------
#pragma argsused
unsigned int licznik = 0;
struct dane_dla_watku // tablica zawiera dane, ktore otrzymaja w¹tki
{
 char nazwa[50];
 int parametr;
} ;
HANDLE wat;
 DWORD WINAPI funkcja_watku( void *argumenty );

int priorytetyProc[4] = { IDLE_PRIORITY_CLASS ,NORMAL_PRIORITY_CLASS, HIGH_PRIORITY_CLASS, REALTIME_PRIORITY_CLASS};
char nazwyProc[][30]={"IDLE_PRIORITY_CLASS" ,"NORMAL_PRIORITY_CLASS", "HIGH_PRIORITY_CLASS", "REALTIME_PRIORITY_CLASS"};
int priorytety[3] = { THREAD_PRIORITY_BELOW_NORMAL, THREAD_PRIORITY_NORMAL, THREAD_PRIORITY_ABOVE_NORMAL};
char nazwy[][30]={ "THREAD_PRIORITY_BELOW_NORMAL", "THREAD_PRIORITY_NORMAL", "THREAD_PRIORITY_ABOVE_NORMAL"};

void stworzProces(int i){
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	//char atrybuty[120]="C:\\Users\\Ada\\Documents\\Visual Studio 2012\\Projects\\Rozproszone\\cos2\\Debug\\cos2.exe ";
	char atrybuty[120]="C:\\Users\\Ada\\Documents\\Visual Studio 2012\\Projects\\Rozproszone\\watk\\Debug\\watk.exe ";
	for(int b=0; b<30; b++)
		atrybuty[83+b]=nazwyProc[i][b];
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
			
			if (!CreateProcess(NULL, atrybuty,	NULL,NULL,FALSE,CREATE_NEW_CONSOLE,	NULL,NULL,&si,&pi) 
				)			
				printf("\nNie udalo sie uruchomic nowego procesu\n");
			else{
				printf("\nStworzono nowy proces\n");
				SetPriorityClass(pi.hProcess, priorytetyProc[i]);
			}
}
void stworzWatek(int i){
	DWORD id; // identyfikator w¹tku
 
	 wat =CreateThread( NULL, 0, funkcja_watku, NULL, 0, &id );
	 if( wat= INVALID_HANDLE_VALUE ){ 
		 printf( "Utworzono watek o identyfikatorze %x o piorytecie: %s\n", id, nazwy[i] );
		// ustawienie priorytetu
		SetThreadPriority( wat, priorytety[i] );
	 }
	 Sleep( 3000 ); // uœpienie w¹tku g³ównego na 20 s
	 printf("\n w ciagu 3 s wykonano %d obliczen\n", licznik);
	 if(TerminateThread(wat,0))
		 printf("zabito");
	 //return watek;
}
DWORD WINAPI funkcja_watku( void *argumenty ){
	licznik = 0;
	while( 1 ) {
		licznik++;
		if(licznik%10000000==0)
			printf( "." );
		if(licznik==INT_MAX)
			ExitThread(0);
	}
 return 0;
}

void napisz(){
	printf("CREATE_PROC\n\n");

	printf("1. IDLE_PRIORITY_CLASS\n");
	printf("2. NORMAL_PRIORITY_CLASS\n");
	printf("3. HIGH_PRIORITY_CLASS\n");
	printf("4. REALTIME_PRIORITY_CLASS\n\n");

	printf("CREATE_THREAD\n");

	printf("1. THREAD_PRIORITY_BELOW_NORMAL\n");
	printf("2. THREAD_PRIORITY_NORMAL\n");
	printf("3. THREAD_PRIORITY_ABOVE_NORMAL\n");



}
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
	system("cls");
	HANDLE watek;
	int i, j=0;
	napisz();
	
	while(1){
		char  znak[100];
		scanf("%s",znak);	

		if(znak[7]=='P'||znak[7]=='p'){
			
			scanf("%d", &i);
			if(i>0&&i<5)
			stworzProces(i-1);
		}
		else if(znak[7]=='T'||znak[7]=='t'){
			scanf("%d", &i);
			if(i>0&&i<4)
			//HANDLE ten=stworzWatek(i-1);
			stworzWatek(i-1);
			//WaitForSingleObject(ten, 3000);
			//TerminateThread(ten, 0);
			printf("\n");
		}
		else if(znak[0]=='H'){
			napisz();
		}		
	}
	 return 0;
}

