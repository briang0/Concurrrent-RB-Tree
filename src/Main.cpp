#include <stdio.h>
#include <string.h>
#include <vector>
#include "Input.cpp"
#include "RedBlackTree.cpp"
#include <queue>

using namespace std;

queue<pthread_t> readOps;
queue<pthread_t> writeOps;
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
  sem_wait(&w_mutex);
  numWriters++;
  sem_post(&w_mutex);
  sem_wait(&write);
  switch (operation[0]) {
    case INSERT:
      tree->add(operation[1]);
      break;
    case DELETE:
      break;
  }
  sem_wait(&w_mutex);
  numWriters++;
  sem_post(&w_mutex);
  sem_post(&write);
}

void *search(void *args) {
  RedBlackTree* tree = ((struct args*) args)->tree;
  int* operation = ((struct args*) args)->op;
  sem_wait(&r_mutex);
  numReaders++;
  if (numReaders == 1) {
    sem_wait(&write);
  }
  sem_post(&r_mutex);
  tree->search(operation[1]);
  sem_wait(&r_mutex);
  numReaders--;
  if (numReaders == 0) {
    sem_post(&write);
  }
  sem_post(&r_mutex);
}

void constructTree(test_case* test, RedBlackTree* tree) {
  for (int key : test->preorderKeys) {
    cout << "Adding " << key << endl;
    tree->add(key);
    tree->preorder(tree->root);
  }
}

void readersWriters(RedBlackTree* tree, queue<int*> readOps, queue<int*> writeOps, test_case* cur) {
  while (!readOps.empty() && !writeOps.empty()) {
    if (numReaders < cur->numReaders) {
      cout << "New Reader" << endl;
      int* operation = readOps.front();
      readOps.pop();
      struct args *searchArgs = (struct args*) malloc(sizeof(struct args));
      searchArgs->op = operation;
      searchArgs->tree = tree;
      pthread_t s;
      pthread_create(&s, NULL, search, (void*) searchArgs);
      cout << "Finished Reader" << endl;
    }
    if (numWriters < cur->numWriters) {
      cout << "New Writer" << endl;
      int* operation = writeOps.front();
      writeOps.pop();
      struct args *searchArgs = (struct args*) malloc(sizeof(struct args));
      searchArgs->op = operation;
      searchArgs->tree = tree;
      pthread_t s;
      pthread_create(&s, NULL, modify, (void*) searchArgs);
      cout << "New Writer" << endl;
    }
  }
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
    sem_init(&write, 0, cur->numWriters);
    sem_init(&r_mutex, 0, 1);
    sem_init(&w_mutex, 0, 1);
    numReaders = 0;
    numWriters = 0;
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
    readersWriters(tree, readOps, writeOps, cur);
  }
}
