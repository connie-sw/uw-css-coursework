#include "BSTree.h"
#include <iostream>
#include <ostream>

using namespace std;

//------------------------------ constructor ---------------------------------
BSTree::BSTree() {
    root = nullptr;
}

//------------------------------ destructor ----------------------------------
BSTree::~BSTree() {
    BSTree::makeEmpty();
}

//------------------------------- insert -------------------------------------
// insert item into the tree
// return recursiveInsert if root is not null
// or create new root and return true when the new root is created
bool BSTree::insert(Client *client) {
    if (root != nullptr) {
        return recursiveInsert(client, root);
    }
        //if root is null, creates new root
    else {
        root = new Node;
        root->client = client;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    return false;
}

//--------------------------- recursiveInsert --------------------------------
// recursively insert node on either left or right of BST in order
// return true when after inserting false if already inserted
bool BSTree::recursiveInsert(Client *&target, Node *&curr) {
    if (curr == nullptr) {
        curr = new Node;
        curr->client = target;
        curr->left = nullptr;
        curr->right = nullptr;
        return true;
    }
    else if (target->getID() < curr->client->getID()) {
        return recursiveInsert(target, curr->left);
    }
    else if (target->getID() >= curr->client->getID()) {
        return recursiveInsert(target, curr->right);
    }


    return false;
}


//------------------------------ retrieve ------------------------------------
// Retrieve the client
// first parameter is object to retrieve
// second parameter holds pointer to found object
// to find the client, return to recursiveRetrieve to travalse the tree
// return true if successful AND *Client points to Client
bool BSTree::retrieve(int target, Client *&ptr) const {
    if (root->client->getID() == target) {
        ptr = root->client;
        return true;
    }
    if (target < root->client->getID()) {
        return recursiveRetrieve(target, root->left, ptr);
    }
    if (target > root->client->getID()) {
        return recursiveRetrieve(target, root->right, ptr);
    }
    return false;
}

//-------------------------- recursiveRetrieve -------------------------------
// recursively retrieve node on either left or right of BST in order
// return true when
bool BSTree::recursiveRetrieve(int target, Node *&curr, Client *&ptr) const {
    if (curr == nullptr) {
        return false;
    }
    if (curr->client->getID() == target) {
        ptr = curr->client;
        return true;
    }
    if (target < curr->client->getID()) {
        return recursiveRetrieve(target, curr->left, ptr);
    }
    if (target > curr->client->getID()) {
        return recursiveRetrieve(target, curr->right, ptr);
    }
    return false;
}

//-------------------------------- display -----------------------------------
// diplay node print in order
void BSTree::display() const {
    printInOrder(root);
}

//----------------------------- printInOrder ---------------------------------
// use in order pattern to display the tree
void BSTree::printInOrder(Node *curr) const {
    if (curr != nullptr) {
        printInOrder(curr->left);
        cout << *(curr->client) << endl;
        printInOrder(curr->right);
    }
}

//------------------------------ makeEmpty -----------------------------------
// calls on delete to remove individual nodes
void BSTree::makeEmpty() {
    clear(root); // <- we can call this to clear all
}

//-------------------------------- clear -------------------------------------
// calls on clear everything
void BSTree::clear(Node *&curr) {
    if (curr->right != nullptr) {
        clear(curr->right);
    }
    if (curr->left != nullptr) {
        clear(curr->left);
    }

    delete curr->client;
    curr->client = nullptr;
    curr->right = nullptr;
    curr->left = nullptr;
    delete curr;
    curr = nullptr;
}


//------------------------------ makeEmpty -----------------------------------
// check if tree is empty
bool BSTree::isEmpty() const {
    return root == nullptr;
}