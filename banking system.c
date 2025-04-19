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
void withdraw() {
    int accNo;
    float amount;
    int found = 0;

    printf("\n==============================\n");
    printf("          WITHDRAW            \n");
    printf("==============================\n");

    printf("Enter Account Number: ");
    if (scanf("%d", &accNo) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    FILE *fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    Account acc;
    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accountNumber == accNo) {
            found = 1;
            printf("Current Balance: %.2f\n", acc.balance);
            printf("Enter amount to withdraw: ");
            if (scanf("%f", &amount) != 1 || amount <= 0) {
                printf("Invalid amount.\n");
                while (getchar() != '\n');
                break;
            }
if (!found) {
        printf("Account not found.\n");
    }

    fclose(fp);
}

// Placeholder declarations
void deposit() {
    // You can implement this similar to withdraw
}
void displayAllAccounts() {
    // You can implement this to show all account details
}
void searchAccount() {
    // You can implement this to search for a specific account
}

int main() {
    int choice;
    while (1) {
        printf("\n==============================\n");
        printf("       BANK MANAGEMENT        \n");
        printf("==============================\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Display All Accounts\n");
        printf("5. Search Account\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                displayAllAccounts();
                break;
            case 5:
                searchAccount();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
