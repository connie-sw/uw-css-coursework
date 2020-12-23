#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//---------------------------------------------------------------------------
// Transaction class:
//   --
//   --
//   --
//
// Implementation and assumptions:
//   -- Maximum account of client has is 10 accounts
//   -- Four valid transaction types
//      D: deposit money from an account
//      W: withdraw money from an account
//      M: withdraw money from an account and deposit it to other account
//      H: display the history of a client
//
//   -- Client ID is limited, 4 digits : minimum 1000, maximum 9999
//   -- If one account is overdrawn, draw from subsequent accounts
//      : aplicable to money markets and bonds
//
//   -- operator <<
//      print out the primary information of the client
//      : ID, last name, first name, initial and final balances
//
//---------------------------------------------------------------------------

class Transaction {
public:

    // constructor
    Transaction(const char = '\0',
                const int = -1, const int = -1, const int = -1);

    // destructor
    ~Transaction();

    char getAction();               // get a transaction type
    int getAccount1();              // get a client's ID
    int getLOSEAccount1();          // get a LOSE account type
    int getAccount2();              // get a client's ID
    int getLOSEAccount2();          // get a LOSE account type
    int getAmount();                // get the amount of money
    bool setData(ifstream &);       // read and set a data from file
    void display();                 // Display transaction


private:
    char action;                    // transaction type
    int account1;                   // a client's ID
    int LOSEAccount1;               // a LOSE account type
    int account2;                   // a client's ID
    int LOSEAccount2;               // a LOSE account type
    int amount;                     // the amount of money

    string fundName(int);           // return name of LOSEAccount
};


#endif //LAB5_TRANSACTION_H
