#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
typedef struct {
    int accountNumber;
    char name[100];
    float balance;
} Account;

void createAccount()
{
  Account acc;
    FILE *fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\n==============================\n");
    printf("      CREATE NEW ACCOUNT      \n");
    printf("==============================\n");

    printf("Enter Account Number : ");
    if (scanf("%d", &acc.accountNumber) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
        while (getchar() != '\n'); // clear buffer
        fclose(fp);
        return;
    }

    printf("Enter Name           : ");
    getchar(); // consume leftover newline
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = 0;

    printf("Enter Initial Balance: ");
    if (scanf("%f", &acc.balance) != 1) {
        printf("Invalid input. Please enter a valid amount.\n");
        while (getchar() != '\n');
        fclose(fp);
        return;
    }

    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp);
    printf("Account created successfully.\n");
}
void deposit();
void displayAllAccounts();
void withdraw();
int main()
{
  
  return 0;
}
