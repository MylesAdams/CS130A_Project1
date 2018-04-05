//
// Created by Myles Adams
//

#include "BSTNode.hpp"

BSTNode::BSTNode(std::string word)
{
    this->data = word;
    this->count = 1;
    this->left = nullptr;
    this->right = nullptr;
}

BSTNode::~BSTNode()
{
    delete right;
    delete left;
}