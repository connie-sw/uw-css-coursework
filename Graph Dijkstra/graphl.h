// ------------------------------------------ graphl.h --------------------------------------------
// Programmer Name:             Connie Lee
// Course Section Number:       CSS 343 A
// Creation Date:               07/30/2020
// Date of Last Modification:   07/31/2020
// ------------------------------------------------------------------------------------------------
//
// Purpose - finds and shows the lowest cost paths from every node to every other node or specific
//           routine by implementing Dijkstra's algorithm
//
// ------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//
//  - This file is a header file of "graphl.cpp".
//
// ------------------------------------------------------------------------------------------------

#ifndef GRAPHL_H
#define GRAPHL_H
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;

class GraphL {

public:

    GraphL();                       // constructor

    ~GraphL();                      // destructor

    void buildGraph(ifstream &);    // build up the graph information and the adjacency list

    void displayGraph();            // display the graph information
    
    void depthFirstSearch();        // do dfs and display in its order


private:

    struct EdgeNode;        // forward reference for the compiler

    struct GraphNode {      // structs used for simplicity, use classes if desired

        EdgeNode* edgeHead; // head of the list of edges

        NodeData* data;     // data information about each node

        bool visited;       // whether node has been visited  

    };

    struct EdgeNode {

        int adjGraphNode;   // subscript of the adjacent graph node

        EdgeNode* nextEdge; // pointer to next edge
    };

    int static const MAXNODES = 100;    // the graph has at most 100 nodes

    int size;                           // number of nodes in the graph

    GraphNode* arrGN[MAXNODES];         // array of GraphNodes

    void insertEdge(int, int);          // insert edge node

    void removeEdge(EdgeNode*);         // remove edge node

    void dfsHelper(int);                // help for doing dfs and displaying in its order

};


#endif