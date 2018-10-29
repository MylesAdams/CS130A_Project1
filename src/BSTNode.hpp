//
// Created by Myles Adams
//

#ifndef CS130A_PROJECT1_BSTNODE_H
#define CS130A_PROJECT1_BSTNODE_H


#include <string>

class BSTNode
{
  public:
    // Word
    std::string data;

    // Count of word
    int count;

    // Left Child
    BSTNode* left;

    // Right Child
    BSTNode* right;

    // Default Constructor
    BSTNode();

    // Constructor given word
    BSTNode(std::string word);

    // Destructor
    ~BSTNode();

};




#endif //CS130A_PROJECT1_BSTNODE_H
