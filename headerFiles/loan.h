#ifndef CLOAN_H
#define CLOAN_H

#include <bits/stdc++.h>
#include <Windows.h>

using namespace std;

// Define a critical section object
extern CRITICAL_SECTION cs;

class cLoan {
private:
    string sBrrowerName;
    double dPrincipal;
    double interestRate;
    int iDuration;

public:
    // Constructor with input validation for interest rate
    cLoan();
    void takeInput();

    // Function to calculate monthly payment
    double monthlyPayment();
};

#endif
