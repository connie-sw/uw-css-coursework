// ----------------------------------- polynomialDriver.cpp ---------------------------------------
// Programmer Name:             Connie Lee
// Course Section Number:       CSS 343 A
// Creation Date:               06/29/2020
// Date of Last Modification:   07/03/2020
// ------------------------------------------------------------------------------------------------
//
// Purpose - tests all functions of ADT polynomial and its copy constructor
//
// ------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//
//  - This test doesn't include cases where power is less than 0.
//  - Testing for changeCoefficient covers testing for insert and remove.
//  - It can be assumed that constructor and destructor work well as every test for all functions
//    and copy constructor is passed and there is no memory leak.
//
// ------------------------------------------------------------------------------------------------

#include <iostream>
using namespace std;

#include "polynomial.h"

int main( ) {

    cout << "---------------- TEST for changeCoefficient ----------------" << endl << endl;

    Polynomial p1;

    p1.changeCoefficient( 3, 1 );
    p1.changeCoefficient( 4, 5 );
    p1.changeCoefficient( 5.1, 3 );
    p1.changeCoefficient( -3.6, 4 );
    p1.changeCoefficient( -2.4, 7 );
    p1.changeCoefficient( 33, 2 );
    p1.changeCoefficient( -4, 0 );

    cout << "[ Inserting Terms ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   p1 = -2.4x^7 + 4x^5 -3.6x^4 + 5.1x^3 + 33x^2 + 3x -4" << endl;

    cout << "Output: " << endl;
    cout << "   p1 = " << p1 << endl << endl;

    
    p1.changeCoefficient( 0, 3 );
    p1.changeCoefficient( 0, 7 );
    p1.changeCoefficient( 0, 0 );

    cout << "[ Deleting Terms ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   p1 = 4x^5 -3.6x^4 + 33x^2 + 3x" << endl;
    
    cout << "Output: " << endl;
    cout << "   p1 = " << p1 << endl << endl;


    p1.changeCoefficient( 1, 5 );
    p1.changeCoefficient( 3.6, 4 );
    p1.changeCoefficient( -3, 1 );

    cout << "[ Changing Terms ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   p1 = x^5 + 3.6x^4 + 33x^2 -3x" << endl;
    
    cout << "Output: " << endl;
    cout << "   p1 = " << p1 << endl << endl;;


    cout << "-------------- TEST for degree AND coefficient -------------" << endl << endl;

    cout << "[ degree,  p1 = " << p1 << "]" << endl;
    cout << "Expected output: " << endl;
    cout << "   " << "5" << endl;
    
    cout << "Output: " << endl;
    cout << "   " << p1.degree() << endl << endl;

    cout << "[ power 4,  p1 = " << p1 << "]" << endl;
    cout << "Expected output: " << endl;
    cout << "   " << "3.6" << endl;
    
    cout << "Output: " << endl;
    cout << "   " << p1.coefficient(4) << endl << endl;
     

    cout << "[ power 3,  p1 = " << p1 << "]" << endl;
    cout << "Expected output: " << endl;
    cout << "   " << "0" << endl;
    
    cout << "Output: " << endl;
    cout << "   " << p1.coefficient(3) << endl << endl;


    cout << "-------------- TEST for Arithmetic Operators ---------------" << endl << endl;

    Polynomial p2;

    p2.changeCoefficient( 4, 3 );
    p2.changeCoefficient( 3.2, 5 );
    p2.changeCoefficient( -3, 2 );

    Polynomial p3;
    p3 = p1 + p2;

    cout << "[ p3 = p1 + p2 ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   p3 = 4.2x^5 + 3.6x^4 + 4x^3 + 30x^2 -3x" << endl;

    cout << "Output: " << endl;
    cout << "   p3 = " << p3 << endl << endl;


    Polynomial p4;
    p4 = p1 - p2;

    cout << "[ p4 = p1 - p2 ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   p4 = -2.2x^5 + 3.6x^4 -4x^3 + 36x^2 -3x" << endl;

    cout << "Output: " << endl;
    cout << "   p4 = " << p4 << endl << endl;


    cout << "-------------- TEST for Assignment Operators ---------------" << endl << endl;
 
    Polynomial p5 = p1;

    cout << "[ p5 = p1 ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   p5 = x^5 + 3.6x^4 + 33x^2 -3x" << endl;

    cout << "Output: " << endl;
    cout << "   p5 = " << p5 << endl << endl;


    Polynomial p6;

    p6.changeCoefficient( 5, 2 );
    p6.changeCoefficient( 21, 4 );
    p6.changeCoefficient( -4, 1 );

    Polynomial p7 = p6;

    cout << "[ p7 = p6 ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   p7 = 21x^4 + 5x^2 -4x" << endl;

    cout << "Output: " << endl;
    cout << "   p7 = " << p7 << endl << endl;


    p6 += p5;

    cout << "[ p6 += p5 ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   p6 = x^5 + 24.6x^4 + 38x^2 -7x" << endl;

    cout << "Output: " << endl;
    cout << "   p6 = " << p6 << endl << endl;
    

    p7 -= p1;

    cout << "[ p7 -= p1 ]" << endl; //x^5 +3.6x^4 + 33x^2 -3x
    cout << "Expected output: " << endl;
    cout << "   p7 = -x^5 + 17.4x^4 -28x^2 -x" << endl;

    cout << "Output: " << endl;
    cout << "   p7 = " << p7 << endl << endl;


    cout << "---------- TEST for Boolean Comparison Operators -----------" << endl << endl;

    string test1;
    if (p1 == p5) {
        test1 = "TRUE";
    }
    else {
        test1 = "FALSE";
    }

    string test2;
    if (p6 == p7) {
        test2 = "TRUE";
    }
    else {
        test2 = "FALSE";
    }

    cout << "[ p1 == p5 ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   TRUE" << endl;
    
    cout << "Output: " << endl;
    cout << "   " << test1 << endl << endl;

    cout << "[ p6 == p7 ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   FALSE" << endl;
    
    cout << "Output: " << endl;
    cout << "   " << test2 << endl << endl;


    if (p6 != p7) {
        test2 = "TRUE";
    }
    else {
        test2 = "FALSE";
    }

    if (p1 != p5) {
        test1 = "TRUE";
    }
    else {
        test1 = "FALSE";
    }

    cout << "[ p6 != p7 ]" << endl;
    cout << "Expected output: " <<endl;
    cout << "   TRUE" << endl;
    
    cout << "Output: " << endl;
    cout << "   " << test2 << endl << endl;

    cout << "[ p1 != p5 ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   FALSE" << endl;
    
    cout << "Output: " << endl;
    cout << "   " << test1 << endl << endl;


    cout << "---------------- TEST for Copy Constructor -----------------" << endl << endl;

    Polynomial p8(p1);

    cout << "[ p8(p1) ]" << endl;
    cout << "Expected output: " << endl;
    cout << "   p8 = " << p1 << endl;
    
    cout << "Output: " << endl;
    cout << "   p8 = " << p8 << endl << endl;

}
