#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#define UNDEF  0
#define SEARCH 1
#define INSERT 2
#define DELETE 3

using namespace std;

// A structure containing all test informationm
struct test_case {
  vector<int> preorderKeys;
  vector<bool> preorderColors;
  int numReaders;
  int numWriters;
  vector<int*> operations;
};

// Parses out all operations and stores them in a test_case
// Input: string line: The file line to be parsed.
//        struct test_case*: The structure to store the data
void getAllOperations(string line, struct test_case* test) {
  const char* delim = " ()\n\t||";
  char *str = strdup(line.c_str());
  char* token;
  token = strtok(str, strdup(delim));
  int upNext = UNDEF;
  while (token != NULL) {
    if (!strcmp(token, "search")) {
      upNext = SEARCH;
    } else if (!strcmp(token, "insert")) {
      upNext = INSERT;
    } else if (!strcmp(token, "delete")) {
      upNext = DELETE;
    } else if (isdigit(token[0])) {
      int* op = (int*) malloc(2 * sizeof(int));
      op[0] = upNext;
      op[1] = atoi(token);
      test->operations.push_back(op);
    }
    token = strtok(NULL, delim);
  }
}

// Finds the number of reading and writing threads and stores them in a test_case
// Input: string line: The current line in the file
//        struct test_case* test: The current test to store the data in.
void getAllThreadCounts(string line, struct test_case* test) {
  const char* delim = " \n\t:";
  char *str = strdup(line.c_str());
  char* token;
  token = strtok(str, strdup(delim));
  bool nextIntType = false;
  while (token != NULL) {
    if (!strcmp(token, "search")) {
      nextIntType = false;
    } else if (!strcmp(token, "modify")) {
      nextIntType = true;
    } else if (isdigit(token[0])){
      if (nextIntType) {
        test->numWriters = atoi(token);
      } else {
        test->numReaders = atoi(token);
      }
    }
    token = strtok(NULL, delim);
  }
}

// Gets the inital node values from a file and stores it in a test structure.
// Input: string line: The current line of text.
//        struct test_case *test: The test_case to store the data
void getAllInitalNodeValues(string line, struct test_case *test) {
  const char* delim = ", \n\0";
  char *str = strdup(line.c_str());
  char* token;
  token = strtok(str, strdup(delim));
  while (token != NULL) {
    if (isdigit(token[0])) {
      int len = strlen(token);
      char last = token[len-1];
      test->preorderColors.push_back((last == 'r'));
      token[len-1] = 0;
      int key = atoi(token);
      test->preorderKeys.push_back(key);
    }
    token = strtok(NULL, delim);
  }
}

// Gets all test cases from a given file.
// Input: string directory: The directory of the file to be read
// Output: vector<struct test_case*>: a vector of struct test_cases that correspond
//         to each test in the file
vector<struct test_case*> getTestsFromFile(string directory) {
  ifstream in(directory);
  string buffer;
  vector<struct test_case*> tests;
  struct test_case* cur = new test_case();
  while (getline(in, buffer)) {
    transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    if (buffer.find("test") != string::npos) {
      tests.push_back(cur);
      cur = new test_case();
    }
    if (buffer.find(",") != string::npos)
      getAllInitalNodeValues(buffer, cur);
    if (buffer.find(":") != string::npos && buffer.find("thread") != string::npos)
      getAllThreadCounts(buffer, cur);
    if (buffer.find("||") != string::npos)
      getAllOperations(buffer, cur);
  }
  tests.push_back(cur);
  return tests;
}
