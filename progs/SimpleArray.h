#ifndef CHARARRAY_H
#define CHARARRAY_H

#include <iostream>
#include "math.h"
#include "Array.h"
#include <vector>

using namespace std;

template <class StorageType>
class SimpleArray {
private:
  vector<StorageType> array;

public:

  SimpleArray(unsigned long long int size=0) {
    array.insert(array.begin(),size,0);
  }

  unsigned long long int at(unsigned long long int position) {
    return array[position];
  }

  unsigned long long int operator[](unsigned long long int position) {
    return array[position];
  }

  void insert(unsigned long long int position,unsigned long long int value) {
    array[position] = value;
  }

  void push_back(unsigned long long int i) {
    array.push_back(i);
  }

};

#endif

