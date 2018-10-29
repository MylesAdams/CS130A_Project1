//
// Created by Myles Adams
//

#include "BinarySearchTree.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

const std::string SORT_OUTPUT_FILEPATH = "../sort.txt";

BinarySearchTree::BinarySearchTree()
{
  root = nullptr;
  count = 0;
}

BinarySearchTree::~BinarySearchTree()
{
  delete root;
}

BSTNode* BinarySearchTree::getRoot()
{
  return root;
}

bool BinarySearchTree::searchWord(const std::string& word)
{
  BSTNode* cur;

  if (root == nullptr)
  {
    return false;
  }
  else
  {
    cur = root;
    int comp;
    while(cur != nullptr)
    {
      if ((comp = word.compare(cur->data)) == 0)
      {
        return true;
      }
      else if (comp < 0)
      {
        cur = cur->left;
      }
      else
      {
        cur = cur->right;
      }
    }
    return false;
  }
}

BSTNode* BinarySearchTree::searchNode(const std::string& word)
{
  BSTNode* cur;

  if (root == nullptr)
  {
    return nullptr;
  }
  else
  {
    cur = root;
    int comp;
    while(cur != nullptr)
    {
      if ((comp = word.compare(cur->data)) == 0)
      {
        return cur;
      }
      else if (comp < 0)
      {
        cur = cur->left;
      }
      else
      {
        cur = cur->right;
      }
    }
    return nullptr;
  }
}

void BinarySearchTree::insertWord(const std::string& word)
{
  BSTNode *cur, *parent;

  if ((cur = searchNode(word)))
  {
    cur->count++;
  }
  else {
    if (root == nullptr)
    {
      root = new BSTNode(word);
      count++;
    }
    else
    {
      cur = root;
      while (cur != nullptr)
      {
        if (word < cur->data)
        {
          parent = cur;
          cur = cur->left;
        }
        else
        {
          parent = cur;
          cur = cur->right;
        }
      }
      if (word < parent->data)
      {
        parent->left = new BSTNode(word);
        count++;
      }
      else
      {
        parent->right = new BSTNode(word);
        count++;
      }
    }
  }
}

void BinarySearchTree::deleteWord(std::string word)
{
  std::transform(word.begin(), word.end(), word.begin(),(int (*)(int))tolower);

  deleteWord(root, word);
}

void BinarySearchTree::deleteWord(BSTNode*& root, const std::string& word)
{
  BSTNode *cur, *parent;
  if ((cur = searchNode(word)))
  {
    if (cur->count == 1)
    {
      cur = root;
      while (cur != nullptr)
      {
        if (word == cur->data)
        {
          break;
        }
        else if (word < cur->data)
        {
          parent = cur;
          cur = cur->left;
        }
        else
        {
          parent = cur;
          cur = cur->right;
        }
      }

      if (cur->left == nullptr && cur->right == nullptr)
      {
        if (cur != root)
        {
          if (parent->left == cur)
            parent->left = nullptr;
          else
            parent->right = nullptr;
        }
        else {
          root = nullptr;
        }

        delete cur;
        count--;
      }
      else if (cur->left != nullptr && cur->right != nullptr)
      {
        BSTNode* rSubMin = findMinimum(cur->right);

        std::string newData = rSubMin->data;
        int newCount = rSubMin->count;

        deleteWord(cur, newData);

        cur->data = newData;
        cur->count = newCount;
      }
      else
      {
        BSTNode* child = (cur->left)? cur->left: cur->right;

        if (cur != root)
        {
          if (cur == parent->left)
            parent->left = child;
          else
            parent->right = child;
        }
        else
        {
          root = child;
        }

        cur->left = nullptr;
        cur->right = nullptr;

        delete cur;
        count--;

      }
    }
    else
    {
      cur->count--;
    }
  }

}

BSTNode* BinarySearchTree::findMinimum(BSTNode* node)
{
  while (node->left != nullptr)
  {
    node = node->left;
  }

  return node;
}

std::vector<std::string> BinarySearchTree::sort()
{
  std::vector<std::string> sortedWords;
  inOrder(root, sortedWords);
  return sortedWords;
}

void BinarySearchTree::rangeSearch(const std::string& first, const std::string& last)
{
  inOrderRange(root, first, last);
}

void BinarySearchTree::inOrderRange(BSTNode* root, const std::string& first, const std::string& last)
{
  if (root == nullptr)
  {
    return;
  }

  inOrderRange(root->left, first, last);
  if (root->data >= first && root->data <= last)
  {
    std::cout << root->data << std::endl;
  }
  inOrderRange(root->right, first, last);
}


void BinarySearchTree::inOrder(BSTNode* root, std::vector<std::string>& vec)
{
  if (root == nullptr)
  {
    return;
  }
  else
  {
    inOrder(root->left, vec);
    vec.push_back(root->data);
    inOrder(root->right, vec);
  }
}

int BinarySearchTree::getCount()
{
  return count;
}
