#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct test_case {
  vector<int> preorderKeys;
  vector<bool> preorderColors;
  int numReaders;
  int numWriters;
  vector<int*> operations;
};

void getAllOperations(string line) {
  const char* delim = "||";
  char *str = strdup(line.c_str());
  char* token;
  token = strtok(str, strdup(delim));
  while (token != NULL) {
    cout << token << endl;
    token = strtok(NULL, delim);
  }
  cout << endl << endl;
}

void getAllThreadCounts(string line) {
  const char* delim = ":";
  char *str = strdup(line.c_str());
  char* token;
  token = strtok(str, strdup(delim));
  while (token != NULL) {
    cout << token << endl;
    token = strtok(NULL, delim);
  }
  cout << endl << endl;
}

void getAllInitalNodeValues(string line, struct test_case *test) {
  const char* delim = ",";
  char *str = strdup(line.c_str());
  char* token;
  token = strtok(str, strdup(delim));
  while (token != NULL) {
    if (strlen(token) > 1) {
      int len = strlen(token);
      char last = token[len-1];
      test->preorderColors.push_back((last == 'r'));
      token[len-1] = 0;
      int key = atoi(token);
      cout << key << endl;
      test->preorderColors.push_back(key);
    }
    token = strtok(NULL, delim);
  }
  cout << endl << endl;
}

int getTestsFromFile(string directory) {
  ifstream in(directory);
  string buffer;
  while (getline(in, buffer)) {
    struct test_case* cur = new test_case();
    transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    if (buffer.find(",") != string::npos)
      getAllInitalNodeValues(buffer, cur);
    if (buffer.find(":") != string::npos && buffer.find("thread") != string::npos)
      getAllThreadCounts(buffer);
    if (buffer.find("||") != string::npos)
      getAllOperations(buffer);
  }
  return 0;
}
