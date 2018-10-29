//
// Created by Myles Adams
//

#include <iostream>
#include "BinarySearchTree.hpp"
#include "HashTable.hpp"
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <chrono>

const std::string SORT_OUTPUT_FILEPATH = "../sort.txt";

const std::string TEST_OUTPUT = "../test_output.txt";

const std::string DATA_PATH = "../hotels-small/";

const double NANO = 1000000000.0;

// 100 words for testing
const std::vector<std::string> wordsToTest = {"hello", "omg", "zip", "first", "for", "from", "get", "give", "go", "have",
                                              "he",
                                              "her", "here", "asd", "aa-", "soccer", "pie", "ability", "babypool",
                                              "breaker",
                                              "ppood", "what", "joke", "cause", "cats", "cattle", "dog", "abbababababba",
                                              "clijpc",
                                              "poq", "asd,,''", "pier", "but", "why", "so", "joke", "peach", "iijasd",
                                              "i", "iuy",
                                              ".,.,", "but", "can't", "dollar", "dome", "everyone-", "everynight",
                                              "everywhere",
                                              "bye", "goodnight", "pui", "guise", "guitar", "pony", "qwer", "pool",
                                              "night",
                                              "children", "sid", "oasdo", "ododod", "yuyuuyuy", "iuqweu", "hdhdhdh",
                                              "giant",
                                              "lkasdjh", "0123", ",z,z,z,", "please", "thank-you", "seven", "guidebook",
                                              "pieme", "guests'", "guite", "gulou", "akjshdjkhas", "wjnasjd", "higher",
                                              "high", "hub", "induce", "infact", "lol", "old", "young", "zen", "zone",
                                              "zoning", "zoo", "///asd", "iu", "worn", "world", "worries", "mild", "zzzz",
                                              "wost", "workman", "nine"};

std::vector<std::string> open(std::string path);
void buildHashTableFromBST(HashTable* hashtable, BSTNode* node);
HashTable* buildHashTableFromBST(BinarySearchTree* bst);
void testAll(BinarySearchTree*& bst, HashTable*& ht);
void testBSTSearch(BinarySearchTree*& bst, std::ofstream& output);
void testBSTInsert(BinarySearchTree*& bst, std::ofstream& output);
void testBSTDelete(BinarySearchTree*& bst, std::ofstream& output);
void testBSTSort(BinarySearchTree*& bst, std::ofstream& output);
void testBSTRangeSearch(BinarySearchTree*& bst, std::ofstream& output);
void testHashSearch(HashTable*& ht, std::ofstream& output);
void testHashInsert(HashTable*& ht, std::ofstream& output);
void testHashDelete(HashTable*& ht, std::ofstream& output);
void testHashSort(HashTable*& ht, std::ofstream& output);
void testHashRangeSearch(HashTable*& ht, std::ofstream& output);

int main()
{

  BinarySearchTree* bst = new BinarySearchTree();

  // Vectors of all filenames
  std::vector<std::string> beijingFiles = open(DATA_PATH + "beijing");
  std::vector<std::string> chicagoFiles = open(DATA_PATH + "chicago");
  std::vector<std::string> dubaiFiles = open(DATA_PATH + "dubai");
  std::vector<std::string> lasvegasFiles = open(DATA_PATH + "las-vegas");
  std::vector<std::string> londonFiles = open(DATA_PATH + "london");
  std::vector<std::string> montrealFiles = open(DATA_PATH + "montreal");
  std::vector<std::string> newdelhiFiles = open(DATA_PATH + "new-delhi");
  std::vector<std::string> nycFiles = open(DATA_PATH + "new-york-city");
  std::vector<std::string> sfFiles = open(DATA_PATH + "san-francisco");
  std::vector<std::string> shanghaiFiles = open(DATA_PATH + "shanghai");

  // Vector of groupings of all files
  std::vector<std::vector<std::string> > allFiles;
  allFiles.push_back(beijingFiles);
  allFiles.push_back(chicagoFiles);
  allFiles.push_back(dubaiFiles);
  allFiles.push_back(lasvegasFiles);
  allFiles.push_back(londonFiles);
  allFiles.push_back(montrealFiles);
  allFiles.push_back(newdelhiFiles);
  allFiles.push_back(nycFiles);
  allFiles.push_back(sfFiles);
  allFiles.push_back(shanghaiFiles);

  // Vector of all folder names
  std::vector<std::string> folderNames;
  folderNames.push_back("beijing/");
  folderNames.push_back("chicago/");
  folderNames.push_back("dubai/");
  folderNames.push_back("las-vegas/");
  folderNames.push_back("london/");
  folderNames.push_back("montreal/");
  folderNames.push_back("new-delhi/");
  folderNames.push_back("new-york-city/");
  folderNames.push_back("san-francisco/");
  folderNames.push_back("shanghai/");

  // Array of all stop words
  std::string stopwords[127] = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours",
                                "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers",
                                "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves",
                                "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are",
                                "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does",
                                "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until",
                                "while", "of", "at", "by", "for", "with", "about", "against", "between", "into",
                                "through", "during", "before", "after", "above", "below", "to", "from", "up", "down",
                                "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here",
                                "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more",
                                "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so",
                                "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"};

  // Put stop words into hash table
  HashTable* stopwordsHash = new HashTable(127);
  for (int i = 0; i < 127; i++)
  {
    stopwordsHash->insert(stopwords[i]);
  }

  // Prepare regex
  std::string rgxWord;
  std::string word;
  std::regex rgx("[a-z]+[a-z_'-]*");

  // Go through all files and build BST from unique words
  for (unsigned int i = 0; i < allFiles.size(); i++)
  {
    for (unsigned int j = 2; j < allFiles[i].size(); j++)
    {
      std::ifstream file;
      file.open(DATA_PATH + folderNames[i] + allFiles[i][j]);
      while (file >> rgxWord)
      {
        std::transform(rgxWord.begin(), rgxWord.end(), rgxWord.begin(), ::tolower);
        for (std::sregex_iterator iter(rgxWord.begin(), rgxWord.end(), rgx), it_end; iter != it_end; iter++)
        {
          word = iter->str();
          if (!(stopwordsHash->search(word)))
          {
            bst->insertWord(word);
          }
        }
      }
    }
  }

  // Build Hash table from BST
  HashTable* hashTable = buildHashTableFromBST(bst);


  auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
  int choice;
  std::string startWord, endWord;
  double seconds;
  double secondsHash;
  std::ofstream sortFile;
  std::vector<std::string> bstSorted, hashSorted;

  // Format cout
  std::cout.precision(17);
  std::cout << std::boolalpha;

  /* Uncomment the line below to test program and write timings to ../test_output.txt */
  // testAll(bst, hashTable);

  // Command Line user interface
  while (true)
  {
    std::cout << "Enter a number to execute an action.\n1 (search), 2 (insert), 3 (delete), 4 (sort), 5 (range search).\n";
    std::cin >> choice;

    while (!std::cin || choice < 1 || choice > 5)
    {
      std::cin.clear();
      std::cin.ignore(512, '\n');
      std::cout << "Invalid entry.\n";
      std::cout << "Enter a number to execute an action.\n1 (search), 2 (insert), 3 (delete), 4 (sort), 5 (range search).\n";
      std::cin >> choice;
    }

    switch (choice)
    {
      case 1:
        std::cout << "Enter word to search:\n";
        std::cin >> word;
        bool found;

        start = std::chrono::high_resolution_clock::now();
        found = bst->searchWord(word);
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        seconds = ns / NANO;
        std::cout << found << std::endl;
        std::cout << std::fixed << "BST: " << seconds << " s" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        found = hashTable->search(word);
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        seconds = ns / NANO;
        std::cout << std::fixed << "Hash: " << seconds << " s\n" << std::endl;
        break;

      case 2:
        std::cout << "Enter word to insert:\n";
        std::cin >> word;

        start = std::chrono::high_resolution_clock::now();
        bst->insertWord(word);
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        seconds = ns / NANO;
        std::cout << std::fixed << "BST: " << seconds << " s" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        hashTable->insert(word);
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        seconds = ns / NANO;
        std::cout << std::fixed << "Hash: " << seconds << " s\n" << std::endl;
        break;

      case 3:
        std::cout << "Enter word to delete:\n";
        std::cin >> word;

        start = std::chrono::high_resolution_clock::now();
        bst->deleteWord(word);
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        seconds = ns / NANO;
        std::cout << "BST: " << std::fixed << seconds << " s" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        hashTable->deleteKey(word);
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        seconds = ns / NANO;
        std::cout << std::fixed << "Hash: " << seconds << " s\n" << std::endl;
        break;

      case 4:
        std::cout << SORT_OUTPUT_FILEPATH << std::endl;

        start = std::chrono::high_resolution_clock::now();
        bstSorted = bst->sort();
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        seconds = ns / NANO;
        std::cout << "BST: " << std::fixed << seconds << " s" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        hashSorted = hashTable->sort();
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        seconds = ns / NANO;
        std::cout << "Hash: " << std::fixed << seconds << " s\n" << std::endl;

        sortFile.open(SORT_OUTPUT_FILEPATH);
        for (auto word : bstSorted)
        {
          sortFile << word + "\n";
        }
        sortFile << "\n";
        for (auto word : hashSorted)
        {
          if (word != "" && word != " ")
          {
            sortFile << word + "\n";
          }
        }
        sortFile.close();
        break;

      case 5:
        std::cout << "Enter the start word\n";
        std::cin >> startWord;
        std::cout << "Enter the end word\n";
        std::cin >> endWord;

        start = std::chrono::high_resolution_clock::now();
        bst->rangeSearch(startWord, endWord);
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        seconds = ns / NANO;

        std::cout << std::endl;

        start = std::chrono::high_resolution_clock::now();
        hashTable->rangeSearch(startWord, endWord);
        end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        secondsHash = ns / NANO;
        std::cout << "\nBST: " << std::fixed << seconds << " s" << std::endl;
        std::cout << "Hash: " << std::fixed << secondsHash << " s\n" << std::endl;
        break;

      default:
        break;
    }
  }
}

// Find files and return vector of strings
std::vector<std::string> open(std::string path = ".")
{
  DIR* dir;
  dirent* pdir;
  std::vector<std::string> files;

  dir = opendir(path.c_str());

  while ((pdir = readdir(dir)))
    files.push_back(pdir->d_name);

  return files;
}

// Build a Hash Table given a BST
HashTable* buildHashTableFromBST(BinarySearchTree* bst)
{
  int size = 3 * bst->getCount() * .5;
  HashTable* hashtable = new HashTable(size);
  BSTNode* node = bst->getRoot();
  buildHashTableFromBST(hashtable, node);
  return hashtable;
}

// Recursive build Hash Table from BST
void buildHashTableFromBST(HashTable* hashtable, BSTNode* node)
{
  if (node == nullptr)
  {
    return;
  }

  buildHashTableFromBST(hashtable, node->left);
  hashtable->insert(node->data, node->count);
  buildHashTableFromBST(hashtable, node->right);
}

// Test all functionality of BST and Hash Table
void testAll(BinarySearchTree*& bst, HashTable*& ht)
{
  std::ofstream testOutput;
  testOutput.open(TEST_OUTPUT);

  testBSTSearch(bst, testOutput);
  testBSTInsert(bst, testOutput);
  testBSTDelete(bst, testOutput);
  testBSTSort(bst, testOutput);
  testBSTRangeSearch(bst, testOutput);

  testHashSearch(ht, testOutput);
  testHashInsert(ht, testOutput);
  testHashDelete(ht, testOutput);
  testHashSort(ht, testOutput);
  testHashRangeSearch(ht, testOutput);

  testOutput.close();
}

// Test BST Search
void testBSTSearch(BinarySearchTree*& bst, std::ofstream& output)
{
  auto start = std::chrono::high_resolution_clock::now();

  for (const std::string word : wordsToTest)
    bst->searchWord(word);

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "BST Search (100 words): ";
  output << ns / NANO;
  output << "\n\n";
}

// Test BST Insert
void testBSTInsert(BinarySearchTree*& bst, std::ofstream& output)
{
  auto start = std::chrono::high_resolution_clock::now();

  for (const std::string word : wordsToTest)
    bst->insertWord(word);

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "BST Insert (100 words): ";
  output << ns / NANO;
  output << "\n\n";
}

// Test BST Delete
void testBSTDelete(BinarySearchTree*& bst, std::ofstream& output)
{
  auto start = std::chrono::high_resolution_clock::now();

  for (const std::string word : wordsToTest)
    bst->deleteWord(word);

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "BST Delete (100 words): ";
  output << ns / NANO;
  output << "\n\n";
}

// Test BST Sort
void testBSTSort(BinarySearchTree*& bst, std::ofstream& output)
{
  auto start = std::chrono::high_resolution_clock::now();

  bst->sort();

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "BST Sort (all words): ";
  output << ns / NANO;
  output << "\n\n";
}

// Test BST Range Search
void testBSTRangeSearch(BinarySearchTree*& bst, std::ofstream& output)
{
  auto start = std::chrono::high_resolution_clock::now();

  bst->rangeSearch("a-", "abad");

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "BST Range Search (10 words): ";
  output << ns / NANO;
  output << "\n\n";

  start = std::chrono::high_resolution_clock::now();

  bst->rangeSearch("a-", "accomodating");

  end = std::chrono::high_resolution_clock::now();
  dur = end - start;
  ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "BST Range Search (100 words): ";
  output << ns / NANO;
  output << "\n\n";

  start = std::chrono::high_resolution_clock::now();

  bst->rangeSearch("a-", "astetics");

  end = std::chrono::high_resolution_clock::now();
  dur = end - start;
  ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "BST Range Search (1000 words): ";
  output << ns / NANO;
  output << "\n\n";
}

// Test Hash Table Search
void testHashSearch(HashTable*& ht, std::ofstream& output)
{
  auto start = std::chrono::high_resolution_clock::now();

  for (const std::string word : wordsToTest)
    ht->search(word);

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "Hash Search (100 words): ";
  output << ns / NANO;
  output << "\n\n";
}

// Test Hash Table Insert
void testHashInsert(HashTable*& ht, std::ofstream& output)
{
  auto start = std::chrono::high_resolution_clock::now();

  for (const std::string word : wordsToTest)
    ht->insert(word);

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "Hash Insert (100 words): ";
  output << ns / NANO;
  output << "\n\n";
}

// Test Hash Table Delete
void testHashDelete(HashTable*& ht, std::ofstream& output)
{
  auto start = std::chrono::high_resolution_clock::now();

  for (const std::string word : wordsToTest)
    ht->deleteKey(word);

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "Hash Delete (100 words): ";
  output << ns / NANO;
  output << "\n\n";
}

// Test Hash Table Sort
void testHashSort(HashTable*& ht, std::ofstream& output)
{
  auto start = std::chrono::high_resolution_clock::now();

  ht->sort();

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "Hash Sort (all words): ";
  output << ns / NANO;
  output << "\n\n";
}

// Test Hash Table Range Search
void testHashRangeSearch(HashTable*& ht, std::ofstream& output)
{
  auto start = std::chrono::high_resolution_clock::now();

  ht->rangeSearch("a-", "abad");

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - start;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "Hash Range Search (10 words): ";
  output << ns / NANO;
  output << "\n\n";

  start = std::chrono::high_resolution_clock::now();

  ht->rangeSearch("a-", "accomodating");

  end = std::chrono::high_resolution_clock::now();
  dur = end - start;
  ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "Hash Range Search (100 words): ";
  output << ns / NANO;
  output << "\n\n";

  start = std::chrono::high_resolution_clock::now();

  ht->rangeSearch("a-", "astetics");

  end = std::chrono::high_resolution_clock::now();
  dur = end - start;
  ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

  output << "Hash Range Search (1000 words): ";
  output << ns / NANO;
  output << "\n\n";
}
