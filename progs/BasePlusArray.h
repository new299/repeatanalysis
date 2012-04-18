#include <iostream>

#include "math.h"
#include <map>
#include <vector>
#include "Array.h"

using namespace std;

#ifndef BASEPLUSARRAY_H
#define BASEPLUSARRAY_H

template <class _BaseType,int _BaseMax,class _ExtendedType,class _ExtractionType,class _IndexType>
class BasePlusArray {
private:
  vector<_BaseType> baseArray;
  map<_ExtractionType,_ExtendedType> extendedMap;
  vector<unsigned char> typeBit;
  _ExtendedType max_value;

public:

  BasePlusArray(_IndexType size=0) {
    baseArray.clear();
    baseArray.insert(baseArray.begin(),size,0);
    
    typeBit.clear();
    typeBit.insert(typeBit.begin(),(size/8)+1,0);
    max_value =0;
  }
	
  _ExtractionType at(_IndexType position) {
    if((typeBit[position/8] & (1 <<(position%8)) ) == 0) {
      return baseArray[position];
    } else {
      return extendedMap[position];
    }
  }

  _ExtractionType get_max_value() {
    return max_value;
  }

  _ExtractionType operator[](_IndexType position) {
    return at(position);
  }

  void insert(_IndexType position,_ExtractionType value) {
    if(value > max_value) max_value = value;

    if(value <= _BaseMax) {
      typeBit[position/8] = typeBit[position/8] | (1 << (position%8)); // set to 1
      baseArray[position] = value;
    } else {
      typeBit[position/8] = typeBit[position/8] & (0xFF - (1 << (position%8))); // set to 0
      extendedMap[position] = value;
    }
  }

   _ExtractionType load(std::istream &in,_BaseType break_symbol) {
    _ExtendedType breaks_count=0;
    _ExtendedType current_unique = _BaseMax+1;

    _BaseType c = in.get();
    for(;!in.eof();) {
      if(c == break_symbol) {
        push_back(current_unique);
        current_unique++;
        breaks_count++;
      } else {
        push_back(c);
      }
      c = in.get();
    }

    return breaks_count;
  }

  void load(std::istream &in) {
    _BaseType c = in.get();
    for(;!in.eof();) {
      push_back(c);
      c = in.get();
    }
  }

  void push_back(_ExtendedType i) {
    if(i > max_value) max_value = i;

    if(i < _BaseMax) {
      baseArray.push_back(i);

      if(typeBit.size() < (baseArray.size()/8+1)) typeBit.push_back(0);
      typeBit[(baseArray.size()-1)/8] = typeBit[(baseArray.size()-1)/8] & (0xFF - (1 << (((baseArray.size()-1)%8)))); // set to 0
    } else {
      baseArray.push_back(0);
      extendedMap[baseArray.size()-1] = i;

      if(typeBit.size() < (baseArray.size()/8+1)) typeBit.push_back(0);
      typeBit[(baseArray.size()-1)/8] = typeBit[(baseArray.size()-1)/8] | (1 << ((baseArray.size()-1)%8)); // set to 1
    }
  }

  _ExtractionType size() const {
    return baseArray.size();
  }
};


template <class _BaseType,int _BaseMax,class _ExtendedType,class _ExtractionType,class _IndexType>
inline std::ostream& operator<<(std::ostream& out, BasePlusArray<_BaseType,_BaseMax,_ExtendedType,_ExtractionType,_IndexType> &rhs) {
  
  for(int n=0;n<rhs.size();n++) {
    out << rhs[n] << ",";
  }
  return out;
}


#endif

