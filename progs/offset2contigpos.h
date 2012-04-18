#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "stringify.h"

using namespace std;
class Offset2ContigPosHtml;

class Offset2ContigPos {
protected:
  friend class Offset2ContigPosHtml;

  vector<int> contigs_start;

public:

  Offset2ContigPos(const char *filename) { 
    ifstream infile(filename);

    contigs_start.push_back(0);
    for(;!infile.eof();) {
      int i;
      infile >> i;
      if(!infile.eof()) contigs_start.push_back(i);
    }
    infile.close();
  }

  string convert(int position) {
    string s;

    int contig, offset;
    int n=0;
    bool found = false;
    for(vector<int>::iterator i = contigs_start.begin();i != contigs_start.end();i++,n++) {
      if(position < (*i)) {
       if(n==1) { contig = n-1; offset = position-(*(i-1));  }
           else { contig = n-1; offset = position-(*(i-1))-1;}
       found = true;
       break;
      }
    }

    if(found == false) {

       if(contigs_start.size()==1)
          { contig = contigs_start.size()-1; offset = position-contigs_start[contigs_start.size()-1]; }
       else
          { contig = contigs_start.size()-1; offset = position-contigs_start[contigs_start.size()-1]-1; }
    }

    s = stringify(contig) + string(",") + stringify(offset);

    return s;
  }  
};
