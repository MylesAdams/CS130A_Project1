//
// Created by Myles Adams
//

#include "HashNode.hpp"

HashNode::HashNode(std::string nodeKey, int nodeValue)
{
  key = nodeKey;
  value = nodeValue;
}

HashNode::HashNode()
{
  // "Null" Node
  key = " ";

  // Default count
  value = 0;
}
