#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct test_case {

};

void getAllOperations(string line) {
  const char* delim = "||";
  char *str = strdup(line.c_str());
  char* token;
  token = strtok(str, strdup(delim));
  while (token != NULL) {
    cout << token;
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
    cout << token;
    token = strtok(NULL, delim);
  }
  cout << endl << endl;
}

void getAllInitalNodeValues(string line) {
  const char* delim = ",";
  char *str = strdup(line.c_str());
  char* token;
  token = strtok(str, strdup(delim));
  while (token != NULL) {
    cout << token;
    token = strtok(NULL, delim);
  }
  cout << endl << endl;
}

int getTestsFromFile(string directory) {
  ifstream in(directory);
  string buffer;
  while (getline(in, buffer)) {
    transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    if (buffer.find(",") != string::npos)
      getAllInitalNodeValues(buffer);
    if (buffer.find(":") != string::npos && buffer.find("thread") != string::npos)
      getAllInitalNodeValues(buffer);
    if (buffer.find("||") != string::npos)
      getAllInitalNodeValues(buffer);
  }
  return 0;
}
