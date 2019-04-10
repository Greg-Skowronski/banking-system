#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int MAXNO = 10;

void StartScreen();

typedef struct {
	char surname[40];
	char name[20];
	char id[10];
	char address[80];
	double balance;
} CLIENT; //data of a client 

int main()
{
    StartScreen();
    return 0;
}

void StartScreen()
{
    printf("\n\n");
    printf("=========================================\n");
    printf("== Welcome to the GregPayments Online! ==\n");
    printf("=========================================\n\n");
    
    FILE* fPointer;
    CLIENT none={"","","","",0.0};
    fPointer = fopen("DATABASE.bin","r+");
    
    if(fPointer==NULL) 
    {
        printf("\nNo database found.\n...Creating new one...\n");
        fPointer = fopen("DATABASE.bin","w+");
        for(int index=0;index<MAXNO;index++) fwrite(&none,sizeof(CLIENT),1,fPointer); 
        printf("Done!\n\n");
    }
    
    fclose(fPointer);
    
}
