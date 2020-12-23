// ------------------------------------------ graphm.h --------------------------------------------
// Programmer Name:             Connie Lee
// Course Section Number:       CSS 343 A
// Creation Date:               07/24/2020
// Date of Last Modification:   08/01/2020
// ------------------------------------------------------------------------------------------------
//
// Purpose - finds and shows the lowest cost paths from every node to every other node or specific
//           routine by implementing Dijkstra's algorithm
//
// ------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//
//  - This file is a header file of "graphm.cpp".
//
// ------------------------------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;
class GraphM {      

public:

    GraphM();                           // constructor

    void buildGraph(ifstream&);         // build up the graph information and the adjacency matrix

    bool insertEdge(int, int, int);     // insert an edge 

    bool removeEdge(int, int);          // remove an edge

    void findShortestPath();            // find the shortest path

    void displayAll();                  // display the graph information

    void display(int, int);             // display the shortest distance with path

    void findPath(int, int);            // find the path node number

    void findData(int, int);            // find the path node description



private:

    struct TableType {

        bool visited;          // whether node has been visited

        int dist;              // shortest distance from source known so far

        int path;              // previous node in path of min dist

    };

    int static const MAXNODES = 100;    // the graph has at most 100 nodes

    NodeData data[MAXNODES];            // data for graph nodes

    int C[MAXNODES][MAXNODES];          // Cost array, the adjacency matrix

    int size;                           // number of nodes in the graph

    TableType T[MAXNODES][MAXNODES];    // stores visited, distance, path

    int findMinNode(const TableType[]) const;

   };

#endif