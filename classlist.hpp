// File Name: classlist.hpp
// Author: Derek Pauly
// Student ID: s829f376
// Assignment Number: 6
// Last Changed: May 6, 2015

#ifndef _CLASSLIST_HPP_
#define _CLASSLIST_HPP_

#include "bin_search_tree.hpp"
#include <string>

const char *ENROLLMENT_FILE = // name of enrollment input file to be read from
        "enrollment_list";
const char *DROPLIST_FILE = // name of droplist input file to be read from
        "drop_list";

// Converts student information line from file to:
// lastName, firstName middleName
Key read_student_record(std::string line);

// Reads student names from file and inserts them into a binary search tree.
void student_file_to_tree(std::ifstream &inFile, Tree *t);

// Remove students who are in the file from the tree.
void remove_drop_students(std::ifstream &inFile, Tree *t);

#endif // _CLASSLIST_HPP
