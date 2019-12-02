#include<stdio.h>

class node{
public:
  int key;
  node* parent;
  node* left;
  node* right;
  bool color;

  node (int inKey, node* inParent, node* inLeft, node* inRight);

  bool isLeaf();

};

node::node (int inKey, node* inParent, node* inLeft, node* inRight) {
  key = inKey;
  parent = inParent;
  left = inLeft;
  right = inRight;
  color = true;
}

bool node::isLeaf() {
  return color == false && right == NULL && left == NULL;
}
