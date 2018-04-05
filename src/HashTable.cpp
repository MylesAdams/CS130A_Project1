//
// Created by Myles Adams
//

#include "HashTable.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

const std::string SORT_OUTPUT_FILEPATH = "../sort.txt";

HashTable::HashTable()
{
    this->size = 1000;
    this->table = new HashNode*[size];
    for (int i = 0; i < size; i ++)
        this->table[i] = new HashNode();
}

HashTable::HashTable(int size)
{
    this->size = size;
    this->table = new HashNode*[size];
    for (int i = 0; i < size; i++)
        this->table[i] = new HashNode();
}

HashTable::~HashTable()
{
    for (int i = 0; i < this->size; i++)
        if (table[i])
            delete table[i];

    delete[] table;
}

int HashTable::hash(std::string key)
{
    unsigned int value = 0;
    for (int i = 0; i < key.length(); i++)
    {
        value = 171*value + key[i];
    }

    return value % size;
}

void HashTable::insert(std::string key)
{
    HashNode* node;
    if((node = searchNode(key)))
        node->value++;
    else
        insert(key, 1);
}

void HashTable::insert(std::string key, int value)
{
    unsigned int hashVal = hash(key);

    while (table[hashVal]->key != " " && table[hashVal]->key != "" && table[hashVal]->key != key)
    {
        hashVal = (hashVal + 1) % size;
    }

    if (table[hashVal]->key != " " && table[hashVal]->key != "")
    {
        std::string s = table[hashVal]->key;
        table[hashVal]->value++;
    }
    else
    {
        table[hashVal]->key = key;
        table[hashVal]->value = value;
    }


}


bool HashTable::search(std::string key)
{
    int hashVal = hash(key);
    int count = 0;

    while (table[hashVal]->key != " " && table[hashVal]->key != key && count != this->size)
    {
        count++;
        hashVal = (hashVal + 1) % size;
    }

    if (table[hashVal]->key == " " || count == this->size)
        return false;
    else
        return true;
}

HashNode* HashTable::searchNode(std::string key)
{
    int hashVal = hash(key);
    int count = 0;

    while (table[hashVal]->key != " " && table[hashVal]->key != key && count != this->size)
    {
        count++;
        hashVal = (hashVal + 1) % size;
    }

    if (table[hashVal]->key == " " || count == this->size)
        return nullptr;
    else
        return table[hashVal];
}

void HashTable::deleteKey(std::string key)
{
    HashNode* node;
    if ((node = searchNode(key)))
    {
        if (node->value == 1)
        {
            node->value--;
            node->key = "";
        }
        else
        {
            node->value--;
        }
    }
}

std::vector<std::string> HashTable::sort()
{
    std::vector<std::string> words;
    words.reserve(size);
    for (int i = 0; i < size; i++)
    {
        if (table[i]->key != "")
            words.push_back(table[i]->key);
    }

    std::sort(words.begin(), words.end());
    return words;
}

void HashTable::rangeSearch(std::string first, std::string last)
{
    for (int i = 0; i < size; i++)
        if (table[i])
            if (table[i]->key >= first && table[i]->key <= last)
                std::cout << table[i]->key + "\n";
}
