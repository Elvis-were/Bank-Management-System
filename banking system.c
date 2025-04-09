#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#define MAX_ACCOUNTS 100
struct accountInfo{
  int accId;
  char name[50];
  float initialDeposit;
};

struct accountInfo client[MAX_ACCOUNTS];
int client_count = 0;

void createAccount()
{
  if(client_count < MAX_ACCOUNTS)
{
    struct accountInfo newClient;
    printf("Enter account Id: \n");
    scanf("%d",&newClient.accId);

    printf("Enter name: \n");
    getchar();
    fgets(newClient.name,sizeof(newClient.name), stdin);
    newClient.name[strcspn(newClient.name, "\n")] = '\0';

    printf("Enter initial deposit: \n");
    scanf("%f",&newClient.initialDeposit);
    client[client_count] = newClient;
    client_count++;

    printf("Account created successfully \n");
}
else{
    printf("Maximum account limit reached! \n");
}

}
void depositCash();
void withdrawCash();
int main()
{
 int choice; 
  return 0;
}
