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
  node* root = tree->root;
  tree->getInOrderTraversal(root);
  int expectedRootKey = 11;
  int expectedRootColor = 0;
  int expectedRightKey = 12;
  int expectedRightColor = 0;
  int actualRootKey = root->key;
  bool actualRootColor = root->color;
  int actualRightKey = root->right->key;
  bool actualRightColor = root->right->color;
  int actualLeftKey = root->left->key;
  bool actualLeftColor = root->left->color;
  cout << actualRootKey << " : " << actualRootColor << endl;
  cout << actualRightKey << " : " << actualRightColor << endl;
  cout << actualLeftKey << " : " << actualLeftColor << endl;
  return 0;
}

int main(){
  int val = testInorderTraversal();
  if (val == 0) {
    cout << "Inorder traversal works" << endl;
  }else {
    cout << "Inorder traversal is broken" << endl;
  }
  val += testInsertion1();
  return 1;
}
