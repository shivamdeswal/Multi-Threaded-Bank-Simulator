#ifndef ADDITIONAL_ACCOUNTS_H
#define ADDITIONAL_ACCOUNTS_H

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
        void vTakeInput();
        void vCalculate_maturityAmount();
        void vDisplay_maturityAmount();
        void vIncrease_Time();
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
        void openAccount();
        void displayAccountInfo();
};

#endif  // ADDITIONAL_ACCOUNTS_H
