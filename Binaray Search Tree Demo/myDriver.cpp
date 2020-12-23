// ----------------------------------------- myDriver.cpp -----------------------------------------
// Programmer Name:             Connie Lee
// Course Section Number:       CSS 343 A
// Creation Date:               07/18/2020
// Date of Last Modification:   07/18/2020
// ------------------------------------------------------------------------------------------------
//
// Purpose - tests a binary search tree class called BinTree along with some additional functions
//
// ------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//
//  - This file includes a given function to build a binary search tree and a given function to
//    initilaize a NodeData array.
//  - This file is a modified version of the "driver.cpp" file for testing.
//  - This file is optimized for testing with "myInputdata.txt".
//
// ------------------------------------------------------------------------------------------------
#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;

const int ARRAYSIZE = 100;

//global function prototypes
void buildTree(BinTree&, ifstream&);      // buill a binary search tree
void initArray(NodeData*[]);             // initialize array to NULL

int main() {
	// create file object infile and open it
	// for testing, call your data file something appropriate, e.g., inputdata.txt
	ifstream infile("myInputdata.txt");
	if (!infile) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	// the NodeData class must have a constructor that takes a string
	NodeData appleND("apple");
	NodeData blueberryND("blueberry");
	NodeData lemonND("lemon");
	NodeData watermelonND("watermelon");
	NodeData tomatoND("tomato");
	NodeData redND("red");
	NodeData greenND("green");
	NodeData blueND("blue");
	NodeData yellowND("yellow");
    NodeData brownND("brown");

	BinTree T, T2, dup;
	NodeData* ndArray[ARRAYSIZE];
	initArray(ndArray);
	cout << "Initial data:" << endl << "  ";
	buildTree(T, infile);              // builds and displays initial data
	cout << endl;
	BinTree first(T);                  // test copy constructor
	dup = dup = T;                     // test operator=, self-assignment


	while (!infile.eof()) {
		cout << "Tree Inorder:" << endl << T;             // operator<< does endl
		T.displaySideways();

		// test retrieve 
		NodeData* p;                    // pointer of retrieved object
		bool found;                     // whether or not object was found in tree
		found = T.retrieve(appleND, p);
		cout << "Retrieve  --> apple:       " << (found ? "found" : "not found") << endl;
		found = T.retrieve(blueberryND, p);
		cout << "Retrieve  --> blueberry:   " << (found ? "found" : "not found") << endl;
		found = T.retrieve(lemonND, p);
		cout << "Retrieve  --> lemon:       " << (found ? "found" : "not found") << endl;
        found = T.retrieve(watermelonND, p);
		cout << "Retrieve  --> watermelon:  " << (found ? "found" : "not found") << endl;
		found = T.retrieve(tomatoND, p);
		cout << "Retrieve  --> tomato:      " << (found ? "found" : "not found") << endl;
		found = T.retrieve(redND, p);
		cout << "Retrieve  --> red:         " << (found ? "found" : "not found") << endl;
        found = T.retrieve(greenND, p);
		cout << "Retrieve  --> green:       " << (found ? "found" : "not found") << endl;
		found = T.retrieve(blueND, p);
		cout << "Retrieve  --> blue:        " << (found ? "found" : "not found") << endl;
		found = T.retrieve(yellowND, p);
		cout << "Retrieve  --> yellow:      " << (found ? "found" : "not found") << endl;
        found = T.retrieve(brownND, p);
		cout << "Retrieve  --> brown:       " << (found ? "found" : "not found") << endl;

		// test getHeight 
		cout << "Height    --> apple:       " << T.getHeight(appleND) << endl;
		cout << "Height    --> blueberry:   " << T.getHeight(blueberryND) << endl;
		cout << "Height    --> lemon:       " << T.getHeight(lemonND) << endl;
		cout << "Height    --> watermelon:  " << T.getHeight(watermelonND) << endl;
		cout << "Height    --> tomato:      " << T.getHeight(tomatoND) << endl;
		cout << "Height    --> red:         " << T.getHeight(redND) << endl;
        cout << "Height    --> green:       " << T.getHeight(greenND) << endl;
		cout << "Height    --> blue:        " << T.getHeight(blueND) << endl;
		cout << "Height    --> yellow:      " << T.getHeight(yellowND) << endl;
		cout << "Height    --> brown:       " << T.getHeight(brownND) << endl;

		// test ==, and != 
		T2 = T;

		cout << "T == T2?       " << (T == T2 ? "equal" : "not equal") << endl;
		cout << "T != first?    " << (T != first ? "not equal" : "equal") << endl;
		cout << "T == dup?      " << (T == dup ? "equal" : "not equal") << endl;
		dup = T;

		// somewhat test bstreeToArray and arrayToBSTree
		T.bstreeToArray(ndArray);
		T.arrayToBSTree(ndArray);
		T.displaySideways();

		T.makeEmpty();                  // empty out the tree
		initArray(ndArray);             // empty out the array

		cout << "---------------------------------------------------------------"
			<< endl;
		cout << "Initial data:" << endl << "  ";
		buildTree(T, infile);
		cout << endl;

	}

	return 0;
}

//------------------------------- buildTree -----------------------------------
// A function to build a tree, read strings from a line, terminating when "$$"
// is encountered.
// Since there is some work to do before the actual insert that is specific to
// the client problem, it's best that building a tree is not a member function.
//
// preconditions: infile is not NULL
// postconditions: Build a tree
// ----------------------------------------------------------------------------
void buildTree(BinTree& T, ifstream& infile) {
	string s;

	for (;;) {
		infile >> s;
		cout << s << ' ';
		if (s == "$$") break;                // at end of one line
		if (infile.eof()) break;             // no more lines of data
		NodeData* ptr = new NodeData(s);     // NodeData constructor takes string

		bool success = T.insert(ptr);
		if (!success)
			delete ptr;                       // duplicate case, not inserted 
	}
}

//------------------------------- initArray -----------------------------------
// A function to initialize the array of NodeData* to NULL pointers.
//
// preconditions: NONE
// postconditions: initialize empty array with size of 100
// ----------------------------------------------------------------------------
void initArray(NodeData* ndArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++)
		ndArray[i] = NULL;
}