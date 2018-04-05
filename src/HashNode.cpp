//
// Created by Myles Adams
//

#include "HashNode.hpp"

HashNode::HashNode(std::string key, int value)
{
    this->key = key;
    this->value = value;
}

HashNode::HashNode()
{
    // "Null" Node
    this->key = " ";

    // Default count
    this->value = 0;
}