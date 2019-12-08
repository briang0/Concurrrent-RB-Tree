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

struct test_case {
  vector<int> preorderKeys;
  vector<bool> preorderColors;
  int numReaders;
  int numWriters;
  vector<int*> operations;
};

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
  return tests;
}
