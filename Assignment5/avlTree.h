#ifndef AVLTREE_H_
#define AVLTREE_H_

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
    void countNodes(nodeType<myType> *);
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

avlTree::avlTree()
{

}

avlTree::~avlTree()
{

}

void avlTree::destroyTree()
{

}

int avlTree::countNodes() const
{

}

int avlTree::height() const
{

}

bool avlTree::search(myType) const
{

}

void avlTree::printTree(treeTraversalOptions) const
{

}

void avlTree::insert(myType)
{

}

void avlTree::deleteNode(myType)
{

}

void avlTree::destroyTree(nodeType<myType> *)
{

}

void avlTree::countNodes(nodeType<myType> *)
{

}

int avlTree::height(nodeType<myType> *)
{

}

nodeType<myType> *avlTree::search(myType, nodeType<myType> *) const
{

}

void avlTree::printTree(nodeType<myType> *, treeTraversalOptions) const
{

}

void avlTree::printGivenLevel(nodeType<myType> *, int) const
{

}

nodeType<myType> *avlTree::insert(myType, nodeType<myType> *)
{

}

nodeType<myType> *avlTree::rightRotate(nodeType<myType> *)
{

}

nodeType<myType> *avlTree::leftRotate(nodeType<myType> *)
{

}

int avlTree::getBalance(nodeType<myType> *) const
{

}

nodeType<myType> *avlTree::deleteNode(myType, nodeType<myType> *)
{

}

nodeType<myType> *avlTree::minValueNode(nodeType<myType> *) const
{

}

#endif
