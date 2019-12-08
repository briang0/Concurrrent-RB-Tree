#include <stdio.h>
#include <string.h>
#include <vector>
#include "Input.cpp"
#include "RedBlackTree.cpp"

using namespace std;

void constructTree(test_case* test, RedBlackTree* tree) {
  for (int key : test->preorderKeys) {
    cout << "Adding " << key << endl;
    tree->add(key);
    tree->preorder(tree->root);
  }
}

int main() {
  RedBlackTree* tree;
  string directory = "RBTinput-1-1-1.txt";
  vector<test_case*> status = getTestsFromFile(directory);
  for (test_case* cur : status) {
    tree = new RedBlackTree();
    constructTree(cur, tree);
    for (int* op : cur->operations) {
      switch (op[0]) {
        case SEARCH:
          tree->search(op[1]);
          break;
        case INSERT:
          tree->add(op[1]);
          break;
        // case DELETE:
        //   tree->remove(op[1]);
        //   break;
      }
    }
  }
}
