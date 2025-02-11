#include <iostream>
#include <vector>
using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;

class Account {
    private:
        int accountID;
        string accountOwner;
        int Balance;
    public: 
        Account(int accountid, string accountowner, int balance) {
            accountID = accountid;
            accountOwner = accountowner;
            Balance = balance;
        }   
        void setaccoountID(int accountid) {
            accountID = accountid;
        }
        int getaccountID() {
            return accountID;
        }
        void setaccoountOwner(string accountowner) {
            accountOwner = accountowner;
        }
        string getaccountOwner() {
            return accountOwner;
        }
        void setBalance(int balance) {
            Balance = balance;
        }
        int getBalance() const {
            return Balance;
        }
        virtual void AccountInfo() const {
            cout << "Account ID: " << accountID << endl;
            cout << "Account Owner: " << accountOwner << endl;
            cout << "Balance: $" << Balance << endl;
        }
};

class Debt : public Account {
    private:
    int accountDebt;
    int finalBalance;
    public:
    Debt(int accountid, string accountower, int balance, int accountdebt)
    : Account(accountid, accountower, balance), accountDebt(accountdebt){}
    void setaccountDebt(int accountdebt) {
        accountDebt = accountdebt;
    }
    int getaccountDebt() {
        return accountDebt;
    }
    void setfinalBalance(int finalbalance) {
        finalBalance = finalbalance;
    }
    int getfinalBalance()  {
        return finalBalance;
    }
    void AccountInfo() const override {
        Account::AccountInfo();
        if ( accountDebt > 0) {
            cout << "Account Debt: $" << accountDebt << endl;
            cout << "Final Balance: $" << (getBalance() - accountDebt) << endl;
        }
    }
};

int main() {
    int AccountID; 
    string AccountOwner;
    
    vector<Account*> accounts;
    vector<Debt> debts;

    accounts.push_back(new Debt(102, "Jean", 17600, 3800));
    accounts.push_back(new Debt(427, "Luis", 1420, 760));

    bool validCredentials = false;
    Account* matchingAccount = nullptr;

    while (!validCredentials) {
        cout << "Enter Account ID: ";
        cin >> AccountID;
        cout << "Enter Account Owner: ";
        cin >> AccountOwner;

        for (const auto& acc : accounts) {
        if(acc->getaccountID() == AccountID && acc->getaccountOwner() == AccountOwner) {
            matchingAccount = acc;
            validCredentials = true;
            break;
            }
        }

        if (!validCredentials) {
            cout << "Invalid credentials. Please try again." << endl;
        }
    }

    if (matchingAccount != nullptr) {
        matchingAccount->AccountInfo();
    } else {
        cout << "Invalid Credentials..." << endl;
    }

    for (auto acc : accounts) {
        delete acc;
    }
    
    return 0;
}
