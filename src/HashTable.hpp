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
    HashNode* searchNode(const std::string& key);

  public:

    // Array of pointers to HashNodes
    HashNode** table;

    // Default Constructor
    HashTable();

    // Constructor given size
    HashTable(int tableSize);

    // Destructor
    ~HashTable();

    // Hash function
    int hash(const std::string& key);

    // Insert key into Hash Table
    void insert(const std::string& key);

    // Insert key, value into Hash Table
    void insert(const std::string& key, int value);

    // Search Hash Table for word
    bool search(const std::string& key);

    // Delete word from Hash Table
    void deleteKey(const std::string& key);

    // Sort Hash Table and return vector of strings
    std::vector<std::string> sort();

    // Range Search Hash Table
    void rangeSearch(const std::string& first, const std::string& last);
};


#endif //CS130A_PROJECT1_HASHTABLE_HPP
