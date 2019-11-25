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

  void insert(node* toInsert);

  void insertKey(int key);

  void fix(node* toEnter);

  void leftRotate(node* toRotate);

  void rightRotate(node* toRotate);

  void remove();

  void inOrderTraversal(vector<node*>* order, node* cur_root);

  vector<node*>* getInOrderTraversal(node* inRoot);

  node* getRoot();

};

void RedBlackTree::inOrderTraversal(vector<node*>* order, node* cur_root) {
  if (cur_root == NULL) {
    return;
  }
  inOrderTraversal(order, cur_root->left);
  order->push_back(cur_root);
  inOrderTraversal(order, cur_root->right);
}

vector<node*>* RedBlackTree::getInOrderTraversal(node* inRoot) {
  vector<node*>* order = new vector<node*>();
  inOrderTraversal(order, inRoot);
  return order;
}

void RedBlackTree::fix(node* toEnter) {
  node* parent;
  node* grandparent;
  while (toEnter != root && toEnter->color) {
    parent = toEnter->parent;
    grandparent = toEnter->parent->parent;

    if (parent == grandparent->left) {
      node* uncle = grandparent->right;
      if (uncle != NULL && uncle->color) {
        grandparent->color = true;
        parent->color = false;
        uncle->color = false;
        toEnter = grandparent;
      } else {
        if (toEnter == parent->right) {
          leftRotate(parent);
          toEnter = parent;
          parent = toEnter->parent;
        }
        rightRotate(grandparent);
        bool temp = parent->color;
        parent->color = grandparent->color;
        grandparent->color = temp;
        toEnter = parent;
      }
    } else {
      node* uncle = grandparent->left;
      if (uncle != NULL && uncle->color) {
        grandparent->color = true;
        parent->color = false;
        uncle->color = false;
        toEnter = grandparent;
      } else {
        if (toEnter == parent->left) {
          rightRotate(parent);
          toEnter = parent;
          parent = toEnter->parent;
        }
        leftRotate(grandparent);
        bool temp = parent->color;
        parent->color = grandparent->color;
        grandparent->color = temp;
        toEnter = parent;
      }
    }
  }
}

void RedBlackTree::leftRotate(node* toRotate) {
  node* right = toRotate->right;
  toRotate->right = right;
  if (toRotate->right != NULL) toRotate->right->parent = toRotate;
  right->parent = toRotate->parent;

  if (toRotate->parent == NULL) root = toRotate->right;
  else if (toRotate == toRotate->parent->left) toRotate->parent->left = right;
  else toRotate->parent->right = right;

  right->left = toRotate;
  toRotate->parent = right;
}

void RedBlackTree::rightRotate(node* toRotate) {
  node* left = toRotate->left;
  toRotate->left = left->right;

  if (toRotate->left != NULL) root = left;
  else if (toRotate == toRotate->parent->left) toRotate->parent->left = left;
  else toRotate->parent->right = left;

  left->right = toRotate;
  toRotate->parent = left;

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

void RedBlackTree::insert(node* toInsert) {
  root = insertHelper(root, toInsert);
  fix(toInsert);
}

void RedBlackTree::insertKey(int key) {
  node* toInsert = new node(key, NULL, NULL, NULL);
}

node* RedBlackTree::getRoot() {
  return root;
}
