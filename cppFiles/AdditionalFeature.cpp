#include<bits/stdc++.h>
using namespace std;
//Adding account alerts and notifications,we can implement a notification system that alerts customers about their account//
class cAccountNotification
{
    public:
        void send_notification(string account_type, string transaction_type, int amount, int balance)
        {
            cout << "Notification for " << account_type << " account:\n";
            cout << "Transaction Type: " << transaction_type << endl;
            cout << "Amount: " << amount << endl;
            cout << "Current Balance: " << balance << endl;
            cout << "-----------------------------------" << endl;
        }
};

/*Adding overdraft protection: Implement a feature to prevent customers from overdrawing their accounts by setting up overdraft
protection*/
class cDraft
{
    private:
        int overdraft_limit;

    public:
        cDraft(int limit) : overdraft_limit(limit)
        {
            // empty //
        }

        bool overdraft_check(int balance, int amount)
        {
            return balance + overdraft_limit >= amount;
        }

        int overdraft_fee()
        {
            return 50; // flat fee for overdraft
        }
};

//Class for Authentication which will allowing users to access their accounts after authentication mechanism.

class cAuthentication
{
    public:
        bool authenticate(string username,string password)
        {
            // list of authorized users and their passwords
            if (username == "shivam" && password == "shivam@123")
            {
                return true;
            }
            else if (username == "raman" && password == "raman@123")
            {
                return true;
            }
            else if (username == "uday" && password == "uday@123")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
};

int main()
{
    cAuthentication auth;
    auth.authenticate("deswal","@!23");
    cAccountNotification notify;
    notify.send_notification("Current", "Withdrawal", 10000, 12000);
}

// 3 comments // 71 loc's