#include <stdio.h>
#include <iostream>
#include <vector>
#include "Node.h"
#include "RedBlackTree.h"

using namespace std;

int testInorderTraversal() {
  node* root = new node(10, NULL, NULL, NULL);
  node* ch1 = new node(12, root, NULL, NULL);
  node* ch2 = new node(11, ch1, NULL, NULL);
  node* ch3 = new node(6, root, NULL, NULL);
  node* ch4 = new node(4, ch3, NULL, NULL);
  node* ch5 = new node(7, ch3, NULL, NULL);

  root->right = ch1;
  root->left = ch3;
  ch1->left = ch2;
  ch3->left = ch4;
  ch3->right = ch5;

  RedBlackTree tree(root);
  vector<node*>* expectedInorder = new vector<node*>();
  expectedInorder->push_back(ch4);
  expectedInorder->push_back(ch3);
  expectedInorder->push_back(ch5);
  expectedInorder->push_back(root);
  expectedInorder->push_back(ch2);
  expectedInorder->push_back(ch1);
  vector<node*>* inorder = tree.getInOrderTraversal(root);

  for (int i = 0; i < 6; i++) {
    cout << inorder->at(i)->key << "\n";
    if (inorder->at(i)->key != expectedInorder->at(i)->key) {
      return 1;
    }
  }
  return 0;
}

int testInsertion1() {
  RedBlackTree* tree = new RedBlackTree();
  tree->add(10);
  tree->add(12);
  tree->add(11);
  tree->add(6);
  tree->add(4);
  tree->add(7);
  tree->getInOrderTraversal(tree->root);
  node* root = tree->root;
  int expected = 10;
  int actual = root->left->right->key;
  if (expected != actual) {
    return 1;
  }
  return 0;
}

int testInsertion2() {
  RedBlackTree* tree = new RedBlackTree();
  tree->add(350);
  tree->add(1235);
  tree->add(11);
  tree->add(325);
  tree->add(294);
  tree->add(37);
  tree->add(35);
  tree->add(3224);
  tree->add(435);
  tree->add(190);
  tree->add(1024);
  tree->add(749);
  tree->add(1);
  tree->add(1456);
  tree->add(397563);
  tree->add(14);
  tree->getInOrderTraversal(tree->root);
  node* root = tree->root;
  int expected = 10;
  int actual = root->left->right->key;
  if (expected != actual) {
    return 1;
  }
  return 0;
}

int main(){
  int val = testInorderTraversal();
  if (val == 0) {
    cout << "Inorder traversal works" << endl;
  }else {
    cout << "Inorder traversal is broken" << endl;
  }
  val = testInsertion1();
  if (val == 0) {
    cout << "testInsertion1 works" << endl;
  }else {
    cout << "testInsertion1 is broken" << endl;
  }
  val = testInsertion2();
  return 1;
}
