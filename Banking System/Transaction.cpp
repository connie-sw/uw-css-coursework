#include "Transaction.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

//------------------------------ constructor ---------------------------------
Transaction::Transaction(const char action, const int account1,
                         const int amount, const int account2) {
    this->action = action;
    this->account1 = account1 / 10;
    this->LOSEAccount1 = account1 % 10;
    this->amount = amount;
    this->account2 = account2;
}

//------------------------------ destructor ----------------------------------
Transaction::~Transaction() {}

//----------------------------- getAction ------------------------------------
// Get a transaction type what to act
char Transaction::getAction() {
    return this->action;
}


//---------------------------- getAccount1 -----------------------------------
// Get a clientID to process the transaction
int Transaction::getAccount1() {
    return this->account1;
}

//-------------------------- getLOSEAccount1 ---------------------------------
// Get a lose account of the client to process the transaction
int Transaction::getLOSEAccount1() {
    return this->LOSEAccount1;
}

//---------------------------- getAccount2 -----------------------------------
// Get a clientID to process the transaction
int Transaction::getAccount2() {
    return this->account2;
}

//-------------------------- getLOSEAccount2 ---------------------------------
// Get a lose account of the client to process the transaction
int Transaction::getLOSEAccount2() {
    return this->LOSEAccount2;
}

//----------------------------- getAmount ------------------------------------
// Get the amount of money to process the transaction
int Transaction::getAmount() {
    return this->amount;
}

//------------------------------ setData -------------------------------------
// Set data for the transaction information
bool Transaction::setData(ifstream &infile) {
    if (infile.eof()) {
        return false;
    }
    string line;
    getline(infile, line);
    istringstream ss(line);
    string type;
    getline(ss, type, ' ');
    if (type == "D" || type == "W") {
        string account1, amount;

        getline(ss, account1, ' ');
        getline(ss, amount, ' ');
        action = type[0];
        this->account1 = stoi(account1.substr(0, 4));
        this->LOSEAccount1 = stoi(account1.substr(4, 1));
        this->amount = stoi(amount);

        return true;

    } else if (type == "M") {
        string account1, amount, account2;

        getline(ss, account1, ' ');
        getline(ss, amount, ' ');
        getline(ss, account2, ' ');

        action = type[0];
        this->account1 = stoi(account1.substr(0, 4));
        this->LOSEAccount1 = stoi(account1.substr(4, 1));
        this->amount = stoi(amount);
        this->account2 = stoi(account2.substr(0, 4));
        this->LOSEAccount2 = stoi(account2.substr(4, 1));

        return true;

    } else if (type == "H") {
        string account1;

        getline(ss, account1, ' ');
        action = type[0];
        this->account1 = stoi(account1);

        return true;

    } else {
        string temp;
        action = type[0];

        return true;
    }

    return false;
}

//------------------------------ Display -------------------------------------
// Display transaction
void Transaction::display() {

    switch (action) {
        case 'D' :
            cout << "deposit" << setw(4) << "$"
            << setw(6) << amount << setw(6) << "into " <<
                 fundName(LOSEAccount1);
            break;
        case 'W' :
            cout << "withdraw" << setw(3) << "$"
            << setw(6) << amount << setw(6) << "from " <<
                 fundName(LOSEAccount1);
            break;
        case 'M' :
            cout << "move" << setw(7) << "$"
            << setw(6) << amount << setw(6) << "from " <<
                 fundName(LOSEAccount1) << endl;
            cout << setw(21) << "to "
            << fundName(LOSEAccount2) << " for client " << account2;
            break;
    }
    cout << endl;
}

//------------------------------ fundName ------------------------------------
// return fund name base on LOSEAccount
string Transaction::fundName(int loseAcc) {
    switch (loseAcc) {
        case 0 :
            return "Money Market";
        case 1 :
            return "Prime Money Market";
        case 2 :
            return "Long Term Bond";
        case 3 :
            return "Short Term Bond";
        case 4 :
            return "500 Index Fund";
        case 5 :
            return "Capital Value Fund";
        case 6 :
            return "Growth Equality Fund";
        case 7 :
            return "Growth Index Fund";
        case 8 :
            return "Value Fund";
        case 9 :
            return "Value Stock Index";
    }
    return "Invalid number";
}
