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
  size = 1000;
  table = new HashNode*[size];
  for (int i = 0; i < size; i ++)
  {
    table[i] = new HashNode();
  }
}

HashTable::HashTable(int tableSize)
{
  size = tableSize;
  table = new HashNode*[size];
  for (int i = 0; i < size; i++)
  {
    table[i] = new HashNode();
  }
}

HashTable::~HashTable()
{
  for (int i = 0; i < size; i++)
  {
    if (table[i])
    {
      delete table[i];
    }
  }

  delete[] table;
}

int HashTable::hash(const std::string& key)
{
  unsigned int value = 0;
  for (unsigned int i = 0; i < key.length(); i++)
  {
    value = 171 * value + key[i];
  }

  return value % size;
}

void HashTable::insert(const std::string& key)
{
  HashNode* node;
  if((node = searchNode(key)))
  {
    node->value++;
  }
  else
  {
    insert(key, 1);
  }
}

void HashTable::insert(const std::string& key, int value)
{
  unsigned int hashVal = hash(key);

  while (table[hashVal]->key != " " &&
         table[hashVal]->key != "" &&
         table[hashVal]->key != key)
  {
    hashVal = (hashVal + 1) % size;
  }

  if (table[hashVal]->key != " " && table[hashVal]->key != "")
  {
    table[hashVal]->value++;
  }
  else
  {
    table[hashVal]->key = key;
    table[hashVal]->value = value;
  }


}

bool HashTable::search(const std::string& key)
{
  int hashVal = hash(key);
  int count = 0;

  while (table[hashVal]->key != " " &&
         table[hashVal]->key != key &&
         count != size)
  {
    count++;
    hashVal = (hashVal + 1) % size;
  }

  if (table[hashVal]->key == " " || count == size)
  {
    return false;
  }
  else
  {
    return true;
  }
}

HashNode* HashTable::searchNode(const std::string& key)
{
  int hashVal = hash(key);
  int count = 0;

  while (table[hashVal]->key != " " &&
         table[hashVal]->key != key &&
         count != size)
  {
    count++;
    hashVal = (hashVal + 1) % size;
  }

  if (table[hashVal]->key == " " || count == size)
  {
    return nullptr;
  }
  else
  {
    return table[hashVal];
  }
}

void HashTable::deleteKey(const std::string& key)
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
    {
      words.push_back(table[i]->key);
    }
  }

  std::sort(words.begin(), words.end());
  return words;
}

void HashTable::rangeSearch(const std::string& first, const std::string& last)
{
  for (int i = 0; i < size; i++)
  {
    if (table[i] && table[i]->key >= first && table[i]->key <= last)
    {
      std::cout << table[i]->key + "\n";
    }
  }
}
