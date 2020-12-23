#ifndef QUEUE_H
#define QUEUE_H

#include "Transaction.h"


class Queue {
public:
    Queue();

    ~Queue();

    void clear();

    bool isEmpty() const;

    // insert item, assume object passed in is valid, return whether successful
    bool enqueue(Transaction *);

    // remove item, parameter is removed item, return whether item is removed
    bool dequeue(Transaction *&);

    // retrieve item, parameter is item at top, return whether item exists
    bool peek(Transaction *&) const;

    void display() ;

private:
    struct Node {
        Transaction *ptr;
        Node *next;
    };
    Node *front;
    Node *rear;
};


#endif // QUEUE_H
