#include<stdio.h>

// A simple class representing a tree node
class node{
public:
  int key;
  node* parent;
  node* left;
  node* right;
  bool color;
  bool db;

  node (int inKey, node* inParent, node* inLeft, node* inRight);

};

node::node (int inKey, node* inParent, node* inLeft, node* inRight) {
  key = inKey;
  parent = inParent;
  left = inLeft;
  right = inRight;
  color = true;
  db = false;
}
