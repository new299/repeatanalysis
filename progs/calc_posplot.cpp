#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "math.h"
#include "stringify.h"
using namespace std;

int main(int argc,char **argv) {
  if(argc < 2) {
    cout << "calc_posplot <input file>" << endl;
    return 0;
  }

  ifstream infile(argv[1]);

  vector<double> values;
  for(;!infile.eof();) {
    double i;
    string s;
    bool failed=false;
    infile >> s;

    try {
      i = convertTo<double>(s); 
    } catch(BadConversion e) {failed=true;}

    if(!failed && !infile.eof()) {
      values.push_back(i);
    }
  }

  for(vector<double>::iterator iter=values.begin();iter != values.end();iter++) {
    double sum =0;
    for(vector<double>::iterator iter1=values.begin();iter1 != values.end();iter1++) {
      if((*iter) != (*iter1)) sum += 1/fabs((*iter)-(*iter1));
    }
    cout << (*iter) << " " << sum << endl;
  }
}
