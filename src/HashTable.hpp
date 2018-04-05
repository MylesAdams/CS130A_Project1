//
// Created by Myles Adams
//

#ifndef CS130A_PROJECT1_HASHTABLE_HPP
#define CS130A_PROJECT1_HASHTABLE_HPP

#include "HashNode.hpp"
#include <vector>

class HashTable
{
private:

    // Size of HashTable
    int size;

    // Search for word and return node
    HashNode* searchNode(std::string key);

public:

    // Array of pointers to HashNodes
    HashNode** table;

    // Default Constructor
    HashTable();

    // Constructor given size
    HashTable(int size);

    // Destructor
    ~HashTable();

    // Hash function
    int hash(std::string key);

    // Insert key into Hash Table
    void insert(std::string key);

    // Insert key, value into Hash Table
    void insert(std::string key, int value);

    // Search Hash Table for word
    bool search(std::string key);

    // Delete word from Hash Table
    void deleteKey(std::string key);

    // Sort Hash Table and return vector of strings
    std::vector<std::string> sort();

    // Range Search Hash Table
    void rangeSearch(std::string first, std::string last);
};


#endif //CS130A_PROJECT1_HASHTABLE_HPP
