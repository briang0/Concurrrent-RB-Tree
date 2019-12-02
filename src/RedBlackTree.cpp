#include <stdio.h>
#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;

node* nil = new node(-1, NULL, NULL, NULL);

class RedBlackTree {
public:
  node* root;

  RedBlackTree(node* inRoot) {
    root = inRoot;
  }

  RedBlackTree() {
    root = NULL;
  }

  node* insertHelper(node*& root, node*& toInsert);

  void insert(node*& toInsert);

  void insertKey(int key);

  void fix(node *toEnter);

  void leftRotate(node *toRotate);

  void rightRotate(node *toRotate);

  void remove();

  void inOrderTraversal(vector<node*>* order, node* cur_root);

  vector<node*>* getInOrderTraversal(node* inRoot);

  void add(int key);

  node* getRoot();

};

void RedBlackTree::inOrderTraversal(vector<node*>* order, node* cur_root) {
  if (cur_root == NULL) {
    return;
  }
  inOrderTraversal(order, cur_root->left);
  order->push_back(cur_root);
  cout << cur_root->key << ", ";
  cout << cur_root->color << "\n";
  inOrderTraversal(order, cur_root->right);
}

vector<node*>* RedBlackTree::getInOrderTraversal(node* inRoot) {
  vector<node*>* order = new vector<node*>();
  inOrderTraversal(order, inRoot);
  return order;
}

// void add(int val) {
//   bool exists = false;
//   node* cur = root;
//   while (!cur.isLeaf() && !found) {
//     if (cur->key == val) {
//       found = !found;
//     }else if (val > cur->key) {
//       cur = cur->right;
//     }else {
//       cur = cur->left;
//     }
//   }
//   if (!found) {
//     toInsert = new node(val, NULL, NULL, NULL);
//     toInsert->color = true;
//   }
// }

void RedBlackTree::fix(node *toEnter) {
  node* cur;
  if (root == toEnter) {
    toEnter->color = false;
    return;
  }
  while (toEnter->parent != NULL && toEnter->parent->color) {
    node* grandparent = toEnter->parent->parent;
    if (grandparent->left == toEnter->parent) {
      if (grandparent->right != NULL) {
        cur = grandparent->right;
        if (cur->color) {
          cur->color = false;
          toEnter->parent->color = false;
          grandparent->color = true;
          toEnter = grandparent;
        }
      } else {
        if (toEnter->parent->right == toEnter) {
          toEnter = toEnter->parent;
          leftRotate(toEnter);
        }
        toEnter->parent->color = false;
        grandparent->color = true;
        rightRotate(grandparent);
      }
    } else {
      if (grandparent->left != NULL) {
        cur = grandparent->left;
        if (cur->color) {
          toEnter->parent->color = false;
          cur->color = false;
          grandparent->color = true;
          toEnter = grandparent;
        }
      } else {
        if (toEnter->parent->left == toEnter) {
          toEnter = toEnter->parent;
          rightRotate(toEnter);
        }
        toEnter->parent->color = false;
        grandparent->color = true;
        leftRotate(grandparent);
      }
    }
    root->color = false;
  }
}

void RedBlackTree::leftRotate(node *toRotate) {
  if (toRotate->right != NULL) {
    node* right = toRotate->right;
    if (right->left != NULL) {
      toRotate->right = right->left;
      right->left->parent = toRotate;
    } else {
      toRotate->right = NULL;
    }
    if (toRotate->parent != NULL) {
      right->parent = toRotate->parent;
    }
    if (toRotate->parent == NULL) {
      root = right;
    } else {
      if (toRotate == toRotate->parent->left) {
        toRotate->parent->left = right;
      } else {
        toRotate->parent->right = right;
      }
    }
    right->left = toRotate;
    toRotate->parent = right;
  }
}

void RedBlackTree::rightRotate(node* toRotate) {
  if (toRotate->left != NULL) {
    node* left = toRotate->left;
    if (left->right != NULL) {
      toRotate->left = left->right;
      left->right->parent = toRotate;
    } else {
      toRotate->left = NULL;
    }
    if (toRotate->parent != NULL) {
      left->parent = toRotate->parent;
    }
    if (toRotate->parent == NULL) {
      root = left;
    } else {
      if (toRotate == toRotate->parent->left) {
        toRotate->parent->left = left;
      } else {
        toRotate->parent->right=left;
      }
    }
  }
}

node* RedBlackTree::insertHelper(node*& root, node*& toInsert) {
  if (root == NULL) return toInsert;

  if (toInsert->key < root->key) {
    root->left = insertHelper(root->left, toInsert);
    root->left->parent = root;
  } else if (toInsert->key > root->key) {
    root->right = insertHelper(root->right, toInsert);
    root->right->parent = root;
  }
  return root;
}

void RedBlackTree::add(int key) {
  node* cur = new node(key, NULL, NULL, NULL);
  node* r = root;
  node* toAdd = NULL;
  if (root == NULL) {
    root = cur;
  } else {
    while (r != NULL) {
      toAdd = r;
      if (r->key < cur->key) {
        r = r->right;
      } else {
        r = r->left;
      }
      cur->parent = toAdd;
      if (toAdd->key < cur->key) {
        toAdd->right = cur;
      }else {
        toAdd->left = cur;
      }
    }
  }
  fix(cur);
}

void RedBlackTree::insertKey(int key) {
  node* toInsert = new node(key, NULL, NULL, NULL);
  add(key);
  fix(toInsert);
}

node* RedBlackTree::getRoot() {
  return root;
}
