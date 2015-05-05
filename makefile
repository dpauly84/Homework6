CC=g++ -Wall

all: parts3

parts3: utils.o array_list.o parts3.hpp parts3.cpp
	$(CC) -o parts3 parts3.cpp array_list.o utils.o

array_list.o: array_list.hpp array_list.cpp
	$(CC) -c array_list.cpp

utils.o: utils.hpp utils.cpp
	$(CC) -c utils.cpp

tidy :
	rm -f utils.o array_list.o core

clean :
	rm -f parts3 utils.o array_list.o core
