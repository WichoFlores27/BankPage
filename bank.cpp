#include <iostream>
#include <vector>
#include <limits>
#include <conio.h>
using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <ostream>

string hashPassword(const string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password.c_str(), password.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

class Account {
    private:
        int accountID;
        string accountOwner;
        string passwordHash;
        bool isActive;
    protected:
        int Balance;
    public: 
        Account(int accountid, string accountowner, int balance, string password)
            : accountID(accountid), accountOwner(accountowner), Balance(balance),
              passwordHash(hashPassword(password)), isActive(balance > 0) {}

        string getPasswordHash() {
            return passwordHash;
        }

        bool verifyPassword(const string& password) {
            return hashPassword(password) == passwordHash;
        }
        void setaccoountID(int accountid) {
            accountID = accountid;
        }
        int getaccountID() {
            return accountID;
        }
        void setaccountOwner(string accountowner) {
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
            cout << "ID: " << accountID << endl;
            cout << "Nombre de cuenta: " << accountOwner << endl;
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
        Debt(int accountid, string accountowner, int balance, int accountdebt, string password)
        : Account(accountid, accountowner, balance, password), accountDebt(accountdebt){}
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
                cout << "Deuda de cuenta: $" << accountDebt << endl;
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

string getHiddenPassword() {
    string password;
    char ch;
    cout << "Ingrese Contrasena: ";
    while ((ch = _getch()) !='\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

int main() {
    int AccountID; 
    string AccountOwner;
    string enteredPassword;
    
    vector<Account*> accounts;
    vector<Debt> debts;

    accounts.push_back(new Debt(102, "Jean", 17600, 3800, "Encit"));
    accounts.push_back(new Debt(427, "Luis", 1420, 760, "FullofDreams"));
    accounts.push_back(new Debt(277, "Kat", 35900, 9743, "Gato"));
    bool validCredentials = false;
    Account* matchingAccount = nullptr;

    while (!validCredentials) {
        cout << "ID: ";
        cin >> AccountID;
        cout << "Nombre de cuenta: ";
        cin >> AccountOwner;
        enteredPassword = getHiddenPassword();

        for (const auto& acc : accounts) {
        if(acc->getaccountID() == AccountID && acc->getaccountOwner() == AccountOwner &&
            acc->verifyPassword(enteredPassword)) {
            matchingAccount = acc;
            validCredentials = true;
            break;
            }
        }

        if (!validCredentials) {
            cout << "Credenciales invalidas, por favor intente de nuevo." << endl;
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
                cout<< "Ingrese monto a depositar: $";
                cin >> depositAmount;
                matchingAccount->deposit(depositAmount);
                cout << "Presione cualquier tecla para continuar...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
                break;
            }
            case 3: {
                int withdrawalAmount;
                cout << "Ingrese monto a retirar: $";
                cin >> withdrawalAmount;
                matchingAccount->withdrawal(withdrawalAmount);
                cout << "Presione cualquier tecla para continuar...\n";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
                break;
            }
            case 4: 
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion Invalida, por favor intente de nuevo.\n";
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
