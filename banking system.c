//prepocessor directives
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
//function to create account
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
//function to deposit
void depositAmount()
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
//functiom to list all accounts in the system
void displayAllAccounts()
{
 FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    Account acc;
    int count = 0;

    printf("\n==============================\n");
    printf("      ALL BANK ACCOUNTS       \n");
    printf("==============================\n");

    while (fread(&acc, sizeof(Account), 1, fp)) {
        displayAccount(acc);
        count++;
    }

    fclose(fp);

    if (count == 0) {
        printf("No accounts found.\n");
    } 
}
//function to search for an account 
void searchAccount()
{
 int accNum;
    Account acc;
    int found = 0;

    printf("\n==============================\n");
    printf("        SEARCH ACCOUNT        \n");
    printf("==============================\n");

    printf("Enter Account Number to search: ");
    if (scanf("%d", &accNum) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
        while (getchar() != '\n');
        return;
    }

    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accountNumber == accNum) {
            displayAccount(acc);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Account not found.\n");
    }   
}
//function to update the customers information
void updateAccountBalance(int accNum, float amount, int isDeposit)
{
     Account acc;
    int found = 0;
    FILE *fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accountNumber == accNum) {
            found = 1;
            if (!isDeposit && acc.balance < amount) {
                printf("Insufficient balance.\n");
                fclose(fp);
                return;
            }

            acc.balance += isDeposit ? amount : -amount;
            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, fp);
            printf("Transaction successful. New balance: %.2f\n", acc.balance);
            break;
        }
    }

    fclose(fp);
    if (!found)
        printf("Account not found.\n");
}
//function to delete an account
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
//function to withdraw
void withdrawAmount()
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
//function to display the dashboard
void dashboard()
{
     int choice;
    do {
        printf("\n==============================\n");
        printf("     BANK MANAGEMENT SYSTEM   \n");
        printf("==============================\n");
        printf("1. Create Account\n");
        printf("2. Search Account\n");
        printf("3. Delete Account\n");
        printf("4. Deposit\n");
        printf("5. Withdraw\n");
        printf("6. Display All Accounts\n");
        printf("7. Exit\n");
        printf("------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear the input buffer
            continue;
        }

        switch (choice) {
            case 1: createAccount(); 
                break;
            case 2: searchAccount(); 
                break;
            case 3: deleteAccount(); 
                break;
            case 4: deposit(); break;
            case 5: withdraw(); 
                break;
            case 6: displayAllAccounts(); 
                break;
            case 7: printf("Exiting the system...\n"); 
                break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 7);
}
int main()
{
 dashboard(); 
  return 0;
}
