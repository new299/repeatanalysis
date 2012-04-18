// $Id: main.cpp,v 1.1 2006/08/28 16:12:32 new Exp $
/// \file main.cpp
/// \author Nava Whiteford <new@soton.ac.uk>
/// $Revision: 1.1 $

#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std; 

int main(int argc, char **argv) {

  // parse command line options

  if(argc < 3) {
    cout << "reverseflat <input> <output>" << endl;
    cout << "create the reverse sequence" << endl;
    return 0;
  }

  ifstream infile(argv[1]);
  ofstream ofile(argv[2]);

  for(;!infile.eof();) {
    string str;
    getline(infile, str);

    for(string::reverse_iterator i=str.rbegin();i != str.rend();i++) {
      if((*i) == 'A') ofile << 'T'; else
      if((*i) == 'T') ofile << 'A'; else
      if((*i) == 'G') ofile << 'C'; else
      if((*i) == 'C') ofile << 'G'; else
                      ofile << (*i);
    }
    if(!infile.eof()) ofile << endl;
  }

  infile.close();
  ofile.close();
  cout << "reverse complete" << endl;

  return 0;
}
