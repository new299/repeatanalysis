#include <iostream>
#include <fstream>
using namespace std;

int main(int argc,char **argv) {
  if(argc < 3) {
    cout << "add_uniquebreaks <input file> <output file> [marker]" << endl;
    return 0;
  }

  ifstream infile(argv[1]);
  ofstream outfile(argv[2]);
  if(!infile)  {cerr << "Can not open input file"  << endl; return -1;}
  if(!outfile) {cerr << "Can not open output file" << endl; return -1;}
  
  int break_marker=10;

  if(argc > 3) {
    break_marker=atoi(argv[3]);
  }

  int marker=127;
  int num_breaks=0;
  for(;!infile.eof();) {
    char s;
    s = infile.get();
    if(!infile.eof()){
      if(s != break_marker) outfile << s;
      else {outfile << (char) marker; marker++; num_breaks++;}
      if(marker > 255) cerr << "ERROR: More the 255 sequence breaks, out of unique markers" << endl;
    }
  }
  infile.close();
  outfile.close();
  cout << num_breaks << endl;
}
