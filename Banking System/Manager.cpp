#include "Manager.h"
#include <iostream>
#include <sstream>

using namespace std;

//------------------------------ constructor ---------------------------------
Manager::Manager() {
    clientList = new BSTree;
    tQueue = new Queue;
}

//------------------------------ destructor ----------------------------------
Manager::~Manager() {
    delete clientList;
    clientList = nullptr;
    delete tQueue;
    tQueue = nullptr;
}

//---------------------------- buildClientList -------------------------------
// Build client list into the list
// continually insert new client data into a BSTree
void Manager::buildClientList(ifstream &infile) {
    Client *ptr;
    bool successfulRead;                            // read good data
    bool success;                                   // successfully insert
    for (;;) {
        ptr = new Client();
        successfulRead = ptr->setData(infile);
        if (infile.eof()) {
            delete ptr;
            break;
        }

        // insert good data into the list, otherwise ignore it
        if (successfulRead) {
            success = clientList->insert(ptr);
        } else {
            delete ptr;
        }
        if (!success) break;
    }
}

//--------------------------- buildTransactions ------------------------------
// Build transcations into the list
// continually enqueue new transaction data into a Queue
void Manager::buildTransactions(ifstream &infile) {
    Transaction *ptr;
    bool successfulRead;                            // read good data
    bool success;                                   // successfully insert
    for (;;) {
        ptr = new Transaction();
        successfulRead = ptr->setData(infile);
        if (infile.eof()) {
            delete ptr;
            break;
        }

        // insert good data into the list, otherwise ignore it
        if (successfulRead) {
            success = tQueue->enqueue(ptr);
        } else {
            delete ptr;
        }
        if (!success) break;
    }
}

//-------------------------- processTransactions -----------------------------
// Process the transactions properly
// retrieve the client to process transaction
// according to the transaction type, act proper transaction
// give an error message for unknown client and unknown transaction type
void Manager::processTransactions() {
    Transaction *ptr;
    Client *targetC;
    Client *targetC2;

    // while the queue is not empty
    while (tQueue->dequeue(ptr)) {

        // chcek for transcation type
        switch (ptr->getAction()) {

            case 'D' :      // deposit

                // retrieve the client and deposit money to the account
                // add the transaction to make history
                if (clientList->retrieve(ptr->getAccount1(), targetC)) {
                    targetC->deposit(ptr->getLOSEAccount1(),
                                     ptr->getAmount());
                    targetC->addHistory(*ptr);
                    break;
                }
                    // fails to retrive the client, give an error message
                else {
                    cout << "Unknown client ID " << ptr->getAccount1()
                         <<" requrested" << endl;
                    break;
                }

            case 'W' :      // witdraw

                // retrieve the client and withdraw money from the account
                // add the transaction to make history
                if (clientList->retrieve(ptr->getAccount1(), targetC)) {
                    targetC->withdraw(ptr->getLOSEAccount1(),
                                      ptr->getAmount());
                    targetC->addHistory(*ptr);
                    break;
                }
                    // fails to retrive the client, give an error message
                else {
                    cout << "Unknown client ID " << ptr->getAccount1()
                         << " requrested" << endl;
                    break;
                }

            case 'M' :      // move

                // retrieve each client
                // withdraw money from the fisrt and depsoit to the second
                // add transactions to make history
                if ( (clientList->retrieve(ptr->getAccount1(), targetC))
                     && (clientList->retrieve(ptr->getAccount2(),
                                              targetC2)) ) {
                    targetC->withdraw(ptr->getLOSEAccount1(),
                                      ptr->getAmount());
                    targetC2->deposit(ptr->getLOSEAccount2(),
                                      ptr->getAmount());
                    targetC->addHistory(*ptr);
                    ptr = new Transaction('D',
                                          ptr->getAccount2() * 10 +ptr->getLOSEAccount2(),
                                          ptr->getAmount());
                    targetC2->addHistory(*ptr);
                    break;
                }
                    // fails to retrive the client, give an error message
                else {
                    cout << "Unknown client ID " << ptr->getAccount1()
                         << " or " << ptr->getAccount2() << " requrested"
                         << endl;
                    break;
                }

            case 'H' :      // history

                // retrieve the client and desplay the history
                if (clientList->retrieve(ptr->getAccount1(), targetC)) {
                    cout << "History of transactions for client ID = "
                         << ptr->getAccount1() << endl;
                    targetC->displayAllHistory();
                }
                    // fails to retrive the client, give an error message
                else {
                    cout << "Unknown client ID " << ptr->getAccount1()
                         << " requrested" << endl;
                    break;
                }


            default :      // for unknown types

                // give an error message
                cout << "Unknown transcation type '"
                     << ptr->getAction() << "' requested" << endl;
                break;

        }
    }

}

//-------------------------------- report -----------------------------------
// display the end of day report
void Manager::report() {
    cout<< "REPORT" << endl << endl;
    clientList->display();


}

