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

  void insert();

  void remove();

  void balance();

  void inOrderTraversal(vector<node*>* order, node* cur_root);

  vector<node*>* getInOrderTraversal(node* inRoot);

  node* getRoot();

};

#endif
