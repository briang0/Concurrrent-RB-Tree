#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

struct test_case {

};

void getAllInitalNodeValues(string line) {
  const char* delim = ",";
  char *str = strdup(line.c_str());
  cout << str << endl;
  char* token;
  token = strtok(str, strdup(delim));
  while (token != NULL) {
    cout << token;
    token = strtok(NULL, delim);
  }
  cout << endl;
}

vector<vector<string>> getTestsFromFile(string directory) {
  ifstream in(directory);
  string buffer;
  while (getline(in, buffer)) {
    if (buffer.find(",") != string::npos)
      getAllInitalNodeValues(buffer);
  }
}
