// File Name: classlist.cpp
// Author: Derek Pauly
// Student ID: s829f376
// Assignment Number: 6
// Last Changed: May 5, 2015

// Program Desc

#include "classlist.hpp"
#include "bin_search_tree.hpp"
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

    if (!(enrollFile.is_open()) && !(dropFile.is_open())) {
        cout << "Error opening one of the files\n" << "Goodbye" << endl;
        exit(EXIT_FAILURE);
    }

    if (!student_file_to_tree(enrollFile, myTree)) {
        cout << "Enrollment file not successully loaded into binary tree" << endl;
    }
    tree_inorder(myTree, cout);
    remove_drop_students(dropFile, myTree);

    outFile << "Class List for CS 300:" << endl;

//    tree_inorder(myTree, cout);
    tree_inorder(myTree, outFile);

    cout << "The class list was saved in the file classlist.txt" << endl;

//    tree_makenull(); // TODO

    return 0;
}

bool remove_drop_students(std::ifstream &inFile, Tree &t) {
    Key student; // student to be removed from tree
    string line; // Line from file
    bool flag;
    flag = (t == NULL) ? false : true;
    while (!inFile.eof() && flag) { // stop when end of file (EOF) is reached
        getline(inFile, line);
        if (line.length() > 0) { // ensure something was read into the line
            student = read_student_record(line);
            tree_remove(t, student);
        }
    }
    if (!flag) {
        cout << "Tree is null or nothing found in file." << endl;
    }
    return flag;
}

// Reads student names from file and inserts them into a binary search tree.
bool student_file_to_tree(ifstream &inFile, Tree &t) {
    Key student; // student to be inserted into tree
    string line; // Line from part text file
    bool flag;
    flag = (t == NULL ? false : true);
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
    string name[4];
    stringstream ss; // Stringstream to hold line from file
    Key returnKey;

    ss << line; // Insert line into Stringstream
//    read_from_string_stream(ss, 7); // ignore first 7 characters (CS 300:)

    for (int i = 0; i < 4; ++i) {
        getline(ss, name[i], ':');
    }
    returnKey = name[3] + ", " + name[1] + " " + name[2]; // format Key
    return returnKey;
}