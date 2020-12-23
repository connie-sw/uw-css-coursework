#include "Client.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//------------------------------ constructor ---------------------------------
Client::Client(const string firstName, const string lastName, int clientID) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->clientID = clientID;
    for (int i = 0; i < MAXACCOUNT; i++) {
        loseAccount[i] = new LOSEAccount;
    }
    this->history = new Queue;
    setFunds();

}

//------------------------------ destructor ----------------------------------
Client::~Client() {
    for (int i = 0; i < MAXACCOUNT; i++) {
        delete loseAccount[i];
        loseAccount[i] = nullptr;
    }
    delete history;
    history = nullptr;
}

//------------------------------- setFunds -----------------------------------
// Set a client's funds with each proper name
void Client::setFunds() {
    loseAccount[0]->setName("Money Market");
    loseAccount[1]->setName("Prime Money Market");
    loseAccount[2]->setName("Long Term Bond");
    loseAccount[3]->setName("Short Term Bond");
    loseAccount[4]->setName("500 Index Fund");
    loseAccount[5]->setName("Capital Value Fund");
    loseAccount[6]->setName("Growth Equality Fund");
    loseAccount[7]->setName("Growth Index Fund");
    loseAccount[8]->setName("Value Fund");
    loseAccount[9]->setName("Value Stock Index");
}

//-------------------------------- setData -----------------------------------
// Set a client's data from the text file
// set first name, last name, clientID, and initial balance of each fund
bool Client::setData(ifstream &infile) {
    infile >> firstName >> lastName >> clientID;

    // check for invlaid clientID
    if (clientID < MINID || clientID > MAXID) {
        return false;
    }

    // read and set data of initial balnace of each fund
    for (int i = 0; i < MAXACCOUNT; i++) {
        int amount;
        infile >> amount;

        // check for invlaid amount
        if (amount < 0) {
            return false;
        }
        // set initial balance
        loseAccount[i]->setInitialBalance(amount);
    }
    return true;
}

//--------------------------------- getID ------------------------------------
// Get the client's ID
int Client::getID() const{
    return clientID;
}

//-------------------------------- deposit -----------------------------------
// Deposit amount to the account
void Client::deposit(int account, int amount) {
    loseAccount[account]->addBalance(amount);
}

//------------------------------- withdraw -----------------------------------
// Withdraw amount from the account
// if fail, check for fund type -  0,1 : money market  &  2,3 : bond
// it can be covered with funds from anohter money market
// 0, 2 : account between account + 1 transfer available
// 1, 3 : account between account - 1 transfer available
void Client::withdraw(int account, int amount) {

    if (loseAccount[account]->subBalance(amount)) {
        return;
    }
    else if (account == 0 || account == 2) {
        int temp = amount - loseAccount[account]->getBalance() ;
        if (temp <= loseAccount[account+1]->getBalance()) {
            loseAccount[account+1]->subBalance(temp);
            loseAccount[account]->setBalance(0);
        }
        else {
            cout << "Withdraw not performed on " <<
            loseAccount[account]->getName() << " for client " <<
            clientID << endl;
        }
    }
    else if (account == 1 || account == 3) {
        int temp = amount - loseAccount[account]->getBalance() ;
        if (temp <= loseAccount[account-1]->getBalance()) {
            loseAccount[account]->setBalance(0);
            loseAccount[account-1]->subBalance(temp);
        }
        else {
            cout << "withdraw not performed on " <<
            loseAccount[account]->getName() << " for client "
            << clientID << endl;
        }
    }
    // fail - unsufficeint balance
    else {
        cout << "withdraw not performed on " << loseAccount[account]->getName()
        << " for client " << clientID << endl;
    }

}

//------------------------------ addHisotry ----------------------------------
// Make history by adding transaction to the queue
void Client::addHistory(Transaction &transaction) {
    history->enqueue(&transaction);
}

//-------------------------- displayAllHisotry -------------------------------
// Display all transaction history of a client
void Client::displayAllHistory() const {
    Transaction *ptr;
        cout << "History of transactions for client " << lastName
        << " " << firstName <<", client ID = " << clientID << endl;
        cout << "Type      Amount  Detail" << endl;
        cout << "--------- ------- --------------------------------------" << endl;
        history->display();

    cout << "history" << endl << endl;
}


//------------------------------ operator< -----------------------------------
bool Client::operator<(const Client &other) const {
    return this->clientID < other.getID();
}

//----------------------------- operator<= -----------------------------------
bool Client::operator<=(const Client &other) const {
    return this->clientID < other.getID() || this->clientID == other.getID();
}

//------------------------------ operator> -----------------------------------
bool Client::operator>(const Client &other) const {
    return this->clientID > other.getID();
}

//----------------------------- operator>= -----------------------------------
bool Client::operator>=(const Client &other) const {
    return this->clientID > other.getID() || this->clientID == other.getID();
}

//----------------------------- operator== -----------------------------------
bool Client::operator==(const Client &other) const {
    return this->clientID == other.getID();
}

//----------------------------- operator!= -----------------------------------
bool Client::operator!=(const Client &other) const {
    return this->clientID != other.getID();
}

//----------------------------- operator<< -----------------------------------
// Display primary information of the client
// for end of day report
ostream &operator<<(ostream &output, const Client &client) {
    output << client.clientID << "  " << client.lastName << " "
           << client.firstName << endl;
    output << "Initial Balance: ";
    for (int i = 0; i < MAXACCOUNT; i++) {
        output << setw(7) << client.loseAccount[i]->getInitialBalance();
    }
    output << endl;
    output << "Final Balance:   ";
    for (int i = 0; i < MAXACCOUNT; i++) {
        output <<  setw(7) << client.loseAccount[i]->getBalance();
    }
    output << endl;
    return output;
}