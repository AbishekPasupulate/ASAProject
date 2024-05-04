#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H

#include <iostream>
#include <string>

constexpr int MAX_ACCOUNTS = 100;
constexpr int MAX_NAME_LENGTH = 50;
constexpr int MAX_TRANSACTIONS = 100;

// Structure to represent a transaction
struct Transaction
{
    int account_number;
    std::string type; // "Deposit", "Withdrawal", "Transfer"
    double amount;
};

// Structure to represent an account
struct Account
{
    int account_number;
    std::string owner;
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int num_transactions;
};

class BankingSystem
{
public:
    BankingSystem();

    void createAccount(int account_number, const std::string &owner, double initial_balance);
    void deposit(int account_number, double amount);
    void withdraw(int account_number, double amount);
    void transfer(int from_account_number, int to_account_number, double amount);
    void calculateInterest(double rate);
    void displayTransactions(int account_number);
    void deleteAccount(int account_number);
    void displayAccountDetails(int account_number);
    void displayAllAccounts();
    void searchAccountsByOwner(const std::string &owner_name);

    Account accounts[MAX_ACCOUNTS];
    int num_accounts;

    Account *findAccount(int account_number);
};

#endif /* BANKING_SYSTEM_H */
