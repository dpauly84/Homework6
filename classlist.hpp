// File Name: classlist.hpp
// Author: Derek Pauly
// Student ID: s829f376
// Assignment Number: 6
// Last Changed: May 5, 2015

#ifndef _CLASSLIST_HPP_
#define _CLASSLIST_HPP_

#include "bin_search_tree.hpp"
#include <string>

const char *ENROLLMENT_FILE = // name of part input file to be read from
        "/home/shockerpc/ClionProjects/Homework6/enrollment_list";
const char *DROPLIST_FILE = // name of part input file to be read from
        "/home/shockerpc/ClionProjects/Homework6/drop_list";

Key read_student_record(std::string line);
bool student_file_to_tree(std::ifstream &inFile, Tree &t);
bool remove_drop_students(std::ifstream &inFile, Tree &t);

#endif // _CLASSLIST_HPP