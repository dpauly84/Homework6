CC=g++ -Wall

all: classlist

classlist: bin_search_tree.o classlist.hpp classlist.cpp
	$(CC) -o classlist classlist.cpp bin_search_tree.o

bin_search_tree.o: bin_search_tree.hpp bin_search_tree.cpp
	$(CC) -c bin_search_tree.cpp

tidy :
	rm -f bin_search_tree.o core

clean :
	rm -f classlist bin_search_tree.o core classlist.txt
