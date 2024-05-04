#include "banking_system.h"

using namespace std;

BankingSystem::BankingSystem() : num_accounts(0) {}

Account *BankingSystem::findAccount(int account_number)
{
    for (int i = 0; i < num_accounts; ++i)
    {
        if (accounts[i].account_number == account_number)
        {
            return &accounts[i];
        }
    }
    return nullptr;
}

void BankingSystem::createAccount(int account_number, const string &owner, double initial_balance)
{
    if (num_accounts >= MAX_ACCOUNTS)
    {
        cout << "Error: Maximum number of accounts reached." << endl;
        return;
    }

    Account new_account;
    new_account.account_number = account_number;
    new_account.owner = owner;
    new_account.balance = initial_balance;
    new_account.num_transactions = 0;

    accounts[num_accounts++] = new_account;
    cout << "Account created successfully." << endl;
}

void BankingSystem::deposit(int account_number, double amount)
{
    Account *account = findAccount(account_number);
    if (account == nullptr)
    {
        cout << "Error: Account not found." << endl;
        return;
    }
    if (amount <= 0)
    {
        cout << "Error: Invalid amount." << endl;
        return;
    }
    account->balance += amount;

    // Update transaction history
    Transaction *transaction = &account->transactions[account->num_transactions++];
    transaction->account_number = account_number;
    transaction->type = "Deposit";
    transaction->amount = amount;

    cout << "Deposit successful. New balance: " << account->balance << endl;
}

void BankingSystem::withdraw(int account_number, double amount)
{
    Account *account = findAccount(account_number);
    if (account == nullptr)
    {
        cout << "Error: Account not found." << endl;
        return;
    }
    if (amount <= 0 || amount > account->balance)
    {
        cout << "Error: Insufficient funds or invalid amount." << endl;
        return;
    }
    account->balance -= amount;

    // Update transaction history
    Transaction *transaction = &account->transactions[account->num_transactions++];
    transaction->account_number = account_number;
    transaction->type = "Withdrawal";
    transaction->amount = amount;

    cout << "Withdrawal successful. New balance: " << account->balance << endl;
}

void BankingSystem::transfer(int from_account_number, int to_account_number, double amount)
{
    Account *from_account = findAccount(from_account_number);
    Account *to_account = findAccount(to_account_number);
    if (from_account == nullptr || to_account == nullptr)
    {
        cout << "Error: One or both accounts not found." << endl;
        return;
    }
    if (amount <= 0 || amount > from_account->balance)
    {
        cout << "Error: Insufficient funds or invalid amount." << endl;
        return;
    }
    from_account->balance -= amount;
    to_account->balance += amount;

    // Update transaction history for both accounts
    Transaction *transaction1 = &from_account->transactions[from_account->num_transactions++];
    transaction1->account_number = from_account_number;
    transaction1->type = "Transfer (to)";
    transaction1->amount = amount;

    Transaction *transaction2 = &to_account->transactions[to_account->num_transactions++];
    transaction2->account_number = to_account_number;
    transaction2->type = "Transfer (from)";
    transaction2->amount = amount;

    cout << "Transfer successful. New balance for " << from_account->owner << ": " << from_account->balance << endl;
    cout << "New balance for " << to_account->owner << ": " << to_account->balance << endl;
}

void BankingSystem::calculateInterest(double rate)
{
    for (int i = 0; i < num_accounts; ++i)
    {
        accounts[i].balance *= (1 + rate);
    }
    cout << "Interest calculated and applied to all accounts." << endl;
}

void BankingSystem::displayTransactions(int account_number)
{
    Account *account = findAccount(account_number);
    if (account == nullptr)
    {
        cout << "Error: Account not found." << endl;
        return;
    }
    cout << "Transaction history for account " << account->account_number << " (" << account->owner << "):" << endl;
    for (int i = 0; i < account->num_transactions; ++i)
    {
        Transaction *transaction = &account->transactions[i];
        cout << "Type: " << transaction->type << ", Amount: " << transaction->amount << endl;
    }
}

void BankingSystem::deleteAccount(int account_number)
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
            cout << "Account " << account_number << " deleted successfully." << endl;
            return;
        }
    }
    cout << "Error: Account not found." << endl;
}

void BankingSystem::displayAccountDetails(int account_number)
{
    Account *account = findAccount(account_number);
    if (account == nullptr)
    {
        cout << "Error: Account not found." << endl;
        return;
    }
    cout << "Account Number: " << account->account_number << endl;
    cout << "Owner: " << account->owner << endl;
    cout << "Balance: " << account->balance << endl;
    cout << "Transaction History:" << endl;
    displayTransactions(account_number);
}

void BankingSystem::displayAllAccounts()
{
    cout << "List of all accounts:" << endl;
    for (int i = 0; i < num_accounts; ++i)
    {
        cout << "Account Number: " << accounts[i].account_number << ", Owner: " << accounts[i].owner
             << ", Balance: " << accounts[i].balance << endl;
    }
}

void BankingSystem::searchAccountsByOwner(const string &owner_name)
{
    cout << "Accounts owned by " << owner_name << ":" << endl;
    for (int i = 0; i < num_accounts; ++i)
    {
        if (accounts[i].owner == owner_name)
        {
            cout << "Account Number: " << accounts[i].account_number << ", Balance: " << accounts[i].balance << endl;
        }
    }
}
/**/
int main()
{
    BankingSystem bank;

    // Creating accounts
    bank.createAccount(1001, "Alice", 5000);
    bank.createAccount(1002, "Bob", 3000);

    // Performing transactions
    bank.deposit(1001, 1000);
    bank.withdraw(1002, 500);
    bank.transfer(1001, 1002, 200);

    // Displaying account details
    bank.displayAccountDetails(1001);
    bank.displayAccountDetails(1002);

    // Displaying all accounts
    bank.displayAllAccounts();

    // Searching accounts by owner name
    bank.searchAccountsByOwner("Alice");

    // Deleting an account
    bank.deleteAccount(1002);

    return 0;
}