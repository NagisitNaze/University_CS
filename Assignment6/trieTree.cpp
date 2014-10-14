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

}

bool trieTree::isPrefix(std::string word) const
{

}

void trieTree::printTree() const
{

}

void trieTree:destoryTree()
{

}

int trieTree::countNodes(trieNodeType *node) const
{

}

int trieTree::height(trieNodeType *node) const
{

}

void trieTree::destoryTree(trieNodeType *node)
{

}

void trieTree::printTree(trieNodeType *node) const
{
  printTree(root);
}
