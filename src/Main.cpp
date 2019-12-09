#include <stdio.h>
#include <string.h>
#include <vector>
#include "Input.cpp"
#include "RedBlackTree.cpp"
#include <queue>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

sem_t write, r_mutex, w_mutex, barrier, b_mutex;
int numReaders = 0;
int numWriters = 0;
int numThreads = 0;

// A structure for holding the parameters needed to make tree calls.
struct args {
  int* op;
  RedBlackTree* tree;
  vector<string>* searchOutput;
};

// Modifies a red black tree concurrently. It can call either insert or delete.
// Input: void* args: A struct args containing all necessary data to modify the tree.
void *modify(void *args) {
  RedBlackTree* tree = ((struct args*) args)->tree;
  int* operation = ((struct args*) args)->op;
  sem_wait(&write);
  numWriters++;
  switch (operation[0]) {
    case INSERT:
      tree->add(operation[1]);
      break;
    case DELETE:
    tree->remove(operation[1]);
      break;
  }
  numWriters--;
  sem_post(&write);
}

// Concurrently searches for a node in the tree
// Input: void* args: A struct args containing all necessary data to search for a node in a tree
void *read(void *args) {
  RedBlackTree* tree = ((struct args*) args)->tree;
  int* operation = ((struct args*) args)->op;
  vector<string>* searchOutput = ((struct args*) args)->searchOutput;
  sem_wait(&r_mutex);
  numReaders++;
  if (numReaders == 1) {
    sem_wait(&write);
  }
  sem_post(&r_mutex);
  int out = tree->search(operation[1]);
  string output = "";
  string status = (out >= 0) ? "true" : "false";
  output.append("search(");
  output.append(to_string(operation[1]));
  output.append(")->");
  output.append(status);
  output.append(", performed by thread ");
  output.append(to_string(pthread_self()));
  output.append("\n");
  searchOutput->push_back(output);
  sem_wait(&r_mutex);
  numReaders--;
  if (numReaders == 0) {
    sem_post(&write);
  }
  sem_post(&r_mutex);
}

// Constructs the tree from a given list of a nodes from a test
// Input: test_case* test: A test_case structure containing all the data of the test, including the inital nodes
//        RedBlackTree* tree: The tree being created
void constructTree(test_case* test, RedBlackTree* tree) {
  for (int key : test->preorderKeys) {
    tree->add(key);
  }
}

// Manages the readers/writers problem. It gives priority to readers, and allows
// a specified number of readers and writers to run. It both modifies and searches
// the tree.
// Input: RedBlackTree* tree: The tree to be modified
//        queue<int*> readOps: A queue of all reading operations that need to be performed.
//        queue<int*> writeOps: A queue of all write operations that need to be performed.
//        test_case* cur: The current test case the readers/writers are performing on.
vector<string>* readersWriters(RedBlackTree* tree, queue<int*> readOps, queue<int*> writeOps, test_case* cur) {
  vector<string>* searchOutput = new vector<string>();
  while (!readOps.empty() || !writeOps.empty()) {
    if (numReaders < cur->numReaders && !readOps.empty()) {
      int* operation = readOps.front();
      readOps.pop();
      struct args *searchArgs = (struct args*) malloc(sizeof(struct args));
      searchArgs->op = operation;
      searchArgs->tree = tree;
      searchArgs->searchOutput = searchOutput;
      pthread_t s;
      pthread_create(&s, NULL, read, (void*) searchArgs);
    }
    if (numWriters < cur->numWriters && !writeOps.empty()) {
      int* operation = writeOps.front();
      writeOps.pop();
      struct args *searchArgs = (struct args*) malloc(sizeof(struct args));
      searchArgs->op = operation;
      searchArgs->tree = tree;
      pthread_t s;
      pthread_create(&s, NULL, modify, (void*) searchArgs);
    }
  }
  sem_wait(&b_mutex);
  numThreads++;
  sem_post(&b_mutex);
  if (numThreads == cur->numReaders + cur->numWriters) {
    sem_post(&barrier);
  }
  sem_wait(&barrier);
  sem_post(&barrier);
  return searchOutput;
}

// Gets the current time in milliseconds
// Output: A long of the elapsed time since the epoch
long getTime() {
  long curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  return curTime;
}

// The driver function for the program. It gets all tests from a file and runs them
// concurrently through the readers/writers problem. It stores running statistics of
// each test in a file.
int main(int argc, char** argv) {
  string directory = "RBTinput-1-1-2.txt";
  if (argc <= 1) {
    cout << "No input file. Trying RBTinput-1-1-2.txt" << endl;
  } else {
    directory = argv[1];
  }
  ofstream outputFile("output.txt", ios::out | ios::trunc);
  queue<int*> readOps;
  queue<int*> writeOps;
  RedBlackTree* tree;
  vector<test_case*> status = getTestsFromFile(directory);
  long entireTime = 0;
  long entireTimeWithConstruction = 0;
  long testStart = 0;
  long testStartWithConstruction = 0;
  for (int i = 1; i < status.size(); i++) {
    outputFile << "Test #" << i << endl;
    tree = new RedBlackTree();
    testStartWithConstruction = getTime();
    constructTree(status[i], tree);
    testStart = getTime();
    for (int* op : status[i]->operations) {
      switch (op[0]) {
        case SEARCH:
          readOps.push(op);
          break;
        case INSERT:
          writeOps.push(op);
          break;
        case DELETE:
          // writeOps.push(op);
          break;
      }
    }
    sem_init(&write, 0, 1);
    sem_init(&r_mutex, 0, 1);
    sem_init(&w_mutex, 0, 1);
    sem_init(&b_mutex, 0, 1);
    sem_init(&barrier, 0, 1);
    numReaders = 0;
    numWriters = 0;
    vector<string>* output = readersWriters(tree, readOps, writeOps, status[i]);
    long endTime = getTime();
    string* preorderOutput = new string();
    for (int i = 0; i < output->size(); i++) {
      outputFile << output->at(i);
    }
    tree->preorder(tree->root, preorderOutput);
    outputFile << *preorderOutput << "\n";
    outputFile << "Time with initial tree construction: " << (endTime - testStartWithConstruction) << "ms\n";
    outputFile << "Time without initial tree construction: " << (endTime - testStart) << "ms\n\n";
    entireTime += (endTime - testStart);
    entireTimeWithConstruction += (endTime - testStartWithConstruction);
  }
  outputFile << "Time with initial tree construction: " << entireTimeWithConstruction << "ms\n";
  outputFile << "Time without initial tree construction: " << entireTime << "ms\n";
  // outputFile.close();
}
