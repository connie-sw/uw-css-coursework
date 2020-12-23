// ----------------------------------------- bintree.cpp ------------------------------------------
// Programmer Name:             Connie Lee
// Course Section Number:       CSS 343 A
// Creation Date:               07/09/2020
// Date of Last Modification:   07/18/2020
// ------------------------------------------------------------------------------------------------
//
// Purpose - creates a binary search tree class called BinTree along with some additional functions
//           such as for tree building, tree modifing, and tree destroying
//
// ------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//
//  - It takes strings as inputs and the string “$$” terminates taking inputs.
//  - Dupliacted strings (inputs) are discarded.
//  - As it forms a binary search tree, smaller strings go left and bigger go right to be inserted.
//  - It is assumed that any binary search tree and array only has at most 100 nodes or data.
//  - "displaySideways" function and "sideways" function were given.
//
// ------------------------------------------------------------------------------------------------

#include "bintree.h"



// ----------------------------------- operator<< ---------------------------------------
// An operator to display the tree using inorder traversal.
//
// predonditions: parameters are not null
// postconditions: calls inorderHelper and display the tree and returns to output endline
// --------------------------------------------------------------------------------------
ostream& operator<<(ostream& output, const BinTree& b) {

    b.inorderHelper(b.root);
    output << endl;

    return output;

}
// end of operator<<


// ---------------------------------- inorderHelper -------------------------------------
// A helper function for operator<< to display a binary tree as in inorder.
//
// Preconditions: no preconditions 
// Postconditions: print out binary search tree in inorder
// --------------------------------------------------------------------------------------
void BinTree::inorderHelper(Node *curr) const {

    if (curr == nullptr) {
       return;
    }
    else {
        inorderHelper(curr->left);
        cout << *curr->data << " ";
        inorderHelper(curr->right);
    }

}
// end of inorderHelper


// ---------------------------------- constructor ---------------------------------------
// Default constructor for the binary search tree.
//
// predonditions: no preconditions 
// postconditions: sets a root to nullptr
// --------------------------------------------------------------------------------------
BinTree::BinTree() {

    root = nullptr;

}
// end of constructor


// -------------------------------- copy constructor ------------------------------------
// Copy constructor for the binary search tree.
// Takes care of a deep copy of the tree.
//
// predonditions: b is not NULL
// postconditions: deep copies the b
// --------------------------------------------------------------------------------------
BinTree::BinTree(const BinTree& b) {

    root = nullptr;
    *this = b;

}
// end of copy constructor


// ----------------------------------- destructor ---------------------------------------
// Destructor for the Polynomial.
// Takes care of de-allocating all nodes in the binary search tree to the system.
//
// predonditions: no preconditions 
// postconditions: deletes all Nodes
// --------------------------------------------------------------------------------------
BinTree::~BinTree() {

    makeEmpty();

}
// end of destructor


// ------------------------------------- isEmpty ----------------------------------------
// A function to tell if the BinTree empty or not.
//
// predonditions: no preconditions
// postconditions: returns to true if it's empty, false if not
// --------------------------------------------------------------------------------------
bool BinTree::isEmpty() const  {

    if (root == nullptr) {
		return true;
	}
    else {
        return false;
    }

}
// end of isEmpty


// ------------------------------------- makeEmpty --------------------------------------
// A function to function to empty the BinTree.
//
// predonditions: no preconditions
// postconditions: the BinTree is empty
// --------------------------------------------------------------------------------------
void BinTree::makeEmpty() {

    clear(root);

}
// end of makeEmpty


// -------------------------------------- clear -----------------------------------------
// A helper function of makeEmpty to empty the BinTree.
//
// predonditions: no preconditions
// postconditions: clear the BinTree and deallocate the nodes
// --------------------------------------------------------------------------------------
void BinTree::clear(Node*& curr) {

    if (curr == nullptr) {
        return;
    }
    else {
        clear(curr->left);
        clear(curr->right);

        delete curr;
        curr = nullptr;
    }

}
// end of clear


// ------------------------------------ operator= ---------------------------------------
// An assinment operator for BinTree.
//
// predonditions: b is not NULL
// postconditions: deep copies the reference b to *this
// --------------------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree& b) {

    if (*this == b) return *this;

    makeEmpty();

    if (b.root == nullptr) return *this;

    assignmentHelper(root, b.root);

    return *this;

}
// end of operator=


// ---------------------------------- assignmentHelper ----------------------------------
// A helper function for the operator=.
//
// preconditions: no preconditions
// postconditions: copies bCurr to thisCurr  
// --------------------------------------------------------------------------------------
void BinTree::assignmentHelper(Node*& thisCurr, Node* bCurr) {

    if (bCurr == nullptr) {
        return;
    }
    else {

        // copy bCurr->data to temp->data
        Node* temp = new Node;
        temp->data = bCurr->data;

        // copy temp to thisCurr
        thisCurr = temp;
        thisCurr->left = nullptr;
        thisCurr->right = nullptr;
        
        assignmentHelper(thisCurr->left, bCurr->left);
        assignmentHelper(thisCurr->right, bCurr->right);

    }
  
}
// end of assignmentHelper


// ----------------------------------- operator== ---------------------------------------
// A comparison operator for BinTree.
//
// predonditions: b is not null
// postconditions: returns to true if they are same, false if not
// --------------------------------------------------------------------------------------
bool BinTree::operator==(const BinTree& b) const {

    return equalHelper(root, b.root);

}
// end of operator==


// ----------------------------------- operator!= ---------------------------------------
// A comparison operator for BinTree.
//
// predonditions: b is not null
// postconditions: returns to false if they are same, true if not
// --------------------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree& b) const {     

    return !equalHelper(root, b.root);

}
// end of operator!=


// ---------------------------------- equalHelper ---------------------------------------
// A helper function for equalHelper.
//
// predonditions: no preconditions
// postconditions: returns to true if they are same, false if not
// --------------------------------------------------------------------------------------
bool BinTree::equalHelper(const Node* thisCurr, const Node* bCurr) const {

    // both trees are empty
    if (thisCurr == nullptr && bCurr == nullptr) {
        return true;
    }
    // one is emptty and the other is not
    else if (thisCurr == nullptr || bCurr == nullptr) {
        return false;
    }
    // data is not equal to other's
    else if (*thisCurr->data != *bCurr->data) {
        return false;
    }
    // data is equal to other's
    else {  // *thisCurr->data == *bCurr->data

        // both trees' current node pointers are on the leaves
        if ( thisCurr->left == nullptr && bCurr->left == nullptr
			    && thisCurr->right == nullptr && bCurr->right == nullptr ) {

            return true;

        }
        // keep going
        else {

            return equalHelper(thisCurr->left, bCurr->left)
			        && equalHelper(thisCurr->right, bCurr->right);

        }

    }    

}
// end of equalHelper


// ------------------------------------- insert -----------------------------------------
// A function to insert new Node to the binary search tree.
//
// predonditions: no preconditions
// postconditions: insert newData in the right place in the binary search tree
// --------------------------------------------------------------------------------------
bool BinTree::insert(NodeData* newData) {

    if (newData == nullptr) {
        return false;
    }
    else {
        return insertHelper(newData, root);
    }

}
// end of insert


// ---------------------------------- insertHelper --------------------------------------
// A helper function for insert.
//
// predonditions: newData and curr are not null
// postconditions: create a new Node with newData and insert them in the right place
// --------------------------------------------------------------------------------------
bool BinTree::insertHelper(NodeData* newData, Node*& curr) {

    if (curr == nullptr) {  // insert new node if the pointer points nothing
        curr = new Node;
        curr->data = newData;
        curr->left = nullptr;
        curr->right = nullptr;
        return true;
    }
    else if (*newData < *curr->data) {  // travarse to left for smaller
        return insertHelper(newData, curr->left);
    }
    else if (*newData > *curr->data) {  // travarse to right for larger
        return insertHelper(newData, curr->right);
    }
    else if (*newData == *curr->data) {
        return false;   // do nothing (duplicates are not allowed)
    }

    return false;

}
// end of insertHelper


// ------------------------------------ retrieve ----------------------------------------
// A function to get the NodeData* of a given object in the tree and to report whether
// the object is found.
//
// predonditions: target is not null
// postconditions: if the object is found, ptr points to the actual object in the tree
// --------------------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData& target, NodeData*& ptr) const {

    if (target == *root->data) {    // find the given object
        ptr = root->data;
        return true;
    }
    else if (target < *root->data) {    // travarse to left for smaller
        return retrieveHelper(target, root->left, ptr);
    }
    else if (target > *root->data) {    // travarse to right for larger
        return retrieveHelper(target, root->right, ptr);
    }
    return false;

}
// end of retrieve


// --------------------------------- retrieveHelper -------------------------------------
// A helper function for retrieveHelper.
//
// predonditions: no preconditions
// postconditions: if the object is found, ptr points to the actual object in the tree
//                  and returns to true, if not returns to false
// --------------------------------------------------------------------------------------
bool BinTree::retrieveHelper(const NodeData& target , Node*& curr, NodeData*& ptr) const {

    if (curr == nullptr) return false;

    if (target == *curr->data) {    // find the given object
        ptr = curr->data;
        return true;
    }
    else if (target < *curr->data) {    // travarse to left for smaller
        return retrieveHelper(target, curr->left, ptr);
    }
    else if (target > *curr->data) {    // trvarse to right for larger
        return retrieveHelper(target, curr->right, ptr);
    }
    return false;

}
// end of retrieveHelper


// ------------------------------------ getHeight ---------------------------------------
// A function to find height of a given value in the tree.
//
// predonditions: target is not null
// postconditions: returns to the height
// --------------------------------------------------------------------------------------
int BinTree::getHeight(const NodeData& target) const {

    if (isEmpty()) return 0;    // the height of an empty tree is 0

    Node* curr = root;

    while (curr != nullptr) {

        if (target == *curr->data) {    // find the given value
            return heightHelper(curr);
            break;
        }
        else if (target < *curr->data) {    // travarse to left for smaller
            curr = curr->left;
        }
        else if (target > *curr->data) {    // travrse to right for larger
            curr = curr->right;
        }

    }
    return 0;   // not found

}
// end of getHeight


// ---------------------------------- heightHelper --------------------------------------
// A helper function for getHeight.
//
// predonditions: no preconditions
// postconditions: finds and returns to the height
// --------------------------------------------------------------------------------------
int BinTree::heightHelper(Node* curr) const {

    if (curr == nullptr) return 0;

    if (curr->left == nullptr && curr->right == nullptr) return 1;

    // the height = max height of its childern + 1
    return max(heightHelper(curr->left), heightHelper(curr->right)) + 1;
    
}
// end of heightHelper


// ---------------------------------- bstreeToArray -------------------------------------
// A function to fill an array of Nodedata* by using an inorder traversal of the tree.
// It leaves the tree empty.
//
// predonditions: no preconditions
// postconditions: fills an array of NodeData* and leaves the tree empty
// --------------------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* arr[]) {

    bstreeToArrayHelper(arr, root, 0);
	makeEmpty();

    delete root;

}
// end of bstreeToArray


// ------------------------------- bstreeToArrayHelper ----------------------------------
// A helper function for bstreeToArray.
//
// predonditions: no preconditions
// postconditions: fills an array of NodeData* 
// --------------------------------------------------------------------------------------
void BinTree::bstreeToArrayHelper(NodeData* arr[], Node* curr, int index) {

	if (curr == nullptr) return;

	bstreeToArrayHelper(arr, curr->left, index);
	while (arr[index] != NULL) {
		index++;
	}
	arr[index] = curr->data;    // fill an array with NodeData
	bstreeToArrayHelper(arr, curr->right, index);
}
//end of bstreeToArrayHelper


// ---------------------------------- arrayToBSTree -------------------------------------
// A function to builds a balanced BinTree from a sorted array of NodeData* leaving the 
// array filled with NULLs.
// The root is at (low+high)/2 where low is the lowest subscript of the array range and
// high is the highest. 
//
// predonditions: no preconditions
// postconditions: builds a balanced BinTree and leaves an array empty 
// --------------------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* arr[]) {

    makeEmpty();

    int low = 0;
    int high = 0;

    while (arr[high] != NULL) {
        high++;
    }

    arrayToBSTreeHelper(arr, low, high - 1);
    
}
// end of arrayToBSTree


// ------------------------------- arrayToBSTreeHelper ----------------------------------
// A helper function for arrayToBSTree.
//
// predonditions: no preconditions
// postconditions: builds a balanced BinTree and leaves an array empty 
// --------------------------------------------------------------------------------------
void BinTree::arrayToBSTreeHelper(NodeData* arr[], int low, int high) {

    if (low > high) return; 
  
    int mid = (low + high) / 2;
    insert(arr[mid]);   // insert the NodeData to a binary search tree
    arr[mid] = NULL;    // leave the array empty
    arrayToBSTreeHelper(arr, low, mid - 1);
    arrayToBSTreeHelper(arr, mid + 1, high);

}
// end of arrayToBSTreeHelper


//---------------------------------- displaySideways ------------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
//
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
// --------------------------------------------------------------------------------------
void BinTree::displaySideways() const {
	sideways(root, 0);
}
// end of displaySideways


//-------------------------------------- sideways --------------------------------------
// Helper method for displaySideways
//
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
// --------------------------------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}
// end of sideways