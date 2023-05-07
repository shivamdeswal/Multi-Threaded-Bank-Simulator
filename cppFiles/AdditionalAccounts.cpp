#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
using namespace std;

class cFixedDeposite 
{
    private:
        int iAmount;
        int iTime;
        float interest_rate;
        int maturityAmount;
        mutex mtx;
        condition_variable cv;
    public:
        void vTakeInput() {
            unique_lock<mutex> lck(mtx);
            cout << "Enter Amount for Fixed Deposite: ";
            cin >> iAmount;
            cout << "Enter Time (in years) for Fixed Deposite: ";
            cin >> iTime;
            cout << "Enter interest rate for Fixed Deposite (in percentage): ";
            cin >> interest_rate;

            if (interest_rate > 11) 
            {
                cout << "Interest rate is more than 11%, defaulting to 11%." << endl;
                interest_rate = 11;
            }

            cv.notify_all();
        }

        void vCalculate_maturityAmount() 
        {
            unique_lock<mutex> lck(mtx);
            cv.wait(lck);

            float r = interest_rate / 100;
            maturityAmount = iAmount * (1 + r * iTime);
        }

        void vDisplay_maturityAmount() 
        {
            unique_lock<mutex> lck(mtx);
            cv.wait(lck);

            cout << "Maturity iAmount after " << iTime << " years: " << maturityAmount << endl;
        }

        void vIncrease_Time() 
        {
            unique_lock<mutex> lck(mtx);

            string choice;
            cout << "Do you want to increase your Fixed Deposite Time? (yes/no): ";
            cin >> choice;

            if (choice == "yes") {
                int new_iTime;
                cout << "Enter new Time (in years) for Fixed Deposite: ";
                cin >> new_iTime;
                iTime += new_iTime;
                cout << "Fixed Deposite Time increased. New Time is " << iTime << " years." << endl;
            }

            cv.notify_all();
        }
};


class cCreateAccount 
{
    private:
        string sName;
        string accountType;
        string aadharNumber;
        int iPhoneNumber;
        long fBalance;

    public:
        void openAccount() 
        {
            cout << "Please enter your name: "<<endl;
            cin>>sName;

            cout << "Please Enter Your Aadhar Number: "<<endl;
            cin>>aadharNumber;

            cout << "Please select an account type (savings or current or any): "<<endl;
            cin>>accountType;

            cout << "Please enter an initial deposit iAmount: "<<endl;
            cin >> fBalance;

            cout << "Please enter you mobile number: "<<endl;
            cin >> iPhoneNumber;

            cout << "\nAccount created successfully!" << endl;
        }

        void displayAccountInfo() 
        {
            cout << "\nName: " << sName << endl;
            cout << "Account Type: " << accountType << endl;
            cout << "AAdhar Card Number " <<aadharNumber<< endl;
            cout << "Account Type: " <<accountType<< endl;
            cout << "Phone Number: " <<iPhoneNumber<< endl;
            cout << "Balance: Rs" << fBalance << endl;
        }
};



int main() 
{
    cCreateAccount account;
    account.openAccount();
    account.displayAccountInfo();

    return 0;
}

//123 loc's