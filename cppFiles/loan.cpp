#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;
// Define a critical section object
CRITICAL_SECTION cs;

class cLoan {
private:
    string sBrrowerName;
    double dPrincipal;
    double interestRate;
    int iDuration;

public:
    // Constructor with input validation for interest rate
    cLoan() 
    {
        InitializeCriticalSection(&cs);
    }
    void takeInput() {
        cout << "Enter the Borror Name: ";
        cin >> sBrrowerName;
        cout << "Enter the principal amount: ";
        cin >> dPrincipal;
        cout << "Enter the loan tenure (in months): ";
        cin >> iDuration;
        cout << "Enter the interest rate: ";
        cin >> interestRate;

        if (interestRate < 12) 
        {
            interestRate = 12;
            cout << "Interest rate cannot be less than 12%. Defaulting to 12%" << endl;
        }
    }

    // Function to calculate monthly payment
    double monthlyPayment() 
    {
        // Enter critical section before performing the calculation
        EnterCriticalSection(&cs);
        double r = interestRate / 100 / 12;
        double n = iDuration * 12;
        double monthly_payment = dPrincipal * r * pow(1 + r, n) / (pow(1 + r, n) - 1);

        // Leave critical section after performing the calculation
        LeaveCriticalSection(&cs);

        return monthly_payment;
    }
};

int main() 
{
    // Initialize the critical section object
    InitializeCriticalSection(&cs);
    cLoan obj;
    obj.takeInput();
    cout << obj.monthlyPayment() << endl;
    // Delete the critical section object
    DeleteCriticalSection(&cs);
    return 0;
}

// 7 comment's // 56 loc's