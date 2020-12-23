#include "LOSEAccount.h"
#include <string>

using namespace std;

//------------------------------ constructor ---------------------------------
LOSEAccount::LOSEAccount(int amount, string name) {
    setInitialBalance(amount);
    setBalance(amount);
    setName(name);
}

//------------------------------- destructor ---------------------------------
LOSEAccount::~LOSEAccount() {
    this->initialBalance = 0;
    this->balance = 0;
}

//--------------------------- setInitialBalance ------------------------------
// set the initial balance
void LOSEAccount::setInitialBalance(int amount) {
    this->initialBalance = amount;
    this->balance = amount;
}

// ----------------------------- setBalance ----------------------------------
// set the balance
void LOSEAccount::setBalance(int amount) {
    this->balance = amount;
}

// ------------------------------- setName -----------------------------------
// set each LOSE account's name
void LOSEAccount::setName(string name) {
    this->name = name;
}

// ------------------------------- getName -----------------------------------
// get the name of LOSE account
string LOSEAccount::getName() const {
    return name;
}


// ----------------------------- addBalance ----------------------------------
// add the amount of money
bool LOSEAccount::addBalance(int amount) {
    if (amount < 0) return false;
    balance += amount;
    return true;
}

// ----------------------------- subBalance ----------------------------------
// substract the amount of money
bool LOSEAccount::subBalance(int amount) {
    if (amount < 0) return false;
    int temp = balance - amount;
    if (temp < 0) {
        return false;
    }
    else {
        balance = temp;
        return true;
    }
}

//--------------------------- getInitialBalance ------------------------------
// get the initial balance
int LOSEAccount::getInitialBalance() const {
    return initialBalance;
}

// ----------------------------- getBalance ----------------------------------
// get the balance
int LOSEAccount::getBalance() const {
    return balance;
}

// -------------------------------- isZero -----------------------------------
// check if the balance is zero
bool LOSEAccount::isZero() const {
    return balance == 0;
}

//------------------------------ operator< -----------------------------------
bool LOSEAccount::operator<(const LOSEAccount &other) const {
    return this->balance < other.getBalance();
}

//----------------------------- operator<= -----------------------------------
bool LOSEAccount::operator<=(const LOSEAccount &other) const {
    return this->balance > other.getBalance() ||
           this->balance == other.getBalance();
}

//------------------------------ operator> -----------------------------------
bool LOSEAccount::operator>(const LOSEAccount &other) const {
    return this->balance > other.getBalance();
}

//----------------------------- operator>= -----------------------------------
bool LOSEAccount::operator>=(const LOSEAccount &other) const {
    return this->balance > other.getBalance() ||
           this->balance == other.getBalance();
}

//----------------------------- operator== -----------------------------------
bool LOSEAccount::operator==(const LOSEAccount &other) const {
    return this->balance == other.getBalance();
}

//----------------------------- operator!= -----------------------------------
bool LOSEAccount::operator!=(const LOSEAccount &other) const {
    return !(this->balance == other.getBalance());
}
