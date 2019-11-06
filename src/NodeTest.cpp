#include <stdio.h>
#include <iostream>
#include "Node.h"

using namespace std;

int testNilNodeCreation() {
  node nil (-1, nullptr, nullptr, nullptr);
  if (!(nil.key == -1 && nil.parent == nullptr && nil.left == nullptr && nil.right == nullptr)) {
    cout << "testNilNodeCreation failure\n";
    return 1;
  }
  return 0;
}

int testParentChildRelationship() {
  node* parent = new node(5, nullptr, nullptr, nullptr);
  node* rightChild = new node(6, parent, nullptr, nullptr);
  node* leftChild = new node(4, parent, nullptr, nullptr);
  cout << "made\n";
  parent->setRight(rightChild);
  parent->setLeft(leftChild);
  int leftChildKey = parent->getLeft()->getKey();
  if (leftChildKey != 4){
    cout << "Unexpected left key\n";
    return 1;
  }
  leftChildKey = parent->getLeft()->getParent()->getRight()->getParent()->getLeft()->getKey();
  if (leftChildKey != 4){
    cout << "Unexpected left key 2 \n";
    return 1;
  }
  int rightChildKey = parent->getLeft()->getParent()->getRight()->getKey();
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
