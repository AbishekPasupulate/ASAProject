#include <deepstate/DeepState.h>
#include "banking_system.c"

#define MAX_TEST_ACCOUNTS 10

// Function to generate random account number
int generate_random_account_number()
{
    return DeepState_IntInRange(1000, 9999);
}

// Function to generate random owner name
char *generate_random_owner_name()
{
    char *owner_name = DeepState_CStrUpToLen(MAX_NAME_LENGTH);
    DeepState_CStrLower(owner_name);
    return owner_name;
}

// Function to generate random initial balance
double generate_random_initial_balance()
{
    return DeepState_DoubleInRange(100.0, 1000.0);
}

// Property-based test for account creation
TEST(BankingSystemPropertyTest, AccountCreation)
{
    int account_number = generate_random_account_number();
    char *owner_name = generate_random_owner_name();
    double initial_balance = generate_random_initial_balance();

    create_account(account_number, owner_name, initial_balance);
    Account *account = find_account(account_number);
    ASSERT_NOT_NULL(account);
    ASSERT_EQ(account->account_number, account_number);
    ASSERT_C_STREQ(account->owner, owner_name);
    ASSERT_EQ(account->balance, initial_balance);
}

// Property-based test for deposit
TEST(BankingSystemPropertyTest, Deposit)
{
    int account_number = generate_random_account_number();
    double initial_balance = generate_random_initial_balance();
    double deposit_amount = DeepState_DoubleInRange(10.0, 100.0);

    create_account(account_number, "TestAccount", initial_balance);
    double expected_balance = initial_balance + deposit_amount;
    deposit(account_number, deposit_amount);

    Account *account = find_account(account_number);
    ASSERT_NOT_NULL(account);
    ASSERT_EQ(account->balance, expected_balance);
}

// Property-based test for withdrawal
TEST(BankingSystemPropertyTest, Withdrawal)
{
    int account_number = generate_random_account_number();
    double initial_balance = generate_random_initial_balance();
    double withdrawal_amount = DeepState_DoubleInRange(10.0, initial_balance - 10.0);

    create_account(account_number, "TestAccount", initial_balance);
    double expected_balance = initial_balance - withdrawal_amount;
    withdraw(account_number, withdrawal_amount);

    Account *account = find_account(account_number);
    ASSERT_NOT_NULL(account);
    ASSERT_EQ(account->balance, expected_balance);
}

// Property-based test for transfer
TEST(BankingSystemPropertyTest, Transfer)
{
    int source_account_number = generate_random_account_number();
    int dest_account_number = generate_random_account_number();
    double source_initial_balance = generate_random_initial_balance();
    double dest_initial_balance = generate_random_initial_balance();
    double transfer_amount = DeepState_DoubleInRange(10.0, 100.0);

    create_account(source_account_number, "SourceAccount", source_initial_balance);
    create_account(dest_account_number, "DestAccount", dest_initial_balance);

    transfer(source_account_number, dest_account_number, transfer_amount);

    Account *source_account = find_account(source_account_number);
    Account *dest_account = find_account(dest_account_number);

    ASSERT_NOT_NULL(source_account);
    ASSERT_NOT_NULL(dest_account);
    ASSERT_EQ(source_account->balance, source_initial_balance - transfer_amount);
    ASSERT_EQ(dest_account->balance, dest_initial_balance + transfer_amount);
}
