// -------------------------------------- polynomial.cpp ------------------------------------------
// Programmer Name:             Connie Lee
// Course Section Number:       CSS 343 A
// Creation Date:               06/25/2020
// Date of Last Modification:   07/03/2020
// ------------------------------------------------------------------------------------------------
//
// Purpose - implements ADT polynomial using a doubly-linked circular list that stores only the 
//           terms with nonzero coefficients
//
// ------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//
//  - The doubly-linked circular list has a dummy header.
//  - Insert function and remove function is used by changeCoefficient to insert and remove a term.
//  - A term which has 0 coefficient is not stored or removed.
//  - A term which has 1 coefficient shows x with its power but not the coefficient.
//  - A term which has -1 coefficient shows -x with its power but not the coefficient.
//  - A term which has 0 power shows only its coefficeint.
//  - It is assumed that power can be greater than or equal to 0.
//  - For example, the polynomial can be represented as : p1 = -5x^4 + 3x^4 + 2.6x^3 -x^2 + x + 4
//
// ------------------------------------------------------------------------------------------------

#include "polynomial.h"
#include <iostream>
#include <string>
using namespace std;


// ----------------------------------- operator<< ---------------------------------------
// An operator to print out the polynomial.
//
// predonditions: parameters are not null
// postconditions: returns to each term of the polynomial excluding dummy header
// --------------------------------------------------------------------------------------
ostream& operator<<(ostream &output, const Polynomial& p) {
    Polynomial::Term* curr = p.head->next;

    // for the first term
    if (curr->coeff == 1) {

        switch (curr->power) {
            case 0:
                output << curr->coeff << " ";             // 1 instead of 1x^0
                break;

            case 1:
                output << "x ";                           // x instead of 1x^1
                break;

            default:
                output << "x^" << curr->power << " ";     // example: x^3 instead of 1x^3
                break;
        }

    }
    else if (curr->coeff == -1) {

        switch (curr->power) {
            case 0:
                output << curr->coeff << " ";           // -1 instead of -1x^0
                break;

            case 1:
                output << "-x ";                        // -x instead of -1x^1
                break;

            default:
                output << "-x^" << curr->power << " ";  // example: -x^3 instead of -1x^3
                break;
        }

    }
    else {

        switch (curr->power) {
            case 0:
                output << curr->coeff << " ";           // example: 3 instead of 3x^0
                break;

            case 1:
                output << curr->coeff << "x ";          // example: 3x instead of 3x^1
                break;
    
            default:
                output << curr->coeff << "x^" << curr->power << " ";     // example: 7x^3
                break;
        }

    }

    
    // for other terms
    for (int i = 0; i < p.size - 1; i++) {

        curr =  curr->next;

        // + is needed right before the term if coefficient >= 0
        if (curr->coeff == 1) {
            
            switch (curr->power) {
                case 0:
                    output << "+ " << curr->coeff << " ";       // + 1 instead of + 1x^0
                    break;

                case 1:
                    output << "+ " << "x ";                     // + x instead of + 1x^1
                    break;
    
                default:
                    output << "+ " << "x^" << curr->power << " ";      // example: + x^3
                    break;
            }

        }
        // + is not needed right before the term if coefficient < 0
        else if (curr->coeff == -1) {

            switch (curr->power) {
                case 0:
                    output << curr->coeff << " ";                  // -1 instead of -1x^0
                    break;

                case 1:
                    output << "-x ";                               // -x instead of -x^0
                    break;
    
                default:
                    output << "-x^" << curr->power << " ";              // example: -x^3
                    break;
            }

        }
        // + is needed right before the term if coefficient >= 0
        else if (curr->coeff > 0) {

            switch (curr->power) {
                case 0:
                    output << "+ " << curr->coeff << " ";
                    break;

                case 1:
                    output << "+ " << curr->coeff << "x ";
                    break;
    
                default:
                    output << "+ " << curr->coeff << "x^" << curr->power << " ";
                    break;
            }

        }
        // + is not needed right before the term if coefficient < 0
        else if (curr->coeff < 0) {

            switch (curr->power) {
                case 0:
                    output << curr->coeff << " ";
                    break;

                case 1:
                    output << curr->coeff << "x ";
                    break;
    
                default:
                    output << curr->coeff << "x^" << curr->power << " ";
                    break;
            }

        }

    }

    return output;

}
// end of operator<<


// ---------------------------------- constructor ---------------------------------------
// Default constructor for the circular doubly linked list.
//
// predonditions: no preconditions 
// postconditions: initializes the size as zero and constructs dummy header which is
//                 linked to itself
// --------------------------------------------------------------------------------------
Polynomial::Polynomial() {

    size = 0;

    Term* dummy = new Term;
    dummy->coeff = 0.0;
    dummy->power = 0;
    head = dummy;
    head->prev = head;
    head->next = head;

}
// end of constructor


// -------------------------------- copy constructor ------------------------------------
// Copy constructor for the circular doubly linked list.
// Takes care of a deep copy of the original link representation.
//
// predonditions: p is not NULL
// postconditions: deep copies the p
// --------------------------------------------------------------------------------------
Polynomial::Polynomial(const Polynomial& p) {

    size = 0;

    Term* dummy = new Term;
    dummy->coeff = 0.0;
    dummy->power = 0;
    head = dummy;
    head->prev = head;
    head->next = head;

    Term* currP = p.head->next;
    for (int i = 0; i < p.size; i++) {
        changeCoefficient(currP->coeff, currP->power);
        currP = currP->next;
    }

}
// end of copy constructor


// ----------------------------------- destructor ---------------------------------------
// Destructor for the Polynomial.
// Takes care of de-allocating all link nodes to the system.
//
// predonditions: no preconditions 
// postconditions: deletes all Terms
// --------------------------------------------------------------------------------------
Polynomial::~Polynomial() {

    if (head != nullptr) {
        Term* curr = head->next;
        while(curr != head) {
            Term* temp = curr;
            curr = curr->next;
            remove(temp);
        }
        delete head;
        head = nullptr;
    }

}
// end of destructor


// ------------------------------------- degree -----------------------------------------
// A funtion that returns to the degree of the polynomial.
//
// predonditions: no preconditions
// postconditions: returns to the degree of the polynomial
// --------------------------------------------------------------------------------------
int Polynomial::degree() const {
    return head->next->power;
}
// end of degree


// ----------------------------------- coefficient --------------------------------------
// A function that returns to the coefficient of a term corresponding to the power.
//
// predonditions: the parameter(power) is greater than or equal to 0
// postconditions: returns to the coefficient of a term corresponding to the power
// --------------------------------------------------------------------------------------
double Polynomial::coefficient(const int power) const {

    // Assumption: power can be greater than or equal to 0 in this program
    if (power < 0) return 0;

    Term* curr = head->next;

    // loop for finding a term matching to the power
    for (int i = 0; i < size; i++) {
        if (curr->power == power) {
            return curr->coeff;
        }
        else {
            curr = curr->next;
        }
    }

    return 0;

}
// end of coefficient


// -------------------------------- changeCoefficient -----------------------------------
// A function that replaces a coefficient of the term corresponding to the power.
//
// predonditions: the second parameter(power) is greater than or equal to 0
// postconditions: creates a new term if the size is 0
//                 insert function is called if a new term needs to be added
//                 remove function is called if newCoefficeint is 0
//                 returns to true if replacement/addition/deletion is successful
//                 returns to false if replacement/addition/deletion is not successful
// --------------------------------------------------------------------------------------
bool Polynomial::changeCoefficient(const double newCoefficient, const int power) {

    // Assumption: power can be greater than or equal to 0 in this program
    if (power < 0) return false;

    // nothing there yet, just add a new term
    if (size == 0) {
        insert(head, newCoefficient, power);
        return true;
    }
    // something there already
    else {

        Term* curr = head->next;

        // loop for finding a term matching to the power
        for (int i = 0; i < size; i++) {

            // if the term already exists
            if (curr->power == power) {
                // if the new coefficient is 0, the term should be removed
                if (newCoefficient == 0) {
                    remove(curr);
                    return true;
                }
                // replace a coefficient to the non-zero new coefficient
                curr->coeff = newCoefficient;
                return true;
            }
            else {
                curr = curr->next;
            }
        }
        // curr is now at the head(dummy)

        curr = curr->next;

        // 0 coefficient term doesn't need to be inserted
        if (newCoefficient == 0) return false;

        // loop for finding proper position to insert a new term
        while (curr->power > power) {
            curr = curr->next;
        }
        // add a new term
        insert(curr, newCoefficient, power);
        return true;

    }
    return false;

}
// end of coefficient


// ----------------------------------- operator+ ----------------------------------------
// An operator which creates a new polynomial to get a summation of *this and &p.
// Compares power to check for common term.
// Adjusts coefficient for common term, otherwise just insert the term in order.
//
// predonditions: p is not NULL
// postconditions: returns to the polynomial which has a summation of *this and &p
// --------------------------------------------------------------------------------------
Polynomial Polynomial::operator+(const Polynomial& p) const {

    // create a new polynomial
    Polynomial result;

    Term* curr = head->next;
    Term* currP = p.head->next;

    // loof for copying *this to the new polynomial
    for (int i = 0; i < size; i++) {
        result.changeCoefficient(curr->coeff, curr->power);
        curr = curr->next;
    }
    curr = result.head->next;

    // loop for adding &p to the new polynimial
    while (currP != p.head) {

        // sum up both coefficients and replace it
        if (curr->power == currP->power) {
            double temp = curr->coeff + currP->coeff;
            result.changeCoefficient(temp, curr->power);
            curr = curr->next;
            currP = currP->next;
        }
        // just insert a term to the new polynomial
        else if (curr->power < currP->power) {
            result.changeCoefficient(currP->coeff, currP->power);
            currP = currP->next;
        }
        else { // curr->power > currP->power
            curr = curr->next;
        }

    }

    return result;

}
// end of operator+


// ----------------------------------- operator- ----------------------------------------
// An operator which creates a new polynomial to get a substraction of &p from *this.
// Compares power to check for common term.
// Adjusts coefficient for common term, otherwise substracts coefficient from 0 and just
// insert the term in order.
//
// predonditions: p is not NULL
// postconditions: returns to the polynomial which has a substraction of &p from *this
// --------------------------------------------------------------------------------------
Polynomial Polynomial::operator-(const Polynomial& p) const {

    // create a new polynomial
    Polynomial result;

    Term* curr = head->next;
    Term* currP = p.head->next;

    // loof for copying *this to the new polynomial
    for (int i = 0; i < size; i++) {
        result.changeCoefficient(curr->coeff, curr->power);
        curr = curr->next;
    }
    curr = result.head->next;

    // loop for substracting &p from the new polynimial
    while (currP != p.head) {

        // substract &p coefficient from current coeffecient and replace it
        if (curr->power == currP->power) {
            double temp = curr->coeff - currP->coeff;
            result.changeCoefficient(temp, curr->power);
            curr = curr->next;
            currP = currP->next;
        }
        // substract &p coeffecient from 0 and insert it
        else if (curr->power < currP->power) {
            double temp = -(currP->coeff);
            result.changeCoefficient(temp, currP->power);
            currP = currP->next;
        }
        else { // curr->power > currP->power
            curr = curr->next;
        }

    }

    return result;

}
// end of operator-


// ----------------------------------- operator== ---------------------------------------
// An operator to compare *this and &p.
//
// predonditions: p is not NULL
// postconditions: returns to true if they are same
//                 returns to false if they are not same
// --------------------------------------------------------------------------------------
bool Polynomial::operator==(const Polynomial& p) const {

    if (degree() == p.degree() && size == p.size) {
        Term* curr = head->next;
        Term* currP = p.head->next;

        // loop for check each term 
        for (int i = 0; i < size; i++) {
            if (curr->power == currP->power && curr->coeff == currP->coeff) {
                curr = curr->next;
                currP = currP->next;
            }
            else {
                return false;
            }
        }
        // they are same if thier every term is same
        return true;
    }

    // they are not same if their degree or size is not same
    else {
        return false;
    }

}
// end of operator==


// ----------------------------------- operator!= ---------------------------------------
// An operator to compare *this and &p.
//
// predonditions: p is not NULL
// postconditions: returns to true if they are not same
//                 returns to false if they are same
// --------------------------------------------------------------------------------------
bool Polynomial::operator!=(const Polynomial& p) const {

    if (degree() == p.degree() && size == p.size) {
        Term* curr = head->next;
        Term* currP = p.head->next;

        // loop for check each term 
        for (int i = 0; i < size; i++) {
            if (curr->power == currP->power && curr->coeff == currP->coeff) {
                curr = curr->next;
                currP = currP->next;
            }
            else {
                return true;
            }
        }
        // they are same if thier every term is same
        return false;
    }

    // they are not same if their degree or size is not same
    else {
        return true;
    }

}
// end of operator!=


// ----------------------------------- operator= ----------------------------------------
// An assignment operator for Polynomial.
//
// predonditions: p is not NULL
// postconditions: deep copies &p to *this
//                 returns to *this
// --------------------------------------------------------------------------------------
Polynomial& Polynomial::operator=(const Polynomial& p) {

    // delete every current term first
    Term* curr = head->next;
    for (int i = 0; i < size; i++) {
        remove(curr);
        curr = curr->next;
    }

    // add(replace) every term of p polynomial to this polynomial
    Term* currP = p.head->next;
    for (int i = 0; i < p.size; i++) {
        changeCoefficient(currP->coeff, currP->power);
        currP = currP->next;
    }

    return *this;

}
// end of operator=


// ----------------------------------- operator+= ---------------------------------------
// An operator which assigns a summation of *this and &p.
// Compares power to check for common term.
// Adjusts coefficient for common term, otherwise just insert the term in order.
//
// predonditions: p is not NULL
// postconditions: returns to *this which has summation of *this and &p
// --------------------------------------------------------------------------------------
Polynomial& Polynomial::operator+=(const Polynomial& p) {

    Term* curr = head->next;
    Term* currP = p.head->next;

    // loop for adding p polynomial to this polynomial
    while (currP != p.head) {

        // sum up both coefficients and replace it
        if (curr->power == currP->power) {
            double temp = curr->coeff + currP->coeff;
            changeCoefficient(temp, curr->power);
            curr = curr->next;
            currP = currP->next;
        }
        // just insert a term to this polynomial
        else if (curr->power < currP->power) {
            changeCoefficient(currP->coeff, currP->power);
            currP = currP->next;
        }
        else { // curr->power > currP->power
            curr = curr->next;
        }

    }

    return *this;

}
// end of operator+=


// ----------------------------------- operator-= ---------------------------------------
// An operator which assigns a substraction of &p from *this.
// Compares power to check for common term.
// Adjusts coefficient for common term, otherwise substracts coefficient from 0 and just
// insert the term in order.
//
// predonditions: p is not NULL
// postconditions: returns to *this which has substraction of &p from *this
// --------------------------------------------------------------------------------------
Polynomial& Polynomial::operator-=(const Polynomial& p) {

    Term* curr = head->next;
    Term* currP = p.head->next;

    // loop for substracting p polynomial from this polynomial
    while (currP != p.head) {

        // substract &p coefficient from this coeffecient and replace it
        if (curr->power == currP->power) {
            double temp = curr->coeff - currP->coeff;
            changeCoefficient(temp, curr->power);
            curr = curr->next;
            currP = currP->next;
        }
        // substract &p coeffecient from 0 and insert it
        else if (curr->power < currP->power) {
            double temp = -(currP->coeff);
            changeCoefficient(temp, currP->power);
            currP = currP->next;
        }
        else { // curr->power > currP->power
            curr = curr->next;
        }

    }

    return *this;

}
// end of operator-=


// ------------------------------------- insert -----------------------------------------
// A function that inserts a new Term node with newCoefficient and power just before the 
// existing Term pointed by the pos pointer.
// Will be used by changeCoefficient to insert a new term.
//
// predonditions: pos is not NULL, newCoefficient is not 0
// postconditions: inserts a term with newCoefficient and power just before the pos
//                 returns to true after insertion
// --------------------------------------------------------------------------------------
bool Polynomial::insert(Term* pos, const double newCoefficient, const int power) {

    Term* newT = new Term;
    Term* prvT = pos->prev;

    newT->coeff = newCoefficient;
    newT->power = power;

    prvT->next = newT;
    newT->prev = prvT;
    newT->next = pos;
    pos->prev = newT;

    size++;

    return true;
}
// end of insert


// ------------------------------------- remove -----------------------------------------
// A function that deletes the existing Term node pointed by the pos pointer.
// Will be used by changeCoefficient to remove an existing term when its coefficient is 
// changed in 0. 
// Will be used by a destructor and the operator= to de-allocates all Term nodes.
//
// predonditions: pos is not NULL
// postconditions: removes the pos term
//                 returns to true after deletion
// --------------------------------------------------------------------------------------
bool Polynomial::remove(Term* pos) {

    Term* prvT = pos->prev;
    Term* nxtT = pos->next;

    prvT->next = nxtT;
    nxtT->prev = prvT;

    delete pos;
    pos = nullptr;

    size--;

    return true;

}
// end of remove