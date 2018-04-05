//
// Created by Myles Adams
//

#ifndef CS130A_PROJECT1_BINARYSEARCHTREE_H
#define CS130A_PROJECT1_BINARYSEARCHTREE_H

#include <string>
#include <fstream>
#include <vector>
#include "BSTNode.hpp"

class BinarySearchTree
{
public:

    // Default Constructor
    BinarySearchTree();

    // Destructor
    ~BinarySearchTree();

    // Return root of BST
    BSTNode* getRoot();

    // Search for word in BST, return bool
    bool searchWord(std::string word);

    // Insert word into BST
    void insertWord(std::string word);

    // Delete word from BST
    void deleteWord(std::string word);

    // Find the minimum value of a BST
    BSTNode* findMinimum(BSTNode* node);

    // Sort BST
    std::vector<std::string> sort();

    // Range Search BST
    void rangeSearch(std::string first, std::string last);

    // Put values of BST into vector in order
    void inOrder(BSTNode* root, std::vector<std::string>& vec);

    // Get count of number of words
    int getCount();


private:
    // Root of BST
    BSTNode* root;

    // Number of Nodes
    int count;

    // Recursive delete word from BST
    void deleteWord(BSTNode* &root, std::string word);

    // Recursive in order function to search for words in range
    void inOrderRange(BSTNode* root, std::string first, std::string last);

    // Serach for word in BST, return pointer to Node
    BSTNode* searchNode(std::string word);


};


#endif //CS130A_PROJECT1_BINARYSEARCHTREE_H
