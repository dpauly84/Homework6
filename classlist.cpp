// File Name: classlist.cpp
// Author: Derek Pauly
// Student ID: s829f376
// Assignment Number: 6
// Last Changed: May 5, 2015

// Program reads student names from the class enrollment file and stores them in a
// binary search tree, disregarding duplicates. The program then reads name from
// the class droplist file and removes the entries from the binary search tree.
// Finally, it writes the binary search tree in alphabetical order to classlist.txt

#include "classlist.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>


using namespace std;

int main() {

    char outFileName[] = "classlist.txt";
    ifstream enrollFile(ENROLLMENT_FILE);
    ifstream dropFile(DROPLIST_FILE);
    ofstream outFile(outFileName);

    Tree myTree = new Node;
    tree_init(myTree);

    // Ensure both input files are opened correctly
    if (!(enrollFile.is_open()) && !(dropFile.is_open())) {
        cout << "Error opening one of the files\n" << "Goodbye" << endl;
        exit(EXIT_FAILURE);
    }

    // Load enrollFile students into binary search tree
    if (!student_file_to_tree(enrollFile, myTree)) {
        cout << "Enrollment file not successully loaded into binary tree" << endl;
        exit(EXIT_FAILURE);
    }
    // Remove drop students from binary search tree
    remove_drop_students(dropFile, myTree);

    outFile << "Class List for CS 300:" << endl;

    // Write contents of tree to outFile with inorder traversal
    tree_inorder(myTree, outFile);

    cout << "The class list was saved in the file classlist.txt" << endl;

    tree_makenull(myTree);

    return EXIT_SUCCESS;
}

// Remove students who are in the file from the tree.
bool remove_drop_students(std::ifstream &inFile, Tree &t) {
    Key student; // student to be removed from tree
    string line; // Line from file
    bool flag;
    flag = (t != NULL);

    while (!inFile.eof() && flag) { // stop when end of file (EOF) is reached
        getline(inFile, line);
        if (line.length() > 0) { // ensure something was read into the line
            student = read_student_record(line);
            tree_remove(t, student);
        }
    }
    return flag;
}

// Reads student names from file and inserts them into a binary search tree.
bool student_file_to_tree(ifstream &inFile, Tree &t) {
    Key student; // student to be inserted into tree
    string line; // Line from file
    bool flag;
    flag = (t != NULL);

    while (!inFile.eof() && flag) { // stop when end of file (EOF) is reached
        getline(inFile, line);
        if (line.length() > 0) { // ensure something was read into the line
            student = read_student_record(line);
            tree_insert(t, student);
        }
    }
    return flag;
}


// Converts student information line from file to:
// lastName, firstName middleName
Key read_student_record(std::string line) {
    string name[4];  // string array to hold class, first, middle and last names
    stringstream ss; // Stringstream to hold line from file
    Key returnKey;

    ss << line; // Insert line into Stringstream

    for (int i = 0; i < 4; ++i) {
        getline(ss, name[i], ':');
    }
    returnKey = name[3] + ", " + name[1] + " " + name[2]; // format Key
    return returnKey;
}