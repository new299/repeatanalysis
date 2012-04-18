#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "stringify.h"
#include "offset2contigpos.h"

using namespace std;

class Offset2ContigPosHtml : public Offset2ContigPos {
  string htmltarget;

public:

  Offset2ContigPosHtml(const char *filename) : Offset2ContigPos(filename) { 
  }

  void set_htmltarget(string htmltarget_in) {
    htmltarget = htmltarget_in; 
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

    s = string("<A HREF=\"") + htmltarget + string("#") + stringify(contig) + string("\">") + stringify(contig) + string(",") + stringify(offset) + string("</A>");

    return s;
  }  
};
