// 211119 211116 211108 //
//Inter Thread Communication
#include <iostream>
#include<windows.h>
#include <thread>
#include <mutex>
#include <condition_variable> //condition_variable works only with unique_lock<mutex>
#include "headerFiles/allProjectFiles.h"

CRITICAL_SECTION cs;
// Abstract base class for a bank account //
class cBankAccount
{
    protected: // data members //
        int balance;
        mutex mtx; //mutex object mtx to protect the balance fromconcurrent access by multiple threads//
        condition_variable cv; //condition_variable object cv to signal and wait on changes to the balance//
        cAccountNotification notify;
        cDraft* draft;

    public:
        cBankAccount(){}
        cBankAccount(int initial_balance) : balance(initial_balance)
        {
            draft = new cDraft(500); // initialize overdraft limit
        }

        //Virtual Functions
        virtual void deposit(int amount) = 0; 
        virtual bool withdraw(int amount) = 0; 
        virtual int get_balance() = 0; 
        virtual void vTakeInput() =0;       
};

// Derived Class or saving Account //
class cSavingAccount : public cBankAccount
{
    public:
        cSavingAccount(int initial_balance) : cBankAccount(initial_balance) 
        {

        }
    //this fn locks the mutex, adds the deposited amount to the balance and signals all waiting threads //
        void deposit(int amount) override
        {
            unique_lock<mutex> lock(mtx);//This guarantees an unlocked status on destruction (even if not called explicitly)//
            balance += amount;
            notify.send_notification("Savings", "Deposit", amount, balance);
            cv.notify_all(); //signal all waiting thread and  atomically releases the mutex
            //Unblocks all threads currently waiting for this condition//
        }
    //it locks the mutex, waits on the condition variable if thebalance is not sufficient
        bool withdraw(int amount) override
        {
            unique_lock<mutex> lock(mtx);
            while (balance < amount)
            {
                cv.wait(lock);// block current thread  the function automatically calls lck.unlock(), allowing other locked threads to .continue. //
                InsufficientFundsException obj("Your Balance is Low");
            }
            if (!draft->overdraft_check(balance, amount))
            {
                InsufficientFundsException obj("Your Balance is Low");
                return false;
            }
            balance -= amount;
            int fee = draft->overdraft_fee();
            balance -= fee; // deduct overdraft fee
            notify.send_notification("Savings", "Withdrawal", amount, balance);
            return true;
        }
    //it locks the mutex and returns the balance
        int get_balance() override
        {
            unique_lock<mutex> lock(mtx);
            return balance;
        }
        void vTakeInput() override{}
};

// Concrete class for a checking account
class cCurrentAccount : public cBankAccount
{

    public:
        cCurrentAccount(int initial_balance) : cBankAccount(initial_balance) {}

        void deposit(int amount) override
        {
            unique_lock<mutex> lock(mtx);
            balance += amount;
            notify.send_notification("Current", "Deposit", amount, balance);
            cv.notify_all();//signal all waiting thread//
        }

        bool withdraw(int amount) override
        {
            unique_lock<mutex> lock(mtx);

            if (balance - amount < -500)
            { // Checking account can have negative balance up to 500
                NegativeBalanceException obj("Your Account has Neative Balance Please Update your balance");
                return false;

            }

            while (balance < amount)
            {
                cv.wait(lock);
                InsufficientFundsException obj("Insufficient Balance");
            }
            if (!draft->overdraft_check(balance, amount))
            {
                NegativeBalanceException obj("Your Account has Negative Balance Please Update your balance");
                return false;
            }

            balance -= amount;
            int fee = draft->overdraft_fee();
            balance -= fee; // deduct overdraft fee
            notify.send_notification("Current", "Withdrawal", amount, balance);
            return true;
        }

        int get_balance() override
        {
            unique_lock<mutex> lock(mtx);
            return balance;
        }
        void vTakeInput() override{}

};

class cNRIAccount : public cBankAccount 
{
    private:
        string sCountry;
        float fInterestRate;
    public:
        cNRIAccount(int initial_balance) : cBankAccount(initial_balance) {}

        void vTakeInput() override
        {
            cout << "Enter Country: ";
            cin >> sCountry;

            cout << "Enter Interest Rate for NRI Account (in percentage): ";
            cin >> fInterestRate;

            if (fInterestRate > 8) 
            {
                cout << "Interest rate is more than 8%, defaulting to 8%." << endl;
                fInterestRate = 8;
            }
        }

        void deposit(int amount) override 
        {
            unique_lock<mutex> lock(mtx);
            balance += amount;
            notify.send_notification("NRI", "Deposit", amount, balance);
            cv.notify_all();
        }

        bool withdraw(int amount) override 
        {
            unique_lock<mutex> lock(mtx);

            if (balance - amount < 0) 
            {
                InsufficientFundsException obj("Insufficient Balance");
                return false;
            }
            balance -= amount;
            notify.send_notification("NRI", "Withdrawal", amount, balance);
            return true;
        }

        int get_balance() override 
        {
            unique_lock<mutex> lock(mtx);
            return balance;
        }

};

void vTransactionTypes(cBankAccount *ptr)
{
    int iChoice;
    do
    {
        cout<<"1.Deposite 2.Withdraw 3.Get Balance"<<endl;
        cin>>iChoice;
        switch(iChoice)
        {
            case 1:
                    int iDeposite;
                    cout<<"Enter Amount You Want To Deposite"<<endl;
                    cin>>iDeposite;
                    thread t1([&]()
                    {
                        ptr->deposit(iDeposite);   
//lamda fn can capture local variables by reference allowing thread to access and modify data This allows for easy sharing of data between the main thread and the thread executing the lambda function//
                    });
                    t1.join();
                    break;

            case 2:
                    int iWithdrawl;
                    cout<<"Enter Amount You Want To Withdrawl"<<endl;
                    cin>>iWithdrawl;
                    thread t2([&]()
                    {
                        ptr->withdraw(iWithdrawl);
                    });
                    t2.join();
                    break;

            case 3:
                    cout<<"Your Balance is: "<<ptr->get_balance()<<endl;
                    break;
            default:
                    cout<<"Please Enter Valid Choice"<<endl;

        }
    } while (true);


}

int main() {
    cBankAccount *ptr;
    string username, password;
    int iChoice;
    int initialBalance;
    bool flag =true;
    cCreateAccount newAccount;
    cFixedDeposite FdAccount;
    cCurrencyExchanger exchangeCurrency(74.50, 59.86, 102.79, 4.49, 91.62);
    cLoan loan;
    cAuthentication auth;
    do
    {
        cout<<"1.Create Account 2.Saving Accounts 3.Current Account 4.NRI Account"
              <<"5.Apply For Loan 6.Fixed Deposite Account 7.Currency Exchanger 8.Exit"
              <<endl;

        cout<<"Enter Choice"<<endl;
        cin>>iChoice;

        switch(iChoice)
        {

            case 1:
                    newAccount.openAccount();
                    newAccount.displayAccountInfo();
                break;

            case 2:
                    cout<<"Enter initialBalance of Your Account"<<endl;
                    cin>>initialBalance;
                    ptr = new cSavingAccount(initialBalance);
                    cout << "Enter your username "<<endl;
                    cin>>username;
                    cout << "Enter your Password "<<endl;
                    cin >>password;
                    if (auth.authenticate(username, password))
                    {
                        vTransactionTypes(ptr);
                    }
                    else
                    {
                        cout << "Authentication failed" << endl;
                        InvalidCredentialsException obj("Invalid User-name and Password");
                        return 1;
                    }
                    break;

            case 3:
                    cout<<"Enter initialBalance of Your Account"<<endl;
                    cin>>initialBalance;
                    ptr = new cCurrentAccount(initialBalance);
                    cout << "Enter your username "<<endl;
                    cin>>username;
                    cout << "Enter your Password "<<endl;
                    cin >>password;
                    if (auth.authenticate(username, password))
                    {
                        vTransactionTypes(ptr);
                    }
                    else
                    {
                        cout << "Authentication failed" << endl;
                        InvalidCredentialsException obj("Invalid User-name and Password");
                        return 1;
                    }
                    break;
            case 4:
                    cout<<"Enter initialBalance of Your Account"<<endl;
                    cin>>initialBalance;
                    ptr = new cNRIAccount(initialBalance);
                    ptr->vTakeInput();
                    vTransactionTypes(ptr);
                    break;
                    
            case 5:
                    cout << "Enter your username "<<endl;
                    cin>>username;
                    cout << "Enter your Password "<<endl;
                    cin >>password;
                    if (auth.authenticate(username, password))
                    {
                        InitializeCriticalSection(&cs);
                        loan.takeInput();
                        cout<<"Monthly Payment is: "<<loan.monthlyPayment()<<endl;
                        DeleteCriticalSection(&cs);
                    }
                    else
                    {
                        cout << "Authentication failed" << endl;
                        InvalidCredentialsException obj("Invalid User-name and Password");
                        return 1;
                    }
                    break;

            case 6:
                    FdAccount.vTakeInput();
                    FdAccount.vDisplay_maturityAmount();
                    FdAccount.vIncrease_Time();
                    FdAccount.vDisplay_maturityAmount();
                    break;

            case 7:
                    exchangeCurrency.display_menu();
                    int choice;
                    cout<<"Enter Choice: "<<endl;
                    exchangeCurrency.exchange_currency(choice);
                    break;
            case 8:
                    flag=false;
                    break;

            default:
                cout<<"Invalid Choice ....."<<endl;
                cout<<"Please Enter Valid Choice"<<endl;

        }

    } while (flag);


    return 0;
}

//10 comments //343 loc's