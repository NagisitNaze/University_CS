#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <math.h>
#include <iostream>

template <class myType>
struct nodeType {
  myType keyValue;
  int nodeHeight;
  nodeType<myType> *left;
  nodeType<myType> *right;
};

enum treeTraversalOptions {
  INORDER,
  PREORDER,
  POSTORDER,
  LEVELORDER,
  NONE
};

template <class myType>
class avlTree {
  public:
    avlTree<myType>();
    ~avlTree<myType>();
    void destroyTree();
    int countNodes() const;
    int height() const;
    bool search(myType) const;
    void printTree(treeTraversalOptions) const;
    void insert(myType);
    void deleteNode(myType);
  private:
    void destroyTree(nodeType<myType> *&);
    int countNodes(nodeType<myType> *) const;
    int height(nodeType<myType> *) const;
    nodeType<myType> *search(myType, nodeType<myType> *) const;
    void printTree(nodeType<myType> *, treeTraversalOptions) const;
    void printGivenLevel(nodeType<myType> *, int) const;
    nodeType<myType> *insert(myType, nodeType<myType> *);
    nodeType<myType> *rightRotate(nodeType<myType> *);
    nodeType<myType> *leftRotate(nodeType<myType> *);
    int getBalance(nodeType<myType> *) const;
    nodeType<myType> *deleteNode(myType, nodeType<myType> *);
    nodeType<myType> *minValueNode(nodeType<myType> *) const;
    nodeType<myType> *root;
};

template <class myType>
avlTree<myType>::avlTree()
{
  root = NULL;
}

template <class myType>
avlTree<myType>::~avlTree<myType>()
{
  destroyTree(root);
}

template <class myType>
void avlTree<myType>::destroyTree()
{
  destroyTree(root);
  if(root == NULL)
    std::cout << "destroyed" << std::endl;
}

template <class myType>
int avlTree<myType>::countNodes() const
{
  return countNodes(root);
}

template <class myType>
int avlTree<myType>::height() const
{
  return height(root);
}

template <class myType>
bool avlTree<myType>::search(myType key) const
{
  nodeType<myType> *result = search(key, root);
  std::cout << std::endl << "searched ";
  if(result == NULL)
    return false;
  return true;
}

template <class myType>
void avlTree<myType>::printTree(treeTraversalOptions options) const
{
  printTree(root, options);
}

template <class myType>
void avlTree<myType>::insert(myType nodeValue)
{
  root = insert(nodeValue, root);
}

template <class myType>
void avlTree<myType>::deleteNode(myType nodeValue)
{
  deleteNode(nodeValue, root);
}

template <class myType>
void avlTree<myType>::destroyTree(nodeType<myType> *&node)
{
  if(node != NULL) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
  node = NULL;
}

template <class myType>
int avlTree<myType>::countNodes(nodeType<myType> *node) const
{
  if(node == NULL)
    return 0;
  return 1 + countNodes(node->left) + countNodes(node->right);
}

template <class myType>
int avlTree<myType>::height(nodeType<myType> *node) const
{
  if(node == NULL)
    return 0;

  // if tree is not empty height is 1 + max of either path
  return 1 + std::max(height(node->left), height(node->right));
}

template <class myType>
nodeType<myType> *avlTree<myType>::search(myType key, nodeType<myType> *node) const
{
  if(node == NULL)
    return NULL;
  else if(key < node->keyValue)
    return search(key, node->left);
  else if(key > node->keyValue)
    return search(key, node->right);
  else
    return node;
}

template <class myType>
void avlTree<myType>::printTree(nodeType<myType> *node, treeTraversalOptions options) const
{
  if(node == NULL)
    return;

  switch(options) {
    case INORDER:
       printTree(node->left, options);
       std::cout << node->keyValue << " ";
       printTree(node->right, options);
    break;
    case PREORDER:
      std::cout << node->keyValue << " ";
      printTree(node->left, options);
      printTree(node->right, options);
    break;
    case POSTORDER:
      printTree(node->left, options);
      printTree(node->right, options);
      std::cout << node->keyValue << " ";
    break;
    case LEVELORDER:
      for(int i = 1; i <=  height(node); i++) {
        printGivenLevel(node, i);

      }
    break;
    case NONE:
      return;
    break;
  }
}

template <class myType>
void avlTree<myType>::printGivenLevel(nodeType<myType> *node, int level) const
{
  if(node == NULL)
    return;

  if(level == 1)
    std::cout << node->keyValue << " ";
  else if(level > 1){
    printGivenLevel(node->left, level-1);
    printGivenLevel(node->right, level-1);
  }
}

template <class myType>
nodeType<myType> *avlTree<myType>::insert(myType key, nodeType<myType> *node)
{
  if(node == NULL) {
    nodeType<myType> *newNode = new nodeType<myType>;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->keyValue = key;
    newNode->nodeHeight = 0;
    return newNode;
  }

  if(key < node->keyValue)
    node->left = insert(key, node->left);
  else if(key > node->keyValue)
    node->right = insert(key, node->right);

  //update height of node
  node->nodeHeight = std::max(height(node->left), height(node->right)) + 1;

  //get balance factor of node to check wheather node became unbalanced
  int bal = getBalance(node);
  std::cout << "not cras";
  if(height(node->left) - height(node->right) > 1) {
    if(height(node->left->left) >= height(node->left->right)) {
      rightRotate(node);
    }else{
      leftRotate(node->right);
      rightRotate(node);
    }
  }else if(height(node->right) - height(node->left) > 1) {
    if(height(node->right->right) >= height(node->right->left)){
      leftRotate(node);
    }else{
      rightRotate(node->left);
      leftRotate(node);
    }

  }
  std::cout << "hed ";

  return node;
}

template <class myType>
nodeType<myType> *avlTree<myType>::leftRotate(nodeType<myType> *node)
{
  nodeType<myType> *otherNode;

  otherNode = node->left;
  node->left = otherNode->right;
  otherNode->right = node;
  node = otherNode;

  return node;
}

template <class myType>
nodeType<myType> *avlTree<myType>::rightRotate(nodeType<myType> *node)
{
  nodeType<myType> *otherNode;

  otherNode = node->right;
  node->right = otherNode->left;
  otherNode->left = node;
  node = otherNode;

  return node;
}

template <class myType>
int avlTree<myType>::getBalance(nodeType<myType> *node) const
{
  if(node == NULL) {
    return 0;
  }
  int lh = height(node->left);
  int rh = height(node->right);

  return lh - rh;
}

template <class myType>
nodeType<myType> *avlTree<myType>::deleteNode(myType key, nodeType<myType> *node)
{
  if(node == NULL)
    return node;

  if(key < node->keyValue)
    node->left = deleteNode(key, node->left);
  else if(key > node->keyValue)
    node->right = deleteNode(key, node->right);
  else{
    if( (node->left == NULL) || (node->right == NULL) ) {
      nodeType<myType> *temp = node->left == NULL ? node->left : node->right;

      if(temp == NULL) {
        temp = node;
        node = NULL;
      }else
        *node = *temp;

      delete temp;
    }else{
      nodeType<myType> *temp = minValueNode(node->right);
      node->keyValue = temp->keyValue;
      node->right = deleteNode(temp->keyValue, node->right);
    }
  }

  if(node == NULL)
    return node;

  node->nodeHeight = std::max(height(node->left), height(node->right)) + 1;

  int bal = getBalance(node);

    // Left Left Case
  if (bal > 1 && getBalance(node->left) >= 0)
      return rightRotate(node);

  // Left Right Case
  if (bal > 1 && getBalance(node->left) < 0) {
      node->left =  leftRotate(node->left);
      return rightRotate(node);
  }

  // Right Right Case
  if (bal < -1 && getBalance(node->right) <= 0)
      return leftRotate(node);

  // Right Left Case
  if (bal < -1 && getBalance(node->right) > 0) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
  }

  return node;
}

template <class myType>
nodeType<myType> *avlTree<myType>::minValueNode(nodeType<myType> *node) const
{
  nodeType<myType> *current = node;

  while(current->left != NULL)
    current = current->left;

  return current;
}

#endif
