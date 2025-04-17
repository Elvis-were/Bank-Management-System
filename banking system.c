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
void deposit();
void displayAllAccounts();
void searchAccount();
void withdraw();
int main()
{
  
  return 0;
}
#include <stdio.h>
#include <string.h>

typedef struct {
    char owner[100];
    double balance;
} BankAccount;

void init_account(BankAccount *acc, const char *owner, double balance) {
    strcpy(acc->owner, owner);
    acc->balance = balance;
}

void deposit(BankAccount *acc, double amount, char *message, size_t size) {
    if (amount <= 0) {
        snprintf(message, size, "Deposit amount must be positive.");
        return;
    }
    acc->balance += amount;
    snprintf(message, size, "Deposited $%.2f. New balance: $%.2f", amount, acc->balance);
}

void withdraw(BankAccount *acc, double amount, char *message, size_t size) {
    if (amount <= 0) {
        snprintf(message, size, "Withdrawal amount must be positive.");
        return;
    }
    if (amount > acc->balance) {
        snprintf(message, size, "Insufficient funds.");
        return;
    }
    acc->balance -= amount;
    snprintf(message, size, "Withdrew $%.2f. New balance: $%.2f", amount, acc->balance);
}

void print_account(const BankAccount *acc) {
    printf("BankAccount(owner='%s', balance=$%.2f)\n", acc->owner, acc->balance);
}
