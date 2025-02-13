#include <iostream>
#include <vector>
#include <limits>
using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

class Account {
    private:
        int accountID;
        string accountOwner;
    protected:
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
        int getBalance() {
            return Balance;
        }
        virtual void AccountInfo() {
            cout << "Account ID: " << accountID << endl;
            cout << "Account Owner: " << accountOwner << endl;
            cout << "Balance: $" << Balance << endl;
        }
        virtual void deposit(int amount) {
            if(amount > 0) {
                Balance += amount;
                cout << "Deposito Exitoso! Nuevo Balance: $" << Balance << endl;
            } else {
                cout << "Cantidad invalida, por favor intente de nuevo" << endl;
            }
        }
        virtual void withdrawal(int amount) {
            if(amount > 0 && amount <= Balance) {
                Balance -= amount;
                cout << "Retiro Exitoso.\nNuevo Balance: $" << Balance << endl;
            } else {
                cout << "Cantidad invalida, por favor intente de nuevo" << endl;
            }
        }
};

class Debt : public Account {
    private:
        int accountDebt;
    public:
        Debt(int accountid, string accountower, int balance, int accountdebt)
        : Account(accountid, accountower, balance), accountDebt(accountdebt){}
        void setaccountDebt(int accountdebt) {
            accountDebt = accountdebt;
        }
        int getaccountDebt() {
            return accountDebt;
        }
        int getfinalBalance()  {
            return getBalance() - accountDebt;
        }

        void setBalance(int balance) {
            Balance = balance;
        }
        int getBalance(){
            return Balance;
        }
        void AccountInfo() override {
            Account::AccountInfo();
            if ( accountDebt > 0) {
                cout << "Account Debt: $" << accountDebt << endl;
                cout << "Final Balance: $" << (getBalance() - accountDebt) << endl;
            }
        }
        void deposit(int amount) override {
            if(amount > 0) {
                Balance += amount;
                cout << "Deposito exitoso! Nuevo Balance: $" << getBalance() << endl;
                cout << "Balance despues de liquidacion: $" << getfinalBalance() << endl;
            } else {
                cout << "Cantidad invalida, por favor intente de nuevo" << endl;
            }
        }
        void withdrawal (int amount) override {
            if(amount > 0 && amount <= getBalance()) {
                Balance -= amount;
                cout << "Retiro exitoso.\nNuevo Balance: $" << getBalance() << endl;
                cout << "Balance despues de liquidacion: $" << getfinalBalance() << endl;
            } else {
                cout << "Cantidad invalida, por favor, intente de nuevo" << endl;
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
    accounts.push_back(new Debt(277, "Kat", 35900, 9743));
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

    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Ver Informacion de la Cuenta\n";
        cout << "2. Realizar un deposito\n";
        cout << "3. Retirar Dinero\n";
        cout << "4. Volver al Menu\n";
        cout << "Ingresa la opcion deseada: ";
        cin >> choice;

        switch (choice) {
        
            case 1:
                matchingAccount->AccountInfo();
                cout << "Presione cualquier tecla para continuar...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Util para que el usuario pueda visualizar su accion y despues, elegir en que momento regresar al menu
                cin.get();
                break;
            case 2: {
                int depositAmount;
                cout<< "Enter Amount to deposit: $";
                cin >> depositAmount;
                matchingAccount->deposit(depositAmount);
                cout << "Presione cualquier tecla para continuar...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
                break;
            }
            case 3: {
                int withdrawalAmount;
                cout << "Enter Amount to Withdraw: $";
                cin >> withdrawalAmount;
                matchingAccount->withdrawal(withdrawalAmount);
                cout << "Presione cualquier tecla para continuar...\n";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
                break;
            }
            case 4: 
                cout << "Exiting program...\n"; 
                break;
            default:
                cout << "Invalid option, please try again.\n";
                cout << "Presione cualquier tecla para continuar.\n";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
        }
    } while (choice !=4);    
        
    for (auto acc : accounts) {
        delete acc;
    }

    return 0;
        
}
