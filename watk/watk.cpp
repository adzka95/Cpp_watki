#include <windows.h>
#include <stdio.h>
//#include <conio.h>
//---------------------------------------------------------------------------
#pragma argsused
struct dane_dla_watku // tablica zawiera dane, ktore otrzymaja w�tki
{
	 char nazwa[50];
	 int parametr;
} dane[3] = { { "THREAD_PRIORITY_BELOW_NORMAL", 2 }, { "THREAD_PRIORITY_NORMA", 5 }, { "THREAD_PRIORITY_ABOVE_NORMAL", 8 } };
 // priorytety w�tk�w
int priorytety[3] = { THREAD_PRIORITY_BELOW_NORMAL, THREAD_PRIORITY_NORMAL, THREAD_PRIORITY_ABOVE_NORMAL};

void gotoxy(int x, int y){
     COORD c;
     c.X = x-1;
     c.Y = y-1;
     SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
}

HANDLE watki[3]; // doj�cia (uchwyty) w�tk�w
 // deklaracja funkcji w�tku
DWORD WINAPI funkcja_watku( void *argumenty );
//---------------------------------------------------------------------------
int main(int argc, char **argv){
	 int i;
	 DWORD id; // identyfikator w�tku
	system ("cls");
	 //printf( "Uruchomienie programu\n" );
	 // tworzenie w�tk�w
	for(int i=0; i<3; i++){
	gotoxy( 1, dane[i].parametr-1 );
	printf( "%s", dane[i].nazwa );
	}
	 for( i = 0; i < 3; i++ ){
		 watki[i] = CreateThread(
		 NULL, // atrybuty bezpiecze�stwa
		 0, // inicjalna wielko�� stosu
		 funkcja_watku, // funkcja w�tku
		 (void *)&dane[i],// dane dla funkcji w�tku
		 0, // flagi utworzenia
		 &id );
		 if( watki[i] != INVALID_HANDLE_VALUE ){
			SetThreadPriority( watki[i], priorytety[i] );
		 }
	 }
	 Sleep( 20000 ); // u�pienie w�tku g��wnego na 20 s
	 for(i=0; i<3; i++){
		 TerminateThread(watki[i],0);
	 }
	  Sleep( 5000 );
	  ExitProcess(0);
	  printf("nie powinno byc widac");
	  Sleep( 5000 );
	 return 0;
}
//---------------------------------------------------------------------------
// trzy takie funkcje pracuj� wsp�bie�nie w programie
DWORD WINAPI funkcja_watku( void *argumenty ){
	 unsigned int licznik = 0;
	 // rzutowanie struktury na w�asny wska�nik
	 struct dane_dla_watku *moje_dane = (struct dane_dla_watku *)argumenty; 
	 Sleep( 1000 );
	 while( 1 ){
		 gotoxy( licznik++ / 5000+1, moje_dane->parametr );
		 printf( "*" );
	 }
	 return 0;
}
