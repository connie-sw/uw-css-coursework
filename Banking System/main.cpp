#include <iostream>
#include "Manager.h"

using namespace std;
// assume input for client and transaction is alwasy 4 digits
int main() {

    Manager lose;

    ifstream clientData("lab5data.txt");
    ifstream transData("lab5command.txt");

    lose.buildClientList(clientData);
    lose.buildTransactions(transData);

    lose.processTransactions();
    lose.report();

    return 0;
}