#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "stringify.h"

using namespace std;

int main(int argc,char **argv) {
  if(argc < 3) {
    cout << "offset2contigposition <contig starts> <position>" << endl;
    return 0;
  }

  // load string into s

  vector<int> contigs_start;

  ifstream infile(argv[1]);

  int position = convertTo<int>(string(argv[2]));

  contigs_start.push_back(0);
  for(;!infile.eof();) {
    int i;
    infile >> i;
    if(!infile.eof()) contigs_start.push_back(i);
  }
  infile.close();

  int n=0;
  bool found = false;
  for(vector<int>::iterator i = contigs_start.begin();i != contigs_start.end();i++,n++) {
    if(position < (*i)) {
     if(n==1) cout << n-1 << "," << position-(*(i-1)) << endl;
         else cout << n-1 << "," << position-(*(i-1))-1 << endl;
     found = true;
     break;
    }
  }

  if(found == false) {

     if(contigs_start.size()==1) 
        cout << contigs_start.size()-1 << "," << position-contigs_start[contigs_start.size()-1] << endl;
     else 
        cout << contigs_start.size()-1 << "," << position-contigs_start[contigs_start.size()-1]-1 << endl;
  }

}
