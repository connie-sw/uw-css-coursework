#include "Queue.h"
#include <assert.h>
#include <iostream>
// note -- destructor, copy constructor, clear, isFull are missing
//      -- subject to typos

//------------------------------ constructor ---------------------------------
Queue::Queue() {
    front = rear = nullptr;
}

//------------------------------ destructor ---------------------------------
Queue::~Queue() {
    clear();
}

//-------------------------------- clear -------------------------------------
// clear everything
void Queue::clear() {

    if (isEmpty()) {
        return;
    }

    Node* current;    // to walk list

    // walk until end of the list and free every memory that was assigned
    while (front != nullptr) {
        current = front;
        front = front->next;
        current->next = nullptr;
        delete current->ptr;
        current->ptr = nullptr;
        delete current;
        current = nullptr;
    }
    // set front pointer to empty
    front = rear = nullptr;

}

//------------------------------ isEmpty -------------------------------------
// check to see if queue is empty
bool Queue::isEmpty() const {
    return (front == nullptr);
}

//------------------------------ enqueue -------------------------------------
// insert item into rear of queue
bool Queue::enqueue(Transaction *transPtr) {

    // create a Node for transaction object.
    Node *nodeptr = new Node;
    assert(nodeptr != nullptr);
    nodeptr->ptr = transPtr;
    nodeptr->next = nullptr;

    // link at front if empty, otherwise at the rear
    if (isEmpty())
        front = nodeptr;
    else
        rear->next = nodeptr;
    rear = nodeptr;                                // either way, rear is set
    return true;
}

//---------------------------------- dequeue ---------------------------------
// remove item from front of queue
bool Queue::dequeue(Transaction *&transPtr) {
    if (isEmpty()) {
        return false;
    }

    transPtr = front->ptr;
    Node *nodeptr = front;
    front = front->next;
    if (isEmpty())
        rear = nullptr;                   // if it's the last node in list
    delete nodeptr;
    nodeptr = nullptr;
    return true;
}

//---------------------------------- peek ------------------------------------
// return item at front of queue
bool Queue::peek(Transaction *&transPtr) const {
    if (isEmpty())
        return false;

    transPtr = front->ptr;
    return true;
}

void Queue::display()  {

    Node* current = front;
    while (current != nullptr) {
        current->ptr->display();
        current = current->next;
    }
    cout << endl;
}
