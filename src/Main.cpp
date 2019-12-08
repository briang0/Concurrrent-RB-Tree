#include <stdio.h>
#include <string.h>
#include <vector>
#include "Input.cpp"
#include "RedBlackTree.cpp"
#include <queue>

using namespace std;

sem_t write, r_mutex, w_mutex;
int numReaders = 0;
int numWriters = 0;

struct args {
  int* op;
  RedBlackTree* tree;
};

void *modify(void *args) {
  RedBlackTree* tree = ((struct args*) args)->tree;
  int* operation = ((struct args*) args)->op;
  sem_wait(&write);
  numWriters++;
  switch (operation[0]) {
    case INSERT:
      tree->add(operation[1]);
      cout << "Added " << operation[1] << endl;
      break;
    case DELETE:
      break;
  }
  numWriters--;
  sem_post(&write);
}

void *read(void *args) {
  RedBlackTree* tree = ((struct args*) args)->tree;
  int* operation = ((struct args*) args)->op;
  sem_wait(&r_mutex);
  numReaders++;
  if (numReaders == 1) {
    sem_wait(&write);
  }
  sem_post(&r_mutex);
  int out = tree->search(operation[1]);
  cout << "searched for " << operation[1] << " result: " << out << endl;
  sem_wait(&r_mutex);
  numReaders--;
  if (numReaders == 0) {
    sem_post(&write);
  }
  sem_post(&r_mutex);
}

void constructTree(test_case* test, RedBlackTree* tree) {
  for (int key : test->preorderKeys) {
    tree->add(key);
  }
}

void readersWriters(RedBlackTree* tree, queue<int*> readOps, queue<int*> writeOps, test_case* cur) {
  while (!readOps.empty() || !writeOps.empty()) {
    if (numReaders < cur->numReaders && !readOps.empty()) {
      int* operation = readOps.front();
      readOps.pop();
      struct args *searchArgs = (struct args*) malloc(sizeof(struct args));
      searchArgs->op = operation;
      searchArgs->tree = tree;
      pthread_t s;
      pthread_create(&s, NULL, read, (void*) searchArgs);
      pthread_join(s, NULL);
    }
    if (numWriters < cur->numWriters && !writeOps.empty()) {
      int* operation = writeOps.front();
      writeOps.pop();
      struct args *searchArgs = (struct args*) malloc(sizeof(struct args));
      searchArgs->op = operation;
      searchArgs->tree = tree;
      pthread_t s;
      pthread_create(&s, NULL, modify, (void*) searchArgs);
      pthread_join(s, NULL);
    }
  }
  cout << "Queues Depleted" << endl << endl;
}

int main() {
  queue<int*> readOps;
  queue<int*> writeOps;
  RedBlackTree* tree;
  string directory = "RBTinput-1-1-1.txt";
  vector<test_case*> status = getTestsFromFile(directory);
  for (test_case* cur : status) {
    tree = new RedBlackTree();
    constructTree(cur, tree);
    for (int* op : cur->operations) {
      switch (op[0]) {
        case SEARCH:
          readOps.push(op);
          break;
        case INSERT:
          writeOps.push(op);
          break;
        case DELETE:
          writeOps.push(op);
          break;
      }
    }
    sem_init(&write, 0, 1);
    sem_init(&r_mutex, 0, 1);
    sem_init(&w_mutex, 0, 1);
    numReaders = 0;
    numWriters = 0;
    readersWriters(tree, readOps, writeOps, cur);
    tree->preorder(tree->root);
  }
}
