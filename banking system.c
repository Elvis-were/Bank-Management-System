#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#define FILE_NAME "accounts.dat"
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
void deposit()
{
int accNum;
    float amount;

    printf("\n==============================\n");
    printf("           DEPOSIT            \n");
    printf("==============================\n");

    printf("Enter Account Number    : ");
    if (scanf("%d", &accNum) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter Amount to Deposit : ");
    if (scanf("%f", &amount) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    updateAccountBalance(accNum, amount, 1);  
}
void displayAllAccounts();
void searchAccount();
void deleteAccount()
{
   int accNum, found = 0;
    Account acc;

    printf("\n==============================\n");
    printf("        DELETE ACCOUNT        \n");
    printf("==============================\n");

    printf("Enter Account Number to delete: ");
    if (scanf("%d", &accNum) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        perror("Error creating temporary file");
        fclose(fp);
        return;
    }

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accountNumber != accNum) {
            fwrite(&acc, sizeof(Account), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);

    if (remove(FILE_NAME) != 0 || rename("temp.dat", FILE_NAME) != 0) {
        perror("Error updating account file");
        return;
    }

    if (found)
        printf("Account deleted successfully.\n");
    else
        printf("Account not found.\n");
 
}
void withdraw()
{
int accNum;
    float amount;

    printf("\n==============================\n");
    printf("          WITHDRAW            \n");
    printf("==============================\n");

    printf("Enter Account Number     : ");
    if (scanf("%d", &accNum) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter Amount to Withdraw : ");
    if (scanf("%f", &amount) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    updateAccountBalance(accNum, amount, 0);    
}

int main()
{
  
  return 0;
}
