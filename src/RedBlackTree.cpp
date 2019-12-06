#include <stdio.h>
#include <iostream>
#include <vector>
#include "Node.h"
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

  void fix(node *&toEnter);

  void leftRotate(node *&toRotate);

  void rightRotate(node *&toRotate);

  void remove();

  void preorder(node* head);

  void inOrderTraversal(vector<node*>* order, node* cur_root);

  vector<node*>* getInOrderTraversal(node* inRoot);

  node* btAdd(node* r, node* n);

  void add(int key);

  node* searchHelper(int key, node* head);

  int search(int key);


};

node* RedBlackTree::searchHelper(int key, node* head) {
  if (head->key == key) {
    return head;
  }
  if (head->key < key && head->right != NULL) {
    return searchHelper(key, head->right);
  }
  if (head->key > key && head->left != NULL) {
    return searchHelper(key, head->left);
  }
  return NULL;
}

int RedBlackTree::search(int key) {
  int* output = (int*) malloc(9 * sizeof(int));
  node* found = searchHelper(key, root);
  if (found == NULL) {
    return -1;
  } else {
    return found->color;
  }
}

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

void RedBlackTree::preorder(node* head) {
  if (head == NULL) {
    return;
  }

  cout << head->key << ":" << head->color << ", ";

  preorder(head->left);
  preorder(head->right);
}

void RedBlackTree::fix(node *&n) {
  node *p, *grandparent;

  while (n != root && n->color != false && n->parent->color) {
    p = n->parent;
    grandparent = n->parent->parent;
    if (p == grandparent->left) {
        node *uncle = grandparent->right;
        if (uncle != NULL && uncle->color) {
            grandparent->color = true;
            p->color = false;
            uncle->color = false;
            n = grandparent;
        } else {
            if (n == p->right) {
                leftRotate(p);
                n = p;
                p = n->parent;
            }
            rightRotate(grandparent);
            bool temp = p->color;
            p->color = grandparent->color;
            grandparent->color = temp;
            n = p;
        }
    } else {
        node *uncle = grandparent->left;
        if (uncle != NULL && uncle->color == true) {
            grandparent->color = true;
            p->color = false;
            uncle->color = false;
            n = grandparent;
        }
        else {
            if (n == p->left) {
                rightRotate(p);
                n = p;
                p = n->parent;
            }
            leftRotate(grandparent);
            bool temp = p->color;
            p->color = grandparent->color;
            grandparent->color = temp;
            n = p;
        }
    }
}

root->color = false;
}

void RedBlackTree::leftRotate(node *&toRotate) {
  node* right = toRotate->right;
  toRotate->right = right->left;
  if (toRotate->right != NULL) {
    toRotate->right->parent = toRotate;
  }
  right->parent = toRotate->parent;
  if(toRotate->parent == NULL) {
    root = right;
  } else if (toRotate == toRotate->parent->left) {
    toRotate->parent->left = right;
  } else {
    toRotate->parent->right = right;
  }
  right->left = toRotate;
  toRotate->parent = right;
}

void RedBlackTree::rightRotate(node*& toRotate) {
  node* left = toRotate->left;
  toRotate->left = left->right;
  if (toRotate->right != NULL) {
    toRotate->left->parent = toRotate;
  }
  left->parent = toRotate->parent;
  if (toRotate->parent != NULL) {
    left->parent = toRotate->parent;
  }
  if (toRotate->parent == NULL) {
    root = left;
  } else if (toRotate == toRotate->parent->left) {
    toRotate->parent->left = left;
  } else {
    toRotate->parent->right = left;
  }
  left->right = toRotate;
  toRotate->parent = left;
}

node* RedBlackTree::btAdd(node* root, node* n) {
  if (root == NULL) {
    return n;
  }
  if (n->key < root->key) {
    root->left = btAdd(root->left, n);
    root->left->parent = root;
  } else if (n->key > root->key) {
    root->right = btAdd(root->right, n);
    root->right->parent = root;
  }
  return root;
}

void RedBlackTree::add(int key) {
  node* n = new node(key, NULL, NULL, NULL);
  root = btAdd(root, n);
  fix(n);
}
