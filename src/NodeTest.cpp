#include <stdio.h>
#include <iostream>
#include "Node.h"

using namespace std;

int testNilNodeCreation() {
  node nil (-1, NULL, NULL, NULL);
  if (!(nil.key == -1 && nil.parent == NULL && nil.left == NULL && nil.right == NULL)) {
    cout << "testNilNodeCreation failure\n";
    return 1;
  }
  return 0;
}

int testParentChildRelationship() {
  node* parent = new node(5, NULL, NULL, NULL);
  node* rightChild = new node(6, parent, NULL, NULL);
  node* leftChild = new node(4, parent, NULL, NULL);
  parent->right = rightChild;
  parent->left = leftChild;
  int leftChildKey = parent->left->key;
  if (leftChildKey != 4){
    cout << "Unexpected left key\n";
    return 1;
  }
  leftChildKey = parent->left->parent->right->parent->left->key;
  if (leftChildKey != 4){
    cout << "Unexpected left key 2 \n";
    return 1;
  }
  int rightChildKey = parent->left->parent->right->key;
  if (rightChildKey != 6) {
    cout << "Unexpected right key\n";
    return 1;
  }

  return 0;
}

int main() {
  int testSum = testNilNodeCreation();
  testSum += testParentChildRelationship();
  cout << testSum << " tests failed\n";
}
