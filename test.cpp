#include <deepstate/DeepState.hpp>
#include "banking_system.h"

using namespace deepstate;

TEST(BankingSystemPropertyTest, AccountCreation)
{
    BankingSystem bankingSystem;
    int account_number = DeepState_IntInRange(1, MAX_ACCOUNTS);
    std::string owner_name = DeepState_CStrUpToLen(MAX_NAME_LENGTH);
    double initial_balance = DeepState_DoubleInRange(1.0, 1000.0);
    bankingSystem.createAccount(account_number, owner_name, initial_balance);

    Account *account = bankingSystem.findAccount(account_number);
    ASSERT(account != nullptr);
    ASSERT_EQ(account->account_number, account_number);
    ASSERT_EQ(account->owner, owner_name);
}

TEST(BankingSystemPropertyTest, Deposit)
{
    BankingSystem bankingSystem;
    int account_number = DeepState_IntInRange(1, MAX_ACCOUNTS);
    double initial_balance = DeepState_DoubleInRange(1.0, 1000.0);
    double deposit_amount = DeepState_DoubleInRange(1.0, 100.0);
    bankingSystem.createAccount(account_number, "TestOwner", initial_balance);
    bankingSystem.deposit(account_number, deposit_amount);

    Account *account = bankingSystem.findAccount(account_number);
    ASSERT(account != nullptr);
    ASSERT_EQ(account->balance, initial_balance + deposit_amount);
}

TEST(BankingSystemPropertyTest, Withdrawal)
{
    BankingSystem bankingSystem;
    int account_number = DeepState_IntInRange(1, MAX_ACCOUNTS);
    double initial_balance = DeepState_DoubleInRange(100.0, 1000.0);
    double withdraw_amount = DeepState_DoubleInRange(1.0, initial_balance);
    bankingSystem.createAccount(account_number, "TestOwner", initial_balance);
    bankingSystem.withdraw(account_number, withdraw_amount);

    Account *account = bankingSystem.findAccount(account_number);
    ASSERT(account != nullptr);
    ASSERT_EQ(account->balance, initial_balance - withdraw_amount);
}

TEST(BankingSystemPropertyTest, Transfer)
{
    BankingSystem bankingSystem;
    int source_account_number = DeepState_IntInRange(1, MAX_ACCOUNTS);
    int dest_account_number = DeepState_IntInRange(1, MAX_ACCOUNTS);
    double initial_balance = DeepState_DoubleInRange(100.0, 1000.0);
    double transfer_amount = DeepState_DoubleInRange(1.0, initial_balance);
    bankingSystem.createAccount(source_account_number, "SourceOwner", initial_balance);
    bankingSystem.createAccount(dest_account_number, "DestOwner", initial_balance);
    bankingSystem.transfer(source_account_number, dest_account_number, transfer_amount);

    Account *source_account = bankingSystem.findAccount(source_account_number);
    Account *dest_account = bankingSystem.findAccount(dest_account_number);
    ASSERT(source_account != nullptr);
    ASSERT(dest_account != nullptr);
    ASSERT_EQ(source_account->balance, initial_balance - transfer_amount);
    ASSERT_EQ(dest_account->balance, initial_balance + transfer_amount);
}

TEST(BankingSystemPropertyTest, InvalidWithdrawal)
{
    BankingSystem bankingSystem;
    int account_number = DeepState_IntInRange(1, MAX_ACCOUNTS);
    double initial_balance = DeepState_DoubleInRange(1.0, 100.0);
    double withdraw_amount = DeepState_DoubleInRange(initial_balance + 1.0, 1000.0);
    bankingSystem.createAccount(account_number, "TestOwner", initial_balance);
    bankingSystem.withdraw(account_number, withdraw_amount);

    Account *account = bankingSystem.findAccount(account_number);
    ASSERT(account == nullptr); // Account should not exist due to invalid withdrawal
}

TEST(BankingSystemPropertyTest, InvalidTransfer)
{
    BankingSystem bankingSystem;
    int source_account_number = DeepState_IntInRange(1, MAX_ACCOUNTS);
    int dest_account_number = DeepState_IntInRange(1, MAX_ACCOUNTS);
    double initial_balance = DeepState_DoubleInRange(1.0, 100.0);
    double transfer_amount = DeepState_DoubleInRange(initial_balance + 1.0, 1000.0);
    bankingSystem.createAccount(source_account_number, "SourceOwner", initial_balance);
    bankingSystem.createAccount(dest_account_number, "DestOwner", initial_balance);
    bankingSystem.transfer(source_account_number, dest_account_number, transfer_amount);

    Account *source_account = bankingSystem.findAccount(source_account_number);
    ASSERT(source_account == nullptr); // Source account should not exist due to invalid transfer
}

TEST(BankingSystemPropertyTest, AccountDeletion)
{
    BankingSystem bankingSystem;
    int account_number = DeepState_IntInRange(1, MAX_ACCOUNTS);
    double initial_balance = DeepState_DoubleInRange(1.0, 100.0);
    bankingSystem.createAccount(account_number, "TestOwner", initial_balance);
    bankingSystem.deleteAccount(account_number);

    Account *account = bankingSystem.findAccount(account_number);
    ASSERT(account == nullptr); // Account should not exist after deletion
}
