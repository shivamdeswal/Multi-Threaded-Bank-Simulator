#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

class NegativeBalanceException : public runtime_error
{
public:
    NegativeBalanceException(const string &message) : runtime_error(message) {}
};

class InvalidAmountException : public runtime_error
{
public:
    InvalidAmountException(const string &message) : runtime_error(message) {}
};

class InsufficientFundsException : public runtime_error
{
public:
    InsufficientFundsException(const string &message) : runtime_error(message) {}
};

class AccountNotFoundException : public runtime_error
{
public:
    AccountNotFoundException(const string &message) : runtime_error(message) {}
};

class TransferException : public runtime_error
{
public:
    TransferException(const string &message) : runtime_error(message) {}
};

class DuplicateAccountException : public runtime_error
{
public:
    DuplicateAccountException(const string &message) : runtime_error(message) {}
};

class InvalidCredentialsException : public runtime_error
{
public:
    InvalidCredentialsException(const string &message) : runtime_error(message) {}
};

#endif // EXCEPTIONS_H
