#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <fstream>
#include "BSTree.h"
#include "Queue.h"

using namespace std;

//---------------------------------------------------------------------------
// Manager class:
//   -- builds a list for each client
//   -- builds a list for each client's transction
//   -- processes the transcations
//   -- displays the end of day report
//
// Implementation and assumptions:
//   -- use a binary search tree for client list
//   -- use a queue for transction list
//
//---------------------------------------------------------------------------

class Manager {
public:
    Manager();                              // constructor
    ~Manager();                             // destructor

    void buildClientList(ifstream &);       // build Client List
    void buildTransactions(ifstream &);     // build Transaction Queue
    void processTransactions();             // process next transaction
    void report();                          // get End of Day Report

private:
    BSTree* clientList;                     // container list for clients
    Queue* tQueue;                          // container queue for transctions

};

#endif //LAB5_MANAGER_H
