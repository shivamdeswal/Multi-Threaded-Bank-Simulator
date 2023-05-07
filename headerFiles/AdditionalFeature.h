#ifndef ADDITIONAL_FEATURE_H
#define ADDITIONAL_FEATURE_H

#include <iostream>
#include <string>

using namespace std;

class cAccountNotification
{
    public:
        void send_notification(string account_type, string transaction_type, int amount, int balance);
};

class cDraft
{
    private:
        int overdraft_limit;

    public:
        cDraft(int limit);
        bool overdraft_check(int balance, int amount);
        int overdraft_fee();
};

class cAuthentication
{
    public:
        bool authenticate(string username, string password);
};

#endif // ADDITIONAL_FEATURE_H
