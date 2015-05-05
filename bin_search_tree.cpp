// File Name: classlist.cpp
// Author: Derek Pauly
// Student ID: s829f376
// Assignment Number: 6
// Last Changed: May 5, 2015

// Program Descriptin

#include "bin_search_tree.hpp"
#include <iostream>
#include <cmath>

// Functions to implement Key operations

// returns true if the two keys are equal, or false otherwise
bool key_isequal(Key a, Key b) { return (a == b); }

// returns true if a < b, or false otherwise
bool key_lessthan(Key a, Key b) { return a.compare(b) < 0; }

// Functions to implement Node methods

// Accessors
Key Node::key() { return m_key; }

Node *Node::parent() { return m_parent; }

Node *Node::leftchild() { return m_leftchild; }

Node *Node::rightchild() { return m_rightchild; }

int Node::num_children() {
    using namespace std;
    if (m_rightchild != NULL && m_leftchild != NULL) return 2;
    else if (m_rightchild != NULL || m_leftchild != NULL) return 1;
    else return 0;
}

// Mutators
void Node::set_key(Key k) { m_key = k; }

void Node::set_parent(Node *p) { m_parent = p; }

void Node::set_leftchild(Node *l) { m_leftchild = l; }

void Node::set_rightchild(Node *r) { m_rightchild = r; }

// The following two functions are private methods of Node. They are not
// available to the user application and are used only to implement tree
// operations.
void Node::replace_with_successor() {
    // successor is minimum value in its right subtree
    using namespace std;
    Node *originalNode = this;
    Node *successor = NULL;
    if (this->rightchild()) {
//        cout << "successor has right child" << endl;
        successor = this->rightchild();
//        cout << "successor: " << successor->key() << endl;
        while (successor->leftchild()) {
//            cout << "While successor->leftchild()" << endl;
            successor = successor->leftchild();
        }
    }

    originalNode->set_key(successor->key());
//    cout << "originalNode->set_key(successor->key()): " << originalNode->key() << endl;
    if (successor->parent() == originalNode) {
//        cout << "(successor->parent() == originalNode): " << endl;
        originalNode->set_rightchild(successor->rightchild());
    } else {
        successor->parent()->set_leftchild(NULL);
    }

    delete successor;
}

void Node::replace_with_predecessor() {
    // precessor is the maximum value in its left subtree

}

// Functions to implement binary search tree operations
// tree initialization - contains what is typically in a constructor
void tree_init(Tree &t) {
    t->set_key("");
    t->set_parent(NULL);
    t->set_leftchild(NULL);
    t->set_rightchild(NULL);
}

// Delete all nodes of a tree - traverse in postorder to delete each child before its parent
void tree_makenull(Tree t) { t = NULL; } // TODO ?

// create a new node for a tree
Node *tree_makenode(Key k, Node *parent) {
    Node *newNode = new Node;
    newNode->set_key(k);
    newNode->set_parent(parent);
    newNode->set_leftchild(NULL);
    newNode->set_rightchild(NULL);
    return newNode;
}

// return pointer to node with key k if found in tree, otherwise NULL
Node *tree_search(Key k, Tree t) {
    Node *returnNode = NULL;
    if (tree_empty(t)) {
        return NULL;
    }
    if (key_isequal(k, t->key())) {
//        std::cout << "Key is found t returned." << std::endl;
        returnNode = t;
    }
    else if (key_lessthan(k, t->key()) && t->leftchild() != NULL) {
//        std::cout << "Going left, t.leftchild is not null." << std::endl;
//        std::cout << "Address of t->leftchild() sent to tree_search: " << t->leftchild() << std::endl;
        returnNode = tree_search(k, t->leftchild());
    }
    else {
        if (t->rightchild() != NULL) {
//            std::cout << "Going right, t.rightchild is not null." << std::endl;
            returnNode = tree_search(k, t->rightchild());
        }
        else {
//            std::cout << "Key not found returning NULL." << std::endl;
            returnNode = NULL;
        }
    }
    return returnNode;
}

// add a node whose key is k to the tree
void tree_insert(Node *&t, Key k) {
    if (tree_empty(t)) {                        // Tree is empty
        t->set_key(k);
    }
    else if (key_isequal(t->key(), k)) {    // Skip duplicates
        return;
    }
    else if (key_lessthan(k, t->key())) {    // Go to left
        if (t->leftchild() == NULL) {
            t->set_leftchild(tree_makenode(k, t));
        }
        else {
            Node *leftNodeCopy = t->leftchild();
            tree_insert(leftNodeCopy, k);
        }
    }
    else {                                    // Go to right
        if (t->rightchild() == NULL) {
            t->set_rightchild(tree_makenode(k, t));
        }
        else {
            Node *rightNodeCopy = t->rightchild();
            tree_insert(rightNodeCopy, k);
        }
    }

}

// remove the node with key k from the tree if it is found
void tree_remove(Node *t, Key k) {
    using namespace std;
    Node *removeNode = tree_search(k, t);
//    cout << "removeNode: " << removeNode->key() << endl;
    if (removeNode == NULL) return;                        // Nothing to remove
    // Node is leaf
    if (removeNode->leftchild() == NULL && removeNode->rightchild() == NULL) {
//        cout << "node is leaf:" << endl;
        if (key_lessthan(removeNode->key(), removeNode->parent()->key())) {
//            cout << "Key less than:" << endl;
            removeNode->parent()->set_leftchild(NULL);
        }
        else {
            removeNode->parent()->set_rightchild(NULL);
//            cout << "KEy greather than than:" << endl;

        }
        delete removeNode;
        return;
    }
        // Node has two children
    else if (removeNode->leftchild() != NULL && removeNode->rightchild() != NULL) {
//        cout << "node has two children" << endl;
        removeNode->replace_with_successor();
    }
        // Node has one child
    else {
//        cout << "node has one chid" << endl;
        Node *parentNode = removeNode->parent();
        Node *childNode = NULL;
        childNode = (removeNode->leftchild() ? removeNode->leftchild() : removeNode->rightchild());
        childNode->set_parent(parentNode);
        if (key_lessthan(removeNode->key(), parentNode->key())) {            // link to left child
            parentNode->set_leftchild(childNode);
        }
        else {                                                            // link to right
            parentNode->set_rightchild(childNode);
        }
        delete removeNode;
        return;
    }
}

// traverse tree in preorder and write keys to file
void tree_preorder(Node *n, std::ostream &os) {
    if (n != NULL && tree_empty(n)) {
        os << "Tree is empty" << std::endl;
        return;
    }
    if (n) {
        os << n->key() << std::endl;
        tree_preorder(n->leftchild(), os);
        tree_preorder(n->rightchild(), os);
    }
}

// traverse tree in postorder and write keys to file
void tree_postorder(Node *n, std::ostream &os) {
    if (n != NULL && tree_empty(n)) {
        os << "Tree is empty" << std::endl;
        return;
    }
    if (n) {
        tree_postorder(n->leftchild(), os);
        tree_postorder(n->rightchild(), os);
        os << n->key() << std::endl;
    }
}

// traverse tree in inorder and write keys to file
void tree_inorder(Node *n, std::ostream &os) {
    if (n != NULL && tree_empty(n)) {
        os << "Tree is empty" << std::endl;
        return;
    }
    if (n == NULL) return;
    tree_inorder(n->leftchild(), os);
    os << "\n" << n->key();
    tree_inorder(n->rightchild(), os);
}

// returns true if t is empty and false otherwise
bool tree_empty(Tree t) {
    return t->key() == "";
}

// returns the height of the tree
int tree_height(Tree t) {
    int leftInt = 0;
    int rightInt = 0;
    if (tree_empty(t) || t == NULL) {
        std::cout << "empty" << std::endl;
        return 0;
    }
    if (t->rightchild()) {
        ++rightInt;
        std::cout << "rightInt" << rightInt << std::endl;
        rightInt = tree_height(t->rightchild());
    }
    if (t->leftchild()) {
        ++leftInt;
        std::cout << "leftInt" << leftInt << std::endl;
        rightInt = tree_height(t->leftchild());
    }


    return (int) (fmax(leftInt, rightInt) + 1);
}