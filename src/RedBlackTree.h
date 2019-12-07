#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include <vector>

using namespace std;

class RedBlackTree {
public:
  node* root;

  RedBlackTree(node* inRoot) {
    root = inRoot;
  }

  RedBlackTree() {
    root = NULL;
  }

  void fix(node*& z);

  void leftRotate(node*& toRotate);

  void rightRotate(node*& toRotate);

  void remove(int key);

  void transplant(node* u, node* v);

  void preorder(node* head);

  void inOrderTraversal(vector<node*>* order, node* cur_root);

  vector<node*>* getInOrderTraversal(node* inRoot);

  node* btAdd(node* r, node* n);

  void add(int key);

  node* searchHelper(int key, node* head);

  int search(int key);

};

#endif
