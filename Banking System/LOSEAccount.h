#ifndef LOSEACCOUNT_H
#define LOSEACCOUNT_H

#include <string>

using namespace std;

//---------------------------------------------------------------------------
// LOSEAccount class:
//   -- holds the balance of the accounts
//   -- sets own balance and returns it
//   -- checks for empty account
//
// Implementation and assumptions:
//   -- Balance must never be negative
//
//---------------------------------------------------------------------------

class LOSEAccount {
public:
    LOSEAccount(int = 0, string = "");         // constructor
    ~LOSEAccount();                            // destructor

    void setInitialBalance(int);               // set the initial balance
    void setBalance(int);                      // set the balance

    void setName(string);                      // set each LOSE account's name
    string getName() const;                    // get the name of LOSE account

    bool addBalance(int);                      // add the money
    bool subBalance(int);                      // substract the money

    int getInitialBalance() const;             // get the initial balance
    int getBalance() const;                    // get the balance

    bool isZero() const;                       // check if the balance is zero


    // comparison operators
    bool operator<(const LOSEAccount &) const;
    bool operator<=(const LOSEAccount &) const;
    bool operator>(const LOSEAccount &) const;
    bool operator>=(const LOSEAccount &) const;
    bool operator==(const LOSEAccount &) const;
    bool operator!=(const LOSEAccount &) const;

private:
    string name;
    int initialBalance;
    int balance;
};

#endif //LAB5_LOSEACCOUNT_H
