#ifndef INPUT
#define INPUT

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>

#define UNDEF 0
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

vector<struct test_case*> getTestsFromFile(string);

vector<string> getAllInitalNodeValues(string);

#endif
