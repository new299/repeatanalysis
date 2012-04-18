#include <iostream>
#include <fstream>
using namespace std;

int main(int argc,char **argv) {
  if(argc < 2) {
    cout << "repchar <input file> [symbol]" << endl;
    cout << "Output positions of [symbol] (characters specified as ASCII code)" << endl;
    cout << "symbol defaults to '#'" << endl;
    return 0;
  }

  ifstream infile(argv[1]);
  if(!infile)  {cerr << "Can not open input file"  << endl; return -1;}
  
  int find_symbol='#';

  if(argc > 3) {
    find_symbol=atoi(argv[3]);
  }

  int marker=127;
  int num_breaks=0;
  for(int n=0;!infile.eof();n++) {
    char s;
    s = infile.get();
    if(!infile.eof()){
      if(s == find_symbol) {
        cout << n << endl;
      }
    }
  }
  infile.close();
}
