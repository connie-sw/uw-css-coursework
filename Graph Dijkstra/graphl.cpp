// ----------------------------------------- graphl.cpp -------------------------------------------
// Programmer Name:             Connie Lee
// Course Section Number:       CSS 343 A
// Creation Date:               07/30/2020
// Date of Last Modification:   07/31/2020
// ------------------------------------------------------------------------------------------------
//
// Purpose - displays the graph information and implement depth-first starting node #1
//
// ------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//
//  - The input data always tells the number of nodes(size) at the first line.
//  - The input data always has a description of each node, a description per line, after the size.
//  - The input data always two integers per a line after the size and descriptions.
//  - If the first integer is zero, it means the end of the data for that one graph.
//  - It is assumed that a description has at most 50 chars.
//  - It is assumed that there are at most 100 nodes.
//  - It is assumed that input data format is always correct.
//
// ------------------------------------------------------------------------------------------------

#include "graphl.h"


// ---------------------------------- constructor ---------------------------------------
// Default constructor for GraphL.
//
// predonditions: no preconditions 
// postconditions: initializes the graph nodes
// --------------------------------------------------------------------------------------
GraphL::GraphL() {

    size = 0;

    for (int i = 0; i < MAXNODES; i++) {
        arrGN[i] = new GraphNode;
        arrGN[i]->edgeHead = nullptr;
        arrGN[i]->data = nullptr;
        arrGN[i]->visited = false;

    }

}
// end of constructor


// ----------------------------------- destructor ---------------------------------------
// Destructor for for GraphL.
//
// predonditions: no preconditions 
// postconditions: deletes the graph nodes and all edge nodes
// --------------------------------------------------------------------------------------
GraphL::~GraphL() {

    for (int i = 0; i <= size; i++) {
		delete arrGN[i]->data;
        arrGN[i]->data = nullptr;
		EdgeNode* curr = arrGN[i]->edgeHead;
		removeEdge(curr);
	}
	for (int i = 0; i < MAXNODES; i++) {	
		delete arrGN[i];
        arrGN[i] = nullptr;
	}
}
// end of destructor


// ----------------------------------- removeEdge ---------------------------------------
// A helper function for destructor by deleting all edge nodes
//
// predonditions: no preconditions 
// postconditions: every node in the linked list of EdgeNode is deleted
// --------------------------------------------------------------------------------------
void GraphL::removeEdge(EdgeNode* curr) {
    
	if (curr == nullptr) return;
	
	removeEdge(curr->nextEdge);
	delete(curr);
    curr = nullptr;

}
// end of removeEdge


// ----------------------------------- buildGraph ---------------------------------------
// A function to build up graph node information and adjacency list of edges between each
// node reading from a data file.
//
// predonditions: infile is not NULL 
// postconditions: the graph information and the adjacency list are built up
// --------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile) {

    infile >> size;
    string line = "";
    getline(infile, line);

    for (int i = 1; i <= size; i++) {
        getline(infile, line);
        arrGN[i]->data = new NodeData(line);
        
    }

    int from, to;
    while (!infile.eof()) {
        infile >> from >> to;
        if (from == 0) break;
        insertEdge(from, to);
    }

}
// end of buildGraph


// ------------------------------------ insertEndge -------------------------------------
// A function to insert EdgeNodes at the beginning of the adjacency list for a GraphNode
//
// predonditions: from and to are greater or equal than 1 and less or equal than 100 
// postconditions: creates new EdgeNode and assigns the value 
// --------------------------------------------------------------------------------------
void GraphL::insertEdge(int from, int to) {

	if (arrGN[from]->edgeHead == nullptr) {
		EdgeNode* newNode = new EdgeNode;
		newNode->adjGraphNode = to;
		arrGN[from]->edgeHead = newNode;
        arrGN[from]->edgeHead->nextEdge = nullptr;
	}
	else {
		EdgeNode* newNode = new EdgeNode;
		newNode->adjGraphNode = to;
		newNode->nextEdge = arrGN[from]->edgeHead;
		arrGN[from]->edgeHead = newNode;
	}

}
// end of insertEdge


// ------------------------------------ displayGraph ------------------------------------
// A function to display each node information and edge in the graph.
//
// predonditions: no preconditions
// postconditions: each edge node of the graph is displayed
// --------------------------------------------------------------------------------------
void GraphL::displayGraph() {

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Graph:" << endl;

    for (int i = 1; i <= size; i++) {   // print out the node array information 

        // print out node number(index) and the description of the node
        cout << endl << "Node #" << i << " " << *arrGN[i]->data << endl << endl;

        EdgeNode* curr = arrGN[i]->edgeHead; // assign to curr

        while (curr != nullptr) // check for linked list
        {
            // print out linked list
            cout << " " << "edge " << i << " " << curr->adjGraphNode << endl;
            curr = curr->nextEdge;  // move pointer to next node in linked list
        }

    }
    cout << endl;

}
// end of displayGraph


// ---------------------------------- depthFirstSearch ----------------------------------
// A function to make a depth-first search and display each node in depth-first order.
//
// predonditions: no preconditions
// postconditions: each edge of the graph is displayed in depth-first order
// --------------------------------------------------------------------------------------
void GraphL::depthFirstSearch() {

    cout << endl << "Depth-fisrt ordering:";  

	for (int i = 1; i <= size; i++) {
		if (!arrGN[i]->visited)	{
			dfsHelper(i);
		}
	}
	cout << endl << endl;

}
// end of depthFirstSearch


// ------------------------------------- dfsHelper -------------------------------------
// A helper function for depthFirstSearch.
//
// predonditions: i is not NULL
// postconditions: each edge of the graph is displayed in depth-first order
// --------------------------------------------------------------------------------------
void GraphL::dfsHelper(int i) {

	cout << " " << i;
	EdgeNode* curr = arrGN[i]->edgeHead; 
	arrGN[i]->visited = true;

	while (curr != nullptr) {
		if (!arrGN[curr->adjGraphNode]->visited) {
			dfsHelper(curr->adjGraphNode);
		}
		curr = curr->nextEdge;    
	}
    
}
// end of dfsHelper
