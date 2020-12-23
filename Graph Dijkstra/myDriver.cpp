// ----------------------------------------- myDriver.cpp -----------------------------------------
// Programmer Name:             Connie Lee
// Course Section Number:       CSS 343 A
// Creation Date:               07/31/2020
// Date of Last Modification:   08/01/2020
// ------------------------------------------------------------------------------------------------
//
// Purpose - tests the basic functionalities of the classes to perform Dijkstra's algorihms and 
//           depth-first search
//
// ------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//
//  - This file is a modified version of the "driver.cpp" file for testing.
//  - This file is optimized for testing with "myInputdataM.txt" and "myInputdataL.txt".
//  - This file is optimized for testing GrpaphM class and GraphL class.
//
// ------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "graphm.h"
#include "graphl.h"
using namespace std;

int main() {
	
	// part 1
	ifstream infile1("myInputdataM.txt");
	if (!infile1) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the shortest path from every node to all other nodes
	for (;;){
		GraphM G;
		G.buildGraph(infile1);
		if (infile1.eof())
			break;
		G.findShortestPath();
		G.displayAll();              // display shortest distance, path to cout
		G.display(3, 1);             // display path from node 3 to 1 to cout ...
        G.display(3, 8);
		G.display(1, 2);
		G.display(1, 4);
        G.display(6, 3);
        G.display(6, 4);
        G.display(10, 7);
        G.display(10, 5);
        G.display(10, 9);
        G.display(2, 4);
        G.display(2, 10);
        G.display(4, 5);
        G.display(5, 3);
        G.display(5, 8);
        G.display(6, 4);
        G.display(6, 7);
        G.display(9, 8);
        G.display(7, 4);
        G.display(8, 7);
	}
   
	// part 2 
	ifstream infile2("myInputdataL.txt");
	if (!infile2) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the depth-first search ordering
	for (;;) {
		GraphL G;
		G.buildGraph(infile2);
		if (infile2.eof())
			break;
		G.displayGraph();
		G.depthFirstSearch();    // find and display depth-first ordering to cout
	}
	
	cout << endl;
	return 0;
}
