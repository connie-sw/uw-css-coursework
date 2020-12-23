#ifndef CLIENT_H
#define CLIENT_H

#include <fstream>
#include "LOSEAccount.h"
#include "Queue.h"

using namespace std;

//---------------------------------------------------------------------------
// Client class:
//   -- holds the primary information of the client
//   -- calls for transactions
//   -- displays client's transaction history
//
// Implementation and assumptions:
//   -- Maximum account of client has is 10 accounts
//   -- listLOSE index present for each section bellow
//      0: Money Market         5: Capital Value Fund
//      1: Prime Money Market   6: Growth Equity Fund
//      2: Long-Term Bond       7: Growth Index Fund
//      3: Short-Term Bond      8: Value Fund
//      4: 500 Index Fund       9: Value Stock Index
//
//   -- Client ID is limited, cannot exceed 9999
//   -- If one account is overdrawn, draw from subsequent accounts
//
//---------------------------------------------------------------------------

const int MINID = 1000;
const int MAXID = 9999;
const int MAXACCOUNT = 10;


class Client {
    // display client information
    friend ostream &operator<<(ostream &, const Client &);

public:
    Client(const string = "", const string = "", int = 0);     // constructor

    ~Client();                              // destructor

    bool setData(ifstream &);               // read and set data from file
    int getID() const;                      // get the client ID

    void deposit(int, int);                 // deposit accounts
    void withdraw(int, int);                // withdraw accounts
    void addHistory(Transaction &);         // add transaction history
    void displayAllHistory() const;         // display all transaction

    // copy operator
    Client &operator=(const Client &);

    // comparison operators
    bool operator<(const Client &) const;
    bool operator<=(const Client &) const;
    bool operator>(const Client &) const;
    bool operator>=(const Client &) const;
    bool operator==(const Client &) const;
    bool operator!=(const Client &) const;


private:
    string firstName;                       // client's first name
    string lastName;                        // client's last name
    int clientID;                           // client's ID
    LOSEAccount* loseAccount[MAXACCOUNT];   // array for client's LOSE account
    Queue* history;                         // queue for client's history

    void setFunds();                        // set client's funds (LOSE)

};


#endif