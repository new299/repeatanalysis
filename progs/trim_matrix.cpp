#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "stringify.h"
using namespace std;

int main(int argc,char **argv) {
  if(argc < 2) {
    cout << "trim_matrix <input file> <x> <y>" << endl;
    return 0;
  }

  int x_trim = convertTo<int>(argv[2]);
  int y_trim = convertTo<int>(argv[3]);

  ifstream infile(argv[1]);
  for(int y=0;!infile.eof() && (y<y_trim);y++) {
    
    stringstream ss(stringstream::in | stringstream::out);
    string str;
    getline(infile, str);

//    char s[1000000];
//    infile.getline(s,1000000);
    ss << str;
    if(!ss.eof()) {
      if(y<y_trim)
      for(int x=0;!ss.eof();x++) {
        int i;
        ss >> i;
        if(!ss.eof())
        if(x<x_trim) cout << i << " ";
      }
      if(y<y_trim) cout << endl;
    }
  }
  infile.close();
}
