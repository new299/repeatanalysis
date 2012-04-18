#include <iostream>
#include <fstream>
using namespace std;

int main(int argc,char **argv) {
  if(argc < 3) {
    cout << "repchar <input file> <output file> [find] [replace]" << endl;
    cout << "Replace [find] with [replace] (characters specified as ASCII code)" << endl;
    cout << "find defaults to \"10\", replace to '#', number of matches is printed to stdout" << endl;
    return 0;
  }

  ifstream infile(argv[1]);
  ofstream outfile(argv[2]);
  if(!infile)  {cerr << "Can not open input file"  << endl; return -1;}
  if(!outfile) {cerr << "Can not open output file" << endl; return -1;}
  
  int find_char=10;
  int rep_char='#';

  if(argc > 3) {
    find_char=atoi(argv[3]);
  }

  if(argc > 4) {
    rep_char=atoi(argv[4]);
  }


  int marker=127;
  int num_breaks=0;
  for(;!infile.eof();) {
    char s;
    s = infile.get();
    if(!infile.eof()){
      if(s != find_char) outfile << s;
      else {outfile << (char) rep_char; num_breaks++;}
    }
  }
  infile.close();
  outfile.close();
  cout << num_breaks << endl;
}
