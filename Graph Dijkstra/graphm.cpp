// ----------------------------------------- graphm.cpp -------------------------------------------
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
//  - The input data always tells the number of nodes(size) at the first line.
//  - The input data always has a description of each node, a description per line, after the size.
//  - The input data always three integers per a line after the size and descriptions.
//  - If the first integer is zero, it means the end of the data for that one graph.
//  - It is assumed that a description has at most 50 chars.
//  - It is assumed that there are at most 100 nodes.
//  - It is assumed that input data format is always correct.
//  - It is assumed that there is no same distance; even if there are same distances, only one of 
//    the path will be print out.
//
// ------------------------------------------------------------------------------------------------

#include "graphm.h"
#include <climits>
#include <iomanip>


// ---------------------------------- constructor ---------------------------------------
// Default constructor for GraphM.
//
// predonditions: no preconditions 
// postconditions: sets all dist to infinity, all visited to false, and all path to 0
// --------------------------------------------------------------------------------------
GraphM::GraphM() {

    size = 0;
    string s = "";

    for (int i = 0; i < MAXNODES; i++) {
        data[i] = s;
        for (int j = 0; j < MAXNODES; j++) {
            C[i][j] = INT_MAX;
            T[i][j].visited = false;
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
        }
    }


}
// end of constructor


// ----------------------------------- buildGraph ---------------------------------------
// A function to build up graph node information and adjacency matrix of edges between
// each node reading from a data file.
//
// predonditions: infile is not NULL 
// postconditions: the graph information and the adjacency matrix are built up
// --------------------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& infile) {

    infile >> size;

    string line = "";
    getline(infile, line);

    for (int i = 1; i <= size; i++) {
        data[i].setData(infile);
    }

    int from, to, cost;
    while (!infile.eof()) {
        infile >> from >> to >> cost;
        if (from == 0) break;
        insertEdge(from, to, cost);
    }

}
// end of buildGraph


// ----------------------------------- insertEndge --------------------------------------
// A function to insert an edge into graph between two given nodes.
//
// predonditions: from and to are greater or equal than 1 and less or equal than 100 
// postconditions: cost are assigned to given nodes
// --------------------------------------------------------------------------------------
bool GraphM::insertEdge(int from, int to, int cost) {
    return C[from][to] = cost;
}
// end of insertEdge


// ----------------------------------- removeEndge --------------------------------------
// A function to remove an edge between two given nodes.
//
// predonditions: from and to are greater or equal than 1 and less or equal than 100 
// postconditions: cost to given nodes are removed by setting cost to 0
// --------------------------------------------------------------------------------------
bool GraphM::removeEdge(int from, int to) {
    return C[from][to] = 0;
}
// end of removeEdge


// --------------------------------- findShortestPath -----------------------------------
// A function to find and update the shortest path between every node to every other node
// in the graph.
//
// predonditions: no preconditions
// postconditions: dist and path are updated
// --------------------------------------------------------------------------------------
void GraphM::findShortestPath() {

    for (int source = 1; source <=size; source++) {

        T[source][source].dist = 0;

        for (int i = 1; i <= size; i++) {

            int v = findMinNode(T[source]);     // not visited, shortest dist at this point   
            T[source][v].visited = true;    // mark v visted

            for (int w = 1; w <= size; w++) {   // for each w adjacent to v

                if (T[source][v].dist + C[v][w] < T[source][w].dist 
                    && !T[source][w].visited && C[v][w] != INT_MAX) {
                    
                    T[source][w].dist = T[source][v].dist + C[v][w];
                    T[source][w].path = v;

                }

            }

        }
        for (int i = 1; i <= size; i++) {

            if (T[source][i].path != 0) {
                T[source][i].visited = true;    // mark visted
            }

        }
        
    }

}
// end of findShortestPath


// ------------------------------------ findMinNode -------------------------------------
// A function to find the index of the node which has not visited yet and the shortest
// dist at this point.
//
// predonditions: minNode[] is no NULL
// postconditions: returns to the index of the node which has not visited yet and the
//                 shortest dist at this point
// --------------------------------------------------------------------------------------
int GraphM::findMinNode(const TableType minNode[]) const {

    int minCost = INT_MAX;
    int minIndex = 0;

    for (int i = 1; i <= size; i++) {

        if (!minNode[i].visited && minNode[i].dist < minCost) {
            minCost = minNode[i].dist;
            minIndex = i;
        }

    }
    return minIndex;
}
// end of findMinNode


// ------------------------------------ displayAll --------------------------------------
// A function to display the shortest cost and path from every node to every other node.
// This function demonstrates that the algorithm works properly by using cout.
//
// predonditions: no preconditions
// postconditions: the graph infromation is displayed
// --------------------------------------------------------------------------------------
void GraphM::displayAll() {

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Description" << setw(23) << "From_node" << setw(13) << "To_node"
        << setw(18) << "Dijkstra's" << setw(10) << "Path" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    for (int from = 1; from <= size; from++) {

        cout << data[from] << endl;     // print out node description

        for (int to = 1; to <= size; to++) {
            
            if (from != to) {
                
                cout << setw(31) << from;   // print out from node
                cout << setw(14) << to;     // print out to node

                if (T[from][to].dist == INT_MAX) {
                    cout << setw(16) << "---" << endl; // no adjacent nodes
                }
                else {
                    cout << setw(16) << T[from][to].dist;   // print out distance

                    cout << setw(10);
                    findPath(from, to); // call helper
                    cout << to << endl;
                }
            }
        }
    }
}
// end of displayAll


// -------------------------------------- display ---------------------------------------
// A function to to display the shortest distance with path information between the from 
// node to to node.
//
// predonditions: from and to are within range of 0 to 100 
// postconditions: the shortest distance between two parameter nodes is diplayed
// --------------------------------------------------------------------------------------
void GraphM::display(int from, int to) {

    cout << "--------------------------------------------------------------------------------" << endl;

    // print out nodes information
    cout << "From_node: "<< setw(3) << from << setw(13) << "To_node: "<< setw(3) << to;

    if (T[from][to].dist == INT_MAX || T[from][to].dist == 0) { 
        
        cout << setw(20) << "---" <<  endl; // no shortest path

    }
    else {

        // print out shortest distance and path
        cout << setw(16) << "Dijkstra's: "<< setw(4) << T[from][to].dist << setw(10) << 
            "Path: " << setw(3);

        findPath(from, to); // call helper
        cout << to << endl << endl;

        cout << "Path_node" << endl;
        findData(from, to); // call helper
        cout << "  " << data[to] << endl;

    }
    cout << endl;

}
// end of display


// ------------------------------------- findPath ---------------------------------------
// A helper function for displayAll and display by finding the path node number.
//
// predonditions: from and to are within range of 0 to 100 
// postconditions: the path node number is displayed
// --------------------------------------------------------------------------------------
void GraphM::findPath(int from, int to) {

    if (T[from][to].dist == INT_MAX || T[from][to].dist == 0) return; // no path

    int pathNumber = T[from][to].path;
	findPath(from, pathNumber);  
    
    cout << pathNumber << " ";      // print out path

}
// end of findPath


// ------------------------------------- findData ---------------------------------------
// A helper function for display by finding the path node descripltion.
//
// predonditions: from and to are within range of 0 to 100 
// postconditions: the path node description is displayed
// --------------------------------------------------------------------------------------
void GraphM::findData(int from, int to) {

    if (T[from][to].dist == INT_MAX || T[from][to].dist == 0) return; // no data

    int pathNumber = T[from][to].path;
	findData(from, pathNumber);

    cout << "  " << data[pathNumber] << endl;    // print out description
}
// end of findData