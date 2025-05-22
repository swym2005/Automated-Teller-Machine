#include <iostream>
#include <fstream>
#define MAX_USERS 200
using namespace std;
int account_index;
int prof_count;
void ini_disp()     // Function for initial display part
{
    cout << "**********************************************" << endl;
    cout << "\t     WELCOME TO SRV BANK" << endl;

    cout << "**********************************************" << endl;
    cout << "\t\tWELCOME USER" << endl;
    cout << "**********************************************" << endl;
}
void menu_display()  // Function for the choice of the user.
{
    cout << "**********************************************" << endl;
    cout << "PLEASE ENTER A CHOICE:-" << endl;
    cout << "**********************************************" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Withdraw money" << endl;
    cout << "3. Deposit money." << endl;
    cout << "4. Exit. " << endl;
    cout << "**********************************************" << endl;
}

class ATM
{
protected:

    int acc_num[MAX_USERS];
    int acc_pin[MAX_USERS];
    double balance[MAX_USERS];
public:
void profile_counter()      // Counts the number of profiles in the file.
{
    string str;
    prof_count = 0;
    ifstream in;
    in.open("accountnumdata.txt");
    prof_count = 0;
    for(int i = 0; i =!in.eof(); i++)
    {
        in >> str;
        prof_count++;
    }
   // cout<<"The number of the accounts are "<<prof_count<<endl;
    in.close();
}
    void accountnumber_extract()       // Extracts the data of account number from the file.
    {
        ifstream in;
        in.open("accountnumdata.txt");
        for (int i = 0; i < prof_count; i++)
        {
            in >> acc_num[i];
        }
        in.close();
    }
    void accountpin_extract()       // Extracts the data of account pin from the file.
    {
        ifstream in;
        in.open("pindata.txt");
        for (int i = 0; i < prof_count; i++)
        {
            in >> acc_pin[i];
        }
        in.close();
    }
    void accountbalance_extract()   // Extracts the data of account balance from the file.
    {
        ifstream in;
        in.open("balancedata.txt");
        for (int i = 0; i < prof_count; i++)
        {
            in >> balance[i];
        }
        in.close();
    }
    void check_balance()        //Function for checking the balance(current),
    {
        cout << "Your current balance is " << balance[account_index] << endl;
    }
    void deposit_money(float amount)    //Function for depositing the money into the account.
    {
        balance[account_index] += amount;
        cout << amount << " deposited succesfully" << endl;
    }
    void withdraw_money(float amount)       //Function for withdrawing the money from the account.
    {
        if (amount <= balance[account_index])
        {
            balance[account_index] -= amount;
            cout << "Withdrawal succesful" << endl;
            cout << "Please collect your cash" << endl;
        }
        else
        {
            cout << "Insufficient balance" << endl;
        }
    }
};
class Account : public ATM
{
public:
    bool login(int account_number, int account_pin)  //Function which allows user to login
    {
        for (int i = 0; i < MAX_USERS; ++i)
        {
            if (account_number == acc_num[i] && account_pin == acc_pin[i])
            {
                account_index = i;
                return true; // Successful login
            }
        }
        return false; // Login failed
    }
    void accountbalance_write()     //Function which writes all the overwrited balance back into the file.
    {
        ofstream out;
        out.open("balancedata.txt");
        for (int i = 0; i < prof_count; i++)
        {
            out << balance[i] << endl;
        }
        out.close();
    }

  
    void create_user()  //Allows user to create a new profile if he/she is not existing.
    {
        ofstream out;
        int anum;
        int apin;
        int abal;
        out.open("accountnumdata.txt", ios::app);
        cout << "Enter your account number" << endl;
        cin >> anum;
        cout << "Enter your pin" << endl;
        cin >> apin;
        cout << "Enter the balance" << endl;
        cin >> abal;
        out << endl
            << anum;
        out.close();
        out.open("pindata.txt", ios::app);
        out << endl
            << apin;
        out.close();
        out.open("balancedata.txt", ios::app);
        out << endl
            << abal;
        out.close();
        system("cls");
        cout << "New user created succesfully" << endl;
    }
};
int main()
{
    int choice;

    Account a1;
    float amount;
    char y;
    int account_number, account_pin;
    ini_disp();
    cout << "Are you a new user?" << endl;      //Asks user if he/she is existing user or not.
    cin >> y;
x:
   a1.profile_counter();
    a1.accountnumber_extract();
    a1.accountpin_extract();
    a1.accountbalance_extract();
    if (y == 'n' || y == 'N')
    {
        cout << "Login:-" << endl;
        cout << "Enter your account number and pin" << endl;
        cin >> account_number >> account_pin;
        if (a1.login(account_number, account_pin))
        {
            do
            {
                amount = 0;
                menu_display();
                cin >> choice;
                switch (choice)         //Using switch case for performing user oriented tasks.
                {
                case 1:
                    system("cls");
                    a1.check_balance();
                    break;
                case 2:
                    cout << "Enter the amount:- " << endl;
                    cin >> amount;
                    system("cls");
                    a1.withdraw_money(amount);
                    a1.accountbalance_write();
                    break;
                case 3:
                    cout << "Enter the amount:- " << endl;
                    cin >> amount;
                    system("cls");
                    a1.deposit_money(amount);
                    a1.accountbalance_write();
                    break;
                case 4:
                    system("cls");
                    cout << "Thank you for choosing SRV ATM services" << endl;
                    break;
                default:
                    cout << "Enter a valid choice" << endl;
                    cout << "**********************************************" << endl;
                    break;
                }
            } while (choice != 4);
        }
        else
        {
            cout << "Login information incorrect" << endl;
            cout << "Try again" << endl;
            goto x;
        }
    }
    else
    {
        a1.create_user();
        y = 'n';
        goto x;
    }

    return 0;
}