//
// Created by Myles Adams
//

#include "BSTNode.hpp"

BSTNode::BSTNode(std::string word)
{
  data = word;
  count = 1;
  left = nullptr;
  right = nullptr;
}

BSTNode::~BSTNode()
{
  delete right;
  delete left;
}
