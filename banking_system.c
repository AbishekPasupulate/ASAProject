#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_NAME_LENGTH 50
#define MAX_TRANSACTIONS 100

// Structure to represent a transaction
typedef struct
{
    int account_number;
    char type[20]; // "Deposit", "Withdrawal", "Transfer"
    double amount;
} Transaction;

// Structure to represent an account
typedef struct
{
    int account_number;
    char owner[MAX_NAME_LENGTH];
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int num_transactions;
} Account;

// Array to store all accounts
Account accounts[MAX_ACCOUNTS];
int num_accounts = 0;

// Function prototypes
Account *find_account(int account_number);
void create_account(int account_number, const char *owner, double initial_balance);
void deposit(int account_number, double amount);
void withdraw(int account_number, double amount);
void transfer(int from_account_number, int to_account_number, double amount);
void calculate_interest(double rate);
void display_transactions(int account_number);
void delete_account(int account_number);
void display_account_details(int account_number);
void display_all_accounts();
void search_accounts_by_owner(const char *owner_name);

// Function to find an account by account number
Account *find_account(int account_number)
{
    for (int i = 0; i < num_accounts; ++i)
    {
        if (accounts[i].account_number == account_number)
        {
            return &accounts[i];
        }
    }
    return NULL;
}

// Function to create a new account
void create_account(int account_number, const char *owner, double initial_balance)
{
    if (num_accounts >= MAX_ACCOUNTS)
    {
        printf("Error: Maximum number of accounts reached.\n");
        return;
    }

    Account new_account;
    new_account.account_number = account_number;
    strncpy(new_account.owner, owner, MAX_NAME_LENGTH);
    new_account.balance = initial_balance;
    new_account.num_transactions = 0;

    accounts[num_accounts++] = new_account;
    printf("Account created successfully.\n");
}

// Function to deposit money into an account
void deposit(int account_number, double amount)
{
    Account *account = find_account(account_number);
    if (account == NULL)
    {
        printf("Error: Account not found.\n");
        return;
    }
    if (amount <= 0)
    {
        printf("Error: Invalid amount.\n");
        return;
    }
    account->balance += amount;

    // Update transaction history
    Transaction *transaction = &account->transactions[account->num_transactions++];
    transaction->account_number = account_number;
    strcpy(transaction->type, "Deposit");
    transaction->amount = amount;

    printf("Deposit successful. New balance: %.2f\n", account->balance);
}

// Function to withdraw money from an account
void withdraw(int account_number, double amount)
{
    Account *account = find_account(account_number);
    if (account == NULL)
    {
        printf("Error: Account not found.\n");
        return;
    }
    if (amount <= 0 || amount > account->balance)
    {
        printf("Error: Insufficient funds or invalid amount.\n");
        return;
    }
    account->balance -= amount;

    // Update transaction history
    Transaction *transaction = &account->transactions[account->num_transactions++];
    transaction->account_number = account_number;
    strcpy(transaction->type, "Withdrawal");
    transaction->amount = amount;

    printf("Withdrawal successful. New balance: %.2f\n", account->balance);
}

// Function to transfer money between two accounts
void transfer(int from_account_number, int to_account_number, double amount)
{
    Account *from_account = find_account(from_account_number);
    Account *to_account = find_account(to_account_number);
    if (from_account == NULL || to_account == NULL)
    {
        printf("Error: One or both accounts not found.\n");
        return;
    }
    if (amount <= 0 || amount > from_account->balance)
    {
        printf("Error: Insufficient funds or invalid amount.\n");
        return;
    }
    from_account->balance -= amount;
    to_account->balance += amount;

    // Update transaction history for both accounts
    Transaction *transaction1 = &from_account->transactions[from_account->num_transactions++];
    transaction1->account_number = from_account_number;
    strcpy(transaction1->type, "Transfer (to)");
    transaction1->amount = amount;

    Transaction *transaction2 = &to_account->transactions[to_account->num_transactions++];
    transaction2->account_number = to_account_number;
    strcpy(transaction2->type, "Transfer (from)");
    transaction2->amount = amount;

    printf("Transfer successful. New balance for %s: %.2f\n", from_account->owner, from_account->balance);
    printf("New balance for %s: %.2f\n", to_account->owner, to_account->balance);
}

// Function to calculate interest for all accounts
void calculate_interest(double rate)
{
    for (int i = 0; i < num_accounts; ++i)
    {
        accounts[i].balance *= (1 + rate);
    }
    printf("Interest calculated and applied to all accounts.\n");
}

// Function to display transaction history for an account
void display_transactions(int account_number)
{
    Account *account = find_account(account_number);
    if (account == NULL)
    {
        printf("Error: Account not found.\n");
        return;
    }
    printf("Transaction history for account %d (%s):\n", account->account_number, account->owner);
    for (int i = 0; i < account->num_transactions; ++i)
    {
        Transaction *transaction = &account->transactions[i];
        printf("Type: %s, Amount: %.2f\n", transaction->type, transaction->amount);
    }
}

// Function to delete an account
void delete_account(int account_number)
{
    for (int i = 0; i < num_accounts; ++i)
    {
        if (accounts[i].account_number == account_number)
        {
            // Shift remaining accounts to fill the gap
            for (int j = i; j < num_accounts - 1; ++j)
            {
                accounts[j] = accounts[j + 1];
            }
            num_accounts--;
            printf("Account %d deleted successfully.\n", account_number);
            return;
        }
    }
    printf("Error: Account not found.\n");
}

// Function to display details of a specific account
void display_account_details(int account_number)
{
    Account *account = find_account(account_number);
    if (account == NULL)
    {
        printf("Error: Account not found.\n");
        return;
    }
    printf("Account Number: %d\n", account->account_number);
    printf("Owner: %s\n", account->owner);
    printf("Balance: %.2f\n", account->balance);
    printf("Transaction History:\n");
    display_transactions(account_number);
}

// Function to display details of all accounts
void display_all_accounts()
{
    printf("List of all accounts:\n");
    for (int i = 0; i < num_accounts; ++i)
    {
        printf("Account Number: %d, Owner: %s, Balance: %.2f\n",
               accounts[i].account_number, accounts[i].owner, accounts[i].balance);
    }
}

// Function to search accounts by owner name
void search_accounts_by_owner(const char *owner_name)
{
    printf("Accounts owned by %s:\n", owner_name);
    for (int i = 0; i < num_accounts; ++i)
    {
        if (strcmp(accounts[i].owner, owner_name) == 0)
        {
            printf("Account Number: %d, Balance: %.2f\n",
                   accounts[i].account_number, accounts[i].balance);
        }
    }
}

// Main function with user interaction
int main()
{
    int choice;
    int account_number;
    char owner[MAX_NAME_LENGTH];
    double amount;
    double rate;
    char owner_name[MAX_NAME_LENGTH];

    do
    {
        printf("\n===== Banking System Menu =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Calculate Interest\n");
        printf("6. Display Transactions\n");
        printf("7. Display Account Details\n");
        printf("8. Display All Accounts\n");
        printf("9. Search Accounts by Owner\n");
        printf("10. Delete Account\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter account number: ");
            scanf("%d", &account_number);
            printf("Enter owner name: ");
            scanf("%s", owner);
            printf("Enter initial balance: ");
            scanf("%lf", &amount);
            create_account(account_number, owner, amount);
            break;
        case 2:
            printf("Enter account number: ");
            scanf("%d", &account_number);
            printf("Enter amount to deposit: ");
            scanf("%lf", &amount);
            deposit(account_number, amount);
            break;
        case 3:
            printf("Enter account number: ");
            scanf("%d", &account_number);
            printf("Enter amount to withdraw: ");
            scanf("%lf", &amount);
            withdraw(account_number, amount);
            break;
        case 4:
            printf("Enter source account number: ");
            scanf("%d", &account_number);
            printf("Enter destination account number: ");
            int dest_account_number;
            scanf("%d", &dest_account_number);
            printf("Enter amount to transfer: ");
            scanf("%lf", &amount);
            transfer(account_number, dest_account_number, amount);
            break;
        case 5:
            printf("Enter interest rate: ");
            scanf("%lf", &rate);
            calculate_interest(rate);
            break;
        case 6:
            printf("Enter account number: ");
            scanf("%d", &account_number);
            display_transactions(account_number);
            break;
        case 7:
            printf("Enter account number: ");
            scanf("%d", &account_number);
            display_account_details(account_number);
            break;
        case 8:
            display_all_accounts();
            break;
        case 9:
            printf("Enter owner name: ");
            scanf("%s", owner_name);
            search_accounts_by_owner(owner_name);
            break;
        case 10:
            printf("Enter account number to delete: ");
            scanf("%d", &account_number);
            delete_account(account_number);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
