#ifndef LAB5_CLIENTLIST_H
#define LAB5_CLIENTLIST_H

#include "Client.h"

using namespace std;


class BSTree {
public:
    BSTree();                               // constructor
    ~BSTree();                              // destructor

    bool insert(Client *);                  // insert object into the tree
    bool retrieve(int, Client *&) const;    // retrive the client
    void display() const;                   // print node in order
    void makeEmpty();                       // remove individual node
    bool isEmpty() const;                   // check for empty tree

private:
    struct Node {
        Client *client;
        Node *right;
        Node *left;
    };
    Node *root;

    bool recursiveInsert(Client *&, Node *&);
    bool recursiveRetrieve(int, Node *&, Client *&) const;
    void printInOrder(Node *) const;
    void clear(Node *&);

};

#endif //LAB5_CLIENTLIST_H
