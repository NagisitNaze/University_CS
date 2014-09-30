#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <math.h>

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
    avlTree();
    ~avlTree();
    void destroyTree();
    int countNodes() const;
    int height() const;
    bool search(myType) const;
    void printTree(treeTraversalOptions) const;
    void insert(myType);
    void deleteNode(myType);
  private:
    void destroyTree(nodeType<myType> *);
    int countNodes(nodeType<myType> *);
    int height(nodeType<myType> *);
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
avlTree::avlTree()
{
  root = NULL;
}

template <class myType>
avlTree::~avlTree()
{
  destroyTree(root);
}

template <class myType>
void avlTree::destroyTree()
{
  destroyTree(root);
}

template <class myType>
int avlTree::countNodes() const
{
  return countNodes(root);
}

template <class myType>
int avlTree::height() const
{
  return height(root);
}

template <class myType>
bool avlTree::search(myType key) const
{
    return search(key, root) != NULL ? true : false;
}

template <class myType>
void avlTree::printTree(treeTraversalOptions options) const
{
  printTree(root, options);
}

template <class myType>
void avlTree::insert(myType nodeValue)
{
  insert(nodeValue, root);
}

template <class myType>
void avlTree::deleteNode(myType nodeValue)
{
  deleteNode(nodeValue, root);
}

template <class myType>
void avlTree::destroyTree(nodeType<myType> *node)
{
  if(node != NULL) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

template <class myType>
int avlTree::countNodes(nodeType<myType> *node)
{
  if(node == NULL)
    return 0;
  return countNodes(node->left) + 1;
  return countNodes(node->right) + 1;
}

template <class myType>
int avlTree::height(nodeType<myType> *node)
{
  if(node == NULL)
    return 0;

  // if tree is not empty height is 1 + max of either path
  return 1 + max(height(node->left), height(node->right));
}

template <class myType>
nodeType<myType> *avlTree::search(myType key, nodeType<myType> *node) const
{
  if(node == NULL)
    return NULL;
  if(key == node->keyValue)
    return node;
  else if(key > node->keyValue)
    return search(key, node->right);
  else if(key > node->keyValue)
    return search(key, node->left);
}

template <class myType>
void avlTree::printTree(nodeType<myType> *node, treeTraversalOptions options) const
{
  switch(options) {
    case INORDER:

    break;
    case PREORDER:

    break;
    case POSTORDER:

    break;
    case LEVELORDER:

    break;
    case NONE:

    break;
  }
}

template <class myType>
void avlTree::printGivenLevel(nodeType<myType> *node, int level) const
{
  if(node == NULL)
    return;

  if(node->nodeHeight == level) {
    std::cout << node->keyValue << " ";
  }

  printGivenLevel(node->right);
  printGivenLevel(node->left);
}

template <class myType>
nodeType<myType> *avlTree::insert(myType key, nodeType<myType> *node)
{
  if(node == NULL) {
    nodeType<myType> *newNode = new nodeType<myType>;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->keyValue = key;
    newNode->nodeHeight = 1;
    return newNode;
  }

  if(key < node->keyValue)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  //update height of node
  node->height = max(height(node->left), height(node->right)) + 1;

  //get balance factor of node to check wheather node became unbalanced
  int bal = getBalance(node);

  //right rotate needed
  if(bal > 1 && key < node->left->keyValue)
    return rightRotate(node);

  //left rotate needed
  if(bal < -1 && key > node->right->keyValue)
    return leftRotate(node);

  //left-right rotate needed
  if(bal > 1 && key > node->left->keyValue) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  //right-left rotate needed
  if(bal < -1 && key < node->right->keyValue) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

template <class myType>
nodeType<myType> *avlTree::leftRotate(nodeType<myType> * node)
{
  nodeType<myType> *oldnode = node;

  //perform rotation
  node = node->left;
  oldnode->left = node->right;
  node->right = oldnode;

  return node;
}

template <class myType>
nodeType<myType> *avlTree::rightRotate(nodeType<myType> *)
{
  nodeType<myType> *oldnode = node;

  node = node->right;
  oldnode->right = node->left;
  node->left = oldnode;

  return node;
}

template <class myType>
int avlTree::getBalance(nodeType<myType> *node) const
{
  if(node == NULL) {
    return 0;
  }
  int lh = height(node->left);
  int rh = height(node->right);

  return lh - rh;
}

template <class myType>
nodeType<myType> *avlTree::deleteNode(myType key, nodeType<myType> *node)
{
  if(node == NULL)
    return node;

  if(key < node->keyValue)
    node->left = deleteNode(node->left, key);
  else if(key > node->keyValue)
    node->right = deleteNode(node->right, key);
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
      node->right = deleteNode(node->right, temp->keyValue);
    }
  }

  if(node == NULL)
    return node;

  node->height = max(height(node->left), height(node->right)) + 1;

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
nodeType<myType> *avlTree::minValueNode(nodeType<myType> *node) const
{
  nodeType<myType> *curent = node;

  while(current->left != NULL)
    current = current->left;

  return current;
}

#endif
