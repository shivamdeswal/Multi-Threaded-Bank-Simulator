#ifndef CURRENCY_EXCHANGE_H
#define CURRENCY_EXCHANGE_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Currency 
{
    private:
        string name;
        double exchange_rate;
    public:
        Currency(string name, double exchange_rate);
        double convert(double amount);
        string get_name();
};

class cCurrencyExchanger
{
    private:
        Currency usd;
        Currency cad;
        Currency pounds;
        Currency ZAR;
        Currency Euro;
    public:
        cCurrencyExchanger(double usd_rate, double cad_rate, double pounds_rate, double ZAR_rate, double Euro_rate);
        void display_menu();
        void exchange_currency(int choice);
};

#endif // CURRENCY_EXCHANGE_H
