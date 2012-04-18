#include <iostream>

#include "math.h"
#include "Array.h"

#ifndef BITPLUSARRAY_H
#define BITPLUSARRAY_H

class BitPlusArray {
private:
  vector<unsigned int>  array;
  vector<unsigned char> arrayAux;
  unsigned int long long bit33;

public:
  BitPlusArray(unsigned long long int size=0) {
    array.insert(array.begin(),size,0);
    arrayAux.insert(arrayAux.begin(),(size/8)+1,0);

    bit33 = (int long long) 1 << 32;
  }
	
  unsigned long long int at(unsigned long long int position) {
		
    unsigned long long int val = array[position];
    if((arrayAux[position/8] & (1 <<(position%8)) ) > 0) val += bit33;

    return val;
  }

  unsigned long long int operator[](unsigned long long int position) {

    unsigned long long int val = array[position];
    if((arrayAux[position/8] & (1 <<(position%8)) ) > 0) val += bit33;

    return val;
  }

  void insert(unsigned long long int position,unsigned long long int value) {

    array[position] = value & 0xFFFFFFFF;

    if((value & bit33) > 0) {
      arrayAux[position/8] = arrayAux[position/8] | (1 << (position%8));
    }
    else arrayAux[position/8] = arrayAux[position/8] & (0xFF - (1 << (position%8)));
  }

  void push_back(unsigned long long int i) {
    if(arrayAux.size() < ((array.size()/8)+1)) arrayAux.push_back(0);

    array.push_back(0);

    insert(array.size()-1,i);
  }
};

#endif

