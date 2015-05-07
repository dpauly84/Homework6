// File Name: bin_search_tree.hpp
// Author: Derek Pauly
// Student ID: s829f376
// Assignment Number: 6
// Last Changed: May 6, 2015

#ifndef _BIN_SEARCH_TREE_HPP_
#define _BIN_SEARCH_TREE_HPP_

#include <string>

// Type definitions
typedef std::string Key;

// Prototypes for stand-alone Key functions
bool key_isequal(Key a, Key b);
bool key_lessthan(Key a, Key b);

// Type definitions for Node and Tree
class Node
{
public:
    // Tree functions can access Node data through the accessors, but
    // tree_remove must access the private methods, so it is a friend.
    friend void tree_remove(Node *t, Key k);
    // tree_insert needs access to the private data
    friend void tree_insert(Node **t, Key k);

    // Accessors
    Key key();
    Node *parent();
    Node *leftchild();
    Node *rightchild();
    int num_children();

    // Mutators
    void set_key(Key k);
    void set_parent(Node *p);
    void set_leftchild(Node *l);
    void set_rightchild(Node *r);



private:
    // Private methods
    void replace_with_successor();
    void replace_with_predecessor();

    // Data members
    Key m_key;
    Node *m_parent;
    Node *m_leftchild;
    Node *m_rightchild;
};

typedef Node * Tree;

// Function prototypes
void tree_init(Tree *t);
void tree_makenull(Tree t);
Node *tree_makenode(Key k, Node *parent);
Node *tree_search(Key k, Tree t);
void tree_insert(Tree *t, Key k);
void tree_remove(Node *t, Key k);
void tree_preorder(Node *n, std::ostream &file);
void tree_postorder(Node *n, std::ostream &file);
void tree_inorder(Node *n, std::ostream &file);
bool tree_empty(Tree t);
int tree_height(Tree t);

#endif // _BIN_SEARCH_TREE_HPP_