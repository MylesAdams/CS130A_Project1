//
// Created by Myles Adams
//

#ifndef CS130A_PROJECT1_HASHNODE_HPP
#define CS130A_PROJECT1_HASHNODE_HPP

#include <string>

class HashNode
{
public:
    // Word
    std::string key;

    // Count of word
    int value;

    // Default Constructor
    HashNode();

    // Constructor given key, value
    HashNode(std::string key, int value);

};


#endif //CS130A_PROJECT1_HASHNODE_HPP
