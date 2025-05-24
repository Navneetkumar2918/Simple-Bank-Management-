#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Account {
    int accNo;
    char name[50];
    char type;
    int balance;

public:
    void createAccount();
    void showAccount() const;
    void modify();
    void deposit(int);
    void withdraw(int);
    int getAccNo() const;
    int getBalance() const;
    char getType() const;
    void report() const;
};

void Account::createAccount() {
    cout << "Enter Account Number: ";
    cin >> accNo;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter Account Type (C/S): ";
    cin >> type;
    type = toupper(type);
    cout << "Enter Initial Amount: ";
    cin >> balance;
}

void Account::showAccount() const {
    cout << "\nAccount No: " << accNo;
    cout << "\nName: " << name;
    cout << "\nType: " << type;
    cout << "\nBalance: " << balance;
}

void Account::modify() {
    cout << "Modify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Modify Type (C/S): ";
    cin >> type;
    cout << "Modify Balance: ";
    cin >> balance;
}

void Account::deposit(int amount) {
    balance += amount;
}

void Account::withdraw(int amount) {
    balance -= amount;
}

int Account::getAccNo() const { return accNo; }
int Account::getBalance() const { return balance; }
char Account::getType() const { return type; }

void Account::report() const {
    cout << accNo << setw(10) << name << setw(6) << type << setw(10) << balance << endl;
}

void writeAccount();
void displayAccount(int);
void modifyAccount(int);
void deleteAccount(int);
void displayAll();
void depositWithdraw(int, int);

int main() {
    int choice;
    int accNo;
    do {
        cout << "\n\n1. New Account\n2. Deposit Amount\n3. Withdraw Amount\n";
        cout << "4. Balance Enquiry\n5. All Account Holder List\n6. Close Account\n";
        cout << "7. Modify Account\n8. Exit\nChoose an option: ";
        cin >> choice;
        switch (choice) {
            case 1: writeAccount(); break;
            case 2: cout << "Enter Account No: "; cin >> accNo; depositWithdraw(accNo, 1); break;
            case 3: cout << "Enter Account No: "; cin >> accNo; depositWithdraw(accNo, 2); break;
            case 4: cout << "Enter Account No: "; cin >> accNo; displayAccount(accNo); break;
            case 5: displayAll(); break;
            case 6: cout << "Enter Account No: "; cin >> accNo; deleteAccount(accNo); break;
            case 7: cout << "Enter Account No: "; cin >> accNo; modifyAccount(accNo); break;
            case 8: cout << "Thanks for using our system!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 8);
    return 0;
}

void writeAccount() {
    Account acc;
    ofstream outFile("bank.dat", ios::binary | ios::app);
    acc.createAccount();
    outFile.write(reinterpret_cast<char *> (&acc), sizeof(Account));
    outFile.close();
}

void displayAccount(int accNo) {
    Account acc;
    ifstream inFile("bank.dat", ios::binary);
    bool found = false;
    while (inFile.read(reinterpret_cast<char *> (&acc), sizeof(Account))) {
        if (acc.getAccNo() == accNo) {
            acc.showAccount();
            found = true;
        }
    }
    inFile.close();
    if (!found) cout << "Account not found!\n";
}

void modifyAccount(int accNo) {
    Account acc;
    fstream File("bank.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    while (!File.eof() && !found) {
        int pos = File.tellg();
        File.read(reinterpret_cast<char *> (&acc), sizeof(Account));
        if (acc.getAccNo() == accNo) {
            acc.showAccount();
            cout << "\nEnter new details:\n";
            acc.modify();
            File.seekp(pos);
            File.write(reinterpret_cast<char *> (&acc), sizeof(Account));
            found = true;
        }
    }
    File.close();
    if (!found) cout << "Account not found!\n";
}

void deleteAccount(int accNo) {
    Account acc;
    ifstream inFile("bank.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char *> (&acc), sizeof(Account))) {
        if (acc.getAccNo() != accNo)
            outFile.write(reinterpret_cast<char *> (&acc), sizeof(Account));
    }
    inFile.close();
    outFile.close();
    remove("bank.dat");
    rename("temp.dat", "bank.dat");
    cout << "Account deleted.\n";
}

void displayAll() {
    Account acc;
    ifstream inFile("bank.dat", ios::binary);
    cout << "\n\nACCOUNT HOLDER LIST:\n";
    while (inFile.read(reinterpret_cast<char *> (&acc), sizeof(Account))) {
        acc.report();
    }
    inFile.close();
}

void depositWithdraw(int accNo, int option) {
    Account acc;
    fstream File("bank.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    while (!File.eof() && !found) {
        int pos = File.tellg();
        File.read(reinterpret_cast<char *> (&acc), sizeof(Account));
        if (acc.getAccNo() == accNo) {
            acc.showAccount();
            int amt;
            cout << (option == 1 ? "\nEnter amount to deposit: " : "\nEnter amount to withdraw: ");
            cin >> amt;
            if (option == 1) acc.deposit(amt);
            else if (amt <= acc.getBalance()) acc.withdraw(amt);
            else cout << "Insufficient balance!\n";
            File.seekp(pos);
            File.write(reinterpret_cast<char *> (&acc), sizeof(Account));
            found = true;
        }
    }
    File.close();
    if (!found) cout << "Account not found!\n";
}
