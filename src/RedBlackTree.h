#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include <vector>

using namespace std;

class RedBlackTree {
public:
  node* root;
  node* toAdd;

  RedBlackTree(node* inRoot) {
    root = inRoot;
  }

  RedBlackTree() {
    root = NULL;
    toAdd = NULL;
  }

  void fix(node*& toEnter);

  void leftRotate(node*& toRotate);

  void rightRotate(node*& toRotate);

  void remove();

  void inOrderTraversal(vector<node*>* order, node* cur_root);

  vector<node*>* getInOrderTraversal(node* inRoot);

  void add(int key);

};

#endif
