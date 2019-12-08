#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "Node.h"
#include "semaphore.h"
#include "pthread.h"

using namespace std;

// RedBlackTree object
class RedBlackTree {
public:
  node* root;

  RedBlackTree(node* inRoot) {
    root = inRoot;
  }

  RedBlackTree() {
    root = NULL;
  }

  void fixDeletion(node*);

  void fix(node*);

  void leftRotate(node*);

  void rightRotate(node*);

  void remove();

  void preorder(node*, string*);

  void inOrderTraversal(vector<node*>*, node*);

  vector<node*>* getInOrderTraversal(node*);

  void transplant(node*, node*);

  void remove(int);

  node* btAdd(node*, node*);

  void add(int);

  node* searchHelper(int, node*);

  int search(int);


};

// This function recursively searches for a node with a key.
// Params: int key: The key to be searched for
//         node* head: The starting point of the search
//Output:
//The node whose key is equal to the input key. NULL if not found.
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

// The driver function for searchHelper.
// Input: int key: the key to be searched for
// Output: 0 if the found node is black
//         1 if the found node is red
//         -1 if the node was not found
int RedBlackTree::search(int key) {
  int* output = (int*) malloc(9 * sizeof(int));
  node* found = searchHelper(key, root);
  if (found == NULL) {
    return -1;
  } else {
    return found->color;
  }
}

// Prints out the in order traversal of the tree
// Input: vector<node*>* order: the in order traversal
//        node* cur_root: The beginning node
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

// The driver for inOrderTraversal
// Input: node* inRoot: The starting point of the traversal
// Output: vector<node*>* of nodes in inorder.
vector<node*>* RedBlackTree::getInOrderTraversal(node* inRoot) {
  vector<node*>* order = new vector<node*>();
  inOrderTraversal(order, inRoot);
  return order;
}

// A function to find the preorder traversal of the tree
// Input: node* head: The starting point of the traversal
//        string* out: The string that stores the traversal
void RedBlackTree::preorder(node* head, string* out) {
  if (head == NULL) {
    out->append("f,");
    return;
  }

  out->append(to_string(head->key));
  out->append((head->color ? "r," : "b,"));

  preorder(head->left, out);
  preorder(head->right, out);
}

// Fixes the tree after a deletion in order to follow red black tree rules
// Input: node* n: The node that took the place of the deleted node
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

// Repairs the tree after an insertion in order to follow red black tree rules
// Input: node* n: The node added to the tree
void RedBlackTree::fix(node *n) {
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

// Rotates n to the position of its left child
// Input: node* n: The node to be rotated
void RedBlackTree::leftRotate(node *n) {
  node* right = n->right;
  n->right = right->left;
  if (n->right != NULL) {
    n->right->parent = n;
  }
  right->parent = n->parent;
  if(n->parent == NULL) {
    root = right;
  } else if (n == n->parent->left) {
    n->parent->left = right;
  } else {
    n->parent->right = right;
  }
  right->left = n;
  n->parent = right;
}

// Rotates n to the position of its right child
// Input: node* n: The node to be rotated
void RedBlackTree::rightRotate(node* toRotate) {
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

// Replaces sub-trees starting at u and v
// Input: u: The first sub-tree
//        v: The second sub-tree
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

// Deletes a node with the input key
// Input: int key: The key of the node to be deleted
void RedBlackTree::remove(int key) {
  node* r = root;
  node* target = NULL;
  node* a;
  node* b;
  while (r != NULL) {
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

// Adds a node in the same manner as a BST
// Input: node* root: The root node of the tree
//        node* n: The node being inserted
node* RedBlackTree::btAdd(node* root, node* n) {
  if (root == NULL) {
    return n;
  }
  if (n->key < root->key) {
    root->left = btAdd(root->left, n);
    root->left->parent = root;
  } else if (n->key >= root->key) {
    root->right = btAdd(root->right, n);
    root->right->parent = root;
  }
  return root;
}

// Adds the node of the input key to the tree. It creates a node and calls btAdd
// Input: int key: The key of the node to be added.
void RedBlackTree::add(int key) {
  node* n = new node(key, NULL, NULL, NULL);
  root = btAdd(root, n);
  fix(n);
}
