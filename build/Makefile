#variables
FLAGS=-c -Wall -std=c++11

all: main

main: main.o BinarySearchTree.o BSTNode.o HashTable.o HashNode.o
	g++ -o main main.o BinarySearchTree.o BSTNode.o HashTable.o HashNode.o

main.o: ../src/main.cpp
	g++ $(FLAGS) ../src/main.cpp

BinarySearchTree.o: ../src/BinarySearchTree.cpp
	g++ $(FLAGS) ../src/BinarySearchTree.cpp

HashTable.o: ../src/HashTable.cpp
	g++ $(FLAGS) ../src/HashTable.cpp

HashNode.o: ../src/HashNode.cpp
	g++ $(FLAGS) ../src/HashNode.cpp

BSTNode.o: ../src/BSTNode.cpp
	g++ $(FLAGS) ../src/BSTNode.cpp

clean:
	rm -rf *o main *~ ../sort.txt
