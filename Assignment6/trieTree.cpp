#include <iostream>
#include "trieTree.h"

trieTree::trieTree()
{
  root = NULL;
}

trieTree::~trieTree()
{
  destroyTree();
}

int trieTree::countNodes() const
{
  return countNodes(root);
}

int trieTree::height() const
{
  return height(root);
}

void trieTree::insert(std::string word)
{
  if(root == NULL) {
    trieNodeType *node = new trieNodeType;
    node->endWordMark = true;
    node->keyValue = '-';
    for (int i = 0; i < 26; i++)
      node->children[i] = NULL;
    root = node;
  }

  //create node for traversal
  trieNodeType *node = root;
  //loop through word
  for(int i=0; i < word.size(); i++) {
    //declare the current char and create index
    char currentChar = word[i];
    int index = currentChar - 'a';

    //if a child exists alread
    if(node->children[index] != NULL) {
      node = node->children[index];
    }else{
      //current doesnt have char, create new one
      trieNodeType *newNode = new trieNodeType;
      newNode->keyValue = currentChar;
      for (int i = 0; i < 26; i++)
        newNode->children[i] = NULL;
      node->children[index] = newNode;
      //assign node to newNode
      node = newNode;
    }
    if( i == word.size() - 1) {
      //word is finished
      node->endWordMark = true;
    }
  }
}

bool trieTree::search(std::string word) const
{
  trieNodeType *current = root;

  while(current != NULL) {
    for( int i = 0; i < word.length(); i++) {
      int index = word[i] - 'a';
      if(current->children[index] == NULL)
        return false;
      current = current->children[index];
    }

    if( current->endWordMark )
      return true;
    else
      return false;
  }
}

bool trieTree::isPrefix(std::string word) const
{
  trieNodeType *current = root;

  while(current != NULL) {
    for(int i = 0; i < word.length(); i++) {
      int index = word[i] - 'a';
      if(current->children[index] == NULL)
        return false;
      current = current->children[index];
    }

    if(current->keyValue == word[word.length()-1])
      return true;
    else
      return false;
  }
}

void trieTree::printTree() const
{
  printTree(root);
}

void trieTree::destroyTree()
{
  destroyTree(root);
}

int trieTree::countNodes(trieNodeType *node) const
{
  if(node == NULL)
    return 0;

  trieNodeType ** i = node->children;
  trieNodeType ** end = i + 26;

  int nodeCount = countNodes(*(i++));

  while(i != end) {
    nodeCount += countNodes(*(i++));
  }

  return 1 + nodeCount;
}

int trieTree::height(trieNodeType *node) const
{
  if(node == NULL)
    return 0;

  trieNodeType ** i = node->children;
  trieNodeType ** end = i + (sizeof(node->children) / sizeof(trieNodeType *));

  int max_height = height(*(i++));

  while(i != end) {
    max_height = std::max(max_height, height(*(i++)));
  }

  return 1 + max_height;
}

void trieTree::destroyTree(trieNodeType *&node)
{
  if(node != NULL) {
    for(int i = 0; i < 26; i++) {
      destroyTree(node->children[i]);
    }
    delete node;
  }
  node = NULL;
}

void trieTree::printTree(trieNodeType *node) const
{
  if(node == NULL)
    return;

  std::cout << node->keyValue << " ";
  for(int i = 0; i < 26; i++) {
    printTree(node->children[i]);
  }
}
