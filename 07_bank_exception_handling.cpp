#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class BankException : public runtime_error {
public:
    explicit BankException(const string& message) : runtime_error(message) {}
};

class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException()
        : BankException("Insufficient balance for withdrawal.") {}
};

class InvalidAmountException : public BankException {
public:
    InvalidAmountException()
        : BankException("Amount must be greater than zero.") {}
};

class BankAccount {
private:
    string name;
    double balance;
public:
    BankAccount(string n, double b) : name(n), balance(b) {}

    void deposit(double amount) {
        if (amount <= 0) throw InvalidAmountException();
        balance += amount;
        cout << "Deposit successful.\n";
    }

    void withdraw(double amount) {
        if (amount <= 0) throw InvalidAmountException();
        if (amount > balance) throw InsufficientFundsException();
        balance -= amount;
        cout << "Withdrawal successful.\n";
    }

    void display() const {
        cout << "Account holder: " << name << '\n';
        cout << "Current balance: " << balance << '\n';
    }
};

int main() {
    string name;
    double initialBalance;
    cout << "Enter account holder name: ";
    getline(cin, name);
    cout << "Enter initial balance: ";
    cin >> initialBalance;

    if (initialBalance < 0) {
        cout << "Initial balance cannot be negative.\n";
        return 0;
    }

    BankAccount account(name, initialBalance);
    int choice;
    double amount;

    do {
        cout << "\n1. Deposit\n2. Withdraw\n3. Display balance\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        try {
            if (choice == 1) {
                cout << "Enter deposit amount: ";
                cin >> amount;
                account.deposit(amount);
            } else if (choice == 2) {
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                account.withdraw(amount);
            } else if (choice == 3) {
                account.display();
            } else if (choice != 4) {
                cout << "Invalid choice.\n";
            }
        } catch (const BankException& e) {
            cout << "Transaction failed: " << e.what() << '\n';
        }
    } while (choice != 4);

    cout << "\nFinal account details:\n";
    account.display();
    return 0;
}
