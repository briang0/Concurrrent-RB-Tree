#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include <vector>

using namespace std;

class RedBlackTree {
public:
  node* root;
  node* nil;

  RedBlackTree(node* inRoot) {
    root = inRoot;
    nil = new node(-1, nullptr, nullptr, nullptr);
  }

  RedBlackTree() {
    root = NULL;
  }

  node* insertHelper(node*& root, node*& toInsert);

  void insert(node*& toInsert);

  void insertKey(int key);

  void fix(node* toEnter);

  void leftRotate(node* toRotate);

  void rightRotate(node* toRotate);

  void remove();

  void inOrderTraversal(vector<node*>* order, node* cur_root);

  vector<node*>* getInOrderTraversal(node* inRoot);

  void add(int key);

  node* getRoot();

};

#endif
