#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#define MAX 1024
#define MAXNO 25
#define MAX_FIRST 30
#define MAX_LAST 50
#define MAX_ID 30
#define MAX_ADDR 80
#define TRUE 1
#define FALSE 0

void Start();
void Menu();
void ClearBuffor();
int Confirm();

void Add();
void Print();
void ClearAll();
void Payment();
void Withdrawal();
void Transfer();
void Find();

void SearchString(char[], float, char);
int CheckString(char[]);


struct Client {
    int NO;
    char first[MAX_FIRST];
    char last[MAX_LAST];
    char id[MAX_ID];
    char addr[MAX_ADDR];
    float acct;
};

int main() {
    
    Start();
    
    Menu();
    
    return 0;
}

void Start()
{
    
    FILE * pFile;
    pFile = fopen("DATA.dat", "rb+");
    
    if(pFile == NULL)
    {
        printf("\n\n");
        perror("Error Occured");
        printf("Creating new database...\n");
        pFile = fopen("DATA.dat", "wb+");
        
        if(pFile == NULL)
        {
            perror("Error Occured");
            exit(1);
        }
        printf("\nDone!");
    }
    
    printf("\n\n");
    printf("+-------------------------------------+\n");
    printf("| Welcome to the GregPayments Online! |\n");
    printf("+-------------------------------------+\n");
    
    fclose(pFile);
}

void Menu()
{
    char Clear;
    int Decision;
    while(1)
    {
        printf("\n\n");
    printf("     +---------------------------+\n");
    printf("     | 1. Create a new account.  |\n");
    printf("     | 2. Display all clients.   |\n");
    printf("     | 3. Make a payment.        |\n");
    printf("     | 4. Make a withdrawal.     |\n");
    printf("     | 5. Make a money transfer. |\n");
    printf("     | 6. Find...                |\n");
    printf("     | 7. !Clear!                |\n");
    printf("     | 8. Exit.                  |\n");
    printf("     +---------------------------+\n");
    
    while(scanf("%d",&Decision)!=1)
    {
        while ((Clear = getchar()) != '\n' && Clear != EOF)
            printf("Error Occured: Not a number.\n");
    }
    
    switch(Decision)
    {
        case 1:
        {
            Add();
            break;
        }
        case 2:
        {
            Print();
            break;
        }
        case 3:
        {
            Payment();
            break;
        }
        case 4:
        {
            Withdrawal();
            break;
        }
        case 5:
        {
            Transfer();
            break;
        }
        case 6:
        {
            Find();
            break;
        }
        case 7:
        {
            ClearAll();
            break;
        }
        case 8:
        {
            printf("\nHave a nice day!\n\n");
            return;
        }
        default:
        {
            printf("Error Occured: Not action found.\n");
            break;
        }
    }
    
    /*ClearBuffor();*/
    
    }
}

void ClearBuffor()
{
    char Clear;
    while ((Clear = getchar()) != '\n' && Clear != EOF);
}

int Confirm()
{
    char Decision;
  
    ClearBuffor();
    
    printf("\nDo you confirm it? Y/N ");
    
    Decision = getchar();
    
    if(Decision == 'Y' || Decision == 'y') return TRUE;
    
    return FALSE;
}

void Add()
{
  char temp[MAX] = "";
  int Good=FALSE;
  FILE * pFile;
    int CurrChar;
    struct Client new = {0, "", "", "", "", 0.0};
    struct Client curr = {0, "", "", "", "", 0.0};
    int Quantity=0;
    
    ClearBuffor();
    
    do{
    printf("Enter first name: ");
    fgets(temp,MAX,stdin);
    strcpy(new.first,temp);
    if(temp[MAX_FIRST]!='\0') 
    {
      printf("String exceeded max size. Bank cut your data.\n");
      new.first[MAX_FIRST-1]='\0';
    }
    new.first[strlen(new.first)-1]='\0';
    if(CheckString(new.first)==TRUE) Good=FALSE;
    else Good=TRUE;
    }while(Good==FALSE);
    
    do{
    printf("Enter last name: ");
    fgets(temp,MAX,stdin);
    strcpy(new.last,temp);
    if(temp[MAX_LAST]!='\0') 
    {
      printf("String exceeded max size. Bank cut your data.\n");
      new.last[MAX_LAST-1]='\0';
    }
    new.last[strlen(new.last)-1]='\0';
    if(CheckString(new.last)==TRUE) Good=FALSE;
    else Good=TRUE;
    }while(Good==FALSE);
    
    do{
      Good=TRUE;
    printf("Enter ID: ");
    fgets(new.id,30,stdin);
    new.id[strlen(new.id)-1]='\0';
    
    for(CurrChar=0; CurrChar<strlen(new.id); CurrChar++)
    {
        if(isdigit(new.id[CurrChar])==0)
        {
            printf("Error Occured. PESEL should have only digits.\n");
            Good=FALSE;
        }
    }
    if(strlen(new.id)!=11) 
    {
        printf("Error Occured. PESEL has 11 digits.\n");
        Good=FALSE;
    }
    }while(Good==FALSE);
    
    do{
      
      Good=TRUE;
    printf("Enter address: ");
    scanf("%[^\n]s", (char*)new.addr);
    if(isspace(new.addr[0])!=0 || strcmp(new.addr,"")==0) 
    {
        printf("Error Occured. Address is required.\n");
        Good=FALSE;
    }
    if(strlen(new.addr)>MAX_ADDR || strlen(new.addr)<2)
    {
        printf("Error Occured. Address is too long/short.\n");
        Good=FALSE;
    }
    /*ClearBuffor();*/
    }while(Good==FALSE);
    printf("\n\nYour entered data: \nName: %s %s\nID: %s\nAddress: %s\n",new.first,new.last,new.id,new.addr);
    
    new.acct = 0.0;
    
    if(Confirm()==TRUE)
    {
        
        pFile = fopen("DATA.dat","rb+");
        
        fseek(pFile,-1*sizeof(struct Client),2);
        fread(&curr,sizeof(struct Client),1,pFile);
        Quantity = curr.NO;
        
        new.NO = Quantity+1;
        fseek(pFile,(Quantity)*sizeof(struct Client),0);
        fwrite(&new,sizeof(struct Client),1,pFile);
        fclose(pFile);
    }
}

void Print()
{
    struct Client curr;
    FILE * pFile;
    pFile = fopen("DATA.dat", "rb+");
    
    printf("+-----+----------------------+----------------------+---------------+----------------------------------------------+\n");
    printf("|  #  |      FIRST NAME      |      LAST  NAME      |     PESEL     |             ADDRESS            |     $$$     |\n");
    printf("+-----+----------------------+----------------------+---------------+----------------------------------------------+\n");
    while (1) {
    fread(&curr, sizeof(struct Client), 1, pFile);
    if(feof(pFile)) {
      break;
    }
    printf("|%4i |%20s  |%20s  |  %11s  |%30s  |%10.2f   |\n",curr.NO,curr.first,curr.last,curr.id,curr.addr,curr.acct);
    }
    printf("+-----+----------------------+----------------------+---------------+----------------------------------------------+\n");
    fclose(pFile);
}

void ClearAll()
{
  FILE * pFile;
    if(Confirm()==TRUE)
    {
        remove("DATA.dat");
        
        pFile = fopen("DATA.dat", "rb+");
    
        if(pFile == NULL)
        {
            pFile = fopen("DATA.dat", "wb+");
            if(pFile == NULL)
            {
                perror("Error Occured");
                exit(1);
            }
            
        }
        fclose(pFile);
        printf("Data deleted successfully.\n");
    }
    else printf("Cancelled.\n");
    
}

void Payment()
{
  FILE * pFile;
  struct Client receiver = {0, "", "", "", "", 0.0};
    int ToWho;
    float Value=0;
    ClearBuffor();
    printf("Enter the user's account ID who will get money from you: \n");
    while(scanf("%d", &ToWho)!=1) 
    {
        printf("Error Occured. Not correct char.\nEnter once again:\n");
        ClearBuffor();
    }
    
    
    pFile = fopen("DATA.dat", "rb");
    fseek(pFile,(ToWho-1)*sizeof(struct Client),0);
    fread(&receiver, sizeof(struct Client), 1, pFile);
    
    if(ToWho!=receiver.NO || ToWho<1)
    {
        printf("Error Occured. Client does not exist.\n");
        fclose(pFile);
        return;
    }
    
    printf("\n\nReceiver: \nName: %s %s\nID: %s\nAddress: %s\nFunds: $%.2f\n",receiver.first,receiver.last,receiver.id,receiver.addr,receiver.acct);
    
        printf("Enter $:  ");
        ClearBuffor();
        while(scanf("%f", &Value)!=1) 
        {
            printf("Error Occured. Not correct char.\nEnter once again:\n");
            ClearBuffor();
        }
        if(Value>=LONG_MAX || Value<=0)
        {
            printf("Error Occured. Wrong value.\n");
            fclose(pFile);
            return;
        }
        if(Value+receiver.acct>=LONG_MAX)
	{
	  printf("Error Occured. Too much money.\n");
            fclose(pFile);
            return;
	}
        printf("\n\nPayment $%.2f to %s %s\nFunds after payment: $%.2f\n", Value, receiver.first, receiver.last, Value+receiver.acct);
        
        if(Confirm()==TRUE)
        {
            fclose(pFile);
            pFile = fopen("DATA.dat", "rb+");
            receiver.acct = receiver.acct + Value;
            fseek(pFile,(ToWho-1)*sizeof(struct Client),0);
            fwrite(&receiver, sizeof(struct Client), 1, pFile);
            printf("Done!\n");
        }
        
    
    
    fclose(pFile);
}

void Withdrawal()
{
  FILE * pFile;
  struct Client victim = {0, "", "", "", "", 0.0};
    int FromWho;
    float Value=0;
    ClearBuffor();
    printf("Enter the user's account ID from which you want to take the money: \n");
    while(scanf("%d", &FromWho)!=1) 
    {
        printf("Error Occured. Not correct char.\nEnter once again:\n");
        ClearBuffor();
    }
    
    
    pFile = fopen("DATA.dat", "rb");
    fseek(pFile,(FromWho-1)*sizeof(struct Client),0);
    fread(&victim, sizeof(struct Client), 1, pFile);
    
    if(FromWho!=victim.NO || FromWho<1)
    {
        printf("Error Occured. Client does not exist.\n");
        fclose(pFile);
        return;
    }
    
    printf("\n\nChosen client: \nName: %s %s\nID: %s\nAddress: %s\nFunds: $%.2f\n",victim.first,victim.last,victim.id,victim.addr,victim.acct);
    
        printf("Enter $ you want to take:  ");
        ClearBuffor();
        while(scanf("%f", &Value)!=1) 
        {
            printf("Error Occured. Not correct char.\nEnter once again:\n");
            ClearBuffor();
        }
        if(Value>=LONG_MAX || Value<=0)
        {
            printf("Error Occured. Wrong value.\n");
            fclose(pFile);
            return;
        }
        if(victim.acct-Value<0)
	{
	  printf("Error Occured. Not enough money.\n");
          fclose(pFile);
          return;
	}
        printf("\n\nTaking away $%.2f from %s %s\nFunds after withdrawal: $%.2f\n", Value, victim.first, victim.last, victim.acct-Value);
        
        if(Confirm()==TRUE)
        {
            fclose(pFile);
            pFile = fopen("DATA.dat", "rb+");
            victim.acct = victim.acct - Value;
            fseek(pFile,(FromWho-1)*sizeof(struct Client),0);
            fwrite(&victim, sizeof(struct Client), 1, pFile);
            printf("Done!\n");
        }
        
    
    
    fclose(pFile);
}

void Transfer()
{
  FILE * pFile;
  struct Client to = {0, "", "", "", "", 0.0};
  struct Client from = {0, "", "", "", "", 0.0};
    int FromWho;
    int ToWho;
    float Value=0;
    
    ClearBuffor();
    printf("Enter the sender's account ID: \n");
    while(scanf("%d", &FromWho)!=1) 
    {
        printf("Error Occured. Not correct char.\nEnter once again:\n");
        ClearBuffor();
    }
    
    
    
    pFile = fopen("DATA.dat", "rb");
    fseek(pFile,(FromWho-1)*sizeof(struct Client),0);
    fread(&from, sizeof(struct Client), 1, pFile);
    
    if(FromWho!=from.NO || FromWho<1)
    {
        printf("Error Occured. Client does not exist.\n");
        fclose(pFile);
        return;
    }
    
    ClearBuffor();
    printf("Enter the receiver's account ID: \n");
    while(scanf("%d", &ToWho)!=1) 
    {
        printf("Error Occured. Not correct char.\nEnter once again:\n");
        ClearBuffor();
    }
    
    
    fseek(pFile,(ToWho-1)*sizeof(struct Client),0);
    fread(&to, sizeof(struct Client), 1, pFile);
    
    if(ToWho!=to.NO || ToWho<1)
    {
        printf("Error Occured. Client does not exist.\n");
        fclose(pFile);
        return;
    }
    
    if(ToWho == FromWho)
    {
        printf("Error Occured. Receiver cannot be sender at the same time.\n");
        fclose(pFile);
        return;
    }
    
    printf("\n\nTransfer:\n%s %s ($%.2f) --> ($%.2f) %s %s\n",from.first,from.last,from.acct,to.acct,to.first,to.last);

        printf("\nEnter $ to transfer:  ");
        ClearBuffor();
        while(scanf("%f", &Value)!=1) 
        {
            printf("Error Occured. Not correct char.\nEnter once again:\n");
            ClearBuffor();
        }
        if(Value>=LONG_MAX || Value<=0)
        {
            printf("Error Occured. Wrong value.\n");
            fclose(pFile);
            return;
        }
        if(from.acct-Value<0)
	{
	  printf("Error Occured. Not enough money.\n");
            fclose(pFile);
            return;
	}
	if(to.acct+Value>LONG_MAX)
	{
	  printf("Error Occured. Too much money.\n");
            fclose(pFile);
            return;
	}
        printf("\n\nTransfer of $%.2f:\nSender: %s %s (funds after: $%.2f)\nReceiver: %s %s (funds after: $%.2f)",Value,from.first,from.last,from.acct-Value,to.first,to.last,to.acct+Value);
        
        if(Confirm()==TRUE)
        {
            fclose(pFile);
            pFile = fopen("DATA.dat", "rb+");
            
            from.acct = from.acct - Value;
            fseek(pFile,(FromWho-1)*sizeof(struct Client),0);
            fwrite(&from, sizeof(struct Client), 1, pFile);
            
            to.acct = to.acct + Value;
            fseek(pFile,(ToWho-1)*sizeof(struct Client),0);
            fwrite(&to, sizeof(struct Client), 1, pFile);
            
            printf("Done!\n");
            
        }
    
    
    fclose(pFile);
}

void Find()
{
  FILE * pFile;
  float SearchAcct=0;
    struct Client found = {0, "", "", "", "", 0.0};
    int Crit;
    char Clear;
    printf("Enter criterion: \n");
    printf(" 1. Account ID.\n 2. First name.\n 3. Surname.\n 4. PESEL.\n 5. Address.\n 6. Balance.\n\n");
    
    while(scanf("%d",&Crit)!=1)
    {
        while ((Clear = getchar()) != '\n' && Clear != EOF)
            printf("Error Occured: Not a number.\n");
    }
    
    switch(Crit)
    {
        case 1:
        {
            int searchedID;
            ClearBuffor();
            printf("Enter the account ID of user you want to find: \n");
            while(scanf("%d", &searchedID)!=1) 
            {
                printf("Error Occured. Not correct char.\nEnter once again:\n");
                ClearBuffor();
            }
            
            
            pFile = fopen("DATA.dat", "rb");
            fseek(pFile,(searchedID-1)*sizeof(struct Client),0);
            fread(&found, sizeof(struct Client), 1, pFile);
    
            if(searchedID!=found.NO || searchedID<1)
            {
                printf("Error Occured. Client not found.\n");
                fclose(pFile);
                return;
            }
    
            printf("\n\nClient has been found: \nName: %s %s\nID: %s\nAddress: %s\nFunds: $%.2f\n",found.first,found.last,found.id,found.addr,found.acct);
            
            fclose(pFile);
            
            break;
        }
        case 2:
        {
            ClearBuffor();
            printf("Enter first name you are searching for: ");
            fgets(found.first,30,stdin);
            found.first[strlen(found.first)-1]='\0';
            printf("\n\n");
            if(CheckString(found.first)==TRUE) return;
            
            SearchString(found.first, 0, 'F');
            break;
        }
        case 3:
        {
            ClearBuffor();    
            printf("Enter last name you are searching for: ");
            fgets(found.last,50,stdin);
            found.last[strlen(found.last)-1]='\0';
            printf("\n\n");
            if(CheckString(found.last)==TRUE) return;
            
            SearchString(found.last, 0, 'L');
            break;
        }
        case 4:
        {
	  int CurrChar;
            ClearBuffor();
            printf("Enter searched ID: ");
            fgets(found.id,30,stdin);
            found.id[strlen(found.id)-1]='\0';
            
            
            for(CurrChar=0; CurrChar<strlen(found.id); CurrChar++)
            {
                if(isdigit(found.id[CurrChar])==0)
                {
                    printf("Error Occured. PESEL should have only digits.\n");
                    return;
                }
            }
            if(strlen(found.id)!=11) 
            {
                printf("Error Occured. PESEL has 11 digits.\n");
                return;
            }
            
            SearchString(found.id, 0, 'I');
            
            break;
        }
        case 5:
        {
            ClearBuffor();
            printf("Enter address: ");
            scanf("%[^\n]s", (char*)found.addr);
            if(isspace(found.addr[0])!=0 || strcmp(found.addr,"")==0) 
            {
                printf("Error Occured. Address is required.\n");
                return;
            }
            if(strlen(found.addr)>MAX_ADDR || strlen(found.addr)<2)
            {
                printf("Error Occured. Address is too long/short.\n");
                return;
            }
            
            SearchString(found.addr, 0, 'A');
            
            break;
        }
        case 6:
        {
	  ClearBuffor();
	  printf("Enter balance you are looking for: ");
	  while(scanf("%f",&SearchAcct)!=1)
	  {
	    printf("Error Occured: Not a number.\n");
	    ClearBuffor();
	  }
	  if(SearchAcct<0 || SearchAcct>LONG_MAX)
	  {
	    printf("Error Occured. Value is too long/short.\n");
                return;
	  }
	  
	  SearchString("", SearchAcct, '$');
	  
            break;
        }
        default:
        {
            printf("Error Occured: Not action found.\n");
            break;
        }
    }
    
}

void SearchString(char searched[], float searchacct, char mode)
{
    int info=TRUE;
    struct Client found = {0, "", "", "", "", 0.0};
    int curr;
    int currMAX=0;
    char temp[sizeof(struct Client)];
    FILE * pFile;
    pFile = fopen("DATA.dat", "rb");
    
    while(1)
    {
        fgets(temp,sizeof(struct Client),pFile);
        if(feof(pFile)) break;
        currMAX++;
    }
    
    fseek(pFile,0*sizeof(struct Client),0);
    
    if(mode!='$')
    {
    for(curr=0;curr<currMAX;curr++)
    {
        fseek(pFile,curr*sizeof(struct Client),0);
        fread(&found, sizeof(struct Client), 1, pFile);
        
        if(strcmp(found.first,searched)==0 && mode=='F')
        {
            printf("\nClient has been found: \nName: %s %s\nID: %s\nAddress: %s\nFunds: $%.2f\n",found.first,found.last,found.id,found.addr,found.acct);
            info=FALSE;
        }
        
        if(strcmp(found.last,searched)==0 && mode=='L')
        {
            printf("\nClient has been found: \nName: %s %s\nID: %s\nAddress: %s\nFunds: $%.2f\n",found.first,found.last,found.id,found.addr,found.acct);
            info=FALSE;
        }
        
        if(strcmp(found.id,searched)==0 && mode=='I')
        {
            printf("\nClient has been found: \nName: %s %s\nID: %s\nAddress: %s\nFunds: $%.2f\n",found.first,found.last,found.id,found.addr,found.acct);
            info=FALSE;
        }
        
        if(strcmp(found.addr,searched)==0 && mode=='A')
        {
            printf("\nClient has been found: \nName: %s %s\nID: %s\nAddress: %s\nFunds: $%.2f\n",found.first,found.last,found.id,found.addr,found.acct);
            info=FALSE;
        }
    }
    }
    else{
      for(curr=0;curr<currMAX;curr++)
      {
	fseek(pFile,curr*sizeof(struct Client),0);
        fread(&found, sizeof(struct Client), 1, pFile);
	
	if(found.acct==searchacct && mode=='$')
        {
            printf("\nClient has been found: \nName: %s %s\nID: %s\nAddress: %s\nFunds: $%.2f\n",found.first,found.last,found.id,found.addr,found.acct);
            info=FALSE;
        }
      }
    }
    if(info==TRUE) printf("\n\nNo client has been found.\n");
    
    fclose(pFile);
}

int CheckString(char CheckThat[])
{
    int CurrChar;
    
    for(CurrChar=0; CurrChar<strlen(CheckThat); CurrChar++)
    {
        if(isdigit(CheckThat[CurrChar])!=0)
        {
            printf("\nError Occured. Name should not have digits.\n");
            return TRUE;
        }
    }
    if(strcmp(CheckThat,"")==0)
        {
            printf("\nError Occured. Empty string.\n");
            return TRUE;
        }
        if(strlen(CheckThat)>1)
    for(CurrChar=0; CurrChar<strlen(CheckThat)-1; CurrChar++)
    {
        if(isspace(CheckThat[CurrChar])!=0 && isspace(CheckThat[CurrChar+1])!=0)
        {
            printf("\nError Occured. Two or more white-space characters next to each other.\n");
            return TRUE;
        }
    }
    if(strlen(CheckThat)<2)
        {
            printf("\nError Occured. Too short.\n");
            return TRUE;
        }
    return FALSE;
}