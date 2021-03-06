// File Name: classlist.cpp
// Author: Derek Pauly
// Student ID: s829f376
// Assignment Number: 6
// Last Changed: May 6, 2015

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
    if (m_rightchild != NULL && m_leftchild != NULL) return 2;
    else if (m_rightchild == NULL && m_leftchild == NULL) return 0;
    else return 1;
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
    // successorNode is minimum value in its right subtree
    Node *originalNode = this;
    Node *successorNode = NULL;

    // Go to rightChild
    if (originalNode->rightchild()) {
        successorNode = this->rightchild();
        // Continually go to leftChild
        while (successorNode->leftchild()) {
            successorNode = successorNode->leftchild();
        }
    }

    // Successor has been found: replace
    originalNode->set_key(successorNode->key());
    if (successorNode->parent() == originalNode) {
        originalNode->set_rightchild(successorNode->rightchild());
    } else {
        successorNode->parent()->set_leftchild(NULL);
    }

    delete successorNode;
}

void Node::replace_with_predecessor() {
    // precessor is the maximum value in its left subtree
    Node *originalNode = this;
    Node *successorNode = NULL;

    // Go to leftChild
    if (originalNode->leftchild()) {
        successorNode = originalNode->leftchild();
        // Continually go to rightChild
        while (successorNode->rightchild()) {
            successorNode = successorNode->rightchild();
        }
    }

    // Successor has been found: replace
    originalNode->set_key(successorNode->key());
    if (successorNode->parent() == originalNode) {
        originalNode->set_leftchild(successorNode->leftchild());
    } else {
        successorNode->parent()->set_rightchild(NULL);
    }
    delete successorNode;
}

// Functions to implement binary search tree operations
// tree initialization - contains what is typically in a constructor
void tree_init(Tree *t) {
    (*t) = NULL;
}

// Delete all nodes of a tree - traverse in postorder to delete each child before its parent
void tree_makenull(Tree t) {
    if (tree_empty(t)) return;

    tree_makenull(t->leftchild());
    tree_makenull(t->rightchild());
    delete t;
}

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
        returnNode = t;
    }
    else if (key_lessthan(k, t->key()) && t->leftchild() != NULL) {
        returnNode = tree_search(k, t->leftchild());
    }
    else {
        if (t->rightchild() != NULL) {
            returnNode = tree_search(k, t->rightchild());
        }
        else {
            returnNode = NULL;
        }
    }
    return returnNode;
}

// add a node whose key is k to the tree
void tree_insert(Node **t, Key k) {
    if (t == NULL) return;                      // Error
    if ((*t) == NULL) {                         // Tree is empty
        (*t) = tree_makenode(k, NULL);
    }

        // Skip duplicates
    else if (key_isequal((*t)->key(), k)) {
        return;
    }

    // Go to left
    else if (key_lessthan(k, (*t)->key())) {
        if ((*t)->m_leftchild == NULL) {
            (*t)->m_leftchild = tree_makenode(k, (*t));
        }
        else {
            tree_insert(&((*t)->m_leftchild), k);
        }
    }
    // Go to right
    else {
        if ((*t)->m_rightchild == NULL) {
            (*t)->m_rightchild = tree_makenode(k, (*t));
        }
        else {
            tree_insert(&((*t)->m_rightchild), k);
        }
    }

}

// remove the node with key k from the tree if it is found
void tree_remove(Node *t, Key k) {
    Node *removeNode = tree_search(k, t);
    if (removeNode == NULL) return;                        // Nothing to remove

    // Node is leaf
    if (removeNode->num_children() == 0) {
        if (key_lessthan(removeNode->key(), removeNode->parent()->key())) {
            removeNode->parent()->set_leftchild(NULL);
        }
        else {
            removeNode->parent()->set_rightchild(NULL);
        }
        delete removeNode;
        return;
    }

    // Node has one child
    else if (removeNode->num_children() == 1) {
        Node *parentNode = removeNode->parent();
        Node *childNode = NULL;

        // Determine if child Node is on left or right side
        childNode = (removeNode->leftchild() ? removeNode->leftchild() : removeNode->rightchild());

        // Assign child Node to remove Node's parent
        childNode->set_parent(parentNode);

        // link removeNode's parentNode to removeNode's left childNode
        if (key_lessthan(removeNode->key(), parentNode->key())) {
            parentNode->set_leftchild(childNode);
        }

        // link removeNode's parentNode to removeNode's right childNode
        else {
            parentNode->set_rightchild(childNode);
        }
        delete removeNode;
        return;
    }

    // Node has two children
    else {
        removeNode->replace_with_successor();
    }
}

// traverse tree in preorder and write keys to file
void tree_preorder(Node *n, std::ostream &os) {
    if (tree_empty(n)) return;

        os << n->key() << std::endl;
        tree_preorder(n->leftchild(), os);
        tree_preorder(n->rightchild(), os);
}

// traverse tree in postorder and write keys to file
void tree_postorder(Node *n, std::ostream &os) {
    if (tree_empty(n)) return;

        tree_postorder(n->leftchild(), os);
        tree_postorder(n->rightchild(), os);
        os << n->key() << std::endl;
}

// traverse tree in inorder and write keys to file
void tree_inorder(Node *n, std::ostream &os) {
    if (tree_empty(n)) return;

    tree_inorder(n->leftchild(), os);
    os << "\n" << n->key();
    tree_inorder(n->rightchild(), os);
}

// returns true if t is empty and false otherwise
bool tree_empty(Tree t) {
    return t == NULL;
}

// returns the height of the tree
int tree_height(Tree t) {
    int left_height, right_height;

    if (t == NULL) return -1;
    right_height = tree_height(t->rightchild());
    left_height = tree_height(t->leftchild());


    return (fmax(left_height, right_height) + 1); // type conversion from double to int
}