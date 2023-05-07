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
        Currency(string name, double exchange_rate) 
        {
            this->name = name;
            this->exchange_rate = exchange_rate;
        }
        double convert(double amount) 
        {
            return amount * exchange_rate;
        }
        string get_name() 
        {
            return name;
        }
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
        cCurrencyExchanger(double usd_rate, double cad_rate, double pounds_rate, double ZAR_rate, double Euro_rate) :
            usd("US Dollars (USD)", usd_rate),
            cad("Canadian Dollars (CAD)", cad_rate),
            pounds("British Pounds (GBP)", pounds_rate),
            ZAR("South African Rand (ZAR)", ZAR_rate),
            Euro("European Euro (Euro)", Euro_rate) 
            {}

        void display_menu() 
        {
            cout << "Welcome to Currency Exchange Program!" << endl;
            cout << "Please choose the currency to exchange:" << endl;
            cout << "1. " << usd.get_name() << endl;
            cout << "2. " << cad.get_name() << endl;
            cout << "3. " << pounds.get_name() << endl;
            cout << "4. " << ZAR.get_name() << endl;
            cout << "5. " << Euro.get_name() << endl;
            cout << "Enter your choice (1-5): ";
        }

        void exchange_currency(int choice) 
        {
            double amount, result;
            Currency* currency;

            switch (choice) 
            {
                case 1:
                    currency = &usd;
                    break;
                case 2:
                    currency = &cad;
                    break;
                case 3:
                    currency = &pounds;
                    break;
                case 4:
                    currency = &ZAR;
                    break;
                case 5:
                    currency = &Euro;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                    return;
            }

            cout << "Enter amount in " << currency->get_name() << ": ";
            cin >> amount;

            result = currency->convert(amount);

            cout << fixed << setprecision(2);
            cout << amount << " " << currency->get_name() << " is equal to " << result << " INR" << endl;
        }
};

int main() 
{
    cCurrencyExchanger exchange(74.50, 59.86, 102.79, 4.49, 91.62);
    int choice;

    exchange.display_menu();
    cin >> choice;

    exchange.exchange_currency(choice);

    return 0;
}
//106//