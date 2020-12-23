// ------------------------------------------ bintree.h -------------------------------------------
// Programmer Name:             Connie Lee
// Course Section Number:       CSS 343 A
// Creation Date:               07/09/2020
// Date of Last Modification:   07/17/2020
// ------------------------------------------------------------------------------------------------
//
// Purpose - creates a binary search tree class called BinTree along with some additional functions
//           such as for tree building, tree modifing, and tree destroying
//
// ------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//
//  - This file is a header file of "bintree.cpp".
//
// ------------------------------------------------------------------------------------------------


#ifndef BINTREE_H
#define BINTREE_H
#include "nodedata.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


class BinTree {

    friend ostream& operator<<(ostream &, const BinTree &);		// operator to print out a binary search tree

public:
	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	

	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true

	BinTree& operator=(const BinTree &);	// assignment operator

	bool operator==(const BinTree &) const;	// comparison operator: true if both trees are same, otherwise false
	bool operator!=(const BinTree &) const; // comparison operator: true if both trees are not same, otherwise false

	bool insert(NodeData*);								// insert a node to the binary search tree
	bool retrieve(const NodeData &, NodeData* &) const; // get the NodeData* of a given object in the tree
    int getHeight (const NodeData &) const;				// find height of a given value in the tree

    void bstreeToArray(NodeData* []);		// fill an array with by using inorder traversal of the tree
    void arrayToBSTree(NodeData* []);		// build a balanced BinTree from the sorted array
	void displaySideways() const;			// provided below, displays the tree sideways
	
private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree


	void inorderHelper(Node*) const;					// display a binary tree as in inorder
	void clear(Node* &);								// helper function for operator <<
	void assignmentHelper(Node* &, Node*);				// helper function for operater =
	bool equalHelper(const Node*, const Node*) const;	// helper function for operator ==, !=

	bool insertHelper(NodeData* , Node* &);								// helper function for insert
	bool retrieveHelper(const NodeData &, Node* &, NodeData* &) const;	// helper function for retrieve
	int heightHelper (Node*) const;										// helper function for getHeight

	void sideways(Node*, int) const;			// helper for displaySideways

	void bstreeToArrayHelper(NodeData* [], Node*, int);	// helper function for bstreeToArray
	void arrayToBSTreeHelper(NodeData* [], int, int);	// helper function for arrayToBSTree

};








#endif