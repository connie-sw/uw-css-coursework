// I will test your BinTree class using either this main or
// a very similar one, and this buildTree.  
// You will want to do thorough testing on your own, 
// which is done by altering the data.

// Windows and unix store files slightly differently. Windows does not
// always store an end-of-line char on the last line, where unix does.
// On windows, always make sure the cursor is on the line after
// the last line of data so it acts like unix/linux.

// presumably bintree.h includes nodedata.h so the include is not needed here

// ------------------------------------------ driver.cpp ------------------------------------------
// Programmer Name:             Connie Lee
// Course Section Number:       CSS 343 A
// Creation Date:               07/09/2020
// Date of Last Modification:   07/18/2020
// ------------------------------------------------------------------------------------------------
//
// Purpose - tests a binary search tree class called BinTree along with some additional functions
//
// ------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//
//  - This is a given file that includes a function to build a binary search tree and a function to
//    initilaize a NodeData array.
//  - This is a given file for testing functions of this program.
//  - This file is optimized for testing with "inputdata.txt".
//
// ------------------------------------------------------------------------------------------------

// #include "bintree.h"
// #include <fstream>
// #include <iostream>
// using namespace std;

// const int ARRAYSIZE = 100;

// //global function prototypes
// void buildTree(BinTree&, ifstream&);      // 
// void initArray(NodeData*[]);             // initialize array to NULL

// int main() {
// 	// create file object infile and open it
// 	// for testing, call your data file something appropriate, e.g., inputdata.txt
// 	ifstream infile("inputdata.txt");
// 	if (!infile) {
// 		cout << "File could not be opened." << endl;
// 		return 1;
// 	}

// 	// the NodeData class must have a constructor that takes a string
// 	NodeData notND("not");
// 	NodeData andND("and");
// 	NodeData sssND("sss");
// 	NodeData ttttND("tttt");
// 	NodeData oooND("ooo");
// 	NodeData yND("y");
// 	NodeData eND("e");
// 	NodeData mND("m");
// 	NodeData tND("t");

// 	BinTree T, T2, dup;
// 	NodeData* ndArray[ARRAYSIZE];
// 	initArray(ndArray);
// 	cout << "Initial data:" << endl << "  ";
// 	buildTree(T, infile);              // builds and displays initial data
// 	cout << endl;
// 	BinTree first(T);                  // test copy constructor
// 	dup = dup = T;                     // test operator=, self-assignment


// 	while (!infile.eof()) {
// 		cout << "Tree Inorder:" << endl << T;             // operator<< does endl
// 		T.displaySideways();

// 		// test retrieve 
// 		NodeData* p;                    // pointer of retrieved object
// 		bool found;                     // whether or not object was found in tree
// 		found = T.retrieve(andND, p);
// 		cout << "Retrieve --> and:  " << (found ? "found" : "not found") << endl;
// 		found = T.retrieve(notND, p);
// 		cout << "Retrieve --> not:  " << (found ? "found" : "not found") << endl;
// 		found = T.retrieve(sssND, p);
// 		cout << "Retrieve --> sss:  " << (found ? "found" : "not found") << endl;

// 		// test getHeight 
// 		cout << "Height    --> and:  " << T.getHeight(andND) << endl;
// 		cout << "Height    --> not:  " << T.getHeight(notND) << endl;
// 		cout << "Height    --> sss:  " << T.getHeight(sssND) << endl;
// 		cout << "Height    --> tttt:  " << T.getHeight(ttttND) << endl;
// 		cout << "Height    --> ooo:  " << T.getHeight(oooND) << endl;
// 		cout << "Height    --> y:  " << T.getHeight(yND) << endl;

// 		// test ==, and != 
// 		T2 = T;

// 		cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
// 		cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
// 		cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
// 		dup = T;

// 		// somewhat test bstreeToArray and arrayToBSTree
// 		T.bstreeToArray(ndArray);
// 		// for (int i = 0; i < ARRAYSIZE; i++) {
// 		// 	if (ndArray[i]== NULL) break;
// 		// 	cout << *ndArray[i] <<" ";
// 		// }
// 		// cout << endl;
// 		T.arrayToBSTree(ndArray);
// 		T.displaySideways();

// 		T.makeEmpty();                  // empty out the tree
// 		initArray(ndArray);             // empty out the array

// 		cout << "---------------------------------------------------------------"
// 			<< endl;
// 		cout << "Initial data:" << endl << "  ";
// 		buildTree(T, infile);
// 		cout << endl;

// 	}

// 	return 0;
// }

// //------------------------------- buildTree -----------------------------------
// // A function to build a tree, read strings from a line, terminating when "$$"
// // is encountered.
// // Since there is some work to do before the actual insert that is specific to
// // the client problem, it's best that building a tree is not a member function.
// //
// // preconditions: infile is not NULL
// // postconditions: Build a tree
// // ----------------------------------------------------------------------------
// void buildTree(BinTree& T, ifstream& infile) {
// 	string s;

// 	for (;;) {
// 		infile >> s;
// 		cout << s << ' ';
// 		if (s == "$$") break;                // at end of one line
// 		if (infile.eof()) break;             // no more lines of data
// 		NodeData* ptr = new NodeData(s);     // NodeData constructor takes string

// 		bool success = T.insert(ptr);
// 		if (!success)
// 			delete ptr;                       // duplicate case, not inserted 
// 	}
// }
// // end of buildTree

// //------------------------------- initArray -----------------------------------
// // A function to initialize the array of NodeData* to NULL pointers.
// //
// // preconditions: NONE
// // postconditions: initialize empty array with size of 100
// // ----------------------------------------------------------------------------
// void initArray(NodeData* ndArray[]) {
// 	for (int i = 0; i < ARRAYSIZE; i++)
// 		ndArray[i] = NULL;
// }
// // end of initArray
