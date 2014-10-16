#include "trieTree.h"

trieTree::trieTree()
{
  root = NULL;
}

trieTree::~trieTree()
{
  destoryTree();
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
    node->endWordMark = false;
    for (int i = 0; i < 26; i++)
      node->children[i] = NULL;
    root == node;
  }else{
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
        trieNodeType->keyValue = currentChar;
        trieNodeType->children[index] = newNode;
        for (int i = 0; i < 26; i++)
          newNode->children[i] == NULL;
        //assign node to newNode
        node = newNode;
      }
      if( i == word.size() - 1) {
        //word is finished
        currentNode->endWordMark = true;
      }
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

void trieTree::destoryTree()
{
  destoryTree(root);
}

int trieTree::countNodes(trieNodeType *node) const
{
  if(node == NULL)
    return 0;
  for(int i = 0; i < 26; i++)
    return 1 + countNodes(node->children[i]);
}

int trieTree::height(trieNodeType *node) const
{
  if(node == NULL)
    return 0;

  return 1 +
}

void trieTree::destoryTree(trieNodeType *&node)
{
  if(node != NULL) {
    for(int i = 0; i < 26; i++) {
      destoryTree(node->children[i]);
      delete node;
    }
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
