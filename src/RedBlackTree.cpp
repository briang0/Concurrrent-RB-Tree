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

  void fixDeletion(node* n);

  void fix(node *&toEnter);

  void leftRotate(node *&toRotate);

  void rightRotate(node *&toRotate);

  void remove();

  void preorder(node* head);

  void inOrderTraversal(vector<node*>* order, node* cur_root);

  vector<node*>* getInOrderTraversal(node* inRoot);

  void transplant(node* u, node* v);

  void remove(int key);

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

void RedBlackTree::fixDeletion(node* n) {
  node* a;
  while (n != root && !n->color) {
    if (n == n->parent->left) {
      a = n->parent->right;
      if (a->color) {
        a->color = false;
        n->parent->color = true;
        leftRotate(n->parent);
        a = n->parent->right;
      }
      if (!a->left->color && !a->right->color) {
        a->color = true;
        n = n->parent;
      }
      else {
        if (!a->right->color) {
          a->left->color = false;
          a->color = true;
          rightRotate(a);
          a = n->parent->right;
        }
        a->color = n->parent->color;
        n->parent->color = false;
        a->right->color = false;
        leftRotate(n->parent);
        n = root;
      }
    }
    else {
      a = n->parent->left;
      if (a->color) {
        a->color = false;
        n->parent->color = true;
        rightRotate(n->parent);
        a = n->parent->left;
      }
      if (!a->right->color && !a->right->color) {
        a->color = true;
        n = n->parent;
      }
      else {
        if (!a->left->color) {
          a->right->color = false;
          a->color = true;
          leftRotate(a);
          a = n->parent->left;
        }
        a->color = n->parent->color;
        n->parent->color = false;
        a->left->color = false;
        rightRotate(n->parent);
        n = root;
      }
    }
  }
  n->color = false;
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

void RedBlackTree::transplant(node* u, node* v) {
  if (u->parent == NULL) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void RedBlackTree::remove(int key) {
  node* r = root;
  node* target = NULL;
  node* a;
  node* b;
  while (r != NULL) {
    cout << "sad" << endl;
    if (r->key == key) {
      target = r;
    } if (r->key <= key) {
      r = r->right;
    } else {
      r = r->left;
    }
  }
  if (target == NULL) {
    return;
  }

  b = target;
  bool temp = target->color;
  if (target->left == NULL) {
    a = target->right;
    transplant(target, target->right);
  } else if (target->right == NULL) {
    a= target->left;
    transplant(target, target->left);
  } else {
    b = target->right;
    while (b->left != NULL) {
      cout << "rad" << endl;
      b = b->left;
    }
    temp = b->color;
    a = b->right;
    if (b->parent == target) {
      a->parent = b;
    } else {
      transplant(b, b->right);
      b->right = target->right;
      b->right->parent = b;
    }
    transplant(target, b);
    b->left = target->left;
    b->left->parent = b;
    b->color = target->color;
  }
  if (!temp) {
    fixDeletion(a);
  }
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
